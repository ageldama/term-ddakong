#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([ddakong-plugin-random-phrase],[0.0.01],[Jonghyouk Yun <ageldama@gmail.com>])

AC_CONFIG_AUX_DIR([./autotools])

AM_INIT_AUTOMAKE([-Wall -Werror foreign parallel-tests])
AM_MAINTAINER_MODE

AC_CONFIG_SRCDIR([src/dllmain.c])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
AM_PROG_AR


LT_INIT()

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SSIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
