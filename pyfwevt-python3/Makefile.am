# Note that we cannot use: AUTOMAKE_OPTIONS = subdir-objects
# subdir-objects will compile the source files to a single version of Python.
# Since subdir-objects is being deprecated we copy the source files instead.
am__installdirs = "$(DESTDIR)$(pyexecdir3)"
pyexecdir = $(pyexecdir3)

if HAVE_PYTHON3
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBFWEVT_DLL_IMPORT@

am_pyfwevt_la_rpath = -rpath $(pyexecdir3)

BUILT_SOURCES = \
	pyfwevt.c pyfwevt.h \
	pyfwevt_error.c pyfwevt_error.h \
	pyfwevt_integer.c pyfwevt_integer.h \
	pyfwevt_libcerror.h \
	pyfwevt_libfwevt.h \
	pyfwevt_python.h \
	pyfwevt_template.c pyfwevt_template.h \
	pyfwevt_unused.h

pyexec_LTLIBRARIES = pyfwevt.la

nodist_pyfwevt_la_SOURCES = $(BUILT_SOURCES)

pyfwevt_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libfwevt/libfwevt.la \
	@LIBCDATA_LIBADD@

pyfwevt_la_CPPFLAGS = $(PYTHON3_CPPFLAGS)
pyfwevt_la_LDFLAGS  = -module -avoid-version $(PYTHON3_LDFLAGS)

$(BUILT_SOURCES):
	/bin/cp -f $(top_srcdir)/pyfwevt/$@ $@

endif

MAINTAINERCLEANFILES = \
	Makefile.in

clean-local:
	/bin/rm -f pyfwevt*.[ch]

distclean: clean
	/bin/rm -f Makefile

