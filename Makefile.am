

if LUA_ENABLED
	LUA_OPT = lua-5.4.7
endif


SUBDIRS = $(LUA_OPT) src


dist_doc_DATA = README.org TODOs.org LICENSE doc
EXTRA_DIST = examples Makefile.util lua-5.4.7

dist-hook:
	-rm -rf examples/random-phrase-dll/src/.libs
	-rm -rf examples/random-phrase-dll/src/.deps
	-rm -rf examples/random-phrase-dll/src/Makefile
	-rm -rf examples/random-phrase-dll/Makefile
	-rm -rf examples/random-phrase-dll/config.log
	-rm -rf examples/random-phrase-dll/stamp-h1
	-rm -rf examples/random-phrase-dll/autom4te.cache
	-rm -f lua-5.4.7/src/lua
	-rm -f lua-5.4.7/src/luac

	-find $(dist) -name '*~' -exec rm {} \;
	-find $(dist) -name '*.a' -exec rm {} \;
	-find $(dist) -name '*.o' -exec rm {} \;
	-find $(dist) -name '*.la' -exec rm {} \;
	-find $(dist) -name '*.lo' -exec rm {} \;


