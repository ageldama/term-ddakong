/**
 * forkpty() utilities
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */
#ifndef pty__h
#define pty__h 1

#include "extern_.h"   /* for EXTERN_ */
#include <sys/types.h> /* for pid_t */

#ifdef __APPLE__
#include <util.h>
#else
/* #include <pty.h> */
#endif

/**
 * forkpty + exec
 *
 * forkpty 실행하여 하위-pty 생성후, exec하여 쉘실행.
 *
 * 쉘은 "SHELL"-환경변수를 읽어 실행. (환경변수가 없다면 "/bin/sh")
 *
 * *WARNING* 쉘환경변수는 커맨드라인 shell-lexer이 적용되지 않는, 단순
 * 실행파일 경로여야 함.
 *
 * 생성한 하위-pty의 file-descriptor을 non-blocking mode으로 설정.
 *
 * @see forkpty()
 *
 * @see execlp()
 *
 * @see getenv()
 *
 * @param fd_amaster (non-null) forkpty()-한 pty-file-descriptor을 전달
 * 받을 포인터.
 *
 * @return exec()-한 프로세스id
 */
EXTERN_ pid_t forkpty_with_exec (int *fd_amaster);

/**
 * forkpty() / exec()-한 프로세스/pty-fd을 종료처리
 *
 * @see kill()
 *
 * @see waitpid()
 *
 * @param pid 종료할 프로세스id
 *
 * @param fd 닫을 pty-file-descriptor
 */
EXTERN_ void kill_forkpty (const pid_t pid, const int fd);

#endif /* ! pty__h */
