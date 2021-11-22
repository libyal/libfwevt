# Note that we cannot use: AUTOMAKE_OPTIONS = subdir-objects
# subdir-objects will compile the source files to a single version of Python.
# Since subdir-objects is being deprecated we copy the source files instead.
am__installdirs = "$(DESTDIR)$(pyexecdir2)"
pyexecdir = $(pyexecdir2)

if HAVE_PYTHON2
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBFWEVT_DLL_IMPORT@

am_pyfwevt_la_rpath = -rpath $(pyexecdir2)

BUILT_SOURCES = \
	pyfwevt.c pyfwevt.h \
	pyfwevt_channel.c pyfwevt_channel.h \
	pyfwevt_channels.c pyfwevt_channels.h \
	pyfwevt_error.c pyfwevt_error.h \
	pyfwevt_event.c pyfwevt_event.h \
	pyfwevt_events.c pyfwevt_events.h \
	pyfwevt_integer.c pyfwevt_integer.h \
	pyfwevt_keyword.c pyfwevt_keyword.h \
	pyfwevt_keywords.c pyfwevt_keywords.h \
	pyfwevt_level.c pyfwevt_level.h \
	pyfwevt_levels.c pyfwevt_levels.h \
	pyfwevt_libcerror.h \
	pyfwevt_libfwevt.h \
	pyfwevt_manifest.c pyfwevt_manifest.h \
	pyfwevt_map.c pyfwevt_map.h \
	pyfwevt_maps.c pyfwevt_maps.h \
	pyfwevt_opcode.c pyfwevt_opcode.h \
	pyfwevt_opcodes.c pyfwevt_opcodes.h \
	pyfwevt_provider.c pyfwevt_provider.h \
	pyfwevt_providers.c pyfwevt_providers.h \
	pyfwevt_python.h \
	pyfwevt_task.c pyfwevt_task.h \
	pyfwevt_tasks.c pyfwevt_tasks.h \
	pyfwevt_template.c pyfwevt_template.h \
	pyfwevt_templates.c pyfwevt_templates.h \
	pyfwevt_unused.h

pyexec_LTLIBRARIES = pyfwevt.la

nodist_pyfwevt_la_SOURCES = $(BUILT_SOURCES)

pyfwevt_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libfwevt/libfwevt.la \
	@LIBCDATA_LIBADD@

pyfwevt_la_CPPFLAGS = $(PYTHON2_CPPFLAGS)
pyfwevt_la_LDFLAGS  = -module -avoid-version $(PYTHON2_LDFLAGS)

$(BUILT_SOURCES):
	/bin/cp -f $(top_srcdir)/pyfwevt/$@ $@

endif

MAINTAINERCLEANFILES = \
	Makefile.in

clean-local:
	/bin/rm -f pyfwevt*.[ch]

distclean: clean
	/bin/rm -f Makefile

