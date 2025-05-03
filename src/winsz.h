/**
 * termios "window-size" + pty-child process
 *
 * Copyright 2025 Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
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
