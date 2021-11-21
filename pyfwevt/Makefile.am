if HAVE_PYTHON
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBFWEVT_DLL_IMPORT@

pyexec_LTLIBRARIES = pyfwevt.la

pyfwevt_la_SOURCES = \
	pyfwevt.c pyfwevt.h \
	pyfwevt_channel.c pyfwevt_channel.h \
	pyfwevt_channels.c pyfwevt_channels.h \
	pyfwevt_error.c pyfwevt_error.h \
	pyfwevt_event.c pyfwevt_event.h \
	pyfwevt_events.c pyfwevt_events.h \
	pyfwevt_integer.c pyfwevt_integer.h \
	pyfwevt_libcerror.h \
	pyfwevt_libfwevt.h \
	pyfwevt_manifest.c pyfwevt_manifest.h \
	pyfwevt_provider.c pyfwevt_provider.h \
	pyfwevt_providers.c pyfwevt_providers.h \
	pyfwevt_python.h \
	pyfwevt_unused.h

pyfwevt_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libfwevt/libfwevt.la \
	@LIBCDATA_LIBADD@

pyfwevt_la_CPPFLAGS = $(PYTHON_CPPFLAGS)
pyfwevt_la_LDFLAGS  = -module -avoid-version $(PYTHON_LDFLAGS)

endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

