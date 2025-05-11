

AM_CPPFLAGS = -fPIC
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

EXTRA_libddakongs_a_SOURCES = pollfd__kqueue.c pollfd__linux_epoll.c pollfd__select.c

bin_PROGRAMS = ddakong

ddakong_SOURCES = main_ddakong.c
ddakong_LDADD = libddakongs.a
ddakong_LDFLAGS = $(LDFLAGS_LIBUTIL)

EXTRA_DIST = *.h

