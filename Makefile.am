

SUBDIRS = src

if RANDOM_PHRASE
    SUBDIRS += plugins/random-phrase
endif

if LUA
    SUBDIRS += plugins/lua
endif



dist_doc_DATA = README.org TODOs.org LICENSE doc
EXTRA_DIST = Makefile.util

dist-hook:
	-find $(distdir) -name '*~' -exec rm {} \;
	-find $(distdir) -name '*.a' -exec rm {} \;
	-find $(distdir) -name '*.o' -exec rm {} \;
	-find $(distdir) -name '*.la' -exec rm {} \;
	-find $(distdir) -name '*.lo' -exec rm {} \;




