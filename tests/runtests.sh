#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libfwevt/.libs/libfwevt.1.dylib && test -f ./pyfwevt/.libs/pyfwevt.so;
then
	install_name_tool -change /usr/local/lib/libfwevt.1.dylib ${PWD}/libfwevt/.libs/libfwevt.1.dylib ./pyfwevt/.libs/pyfwevt.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

