#include "config.h"

#include "lua_binding.h"
#include "lua_binding__g.h"
#include "plugin-api.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> /* pid_t */

#include "lua.h"

void *luab__g_print_banner_pfn = NULL;
void *luab__g_get_verbose_flag_pfn = NULL;
void *luab__g_set_verbose_flag_pfn = NULL;
void *luab__g_get_keylog_filename_pfn = NULL;
void *luab__g_get_default_keylog_filename_pfn = NULL;
void *luab__g_get_plugin_dll_filename_pfn = NULL;
void *luab__g_get_child_pid_pfn = NULL;
void *luab__g_get_child_fd_pfn = NULL;

int
luab__g_print_banner (lua_State *L)
{
  /* () => () */
  assert (luab__g_print_banner_pfn != NULL);
  typedef void (*pfn_t) (void *);
  ((pfn_t)luab__g_print_banner_pfn) (stderr);
  return 0;
}

int
luab__g_get_verbose_flag (lua_State *L)
{
  /* () => (b_verbose) */
  assert (luab__g_get_verbose_flag_pfn != NULL);
  typedef int (*pfn_t) (void);
  const int n_bool = ((pfn_t)luab__g_get_verbose_flag_pfn) ();
  lua_pushboolean (L, n_bool);
  return 1;
}

int
luab__g_set_verbose_flag (lua_State *L)
{
  /* (b_verbose) => () */
  int n_flag = lua_tointeger (L, -1);
  lua_remove (L, 1);

  assert (luab__g_set_verbose_flag_pfn != NULL);
  typedef void (*pfn_t) (int);

  ((pfn_t)luab__g_set_verbose_flag_pfn) (n_flag);

  return 0;
}

int
luab__g_get_keylog_filename (lua_State *L)
{
  /* () => (sz_keylog_filename) */
  assert (luab__g_get_keylog_filename_pfn);
  typedef char *(*pfn_t) (void);

  void *fn = ((pfn_t)luab__g_get_keylog_filename_pfn) ();

  if (NULL == fn)
    lua_pushnil (L);
  else
    lua_pushstring (L, fn);

  return 1;
}

int
luab__g_get_default_keylog_filename (lua_State *L)
{
  /* () => (sz_default_keylog_filename) */
  assert (luab__g_get_default_keylog_filename_pfn);
  typedef char *(*pfn_t) (void);

  lua_pushstring (L, ((pfn_t)luab__g_get_default_keylog_filename_pfn) ());

  return 1;
}

int
luab__g_get_plugin_dll_filename (lua_State *L)
{
  /* () => (sz_plugin_dll_filename) */
  assert (luab__g_get_plugin_dll_filename_pfn);
  typedef char *(*pfn_t) (void);

  lua_pushstring (L, ((pfn_t)luab__g_get_plugin_dll_filename_pfn) ());

  return 1;
}

int
luab__g_get_child_pid (lua_State *L)
{
  /* () => (pid) */
  assert (luab__g_get_child_pid_pfn);
  typedef pid_t (*pfn_t) (void);

  lua_pushinteger (L, ((pfn_t)luab__g_get_child_pid_pfn) ());

  return 1;
}

int
luab__g_get_child_fd (lua_State *L)
{
  /* () => (fd) */
  assert (luab__g_get_child_fd_pfn);
  typedef int (*pfn_t) (void);

  lua_pushinteger (L, ((pfn_t)luab__g_get_child_fd_pfn) ());

  return 1;
}
