#include "config.h"

#include "plugin-api.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



set_current_handle_input_fn_t set_current_handle_input = NULL;


void ddakong_plugin_entry
(const plugin_func_t *funcs, const ssize_t funcs_len)
{
  for (int i = 0 ; i < funcs_len ; i ++)
    {
      plugin_func_t *p_func_row = (plugin_func_t *) &funcs[i];
      fprintf(stderr, "# fn: %s @ %p\n",
              p_func_row->sz_func_name, p_func_row->p_func);

      /* capture needed function: */
      if (0 == strcmp(p_func_row->sz_func_name,
                      "set_current_handle_input"))
        {
          set_current_handle_input = p_func_row->p_func;
        }
    }

  /* FIXME: */
  /* set_current_handle_input((void *) handle_input); */
  set_current_handle_input((void *) NULL);
}
