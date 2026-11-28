/*
 * Library integer functions test program
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

	/* Test unsupported UTF-16 stream (> 42 bytes without NUL)
	 */
	{
		uint8_t utf16_stream_long[ 46 ] = {
			'1', 0, '2', 0, '3', 0, '4', 0, '5', 0, '6', 0, '7', 0, '8', 0,
			'9', 0, '0', 0, '1', 0, '2', 0, '3', 0, '4', 0, '5', 0, '6', 0,
			'7', 0, '8', 0, '9', 0, '0', 0, '1', 0, '2', 0, 0, 0 };
		uint8_t utf16_stream_high_byte[ 4 ] = { '1', 1, 0, 0 };
		uint8_t utf16_stream_non_digit[ 4 ] = { 'a', 0, 0, 0 };

		result = libfwevt_integer_copy_from_utf16_stream(
		          &integer_value,
		          utf16_stream_long,
		          46,
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
		          utf16_stream_high_byte,
		          4,
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
		          utf16_stream_non_digit,
		          4,
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

/* Tests the libfwevt_integer_as_signed_decimal_get_string_size function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_integer_as_signed_decimal_get_string_size(
     void )
{
	libcerror_error_t *error = NULL;
	size_t string_size       = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_integer_as_signed_decimal_get_string_size(
	          0,
	          32,
	          &string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "string_size",
	 string_size,
	 (size_t) 2 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_integer_as_signed_decimal_get_string_size(
	          12345,
	          32,
	          &string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "string_size",
	 string_size,
	 (size_t) 6 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test negative value (sign-magnitude representation used by function)
	 */
	result = libfwevt_integer_as_signed_decimal_get_string_size(
	          0x8000007bUL,
	          32,
	          &string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "string_size",
	 string_size,
	 (size_t) 5 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test minimum negative value (only sign bit set)
	 */
	result = libfwevt_integer_as_signed_decimal_get_string_size(
	          0x80,
	          8,
	          &string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "string_size",
	 string_size,
	 (size_t) 5 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_integer_as_signed_decimal_get_string_size(
	          0,
	          32,
	          NULL,
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

/* Tests the libfwevt_integer_as_signed_decimal_copy_to_utf8_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_integer_as_signed_decimal_copy_to_utf8_string_with_index(
     void )
{
	uint8_t utf8_string[ 32 ];

	libcerror_error_t *error = NULL;
	size_t utf8_string_index = 0;
	int result               = 0;

	/* Test regular cases
	 */
	utf8_string_index = 0;

	result = libfwevt_integer_as_signed_decimal_copy_to_utf8_string_with_index(
	          12345,
	          32,
	          utf8_string,
	          32,
	          &utf8_string_index,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_index",
	 utf8_string_index,
	 (size_t) 6 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = narrow_string_compare(
	          (char *) utf8_string,
	          "12345",
	          6 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf8_string_index = 0;

	result = libfwevt_integer_as_signed_decimal_copy_to_utf8_string_with_index(
	          0x8000007bUL,
	          32,
	          utf8_string,
	          32,
	          &utf8_string_index,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_index",
	 utf8_string_index,
	 (size_t) 5 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = narrow_string_compare(
	          (char *) utf8_string,
	          "-123",
	          5 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf8_string_index = 0;

	result = libfwevt_integer_as_signed_decimal_copy_to_utf8_string_with_index(
	          0x80,
	          8,
	          utf8_string,
	          32,
	          &utf8_string_index,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = narrow_string_compare(
	          (char *) utf8_string,
	          "-128",
	          5 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	utf8_string_index = 0;

	result = libfwevt_integer_as_signed_decimal_copy_to_utf8_string_with_index(
	          123,
	          32,
	          NULL,
	          32,
	          &utf8_string_index,
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

	result = libfwevt_integer_as_signed_decimal_copy_to_utf8_string_with_index(
	          123,
	          32,
	          utf8_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf8_string_index,
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

	result = libfwevt_integer_as_signed_decimal_copy_to_utf8_string_with_index(
	          123,
	          32,
	          utf8_string,
	          32,
	          NULL,
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

	result = libfwevt_integer_as_signed_decimal_copy_to_utf8_string_with_index(
	          123,
	          32,
	          utf8_string,
	          2,
	          &utf8_string_index,
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

/* Tests the libfwevt_integer_as_signed_decimal_copy_to_utf16_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_integer_as_signed_decimal_copy_to_utf16_string_with_index(
     void )
{
	uint16_t utf16_string[ 32 ];

	libcerror_error_t *error  = NULL;
	size_t utf16_string_index = 0;
	int result                = 0;

	/* Test regular cases
	 */
	utf16_string_index = 0;

	result = libfwevt_integer_as_signed_decimal_copy_to_utf16_string_with_index(
	          12345,
	          32,
	          utf16_string,
	          32,
	          &utf16_string_index,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 6 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FWEVT_TEST_ASSERT_EQUAL_UINT16(
	 "utf16_string[ 0 ]",
	 utf16_string[ 0 ],
	 (uint16_t) '1' );

	utf16_string_index = 0;

	result = libfwevt_integer_as_signed_decimal_copy_to_utf16_string_with_index(
	          0x8000007bUL,
	          32,
	          utf16_string,
	          32,
	          &utf16_string_index,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 5 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FWEVT_TEST_ASSERT_EQUAL_UINT16(
	 "utf16_string[ 0 ]",
	 utf16_string[ 0 ],
	 (uint16_t) '-' );

	utf16_string_index = 0;

	result = libfwevt_integer_as_signed_decimal_copy_to_utf16_string_with_index(
	          0x80,
	          8,
	          utf16_string,
	          32,
	          &utf16_string_index,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	utf16_string_index = 0;

	result = libfwevt_integer_as_signed_decimal_copy_to_utf16_string_with_index(
	          123,
	          32,
	          NULL,
	          32,
	          &utf16_string_index,
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

	result = libfwevt_integer_as_signed_decimal_copy_to_utf16_string_with_index(
	          123,
	          32,
	          utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_string_index,
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

	result = libfwevt_integer_as_signed_decimal_copy_to_utf16_string_with_index(
	          123,
	          32,
	          utf16_string,
	          32,
	          NULL,
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

	result = libfwevt_integer_as_signed_decimal_copy_to_utf16_string_with_index(
	          123,
	          32,
	          utf16_string,
	          2,
	          &utf16_string_index,
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

/* Tests the libfwevt_integer_as_unsigned_decimal_get_string_size function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_integer_as_unsigned_decimal_get_string_size(
     void )
{
	libcerror_error_t *error = NULL;
	size_t string_size       = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_integer_as_unsigned_decimal_get_string_size(
	          12345,
	          &string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "string_size",
	 string_size,
	 (size_t) 6 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_integer_as_unsigned_decimal_get_string_size(
	          12345,
	          NULL,
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

/* Tests the libfwevt_integer_as_unsigned_decimal_copy_to_utf8_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_integer_as_unsigned_decimal_copy_to_utf8_string_with_index(
     void )
{
	uint8_t utf8_string[ 32 ];

	libcerror_error_t *error = NULL;
	size_t utf8_string_index = 0;
	int result               = 0;

	/* Test regular cases
	 */
	utf8_string_index = 0;

	result = libfwevt_integer_as_unsigned_decimal_copy_to_utf8_string_with_index(
	          12345,
	          utf8_string,
	          32,
	          &utf8_string_index,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_index",
	 utf8_string_index,
	 (size_t) 6 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = narrow_string_compare(
	          (char *) utf8_string,
	          "12345",
	          6 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	utf8_string_index = 0;

	result = libfwevt_integer_as_unsigned_decimal_copy_to_utf8_string_with_index(
	          123,
	          NULL,
	          32,
	          &utf8_string_index,
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

	result = libfwevt_integer_as_unsigned_decimal_copy_to_utf8_string_with_index(
	          123,
	          utf8_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf8_string_index,
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

	result = libfwevt_integer_as_unsigned_decimal_copy_to_utf8_string_with_index(
	          123,
	          utf8_string,
	          32,
	          NULL,
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

	result = libfwevt_integer_as_unsigned_decimal_copy_to_utf8_string_with_index(
	          123,
	          utf8_string,
	          2,
	          &utf8_string_index,
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

/* Tests the libfwevt_integer_as_unsigned_decimal_copy_to_utf16_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_integer_as_unsigned_decimal_copy_to_utf16_string_with_index(
     void )
{
	uint16_t utf16_string[ 32 ];

	libcerror_error_t *error  = NULL;
	size_t utf16_string_index = 0;
	int result                = 0;

	/* Test regular cases
	 */
	utf16_string_index = 0;

	result = libfwevt_integer_as_unsigned_decimal_copy_to_utf16_string_with_index(
	          12345,
	          utf16_string,
	          32,
	          &utf16_string_index,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 6 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	utf16_string_index = 0;

	result = libfwevt_integer_as_unsigned_decimal_copy_to_utf16_string_with_index(
	          123,
	          NULL,
	          32,
	          &utf16_string_index,
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

	result = libfwevt_integer_as_unsigned_decimal_copy_to_utf16_string_with_index(
	          123,
	          utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_string_index,
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

	result = libfwevt_integer_as_unsigned_decimal_copy_to_utf16_string_with_index(
	          123,
	          utf16_string,
	          32,
	          NULL,
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

	result = libfwevt_integer_as_unsigned_decimal_copy_to_utf16_string_with_index(
	          123,
	          utf16_string,
	          2,
	          &utf16_string_index,
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

/* Tests the libfwevt_integer_as_hexadecimal_copy_to_utf8_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_integer_as_hexadecimal_copy_to_utf8_string_with_index(
     void )
{
	uint8_t utf8_string[ 32 ];

	libcerror_error_t *error = NULL;
	size_t utf8_string_index = 0;
	int result               = 0;

	/* Test regular cases
	 */
	utf8_string_index = 0;

	result = libfwevt_integer_as_hexadecimal_copy_to_utf8_string_with_index(
	          0x1234abcdUL,
	          32,
	          utf8_string,
	          32,
	          &utf8_string_index,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_index",
	 utf8_string_index,
	 (size_t) 11 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = narrow_string_compare(
	          (char *) utf8_string,
	          "0x1234abcd",
	          11 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	utf8_string_index = 0;

	result = libfwevt_integer_as_hexadecimal_copy_to_utf8_string_with_index(
	          0x0123456789abcdefULL,
	          64,
	          utf8_string,
	          32,
	          &utf8_string_index,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_index",
	 utf8_string_index,
	 (size_t) 19 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = narrow_string_compare(
	          (char *) utf8_string,
	          "0x0123456789abcdef",
	          19 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	utf8_string_index = 0;

	result = libfwevt_integer_as_hexadecimal_copy_to_utf8_string_with_index(
	          0x1234,
	          16,
	          utf8_string,
	          32,
	          &utf8_string_index,
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

	result = libfwevt_integer_as_hexadecimal_copy_to_utf8_string_with_index(
	          0x1234,
	          32,
	          NULL,
	          32,
	          &utf8_string_index,
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

	result = libfwevt_integer_as_hexadecimal_copy_to_utf8_string_with_index(
	          0x1234,
	          32,
	          utf8_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf8_string_index,
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

	result = libfwevt_integer_as_hexadecimal_copy_to_utf8_string_with_index(
	          0x1234,
	          32,
	          utf8_string,
	          32,
	          NULL,
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

	result = libfwevt_integer_as_hexadecimal_copy_to_utf8_string_with_index(
	          0x1234,
	          32,
	          utf8_string,
	          5,
	          &utf8_string_index,
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

/* Tests the libfwevt_integer_as_hexadecimal_copy_to_utf16_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_integer_as_hexadecimal_copy_to_utf16_string_with_index(
     void )
{
	uint16_t utf16_string[ 32 ];

	libcerror_error_t *error  = NULL;
	size_t utf16_string_index = 0;
	int result                = 0;

	/* Test regular cases
	 */
	utf16_string_index = 0;

	result = libfwevt_integer_as_hexadecimal_copy_to_utf16_string_with_index(
	          0x1234abcdUL,
	          32,
	          utf16_string,
	          32,
	          &utf16_string_index,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 11 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_string_index = 0;

	result = libfwevt_integer_as_hexadecimal_copy_to_utf16_string_with_index(
	          0x0123456789abcdefULL,
	          64,
	          utf16_string,
	          32,
	          &utf16_string_index,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 19 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	utf16_string_index = 0;

	result = libfwevt_integer_as_hexadecimal_copy_to_utf16_string_with_index(
	          0x1234,
	          16,
	          utf16_string,
	          32,
	          &utf16_string_index,
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

	result = libfwevt_integer_as_hexadecimal_copy_to_utf16_string_with_index(
	          0x1234,
	          32,
	          NULL,
	          32,
	          &utf16_string_index,
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

	result = libfwevt_integer_as_hexadecimal_copy_to_utf16_string_with_index(
	          0x1234,
	          32,
	          utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_string_index,
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

	result = libfwevt_integer_as_hexadecimal_copy_to_utf16_string_with_index(
	          0x1234,
	          32,
	          utf16_string,
	          32,
	          NULL,
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

	result = libfwevt_integer_as_hexadecimal_copy_to_utf16_string_with_index(
	          0x1234,
	          32,
	          utf16_string,
	          5,
	          &utf16_string_index,
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

	FWEVT_TEST_RUN(
	 "libfwevt_integer_as_signed_decimal_get_string_size",
	 fwevt_test_integer_as_signed_decimal_get_string_size );

	FWEVT_TEST_RUN(
	 "libfwevt_integer_as_signed_decimal_copy_to_utf8_string_with_index",
	 fwevt_test_integer_as_signed_decimal_copy_to_utf8_string_with_index );

	FWEVT_TEST_RUN(
	 "libfwevt_integer_as_signed_decimal_copy_to_utf16_string_with_index",
	 fwevt_test_integer_as_signed_decimal_copy_to_utf16_string_with_index );

	FWEVT_TEST_RUN(
	 "libfwevt_integer_as_unsigned_decimal_get_string_size",
	 fwevt_test_integer_as_unsigned_decimal_get_string_size );

	FWEVT_TEST_RUN(
	 "libfwevt_integer_as_unsigned_decimal_copy_to_utf8_string_with_index",
	 fwevt_test_integer_as_unsigned_decimal_copy_to_utf8_string_with_index );

	FWEVT_TEST_RUN(
	 "libfwevt_integer_as_unsigned_decimal_copy_to_utf16_string_with_index",
	 fwevt_test_integer_as_unsigned_decimal_copy_to_utf16_string_with_index );

	FWEVT_TEST_RUN(
	 "libfwevt_integer_as_hexadecimal_copy_to_utf8_string_with_index",
	 fwevt_test_integer_as_hexadecimal_copy_to_utf8_string_with_index );

	FWEVT_TEST_RUN(
	 "libfwevt_integer_as_hexadecimal_copy_to_utf16_string_with_index",
	 fwevt_test_integer_as_hexadecimal_copy_to_utf16_string_with_index );

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */
}

