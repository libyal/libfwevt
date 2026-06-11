#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libfwevt/.libs/libfwevt.1.dylib && test -f ./pyfwevt/.libs/pyfwevt.so
then
	install_name_tool -change /usr/local/lib/libfwevt.1.dylib ${PWD}/libfwevt/.libs/libfwevt.1.dylib ./pyfwevt/.libs/pyfwevt.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

