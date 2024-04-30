/*
 * Library integer functions test program
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

#include "../libfwevt/libfwevt_integer.h"

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

/* Tests the libfwevt_integer_copy_from_utf16_stream function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_integer_copy_from_utf16_stream(
     void )
{
	uint8_t utf16_stream1[ 10 ] = {
		'1', 0, '2', 0, '3', 0, '4', 0, 0, 0 };

	libcerror_error_t *error = NULL;
	uint64_t integer_value   = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_integer_copy_from_utf16_stream(
	          &integer_value,
	          utf16_stream1,
	          10,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_UINT64(
	 "integer_value",
	 integer_value,
	 (uint64_t) 1234 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_integer_copy_from_utf16_stream(
	          NULL,
	          utf16_stream1,
	          10,
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

	result = libfwevt_integer_copy_from_utf16_stream(
	          &integer_value,
	          NULL,
	          10,
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

	result = libfwevt_integer_copy_from_utf16_stream(
	          &integer_value,
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

	result = libfwevt_integer_copy_from_utf16_stream(
	          &integer_value,
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

	result = libfwevt_integer_copy_from_utf16_stream(
	          &integer_value,
	          utf16_stream1,
	          9,
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
	 "libfwevt_integer_copy_from_utf16_stream",
	 fwevt_test_integer_copy_from_utf16_stream );

	/* TODO: add tests for libfwevt_integer_as_signed_decimal_get_string_size */

	/* TODO: add tests for libfwevt_integer_as_signed_decimal_copy_to_utf8_string_with_index */

	/* TODO: add tests for libfwevt_integer_as_signed_decimal_copy_to_utf16_string_with_index */

	/* TODO: add tests for libfwevt_integer_as_unsigned_decimal_get_string_size */

	/* TODO: add tests for libfwevt_integer_as_unsigned_decimal_copy_to_utf8_string_with_index */

	/* TODO: add tests for libfwevt_integer_as_unsigned_decimal_copy_to_utf16_string_with_index */

	/* TODO: add tests for libfwevt_integer_as_hexadecimal_copy_to_utf8_string_with_index */

	/* TODO: add tests for libfwevt_integer_as_hexadecimal_copy_to_utf16_string_with_index */

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */
}

