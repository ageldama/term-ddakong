
LUA_INCLUDE = -I$(top_srcdir)/lua-5.4.7/src
LUA_LDFLAGS_ = -L$(top_srcdir)/lua-5.4.7/src/ -llua


AM_CPPFLAGS = -fPIC \
    -Wall -Wextra -Werror \
    -Wconversion -Wsign-conversion \
    -Wformat-security \
    -Wno-nullability-completeness \
    -std=c99 -D_POSIX_C_SOURCE -D_GNU_SOURCE \
		${LUA_INCLUDE}

# TODO -fhardened (gcc)
# -Wno-c23-extensions 


noinst_LIBRARIES = libddakongs.a

libddakongs_a_SOURCES = err.c fd_io.c getopt_.c \
    hangeul.c hangeul_tables.c \
    im_handler.c im_handler_hangeul.c \
    pty_.c sig.c termios_.c utf8_.c winsz.c \
    plugin.c plugin_func_registry.c

bin_PROGRAMS = ddakong

ddakong_SOURCES = main_ddakong.c
ddakong_LDADD = libddakongs.a
ddakong_LDFLAGS = ${LUA_LDFLAGS_}

EXTRA_DIST = *.h

