#include "config.h"

#include "lua_binding.h"
#include "lua_binding__input_handler.h"
#include "plugin-api.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lua.h"
#include "lauxlib.h"



lua_State *_input_handler_L = NULL;
int _input_handler_lref = -1;


void *luab__input_handler_get_current_handle_input_fn_pfn = NULL;
void *luab__input_handler_set_current_handle_input_fn_pfn = NULL;


int luab__input_handler_get_current_handle_input_fn (lua_State *L)
{
  /*
    () => (cfn | lfn)

    NOTE: only support c-func currently.
  */
  typedef void *(*pfn_t)(void);
  assert(luab__input_handler_get_current_handle_input_fn_pfn != NULL);
  void *pf = ((pfn_t) luab__input_handler_get_current_handle_input_fn_pfn)();

  if (pf == luab__input_handler_handle_input)
    {
      lua_rawgeti(L, LUA_REGISTRYINDEX, _input_handler_lref);
      return 1;
    }

  /* otherwise: */
  lua_pushcfunction(L, pf);
  return 1;
}


int luab__input_handler_set_current_handle_input_fn (lua_State *L)
{
  /* (fn) => () */
  int fn_handler = luaL_ref(L, LUA_REGISTRYINDEX);
  _input_handler_L = L;

  /* deref? */
  if (_input_handler_lref != -1)
    {
      luaL_unref (L, LUA_REGISTRYINDEX, _input_handler_lref);
    }
  _input_handler_lref = fn_handler;

  typedef void (*pfn_t)(void * /*handle_input_fn_t*/);
  assert(luab__input_handler_set_current_handle_input_fn_pfn != NULL);
  ((pfn_t) luab__input_handler_set_current_handle_input_fn_pfn)
    (luab__input_handler_handle_input);

  return 0;
}


void luab__input_handler_handle_input
(void *p_status,
 const int fd_keyin,
 const int fd_child,
 char *buf,
 const ssize_t buf_max,
 handle_write_to_child_cb_t write_cb,
 void *write_cb_aux)
{
  lua_State *L = _input_handler_L;
  assert(L != NULL);
  assert(_input_handler_lref != -1);
  lua_rawgeti(L, LUA_REGISTRYINDEX, _input_handler_lref);

  /* (fd_keyin, fd_child) => () */
  lua_pushnumber(L, fd_keyin);
  lua_pushnumber(L, fd_child);

  lua_call(L, 2, 0);
}

