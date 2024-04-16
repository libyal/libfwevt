if HAVE_PYTHON
AM_CFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFWEVT_DLL_IMPORT@

pyexec_LTLIBRARIES = pyfwevt.la

pyfwevt_la_SOURCES = \
	pyfwevt.c pyfwevt.h \
	pyfwevt_channel.c pyfwevt_channel.h \
	pyfwevt_channels.c pyfwevt_channels.h \
	pyfwevt_error.c pyfwevt_error.h \
	pyfwevt_event.c pyfwevt_event.h \
	pyfwevt_events.c pyfwevt_events.h \
	pyfwevt_guid.c pyfwevt_guid.h \
	pyfwevt_integer.c pyfwevt_integer.h \
	pyfwevt_keyword.c pyfwevt_keyword.h \
	pyfwevt_keywords.c pyfwevt_keywords.h \
	pyfwevt_level.c pyfwevt_level.h \
	pyfwevt_levels.c pyfwevt_levels.h \
	pyfwevt_libcerror.h \
	pyfwevt_libfguid.h \
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
	pyfwevt_template_item.c pyfwevt_template_item.h \
	pyfwevt_template_items.c pyfwevt_template_items.h \
	pyfwevt_templates.c pyfwevt_templates.h \
	pyfwevt_unused.h

pyfwevt_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libfwevt/libfwevt.la \
	@LIBCDATA_LIBADD@ \
	@LIBFGUID_LIBADD@

pyfwevt_la_CPPFLAGS = $(PYTHON_CPPFLAGS)
pyfwevt_la_LDFLAGS  = -module -avoid-version $(PYTHON_LDFLAGS)

endif

DISTCLEANFILES = \
	Makefile \
	Makefile.in

