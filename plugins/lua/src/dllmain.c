#include "config.h"

#include "plugin-api.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lua.h"
#include "lauxlib.h"



lua_State *L = NULL;


void ddakong_plugin_entry
(const plugin_func_t *funcs, const ssize_t funcs_len)
{
  L = luaL_newstate();
  
  for (int i = 0 ; i < funcs_len ; i ++)
    {
      plugin_func_t *p_func_row = (plugin_func_t *) &funcs[i];
      fprintf(stderr, "# fn: %s @ %p\n",
              p_func_row->sz_func_name, p_func_row->p_func);
    }

}


void ddakong_plugin_deinit() {}
