lib_LTLIBRARIES = librandom_phrase_ddakong.la
librandom_phrase_ddakong_la_SOURCES = dllmain.c im_handler.c


.PHONY: cp-lib
cp-lib: all
	-cp -fv .libs/librandom_phrase_ddakong.so $(top_builddir)

clean-local:
	-rm -fv $(top_builddir)/librandom_phrase_ddakong.so
