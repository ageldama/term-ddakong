/**
 * 조합중인 글자(pre-edit) 터미널 표시
 *
 * Copyright Sungjoon Moon <sumoon@seoulsaram.org>, 2026. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#ifndef preedit__h
#define preedit__h 1

#include <unistd.h>

#include "extern_.h"
#include "typedef_.h"

/**
 * preedit 표시 준비
 *
 * carry-pipe 생성: DSR/CPR 커서위치 응답을 기다리는 동안 끼어든
 * 키입력을 보관했다가 다시 처리하기 위한 self-pipe.
 *
 * @see preedit_carry_fd()
 *
 * @param fd_term_out 터미널 출력 fd (보통 STDOUT_FILENO)
 *
 * @param fd_term_in 터미널 입력 fd (보통 STDIN_FILENO)
 */
EXTERN_ void preedit_init (const int fd_term_out, const int fd_term_in);

/**
 * carry-pipe의 read-end fd
 *
 * 메인루프에서 polling에 추가하여, 읽을 수 있게 되면 키입력처럼
 * 처리해야 함. (stdin보다 먼저: 시간상 더 앞선 입력이므로)
 *
 * @return fd, 준비되지 않았다면 -1.
 */
EXTERN_ int preedit_carry_fd (void);

/**
 * 화면에 표시중인 preedit 글자를 지우고, 커서를 입력지점으로 복귀
 *
 * 표시중이 아니라면 아무 것도 하지 않음.
 *
 * 터미널에 다른 출력(자식 echo/출력 등)을 쓰기 전에 반드시 호출할
 * 것.
 */
EXTERN_ void preedit_erase (void);

/**
 * 한글오토마타의 조합중 글자를 화면에 표시
 *
 * preedit 비활성(-P), 오토마타 비어있음, 조합 불가능 상태라면 아무
 * 것도 하지 않음.
 *
 * 입력지점을 모르면 DSR(ESC[6n)으로 커서위치를 질의. 터미널이
 * 응답하지 않으면 preedit 기능을 스스로 비활성화.
 *
 * 우측 끝에서 2칸 폭이 들어가지 못하면 다음 줄 첫칸에 표시하며,
 * 최하단 줄에서는 한 줄 스크롤 후 표시.
 */
EXTERN_ void preedit_draw (void);

/**
 * 기억해둔 입력지점(커서위치)을 무효화
 *
 * 자식 출력 등으로 커서가 움직였을 수 있을 때 호출. 다음
 * preedit_draw()에서 커서위치를 다시 질의함.
 */
EXTERN_ void preedit_invalidate (void);

/**
 * 터미널 크기변경(SIGWINCH) 처리
 *
 * reflow으로 화면이 재배치되므로, 표시상태/입력지점을 모두 버림.
 */
EXTERN_ void preedit_on_resize (void);

#endif /* ! preedit__h */
