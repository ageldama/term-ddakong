/**
 * ddakong DLL plugin example: dll-main
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#include "config.h"

#include "plugin-api.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

set_current_handle_input_fn_t set_current_handle_input_fn = NULL;

void
ddakong_plugin_entry (const plugin_func_t *funcs, const ssize_t funcs_len)
{
  for (int i = 0; i < funcs_len; i++)
    {
      plugin_func_t *p_func_row = (plugin_func_t *)&funcs[i];
      fprintf (stderr, "# fn: %s @ %p\n", p_func_row->sz_func_name,
               p_func_row->p_func);

      /* capture needed function: */
      if (0
          == strcmp (p_func_row->sz_func_name, "set_current_handle_input_fn"))
        {
          set_current_handle_input_fn = p_func_row->p_func;
          fprintf (stderr, "# GOT set_current_handle_input_fn: %p\n",
                   set_current_handle_input_fn);
        }
    }

  if (set_current_handle_input_fn != NULL)
    {
      set_current_handle_input_fn ((void *)handle_input);
      fprintf (stderr,
               "# my own custom `handle_input` has been installed: %p\n",
               handle_input);
    }
  else
    {
      fprintf (stderr,
               "# own custom `handle_input` installation failed: "
               "`set_current_handle_input_fn`-plugin function not found\n");
    }

  fprintf (stderr,
           "\n\n# CUSTOM PLUGIN HAS LOADED: PRESS ANY ALPHABET KEY...\n\n");
}

void
ddakong_plugin_deinit ()
{
}
