/**
 * 커맨드라인/설정을 반영하는 전역변수
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#ifndef global_flags_h
#define global_flags_h 1

#include "extern_.h"

#include <stdio.h>
#include <sys/types.h>

/**
 * (BOOL) "verbose logging" 할지?
 */
EXTERN_ int verbose_flag;

/**
 * (sz-string, nullable) 키로깅 파일이름. NULL-이면 키로깅 하지않음.
 */
EXTERN_ char *keylog_filename;

EXTERN_ char *default_keylog_filename;

EXTERN_ int child_fd;

EXTERN_ pid_t child_pid;

/**
 * (sz, nullable) 플러그인 DLL 파일경로. NULL-이면 로딩하지 않음.
 */
EXTERN_ char *plugin_dll_filename;

void print_banner (FILE *fp);

/**
 * 커맨드라인 처리함수
 *
 * @see getopt
 */
EXTERN_ void do_getopt (int argc, char **argv);

#endif /* ! global-flags_h */
