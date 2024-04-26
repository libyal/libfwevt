AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFVALUE_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBFWEVT_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYFWEVT = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	$(TESTS_PYFWEVT)

check_SCRIPTS = \
	pyfwevt_test_event.py \
	pyfwevt_test_manifest.py \
	pyfwevt_test_provider.py \
	pyfwevt_test_support.py \
	test_library.sh \
	test_manpage.sh \
	test_python_module.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	fwevt_test_channel \
	fwevt_test_error \
	fwevt_test_event \
	fwevt_test_keyword \
	fwevt_test_level \
	fwevt_test_manifest \
	fwevt_test_map \
	fwevt_test_notify \
	fwevt_test_opcode \
	fwevt_test_provider \
	fwevt_test_support \
	fwevt_test_task \
	fwevt_test_template \
	fwevt_test_template_item \
	fwevt_test_xml_document \
	fwevt_test_xml_tag \
	fwevt_test_xml_template_value \
	fwevt_test_xml_token \
	fwevt_test_xml_value

fwevt_test_channel_SOURCES = \
	fwevt_test_channel.c \
	fwevt_test_libcerror.h \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_memory.c fwevt_test_memory.h \
	fwevt_test_unused.h

fwevt_test_channel_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCERROR_LIBADD@

fwevt_test_error_SOURCES = \
	fwevt_test_error.c \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_unused.h

fwevt_test_error_LDADD = \
	../libfwevt/libfwevt.la

fwevt_test_event_SOURCES = \
	fwevt_test_event.c \
	fwevt_test_libcerror.h \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_memory.c fwevt_test_memory.h \
	fwevt_test_unused.h

fwevt_test_event_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCERROR_LIBADD@

fwevt_test_keyword_SOURCES = \
	fwevt_test_keyword.c \
	fwevt_test_libcerror.h \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_memory.c fwevt_test_memory.h \
	fwevt_test_unused.h

fwevt_test_keyword_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCERROR_LIBADD@

fwevt_test_level_SOURCES = \
	fwevt_test_level.c \
	fwevt_test_libcerror.h \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_memory.c fwevt_test_memory.h \
	fwevt_test_unused.h

fwevt_test_level_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCERROR_LIBADD@

fwevt_test_manifest_SOURCES = \
	fwevt_test_libcerror.h \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_manifest.c \
	fwevt_test_memory.c fwevt_test_memory.h \
	fwevt_test_unused.h

fwevt_test_manifest_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCERROR_LIBADD@

fwevt_test_map_SOURCES = \
	fwevt_test_libcerror.h \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_map.c \
	fwevt_test_memory.c fwevt_test_memory.h \
	fwevt_test_unused.h

fwevt_test_map_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCERROR_LIBADD@

fwevt_test_notify_SOURCES = \
	fwevt_test_libcerror.h \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_notify.c \
	fwevt_test_unused.h

fwevt_test_notify_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCERROR_LIBADD@

fwevt_test_opcode_SOURCES = \
	fwevt_test_libcerror.h \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_memory.c fwevt_test_memory.h \
	fwevt_test_opcode.c \
	fwevt_test_unused.h

fwevt_test_opcode_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCERROR_LIBADD@

fwevt_test_provider_SOURCES = \
	fwevt_test_libcerror.h \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_memory.c fwevt_test_memory.h \
	fwevt_test_provider.c \
	fwevt_test_unused.h

fwevt_test_provider_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCERROR_LIBADD@

fwevt_test_support_SOURCES = \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_support.c \
	fwevt_test_unused.h

fwevt_test_support_LDADD = \
	../libfwevt/libfwevt.la

fwevt_test_task_SOURCES = \
	fwevt_test_libcerror.h \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_memory.c fwevt_test_memory.h \
	fwevt_test_task.c \
	fwevt_test_unused.h

fwevt_test_task_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCERROR_LIBADD@

fwevt_test_template_SOURCES = \
	fwevt_test_libcerror.h \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_memory.c fwevt_test_memory.h \
	fwevt_test_template.c \
	fwevt_test_unused.h

fwevt_test_template_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCERROR_LIBADD@

fwevt_test_template_item_SOURCES = \
	fwevt_test_libcerror.h \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_memory.c fwevt_test_memory.h \
	fwevt_test_template_item.c \
	fwevt_test_unused.h

fwevt_test_template_item_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCERROR_LIBADD@

fwevt_test_xml_document_SOURCES = \
	fwevt_test_libcerror.h \
	fwevt_test_libcnotify.h \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_memory.c fwevt_test_memory.h \
	fwevt_test_unused.h \
	fwevt_test_xml_document.c

fwevt_test_xml_document_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCERROR_LIBADD@

fwevt_test_xml_tag_SOURCES = \
	fwevt_test_libcerror.h \
	fwevt_test_libfvalue.h \
	fwevt_test_libfwevt.h \
	fwevt_test_libuna.h \
	fwevt_test_macros.h \
	fwevt_test_memory.c fwevt_test_memory.h \
	fwevt_test_unused.h \
	fwevt_test_xml_tag.c

fwevt_test_xml_tag_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCERROR_LIBADD@

fwevt_test_xml_template_value_SOURCES = \
	fwevt_test_libcerror.h \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_memory.c fwevt_test_memory.h \
	fwevt_test_unused.h \
	fwevt_test_xml_template_value.c

fwevt_test_xml_template_value_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCERROR_LIBADD@

fwevt_test_xml_token_SOURCES = \
	fwevt_test_libcerror.h \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_memory.c fwevt_test_memory.h \
	fwevt_test_unused.h \
	fwevt_test_xml_token.c

fwevt_test_xml_token_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCERROR_LIBADD@

fwevt_test_xml_value_SOURCES = \
	fwevt_test_libcerror.h \
	fwevt_test_libfvalue.h \
	fwevt_test_libfwevt.h \
	fwevt_test_libuna.h \
	fwevt_test_macros.h \
	fwevt_test_memory.c fwevt_test_memory.h \
	fwevt_test_unused.h \
	fwevt_test_xml_value.c

fwevt_test_xml_value_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCERROR_LIBADD@

DISTCLEANFILES = \
	Makefile \
	Makefile.in \
	notify_stream.log

