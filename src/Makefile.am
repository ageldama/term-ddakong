

AM_CPPFLAGS = -fPIC \
		-D_GNU_SOURCE \
		-D_POSIX_C_SOURCE -D_XOPEN_SOURCE=700 \
		-D_DEFAULT_SOURCE -D__BSD_VISIBLE

## TODO _POSIX_C_SOURCE
## TODO _XOPEN_SOURCE
## TODO _BSD_SOURCE
## TODO _DEFAULT_SOURCE
## TODO __BSD_VISIBLE


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
ddakong_LDFLAGS = $(LDFLAGS_LIBUTIL)

EXTRA_DIST = *.h

