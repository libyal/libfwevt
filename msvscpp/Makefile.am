MSVSCPP_FILES = \
	fwevt_test_get_version/fwevt_test_get_version.vcproj \
	libcdata/libcdata.vcproj \
	libcerror/libcerror.vcproj \
	libcnotify/libcnotify.vcproj \
	libcstring/libcstring.vcproj \
	libcthreads/libcthreads.vcproj \
	libfdatetime/libfdatetime.vcproj \
	libfguid/libfguid.vcproj \
	libfvalue/libfvalue.vcproj \
	libfwevt/libfwevt.vcproj \
	libuna/libuna.vcproj \
	libfwevt.sln

SCRIPT_FILES = \
	scripts/vs2008_x64.sh \
	scripts/vs2008_x64_sln.sed \
	scripts/vs2008_x64_vcproj.sed \
	scripts/vs2010_x64.sh \
	scripts/vs2010_x64_sln.sed \
	scripts/vs2010_x64_vcxproj.sed

EXTRA_DIST = \
	$(MSVSCPP_FILES) \
	$(SCRIPT_FILES)

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

