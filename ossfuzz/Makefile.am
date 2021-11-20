if HAVE_LIB_FUZZING_ENGINE
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common

bin_PROGRAMS = \
	manifest_fuzzer \
	xml_document_fuzzer

manifest_fuzzer_SOURCES = \
	manifest_fuzzer.cc \
	ossfuzz_libfwevt.h

manifest_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libfwevt/libfwevt.la

xml_document_fuzzer_SOURCES = \
	ossfuzz_libfwevt.h \
	xml_document_fuzzer.cc

xml_document_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libfwevt/libfwevt.la
endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on manifest_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(manifest_fuzzer_SOURCES)
	@echo "Running splint on xml_document_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(xml_document_fuzzer_SOURCES)

