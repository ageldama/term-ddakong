/**
 * ddakong Lua-scripting plugin
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#ifndef lua_binding__err_h
#define lua_binding__err_h 1

#include "extern_.h"
#include "lua.h"

EXTERN_ void *luab__ERR_err_p_pfn;
EXTERN_ void *luab__ERR_clear_pfn;
EXTERN_ void *luab__ERR_set_pfn;
EXTERN_ void *luab__ERR_dieif_pfn;
EXTERN_ void *luab__ERR_warn_and_clear_if_pfn;

EXTERN_ int luab__ERR_err_p (lua_State *L);
EXTERN_ int luab__ERR_clear (lua_State *L);
EXTERN_ int luab__ERR_set (lua_State *L);
EXTERN_ int luab__ERR_dieif (lua_State *L);
EXTERN_ int luab__ERR_warn_and_clear_if (lua_State *L);
EXTERN_ int luab__ERR_get_errmsg (lua_State *L);

#endif /* ! lua_binding__err_h */
