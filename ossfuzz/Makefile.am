if HAVE_LIB_FUZZING_ENGINE
AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common

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

DISTCLEANFILES = \
	Makefile \
	Makefile.in

splint-local:
	@echo "Running splint on manifest_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(manifest_fuzzer_SOURCES)
	@echo "Running splint on xml_document_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(xml_document_fuzzer_SOURCES)

