lib_LTLIBRARIES = liblua_ddakong.la


liblua_ddakong_la_SOURCES = dllmain.c im_handler.c
liblua_ddakong_la_LIBADD = -L$(top_srcdir)/$(LUA_SRC)/src -llua
liblua_ddakong_la_CFLAGS = -I$(top_srcdir)/$(LUA_SRC)/src

nodist_liblua_ddakong_la_SOURCES = __lua_built__.c



__lua_built__.c:
	make -C $(top_srcdir)/$(LUA_SRC)
	touch $(srcdir)/__lua_built__.c


all-local:
	-cp -fv .libs/liblua_ddakong.so $(top_srcdir)


clean-local:
	-rm -fv $(top_srcdir)/liblua_ddakong.so
	-make -C $(top_srcdir)/$(LUA_SRC) clean
	-rm -fv $(srcdir)/__lua_built__.c
