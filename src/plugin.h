#ifndef plugin_h
#define plugin_h 1

#include "config.h"
#include "extern_.h"
#include <stdlib.h>



#ifndef DDAKONG_PLUGIN_ENTRY_NAME
/**
 * 플러그인 DLL 로딩한 다음 호출할 초기화 함수 이름
 */
#define DDAKONG_PLUGIN_ENTRY_NAME "ddakong_plugin_entry"
#endif

typedef struct {
  void *p_dll;
} dll_plugin_context_t;



typedef struct {
  void *p_func;
  char *sz_func_name;
  char *sz_func_doc;
} plugin_func_t;



EXTERN_ const plugin_func_t plugin_funcs[];

EXTERN_ const ssize_t plugin_funcs_len;


typedef void (*ddakong_plugin_entry_fn_t)
(const plugin_func_t *, const ssize_t);


#endif /* ! plugin_h */
