

SUBDIRS = src plugins/random-phrase


dist_doc_DATA = README.org TODOs.org LICENSE doc
EXTRA_DIST = Makefile.util

dist-hook:
	-find $(dist) -name '*~' -exec rm {} \;
	-find $(dist) -name '*.a' -exec rm {} \;
	-find $(dist) -name '*.o' -exec rm {} \;
	-find $(dist) -name '*.la' -exec rm {} \;
	-find $(dist) -name '*.lo' -exec rm {} \;




