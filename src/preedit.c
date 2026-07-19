/**
 * 조합중인 글자(pre-edit) 터미널 표시
 *
 * Copyright Sungjoon Moon <sumoon@seoulsaram.org>, 2026. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#include "preedit.h"

#include <ctype.h>
#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "cc_nanny.h"
#include "global_flags.h"
#include "hangeul.h"
#include "im_handler_hangeul.h"
#include "utf8_.h"

/** DSR(ESC[6n) 커서위치 응답 대기시간 (밀리초) */
#ifndef preedit__CPR_TIMEOUT_MILLIS
#define preedit__CPR_TIMEOUT_MILLIS 200
#endif

/** CPR 응답 대기중 carry-pipe으로 보관할 최대 바이트수 */
#ifndef preedit__CPR_CARRY_MAX
#define preedit__CPR_CARRY_MAX 256
#endif

static int _fd_out = -1;
static int _fd_in = -1;

/** carry-pipe: [0]=read-end, [1]=write-end */
static int _carry_pipe[2] = { -1, -1 };

/** preedit 글자가 화면에 표시중인지 */
static BOOL _shown = FALSE;

/** _row/_col 이 유효한지 */
static BOOL _pos_valid = FALSE;

/** 표시중인 preedit이 입력지점 다음줄 첫칸에 그려졌는지 */
static BOOL _wrapped = FALSE;

/** 입력지점 (1-based) : 자식이 다음 출력을 이어갈 커서위치 */
static int _row = 0, _col = 0;

/** 터미널 크기 (마지막 질의시점) */
static int _rows = 0, _cols = 0;

void
preedit_init (const int fd_term_out, const int fd_term_in)
{
  _fd_out = fd_term_out;
  _fd_in = fd_term_in;

  if (-1 == pipe (_carry_pipe))
    {
      perror ("pipe: preedit carry");
      _carry_pipe[0] = _carry_pipe[1] = -1;
    }
}

int
preedit_carry_fd (void)
{
  return _carry_pipe[0];
}

void
preedit_invalidate (void)
{
  _pos_valid = FALSE;
}

void
preedit_on_resize (void)
{
  /* reflow으로 표시위치를 알 수 없게 됨: 지우려고 하지도 말 것 */
  _shown = FALSE;
  _pos_valid = FALSE;
}

static void
_carry_put (const BYTE *buf, const ssize_t len)
{
  if (len > 0 && _carry_pipe[1] != -1)
    {
      ssize_t n UNUSED = write (_carry_pipe[1], buf, (size_t)len);
    }
}

/**
 * DSR 커서위치 응답(CPR: `ESC[row;colR`) 읽기
 *
 * 응답 앞에 끼어든 (사용자 키입력) 바이트들은 carry-pipe에 순서대로
 * 보관.
 *
 * @return 응답을 파싱했다면 TRUE, 타임아웃/에러 FALSE.
 */
static BOOL
_read_cpr (int *p_row, int *p_col)
{
  BYTE seq[16];
  ssize_t seq_len = 0;
  ssize_t n_carried = 0;

  while (n_carried < preedit__CPR_CARRY_MAX)
    {
      struct pollfd pfd = { .fd = _fd_in, .events = POLLIN };
      int n_evt = poll (&pfd, 1, preedit__CPR_TIMEOUT_MILLIS);
      if (n_evt == -1 && errno == EINTR)
        continue;
      if (n_evt <= 0)
        return FALSE; /* timeout */

      BYTE ch;
      if (1 != read (_fd_in, &ch, 1))
        return FALSE;

      if (seq_len == 0)
        {
          if (ch == '\x1b')
            seq[seq_len++] = ch;
          else
            {
              _carry_put (&ch, 1);
              n_carried++;
            }
          continue;
        }

      /* CPR 시퀀스가 아니게 되면: 지금까지 모은 것을 carry으로 */
      BOOL ok = (seq_len == 1)
                    ? (ch == '[')
                    : (isdigit ((unsigned char)ch) || ch == ';' || ch == 'R');
      if (!ok || seq_len >= (ssize_t)sizeof (seq) - 2)
        {
          _carry_put (seq, seq_len);
          n_carried += seq_len;
          seq_len = 0;

          if (ch == '\x1b')
            seq[seq_len++] = ch;
          else
            {
              _carry_put (&ch, 1);
              n_carried++;
            }
          continue;
        }

      seq[seq_len++] = ch;

      if (ch == 'R')
        {
          seq[seq_len] = '\0';
          if (2 == sscanf ((char *)seq + 1, "[%d;%dR", p_row, p_col))
            return TRUE;

          _carry_put (seq, seq_len);
          n_carried += seq_len;
          seq_len = 0;
        }
    }

  return FALSE;
}

/**
 * 터미널크기 + 커서위치(입력지점) 질의
 */
static BOOL
_query_input_point (void)
{
  struct winsize winsz;
  /* TODO => winsz.c? */
  if (-1 == ioctl (_fd_in, TIOCGWINSZ, &winsz))
    return FALSE;
  _rows = winsz.ws_row;
  _cols = winsz.ws_col;

  if (4 != write (_fd_out, "\x1b[6n", 4))
    return FALSE;

  return _read_cpr (&_row, &_col);
}

void
preedit_erase (void)
{
  if (!_shown)
    return;

  char seq[64];
  int n;

  if (_wrapped)
    {
      /* 다음줄 첫칸의 2칸을 지우고, 입력지점으로 복귀 */
      n = snprintf (seq, sizeof (seq), "\x1b[%d;1H  \x1b[%d;%dH", _row + 1,
                    _row, _col);
    }
  else
    {
      n = snprintf (seq, sizeof (seq), "\x1b[%d;%dH  \x1b[%d;%dH", _row, _col,
                    _row, _col);
    }

  ssize_t n_written UNUSED = write (_fd_out, seq, (size_t)n);
  _shown = FALSE;
}

void
preedit_draw (void)
{
  if (!preedit_flag)
    return;

  if (_shown)
    preedit_erase ();

  hangeul_automata_status *p_status = &_hangeul_avtomat;
  if (hangeul_empty_automata_status_p (p_status))
    return;

  UNICODE_32 unich = hangeul_auto_compose_to_unicode (
      p_status->cho, p_status->jung, p_status->jong);
  if (unich == 0x00)
    return;

  BYTE utf8[8];
  int utf8_len = unicode_to_utf8 (unich, utf8);
  if (utf8_len <= 0)
    return;

  if (!_pos_valid)
    {
      if (!_query_input_point ())
        {
          /* 커서위치를 모르면 지울 수도 없으므로, 표시하지 않음 */
          preedit_flag = 0;
          if (verbose_flag)
            {
              fprintf (stderr,
                       "# preedit: no cursor position report, disabled\n");
            }
          return;
        }
      _pos_valid = TRUE;
    }

  char seq[64];
  int n;

  if (_cols <= 0 || _col + 1 <= _cols)
    {
      /* 한글은 2칸 폭: 입력지점에 들어감 */
      _wrapped = FALSE;
      n = snprintf (seq, sizeof (seq), "\x1b[%d;%dH", _row, _col);
    }
  else if (_row < _rows)
    {
      /* 우측 끝: 다음줄 첫칸에 표시 */
      _wrapped = TRUE;
      n = snprintf (seq, sizeof (seq), "\x1b[%d;1H", _row + 1);
    }
  else
    {
      /* 우측 끝 + 최하단: 한 줄 스크롤. 입력지점도 한 줄 위로 */
      _wrapped = TRUE;
      n = snprintf (seq, sizeof (seq), "\x1b[%d;1H\n", _row);
      _row -= 1;
    }

  ssize_t n_written UNUSED = write (_fd_out, seq, (size_t)n);
  n_written = write (_fd_out, utf8, (size_t)utf8_len);
  _shown = TRUE;
}
