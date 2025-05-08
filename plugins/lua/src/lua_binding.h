/**
 * ddakong Lua-scripting plugin
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#ifndef lua_binding_h
#define lua_binding_h 1

#include "extern_.h"
#include "plugin-api.h"

#include "lua.h"
#include <stdlib.h>

typedef struct
{
  char *sz_lua_func_name;
  lua_CFunction pfn_wrap;
  void **ppfn;
} lua_binding_row_t;

EXTERN_ const ssize_t __lua_bindings_len;

EXTERN_
lua_binding_row_t __lua_bindings[];

EXTERN_ void lua_binding_build (lua_State *L, const plugin_func_t *funcs,
                                const ssize_t funcs_len);

#endif /* ! lua_binding_h */
