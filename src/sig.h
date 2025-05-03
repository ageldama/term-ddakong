/**
 * Unix signal handling utilities
 *
 * Copyright 2025 Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#ifndef sig_h
#define sig_h 1

#include <sys/types.h>

#include "extern_.h"

/**
 * `signo'-시그널 처리함수("sigaction")을 설정
 *
 * NOTE: "_norecover"-인 이유는, 원래의 시그널핸들러를 별도로
 * 되돌리거나 저장해두지 않기 때문. (프로세스가 종료되면 자동으로
 * 복구되므로)
 *
 * @param signo trap할 시그널번호
 *
 * @param handler 시그널처리함수
 */
EXTERN_ void signal_trap_norecover (const int signo, void (*handler) (int));

#endif /* ! sig_h */
