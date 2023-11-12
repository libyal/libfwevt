include_HEADERS = \
	libfwevt.h

pkginclude_HEADERS = \
	libfwevt/definitions.h \
	libfwevt/error.h \
	libfwevt/extern.h \
	libfwevt/features.h \
	libfwevt/types.h

EXTRA_DIST = \
	libfwevt.h.in \
	libfwevt/definitions.h.in \
	libfwevt/features.h.in \
	libfwevt/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libfwevt.h
	-rm -f libfwevt/definitions.h
	-rm -f libfwevt/features.h
	-rm -f libfwevt/types.h
	-rm -f Makefile

