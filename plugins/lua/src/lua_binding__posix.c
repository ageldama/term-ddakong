#include "config.h"

#include "lua_binding.h"
#include "lua_binding__posix.h"
#include "plugin-api.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lua.h"


void *luab__posix_cp_fd_pfn = NULL;
void *luab__posix_fcntl_nb_pfn = NULL;
void *luab__posix_winsz_update_pfn = NULL;
void *luab__posix_termios__init_pfn = NULL;
void *luab__posix_termios__reset_pfn = NULL;
void *luab__posix_signal_trap_norecover_pfn = NULL;
void *luab__posix_forkpty_with_exec_pfn = NULL;
void *luab__posix_kill_forkpty_pfn = NULL;


int luab__posix_cp_fd(lua_State *L)
{
  int src_fd = lua_tointeger(L, -1);
  int dst_fd = lua_tointeger(L, -2);
  ssize_t buf_len = 0;
  const char *buf = lua_tolstring(L, -3, &buf_len);

  lua_remove(L, 3);

  typedef ssize_t (*pfn_t)
    (const int /*src_fd*/,
     const int /*dst_fd*/,
     const char * /*buf*/,
     const ssize_t /*buf_len*/);
  assert(luab__posix_cp_fd_pfn != NULL);

  ssize_t n_written = ((pfn_t) luab__posix_cp_fd_pfn)
    (src_fd, dst_fd, buf, buf_len);

  lua_pushnumber(L, n_written);
  return 1;
}


int luab__posix_fcntl_nb(lua_State *L)
{
  int fd = lua_tointeger(L, -1);
  lua_remove(L, 1);

  typedef int (*pfn_t)(const int /*fd*/, int * /*p_old_fl*/);
  assert(luab__posix_fcntl_nb != NULL);

  int old_fl = 0;
  int n_ret = ((pfn_t) luab__posix_fcntl_nb_pfn)(fd, &old_fl);

  lua_newtable(L); /* result table */

  lua_pushstring(L, "ret_fcntl");
  lua_pushinteger(L, n_ret);
  lua_settable(L, -3);

  lua_pushstring(L, "old_fcntl");
  lua_pushinteger(L, old_fl);
  lua_settable(L, -3);

  return 1;
}


int luab__posix_winsz_update(lua_State *L)
{
  int fd = lua_tointeger(L, -1);
  lua_remove(L, 1);

  typedef void (*pfn_t)(const int /*child_fd*/);
  assert(luab__posix_winsz_update_pfn != NULL);

  ((pfn_t) luab__posix_winsz_update_pfn)(fd);

  return 0;
}


int luab__posix_termios__init(lua_State *L)
{
  int b_echo = lua_toboolean(L, -1);
  lua_remove(L, 1);

  typedef void (*pfn_t)(int /*echo*/);
  assert(luab__posix_termios__init_pfn != NULL);

  ((pfn_t) luab__posix_termios__init_pfn)(b_echo);

  return 0;
}


int luab__posix_termios__reset(lua_State *L)
{
  typedef void (*pfn_t)(void);
  assert(luab__posix_termios__reset_pfn != NULL);

  ((pfn_t) luab__posix_termios__reset_pfn)();

  return 0;
}




#if 0
EXTERN_ int luab__posix_signal_trap_norecover(lua_State *L);
EXTERN_ int luab__posix_forkpty_with_exec(lua_State *L);
EXTERN_ int luab__posix_kill_forkpty(lua_State *L);
#endif

