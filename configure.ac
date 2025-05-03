#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.72])
AC_INIT([term-ddakong],[0.0.6],[ageldama@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_CONFIG_SRCDIR([src/main_ddakong.c])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
AX_CHECK_COMPILE_FLAG([-std=c99])
AC_PROG_RANLIB
AM_PROG_AR



# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdint.h fcntl.h stdint.h
sys/epoll.h sys/ioctl.h pty.h
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


AC_CHECK_FUNCS([atexit forkpty epoll_create1
getenv execlp kill close read write
sigemptyset sigaction waitpid
snprintf perror
isalpha isprint
ioctl tcgetattr tcsetattr
getopt abort
vasprintf
exit fprintf fcntl],[],[AC_MSG_ERROR([required function cannot be found])])



# TODO TIOCGWINSZ struct winsize
# TODO ISTRIP ICANON ECHO ISIG TCSANOW 
# TODO WEXITSTATUS WNOHANG
# TODO optarg optopt abort
# TODO F_SETFL, F_GETFL, O_NONBLOCK


#
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
