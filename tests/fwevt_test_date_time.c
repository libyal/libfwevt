/*
 * Library date and time functions test program
 *
 * Copyright (C) 2011-2024, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fwevt_test_libcerror.h"
#include "fwevt_test_libfwevt.h"
#include "fwevt_test_macros.h"
#include "fwevt_test_unused.h"

#include "../libfwevt/libfwevt_date_time.h"

/* Tests the libfwevt_utf8_string_copy_to_filetime function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_utf8_string_copy_to_filetime(
     void )
{
	libcerror_error_t *error = NULL;
	uint64_t filetime        = 0;
	int result               = 0;

	result = libfwevt_utf8_string_copy_to_filetime(
	          (uint8_t *) "1601-01-01T00:00:00.000000000Z",
	          31,
	          &filetime,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_UINT64(
	 "filetime",
	 filetime,
	 (uint64_t) 0ULL );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_utf8_string_copy_to_filetime(
	          (uint8_t *) "2022-07-06T12:24:40.608115500Z",
	          31,
	          &filetime,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_UINT64(
	 "filetime",
	 filetime,
	 (uint64_t) 133015838806081155ULL );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc FWEVT_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] FWEVT_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc FWEVT_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] FWEVT_TEST_ATTRIBUTE_UNUSED )
#endif
{
	FWEVT_TEST_UNREFERENCED_PARAMETER( argc )
	FWEVT_TEST_UNREFERENCED_PARAMETER( argv )

	FWEVT_TEST_RUN(
	 "libfwevt_utf8_string_copy_to_filetime",
	 fwevt_test_utf8_string_copy_to_filetime );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

