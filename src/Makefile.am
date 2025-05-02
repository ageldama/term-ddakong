AM_CPPFLAGS = -I../include

noinst_LIBRARIES = libddakongs.a

libddakongs_a_SOURCES = err.h fd_io.c getopt_.c hangeul.c hangeul_tables.c im_handler.c im_handler_hangeul.c pty_.c sig.c termios_.c utf8_.c winsz.c

bin_PROGRAMS = ddakong

ddakong_SOURCES = main_ddakong.c
ddakong_LDADD = libddakongs.a
