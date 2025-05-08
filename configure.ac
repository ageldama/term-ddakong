#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.72])
AC_INIT([ddakong],[1.0],[Jonghyouk Yun <ageldama@gmail.com>])
AC_CONFIG_AUX_DIR([./autotools])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_CONFIG_SRCDIR([src/main_ddakong.c])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_MACRO_DIR([m4])


# Features

AC_ARG_ENABLE([select],
              AS_HELP_STRING([--enable-select],
                             [Enable select(2) instead of epoll/kqueue]))


AC_ARG_ENABLE([lua],
              AS_HELP_STRING([--disable-lua],
                             [Disable Lua scripting plugin]))


AC_ARG_ENABLE([random-phrase],
              AS_HELP_STRING([--disable-random-phrase],
                             [Disable Random phrase (example) plugin]))


AC_ARG_WITH([lua],
            [AS_HELP_STRING([--with-lua],
                [With external Lua @<:@default=builtin-lua@:>@])],
            [], [])

AC_ARG_WITH([lua-cflags],
            [AS_HELP_STRING([--with-lua-cflags],
                [With external Lua cflags @<:@default=builtin-lua@:>@])],
            [], [])

AC_ARG_WITH([lua-libs],
            [AS_HELP_STRING([--with-lua-libs],
                [With external Lua libs @<:@default=builtin-lua@:>@])],
            [], [])


AC_ARG_WITH([lua-pkg-config],
            [AS_HELP_STRING([--with-lua-pkg-config],
                [With Lua pkg-config @<:@default=builtin-lua@:>@])],
            [], [])




# Checks for programs.
AC_PROG_CC
AX_CHECK_COMPILE_FLAG([-std=c99])
AC_PROG_RANLIB
AM_PROG_AR



# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([sys/epoll.h])

AC_CHECK_HEADERS([pty.h])

AC_CHECK_HEADERS([libutil.h])

AC_CHECK_HEADERS([sys/signal.h])

AC_CHECK_HEADERS([stdint.h fcntl.h stdint.h
sys/ioctl.h
sys/types.h stddef.h
signal.h sys/wait.h
stdarg.h ctype.h
termios.h unistd.h],[],[AC_MSG_ERROR([required header cannot be found])])

AC_HEADER_ASSERT
AC_HEADER_TIOCGWINSZ

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.


AC_CHECK_FUNCS([epoll_create1])

AC_CHECK_FUNCS([forkpty])

AC_CHECK_FUNCS([atexit
getenv execlp kill close read write
sigemptyset sigaction waitpid
snprintf perror
isalpha isprint
ioctl tcgetattr tcsetattr
getopt abort
vasprintf
exit fprintf fcntl],[],[AC_MSG_ERROR([required function cannot be found])])


AC_CHECK_LIB(dl, [dlopen],
[
  LIBS="$LIBS -ldl"
  AC_DEFINE([HAVE_DLOPEN], [1], [have dlopen])
  AC_SUBST(enable_dlopen, [yes])
],
[
  AC_SUBST(enable_lua, [no])
  AC_SUBST(enable_random_phrase, [no])

  AC_MSG_NOTICE(["libdl" cannot be found, Plugin system DISABLED.])
])



#
AM_CONDITIONAL([LUA], [test x"$enable_lua" != x"no"])

AM_CONDITIONAL([RANDOM_PHRASE], [test x"$enable_random_phrase" != x"no"])


#
AC_CONFIG_FILES([Makefile src/Makefile])


AS_IF([test x"$enable_random_phrase" != x"no"],
    [AC_CONFIG_SUBDIRS([plugins/random-phrase])])

AS_IF([test x"$enable_lua" != x"no"],
    [AC_CONFIG_SUBDIRS([plugins/lua])])

AS_IF([test x"$enable_select" == x"yes"],
    [AC_DEFINE([ENABLE_SELECT], [1], [use select(1)])])


AC_OUTPUT



AS_ECHO("")
AS_ECHO("- FEATURE RECAP ---------------------------------------------")

AS_ECHO_N("Plugin system: ")
AS_IF([test x"$enable_dlopen" != x"no"], [AS_ECHO([YES])], [AS_ECHO([NO])])

AS_ECHO_N("Example plugin ("random-phrase"): ")
AS_IF([test x"$enable_random_phrase" != x"no"], [AS_ECHO([YES])], [AS_ECHO([NO])])

AS_ECHO_N("Lua scripting: ")
AS_IF([test x"$enable_lua" != x"no"],
    [AS_IF([test x"$with_lua" != x""], [AS_ECHO("YES external @<:@$with_lua@:>@")],
           [test x"$with_lua_pkg_config" != x""], [AS_ECHO("YES pkg-config @<:@$with_lua_pkg_config@:>@")],
           [AS_ECHO("YES @<:@--INTERNAL--@:>@")])],
    [AS_ECHO([NO])])


AS_ECHO("")


