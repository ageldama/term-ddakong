#include "config.h"

#include "lua_binding.h"
#include "lua_binding__posix.h"
#include "plugin-api.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> /* pid_t */
#include <unistd.h>

#include "lauxlib.h"
#include "lua.h"

void *luab__posix_cp_fd_pfn = NULL;
void *luab__posix_fcntl_nb_pfn = NULL;
void *luab__posix_winsz_update_pfn = NULL;
void *luab__posix_termios__init_pfn = NULL;
void *luab__posix_termios__reset_pfn = NULL;
void *luab__posix_signal_trap_norecover_pfn = NULL;
void *luab__posix_forkpty_with_exec_pfn = NULL;
void *luab__posix_kill_forkpty_pfn = NULL;

int
luab__posix_cp_fd (lua_State *L)
{
  /* (src_fd, dst_fd, buf) => n_written */
  ssize_t buf_len = 0;
  const char *buf = lua_tolstring (L, -1, &buf_len);
  int dst_fd = lua_tointeger (L, -2);
  int src_fd = lua_tointeger (L, -3);

  lua_remove (L, 3);

  typedef ssize_t (*pfn_t) (const int /*src_fd*/, const int /*dst_fd*/,
                            const char * /*buf*/, const ssize_t /*buf_len*/);
  assert (luab__posix_cp_fd_pfn != NULL);

  ssize_t n_written
      = ((pfn_t)luab__posix_cp_fd_pfn) (src_fd, dst_fd, buf, buf_len);

  lua_pushnumber (L, n_written);
  return 1;
}

int
luab__posix_fcntl_nb (lua_State *L)
{
  /* (fd) => {ret_fcntl:, old_fcntl:} */
  int fd = lua_tointeger (L, -1);
  lua_remove (L, 1);

  typedef int (*pfn_t) (const int /*fd*/, int * /*p_old_fl*/);
  assert (luab__posix_fcntl_nb != NULL);

  int old_fl = 0;
  int n_ret = ((pfn_t)luab__posix_fcntl_nb_pfn) (fd, &old_fl);

  lua_newtable (L); /* result table */

  lua_pushstring (L, "ret_fcntl");
  lua_pushinteger (L, n_ret);
  lua_settable (L, -3);

  lua_pushstring (L, "old_fcntl");
  lua_pushinteger (L, old_fl);
  lua_settable (L, -3);

  return 1;
}

int
luab__posix_winsz_update (lua_State *L)
{
  /* (fd) => () */
  int fd = lua_tointeger (L, -1);
  lua_remove (L, 1);

  typedef void (*pfn_t) (const int /*child_fd*/);
  assert (luab__posix_winsz_update_pfn != NULL);

  ((pfn_t)luab__posix_winsz_update_pfn) (fd);

  return 0;
}

int
luab__posix_termios__init (lua_State *L)
{
  /* (b_echo) => () */
  int b_echo = lua_toboolean (L, -1);
  lua_remove (L, 1);

  typedef void (*pfn_t) (int /*echo*/);
  assert (luab__posix_termios__init_pfn != NULL);

  ((pfn_t)luab__posix_termios__init_pfn) (b_echo);

  return 0;
}

int
luab__posix_termios__reset (lua_State *L)
{
  /* () => () */
  typedef void (*pfn_t) (void);
  assert (luab__posix_termios__reset_pfn != NULL);

  ((pfn_t)luab__posix_termios__reset_pfn) ();

  return 0;
}

int
luab__posix_forkpty_with_exec (lua_State *L)
{
  /* () => {pid:, fd:} */
  typedef pid_t (*pfn_t) (int * /*p_fd*/);
  assert (luab__posix_forkpty_with_exec_pfn != NULL);

  int fd = 0;
  pid_t pid = ((pfn_t)luab__posix_forkpty_with_exec_pfn) (&fd);

  lua_newtable (L); /* result table */

  lua_pushstring (L, "pid");
  lua_pushinteger (L, pid);
  lua_settable (L, -3);

  lua_pushstring (L, "fd");
  lua_pushinteger (L, fd);
  lua_settable (L, -3);

  return 1;
}

int
luab__posix_kill_forkpty (lua_State *L)
{
  /* (pid, fd) => () */
  pid_t pid = lua_tointeger (L, -2);
  int fd = lua_tointeger (L, -1);
  lua_remove (L, 2);

  assert (luab__posix_kill_forkpty_pfn != NULL);
  typedef void (*pfn_t) (const pid_t /*pid*/, const int /*fd*/);

  ((pfn_t)luab__posix_kill_forkpty_pfn) (pid, fd);

  return 0;
}

lua_State *_sig_hdlr_L = NULL; /* NOTE dirty, limited */

void
_sig_hdlr (int signo)
{
  assert (_sig_hdlr_L != NULL);

  lua_State *L = _sig_hdlr_L;

  lua_getglobal (L, "ddakong");
  lua_getfield (L, -1, "__posix_signal_trap_norecover_actions");
  lua_rawgeti (L, -1, signo);

  if (lua_isnil (L, -1))
    {
      lua_remove (L, 1);
      return;
    }

  int cb_ref = lua_tointeger (L, -1);
  lua_remove (L, 1);
  lua_rawgeti (L, LUA_REGISTRYINDEX, cb_ref);

  lua_pushnumber (L, signo);
  lua_call (L, 1, 0);
}

int
luab__posix_signal_trap_norecover (lua_State *L)
{
  /* (n_sig, fn_action) => () */
  int fn_action = luaL_ref (L, LUA_REGISTRYINDEX);
  const int n_sig = lua_tointeger (L, -1);

  lua_remove (L, 1);

  assert (luab__posix_signal_trap_norecover_pfn);
  typedef void (*pfn_t) (const int /*signo*/,
                         void (* /*handler*/) (int /*signo*/));

  ((pfn_t)luab__posix_signal_trap_norecover_pfn) (n_sig, _sig_hdlr);

  _sig_hdlr_L = L;

  /* ddakong.__posix_signal_trap_norecover_actions */
  lua_getglobal (L, "ddakong");
  lua_getfield (L, -1, "__posix_signal_trap_norecover_actions");

  lua_pushnumber (L, n_sig);
  lua_pushnumber (L, fn_action);

  lua_settable (L, -3);

  return 0;
}

void
lua_binding_build__posix (lua_State *L)
{
  lua_pushstring (L, "__posix_signal_trap_norecover_actions");
  lua_newtable (L);
  lua_settable (L, -3);
}

int
luab__posix_fdread (lua_State *L)
{
  /* (fd, max_len) => (buf) */
  int fd = lua_tointeger (L, -2);
  ssize_t max_len = lua_tointeger (L, -1);
  lua_remove (L, 2);

  void *buf = malloc (max_len);
  memset (buf, 0, max_len);

  ssize_t n_read = read (fd, buf, max_len);

  lua_pushlstring (L, buf, n_read);
  free (buf);

  return 1;
}

int
luab__posix_fdwrite (lua_State *L)
{
  /* (fd, buf) => (n_written) */
  int fd = lua_tointeger (L, -2);
  ssize_t buf_len = 0;
  const char *buf = lua_tolstring (L, -1, &buf_len);
  lua_remove (L, 2);

  ssize_t n_written = write (fd, buf, buf_len);

  lua_pushnumber (L, n_written);
  return 1;
}
