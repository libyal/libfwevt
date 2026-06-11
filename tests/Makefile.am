AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFWNT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBFWEVT_DLL_IMPORT@

check_PYTHONdir = $(abs_top_builddir)

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages

if HAVE_PYTHON_TESTS
check_AUTOTESTS += test_python_module
endif

check_PYTHON_SCRIPTS = \
	pyfwevt_test_event.py \
	pyfwevt_test_manifest.py \
	pyfwevt_test_provider.py \
	pyfwevt_test_support.py

check_PROGRAMS = \
	fwevt_test_channel \
	fwevt_test_data_segment \
	fwevt_test_date_time \
	fwevt_test_error \
	fwevt_test_event \
	fwevt_test_floating_point \
	fwevt_test_integer \
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

fwevt_test_data_segment_SOURCES = \
	fwevt_test_data_segment.c \
	fwevt_test_libcerror.h \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_memory.c fwevt_test_memory.h \
	fwevt_test_unused.h

fwevt_test_data_segment_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCERROR_LIBADD@

fwevt_test_date_time_SOURCES = \
	fwevt_test_date_time.c \
	fwevt_test_libcerror.h \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_unused.h

fwevt_test_date_time_LDADD = \
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

fwevt_test_floating_point_SOURCES = \
	fwevt_test_floating_point.c \
	fwevt_test_libcerror.h \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_unused.h

fwevt_test_floating_point_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCERROR_LIBADD@

fwevt_test_integer_SOURCES = \
	fwevt_test_integer.c \
	fwevt_test_libcerror.h \
	fwevt_test_libfwevt.h \
	fwevt_test_macros.h \
	fwevt_test_unused.h

fwevt_test_integer_LDADD = \
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
	fwevt_test_libfwevt.h \
	fwevt_test_libuna.h \
	fwevt_test_macros.h \
	fwevt_test_memory.c fwevt_test_memory.h \
	fwevt_test_unused.h \
	fwevt_test_xml_value.c

fwevt_test_xml_value_LDADD = \
	../libfwevt/libfwevt.la \
	@LIBCERROR_LIBADD@

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_library: package.m4 test_library.at test_macros.at

test_manpages: package.m4 test_manpages.at

test_python_module: package.m4 test_python_module.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	$(check_PYTHON_SCRIPTS) \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	notify_stream.log

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

