
SUBDIRS = src

EXTRA_DIST = $(LUA_SRC)

.PHONY: cp-lib
cp-lib:
	make -C $(top_builddir)/src $@

dist-hook:
	-find $(distdir) -name '*~' -exec rm {} \;
	-find $(distdir) -name '*.a' -exec rm {} \;
	-find $(distdir) -name '*.o' -exec rm {} \;
	-rm -f $(distdir)/$(LUA_SRC)/src/lua
	-rm -f $(distdir)/$(LUA_SRC)/src/luac

