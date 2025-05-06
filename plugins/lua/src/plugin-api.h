#ifndef __plugin_api_h__
#define __plugin_api_h__ 1

#if defined(__cplusplus)
#define EXTERN_ extern "c"
#else
#define EXTERN_ extern
#endif


#include <stdlib.h>


typedef struct {
  void *p_func;
  char *sz_func_name;
  char *sz_func_doc;
} plugin_func_t;


EXTERN_ void ddakong_plugin_entry
(const plugin_func_t *, const ssize_t);


EXTERN_ void ddakong_plugin_deinit();



#endif /* ! __plugin_api_h__ */
