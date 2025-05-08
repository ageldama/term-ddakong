

AM_CPPFLAGS = -fPIC \
    -Wall -Wextra -Werror \
    -Wconversion -Wsign-conversion \
    -Wformat-security \
    -Wno-nullability-completeness \
    -std=c99 \
		-D_GNU_SOURCE \
		-D_POSIX_C_SOURCE -D_XOPEN_SOURCE=700 \
		-D_BSD_SOURCE -D__BSD_VISIBLE \
		-Wno-error=c23-extensions

## TODO -fhardened (gcc)


noinst_LIBRARIES = libddakongs.a

libddakongs_a_SOURCES = err.c fd_io.c getopt_.c \
    hangeul.c hangeul_tables.c \
    im_handler.c im_handler_hangeul.c \
    pty_.c sig.c termios_.c utf8_.c winsz.c \
    plugin.c plugin_func_registry.c \
    pollfd.c

bin_PROGRAMS = ddakong

ddakong_SOURCES = main_ddakong.c
ddakong_LDADD = libddakongs.a
ddakong_LDFLAGS = -lutil

EXTRA_DIST = *.h

