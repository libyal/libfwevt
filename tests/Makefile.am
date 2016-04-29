AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBFWEVT_DLL_IMPORT@

TESTS = \
	test_api_functions.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	fwevt_test_get_version

fwevt_test_get_version_SOURCES = \
	fwevt_test_get_version.c \
	fwevt_test_libcstring.h \
	fwevt_test_libfwevt.h \
	fwevt_test_unused.h

fwevt_test_get_version_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

