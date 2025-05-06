#include "config.h"

#include "plugin-api.h"
#include "lua_binding.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordexp_.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "lua_binding__g.h"


int verbose_flag = 1;

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

  luaL_openlibs(L);

  /* bind func-ptr => lua-mod */
  lua_newtable(L); /* you'are the bottom of my heart */
  lua_binding_build(L, funcs, funcs_len);
  lua_setglobal(L, "ddakong");

  /* verbose_flag <= get_verbose_flag */
  verbose_flag = ((int (*)())luab__g_get_verbose_flag_pfn)();

  /* dofile: init.lua */
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
      fprintf(stderr, "# wordexp failed (%s) (%s)\n",
              sz_ddakong_lua_,
              wordexp__errmsg(n_wordexp));
      return;
    }

  if (verbose_flag) fprintf(stderr, "# lua dofile: %s ...\n", sz_ddakong_lua);

  int n_dofile = luaL_dofile(L, sz_ddakong_lua);
  if(n_dofile != 0)
    {
      fprintf(stderr, "# lua-dofile err(0x%x) %s\n",
              n_dofile, lua_tostring(L, -1));
    }
  else
    {
      if (verbose_flag)
        {
          fprintf(stderr, "# lua-dofile result (OK-ish) = %s\n",
                  lua_tostring(L, -1));
        }
    }

  return;
}


void ddakong_plugin_deinit()
{
  if (L != NULL)
    {
      lua_close(L);
      L = NULL;
    }
}
