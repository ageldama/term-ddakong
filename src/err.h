/**
 * Simple error facility for plain-C
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#ifndef err_h
#define err_h 1

#include <stdio.h>
#include <stdlib.h>

#include "extern_.h"
#include "typedef_.h"

/**
 * `ERR'-구조체의 `ERR.errmsg'-을 해제하는 함수.
 */
typedef void (*ERR_errmsg_free) (void *_Nullable);

/**
 * 에러메시지 구조체
 */
typedef struct
{
  /** 에러메시지 (nullable) */
  char *errmsg;

  /** 에러메시지 해제함수 (nullable) */
  ERR_errmsg_free errmsg_free;
} ERR;

/**
 * 에러메시지 구조체가 에러를 담고 있는지, 비어 있는지?
 *
 * @param p_err 에러구조체 (non-null)
 *
 * @return BOOL
 */
EXTERN_ BOOL ERR_err_p (const ERR *p_err);

/**
 * 에러메시지 구조체의 필드들을 모두 비우기
 *
 * `errmsg_free'-함수와 `errmsg`-이 할당되어 있다면,
 * 이 함수를 호출하여 `errmsg'-의 메모리를 해제.
 *
 * @param p_err 에러구조체 (non-null)
 */
EXTERN_ void ERR_clear (ERR *p_err);

/**
 * 에러메시지를 assign.
 *
 * *WARNING* 기존에 세팅된 `errmsg', `errmsg_free' 필드를 자동으로
 * 정리해주지 않습니다.
 *
 * @param p_err
 *
 * @param errmsg 에러메시지 문자열 (sz, non-null)
 *
 * @param errmsg_free 에러메시지 해제함수 (nullable)
 */
EXTERN_ void ERR_set (ERR *p_err, const char *errmsg,
                      ERR_errmsg_free errmsg_free);

/**
 * 에러메시지 해제가 불필요한 에러메시지를 assign.
 *
 * *WARNING* 기존에 세팅된 `errmsg`, `errmsg_free' 필드를 자동으로
 * 정리해주지 않습니다.
 *
 * @param p_err
 *
 * @param errmsg 에러메시지 문자열 (sz, non-null)
 */
#define ERR_set_nofree(p_err, errmsg) (ERR_set (p_err, errmsg, NULL))

EXTERN_ void ERR_set_nofree_fn (ERR *p_err, const char *sz_errmsg);

/**
 * 에러메시지를 printf.
 *
 * `errmsg'-을 위한 메모리를 할당하고, 해제함수(`errmsg_free')도
 * 자동으로 설정해줌.
 *
 * @param p_err (non-null)
 *
 * @param errmsg_fmt `sprintf' 포매팅문자열
 */
EXTERN_ char *ERR_printf (ERR *p_err, const char *errmsg_fmt, ...);

/**
 * 에러가 있다면(`ERR_err_p'), 프로세스를 강제종료.
 *
 * @param p_err (non-null)
 */
EXTERN_ void ERR_dieif (const ERR *p_err);

/**
 * 에러가 있다면(`ERR_err_p'), `fp_out'-에 경고출력.
 *
 * @param p_err (non-null)
 *
 * @param fp_out 경고를 출력할 `FILE *' (nullable: NULL-이면 stderr에 출력)
 */
EXTERN_ void ERR_warn_and_clear_if (ERR *p_err, FILE *fp_out);

/**
 * Assertion-expression을 평가후(runtime), 에러가 있다면 에러메시지
 * 할당.
 *
 * @param p_err (non-null) assertion-평가결과를 세팅할 에러구조체.
 *
 * @param assertion 평가식 (eg: `xyz != NULL`)
 */
#define ERR_assert(p_err, assertion)                                          \
  ((assertion) ?: ERR_set_nofree (p_err, "Assertion failed: "##assertion))

#endif /* ! err_h */
