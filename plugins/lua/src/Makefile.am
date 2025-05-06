lib_LTLIBRARIES = liblua_ddakong.la


liblua_ddakong_la_SOURCES = dllmain.c wordexp_.c \
	lua_binding_build.c

if EXTERNAL_LUA
liblua_ddakong_la_LIBADD = $(EXTERNAL_LUA_LIBS)
liblua_ddakong_la_CFLAGS = $(EXTERNAL_LUA_CFLAGS)
else
liblua_ddakong_la_LIBADD = -L$(top_srcdir)/$(LUA_SRC)/src -llua
liblua_ddakong_la_CFLAGS = -I$(top_srcdir)/$(LUA_SRC)/src
endif


nodist_liblua_ddakong_la_SOURCES = __lua_built__.c



__lua_built__.c:
if EXTERNAL_LUA
else
	-patch -N $(top_srcdir)/$(LUA_SRC)/src/Makefile $(top_srcdir)/lua-5.4.7-src-Makefile.patch
	make -C $(top_srcdir)/$(LUA_SRC)
endif
	touch $(srcdir)/__lua_built__.c


all-local:
	-cp -fv .libs/liblua_ddakong.so $(top_srcdir)


clean-local:
	-rm -fv $(top_srcdir)/liblua_ddakong.so
	-make -C $(top_srcdir)/$(LUA_SRC) clean
	-rm -fv $(srcdir)/__lua_built__.c
