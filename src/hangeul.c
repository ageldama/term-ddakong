/**
 * 한글/2벌식 => 유니코드 오토마타
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#include "hangeul.h"

#include <assert.h>
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>

#include "err.h"

UNICODE_32
hangeul_auto_compose_to_unicode (const BYTE cho, const BYTE jung,
                                 const BYTE jong)
{
  if (hangeul_partial_jamo_p (cho, jung, jong))
    return hangeul_jamo_compose_to_unicode (cho, jung, jong);
  return hangeul_full_compose_to_unicode (cho, jung, jong);
}

UNICODE_32
hangeul_jamo_compose_to_unicode (const BYTE cho, const BYTE jung,
                                 const BYTE jong)
{
  if (cho == CHOJUNGJONG_NUL && jung == CHOJUNGJONG_NUL
      && jong == CHOJUNGJONG_NUL)
    return 0x00;

  if (cho != CHOJUNGJONG_NUL && jung == CHOJUNGJONG_NUL)
    {
      return hangeul_jamo_jaeum_to_unicode (CHOSEONG, cho);
    }
  else if (jung != CHOJUNGJONG_NUL)
    {
      return (UNICODE_32)(0x314f + jung);
    }
  else if (jong != CHOJUNGJONG_NUL)
    {
      return hangeul_jamo_jaeum_to_unicode (JONGSEONG, jong);
    }

  return 0x00;
}

UNICODE_32
hangeul_full_compose_to_unicode (const BYTE cho, const BYTE jung,
                                 const BYTE jong)
{
  /* it's kind of magic */
  UNICODE_32 cho_ = 0;
  if (cho != CHOJUNGJONG_NUL)
    cho_ = ((UNICODE_32)cho * 588);
  UNICODE_32 jung_ = 0;
  if (jung != CHOJUNGJONG_NUL)
    jung_ = ((UNICODE_32)jung * 28);
  UNICODE_32 jong_ = 0;
  if (jong != CHOJUNGJONG_NUL)
    jong_ = ((UNICODE_32)jong);
  return cho_ + jung_ + jong_ + 44032;
}

BOOL
hangeul_partial_jamo_p (const BYTE cho, const BYTE jung, const BYTE jong)
{
  if (cho != CHOJUNGJONG_NUL && jung == CHOJUNGJONG_NUL)
    return TRUE;

  if (cho == CHOJUNGJONG_NUL && jung != CHOJUNGJONG_NUL)
    return TRUE;

  if (cho == CHOJUNGJONG_NUL && jong != CHOJUNGJONG_NUL)
    return TRUE;

  /* otherwise: */
  return FALSE;
}

void
hangeul_clear_automata_status (hangeul_automata_status *p_status)
{
  if (p_status == NULL)
    return;

  p_status->stage = CHOJUNGJONG_NUL;
  p_status->prev_ch = 0x00;
  p_status->cho = CHOJUNGJONG_NUL;
  p_status->jung = CHOJUNGJONG_NUL;
  p_status->jong = CHOJUNGJONG_NUL;
}

BOOL
hangeul_empty_automata_status_p (const hangeul_automata_status *p_status)
{
  if (p_status == NULL)
    return TRUE;
  else if (p_status->stage == CHOJUNGJONG_NUL
           || (p_status->cho == CHOJUNGJONG_NUL
               && p_status->jung == CHOJUNGJONG_NUL
               && p_status->jong == CHOJUNGJONG_NUL))
    return TRUE;
  /* otherwise: */
  return FALSE;
}

void
hangeul_put_unicode (UNICODE_32 *outbuf, const ssize_t outbuf_max,
                     ssize_t *p_pos, UNICODE_32 ch)
{
  assert ((*p_pos) + 1
          <= outbuf_max); /* programming-error: allocate more buffer */
  outbuf[*p_pos] = ch;
  (*p_pos)++;
}

JAMOEUM
hangeul_2beol_alpha_as_jamoeum (const BYTE ch)
{
  assert (isalpha (ch)); /* programming error: pass only `alpha' */
  BYTE upch = (BYTE)toupper (ch);

  switch (upch)
    {
    case 'Q':
    case 'W':
    case 'E':
    case 'R':
    case 'T':
    case 'A':
    case 'S':
    case 'D':
    case 'F':
    case 'G':
    case 'Z':
    case 'X':
    case 'C':
    case 'V':
      return JAEUM;

    default:
      return MOEUM;
    }
}


ssize_t
hangeul_2beol_fill (const BYTE ch, hangeul_automata_status *p_status,
                    UNICODE_32 *outbuf, const ssize_t outbuf_max)
{
  ssize_t cur_pos = 0;

  /* 비-한글입력: */
  if (!isalpha (ch))
    {
      if (!hangeul_empty_automata_status_p (p_status))
        {
          hangeul_2beol_commit_1_and_flush (p_status, outbuf, outbuf_max,
                                            &cur_pos);
        }
      hangeul_put_unicode (outbuf, outbuf_max, &cur_pos, (UNICODE_32)ch);

      p_status->stage = CHOJUNGJONG_NUL;
      p_status->prev_ch = 0x00;
      return cur_pos;
    }

  /* 한글입력일 때: */
  JAMOEUM jamoeum = hangeul_2beol_alpha_as_jamoeum (ch);

  if (JAEUM == jamoeum)
    { /* 자음 */
      switch (p_status->stage)
        {
        case CHOJUNGJONG_NUL:
          /* (상태:NUL)
             => state((*1st*)초성, input->초성)
          */
          p_status->stage = CHOSEONG;
          p_status->cho = hangeul_2beol_find_code (CHOSEONG, ch);
          break;

        case CHOSEONG:
          /* (상태:초성)
             => 2중초성-p(state:초성, input),
             state((*2nd*)초성, combined->초성);
             commit(prev), state((*1st*)초성, input->초성).
          */
          BYTE dbl_cho
              = hangeul_double_jaeum (CHOSEONG, p_status->prev_ch, ch);

          if (dbl_cho != CHOJUNGJONG_NUL)
            {
              if (p_status->cho == dbl_cho)
                {
                  /* 이미, 2중초성 */
                  /* (eg) ㄲㄲㄲㄲㄲㄲㄲㄲㄲ-연사 */
                  hangeul_2beol_commit_1_and_flush (p_status, outbuf,
                                                    outbuf_max, &cur_pos);

                  p_status->stage = CHOSEONG;
                  p_status->cho = hangeul_2beol_find_code (CHOSEONG, ch);
                  p_status->jung = CHOJUNGJONG_NUL;
                  p_status->jong = CHOJUNGJONG_NUL;
                }
              else
                {
                  /* 2중 초성 */
                  p_status->stage = CHOSEONG;
                  p_status->cho = dbl_cho;
                }
            }
          else
            {
              /* 2중 종성으로 만들 수 있으면,
                 그렇게 조합한 종성 하나만 commit. */
              BYTE dbl_jong
                  = hangeul_double_jaeum (JONGSEONG, p_status->prev_ch, ch);

              if (dbl_jong != CHOJUNGJONG_NUL)
                {
                  p_status->stage = JONGSEONG;
                  p_status->cho = CHOJUNGJONG_NUL;
                  p_status->jung = CHOJUNGJONG_NUL;
                  p_status->jong = dbl_jong;
                  hangeul_2beol_commit_1_and_flush (p_status, outbuf,
                                                    outbuf_max, &cur_pos);
                }
              else
                {
                  hangeul_2beol_commit_1_and_flush (p_status, outbuf,
                                                    outbuf_max, &cur_pos);

                  p_status->stage = CHOSEONG;
                  p_status->cho = hangeul_2beol_find_code (CHOSEONG, ch);
                }
            }
          break;

        case JUNGSEONG:
          /* (상태:중성)
             => state(종성, input->종성)
          */
          p_status->stage = JONGSEONG;
          p_status->jong = hangeul_2beol_find_code (JONGSEONG, ch);
          break;

        case JONGSEONG:
          /* (상태:종성)
             => 2중종성-p(state:종성, input),
             state(두번째 종성,->종성);
             commit(prev), state(new, input->초성).
          */
          BYTE dbl_jong
              = hangeul_double_jaeum (JONGSEONG, p_status->prev_ch, ch);

          if (dbl_jong != CHOJUNGJONG_NUL)
            {
              p_status->stage = JONGSEONG;
              p_status->jong = dbl_jong; /* 2중 종성 */
            }
          else
            {
              hangeul_2beol_commit_1_and_flush (p_status, outbuf, outbuf_max,
                                                &cur_pos);

              p_status->stage = CHOSEONG;
              p_status->cho = hangeul_2beol_find_code (CHOSEONG, ch);
            }
          break;

        default:
          break;
        }
    }
  else
    { /* 모음 */
      switch (p_status->stage)
        {
        case CHOJUNGJONG_NUL:
          /* (상태:NUL)
             => state(NUL, ->NUL), commit(input).
          */
          p_status->stage = CHOJUNGJONG_NUL;
          hangeul_put_jamo_unicode (outbuf, outbuf_max, &cur_pos, JUNGSEONG,
                                    ch);
          break;

        case CHOSEONG:
          /* (상태:초성)
             => state(중성, input->중성).
          */
          p_status->stage = JUNGSEONG;
          p_status->jung = hangeul_2beol_find_code (JUNGSEONG, ch);
          break;

        case JUNGSEONG:
          /* (상태:중성)
             => 2중중성-p(state:중성, input),
             state(두번째 중성, prev + input ->중성);
             commit(prev), commit(input).
          */
          BYTE dbl_jung
              = hangeul_double_jaeum (JUNGSEONG, p_status->prev_ch, ch);

          if (dbl_jung != CHOJUNGJONG_NUL)
            {
              /* 중성 => 2중-중성 ( (eg) 까마귀 ) */
              p_status->stage = JUNGSEONG;
              p_status->jung = dbl_jung;
            }
          else
            {
              hangeul_2beol_commit_1_and_flush (p_status, outbuf, outbuf_max,
                                                &cur_pos);
              hangeul_put_jamo_unicode (outbuf, outbuf_max, &cur_pos,
                                        JUNGSEONG, ch);
              p_status->stage = CHOJUNGJONG_NUL;
            }
          break;

        case JONGSEONG:
          /* (상태:종성)
             => commit(prev + left(decomposed-종성(prev))),
             state(중성, right(decomposed-종성(prev))->초성, input->중성).
          */
          BYTE jong_left = CHOJUNGJONG_NUL;
          BYTE jong_right = CHOJUNGJONG_NUL;

          int n_decomposed = hangeul_decompose_jongseong (
              p_status->jong, &jong_left, &jong_right);

          if (n_decomposed == 2)
            { /* 분리해서 분배. (eg) 밝+ㅏ => 발가. */
              p_status->jong = jong_left;
              hangeul_2beol_commit_1_and_flush (p_status, outbuf, outbuf_max,
                                                &cur_pos);

              p_status->stage = JUNGSEONG;
              p_status->cho
                  = hangeul_remap_code (JONGSEONG, CHOSEONG, jong_right);
              p_status->jung = hangeul_2beol_find_code (JUNGSEONG, ch);
            }
          else if (n_decomposed <= 1)
            {
              /* 분리가능한 종성이 아니라면, 다음 모음에 뺏김.
               *
               * (eg) 발+ㅏ => 바라.
               */
              p_status->stage = JUNGSEONG;
              BYTE stolen_jong = p_status->jong;
              p_status->jong = CHOJUNGJONG_NUL;
              hangeul_2beol_commit_1_and_flush (p_status, outbuf, outbuf_max,
                                                &cur_pos);

              p_status->stage = JUNGSEONG;
              /* 종성=>초성 */
              p_status->cho
                  = hangeul_remap_code (JONGSEONG, CHOSEONG, stolen_jong);
              p_status->jung = hangeul_2beol_find_code (JUNGSEONG, ch);
            }
          break;

        default:
          break;
        }
    }

  p_status->prev_ch = ch;
  return cur_pos;
}

BYTE
hangeul_remap_code (const CHOJUNGJONG from_cjj, const CHOJUNGJONG to_cjj,
                    const BYTE from_code)
{
  BYTE *from_lut = NULL;
  switch (from_cjj)
    {
    case CHOSEONG:
      from_lut = (BYTE *)_cho_code_to_2beol_lut;
      break;
    case JUNGSEONG:
      from_lut = (BYTE *)_jung_code_to_2beol_lut;
      break;
    case JONGSEONG:
      from_lut = (BYTE *)_jong_code_to_2beol_lut;
      break;
    default:
      assert ("programming-error: allowed only CHOJUNGJONG" == NULL);
    }

  BYTE from_ch = from_lut[(int)from_code];
  return hangeul_2beol_find_code (to_cjj, from_ch);
}

BYTE
hangeul_2beol_find_code (const CHOJUNGJONG chojungjong, const BYTE ch)
{
  BYTE *lut = NULL;
  ssize_t lut_len = 0;
  switch (chojungjong)
    {
    case CHOSEONG:
      lut = (BYTE *)_cho_code_to_2beol_lut;
      lut_len = _cho_code_to_2beol_lut_len;
      break;
    case JUNGSEONG:
      lut = (BYTE *)_jung_code_to_2beol_lut;
      lut_len = _jung_code_to_2beol_lut_len;
      break;
    case JONGSEONG:
      lut = (BYTE *)_jong_code_to_2beol_lut;
      lut_len = _jong_code_to_2beol_lut_len;
      break;
    default:
      assert ("programming-error: allowed only CHOJUNGJONG" == NULL);
    }

  for (BYTE i = 0; i < lut_len; i++)
    {
      BYTE cur_ch = lut[(ssize_t)i];

      if (CHOJUNGJONG_NUL == cur_ch)
        continue;

      if (cur_ch == ch)
        {
          return i;
        }
    }

  /* otherwise: */
  return (BYTE)CHOJUNGJONG_NUL;
}

BYTE
hangeul_double_jaeum (const CHOJUNGJONG chojungjong, const BYTE prev_ch,
                      const BYTE ch)
{
  BYTE **lut = NULL;
  ssize_t lut_len = 0;
  switch (chojungjong)
    {
    case CHOSEONG:
      lut = (BYTE **)_cho_chord_to_2beol_lut;
      lut_len = _cho_chord_to_2beol_lut_len;
      break;
    case JUNGSEONG:
      /* NOTE 함수이름은 "자음"-이지만, 모음도 처리 데헷! */
      lut = (BYTE **)_jung_chord_to_2beol_lut;
      lut_len = _jung_chord_to_2beol_lut_len;
      break;
    case JONGSEONG:
      lut = (BYTE **)_jong_chord_to_2beol_lut;
      lut_len = _jong_chord_to_2beol_lut_len;
      break;
    default:
      assert ("programming-error: allowed only CHOJUNGJONG" == NULL);
    }

  for (BYTE i = 0; i < lut_len; i++)
    {
      BYTE *cur_sz = lut[(ssize_t)i];

      if (NULL == cur_sz)
        continue;

      if (cur_sz[0] == prev_ch && cur_sz[1] == ch)
        {
          return i;
        }
    }

  /* otherwise: */
  return (BYTE)CHOJUNGJONG_NUL;
}

EXTERN_ UNICODE_32
hangeul_2beol_commit_1_and_flush (hangeul_automata_status *p_status,
                                  UNICODE_32 *outbuf, const ssize_t outbuf_max,
                                  ssize_t *p_cur_pos)
{
  UNICODE_32 prev_code = hangeul_flush_automata_status (p_status);
  if (prev_code != 0x00)
    {
      hangeul_put_unicode (outbuf, outbuf_max, p_cur_pos, prev_code);
    }
  return prev_code;
}

UNICODE_32
hangeul_flush_automata_status (hangeul_automata_status *p_status)
{
  if (p_status == NULL)
    return 0x00;

  /* -- */
  UNICODE_32 unich = 0x00;

  if (!hangeul_empty_automata_status_p (p_status))
    {
      unich = hangeul_auto_compose_to_unicode (p_status->cho, p_status->jung,
                                               p_status->jong);
    }

  hangeul_clear_automata_status (p_status);

  return unich;
}

int
hangeul_decompose_jongseong (const BYTE jongseong, BYTE *pout_left,
                             BYTE *pout_right)
{
  if (jongseong >= _jong_chord_to_2beol_lut_len)
    {
      return 0;
    }

  /* 분해가능한지? */
  const char *sz_chord = _jong_chord_to_2beol_lut[(int)jongseong];
  if (NULL == sz_chord)
    {
      *pout_left = jongseong;
      return 1;
    }

  /* 분해 */
  *pout_left = hangeul_2beol_find_code (JONGSEONG, sz_chord[0]);
  *pout_right = hangeul_2beol_find_code (JONGSEONG, sz_chord[1]);
  return 2;
}

UNICODE_32
hangeul_put_jamo_unicode (UNICODE_32 *outbuf, const ssize_t outbuf_max,
                          ssize_t *p_pos, CHOJUNGJONG cjj, BYTE ch)
{
  BYTE code = hangeul_2beol_find_code (cjj, ch);
  BYTE cho = CHOJUNGJONG_NUL;
  BYTE jung = CHOJUNGJONG_NUL;
  BYTE jong = CHOJUNGJONG_NUL;

  switch (cjj)
    {
    case CHOSEONG:
      cho = code;
      break;
    case JUNGSEONG:
      jung = code;
      break;
    case JONGSEONG:
      jong = code;
      break;
    }

  UNICODE_32 unich = 0x00;

  if (code != CHOJUNGJONG_NUL)
    {
      UNICODE_32 unich = hangeul_jamo_compose_to_unicode (cho, jung, jong);
      if (unich != 0x00)
        {
          hangeul_put_unicode (outbuf, outbuf_max, p_pos, unich);
        }
    }

  return unich;
}

UNICODE_32
hangeul_jamo_jaeum_to_unicode (const CHOJUNGJONG cjj, const BYTE code)
{
  for (int i = 0; i < _jamo_jaeum_unicode_2beol_lut_len; i++)
    {
      hangeul_jamo_jaeum_unicode_2beol_row_t row
          = _jamo_jaeum_unicode_2beol_lut[i];

      if (row.cjj == cjj && row.code == code)
        {
          return row.unicode;
        }
    }

  /* not found: */
  return 0x00;
}
