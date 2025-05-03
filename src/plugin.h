/**
 * "DLL"-Plugin system of Ddakong
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#ifndef plugin_h
#define plugin_h 1

#include "config.h"
#include "extern_.h"
#include "typedef_.h"
#include <stdlib.h>



#ifndef DDAKONG_PLUGIN_ENTRY_NAME
/**
 * 플러그인 DLL 로딩한 다음 호출할 초기화 함수 이름
 */
#define DDAKONG_PLUGIN_ENTRY_NAME "ddakong_plugin_entry"
#endif


/**
 * DLL-PLUGIN 구조체 타입
 */
typedef struct {
  void *p_dll;
} dll_plugin_context_t;


/**
 * 로딩한 DLL 파일의 * ddakong_plugin_entry() 함수에 전달할 함수포인터
 * 배열의 행타입.
 *
 * @param p_func 함수포인터
 *
 * @param sz_func_name 함수의 이름 (예: "printf")
 *
 * @param sz_func_doc 함수설명 (예: "prints somethign")
 */
typedef struct {
  void *p_func;
  char *sz_func_name;
  char *sz_func_doc;
} plugin_func_t;


/**
 * DLL-PLUGIN에 전달할 함수포인터 배열
 */
EXTERN_ const plugin_func_t plugin_funcs[];

/**
 * DLL-PLUGIN에 전달할 함수포인터 배열의 길이
 */
EXTERN_ const ssize_t plugin_funcs_len;


/**
 * DLL-PLUGIN에서 찾아 실행할 ddakong_plugin_entry() 함수의 타입
 */
typedef void (*ddakong_plugin_entry_fn_t)
(const plugin_func_t *, const ssize_t);


/**
 * DLL-PLUGIN 로드 + 초기화
 *
 * DLL파일에서 ddakong_plugin_entry() 함수를 찾아, 플러그인이 호출할
 * 수 있는 함수포인터 목록을 전달하여 초기화.
 *
 * @param p_plugin_ctx (non-null)
 *
 * @param sz_dll_filename 로딩할 DLL파일이름
 *
 * @return 로딩 및 초기화에 성공했다면 TRUE
 */
EXTERN_
BOOL dll_plugin_load
(dll_plugin_context_t *p_plugin_ctx, const char *sz_dll_filename);

/**
 * DLL-PLUGIN 해제
 *
 * @param p_plugin_ctx (non-null)
 */
EXTERN_
void dll_plugin_unload
(dll_plugin_context_t *p_plugin_ctx);


#endif /* ! plugin_h */
