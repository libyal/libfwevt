#!/bin/sh
# Script to run tests
#
# Version: 20260714

if [ -f "${PWD}/libfwevt/.libs/libfwevt.1.dylib" ] && [ -f ./pyfwevt/.libs/pyfwevt.so ]
then
    install_name_tool -change /usr/local/lib/libfwevt.1.dylib "${PWD}/libfwevt/.libs/libfwevt.1.dylib" ./pyfwevt/.libs/pyfwevt.so
fi

make check-build > /dev/null

# shellcheck disable=SC2068
make check $@
RESULT=$?

if [ ${RESULT} -ne 0 ]
then
    find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

