/*
 * Library xml_value type test program
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
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fwevt_test_libcerror.h"
#include "fwevt_test_libfwevt.h"
#include "fwevt_test_libuna.h"
#include "fwevt_test_macros.h"
#include "fwevt_test_memory.h"
#include "fwevt_test_unused.h"

#include "../libfwevt/libfwevt_xml_string.h"
#include "../libfwevt/libfwevt_xml_value.h"

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

/* Tests the libfwevt_xml_value_initialize function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_value_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfwevt_xml_value_t *xml_value = NULL;
	int result                      = 0;

#if defined( HAVE_FWEVT_TEST_MEMORY )
	int number_of_malloc_fail_tests = 2;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libfwevt_xml_value_initialize(
	          &xml_value,
	          LIBFWEVT_VALUE_TYPE_BINARY_DATA,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_value",
	 xml_value );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_internal_xml_value_free(
	          (libfwevt_internal_xml_value_t **) &xml_value,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "xml_value",
	 xml_value );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_xml_value_initialize(
	          NULL,
	          LIBFWEVT_VALUE_TYPE_BINARY_DATA,
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

	xml_value = (libfwevt_xml_value_t *) 0x12345678UL;

	result = libfwevt_xml_value_initialize(
	          &xml_value,
	          LIBFWEVT_VALUE_TYPE_BINARY_DATA,
	          &error );

	xml_value = NULL;

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_FWEVT_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfwevt_xml_value_initialize with malloc failing
		 */
		fwevt_test_malloc_attempts_before_fail = test_number;

		result = libfwevt_xml_value_initialize(
		          &xml_value,
		          LIBFWEVT_VALUE_TYPE_BINARY_DATA,
		          &error );

		if( fwevt_test_malloc_attempts_before_fail != -1 )
		{
			fwevt_test_malloc_attempts_before_fail = -1;

			if( xml_value != NULL )
			{
				libfwevt_internal_xml_value_free(
				 (libfwevt_internal_xml_value_t **) &xml_value,
				 NULL );
			}
		}
		else
		{
			FWEVT_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			FWEVT_TEST_ASSERT_IS_NULL(
			 "xml_value",
			 xml_value );

			FWEVT_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libfwevt_xml_value_initialize with memset failing
		 */
		fwevt_test_memset_attempts_before_fail = test_number;

		result = libfwevt_xml_value_initialize(
		          &xml_value,
		          LIBFWEVT_VALUE_TYPE_BINARY_DATA,
		          &error );

		if( fwevt_test_memset_attempts_before_fail != -1 )
		{
			fwevt_test_memset_attempts_before_fail = -1;

			if( xml_value != NULL )
			{
				libfwevt_internal_xml_value_free(
				 (libfwevt_internal_xml_value_t **) &xml_value,
				 NULL );
			}
		}
		else
		{
			FWEVT_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			FWEVT_TEST_ASSERT_IS_NULL(
			 "xml_value",
			 xml_value );

			FWEVT_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_FWEVT_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( xml_value != NULL )
	{
		libfwevt_internal_xml_value_free(
		 (libfwevt_internal_xml_value_t **) &xml_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_value_free function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_value_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfwevt_xml_value_free(
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

/* Tests the libfwevt_xml_value_get_type function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_value_get_type(
     libfwevt_xml_value_t *xml_value )
{
	libcerror_error_t *error = NULL;
	int result               = 0;
	uint8_t value_type       = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_value_get_type(
	          xml_value,
	          &value_type,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_UINT8(
	 "value_type",
	 value_type,
	 (uint8_t) LIBFWEVT_VALUE_TYPE_BINARY_DATA );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_xml_value_get_type(
	          NULL,
	          &value_type,
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

	result = libfwevt_xml_value_get_type(
	          xml_value,
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

/* Tests the libfwevt_xml_value_get_number_of_data_segments function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_value_get_number_of_data_segments(
     libfwevt_xml_value_t *xml_value )
{
	libcerror_error_t *error    = NULL;
	int number_of_data_segments = 0;
	int result                  = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_value_get_number_of_data_segments(
	          xml_value,
	          &number_of_data_segments,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "number_of_data_segments",
	 number_of_data_segments,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_xml_value_get_number_of_data_segments(
	          NULL,
	          &number_of_data_segments,
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

	result = libfwevt_xml_value_get_number_of_data_segments(
	          xml_value,
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

/* Tests the libfwevt_xml_value_get_data_size function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_value_get_data_size(
     libfwevt_xml_value_t *xml_value )
{
	libcerror_error_t *error = NULL;
	size_t data_size         = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_value_get_data_size(
	          xml_value,
	          &data_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "data_size",
	 data_size,
	 (size_t) 4 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_xml_value_get_data_size(
	          NULL,
	          &data_size,
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

	result = libfwevt_xml_value_get_data_size(
	          xml_value,
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

/* Tests the libfwevt_xml_value_get_data_as_utf8_string_size function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_value_get_data_as_utf8_string_size(
     libfwevt_xml_value_t *xml_value )
{
	libcerror_error_t *error          = NULL;
	size_t utf8_xml_value_string_size = 0;
	int result                        = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_value_get_data_as_utf8_string_size(
	          xml_value,
	          &utf8_xml_value_string_size,
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
	result = libfwevt_xml_value_get_data_as_utf8_string_size(
	          NULL,
	          &utf8_xml_value_string_size,
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

	result = libfwevt_xml_value_get_data_as_utf8_string_size(
	          xml_value,
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

/* Tests the libfwevt_internal_xml_value_get_data_as_utf8_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_internal_xml_value_get_data_as_utf8_string_with_index(
     libfwevt_xml_value_t *xml_value )
{
	uint8_t utf8_string[ 32 ];

	libcerror_error_t *error = NULL;
	size_t utf8_string_index = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_internal_xml_value_get_data_as_utf8_string_with_index(
	          (libfwevt_internal_xml_value_t *) xml_value,
	          utf8_string,
	          32,
	          &utf8_string_index,
	          0,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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
	result = libfwevt_internal_xml_value_get_data_as_utf8_string_with_index(
	          NULL,
	          utf8_string,
	          32,
	          &utf8_string_index,
	          0,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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

	result = libfwevt_internal_xml_value_get_data_as_utf8_string_with_index(
	          (libfwevt_internal_xml_value_t *) xml_value,
	          NULL,
	          32,
	          &utf8_string_index,
	          0,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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

	result = libfwevt_internal_xml_value_get_data_as_utf8_string_with_index(
	          (libfwevt_internal_xml_value_t *) xml_value,
	          utf8_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf8_string_index,
	          0,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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

	result = libfwevt_internal_xml_value_get_data_as_utf8_string_with_index(
	          (libfwevt_internal_xml_value_t *) xml_value,
	          utf8_string,
	          32,
	          NULL,
	          0,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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

/* Tests the libfwevt_xml_value_get_data_as_utf16_string_size function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_value_get_data_as_utf16_string_size(
     libfwevt_xml_value_t *xml_value )
{
	libcerror_error_t *error           = NULL;
	size_t utf16_xml_value_string_size = 0;
	int result                         = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_value_get_data_as_utf16_string_size(
	          xml_value,
	          &utf16_xml_value_string_size,
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
	result = libfwevt_xml_value_get_data_as_utf16_string_size(
	          NULL,
	          &utf16_xml_value_string_size,
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

	result = libfwevt_xml_value_get_data_as_utf16_string_size(
	          xml_value,
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

/* Tests the libfwevt_internal_xml_value_get_data_as_utf16_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_internal_xml_value_get_data_as_utf16_string_with_index(
     libfwevt_xml_value_t *xml_value )
{
	uint16_t utf16_string[ 32 ];

	libcerror_error_t *error  = NULL;
	size_t utf16_string_index = 0;
	int result                = 0;

	/* Test regular cases
	 */
	result = libfwevt_internal_xml_value_get_data_as_utf16_string_with_index(
	          (libfwevt_internal_xml_value_t *) xml_value,
	          utf16_string,
	          32,
	          &utf16_string_index,
	          0,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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
	result = libfwevt_internal_xml_value_get_data_as_utf16_string_with_index(
	          NULL,
	          utf16_string,
	          32,
	          &utf16_string_index,
	          0,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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

	result = libfwevt_internal_xml_value_get_data_as_utf16_string_with_index(
	          (libfwevt_internal_xml_value_t *) xml_value,
	          NULL,
	          32,
	          &utf16_string_index,
	          0,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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

	result = libfwevt_internal_xml_value_get_data_as_utf16_string_with_index(
	          (libfwevt_internal_xml_value_t *) xml_value,
	          utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_string_index,
	          0,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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

	result = libfwevt_internal_xml_value_get_data_as_utf16_string_with_index(
	          (libfwevt_internal_xml_value_t *) xml_value,
	          utf16_string,
	          32,
	          NULL,
	          0,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
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

/* Helper to exercise UTF-8 and UTF-16 string size & copy for a single xml_value type/data
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_value_check_type_strings(
     uint8_t value_type,
     const uint8_t *data,
     size_t data_size,
     uint8_t escape_characters )
{
	uint8_t utf8_string[ 256 ];
	uint16_t utf16_string[ 256 ];

	libcerror_error_t *error        = NULL;
	libfwevt_xml_value_t *xml_value = NULL;
	size_t string_size              = 0;
	size_t string_index             = 0;
	int data_segment_index          = 0;
	int result                      = 0;

	result = libfwevt_xml_value_initialize( &xml_value, value_type, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

	result = libfwevt_xml_value_append_data_segment( xml_value, data, data_size, &data_segment_index, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

	result = libfwevt_internal_xml_value_get_data_as_utf8_string_size(
	          (libfwevt_internal_xml_value_t *) xml_value, &string_size, escape_characters, LIBUNA_CODEPAGE_WINDOWS_1252, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_IS_NULL( "error", error );

	string_index = 0;
	result = libfwevt_internal_xml_value_get_data_as_utf8_string_with_index(
	          (libfwevt_internal_xml_value_t *) xml_value, utf8_string, 256, &string_index, escape_characters, LIBUNA_CODEPAGE_WINDOWS_1252, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_IS_NULL( "error", error );

	result = libfwevt_internal_xml_value_get_data_as_utf16_string_size(
	          (libfwevt_internal_xml_value_t *) xml_value, &string_size, escape_characters, LIBUNA_CODEPAGE_WINDOWS_1252, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_IS_NULL( "error", error );

	string_index = 0;
	result = libfwevt_internal_xml_value_get_data_as_utf16_string_with_index(
	          (libfwevt_internal_xml_value_t *) xml_value, utf16_string, 256, &string_index, escape_characters, LIBUNA_CODEPAGE_WINDOWS_1252, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_IS_NULL( "error", error );

	result = libfwevt_internal_xml_value_free( (libfwevt_internal_xml_value_t **) &xml_value, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free( &error );
	}
	if( xml_value != NULL )
	{
		libfwevt_internal_xml_value_free( (libfwevt_internal_xml_value_t **) &xml_value, NULL );
	}
	return( 0 );
}

/* Tests libfwevt_xml_value_copy_data, typed integer/filetime getters, public string getters,
 * all value types, and libfwevt_xml_string functions
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_value_comprehensive(
     void )
{
	uint8_t buf[ 64 ];
	uint8_t utf8_str[ 128 ];
	uint16_t utf16_str[ 128 ];
	uint8_t int8_data[ 1 ]        = { 0x2a };
	uint8_t int16_data[ 2 ]       = { 0x39, 0x05 };
	uint8_t int32_data[ 4 ]       = { 0x78, 0x56, 0x34, 0x12 };
	uint8_t int64_data[ 8 ]       = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
	uint8_t bool_false[ 4 ]       = { 0x00, 0x00, 0x00, 0x00 };
	uint8_t bool_true[ 4 ]        = { 0x01, 0x00, 0x00, 0x00 };
	uint8_t float32_data[ 4 ]     = { 0x00, 0x00, 0xc0, 0x3f }; /* 1.5f */
	uint8_t float64_data[ 8 ]     = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x3f }; /* 1.5 */
	uint8_t guid_data[ 16 ]       = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	uint8_t filetime_data[ 8 ]    = { 0x00, 0x80, 0x3e, 0xd5, 0xde, 0xb1, 0x9d, 0x01 };
	uint8_t systemtime_data[ 16 ] = { 0xe6, 0x07, 0x07, 0x00, 0x03, 0x00, 0x06, 0x00, 0x0c, 0x00, 0x18, 0x00, 0x28, 0x00, 0x00, 0x00 };
	uint8_t sid_data[ 12 ]        = { 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x12, 0x00, 0x00, 0x00 }; /* S-1-5-18 */
	uint8_t utf16_esc[ 14 ]       = { 'a', 0, '&', 0, '<', 0, '>', 0, 'b', 0, 0, 0, 0, 0 };
	uint8_t utf16_num[ 8 ]        = { '4', 0, '2', 0, 0, 0, 0, 0 };
	uint8_t utf16_bignum[ 24 ]    = { '9', 0, '9', 0, '9', 0, '9', 0, '9', 0, '9', 0, '9', 0, '9', 0, '9', 0, '9', 0, '9', 0, 0, 0 };
	uint8_t utf16_badnum[ 4 ]     = { 'x', 0, 0, 0 };
	uint8_t utf16_iso[ 62 ]       = {
		'2', 0, '0', 0, '2', 0, '2', 0, '-', 0, '0', 0, '7', 0, '-', 0,
		'0', 0, '6', 0, 'T', 0, '1', 0, '2', 0, ':', 0, '2', 0, '4', 0,
		':', 0, '4', 0, '0', 0, '.', 0, '6', 0, '0', 0, '8', 0, '1', 0,
		'1', 0, '5', 0, '5', 0, '0', 0, '0', 0, 'Z', 0, 0, 0 };
	uint8_t utf16_bom_le[ 10 ]    = { 0xff, 0xfe, 'a', 0, '&', 0, '<', 0, '>', 0 };
	uint8_t utf16_bom_be[ 10 ]    = { 0xfe, 0xff, 0, 'a', 0, '&', 0, '<', 0, '>' };
	uint8_t utf16_surr[ 4 ]       = { 0x00, 0xd8, 0x00, 0x00 };
	uint8_t byte_str[ 5 ]         = { 't', 'e', 's', 't', 0 };

	libcerror_error_t *error        = NULL;
	libfwevt_xml_value_t *xml_value = NULL;
	size_t string_size              = 0;
	size_t string_index             = 0;
	uint64_t val64                  = 0;
	uint32_t val32                  = 0;
	uint8_t val8                    = 0;
	int seg_idx                     = 0;
	int result                      = 0;

	/* Test internal_xml_value_free error and xml_value_free non-NULL
	 */
	result = libfwevt_internal_xml_value_free( NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	xml_value = (libfwevt_xml_value_t *) 0x12345678UL;
	result = libfwevt_xml_value_free( &xml_value, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_IS_NULL( "xml_value", xml_value );

	/* Test append_data_segment error cases
	 */
	result = libfwevt_xml_value_append_data_segment( NULL, int32_data, 4, &seg_idx, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	/* Test copy_data with 2 segments + error cases
	 */
	result = libfwevt_xml_value_initialize( &xml_value, LIBFWEVT_VALUE_TYPE_BINARY_DATA, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_value_append_data_segment( xml_value, (uint8_t *) "ab", 2, &seg_idx, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_value_append_data_segment( xml_value, (uint8_t *) "cd", 2, &seg_idx, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

	result = libfwevt_xml_value_copy_data( xml_value, buf, 4, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "cmp", memory_compare( buf, "abcd", 4 ), 0 );

	result = libfwevt_xml_value_copy_data( NULL, buf, 4, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	result = libfwevt_xml_value_copy_data( xml_value, NULL, 4, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	result = libfwevt_xml_value_copy_data( xml_value, buf, 3, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	result = libfwevt_xml_value_copy_data( xml_value, buf, (size_t) SSIZE_MAX + 1, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	/* Test public UTF-8/UTF-16 string wrappers on xml_value
	 */
	result = libfwevt_xml_value_get_utf8_string_size( xml_value, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_value_copy_to_utf8_string( xml_value, utf8_str, 128, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_value_get_utf8_string_size( NULL, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_xml_value_get_utf8_string_size( xml_value, NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_xml_value_copy_to_utf8_string( NULL, utf8_str, 128, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	result = libfwevt_xml_value_get_utf16_string_size( xml_value, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_value_copy_to_utf16_string( xml_value, utf16_str, 128, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_value_get_utf16_string_size( NULL, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_xml_value_get_utf16_string_size( xml_value, NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_xml_value_copy_to_utf16_string( NULL, utf16_str, 128, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	/* Unsupported type for integer/filetime getters returns 0
	 */
	result = libfwevt_value_get_data_as_8bit_integer( xml_value, &val8, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 0 );
	result = libfwevt_value_get_data_as_32bit_integer( xml_value, &val32, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 0 );
	result = libfwevt_value_get_data_as_64bit_integer( xml_value, &val64, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 0 );
	result = libfwevt_value_get_data_as_filetime( xml_value, &val64, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 0 );

	result = libfwevt_internal_xml_value_free( (libfwevt_internal_xml_value_t **) &xml_value, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

	/* Test integer getters: 8/32/64-bit on numeric and UTF-16 string values + errors
	 */
	result = libfwevt_value_get_data_as_8bit_integer( NULL, &val8, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_value_get_data_as_32bit_integer( NULL, &val32, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_value_get_data_as_64bit_integer( NULL, &val64, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_value_get_data_as_filetime( NULL, &val64, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	result = libfwevt_xml_value_initialize( &xml_value, LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_8BIT, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_value_get_data_as_8bit_integer( xml_value, NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_value_get_data_as_32bit_integer( xml_value, NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_value_get_data_as_64bit_integer( xml_value, NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	/* No data segment yet -> error */
	result = libfwevt_value_get_data_as_8bit_integer( xml_value, &val8, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_value_get_data_as_32bit_integer( xml_value, &val32, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_value_get_data_as_64bit_integer( xml_value, &val64, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_xml_value_append_data_segment( xml_value, int8_data, 1, &seg_idx, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_value_get_data_as_8bit_integer( xml_value, &val8, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_UINT8( "val8", val8, (uint8_t) 0x2a );
	result = libfwevt_value_get_data_as_32bit_integer( xml_value, &val32, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_UINT32( "val32", val32, (uint32_t) 0x2a );
	result = libfwevt_value_get_data_as_64bit_integer( xml_value, &val64, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_UINT64( "val64", val64, (uint64_t) 0x2a );
	result = libfwevt_internal_xml_value_free( (libfwevt_internal_xml_value_t **) &xml_value, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

	/* Integer from UTF-16 string (valid, overflow for 8/32-bit, invalid)
	 */
	result = libfwevt_xml_value_initialize( &xml_value, LIBFWEVT_VALUE_TYPE_STRING_UTF16, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_value_append_data_segment( xml_value, utf16_num, 6, &seg_idx, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_value_get_data_as_8bit_integer( xml_value, &val8, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_UINT8( "val8", val8, (uint8_t) 42 );
	result = libfwevt_value_get_data_as_32bit_integer( xml_value, &val32, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_UINT32( "val32", val32, (uint32_t) 42 );
	result = libfwevt_value_get_data_as_64bit_integer( xml_value, &val64, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_UINT64( "val64", val64, (uint64_t) 42 );
	result = libfwevt_internal_xml_value_free( (libfwevt_internal_xml_value_t **) &xml_value, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

	result = libfwevt_xml_value_initialize( &xml_value, LIBFWEVT_VALUE_TYPE_STRING_UTF16, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_value_append_data_segment( xml_value, utf16_bignum, 24, &seg_idx, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_value_get_data_as_8bit_integer( xml_value, &val8, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_value_get_data_as_32bit_integer( xml_value, &val32, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_internal_xml_value_free( (libfwevt_internal_xml_value_t **) &xml_value, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

	result = libfwevt_xml_value_initialize( &xml_value, LIBFWEVT_VALUE_TYPE_STRING_UTF16, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_value_append_data_segment( xml_value, utf16_badnum, 4, &seg_idx, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_value_get_data_as_8bit_integer( xml_value, &val8, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_value_get_data_as_32bit_integer( xml_value, &val32, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_value_get_data_as_64bit_integer( xml_value, &val64, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_value_get_data_as_filetime( xml_value, &val64, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_internal_xml_value_free( (libfwevt_internal_xml_value_t **) &xml_value, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

	/* Filetime getter: FILETIME binary (8-byte and bad size), UTF-16 ISO8601
	 */
	result = libfwevt_xml_value_initialize( &xml_value, LIBFWEVT_VALUE_TYPE_FILETIME, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_value_get_data_as_filetime( xml_value, NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_value_get_data_as_filetime( xml_value, &val64, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_xml_value_append_data_segment( xml_value, filetime_data, 8, &seg_idx, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_value_get_data_as_filetime( xml_value, &val64, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_internal_xml_value_free( (libfwevt_internal_xml_value_t **) &xml_value, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

	result = libfwevt_xml_value_initialize( &xml_value, LIBFWEVT_VALUE_TYPE_FILETIME, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_value_append_data_segment( xml_value, filetime_data, 4, &seg_idx, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_value_get_data_as_filetime( xml_value, &val64, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_internal_xml_value_free( (libfwevt_internal_xml_value_t **) &xml_value, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

	result = libfwevt_xml_value_initialize( &xml_value, LIBFWEVT_VALUE_TYPE_STRING_UTF16, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_value_append_data_segment( xml_value, utf16_iso, 62, &seg_idx, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_value_get_data_as_filetime( xml_value, &val64, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_internal_xml_value_free( (libfwevt_internal_xml_value_t **) &xml_value, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

	/* Exercise all value types for UTF-8 and UTF-16 string formatting
	 */
	FWEVT_TEST_ASSERT_EQUAL_INT( "utf16_noesc", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_STRING_UTF16, utf16_esc, 12, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "utf16_esc", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_STRING_UTF16, utf16_esc, 12, 1 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "utf16_empty", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_STRING_UTF16, utf16_esc, 0, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "bytestr", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_STRING_BYTE_STREAM, byte_str, 5, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "bytestr_empty", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_STRING_BYTE_STREAM, byte_str, 0, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "int8", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_INTEGER_8BIT, int8_data, 1, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "uint8", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_8BIT, int8_data, 1, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "int16", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_INTEGER_16BIT, int16_data, 2, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "uint16", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_16BIT, int16_data, 2, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "int32", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_INTEGER_32BIT, int32_data, 4, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "uint32", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_32BIT, int32_data, 4, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "int64", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_INTEGER_64BIT, int64_data, 8, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "uint64", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_64BIT, int64_data, 8, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "float32", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_FLOATING_POINT_32BIT, float32_data, 4, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "float64", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_FLOATING_POINT_64BIT, float64_data, 8, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "bool_false", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_BOOLEAN, bool_false, 4, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "bool_true", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_BOOLEAN, bool_true, 4, 0 ), 1 );
	/* Empty binary data: size succeeds (0), copy returns -1
	 */
	result = libfwevt_xml_value_initialize( &xml_value, LIBFWEVT_VALUE_TYPE_BINARY_DATA, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_value_append_data_segment( xml_value, int32_data, 0, &seg_idx, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_value_get_data_as_utf8_string_size( xml_value, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_SIZE( "string_size", string_size, (size_t) 0 );
	result = libfwevt_xml_value_get_data_as_utf16_string_size( xml_value, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_SIZE( "string_size", string_size, (size_t) 0 );
	result = libfwevt_internal_xml_value_free( (libfwevt_internal_xml_value_t **) &xml_value, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "guid", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_GUID, guid_data, 16, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "filetime", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_FILETIME, filetime_data, 8, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "systemtime", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_SYSTEMTIME, systemtime_data, 16, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "sid", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_NT_SECURITY_IDENTIFIER, sid_data, 12, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "hex32", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_HEXADECIMAL_INTEGER_32BIT, int32_data, 4, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "hex64", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_HEXADECIMAL_INTEGER_64BIT, int64_data, 8, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "size4", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_SIZE, int32_data, 4, 0 ), 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "size8", fwevt_test_xml_value_check_type_strings( LIBFWEVT_VALUE_TYPE_SIZE, int64_data, 8, 0 ), 1 );

	/* Test invalid data sizes in get_data_segment_with_cached_value and unsupported type
	 */
	{
		uint8_t bad_types[ 9 ] = {
			LIBFWEVT_VALUE_TYPE_INTEGER_8BIT,
			LIBFWEVT_VALUE_TYPE_INTEGER_16BIT,
			LIBFWEVT_VALUE_TYPE_INTEGER_32BIT,
			LIBFWEVT_VALUE_TYPE_INTEGER_64BIT,
			LIBFWEVT_VALUE_TYPE_GUID,
			LIBFWEVT_VALUE_TYPE_FILETIME,
			LIBFWEVT_VALUE_TYPE_SYSTEMTIME,
			LIBFWEVT_VALUE_TYPE_NT_SECURITY_IDENTIFIER,
			0x7f
		};
		int t_idx = 0;

		for( t_idx = 0; t_idx < 9; t_idx++ )
		{
			result = libfwevt_xml_value_initialize( &xml_value, bad_types[ t_idx ], &error );
			FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
			result = libfwevt_xml_value_append_data_segment( xml_value, int32_data, 3, &seg_idx, &error );
			FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
			result = libfwevt_xml_value_get_data_as_utf8_string_size( xml_value, &string_size, &error );
			FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
			libcerror_error_free( &error );
			result = libfwevt_xml_value_get_data_as_utf16_string_size( xml_value, &string_size, &error );
			FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
			libcerror_error_free( &error );
			result = libfwevt_internal_xml_value_free( (libfwevt_internal_xml_value_t **) &xml_value, &error );
			FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
		}
	}

	/* Test boolean buffer too small for UTF-8 and UTF-16
	 */
	result = libfwevt_xml_value_initialize( &xml_value, LIBFWEVT_VALUE_TYPE_BOOLEAN, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_value_append_data_segment( xml_value, bool_false, 4, &seg_idx, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_value_get_data_as_utf8_string( xml_value, utf8_str, 2, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_xml_value_get_data_as_utf16_string( xml_value, utf16_str, 2, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_internal_xml_value_free( (libfwevt_internal_xml_value_t **) &xml_value, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

	/* Test libfwevt_xml_string functions directly (UTF-8 & UTF-16, BOMs, escapes, unpaired surrogates, errors)
	 */
	result = libfwevt_utf8_xml_string_size_from_utf16_stream( utf16_bom_le, 10, 0, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_utf8_xml_string_size_from_utf16_stream( utf16_bom_be, 10, 0, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_utf8_xml_string_size_from_utf16_stream( utf16_bom_le, 0, 0, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_utf8_xml_string_size_from_utf16_stream( utf16_surr, 4, LIBUNA_ENDIAN_LITTLE | LIBUNA_UTF16_STREAM_ALLOW_UNPAIRED_SURROGATE, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_utf8_xml_string_size_from_utf16_stream( utf16_surr, 4, LIBUNA_ENDIAN_LITTLE, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_utf8_xml_string_size_from_utf16_stream( NULL, 10, 0, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_utf8_xml_string_size_from_utf16_stream( utf16_bom_le, (size_t) SSIZE_MAX + 1, 0, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_utf8_xml_string_size_from_utf16_stream( utf16_bom_le, 9, 0, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_utf8_xml_string_size_from_utf16_stream( utf16_bom_le, 10, 0, NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	string_index = 0;
	result = libfwevt_utf8_xml_string_with_index_copy_from_utf16_stream( utf8_str, 128, &string_index, utf16_bom_le, 10, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	string_index = 0;
	result = libfwevt_utf8_xml_string_with_index_copy_from_utf16_stream( utf8_str, 128, &string_index, utf16_bom_be, 10, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	string_index = 0;
	result = libfwevt_utf8_xml_string_with_index_copy_from_utf16_stream( utf8_str, 128, &string_index, utf16_surr, 4, LIBUNA_ENDIAN_LITTLE | LIBUNA_UTF16_STREAM_ALLOW_UNPAIRED_SURROGATE, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	string_index = 0;
	result = libfwevt_utf8_xml_string_with_index_copy_from_utf16_stream( utf8_str, 128, &string_index, utf16_surr, 4, LIBUNA_ENDIAN_LITTLE, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	/* Buffer too small at &, <, >, and NUL */
	string_index = 0;
	result = libfwevt_utf8_xml_string_with_index_copy_from_utf16_stream( utf8_str, 4, &string_index, utf16_bom_le, 10, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	string_index = 0;
	result = libfwevt_utf8_xml_string_with_index_copy_from_utf16_stream( utf8_str, 8, &string_index, utf16_bom_le, 10, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	string_index = 0;
	result = libfwevt_utf8_xml_string_with_index_copy_from_utf16_stream( utf8_str, 12, &string_index, utf16_bom_le, 10, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	string_index = 0;
	result = libfwevt_utf8_xml_string_with_index_copy_from_utf16_stream( utf8_str, 14, &string_index, utf16_bom_le, 10, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	string_index = 0;
	result = libfwevt_utf8_xml_string_with_index_copy_from_utf16_stream( NULL, 128, &string_index, utf16_bom_le, 10, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_utf8_xml_string_with_index_copy_from_utf16_stream( utf8_str, (size_t) SSIZE_MAX + 1, &string_index, utf16_bom_le, 10, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_utf8_xml_string_with_index_copy_from_utf16_stream( utf8_str, 128, NULL, utf16_bom_le, 10, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_utf8_xml_string_with_index_copy_from_utf16_stream( utf8_str, 128, &string_index, NULL, 10, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_utf8_xml_string_with_index_copy_from_utf16_stream( utf8_str, 128, &string_index, utf16_bom_le, (size_t) SSIZE_MAX + 1, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_utf8_xml_string_with_index_copy_from_utf16_stream( utf8_str, 128, &string_index, utf16_bom_le, 0, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	/* UTF-16 xml_string functions
	 */
	result = libfwevt_utf16_xml_string_size_from_utf16_stream( utf16_bom_le, 10, 0, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_utf16_xml_string_size_from_utf16_stream( utf16_bom_be, 10, 0, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_utf16_xml_string_size_from_utf16_stream( utf16_bom_le, 0, 0, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_utf16_xml_string_size_from_utf16_stream( utf16_surr, 4, LIBUNA_ENDIAN_LITTLE | LIBUNA_UTF16_STREAM_ALLOW_UNPAIRED_SURROGATE, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_utf16_xml_string_size_from_utf16_stream( utf16_surr, 4, LIBUNA_ENDIAN_LITTLE, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_utf16_xml_string_size_from_utf16_stream( NULL, 10, 0, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_utf16_xml_string_size_from_utf16_stream( utf16_bom_le, (size_t) SSIZE_MAX + 1, 0, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_utf16_xml_string_size_from_utf16_stream( utf16_bom_le, 9, 0, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_utf16_xml_string_size_from_utf16_stream( utf16_bom_le, 10, 0, NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	string_index = 0;
	result = libfwevt_utf16_xml_string_with_index_copy_from_utf16_stream( utf16_str, 128, &string_index, utf16_bom_le, 10, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	string_index = 0;
	result = libfwevt_utf16_xml_string_with_index_copy_from_utf16_stream( utf16_str, 128, &string_index, utf16_bom_be, 10, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	string_index = 0;
	result = libfwevt_utf16_xml_string_with_index_copy_from_utf16_stream( utf16_str, 128, &string_index, utf16_surr, 4, LIBUNA_ENDIAN_LITTLE | LIBUNA_UTF16_STREAM_ALLOW_UNPAIRED_SURROGATE, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	string_index = 0;
	result = libfwevt_utf16_xml_string_with_index_copy_from_utf16_stream( utf16_str, 128, &string_index, utf16_surr, 4, LIBUNA_ENDIAN_LITTLE, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	string_index = 0;
	result = libfwevt_utf16_xml_string_with_index_copy_from_utf16_stream( utf16_str, 4, &string_index, utf16_bom_le, 10, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	string_index = 0;
	result = libfwevt_utf16_xml_string_with_index_copy_from_utf16_stream( utf16_str, 8, &string_index, utf16_bom_le, 10, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	string_index = 0;
	result = libfwevt_utf16_xml_string_with_index_copy_from_utf16_stream( utf16_str, 12, &string_index, utf16_bom_le, 10, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	string_index = 0;
	result = libfwevt_utf16_xml_string_with_index_copy_from_utf16_stream( utf16_str, 14, &string_index, utf16_bom_le, 10, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	string_index = 0;
	result = libfwevt_utf16_xml_string_with_index_copy_from_utf16_stream( NULL, 128, &string_index, utf16_bom_le, 10, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_utf16_xml_string_with_index_copy_from_utf16_stream( utf16_str, (size_t) SSIZE_MAX + 1, &string_index, utf16_bom_le, 10, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_utf16_xml_string_with_index_copy_from_utf16_stream( utf16_str, 128, NULL, utf16_bom_le, 10, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_utf16_xml_string_with_index_copy_from_utf16_stream( utf16_str, 128, &string_index, NULL, 10, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_utf16_xml_string_with_index_copy_from_utf16_stream( utf16_str, 128, &string_index, utf16_bom_le, (size_t) SSIZE_MAX + 1, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_utf16_xml_string_with_index_copy_from_utf16_stream( utf16_str, 128, &string_index, utf16_bom_le, 0, 0, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free( &error );
	}
	if( xml_value != NULL )
	{
		libfwevt_internal_xml_value_free( (libfwevt_internal_xml_value_t **) &xml_value, NULL );
	}
	return( 0 );
}

#endif /* #if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

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
#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

	libcerror_error_t *error        = NULL;
	libfwevt_xml_value_t *xml_value = NULL;
	int data_segment_index          = 0;
	int result                      = 0;

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	FWEVT_TEST_UNREFERENCED_PARAMETER( argc )
	FWEVT_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

	FWEVT_TEST_RUN(
	 "libfwevt_xml_value_initialize",
	 fwevt_test_xml_value_initialize );

	FWEVT_TEST_RUN(
	 "libfwevt_xml_value_free",
	 fwevt_test_xml_value_free );

	/* TODO: add tests for libfwevt_internal_xml_value_free */

	/* TODO: add tests for libfwevt_xml_value_append_data_segment */

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize xml_value for tests
	 */
	result = libfwevt_xml_value_initialize(
	          &xml_value,
	          LIBFWEVT_VALUE_TYPE_BINARY_DATA,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_value",
	 xml_value );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_value_append_data_segment(
	          xml_value,
	          (uint8_t *) "data",
	          4,
	          &data_segment_index,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_value_get_type",
	 fwevt_test_xml_value_get_type,
	 xml_value );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_value_get_number_of_data_segments",
	 fwevt_test_xml_value_get_number_of_data_segments,
	 xml_value );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_value_get_data_size",
	 fwevt_test_xml_value_get_data_size,
	 xml_value );

	/* TODO: add tests for libfwevt_xml_value_copy_data */

	/* TODO: add tests for libfwevt_value_get_data_as_8bit_integer */

	/* TODO: add tests for libfwevt_value_get_data_as_32bit_integer */

	/* TODO: add tests for libfwevt_value_get_data_as_64bit_integer */

	/* TODO: add tests for libfwevt_value_get_data_as_filetime */

	/* TODO: add tests for libfwevt_xml_value_get_utf8_string_size_with_index */

	/* TODO: add tests for libfwevt_xml_value_copy_to_utf8_string_with_index */

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_value_get_data_as_utf8_string_size",
	 fwevt_test_xml_value_get_data_as_utf8_string_size,
	 xml_value );

	/* TODO: add tests for libfwevt_xml_value_get_data_as_utf8_string */

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_internal_xml_value_get_data_as_utf8_string_with_index",
	 fwevt_test_internal_xml_value_get_data_as_utf8_string_with_index,
	 xml_value );

	/* TODO: add tests for libfwevt_xml_value_get_utf16_string_size_with_index */

	/* TODO: add tests for libfwevt_xml_value_copy_to_utf16_string_with_index */

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_value_get_data_as_utf16_string_size",
	 fwevt_test_xml_value_get_data_as_utf16_string_size,
	 xml_value );

	/* TODO: add tests for libfwevt_xml_value_get_data_as_utf16_string */

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_internal_xml_value_get_data_as_utf16_string_with_index",
	 fwevt_test_internal_xml_value_get_data_as_utf16_string_with_index,
	 xml_value );

	FWEVT_TEST_RUN(
	 "libfwevt_xml_value_comprehensive",
	 fwevt_test_xml_value_comprehensive );

#if defined( HAVE_DEBUG_OUTPUT )

	/* TODO: add tests for libfwevt_debug_print_xml_value_with_index */

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	/* Clean up
	 */
	result = libfwevt_internal_xml_value_free(
	          (libfwevt_internal_xml_value_t **) &xml_value,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "xml_value",
	 xml_value );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

#endif /* #if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( xml_value != NULL )
	{
		libfwevt_internal_xml_value_free(
		 (libfwevt_internal_xml_value_t **) &xml_value,
		 NULL );
	}
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */
}

