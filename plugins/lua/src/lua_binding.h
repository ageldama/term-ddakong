#ifndef lua_binding_h
#define lua_binding_h 1

#include "extern_.h"
#include "plugin-api.h"

#include <stdlib.h>
#include "lua.h"


typedef struct {
  char *sz_lua_func_name;
  plugin_func_t *p_plugin_func;
} lua_binding_row_t;


EXTERN_ const ssize_t __lua_bindings_len;

EXTERN_
lua_binding_row_t __lua_bindings[];


EXTERN_ void lua_binding_build
(lua_State *L,
 const plugin_func_t *funcs,
 const ssize_t funcs_len);


#endif /* ! lua_binding_h */

