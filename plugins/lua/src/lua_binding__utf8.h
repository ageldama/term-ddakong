/**
 * ddakong Lua-scripting plugin
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#ifndef lua_binding__utf8_h
#define lua_binding__utf8_h 1

#include "extern_.h"
#include "lua.h"

EXTERN_ void *luab__utf8_unicode_to_utf8_pfn;

EXTERN_ int luab__utf8_unicode_to_utf8 (lua_State *L);

#endif /* ! lua_binding__utf8_h */
