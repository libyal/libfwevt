/*
 * Library xml_value type test program
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
	          LIBFVALUE_VALUE_TYPE_BINARY_DATA,
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
	          LIBFVALUE_VALUE_TYPE_BINARY_DATA,
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
	          LIBFVALUE_VALUE_TYPE_BINARY_DATA,
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
		          LIBFVALUE_VALUE_TYPE_BINARY_DATA,
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
		          LIBFVALUE_VALUE_TYPE_BINARY_DATA,
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
	int type                 = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_value_get_type(
	          xml_value,
	          &type,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "type",
	 type,
	 LIBFVALUE_VALUE_TYPE_BINARY_DATA );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_xml_value_get_type(
	          NULL,
	          &type,
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

/* Tests the libfwevt_xml_value_get_number_of_value_entries function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_value_get_number_of_value_entries(
     libfwevt_xml_value_t *xml_value )
{
	libcerror_error_t *error    = NULL;
	int number_of_value_entries = 0;
	int result                  = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_value_get_number_of_value_entries(
	          xml_value,
	          &number_of_value_entries,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "number_of_value_entries",
	 number_of_value_entries,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_xml_value_get_number_of_value_entries(
	          NULL,
	          &number_of_value_entries,
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

	result = libfwevt_xml_value_get_number_of_value_entries(
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

	/* TODO: add tests for libfwevt_xml_value_set_format_flags */

	/* TODO: add tests for libfwevt_xml_value_append_data */

	/* TODO: add tests for libfwevt_xml_value_type_set_data_string */

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize xml_value for tests
	 */
	result = libfwevt_xml_value_initialize(
	          &xml_value,
	          LIBFVALUE_VALUE_TYPE_BINARY_DATA,
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

	result = libfwevt_xml_value_set_data(
	          xml_value,
	          (uint8_t *) "data",
	          4,
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

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_value_get_type",
	 fwevt_test_xml_value_get_type,
	 xml_value );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_value_get_number_of_value_entries",
	 fwevt_test_xml_value_get_number_of_value_entries,
	 xml_value );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_value_get_data_size",
	 fwevt_test_xml_value_get_data_size,
	 xml_value );

	/* TODO: add tests for libfwevt_xml_value_copy_data */

	/* TODO: add tests for libfwevt_xml_value_copy_to_8bit */

	/* TODO: add tests for libfwevt_xml_value_copy_to_32bit */

	/* TODO: add tests for libfwevt_xml_value_copy_to_64bit */

	/* TODO: add tests for libfwevt_xml_value_get_utf8_string_size_with_index */

	/* TODO: add tests for libfwevt_xml_value_copy_to_utf8_string_with_index */

	/* TODO: add tests for libfwevt_xml_value_get_utf8_string_size */

	/* TODO: add tests for libfwevt_xml_value_copy_to_utf8_string */

	/* TODO: add tests for libfwevt_xml_value_get_utf16_string_size_with_index */

	/* TODO: add tests for libfwevt_xml_value_copy_to_utf16_string_with_index */

	/* TODO: add tests for libfwevt_xml_value_get_utf16_string_size */

	/* TODO: add tests for libfwevt_xml_value_copy_to_utf16_string */

#if defined( HAVE_DEBUG_OUTPUT )

	/* TODO: add tests for libfwevt_debug_print_xml_value */

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

