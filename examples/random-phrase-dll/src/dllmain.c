#include <stdio.h>
#include <stdlib.h>


#if defined(__cplusplus)
#define EXTERN_ extern "c"
#else
#define extern
#endif


typedef struct {
  void *p_func;
  char *sz_func_name;
  char *sz_func_doc;
} plugin_func_t;


EXTERN_ void ddakong_plugin_entry
(const plugin_func_t *, const ssize_t);
{
}
