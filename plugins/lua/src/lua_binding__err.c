#include "config.h"

#include "lua_binding.h"
#include "plugin-api.h"

#include <stdlib.h>

#include "lua.h"



void *_luab_get_plugin_funcs_len_pfn = NULL;

int _luab_get_plugin_funcs_len(lua_State *L)
{
  typedef ssize_t (*pfn_t)(void);
  lua_pushnumber(L,
                 ((pfn_t) _luab_get_plugin_funcs_len_pfn)
                 ());
  return 0;
}
