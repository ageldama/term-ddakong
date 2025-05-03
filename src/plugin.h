#ifndef plugin_h
#define plugin_h 1

#include "config.h"
#include "extern_.h"


typedef struct {
  void *p_func;
  char *sz_func_name;
} PLUGIN_FUNC_ENTRY;


/* TODO factor-out: main => im_handler */


#endif /* ! plugin_h */
