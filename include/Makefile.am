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
	/bin/rm -f libfwevt.h
	/bin/rm -f libfwevt/definitions.h
	/bin/rm -f libfwevt/features.h
	/bin/rm -f libfwevt/types.h
	/bin/rm -f Makefile

