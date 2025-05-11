lib_LTLIBRARIES = liblua_ddakong.la


liblua_ddakong_la_SOURCES = dllmain.c wordexp_.c \
    lua_binding_build.c \
    lua_binding__err.c lua_binding__g.c \
    lua_binding__utf8.c lua_binding__posix.c \
    lua_binding__input_handler.c


if EXTERNAL_LUA
liblua_ddakong_la_LIBADD = $(EXTERNAL_LUA_LIBS)
liblua_ddakong_la_CFLAGS = $(EXTERNAL_LUA_CFLAGS)
else
liblua_ddakong_la_LIBADD = -L$(top_srcdir)/$(LUA_SRC)/src -llua
liblua_ddakong_la_CFLAGS = -I$(top_srcdir)/$(LUA_SRC)/src
endif


nodist_liblua_ddakong_la_SOURCES = $(abs_builddir)/__lua_built__.c



$(abs_builddir)/__lua_built__.c:
if EXTERNAL_LUA
else
	CC="$(CC)" AR="$(AR)" RANLIB="$(RANLIB)" make -C $(top_srcdir)/$(LUA_SRC)
endif
	touch $(abs_builddir)/__lua_built__.c


.PHONY: cp-lib
cp-lib: all
	-cp -fv .libs/liblua_ddakong.so $(top_builddir)


clean-local:
	-rm -fv $(abs_builddir)/__lua_built__.c \
		$(top_builddir)/liblua_ddakong.so
	-make -C $(top_srcdir)/$(LUA_SRC) clean


