/*
 * Library xml_template_value type test program
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fwevt_test_libcerror.h"
#include "fwevt_test_libfwevt.h"
#include "fwevt_test_macros.h"
#include "fwevt_test_memory.h"
#include "fwevt_test_unused.h"

#include "../libfwevt/libfwevt_xml_template_value.h"

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

/* Tests the libfwevt_xml_template_value_initialize function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_template_value_initialize(
     void )
{
	libcerror_error_t *error                          = NULL;
	libfwevt_xml_template_value_t *xml_template_value = NULL;
	int result                                        = 0;

#if defined( HAVE_FWEVT_TEST_MEMORY )
	int number_of_malloc_fail_tests                   = 1;
	int number_of_memset_fail_tests                   = 1;
	int test_number                                   = 0;
#endif

	/* Test regular cases
	 */
	result = libfwevt_xml_template_value_initialize(
	          &xml_template_value,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_template_value",
	 xml_template_value );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_template_value_free(
	          &xml_template_value,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "xml_template_value",
	 xml_template_value );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_xml_template_value_initialize(
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

	xml_template_value = (libfwevt_xml_template_value_t *) 0x12345678UL;

	result = libfwevt_xml_template_value_initialize(
	          &xml_template_value,
	          &error );

	xml_template_value = NULL;

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
		/* Test libfwevt_xml_template_value_initialize with malloc failing
		 */
		fwevt_test_malloc_attempts_before_fail = test_number;

		result = libfwevt_xml_template_value_initialize(
		          &xml_template_value,
		          &error );

		if( fwevt_test_malloc_attempts_before_fail != -1 )
		{
			fwevt_test_malloc_attempts_before_fail = -1;

			if( xml_template_value != NULL )
			{
				libfwevt_xml_template_value_free(
				 &xml_template_value,
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
			 "xml_template_value",
			 xml_template_value );

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
		/* Test libfwevt_xml_template_value_initialize with memset failing
		 */
		fwevt_test_memset_attempts_before_fail = test_number;

		result = libfwevt_xml_template_value_initialize(
		          &xml_template_value,
		          &error );

		if( fwevt_test_memset_attempts_before_fail != -1 )
		{
			fwevt_test_memset_attempts_before_fail = -1;

			if( xml_template_value != NULL )
			{
				libfwevt_xml_template_value_free(
				 &xml_template_value,
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
			 "xml_template_value",
			 xml_template_value );

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
	if( xml_template_value != NULL )
	{
		libfwevt_xml_template_value_free(
		 &xml_template_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_template_value_free function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_template_value_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfwevt_xml_template_value_free(
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

/* Tests the libfwevt_xml_template_value_get_type function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_template_value_get_type(
     libfwevt_xml_template_value_t *xml_template_value )
{
	libcerror_error_t *error = NULL;
	uint8_t type             = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_template_value_get_type(
	          xml_template_value,
	          &type,
	          &error );

	FWEVT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_xml_template_value_get_type(
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

	result = libfwevt_xml_template_value_get_type(
	          xml_template_value,
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

/* Tests the libfwevt_xml_template_value_set_type function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_template_value_set_type(
     void )
{
	libcerror_error_t *error                          = NULL;
	libfwevt_xml_template_value_t *xml_template_value = NULL;
	int result                                        = 0;

	/* Initialize test
	 */
	result = libfwevt_xml_template_value_initialize(
	          &xml_template_value,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_template_value",
	 xml_template_value );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_xml_template_value_set_type(
	          xml_template_value,
	          0x01,
	          &error );

	FWEVT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_xml_template_value_set_type(
	          NULL,
	          0x01,
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
	result = libfwevt_xml_template_value_free(
	          &xml_template_value,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "xml_template_value",
	 xml_template_value );

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
	if( xml_template_value != NULL )
	{
		libfwevt_xml_template_value_free(
		 &xml_template_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_template_value_get_offset function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_template_value_get_offset(
     libfwevt_xml_template_value_t *xml_template_value )
{
	libcerror_error_t *error = NULL;
	size_t offset            = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_template_value_get_offset(
	          xml_template_value,
	          &offset,
	          &error );

	FWEVT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_xml_template_value_get_offset(
	          NULL,
	          &offset,
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

	result = libfwevt_xml_template_value_get_offset(
	          xml_template_value,
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

/* Tests the libfwevt_xml_template_value_set_offset function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_template_value_set_offset(
     void )
{
	libcerror_error_t *error                          = NULL;
	libfwevt_xml_template_value_t *xml_template_value = NULL;
	int result                                        = 0;

	/* Initialize test
	 */
	result = libfwevt_xml_template_value_initialize(
	          &xml_template_value,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_template_value",
	 xml_template_value );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_xml_template_value_set_offset(
	          xml_template_value,
	          0,
	          &error );

	FWEVT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_xml_template_value_set_offset(
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
	result = libfwevt_xml_template_value_free(
	          &xml_template_value,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "xml_template_value",
	 xml_template_value );

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
	if( xml_template_value != NULL )
	{
		libfwevt_xml_template_value_free(
		 &xml_template_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_template_value_get_size function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_template_value_get_size(
     libfwevt_xml_template_value_t *xml_template_value )
{
	libcerror_error_t *error = NULL;
	uint16_t size            = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_template_value_get_size(
	          xml_template_value,
	          &size,
	          &error );

	FWEVT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_xml_template_value_get_size(
	          NULL,
	          &size,
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

	result = libfwevt_xml_template_value_get_size(
	          xml_template_value,
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

/* Tests the libfwevt_xml_template_value_set_size function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_template_value_set_size(
     void )
{
	libcerror_error_t *error                          = NULL;
	libfwevt_xml_template_value_t *xml_template_value = NULL;
	int result                                        = 0;

	/* Initialize test
	 */
	result = libfwevt_xml_template_value_initialize(
	          &xml_template_value,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_template_value",
	 xml_template_value );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_xml_template_value_set_size(
	          xml_template_value,
	          0,
	          &error );

	FWEVT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_xml_template_value_set_size(
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
	result = libfwevt_xml_template_value_free(
	          &xml_template_value,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "xml_template_value",
	 xml_template_value );

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
	if( xml_template_value != NULL )
	{
		libfwevt_xml_template_value_free(
		 &xml_template_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_template_value_get_flags function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_template_value_get_flags(
     libfwevt_xml_template_value_t *xml_template_value )
{
	libcerror_error_t *error = NULL;
	uint8_t flags            = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_xml_template_value_get_flags(
	          xml_template_value,
	          &flags,
	          &error );

	FWEVT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_xml_template_value_get_flags(
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

	result = libfwevt_xml_template_value_get_flags(
	          xml_template_value,
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

/* Tests the libfwevt_xml_template_value_set_flags function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_template_value_set_flags(
     void )
{
	libcerror_error_t *error                          = NULL;
	libfwevt_xml_template_value_t *xml_template_value = NULL;
	int result                                        = 0;

	/* Initialize test
	 */
	result = libfwevt_xml_template_value_initialize(
	          &xml_template_value,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_template_value",
	 xml_template_value );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_xml_template_value_set_flags(
	          xml_template_value,
	          0,
	          &error );

	FWEVT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_xml_template_value_set_flags(
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
	result = libfwevt_xml_template_value_free(
	          &xml_template_value,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "xml_template_value",
	 xml_template_value );

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
	if( xml_template_value != NULL )
	{
		libfwevt_xml_template_value_free(
		 &xml_template_value,
		 NULL );
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

	libcerror_error_t *error                          = NULL;
	libfwevt_xml_template_value_t *xml_template_value = NULL;
	int result                                        = 0;

#endif /* #if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	FWEVT_TEST_UNREFERENCED_PARAMETER( argc )
	FWEVT_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

	FWEVT_TEST_RUN(
	 "libfwevt_xml_template_value_initialize",
	 fwevt_test_xml_template_value_initialize );

	FWEVT_TEST_RUN(
	 "libfwevt_xml_template_value_free",
	 fwevt_test_xml_template_value_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize test
	 */
	result = libfwevt_xml_template_value_initialize(
	          &xml_template_value,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_template_value",
	 xml_template_value );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_template_value_get_type",
	 fwevt_test_xml_template_value_get_type,
	 xml_template_value );

	FWEVT_TEST_RUN(
	 "libfwevt_xml_template_value_set_type",
	 fwevt_test_xml_template_value_set_type );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_template_value_get_offset",
	 fwevt_test_xml_template_value_get_offset,
	 xml_template_value );

	FWEVT_TEST_RUN(
	 "libfwevt_xml_template_value_set_offset",
	 fwevt_test_xml_template_value_set_offset );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_template_value_get_size",
	 fwevt_test_xml_template_value_get_size,
	 xml_template_value );

	FWEVT_TEST_RUN(
	 "libfwevt_xml_template_value_set_size",
	 fwevt_test_xml_template_value_set_size );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_xml_template_value_get_flags",
	 fwevt_test_xml_template_value_get_flags,
	 xml_template_value );

	FWEVT_TEST_RUN(
	 "libfwevt_xml_template_value_set_flags",
	 fwevt_test_xml_template_value_set_flags );

	/* Clean up
	 */
	result = libfwevt_xml_template_value_free(
	          &xml_template_value,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "xml_template_value",
	 xml_template_value );

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
	if( xml_template_value != NULL )
	{
		libfwevt_xml_template_value_free(
		 &xml_template_value,
		 NULL );
	}
	return( EXIT_FAILURE );

#endif /* #if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */
}

