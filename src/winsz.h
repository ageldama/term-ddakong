/**
 * termios "window-size" + pty-child process
 *
 * copyright 2025 <ageldama@gmail.com>, 2025. all rights reserved. use
 * of this source code is governed by a gplv3 license that can be
 * found in the license file.
 */

#ifndef winsz_h
#define winsz_h 1

#include "extern_.h"

/**
 * 현재 프로세스의 "termios window-size"-을 얻어서,
 * child_fd(pty child)-에 그대로 적용하기.
 *
 * @param child_fd 윈도크기를 복사 받을 대상 fd
 */
EXTERN_ void winsz_update (const int child_fd);

#endif /* ! winsz_h */
