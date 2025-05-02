cmake_minimum_required(VERSION 3.10)

project(term-ddakong)


set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)


include(CheckFunctionExists)

check_function_exists(vasprintf vasprintf_FOUND)

if(${vasprintf_FOUND})
    add_definitions("-D_GNU_SOURCE")
endif()

# TODO epoll
add_definitions("-D_POSIX_C_SOURCE")



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


