/*
 * Library xml_tag type test program
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

#include "../libfwevt/libfwevt_xml_tag.h"
#include "../libfwevt/libfwevt_xml_value.h"

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

/* Tests the libfwevt_xml_tag_initialize function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfwevt_xml_tag_t *xml_tag     = NULL;
	int result                      = 0;

#if defined( HAVE_FWEVT_TEST_MEMORY )
	int number_of_malloc_fail_tests = 3;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_initialize(
	          &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_tag",
	 xml_tag );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_internal_xml_tag_free(
	          (libfwevt_internal_xml_tag_t **) &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "xml_tag",
	 xml_tag );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_xml_tag_initialize(
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

	xml_tag = (libfwevt_xml_tag_t *) 0x12345678UL;

	result = libfwevt_xml_tag_initialize(
	          &xml_tag,
	          &error );

	xml_tag = NULL;

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
		/* Test libfwevt_xml_tag_initialize with malloc failing
		 */
		fwevt_test_malloc_attempts_before_fail = test_number;

		result = libfwevt_xml_tag_initialize(
		          &xml_tag,
		          &error );

		if( fwevt_test_malloc_attempts_before_fail != -1 )
		{
			fwevt_test_malloc_attempts_before_fail = -1;

			if( xml_tag != NULL )
			{
				libfwevt_internal_xml_tag_free(
				 (libfwevt_internal_xml_tag_t **) &xml_tag,
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
			 "xml_tag",
			 xml_tag );

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
		/* Test libfwevt_xml_tag_initialize with memset failing
		 */
		fwevt_test_memset_attempts_before_fail = test_number;

		result = libfwevt_xml_tag_initialize(
		          &xml_tag,
		          &error );

		if( fwevt_test_memset_attempts_before_fail != -1 )
		{
			fwevt_test_memset_attempts_before_fail = -1;

			if( xml_tag != NULL )
			{
				libfwevt_internal_xml_tag_free(
				 (libfwevt_internal_xml_tag_t **) &xml_tag,
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
			 "xml_tag",
			 xml_tag );

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
	if( xml_tag != NULL )
	{
		libfwevt_internal_xml_tag_free(
		 (libfwevt_internal_xml_tag_t **) &xml_tag,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_tag_free function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfwevt_xml_tag_free(
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

/* Tests the libfwevt_xml_tag_set_type function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_set_type(
     void )
{
	libcerror_error_t *error    = NULL;
	libfwevt_xml_tag_t *xml_tag = NULL;
	int result                  = 0;

	/* Initialize test
	 */
	result = libfwevt_xml_tag_initialize(
	          &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_tag",
	 xml_tag );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_set_type(
	          xml_tag,
	          0,
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
	result = libfwevt_xml_tag_set_type(
	          NULL,
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

	/* Clean up
	 */
	result = libfwevt_internal_xml_tag_free(
	          (libfwevt_internal_xml_tag_t **) &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "xml_tag",
	 xml_tag );

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
	if( xml_tag != NULL )
	{
		libfwevt_internal_xml_tag_free(
		 (libfwevt_internal_xml_tag_t **) &xml_tag,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_tag_set_name_data function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_set_name_data(
     void )
{
	uint8_t name_data[ 10 ]     = { 'n', 0, 'a', 0, 'm', 0, 'e', 0, 0 };
	libcerror_error_t *error    = NULL;
	libfwevt_xml_tag_t *xml_tag = NULL;
	int result                  = 0;

	/* Initialize test
	 */
	result = libfwevt_xml_tag_initialize(
	          &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_tag",
	 xml_tag );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_set_name_data(
	          xml_tag,
	          name_data,
	          10,
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
	result = libfwevt_xml_tag_set_name_data(
	          NULL,
	          name_data,
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

	result = libfwevt_xml_tag_set_name_data(
	          xml_tag,
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

	result = libfwevt_xml_tag_set_name_data(
	          xml_tag,
	          name_data,
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

	/* Clean up
	 */
	result = libfwevt_internal_xml_tag_free(
	          (libfwevt_internal_xml_tag_t **) &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "xml_tag",
	 xml_tag );

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
	if( xml_tag != NULL )
	{
		libfwevt_internal_xml_tag_free(
		 (libfwevt_internal_xml_tag_t **) &xml_tag,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_tag_set_value_type function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_set_value_type(
     void )
{
	libcerror_error_t *error    = NULL;
	libfwevt_xml_tag_t *xml_tag = NULL;
	int result                  = 0;

	/* Initialize test
	 */
	result = libfwevt_xml_tag_initialize(
	          &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_tag",
	 xml_tag );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_set_value_type(
	          xml_tag,
	          LIBFWEVT_VALUE_TYPE_BINARY_DATA,
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
	result = libfwevt_xml_tag_set_value_type(
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

	result = libfwevt_xml_tag_set_value_type(
	          xml_tag,
	          LIBFWEVT_VALUE_TYPE_INTEGER_32BIT,
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

	/* Clean up
	 */
	result = libfwevt_internal_xml_tag_free(
	          (libfwevt_internal_xml_tag_t **) &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "xml_tag",
	 xml_tag );

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
	if( xml_tag != NULL )
	{
		libfwevt_internal_xml_tag_free(
		 (libfwevt_internal_xml_tag_t **) &xml_tag,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_tag_set_value_data function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_set_value_data(
     void )
{
	libcerror_error_t *error    = NULL;
	libfwevt_xml_tag_t *xml_tag = NULL;
	int result                  = 0;

	/* Initialize test
	 */
	result = libfwevt_xml_tag_initialize(
	          &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_tag",
	 xml_tag );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_value_type(
	          xml_tag,
	          LIBFWEVT_VALUE_TYPE_BINARY_DATA,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_set_value_data(
	          xml_tag,
	          (uint8_t *) "data",
	          4,
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
	result = libfwevt_xml_tag_set_value_data(
	          NULL,
	          (uint8_t *) "data",
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

	result = libfwevt_xml_tag_set_value_data(
	          xml_tag,
	          NULL,
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

	result = libfwevt_xml_tag_set_value_data(
	          xml_tag,
	          (uint8_t *) "data",
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

	/* Clean up
	 */
	result = libfwevt_internal_xml_tag_free(
	          (libfwevt_internal_xml_tag_t **) &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "xml_tag",
	 xml_tag );

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
	if( xml_tag != NULL )
	{
		libfwevt_internal_xml_tag_free(
		 (libfwevt_internal_xml_tag_t **) &xml_tag,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_tag_get_utf8_name_size function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_utf8_name_size(
     libfwevt_xml_tag_t *xml_tag )
{
	libcerror_error_t *error = NULL;
	size_t utf8_name_size    = 0;
	int result               = 0;

	/* Test regular cases
	 */
	utf8_name_size = 0;

	result = libfwevt_xml_tag_get_utf8_name_size(
	          xml_tag,
	          &utf8_name_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_name_size",
	 utf8_name_size,
	 (size_t) 5 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	utf8_name_size = 0;

	result = libfwevt_xml_tag_get_utf8_name_size(
	          NULL,
	          &utf8_name_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_name_size",
	 utf8_name_size,
	 (size_t) 0 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_xml_tag_get_utf8_name_size(
	          xml_tag,
	          NULL,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_name_size",
	 utf8_name_size,
	 (size_t) 0 );

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

/* Tests the libfwevt_xml_tag_get_utf8_name function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_utf8_name(
     libfwevt_xml_tag_t *xml_tag )
{
	uint8_t utf8_name[ 32 ];

	uint8_t expected_utf8_name[ 5 ] = { 'n', 'a', 'm', 'e', 0 };
	libcerror_error_t *error        = NULL;
	int result                      = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_get_utf8_name(
	          xml_tag,
	          utf8_name,
	          32,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          expected_utf8_name,
	          utf8_name,
	          5 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libfwevt_xml_tag_get_utf8_name(
	          NULL,
	          utf8_name,
	          32,
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

	result = libfwevt_xml_tag_get_utf8_name(
	          xml_tag,
	          NULL,
	          32,
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

	result = libfwevt_xml_tag_get_utf8_name(
	          xml_tag,
	          utf8_name,
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

	result = libfwevt_xml_tag_get_utf8_name(
	          xml_tag,
	          utf8_name,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_tag_get_utf16_name_size function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_utf16_name_size(
     libfwevt_xml_tag_t *xml_tag )
{
	libcerror_error_t *error = NULL;
	size_t utf16_name_size   = 0;
	int result               = 0;

	/* Test regular cases
	 */
	utf16_name_size = 0;

	result = libfwevt_xml_tag_get_utf16_name_size(
	          xml_tag,
	          &utf16_name_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_name_size",
	 utf16_name_size,
	 (size_t) 5 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	utf16_name_size = 0;

	result = libfwevt_xml_tag_get_utf16_name_size(
	          NULL,
	          &utf16_name_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_name_size",
	 utf16_name_size,
	 (size_t) 0 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_xml_tag_get_utf16_name_size(
	          xml_tag,
	          NULL,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_name_size",
	 utf16_name_size,
	 (size_t) 0 );

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

/* Tests the libfwevt_xml_tag_get_utf16_name function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_utf16_name(
     libfwevt_xml_tag_t *xml_tag )
{
	uint16_t utf16_name[ 32 ];

	uint16_t expected_utf16_name[ 5 ] = { 'n', 'a', 'm', 'e', 0 };
	libcerror_error_t *error          = NULL;
	int result                        = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_get_utf16_name(
	          xml_tag,
	          utf16_name,
	          32,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          expected_utf16_name,
	          utf16_name,
	          (size_t) 5 * sizeof( uint16_t ) );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libfwevt_xml_tag_get_utf16_name(
	          NULL,
	          utf16_name,
	          32,
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

	result = libfwevt_xml_tag_get_utf16_name(
	          xml_tag,
	          NULL,
	          32,
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

	result = libfwevt_xml_tag_get_utf16_name(
	          xml_tag,
	          utf16_name,
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

	result = libfwevt_xml_tag_get_utf16_name(
	          xml_tag,
	          utf16_name,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_tag_get_value function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_value(
     libfwevt_xml_tag_t *xml_tag )
{
	libcerror_error_t *error        = NULL;
	libfwevt_xml_value_t *xml_value = NULL;
	int result                      = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_get_value(
	          xml_tag,
	          &xml_value,
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

	result = libfwevt_xml_value_free(
	          &xml_value,
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
	result = libfwevt_xml_tag_get_value(
	          NULL,
	          &xml_value,
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

	result = libfwevt_xml_tag_get_value(
	          xml_tag,
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
	if( xml_value != NULL )
	{
		libfwevt_internal_xml_value_free(
		 (libfwevt_internal_xml_value_t **) &xml_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_tag_get_utf8_value_size function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_utf8_value_size(
     libfwevt_xml_tag_t *xml_tag )
{
	libcerror_error_t *error = NULL;
	size_t utf8_value_size   = 0;
	int result               = 0;

	/* Test regular cases
	 */
	utf8_value_size = 0;

	result = libfwevt_xml_tag_get_utf8_value_size(
	          xml_tag,
	          &utf8_value_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_value_size",
	 utf8_value_size,
	 (size_t) 9 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	utf8_value_size = 0;

	result = libfwevt_xml_tag_get_utf8_value_size(
	          NULL,
	          &utf8_value_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_value_size",
	 utf8_value_size,
	 (size_t) 0 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_xml_tag_get_utf8_value_size(
	          xml_tag,
	          NULL,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_value_size",
	 utf8_value_size,
	 (size_t) 0 );

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

/* Tests the libfwevt_xml_tag_get_utf8_value function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_utf8_value(
     libfwevt_xml_tag_t *xml_tag )
{
	uint8_t utf8_value[ 32 ];

	uint8_t expected_utf8_value[ 9 ] = { '6', '4', '6', '1', '7', '4', '6', '1', 0 };
	libcerror_error_t *error         = NULL;
	int result                       = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_get_utf8_value(
	          xml_tag,
	          utf8_value,
	          32,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          expected_utf8_value,
	          utf8_value,
	          9 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libfwevt_xml_tag_get_utf8_value(
	          NULL,
	          utf8_value,
	          32,
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

	result = libfwevt_xml_tag_get_utf8_value(
	          xml_tag,
	          NULL,
	          32,
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

	result = libfwevt_xml_tag_get_utf8_value(
	          xml_tag,
	          utf8_value,
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

	result = libfwevt_xml_tag_get_utf8_value(
	          xml_tag,
	          utf8_value,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_tag_get_utf16_value_size function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_utf16_value_size(
     libfwevt_xml_tag_t *xml_tag )
{
	libcerror_error_t *error = NULL;
	size_t utf16_value_size  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	utf16_value_size = 0;

	result = libfwevt_xml_tag_get_utf16_value_size(
	          xml_tag,
	          &utf16_value_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_value_size",
	 utf16_value_size,
	 (size_t) 9 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	utf16_value_size = 0;

	result = libfwevt_xml_tag_get_utf16_value_size(
	          NULL,
	          &utf16_value_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_value_size",
	 utf16_value_size,
	 (size_t) 0 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_xml_tag_get_utf16_value_size(
	          xml_tag,
	          NULL,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_value_size",
	 utf16_value_size,
	 (size_t) 0 );

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

/* Tests the libfwevt_xml_tag_get_utf16_value function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_utf16_value(
     libfwevt_xml_tag_t *xml_tag )
{
	uint16_t utf16_value[ 32 ];

	uint16_t expected_utf16_value[ 9 ] = { '6', '4', '6', '1', '7', '4', '6', '1', 0 };
	libcerror_error_t *error           = NULL;
	int result                         = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_get_utf16_value(
	          xml_tag,
	          utf16_value,
	          32,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          expected_utf16_value,
	          utf16_value,
	          (size_t) 9 * sizeof( uint16_t ) );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libfwevt_xml_tag_get_utf16_value(
	          NULL,
	          utf16_value,
	          32,
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

	result = libfwevt_xml_tag_get_utf16_value(
	          xml_tag,
	          NULL,
	          32,
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

	result = libfwevt_xml_tag_get_utf16_value(
	          xml_tag,
	          utf16_value,
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

	result = libfwevt_xml_tag_get_utf16_value(
	          xml_tag,
	          utf16_value,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_tag_get_number_of_attributes function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_number_of_attributes(
     libfwevt_xml_tag_t *xml_tag )
{
	libcerror_error_t *error = NULL;
	int number_of_attributes = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_get_number_of_attributes(
	          xml_tag,
	          &number_of_attributes,
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
	result = libfwevt_xml_tag_get_number_of_attributes(
	          NULL,
	          &number_of_attributes,
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

	result = libfwevt_xml_tag_get_number_of_attributes(
	          xml_tag,
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

/* Tests the libfwevt_xml_tag_get_attribute_by_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_attribute_by_index(
     libfwevt_xml_tag_t *xml_tag )
{
	libcerror_error_t *error              = NULL;
	libfwevt_xml_tag_t *attribute_xml_tag = NULL;
	int number_of_attributes              = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libfwevt_xml_tag_get_number_of_attributes(
	          xml_tag,
	          &number_of_attributes,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	if( number_of_attributes > 0 )
	{
		result = libfwevt_xml_tag_get_attribute_by_index(
		          xml_tag,
		          0,
		          &attribute_xml_tag,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NOT_NULL(
		 "attribute_xml_tag",
		 attribute_xml_tag );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Clean up
		 */
		result = libfwevt_internal_xml_tag_free(
		          (libfwevt_internal_xml_tag_t **) &attribute_xml_tag,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "attribute_xml_tag",
		 attribute_xml_tag );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libfwevt_xml_tag_get_attribute_by_index(
	          NULL,
	          0,
	          &attribute_xml_tag,
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

	result = libfwevt_xml_tag_get_attribute_by_index(
	          xml_tag,
	          -1,
	          &attribute_xml_tag,
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

	result = libfwevt_xml_tag_get_attribute_by_index(
	          xml_tag,
	          0,
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
	if( attribute_xml_tag != NULL )
	{
		libfwevt_internal_xml_tag_free(
		 (libfwevt_internal_xml_tag_t **) &attribute_xml_tag,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_tag_get_attribute_by_utf8_name function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_attribute_by_utf8_name(
     libfwevt_xml_tag_t *xml_tag )
{
	uint8_t utf8_name[ 5 ]                = { 'T', 'e', 's', 't', 0 };
	libcerror_error_t *error              = NULL;
	libfwevt_xml_tag_t *attribute_xml_tag = NULL;
	int result                            = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_get_attribute_by_utf8_name(
	          xml_tag,
	          utf8_name,
	          4,
	          &attribute_xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "attribute_xml_tag",
	 attribute_xml_tag );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( result != 0 )
	{
		/* Clean up
		 */
		result = libfwevt_internal_xml_tag_free(
		          (libfwevt_internal_xml_tag_t **) &attribute_xml_tag,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "attribute_xml_tag",
		 attribute_xml_tag );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libfwevt_xml_tag_get_attribute_by_utf8_name(
	          NULL,
	          utf8_name,
	          4,
	          &attribute_xml_tag,
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

	result = libfwevt_xml_tag_get_attribute_by_utf8_name(
	          xml_tag,
	          NULL,
	          4,
	          &attribute_xml_tag,
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

	result = libfwevt_xml_tag_get_attribute_by_utf8_name(
	          xml_tag,
	          utf8_name,
	          (size_t) SSIZE_MAX + 1,
	          &attribute_xml_tag,
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

	result = libfwevt_xml_tag_get_attribute_by_utf8_name(
	          xml_tag,
	          utf8_name,
	          4,
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
	if( attribute_xml_tag != NULL )
	{
		libfwevt_internal_xml_tag_free(
		 (libfwevt_internal_xml_tag_t **) &attribute_xml_tag,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_tag_get_attribute_by_utf16_name function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_attribute_by_utf16_name(
     libfwevt_xml_tag_t *xml_tag )
{
	uint16_t utf16_name[ 5 ]              = { 'T', 'e', 's', 't', 0 };
	libcerror_error_t *error              = NULL;
	libfwevt_xml_tag_t *attribute_xml_tag = NULL;
	int result                            = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_get_attribute_by_utf16_name(
	          xml_tag,
	          utf16_name,
	          4,
	          &attribute_xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "attribute_xml_tag",
	 attribute_xml_tag );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( result != 0 )
	{
		/* Clean up
		 */
		result = libfwevt_internal_xml_tag_free(
		          (libfwevt_internal_xml_tag_t **) &attribute_xml_tag,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "attribute_xml_tag",
		 attribute_xml_tag );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libfwevt_xml_tag_get_attribute_by_utf16_name(
	          NULL,
	          utf16_name,
	          4,
	          &attribute_xml_tag,
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

	result = libfwevt_xml_tag_get_attribute_by_utf16_name(
	          xml_tag,
	          NULL,
	          4,
	          &attribute_xml_tag,
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

	result = libfwevt_xml_tag_get_attribute_by_utf16_name(
	          xml_tag,
	          utf16_name,
	          (size_t) SSIZE_MAX + 1,
	          &attribute_xml_tag,
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

	result = libfwevt_xml_tag_get_attribute_by_utf16_name(
	          xml_tag,
	          utf16_name,
	          4,
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
	if( attribute_xml_tag != NULL )
	{
		libfwevt_internal_xml_tag_free(
		 (libfwevt_internal_xml_tag_t **) &attribute_xml_tag,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_tag_get_number_of_elements function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_number_of_elements(
     libfwevt_xml_tag_t *xml_tag )
{
	libcerror_error_t *error = NULL;
	int number_of_elements   = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_get_number_of_elements(
	          xml_tag,
	          &number_of_elements,
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
	result = libfwevt_xml_tag_get_number_of_elements(
	          NULL,
	          &number_of_elements,
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

	result = libfwevt_xml_tag_get_number_of_elements(
	          xml_tag,
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

/* Tests the libfwevt_xml_tag_get_element_by_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_element_by_index(
     libfwevt_xml_tag_t *xml_tag )
{
	libcerror_error_t *error            = NULL;
	libfwevt_xml_tag_t *element_xml_tag = NULL;
	int number_of_elements              = 0;
	int result                          = 0;

	/* Initialize test
	 */
	result = libfwevt_xml_tag_get_number_of_elements(
	          xml_tag,
	          &number_of_elements,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	if( number_of_elements > 0 )
	{
		result = libfwevt_xml_tag_get_element_by_index(
		          xml_tag,
		          0,
		          &element_xml_tag,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NOT_NULL(
		 "element_xml_tag",
		 element_xml_tag );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Clean up
		 */
		result = libfwevt_internal_xml_tag_free(
		          (libfwevt_internal_xml_tag_t **) &element_xml_tag,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "element_xml_tag",
		 element_xml_tag );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libfwevt_xml_tag_get_element_by_index(
	          NULL,
	          0,
	          &element_xml_tag,
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

	result = libfwevt_xml_tag_get_element_by_index(
	          xml_tag,
	          -1,
	          &element_xml_tag,
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

	result = libfwevt_xml_tag_get_element_by_index(
	          xml_tag,
	          0,
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
	if( element_xml_tag != NULL )
	{
		libfwevt_internal_xml_tag_free(
		 (libfwevt_internal_xml_tag_t **) &element_xml_tag,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_tag_get_element_by_utf8_name function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_element_by_utf8_name(
     libfwevt_xml_tag_t *xml_tag )
{
	uint8_t utf8_name[ 5 ]              = { 'T', 'e', 's', 't', 0 };
	libcerror_error_t *error            = NULL;
	libfwevt_xml_tag_t *element_xml_tag = NULL;
	int result                          = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_get_element_by_utf8_name(
	          xml_tag,
	          utf8_name,
	          4,
	          &element_xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "element_xml_tag",
	 element_xml_tag );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( result != 0 )
	{
		/* Clean up
		 */
		result = libfwevt_internal_xml_tag_free(
		          (libfwevt_internal_xml_tag_t **) &element_xml_tag,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "element_xml_tag",
		 element_xml_tag );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libfwevt_xml_tag_get_element_by_utf8_name(
	          NULL,
	          utf8_name,
	          4,
	          &element_xml_tag,
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

	result = libfwevt_xml_tag_get_element_by_utf8_name(
	          xml_tag,
	          NULL,
	          4,
	          &element_xml_tag,
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

	result = libfwevt_xml_tag_get_element_by_utf8_name(
	          xml_tag,
	          utf8_name,
	          (size_t) SSIZE_MAX + 1,
	          &element_xml_tag,
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

	result = libfwevt_xml_tag_get_element_by_utf8_name(
	          xml_tag,
	          utf8_name,
	          4,
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
	if( element_xml_tag != NULL )
	{
		libfwevt_internal_xml_tag_free(
		 (libfwevt_internal_xml_tag_t **) &element_xml_tag,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_tag_get_element_by_utf16_name function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_element_by_utf16_name(
     libfwevt_xml_tag_t *xml_tag )
{
	uint16_t utf16_name[ 5 ]            = { 'T', 'e', 's', 't', 0 };
	libcerror_error_t *error            = NULL;
	libfwevt_xml_tag_t *element_xml_tag = NULL;
	int result                          = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_get_element_by_utf16_name(
	          xml_tag,
	          utf16_name,
	          4,
	          &element_xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "element_xml_tag",
	 element_xml_tag );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( result != 0 )
	{
		/* Clean up
		 */
		result = libfwevt_internal_xml_tag_free(
		          (libfwevt_internal_xml_tag_t **) &element_xml_tag,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "element_xml_tag",
		 element_xml_tag );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libfwevt_xml_tag_get_element_by_utf16_name(
	          NULL,
	          utf16_name,
	          4,
	          &element_xml_tag,
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

	result = libfwevt_xml_tag_get_element_by_utf16_name(
	          xml_tag,
	          NULL,
	          4,
	          &element_xml_tag,
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

	result = libfwevt_xml_tag_get_element_by_utf16_name(
	          xml_tag,
	          utf16_name,
	          (size_t) SSIZE_MAX + 1,
	          &element_xml_tag,
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

	result = libfwevt_xml_tag_get_element_by_utf16_name(
	          xml_tag,
	          utf16_name,
	          4,
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
	if( element_xml_tag != NULL )
	{
		libfwevt_internal_xml_tag_free(
		 (libfwevt_internal_xml_tag_t **) &element_xml_tag,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_tag_get_flags function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_flags(
     libfwevt_xml_tag_t *xml_tag )
{
	libcerror_error_t *error = NULL;
	uint8_t flags            = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_get_flags(
	          xml_tag,
	          &flags,
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
	result = libfwevt_xml_tag_get_flags(
	          NULL,
	          &flags,
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

	result = libfwevt_xml_tag_get_flags(
	          xml_tag,
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

/* Tests the libfwevt_xml_tag_get_utf8_xml_string_size function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_utf8_xml_string_size(
     libfwevt_xml_tag_t *xml_tag )
{
	libcerror_error_t *error    = NULL;
	size_t utf8_xml_string_size = 0;
	int result                  = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_get_utf8_xml_string_size(
	          xml_tag,
	          0,
	          &utf8_xml_string_size,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_xml_string_size",
	 utf8_xml_string_size,
	 (size_t) 23 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_xml_tag_get_utf8_xml_string_size(
	          NULL,
	          0,
	          &utf8_xml_string_size,
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

	result = libfwevt_xml_tag_get_utf8_xml_string_size(
	          xml_tag,
	          0,
	          NULL,
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

/* Tests the libfwevt_xml_tag_get_utf8_xml_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_utf8_xml_string_with_index(
     libfwevt_xml_tag_t *xml_tag )
{
	uint8_t expected_utf8_string[ 23 ] = {
		'<', 'n', 'a', 'm', 'e', '>', '6', '4', '6', '1', '7', '4', '6', '1', '<', '/',
		'n', 'a', 'm', 'e', '>', '\n', 0 };

	uint8_t utf8_string[ 32 ];

	libcerror_error_t *error = NULL;
	size_t utf8_string_index = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_get_utf8_xml_string_with_index(
	          xml_tag,
	          0,
	          utf8_string,
	          32,
	          &utf8_string_index,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_index",
	 utf8_string_index,
	 (size_t) 23 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          expected_utf8_string,
	          utf8_string,
	          23 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	utf8_string_index = 0;

	result = libfwevt_xml_tag_get_utf8_xml_string_with_index(
	          NULL,
	          0,
	          utf8_string,
	          32,
	          &utf8_string_index,
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

	result = libfwevt_xml_tag_get_utf8_xml_string_with_index(
	          xml_tag,
	          0,
	          NULL,
	          32,
	          &utf8_string_index,
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

	result = libfwevt_xml_tag_get_utf8_xml_string_with_index(
	          xml_tag,
	          0,
	          utf8_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf8_string_index,
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

	result = libfwevt_xml_tag_get_utf8_xml_string_with_index(
	          xml_tag,
	          0,
	          utf8_string,
	          32,
	          NULL,
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

/* Tests the libfwevt_xml_tag_get_utf16_xml_string_size function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_utf16_xml_string_size(
     libfwevt_xml_tag_t *xml_tag )
{
	libcerror_error_t *error     = NULL;
	size_t utf16_xml_string_size = 0;
	int result                   = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_get_utf16_xml_string_size(
	          xml_tag,
	          0,
	          &utf16_xml_string_size,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_xml_string_size",
	 utf16_xml_string_size,
	 (size_t) 23 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_xml_tag_get_utf16_xml_string_size(
	          NULL,
	          0,
	          &utf16_xml_string_size,
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

	result = libfwevt_xml_tag_get_utf16_xml_string_size(
	          xml_tag,
	          0,
	          NULL,
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

/* Tests the libfwevt_xml_tag_get_utf16_xml_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_utf16_xml_string_with_index(
     libfwevt_xml_tag_t *xml_tag )
{
	uint16_t expected_utf16_string[ 23 ] = {
		'<', 'n', 'a', 'm', 'e', '>', '6', '4', '6', '1', '7', '4', '6', '1', '<', '/',
		'n', 'a', 'm', 'e', '>', '\n', 0 };

	uint16_t utf16_string[ 32 ];

	libcerror_error_t *error  = NULL;
	size_t utf16_string_index = 0;
	int result                = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_tag_get_utf16_xml_string_with_index(
	          xml_tag,
	          0,
	          utf16_string,
	          32,
	          &utf16_string_index,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 (size_t) 23 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          expected_utf16_string,
	          utf16_string,
	          23 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	utf16_string_index = 0;

	result = libfwevt_xml_tag_get_utf16_xml_string_with_index(
	          NULL,
	          0,
	          utf16_string,
	          32,
	          &utf16_string_index,
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

	result = libfwevt_xml_tag_get_utf16_xml_string_with_index(
	          xml_tag,
	          0,
	          NULL,
	          32,
	          &utf16_string_index,
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

	result = libfwevt_xml_tag_get_utf16_xml_string_with_index(
	          xml_tag,
	          0,
	          utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &utf16_string_index,
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

	result = libfwevt_xml_tag_get_utf16_xml_string_with_index(
	          xml_tag,
	          0,
	          utf16_string,
	          32,
	          NULL,
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

/* Tests the exact UTF-8 and UTF-16 XML string size of a tag with a
 * linefeed or NUL character value and that the string written to a
 * buffer of the reported size is complete
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_get_xml_string_size_linefeed_value(
     void )
{
	uint8_t name_data[ 10 ] = {
		'T', 0, 'e', 0, 's', 0, 't', 0, 0, 0 };

	uint8_t value_data[ 2 ] = { 0 };

	uint16_t expected_utf16_string[ 15 ] = {
		'<', '!', '[', 'C', 'D', 'A', 'T', 'A', '[', '\n', ']', ']', '>', '\n', 0 };

	uint16_t expected_utf16_cdata_nul_string[ 14 ] = {
		'<', '!', '[', 'C', 'D', 'A', 'T', 'A', '[', ']', ']', '>', '\n', 0 };

	uint16_t expected_utf16_pi_string[ 12 ] = {
		'<', '?', 'T', 'e', 's', 't', ' ', '\n', '?', '>', '\n', 0 };

	uint8_t expected_utf8_cdata_string[ 15 ] = {
		'<', '!', '[', 'C', 'D', 'A', 'T', 'A', '[', '\n', ']', ']', '>', '\n', 0 };

	uint8_t expected_utf8_pi_string[ 12 ] = {
		'<', '?', 'T', 'e', 's', 't', ' ', '\n', '?', '>', '\n', 0 };

	uint16_t *utf16_string = NULL;
	uint8_t *utf8_string   = NULL;

	libcerror_error_t *error       = NULL;
	libfwevt_xml_tag_t *xml_tag   = NULL;
	size_t utf16_string_index     = 0;
	size_t utf16_string_size      = 0;
	size_t utf8_string_index      = 0;
	size_t utf8_string_size       = 0;
	int result                    = 0;

	/* A CDATA tag with a value consisting of a single linefeed (0x0a)
	 * The reported string size must exactly cover the written string:
	 * sizeof( "><![CDATA[" ) + sizeof( linefeed ) + sizeof( "]]>" ) +
	 * sizeof( linefeed ) + sizeof( end of string character )
	 * This is a regression test for a heap buffer overflow reported by
	 * clusterfuzz where a too small size was followed by a successful
	 * XML string write into a buffer of that size
	 */
	result = libfwevt_xml_tag_initialize(
	          &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_tag",
	 xml_tag );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_type(
	          xml_tag,
	          LIBFWEVT_XML_TAG_TYPE_CDATA,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_name_data(
	          xml_tag,
	          name_data,
	          (size_t) 10,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_value_type(
	          xml_tag,
	          LIBFWEVT_VALUE_TYPE_STRING_UTF16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	value_data[ 0 ] = '\n';
	value_data[ 1 ] = 0;

	result = libfwevt_xml_tag_set_value_data(
	          xml_tag,
	          value_data,
	          (size_t) 2,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_get_utf16_xml_string_size(
	          xml_tag,
	          (uint32_t) 0,
	          &utf16_string_size,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 15 );

	utf16_string = (uint16_t *) malloc(
	               sizeof( uint16_t ) * utf16_string_size );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "utf16_string",
	 utf16_string );

	utf16_string_index = 0;

	result = libfwevt_xml_tag_get_utf16_xml_string_with_index(
	          xml_tag,
	          (uint32_t) 0,
	          utf16_string,
	          utf16_string_size,
	          &utf16_string_index,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 utf16_string_size );

	result = memory_compare(
	          expected_utf16_string,
	          utf16_string,
	          (size_t) 15 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	free(
	 utf16_string );

	utf16_string = NULL;

	result = libfwevt_internal_xml_tag_free(
	          (libfwevt_internal_xml_tag_t **) &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Same CDATA tag, written as a UTF-8 string
	 */
	result = libfwevt_xml_tag_initialize(
	          &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_tag",
	 xml_tag );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_type(
	          xml_tag,
	          LIBFWEVT_XML_TAG_TYPE_CDATA,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_name_data(
	          xml_tag,
	          name_data,
	          (size_t) 10,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_value_type(
	          xml_tag,
	          LIBFWEVT_VALUE_TYPE_STRING_UTF16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_value_data(
	          xml_tag,
	          value_data,
	          (size_t) 2,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_get_utf8_xml_string_size(
	          xml_tag,
	          (uint32_t) 0,
	          &utf8_string_size,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_size",
	 utf8_string_size,
	 (size_t) 15 );

	utf8_string = (uint8_t *) malloc(
	                utf8_string_size );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "utf8_string",
	 utf8_string );

	utf8_string_index = 0;

	result = libfwevt_xml_tag_get_utf8_xml_string_with_index(
	          xml_tag,
	          (uint32_t) 0,
	          utf8_string,
	          utf8_string_size,
	          &utf8_string_index,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_index",
	 utf8_string_index,
	 utf8_string_size );

	result = memory_compare(
	          expected_utf8_cdata_string,
	          utf8_string,
	          (size_t) 15 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	free(
	 utf8_string );

	utf8_string = NULL;

	result = libfwevt_internal_xml_tag_free(
	          (libfwevt_internal_xml_tag_t **) &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* A PI tag with a value consisting of a single linefeed (0x0a)
	 */
	result = libfwevt_xml_tag_initialize(
	          &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_tag",
	 xml_tag );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_type(
	          xml_tag,
	          LIBFWEVT_XML_TAG_TYPE_PI,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_name_data(
	          xml_tag,
	          name_data,
	          (size_t) 10,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_value_type(
	          xml_tag,
	          LIBFWEVT_VALUE_TYPE_STRING_UTF16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_value_data(
	          xml_tag,
	          value_data,
	          (size_t) 2,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_get_utf16_xml_string_size(
	          xml_tag,
	          (uint32_t) 0,
	          &utf16_string_size,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 12 );

	utf16_string = (uint16_t *) malloc(
	               sizeof( uint16_t ) * utf16_string_size );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "utf16_string",
	 utf16_string );

	utf16_string_index = 0;

	result = libfwevt_xml_tag_get_utf16_xml_string_with_index(
	          xml_tag,
	          (uint32_t) 0,
	          utf16_string,
	          utf16_string_size,
	          &utf16_string_index,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 utf16_string_size );

	result = memory_compare(
	          expected_utf16_pi_string,
	          utf16_string,
	          (size_t) 12 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	free(
	 utf16_string );

	utf16_string = NULL;

	result = libfwevt_internal_xml_tag_free(
	          (libfwevt_internal_xml_tag_t **) &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Same PI tag, written as a UTF-8 string
	 */
	result = libfwevt_xml_tag_initialize(
	          &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_tag",
	 xml_tag );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_type(
	          xml_tag,
	          LIBFWEVT_XML_TAG_TYPE_PI,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_name_data(
	          xml_tag,
	          name_data,
	          (size_t) 10,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_value_type(
	          xml_tag,
	          LIBFWEVT_VALUE_TYPE_STRING_UTF16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_value_data(
	          xml_tag,
	          value_data,
	          (size_t) 2,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_get_utf8_xml_string_size(
	          xml_tag,
	          (uint32_t) 0,
	          &utf8_string_size,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_size",
	 utf8_string_size,
	 (size_t) 12 );

	utf8_string = (uint8_t *) malloc(
	                utf8_string_size );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "utf8_string",
	 utf8_string );

	utf8_string_index = 0;

	result = libfwevt_xml_tag_get_utf8_xml_string_with_index(
	          xml_tag,
	          (uint32_t) 0,
	          utf8_string,
	          utf8_string_size,
	          &utf8_string_index,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_index",
	 utf8_string_index,
	 utf8_string_size );

	result = memory_compare(
	          expected_utf8_pi_string,
	          utf8_string,
	          (size_t) 12 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	free(
	 utf8_string );

	utf8_string = NULL;

	result = libfwevt_internal_xml_tag_free(
	          (libfwevt_internal_xml_tag_t **) &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* A CDATA tag with a value consisting of a single NUL (0x00) character
	 */
	result = libfwevt_xml_tag_initialize(
	          &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_tag",
	 xml_tag );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_type(
	          xml_tag,
	          LIBFWEVT_XML_TAG_TYPE_CDATA,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_name_data(
	          xml_tag,
	          name_data,
	          (size_t) 10,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_value_type(
	          xml_tag,
	          LIBFWEVT_VALUE_TYPE_STRING_UTF16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	value_data[ 0 ] = 0;
	value_data[ 1 ] = 0;

	result = libfwevt_xml_tag_set_value_data(
	          xml_tag,
	          value_data,
	          (size_t) 2,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_get_utf16_xml_string_size(
	          xml_tag,
	          (uint32_t) 0,
	          &utf16_string_size,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 14 );

	utf16_string = (uint16_t *) malloc(
	               sizeof( uint16_t ) * utf16_string_size );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "utf16_string",
	 utf16_string );

	utf16_string_index = 0;

	result = libfwevt_xml_tag_get_utf16_xml_string_with_index(
	          xml_tag,
	          (uint32_t) 0,
	          utf16_string,
	          utf16_string_size,
	          &utf16_string_index,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_index",
	 utf16_string_index,
	 utf16_string_size );

	result = memory_compare(
	          expected_utf16_cdata_nul_string,
	          utf16_string,
	          (size_t) 14 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	free(
	 utf16_string );

	utf16_string = NULL;

	result = libfwevt_internal_xml_tag_free(
	          (libfwevt_internal_xml_tag_t **) &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

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
	if( utf16_string != NULL )
	{
		free(
		 utf16_string );
	}
	if( utf8_string != NULL )
	{
		free(
		 utf8_string );
	}
	if( xml_tag != NULL )
	{
		libfwevt_internal_xml_tag_free(
		 (libfwevt_internal_xml_tag_t **) &xml_tag,
		 NULL );
	}
	return( 0 );
}

/* Tests xml_tag attributes, elements, flags, types (NODE/CDATA/PI), and XML serialization
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_tag_comprehensive(
     void )
{
	uint8_t root_name[ 10 ]   = { 'R', 0, 'o', 0, 'o', 0, 't', 0, 0, 0 };
	uint8_t attr1_name[ 12 ]  = { 'A', 0, 't', 0, 't', 0, 'r', 0, '1', 0, 0, 0 };
	uint8_t attr2_name[ 12 ]  = { 'A', 0, 't', 0, 't', 0, 'r', 0, '2', 0, 0, 0 };
	uint8_t attr_val[ 8 ]     = { 'V', 0, 'a', 0, 'l', 0, 0, 0 };
	uint8_t child1_name[ 14 ] = { 'C', 0, 'h', 0, 'i', 0, 'l', 0, 'd', 0, '1', 0, 0, 0 };
	uint8_t child2_name[ 14 ] = { 'C', 0, 'h', 0, 'i', 0, 'l', 0, 'd', 0, '2', 0, 0, 0 };
	uint8_t grand_name[ 12 ]  = { 'G', 0, 'r', 0, 'a', 0, 'n', 0, 'd', 0, 0, 0 };
	uint8_t pi_name[ 8 ]      = { 'x', 0, 'm', 0, 'l', 0, 0, 0 };
	uint8_t utf16_val[ 8 ]    = { 'H', 0, 'i', 0, '!', 0, 0, 0 };
	uint16_t u16_attr2[ 6 ]   = { 'A', 't', 't', 'r', '2', 0 };
	uint16_t u16_child2[ 7 ]  = { 'C', 'h', 'i', 'l', 'd', '2', 0 };
	uint16_t u16_nope[ 5 ]    = { 'N', 'o', 'p', 'e', 0 };
	uint8_t utf8_buf[ 512 ];
	uint16_t utf16_buf[ 512 ];

	libcerror_error_t *error         = NULL;
	libfwevt_xml_tag_t *root_tag     = NULL;
	libfwevt_xml_tag_t *attr1        = NULL;
	libfwevt_xml_tag_t *attr2        = NULL;
	libfwevt_xml_tag_t *child1       = NULL;
	libfwevt_xml_tag_t *child2       = NULL;
	libfwevt_xml_tag_t *grand        = NULL;
	libfwevt_xml_tag_t *cdata_tag    = NULL;
	libfwevt_xml_tag_t *pi_tag       = NULL;
	libfwevt_xml_tag_t *found_tag    = NULL;
	size_t string_size               = 0;
	size_t string_index              = 0;
	int seg_idx                      = 0;
	int result                       = 0;

	/* Initialize root tag
	 */
	result = libfwevt_xml_tag_initialize( &root_tag, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_name_data( root_tag, root_name, 10, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

	/* Error cases for setters/appenders
	 */
	result = libfwevt_xml_tag_set_name_data( NULL, root_name, 10, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_xml_tag_set_name_data( root_tag, root_name, 10, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_xml_tag_set_flags( NULL, LIBFWEVT_XML_TAG_FLAG_IS_TEMPLATE_DEFINITION, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_xml_tag_set_value_type( NULL, LIBFWEVT_VALUE_TYPE_STRING_UTF16, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_xml_tag_append_value_data( NULL, utf16_val, 8, &seg_idx, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_xml_tag_append_attribute( NULL, NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );
	result = libfwevt_xml_tag_append_element( NULL, NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	/* Add 2 attributes
	 */
	result = libfwevt_xml_tag_initialize( &attr1, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_name_data( attr1, attr1_name, 12, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_value_type( attr1, LIBFWEVT_VALUE_TYPE_STRING_UTF16, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_value_data( attr1, attr_val, 8, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_append_attribute( root_tag, attr1, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	attr1 = NULL;

	result = libfwevt_xml_tag_initialize( &attr2, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_name_data( attr2, attr2_name, 12, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_value_type( attr2, LIBFWEVT_VALUE_TYPE_STRING_UTF16, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_value_data( attr2, attr_val, 8, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_flags( attr2, LIBFWEVT_XML_TAG_FLAG_IS_TEMPLATE_DEFINITION, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_append_attribute( root_tag, attr2, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	attr2 = NULL;

	/* Add child elements: empty node, nested node with value, CDATA, PI
	 */
	result = libfwevt_xml_tag_initialize( &child1, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_name_data( child1, child1_name, 14, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_append_element( root_tag, child1, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	child1 = NULL;

	result = libfwevt_xml_tag_initialize( &child2, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_name_data( child2, child2_name, 14, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_value_type( child2, LIBFWEVT_VALUE_TYPE_STRING_UTF16, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_append_value_data( child2, utf16_val, 8, &seg_idx, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

	result = libfwevt_xml_tag_initialize( &grand, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_name_data( grand, grand_name, 12, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_value_type( grand, LIBFWEVT_VALUE_TYPE_STRING_UTF16, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_value_data( grand, utf16_val, 8, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_flags( grand, LIBFWEVT_XML_TAG_FLAG_IS_TEMPLATE_DEFINITION, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_append_element( child2, grand, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	grand = NULL;

	result = libfwevt_xml_tag_append_element( root_tag, child2, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	child2 = NULL;

	/* Test attribute lookup by index, UTF-8 name, UTF-16 name (match & no-match)
	 */
	found_tag = NULL;
	result = libfwevt_xml_tag_get_attribute_by_index( root_tag, 0, &found_tag, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "found_tag", found_tag );

	found_tag = NULL;
	result = libfwevt_xml_tag_get_attribute_by_utf8_name( root_tag, (uint8_t *) "Attr2", 5, &found_tag, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "found_tag", found_tag );

	found_tag = NULL;
	result = libfwevt_xml_tag_get_attribute_by_utf8_name( root_tag, (uint8_t *) "Nope", 4, &found_tag, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 0 );

	found_tag = NULL;
	result = libfwevt_xml_tag_get_attribute_by_utf16_name( root_tag, u16_attr2, 5, &found_tag, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "found_tag", found_tag );

	found_tag = NULL;
	result = libfwevt_xml_tag_get_attribute_by_utf16_name( root_tag, u16_nope, 4, &found_tag, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 0 );

	/* Test element lookup by index, UTF-8 name, UTF-16 name (match & no-match)
	 */
	found_tag = NULL;
	result = libfwevt_xml_tag_get_element_by_index( root_tag, 1, &found_tag, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "found_tag", found_tag );

	found_tag = NULL;
	result = libfwevt_xml_tag_get_element_by_utf8_name( root_tag, (uint8_t *) "Child2", 6, &found_tag, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "found_tag", found_tag );

	found_tag = NULL;
	result = libfwevt_xml_tag_get_element_by_utf8_name( root_tag, (uint8_t *) "Nope", 4, &found_tag, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 0 );

	found_tag = NULL;
	result = libfwevt_xml_tag_get_element_by_utf16_name( root_tag, u16_child2, 6, &found_tag, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "found_tag", found_tag );

	found_tag = NULL;
	result = libfwevt_xml_tag_get_element_by_utf16_name( root_tag, u16_nope, 4, &found_tag, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 0 );

	result = libfwevt_xml_tag_initialize( &cdata_tag, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_type( cdata_tag, LIBFWEVT_XML_TAG_TYPE_CDATA, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_value_type( cdata_tag, LIBFWEVT_VALUE_TYPE_STRING_UTF16, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_value_data( cdata_tag, utf16_val, 8, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_append_element( root_tag, cdata_tag, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	cdata_tag = NULL;

	result = libfwevt_xml_tag_initialize( &pi_tag, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_type( pi_tag, LIBFWEVT_XML_TAG_TYPE_PI, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_name_data( pi_tag, pi_name, 8, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_value_type( pi_tag, LIBFWEVT_VALUE_TYPE_STRING_UTF16, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_set_value_data( pi_tag, utf16_val, 8, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	result = libfwevt_xml_tag_append_element( root_tag, pi_tag, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	pi_tag = NULL;

	/* Test UTF-8 and UTF-16 XML string formatting of the full tree
	 */
	result = libfwevt_xml_tag_get_utf8_xml_string_size( root_tag, 0, &string_size, LIBUNA_CODEPAGE_WINDOWS_1252, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_IS_NULL( "error", error );

	string_index = 0;
	result = libfwevt_xml_tag_get_utf8_xml_string_with_index( root_tag, 0, utf8_buf, 512, &string_index, LIBUNA_CODEPAGE_WINDOWS_1252, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_SIZE( "string_index", string_index, string_size );
	FWEVT_TEST_ASSERT_IS_NULL( "error", error );

	/* Test buffer too small errors across every incremental size boundary
	 */
	{
		size_t test_sz = 0;

		for( test_sz = 1; test_sz < string_size; test_sz++ )
		{
			string_index = 0;
			result = libfwevt_xml_tag_get_utf8_xml_string_with_index( root_tag, 0, utf8_buf, test_sz, &string_index, LIBUNA_CODEPAGE_WINDOWS_1252, &error );
			FWEVT_TEST_ASSERT_EQUAL_INT( "utf8_small", result, -1 );
			libcerror_error_free( &error );
		}
	}

	result = libfwevt_xml_tag_get_utf16_xml_string_size( root_tag, 0, &string_size, LIBUNA_CODEPAGE_WINDOWS_1252, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_IS_NULL( "error", error );

	string_index = 0;
	result = libfwevt_xml_tag_get_utf16_xml_string_with_index( root_tag, 0, utf16_buf, 512, &string_index, LIBUNA_CODEPAGE_WINDOWS_1252, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_SIZE( "string_index", string_index, string_size );
	FWEVT_TEST_ASSERT_IS_NULL( "error", error );

	{
		size_t test_sz = 0;

		for( test_sz = 1; test_sz < string_size; test_sz++ )
		{
			string_index = 0;
			result = libfwevt_xml_tag_get_utf16_xml_string_with_index( root_tag, 0, utf16_buf, test_sz, &string_index, LIBUNA_CODEPAGE_WINDOWS_1252, &error );
			FWEVT_TEST_ASSERT_EQUAL_INT( "utf16_small", result, -1 );
			libcerror_error_free( &error );
		}
	}

	/* Test tag with empty value and tag with unsupported type
	 */
	{
		libfwevt_xml_tag_t *empty_val_tag = NULL;

		result = libfwevt_xml_tag_initialize( &empty_val_tag, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
		result = libfwevt_xml_tag_set_name_data( empty_val_tag, NULL, 10, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
		libcerror_error_free( &error );
		result = libfwevt_xml_tag_set_name_data( empty_val_tag, root_name, (size_t) SSIZE_MAX + 1, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
		libcerror_error_free( &error );
		result = libfwevt_xml_tag_set_name_data( empty_val_tag, root_name, 10, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
		result = libfwevt_xml_tag_set_value_type( empty_val_tag, LIBFWEVT_VALUE_TYPE_STRING_UTF16, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

		result = libfwevt_xml_tag_get_utf8_xml_string_size( empty_val_tag, 1, &string_size, LIBUNA_CODEPAGE_WINDOWS_1252, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
		string_index = 0;
		result = libfwevt_xml_tag_get_utf8_xml_string_with_index( empty_val_tag, 1, utf8_buf, 512, &string_index, LIBUNA_CODEPAGE_WINDOWS_1252, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
		string_index = 0;
		result = libfwevt_xml_tag_get_utf8_xml_string_with_index( empty_val_tag, 1, utf8_buf, string_size - 2, &string_index, LIBUNA_CODEPAGE_WINDOWS_1252, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
		libcerror_error_free( &error );

		result = libfwevt_xml_tag_get_utf16_xml_string_size( empty_val_tag, 1, &string_size, LIBUNA_CODEPAGE_WINDOWS_1252, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
		string_index = 0;
		result = libfwevt_xml_tag_get_utf16_xml_string_with_index( empty_val_tag, 1, utf16_buf, 512, &string_index, LIBUNA_CODEPAGE_WINDOWS_1252, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
		string_index = 0;
		result = libfwevt_xml_tag_get_utf16_xml_string_with_index( empty_val_tag, 1, utf16_buf, string_size - 2, &string_index, LIBUNA_CODEPAGE_WINDOWS_1252, &error );
		FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
		libcerror_error_free( &error );

		libfwevt_internal_xml_tag_free( (libfwevt_internal_xml_tag_t **) &empty_val_tag, &error );
	}

	result = libfwevt_internal_xml_tag_free( (libfwevt_internal_xml_tag_t **) &root_tag, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free( &error );
	}
	if( pi_tag != NULL )
	{
		libfwevt_internal_xml_tag_free( (libfwevt_internal_xml_tag_t **) &pi_tag, NULL );
	}
	if( cdata_tag != NULL )
	{
		libfwevt_internal_xml_tag_free( (libfwevt_internal_xml_tag_t **) &cdata_tag, NULL );
	}
	if( grand != NULL )
	{
		libfwevt_internal_xml_tag_free( (libfwevt_internal_xml_tag_t **) &grand, NULL );
	}
	if( child2 != NULL )
	{
		libfwevt_internal_xml_tag_free( (libfwevt_internal_xml_tag_t **) &child2, NULL );
	}
	if( child1 != NULL )
	{
		libfwevt_internal_xml_tag_free( (libfwevt_internal_xml_tag_t **) &child1, NULL );
	}
	if( attr2 != NULL )
	{
		libfwevt_internal_xml_tag_free( (libfwevt_internal_xml_tag_t **) &attr2, NULL );
	}
	if( attr1 != NULL )
	{
		libfwevt_internal_xml_tag_free( (libfwevt_internal_xml_tag_t **) &attr1, NULL );
	}
	if( root_tag != NULL )
	{
		libfwevt_internal_xml_tag_free( (libfwevt_internal_xml_tag_t **) &root_tag, NULL );
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

	uint8_t name_data[ 10 ]     = { 'n', 0, 'a', 0, 'm', 0, 'e', 0, 0 };
	libcerror_error_t *error    = NULL;
	libfwevt_xml_tag_t *xml_tag = NULL;
	int result                  = 0;

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	FWEVT_TEST_UNREFERENCED_PARAMETER( argc )
	FWEVT_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

	FWEVT_TEST_RUN(
	 "libfwevt_xml_tag_initialize",
	 fwevt_test_xml_tag_initialize );

	FWEVT_TEST_RUN(
	 "libfwevt_xml_tag_free",
	 fwevt_test_xml_tag_free );

	/* TODO: add tests for libfwevt_internal_xml_tag_free */

	FWEVT_TEST_RUN(
	 "libfwevt_xml_tag_set_type",
	 fwevt_test_xml_tag_set_type );

	FWEVT_TEST_RUN(
	 "libfwevt_xml_tag_set_name_data",
	 fwevt_test_xml_tag_set_name_data );

	FWEVT_TEST_RUN(
	 "libfwevt_xml_tag_set_value_type",
	 fwevt_test_xml_tag_set_value_type );

	FWEVT_TEST_RUN(
	 "libfwevt_xml_tag_set_value_data",
	 fwevt_test_xml_tag_set_value_data );

	/* TODO: add tests for libfwevt_xml_tag_append_value_data */

	/* TODO: add tests for libfwevt_xml_tag_append_attribute */

	/* TODO: add tests for libfwevt_xml_tag_append_element */

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize xml_tag for tests
	 */
	result = libfwevt_xml_tag_initialize(
	          &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_tag",
	 xml_tag );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_name_data(
	          xml_tag,
	          name_data,
	          10,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_value_type(
	          xml_tag,
	          LIBFWEVT_VALUE_TYPE_BINARY_DATA,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_tag_set_value_data(
	          xml_tag,
	          (uint8_t *) "data",
	          4,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_utf8_name_size",
	 fwevt_test_xml_tag_get_utf8_name_size,
	 xml_tag );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_utf8_name",
	 fwevt_test_xml_tag_get_utf8_name,
	 xml_tag );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_utf16_name_size",
	 fwevt_test_xml_tag_get_utf16_name_size,
	 xml_tag );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_utf16_name",
	 fwevt_test_xml_tag_get_utf16_name,
	 xml_tag );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_value",
	 fwevt_test_xml_tag_get_value,
	 xml_tag );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_utf8_value_size",
	 fwevt_test_xml_tag_get_utf8_value_size,
	 xml_tag );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_utf8_value",
	 fwevt_test_xml_tag_get_utf8_value,
	 xml_tag );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_utf16_value_size",
	 fwevt_test_xml_tag_get_utf16_value_size,
	 xml_tag );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_utf16_value",
	 fwevt_test_xml_tag_get_utf16_value,
	 xml_tag );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_number_of_attributes",
	 fwevt_test_xml_tag_get_number_of_attributes,
	 xml_tag );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_attribute_by_index",
	 fwevt_test_xml_tag_get_attribute_by_index,
	 xml_tag );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_attribute_by_utf8_name",
	 fwevt_test_xml_tag_get_attribute_by_utf8_name,
	 xml_tag );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_attribute_by_utf16_name",
	 fwevt_test_xml_tag_get_attribute_by_utf16_name,
	 xml_tag );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_number_of_elements",
	 fwevt_test_xml_tag_get_number_of_elements,
	 xml_tag );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_element_by_index",
	 fwevt_test_xml_tag_get_element_by_index,
	 xml_tag );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_element_by_utf8_name",
	 fwevt_test_xml_tag_get_element_by_utf8_name,
	 xml_tag );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_element_by_utf16_name",
	 fwevt_test_xml_tag_get_element_by_utf16_name,
	 xml_tag );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_flags",
	 fwevt_test_xml_tag_get_flags,
	 xml_tag );

	/* TODO: add tests for libfwevt_xml_tag_set_flags */

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_utf8_xml_string_size",
	 fwevt_test_xml_tag_get_utf8_xml_string_size,
	 xml_tag );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_utf8_xml_string_with_index",
	 fwevt_test_xml_tag_get_utf8_xml_string_with_index,
	 xml_tag );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_utf16_xml_string_size",
	 fwevt_test_xml_tag_get_utf16_xml_string_size,
	 xml_tag );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_tag_get_utf16_xml_string_with_index",
	 fwevt_test_xml_tag_get_utf16_xml_string_with_index,
	 xml_tag );

	FWEVT_TEST_RUN(
	 "libfwevt_xml_tag_get_xml_string_size_linefeed_value",
	 fwevt_test_xml_tag_get_xml_string_size_linefeed_value );

	FWEVT_TEST_RUN(
	 "libfwevt_xml_tag_comprehensive",
	 fwevt_test_xml_tag_comprehensive );

#if defined( HAVE_DEBUG_OUTPUT )

	/* TODO: add tests for libfwevt_xml_tag_debug_print_value_string */

	/* TODO: add tests for libfwevt_xml_tag_debug_print */

	/* TODO: add tests for libfwevt_xml_tag_name_debug_print */

	/* TODO: add tests for libfwevt_xml_tag_value_debug_print */

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	/* Clean up
	 */
	result = libfwevt_internal_xml_tag_free(
	          (libfwevt_internal_xml_tag_t **) &xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "xml_tag",
	 xml_tag );

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
	if( xml_tag != NULL )
	{
		libfwevt_internal_xml_tag_free(
		 (libfwevt_internal_xml_tag_t **) &xml_tag,
		 NULL );
	}
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */
}

