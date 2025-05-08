/**
 * ddakong Lua-scripting plugin: plugin api header
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#ifndef __plugin_api_h__
#define __plugin_api_h__ 1

#include "config.h"

#include "extern_.h"

#include <stdlib.h>
#include <unistd.h>

typedef struct
{
  void *p_func;
  char *sz_func_name;
  char *sz_func_doc;
} plugin_func_t;

EXTERN_ void ddakong_plugin_entry (const plugin_func_t *, const ssize_t);

EXTERN_ void ddakong_plugin_deinit ();

#endif /* ! __plugin_api_h__ */
