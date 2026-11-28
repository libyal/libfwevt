/*
 * Library date and time functions test program
 *
 * Copyright (C) 2011-2026, Joachim Metz <joachim.metz@gmail.com>
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

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

/* Tests the libfwevt_filetime_copy_from_utf16_stream function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_filetime_copy_from_utf16_stream(
     void )
{
	uint8_t utf16_stream1[ 62 ] = {
		'1', 0, '6', 0, '0', 0, '1', 0, '-', 0, '0', 0, '1', 0, '-', 0,
	       	'0', 0, '1', 0, 'T', 0, '0', 0, '0', 0, ':', 0, '0', 0, '0', 0,
	       	':', 0, '0', 0, '0', 0, '.', 0, '0', 0, '0', 0, '0', 0, '0', 0,
	       	'0', 0, '0', 0, '0', 0, '0', 0, '0', 0, 'Z', 0, 0, 0 };

	uint8_t utf16_stream2[ 62 ] = {
		'2', 0, '0', 0, '2', 0, '2', 0, '-', 0, '0', 0, '7', 0, '-', 0,
	       	'0', 0, '6', 0, 'T', 0, '1', 0, '2', 0, ':', 0, '2', 0, '4', 0,
	       	':', 0, '4', 0, '0', 0, '.', 0, '6', 0, '0', 0, '8', 0, '1', 0,
	       	'1', 0, '5', 0, '5', 0, '0', 0, '0', 0, 'Z', 0, 0, 0 };

	libcerror_error_t *error = NULL;
	uint64_t filetime        = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_filetime_copy_from_utf16_stream(
	          &filetime,
	          utf16_stream1,
	          62,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_UINT64(
	 "filetime",
	 filetime,
	 (uint64_t) 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_filetime_copy_from_utf16_stream(
	          &filetime,
	          utf16_stream2,
	          62,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_UINT64(
	 "filetime",
	 filetime,
	 (uint64_t) 133015838806081155UL );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test leap year (2000-02-29) and month 12 (2024-12-31) and month 4 (2023-04-30)
	 */
	{
		uint8_t utf16_leap_feb[ 62 ] = {
			'2', 0, '0', 0, '0', 0, '0', 0, '-', 0, '0', 0, '2', 0, '-', 0,
			'2', 0, '9', 0, 'T', 0, '2', 0, '3', 0, ':', 0, '5', 0, '9', 0,
			':', 0, '5', 0, '9', 0, '.', 0, '0', 0, '0', 0, '0', 0, '0', 0,
			'0', 0, '0', 0, '0', 0, '0', 0, '0', 0, 'Z', 0, 0, 0 };
		uint8_t utf16_nonleap_feb[ 62 ] = {
			'2', 0, '0', 0, '2', 0, '3', 0, '-', 0, '0', 0, '2', 0, '-', 0,
			'2', 0, '8', 0, 'T', 0, '0', 0, '0', 0, ':', 0, '0', 0, '0', 0,
			':', 0, '0', 0, '0', 0, '.', 0, '0', 0, '0', 0, '0', 0, '0', 0,
			'0', 0, '0', 0, '0', 0, '0', 0, '0', 0, 'Z', 0, 0, 0 };
		uint8_t utf16_leap_dec[ 62 ] = {
			'2', 0, '0', 0, '2', 0, '4', 0, '-', 0, '1', 0, '2', 0, '-', 0,
			'3', 0, '1', 0, 'T', 0, '0', 0, '0', 0, ':', 0, '0', 0, '0', 0,
			':', 0, '0', 0, '0', 0, '.', 0, '0', 0, '0', 0, '0', 0, '0', 0,
			'0', 0, '0', 0, '0', 0, '0', 0, '0', 0, 'Z', 0, 0, 0 };
		uint8_t utf16_apr[ 62 ] = {
			'2', 0, '0', 0, '2', 0, '3', 0, '-', 0, '0', 0, '4', 0, '-', 0,
			'3', 0, '0', 0, 'T', 0, '0', 0, '0', 0, ':', 0, '0', 0, '0', 0,
			':', 0, '0', 0, '0', 0, '.', 0, '0', 0, '0', 0, '0', 0, '0', 0,
			'0', 0, '0', 0, '0', 0, '0', 0, '0', 0, 'Z', 0, 0, 0 };

		result = libfwevt_filetime_copy_from_utf16_stream( &filetime, utf16_leap_feb, 62, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
		FWEVT_TEST_ASSERT_IS_NULL( "error", error );

		result = libfwevt_filetime_copy_from_utf16_stream( &filetime, utf16_nonleap_feb, 62, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
		FWEVT_TEST_ASSERT_IS_NULL( "error", error );

		result = libfwevt_filetime_copy_from_utf16_stream( &filetime, utf16_leap_dec, 62, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
		FWEVT_TEST_ASSERT_IS_NULL( "error", error );

		result = libfwevt_filetime_copy_from_utf16_stream( &filetime, utf16_apr, 62, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
		FWEVT_TEST_ASSERT_IS_NULL( "error", error );
	}

	/* Test error cases
	 */
	result = libfwevt_filetime_copy_from_utf16_stream(
	          NULL,
	          utf16_stream1,
	          62,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_filetime_copy_from_utf16_stream(
	          &filetime,
	          NULL,
	          62,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_filetime_copy_from_utf16_stream(
	          &filetime,
	          utf16_stream1,
	          0,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_filetime_copy_from_utf16_stream(
	          &filetime,
	          utf16_stream1,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_filetime_copy_from_utf16_stream(
	          &filetime,
	          utf16_stream1,
	          63,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test malformed date-time streams covering all validation branches
	 */
	{
		uint8_t bad[ 62 ];
		size_t idx = 0;

		/* Bad separator */
		for( idx = 0; idx < 62; idx++ ) bad[ idx ] = utf16_stream2[ idx ];
		bad[ 8 ] = 'X';
		result = libfwevt_filetime_copy_from_utf16_stream( &filetime, bad, 62, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
		libcerror_error_free( &error );

		/* Bad year digit */
		for( idx = 0; idx < 62; idx++ ) bad[ idx ] = utf16_stream2[ idx ];
		bad[ 0 ] = 'A';
		result = libfwevt_filetime_copy_from_utf16_stream( &filetime, bad, 62, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
		libcerror_error_free( &error );

		/* Bad month digit */
		for( idx = 0; idx < 62; idx++ ) bad[ idx ] = utf16_stream2[ idx ];
		bad[ 10 ] = 'A';
		result = libfwevt_filetime_copy_from_utf16_stream( &filetime, bad, 62, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
		libcerror_error_free( &error );

		/* Bad day digit */
		for( idx = 0; idx < 62; idx++ ) bad[ idx ] = utf16_stream2[ idx ];
		bad[ 16 ] = 'A';
		result = libfwevt_filetime_copy_from_utf16_stream( &filetime, bad, 62, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
		libcerror_error_free( &error );

		/* Bad hour digit */
		for( idx = 0; idx < 62; idx++ ) bad[ idx ] = utf16_stream2[ idx ];
		bad[ 22 ] = 'A';
		result = libfwevt_filetime_copy_from_utf16_stream( &filetime, bad, 62, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
		libcerror_error_free( &error );

		/* Bad minute digit */
		for( idx = 0; idx < 62; idx++ ) bad[ idx ] = utf16_stream2[ idx ];
		bad[ 28 ] = 'A';
		result = libfwevt_filetime_copy_from_utf16_stream( &filetime, bad, 62, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
		libcerror_error_free( &error );

		/* Bad second digit */
		for( idx = 0; idx < 62; idx++ ) bad[ idx ] = utf16_stream2[ idx ];
		bad[ 34 ] = 'A';
		result = libfwevt_filetime_copy_from_utf16_stream( &filetime, bad, 62, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
		libcerror_error_free( &error );

		/* Bad fraction digit */
		for( idx = 0; idx < 62; idx++ ) bad[ idx ] = utf16_stream2[ idx ];
		bad[ 40 ] = 'A';
		result = libfwevt_filetime_copy_from_utf16_stream( &filetime, bad, 62, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
		libcerror_error_free( &error );

		/* Year < 1600 */
		for( idx = 0; idx < 62; idx++ ) bad[ idx ] = utf16_stream2[ idx ];
		bad[ 0 ] = '1'; bad[ 2 ] = '5'; bad[ 4 ] = '9'; bad[ 6 ] = '9';
		result = libfwevt_filetime_copy_from_utf16_stream( &filetime, bad, 62, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
		libcerror_error_free( &error );

		/* Month out of range (13) */
		for( idx = 0; idx < 62; idx++ ) bad[ idx ] = utf16_stream2[ idx ];
		bad[ 10 ] = '1'; bad[ 12 ] = '3';
		result = libfwevt_filetime_copy_from_utf16_stream( &filetime, bad, 62, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
		libcerror_error_free( &error );

		/* Day out of range (32) */
		for( idx = 0; idx < 62; idx++ ) bad[ idx ] = utf16_stream2[ idx ];
		bad[ 16 ] = '3'; bad[ 18 ] = '2';
		result = libfwevt_filetime_copy_from_utf16_stream( &filetime, bad, 62, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
		libcerror_error_free( &error );

		/* Hours out of range (24) */
		for( idx = 0; idx < 62; idx++ ) bad[ idx ] = utf16_stream2[ idx ];
		bad[ 22 ] = '2'; bad[ 24 ] = '4';
		result = libfwevt_filetime_copy_from_utf16_stream( &filetime, bad, 62, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
		libcerror_error_free( &error );

		/* Minutes out of range (60) */
		for( idx = 0; idx < 62; idx++ ) bad[ idx ] = utf16_stream2[ idx ];
		bad[ 28 ] = '6'; bad[ 30 ] = '0';
		result = libfwevt_filetime_copy_from_utf16_stream( &filetime, bad, 62, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
		libcerror_error_free( &error );

		/* Seconds out of range (60) */
		for( idx = 0; idx < 62; idx++ ) bad[ idx ] = utf16_stream2[ idx ];
		bad[ 34 ] = '6'; bad[ 36 ] = '0';
		result = libfwevt_filetime_copy_from_utf16_stream( &filetime, bad, 62, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
		libcerror_error_free( &error );
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

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

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

	FWEVT_TEST_RUN(
	 "libfwevt_filetime_copy_from_utf16_stream",
	 fwevt_test_filetime_copy_from_utf16_stream );

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */
}

