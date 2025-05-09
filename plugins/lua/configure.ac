#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([ddakong-plugin-lua],[0.0.01],[Jonghyouk Yun <ageldama@gmail.com>])

AC_CONFIG_AUX_DIR([./autotools])

AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AM_MAINTAINER_MODE

AC_CONFIG_SRCDIR([src/dllmain.c])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_MACRO_DIR([m4])

# Features

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


AM_CONDITIONAL([EXTERNAL_LUA],
    [test x"$with_lua" != x"" -o x"$with_lua_pkg_config" != x""])

AS_IF([test x"$with_lua" != x""], [
    AS_IF([test x"$with_lua_cflags" != x""],
          [AC_SUBST(EXTERNAL_LUA_CFLAGS, ["$with_lua_cflags"])],
          [AC_SUBST(EXTERNAL_LUA_CFLAGS, ["-I$with_lua/include"])])
    AS_IF([test x"$with_lua_libs" != x""],
          [AC_SUBST(EXTERNAL_LUA_LIBS, ["$with_lua_libs"])],
          [AC_SUBST(EXTERNAL_LUA_LIBS, ["-L$with_lua/lib -llua"])])
],
[test x"$with_lua_pkg_config" != x""], [
    AC_SUBST(EXTERNAL_LUA_CFLAGS, [`pkg-config --cflags $with_lua_pkg_config`])
    AC_SUBST(EXTERNAL_LUA_LIBS, [`pkg-config --libs $with_lua_pkg_config`])
])


# Checks for programs.
AC_PROG_CC
AM_PROG_AR

LT_INIT()


# Checks for libraries.
AC_CHECK_LIB(m, [pow],
[
  LIBS="$LIBS -lm"
  AC_DEFINE([HAVE_M], [1], [have m])
],
[
  AC_MSG_ERROR(["libm" cannot be found, needed to build Lua])
])

AC_CHECK_LIB(dl, [dlopen],
[
  LIBS="$LIBS -ldl"
  AC_DEFINE([HAVE_DLOPEN], [1], [have dlopen])
],
[
  AC_MSG_ERROR(["libdl" cannot be found, needed to build Lua])
])

AC_CHECK_FUNCS([
    fprintf
    wordexp wordfree
    memset
    getenv
    strncpy
],[],
[AC_MSG_ERROR([required function cannot be found])])



#
AC_SUBST(LUA_SRC, [lua-5.4.7])


# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SSIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT


dnl AS_ECHO([Msg: $with_lua])
