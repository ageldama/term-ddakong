#ifndef lua_binding__posix_h
#define lua_binding__posix_h 1

#include "extern_.h"
#include "lua.h"

EXTERN_ void *luab__posix_cp_fd_pfn;
EXTERN_ void *luab__posix_fcntl_nb_pfn;
EXTERN_ void *luab__posix_winsz_update_pfn;
EXTERN_ void *luab__posix_termios__init_pfn;
EXTERN_ void *luab__posix_termios__reset_pfn;
EXTERN_ void *luab__posix_signal_trap_norecover_pfn;
EXTERN_ void *luab__posix_forkpty_with_exec_pfn;
EXTERN_ void *luab__posix_kill_forkpty_pfn;

EXTERN_ int luab__posix_cp_fd (lua_State *L);
EXTERN_ int luab__posix_fcntl_nb (lua_State *L);
EXTERN_ int luab__posix_winsz_update (lua_State *L);
EXTERN_ int luab__posix_termios__init (lua_State *L);
EXTERN_ int luab__posix_termios__reset (lua_State *L);
EXTERN_ int luab__posix_signal_trap_norecover (lua_State *L);
EXTERN_ int luab__posix_forkpty_with_exec (lua_State *L);
EXTERN_ int luab__posix_kill_forkpty (lua_State *L);

EXTERN_ int luab__posix_fdread (lua_State *L);
EXTERN_ int luab__posix_fdwrite (lua_State *L);

EXTERN_ void lua_binding_build__posix (lua_State *L);

#endif /* ! lua_binding__posix_h */
