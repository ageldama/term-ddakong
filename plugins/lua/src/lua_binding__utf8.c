#include "config.h"

#include "lua_binding.h"
#include "lua_binding__utf8.h"
#include "plugin-api.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> /* uint32_t */

#include "lua.h"


void *luab__utf8_unicode_to_utf8_pfn = NULL;


int luab__utf8_unicode_to_utf8(lua_State *L)
{
  uint32_t unicode = (uint32_t) lua_tointeger(L, -1);
  lua_remove(L, 1);
  
  char buf[10];
  /* const ssize_t buf_max = 10; */

  typedef int (*pfn_t)(const uint32_t unicode,
                       char *buf);

  int n_utf8 = ((pfn_t) luab__utf8_unicode_to_utf8_pfn)
    (unicode, buf);

  lua_pushlstring(L, buf, n_utf8);
  return 1;
}
