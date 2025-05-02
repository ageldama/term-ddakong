cmake_minimum_required(VERSION 3.10)

project(term-ddakong)


set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)


include(CheckSymbolExists)
include(CheckFunctionExists)


# vasprintf

check_symbol_exists(vasprintf "stdio.h" HAVE_vasprintf)

if(HAVE_vasprintf)
    add_definitions("-D_GNU_SOURCE")
else()
    message(FATAL_ERROR "vasprintf NOT FOUND")
endif()



# epoll

add_definitions("-D_POSIX_C_SOURCE")


check_symbol_exists(epoll_create sys/epoll.h EPOLL_SUPPORTED)

if(EPOLL_SUPPORTED)
  message(STATUS "epoll is supported.")
else()
  message(FATAL_ERROR "epoll is not supported.")
endif()



# pty

check_symbol_exists(forkpty pty.h HAVE_FORKPTY)

if(NOT HAVE_FORKPTY)
       message(FATAL_ERROR "forkpty() NOT FOUND")
endif()



# TODO stdio.h
# TODO stdlib.h
# TODO sys/types.h
# TODO ssize_t
# TODO unistd.h
# TODO stdint.h
# TODO assert.h
# TODO stddef.h
# TODO getenv
# TODO execlp
# TODO kill
# TODO close
# TODO SIGTERM
# TODO struct sigaction
# TODO sigemptyset sigaction
# TODO signal.h
# TODO sys/ioctl.h ioctl STDIN_FILENO TIOCGWINSZ struct winsize
# TODO termios.h tcgetattr ISTRIP ICANON ECHO ISIG TCSANOW tcsetattr
# TODO sys/wait.h waitpid WEXITSTATUS WNOHANG
# TODO snprintf perror
# TODO fcntl.h
# TODO assert
# TODO stdarg.h
# TODO ctype.h
# TODO va_list type
# TODO getopt optarg optopt abort
# TODO exit
# TODO EXIT_SUCCESS EXIT_FAILURE
# TODO va_start vasprintf va_end
# TODO fprintf
# TODO stderr
# TODO fcntl, F_SETFL, F_GETFL, O_NONBLOCK
# TODO read / write


# ----------------------------------------------------------

add_library(ddakongs
  src/err.c
  src/fd_io.c
  src/hangeul.c
  src/hangeul_tables.c
  src/im_handler.c
  src/im_handler_hangeul.c
  src/pty_.c
  src/sig.c
  src/termios_.c
  src/utf8_.c
  src/winsz.c)

target_include_directories(ddakongs PUBLIC include)

add_executable(ddakong src/getopt_.c src/main_ddakong.c)

target_link_libraries(ddakong PUBLIC ddakongs)


