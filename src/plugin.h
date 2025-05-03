#ifndef plugin_h
#define plugin_h 1

#include "config.h"
#include "extern_.h"
#include <stdlib.h>

typedef struct {
  void *p_func;
  char *sz_func_name;
  char *sz_func_doc;
} plugin_func_t;



EXTERN_ const plugin_func_t plugin_funcs[];

EXTERN_ const ssize_t plugin_funcs_len;


#endif /* ! plugin_h */
