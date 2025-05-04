

SUBDIRS = src $(PLUGIN_RANDOM_PHRASE_DIR) $(PLUGIN_LUA_DIR)


dist_doc_DATA = README.org TODOs.org LICENSE doc
EXTRA_DIST = Makefile.util

dist-hook:
	-find $(distdir) -name '*~' -exec rm {} \;
	-find $(distdir) -name '*.a' -exec rm {} \;
	-find $(distdir) -name '*.o' -exec rm {} \;
	-find $(distdir) -name '*.la' -exec rm {} \;
	-find $(distdir) -name '*.lo' -exec rm {} \;




