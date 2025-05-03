/**
 * "DLL"-Plugin system of Ddakong
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#include "plugin.h"
#include "typedef_.h"
#include "global_flags.h"
#include "cc_nanny.h"

#include <assert.h>
#include <stdio.h>
#include <dlfcn.h>



#if (HAVE_DLOPEN && HAVE_DLSYM && HAVE_DLCLOSE)

BOOL dll_plugin_load
(dll_plugin_context_t *p_plugin_ctx, const char *sz_dll_filename)
{
  assert(p_plugin_ctx != NULL);
  assert(p_plugin_ctx->p_dll == NULL);

  if (verbose_flag)
    {
      fprintf(stderr, "# plugin: dll=%s\n", sz_dll_filename);
    }

  if (NULL == sz_dll_filename)
    {
      if (verbose_flag)
        {
          fprintf(stderr, "# plugin: not-specified\n");
        }
      return FALSE;
    }

  p_plugin_ctx->p_dll = dlopen(sz_dll_filename, RTLD_LAZY);
  if (NULL == p_plugin_ctx->p_dll)
    {
      perror(dlerror());
      return FALSE;
    }

  void *fun = dlsym(p_plugin_ctx->p_dll,
                    DDAKONG_PLUGIN_ENTRY_NAME);
  if (NULL == fun)
    {
      perror(dlerror());
      dlclose(p_plugin_ctx->p_dll);
      p_plugin_ctx->p_dll = NULL;
      return FALSE;
    }

  if (verbose_flag)
    {
      fprintf(stderr, "# plugin: calling (%s @ %p)\n",
              DDAKONG_PLUGIN_ENTRY_NAME, fun);
    }

  ddakong_plugin_entry_fn_t fun2 = (ddakong_plugin_entry_fn_t) fun;
  fun2(plugin_funcs, plugin_funcs_len);

  if (verbose_flag)
    {
      fprintf(stderr, "# plugin: called (%s @ %p)\n",
              DDAKONG_PLUGIN_ENTRY_NAME, fun);
    }

  return TRUE;
}

void dll_plugin_unload
(dll_plugin_context_t *p_plugin_ctx)
{
  assert(p_plugin_ctx != NULL);
  assert(p_plugin_ctx->p_dll != NULL);

  dlclose(p_plugin_ctx->p_dll);
  p_plugin_ctx->p_dll = NULL;
}

#else

/* NOTE dll-plugin has disabled */
BOOL dll_plugin_load
(dll_plugin_context_t *p_plugin_ctx UNUSED,
 const char *sz_dll_filename UNUSED)
{
  if (verbose_flag)
    {
      fprintf(stderr, "# plugin: not-supported\n");
    }
  return FALSE;
}

void dll_plugin_unload
(dll_plugin_context_t *p_plugin_ctx UNUSED)
{}

#endif /* HAVE_DLOPEN */
