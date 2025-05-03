/**
 * forkpty() utilities
 *
 * Copyright 2025 Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */
#ifndef pty__h
#define pty__h 1

#include <sys/types.h>

#include "extern_.h"

#ifdef __APPLE__
#include <util.h>
#else
/*#include <pty.h>*/
#endif

EXTERN_ pid_t forkpty_with_exec (int *fd_amaster);

EXTERN_ void kill_forkpty (const pid_t pid, const int fd);

#endif /* ! pty__h */
