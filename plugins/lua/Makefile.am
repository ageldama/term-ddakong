
SUBDIRS = src

EXTRA_DIST = lua-5.4.7

dist-hook:
	-find $(dist) -name '*~' -exec rm {} \;
	-find $(dist) -name '*.a' -exec rm {} \;
	-find $(dist) -name '*.o' -exec rm {} \;
	-rm -f $(dist)/lua-5.4.7/src/lua
	-rm -f $(dist)/lua-5.4.7/src/luac
