lib_LTLIBRARIES = liblua_ddakong.la


liblua_ddakong_la_SOURCES = dllmain.c im_handler.c __lua_built__.c
liblua_ddakong_la_LIBADD = -L$(top_srcdir)/lua-5.4.7/src -llua
liblua_ddakong_la_CFLAGS = -I$(top_srcdir)/lua-5.4.7/src


__lua_built__.c:
	make -C $(top_srcdir)/lua-5.4.7
	touch $(srcdir)/__lua_built__.c


all-local:
	-cp -fv .libs/liblua_ddakong.so $(top_srcdir)


clean-local:
	-rm -fv $(top_srcdir)/liblua_ddakong.so
	-make -C $(top_srcdir)/lua-5.4.7 clean
	-rm -fv $(srcdir)/__lua_built__.c
