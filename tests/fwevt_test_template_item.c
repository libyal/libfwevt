/*
 * Library template_item type test program
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fwevt_test_libcerror.h"
#include "fwevt_test_libfwevt.h"
#include "fwevt_test_macros.h"
#include "fwevt_test_memory.h"
#include "fwevt_test_unused.h"

#include "../libfwevt/libfwevt_template_item.h"

uint8_t fwevt_test_template_item_data1[ 36 ] = {
	0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00,
	0x14, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x6e, 0x00, 0x61, 0x00, 0x6d, 0x00, 0x65, 0x00,
	0x00, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

/* Tests the libfwevt_template_item_initialize function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_template_item_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfwevt_template_item_t *template_item         = NULL;
	int result                      = 0;

#if defined( HAVE_FWEVT_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libfwevt_template_item_initialize(
	          &template_item,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "template_item",
	 template_item );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_internal_template_item_free(
	          (libfwevt_internal_template_item_t **) &template_item,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "template_item",
	 template_item );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_template_item_initialize(
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

	template_item = (libfwevt_template_item_t *) 0x12345678UL;

	result = libfwevt_template_item_initialize(
	          &template_item,
	          &error );

	template_item = NULL;

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
		/* Test libfwevt_template_item_initialize with malloc failing
		 */
		fwevt_test_malloc_attempts_before_fail = test_number;

		result = libfwevt_template_item_initialize(
		          &template_item,
		          &error );

		if( fwevt_test_malloc_attempts_before_fail != -1 )
		{
			fwevt_test_malloc_attempts_before_fail = -1;

			if( template_item != NULL )
			{
				libfwevt_internal_template_item_free(
				 (libfwevt_internal_template_item_t **) &template_item,
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
			 "template_item",
			 template_item );

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
		/* Test libfwevt_template_item_initialize with memset failing
		 */
		fwevt_test_memset_attempts_before_fail = test_number;

		result = libfwevt_template_item_initialize(
		          &template_item,
		          &error );

		if( fwevt_test_memset_attempts_before_fail != -1 )
		{
			fwevt_test_memset_attempts_before_fail = -1;

			if( template_item != NULL )
			{
				libfwevt_internal_template_item_free(
				 (libfwevt_internal_template_item_t **) &template_item,
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
			 "template_item",
			 template_item );

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
	if( template_item != NULL )
	{
		libfwevt_internal_template_item_free(
		 (libfwevt_internal_template_item_t **) &template_item,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

/* Tests the libfwevt_template_item_free function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_template_item_free(
     void )
{
	libcerror_error_t *error = NULL;
	libfwevt_template_item_t *template_item  = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	template_item = (libfwevt_template_item_t *) 0x12345678UL;

	result = libfwevt_template_item_free(
	          &template_item,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "template_item",
	 template_item );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_template_item_free(
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

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

/* Tests the libfwevt_internal_template_item_free function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_internal_template_item_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfwevt_internal_template_item_free(
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

/* Tests the libfwevt_template_item_read_data function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_template_item_read_data(
     void )
{
	uint8_t invalid_name_size_data[ 24 ] = {
		0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00,
		0x14, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00 };
	libcerror_error_t *error                = NULL;
	libfwevt_template_item_t *template_item = NULL;
	int result                              = 0;

	/* Initialize test
	 */
	result = libfwevt_template_item_initialize(
	          &template_item,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	/* Test regular cases
	 */
	result = libfwevt_template_item_read_data(
	          template_item,
	          fwevt_test_template_item_data1,
	          36,
	          0,
	          0,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error case where name is already set
	 */
	result = libfwevt_template_item_read_data(
	          template_item,
	          fwevt_test_template_item_data1,
	          36,
	          0,
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

	result = libfwevt_internal_template_item_free(
	          (libfwevt_internal_template_item_t **) &template_item,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libfwevt_template_item_initialize(
	          &template_item,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	/* Test error cases
	 */
	result = libfwevt_template_item_read_data(
	          NULL,
	          fwevt_test_template_item_data1,
	          36,
	          0,
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

	result = libfwevt_template_item_read_data(
	          template_item,
	          NULL,
	          36,
	          0,
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

	result = libfwevt_template_item_read_data(
	          template_item,
	          fwevt_test_template_item_data1,
	          (size_t) SSIZE_MAX + 1,
	          0,
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

	result = libfwevt_template_item_read_data(
	          template_item,
	          fwevt_test_template_item_data1,
	          36,
	          36,
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

	result = libfwevt_template_item_read_data(
	          template_item,
	          fwevt_test_template_item_data1,
	          19,
	          0,
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

	/* Test name_offset < template_data_offset
	 */
	result = libfwevt_template_item_read_data(
	          template_item,
	          fwevt_test_template_item_data1,
	          36,
	          0,
	          0x20,
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

	/* Test name_offset >= data_size - 4
	 */
	result = libfwevt_template_item_read_data(
	          template_item,
	          fwevt_test_template_item_data1,
	          24,
	          0,
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

	/* Test name_size out of bounds
	 */
	result = libfwevt_template_item_read_data(
	          template_item,
	          fwevt_test_template_item_data1,
	          35,
	          0,
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

	/* Test name_size == 4 (zero after header)
	 */
	result = libfwevt_template_item_read_data(
	          template_item,
	          invalid_name_size_data,
	          24,
	          0,
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

#if defined( HAVE_FWEVT_TEST_MEMORY )
	fwevt_test_malloc_attempts_before_fail = 0;

	result = libfwevt_template_item_read_data(
	          template_item,
	          fwevt_test_template_item_data1,
	          36,
	          0,
	          0,
	          &error );

	if( fwevt_test_malloc_attempts_before_fail != -1 )
	{
		fwevt_test_malloc_attempts_before_fail = -1;
	}
	else
	{
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
#if defined( OPTIMIZATION_DISABLED )
	fwevt_test_memcpy_attempts_before_fail = 0;

	result = libfwevt_template_item_read_data(
	          template_item,
	          fwevt_test_template_item_data1,
	          36,
	          0,
	          0,
	          &error );

	if( fwevt_test_memcpy_attempts_before_fail != -1 )
	{
		fwevt_test_memcpy_attempts_before_fail = -1;
	}
	else
	{
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
#endif
#endif

	result = libfwevt_internal_template_item_free(
	          (libfwevt_internal_template_item_t **) &template_item,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( template_item != NULL )
	{
		libfwevt_internal_template_item_free(
		 (libfwevt_internal_template_item_t **) &template_item,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_template_item getter functions
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_template_item_getters(
     void )
{
	uint8_t utf8_string[ 32 ];
	uint16_t utf16_string[ 32 ];

	libcerror_error_t *error                = NULL;
	libfwevt_template_item_t *empty_item    = NULL;
	libfwevt_template_item_t *template_item = NULL;
	size_t string_size                      = 0;
	uint16_t number_of_values               = 0;
	uint16_t value_data_size                = 0;
	uint8_t input_data_type                 = 0;
	uint8_t output_data_type                = 0;
	int result                              = 0;

	result = libfwevt_template_item_initialize(
	          &template_item,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libfwevt_template_item_read_data(
	          template_item,
	          fwevt_test_template_item_data1,
	          36,
	          0,
	          0,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libfwevt_template_item_initialize(
	          &empty_item,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	/* Test input_data_type
	 */
	result = libfwevt_template_item_get_input_data_type(
	          template_item,
	          &input_data_type,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_UINT8( "input_data_type", input_data_type, 1 );

	result = libfwevt_template_item_get_input_data_type( NULL, &input_data_type, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	result = libfwevt_template_item_get_input_data_type( template_item, NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	/* Test output_data_type
	 */
	result = libfwevt_template_item_get_output_data_type(
	          template_item,
	          &output_data_type,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_UINT8( "output_data_type", output_data_type, 1 );

	result = libfwevt_template_item_get_output_data_type( NULL, &output_data_type, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	result = libfwevt_template_item_get_output_data_type( template_item, NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	/* Test number_of_values
	 */
	result = libfwevt_template_item_get_number_of_values(
	          template_item,
	          &number_of_values,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_UINT16( "number_of_values", number_of_values, 1 );

	result = libfwevt_template_item_get_number_of_values( NULL, &number_of_values, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	result = libfwevt_template_item_get_number_of_values( template_item, NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	/* Test value_data_size
	 */
	result = libfwevt_template_item_get_value_data_size(
	          template_item,
	          &value_data_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_UINT16( "value_data_size", value_data_size, 4 );

	result = libfwevt_template_item_get_value_data_size( NULL, &value_data_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	result = libfwevt_template_item_get_value_data_size( template_item, NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	/* Test UTF-8 name size and name
	 */
	result = libfwevt_template_item_get_utf8_name_size( template_item, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_SIZE( "string_size", string_size, (size_t) 5 );

	result = libfwevt_template_item_get_utf8_name_size( empty_item, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 0 );

	result = libfwevt_template_item_get_utf8_name_size( NULL, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	result = libfwevt_template_item_get_utf8_name_size( template_item, NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	result = libfwevt_template_item_get_utf8_name( template_item, utf8_string, 32, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

	result = libfwevt_template_item_get_utf8_name( empty_item, utf8_string, 32, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 0 );

	result = libfwevt_template_item_get_utf8_name( NULL, utf8_string, 32, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	result = libfwevt_template_item_get_utf8_name( template_item, NULL, 32, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	/* Test UTF-16 name size and name
	 */
	result = libfwevt_template_item_get_utf16_name_size( template_item, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_SIZE( "string_size", string_size, (size_t) 5 );

	result = libfwevt_template_item_get_utf16_name_size( empty_item, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 0 );

	result = libfwevt_template_item_get_utf16_name_size( NULL, &string_size, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	result = libfwevt_template_item_get_utf16_name_size( template_item, NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	result = libfwevt_template_item_get_utf16_name( template_item, utf16_string, 32, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

	result = libfwevt_template_item_get_utf16_name( empty_item, utf16_string, 32, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 0 );

	result = libfwevt_template_item_get_utf16_name( NULL, utf16_string, 32, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	result = libfwevt_template_item_get_utf16_name( template_item, NULL, 32, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	libcerror_error_free( &error );

	result = libfwevt_internal_template_item_free(
	          (libfwevt_internal_template_item_t **) &empty_item,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

	result = libfwevt_internal_template_item_free(
	          (libfwevt_internal_template_item_t **) &template_item,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( empty_item != NULL )
	{
		libfwevt_internal_template_item_free(
		 (libfwevt_internal_template_item_t **) &empty_item,
		 NULL );
	}
	if( template_item != NULL )
	{
		libfwevt_internal_template_item_free(
		 (libfwevt_internal_template_item_t **) &template_item,
		 NULL );
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
	 "libfwevt_template_item_initialize",
	 fwevt_test_template_item_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	FWEVT_TEST_RUN(
	 "libfwevt_template_item_free",
	 fwevt_test_template_item_free );

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

	FWEVT_TEST_RUN(
	 "libfwevt_internal_template_item_free",
	 fwevt_test_internal_template_item_free );

	FWEVT_TEST_RUN(
	 "libfwevt_template_item_read_data",
	 fwevt_test_template_item_read_data );

	FWEVT_TEST_RUN(
	 "libfwevt_template_item_getters",
	 fwevt_test_template_item_getters );

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

