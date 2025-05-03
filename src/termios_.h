/**
 * termios init/reset
 *
 * copyright 2025 <ageldama@gmail.com>, 2025. all rights reserved. use
 * of this source code is governed by a gplv3 license that can be
 * found in the license file.
 */

#ifndef termios__h
#define termios__h 1

#include "extern_.h"

/**
 * termios 상태세팅
 *
 * 이후 termios__reset()-에서 복구할 수 있도록, 전역변수에 원래상태를
 * 저장.
 *
 * 다음과 같이 설정:
 *
 * - ECHO : 선택에 따라 설정 (`echo'-파라미터)
 *
 * - STRIP, CANON : buffering등 적용 끔.
 *
 * - SIG : Control-C 등 처리를 받지 않고, pty-child에 그대로
 *   forwarding하기 위해 끔.
 *
 * @param echo "echo"-모드 켤지? (BOOL)
 */
EXTERN_ void termios__init (int echo);

/**
 * termios 상태복구
 *
 * termios__init()-에서 저장해둔 원래 상태를 사용.
 */
EXTERN_ void termios__reset (void);

#endif /* ! termios__h */
