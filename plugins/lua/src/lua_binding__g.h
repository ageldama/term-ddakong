#ifndef lua_binding__global_h
#define lua_binding__global_h 1

#include "extern_.h"
#include "lua.h"

EXTERN_ void *luab__g_print_banner_pfn;
EXTERN_ void *luab__g_get_verbose_flag_pfn;
EXTERN_ void *luab__g_set_verbose_flag_pfn;
EXTERN_ void *luab__g_get_keylog_filename_pfn;
EXTERN_ void *luab__g_get_default_keylog_filename_pfn;
EXTERN_ void *luab__g_get_plugin_dll_filename_pfn;
EXTERN_ void *luab__g_get_child_pid_pfn;
EXTERN_ void *luab__g_get_child_fd_pfn;

EXTERN_ int luab__g_print_banner (lua_State *L);
EXTERN_ int luab__g_get_verbose_flag (lua_State *L);
EXTERN_ int luab__g_set_verbose_flag (lua_State *L);
EXTERN_ int luab__g_get_keylog_filename (lua_State *L);
EXTERN_ int luab__g_get_default_keylog_filename (lua_State *L);
EXTERN_ int luab__g_get_plugin_dll_filename (lua_State *L);
EXTERN_ int luab__g_get_child_pid (lua_State *L);
EXTERN_ int luab__g_get_child_fd (lua_State *L);

#endif /* ! lua_binding__global_h */
