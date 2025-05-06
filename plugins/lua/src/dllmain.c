#include "config.h"

#include "plugin-api.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordexp_.h"

#include "lua.h"
#include "lauxlib.h"



lua_State *L = NULL;


#define sz_ddakong_lua_len 4096
char sz_ddakong_lua[sz_ddakong_lua_len] = {};


void ddakong_plugin_entry
(const plugin_func_t *funcs, const ssize_t funcs_len)
{
  L = luaL_newstate();
  if (L == NULL)
    {
      fprintf(stderr, "# luaL_newstate has failed, aborting plugin\n");
      return;
    }

  for (int i = 0 ; i < funcs_len ; i ++)
    {
      plugin_func_t *p_func_row = (plugin_func_t *) &funcs[i];
      fprintf(stderr, "# fn: %s @ %p\n",
              p_func_row->sz_func_name, p_func_row->p_func);

      /* TODO bind func-ptr => lua-mod */
    }

  /* load init.lua */
  memset(sz_ddakong_lua, 0, sz_ddakong_lua_len);

  char *sz_ddakong_lua_ = getenv("DDAKONG_LUA");
  if (NULL == sz_ddakong_lua_)
    {
      sz_ddakong_lua_ = "~/.ddakong/init.lua";
    }

  int n_wordexp = wordexp_1st(sz_ddakong_lua_,
                              sz_ddakong_lua,
                              sz_ddakong_lua_len);
  if (0 != n_wordexp)
    {
      fprintf(stderr, "# wordexp failed (%s)\n",
              wordexp__errmsg(n_wordexp));
      return;
    }

  // TODO

}


void ddakong_plugin_deinit()
{
  if (L != NULL)
    {
      lua_close(L);
      L = NULL;
    }
}
