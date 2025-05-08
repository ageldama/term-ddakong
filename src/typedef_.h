/**
 * 공통타입 정의
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#ifndef typedef__h
#define typedef__h 1

#include "extern_.h"
#include <stdint.h>

/**
 * 1-바이트
 *
 * C23-등에서 정의해주기 전에는 이렇게 적당히 쓰려고.
 */
#ifndef BYTE
#define BYTE char
#endif /* ! BYTE */

/**
 * "true" (BOOL)
 */
#ifndef TRUE
#define TRUE 1
#endif /* ! TRUE */

/**
 * "false" (BOOL)
 */
#ifndef FALSE
#define FALSE 0
#endif /* ! FALSE */

/**
 * BOOL-타입 (1바이트)
 */
#ifndef BOOL
#define BOOL char
#endif /* ! BOOL */

/**
 * 유니코드 코드값 (4바이트)
 *
 * UTF-8등 인코딩 전의 유니코드 코드포인트 정수값.
 */
#ifndef UNICODE_32
#define UNICODE_32 uint32_t
#endif /* ! UNICODE_32 */

#endif /* ! typedef__h */
