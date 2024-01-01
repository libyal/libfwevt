/*
 * Library template type test program
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
#include <byte_stream.h>
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

#include "../libfwevt/libfwevt_template.h"

unsigned char fwevt_test_template_data1[ 268 ] = {
	0x54, 0x45, 0x4d, 0x50, 0x0c, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
	0xc4, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xd8, 0x35, 0x02, 0x92, 0x3f, 0x4d, 0x1d, 0x56,
	0x53, 0xb7, 0xb5, 0x2e, 0xd9, 0xb4, 0x7a, 0x5a, 0x0f, 0x01, 0x01, 0x00, 0x01, 0xff, 0xff, 0x90,
	0x00, 0x00, 0x00, 0x44, 0x82, 0x09, 0x00, 0x45, 0x00, 0x76, 0x00, 0x65, 0x00, 0x6e, 0x00, 0x74,
	0x00, 0x44, 0x00, 0x61, 0x00, 0x74, 0x00, 0x61, 0x00, 0x00, 0x00, 0x02, 0x41, 0xff, 0xff, 0x33,
	0x00, 0x00, 0x00, 0x8a, 0x6f, 0x04, 0x00, 0x44, 0x00, 0x61, 0x00, 0x74, 0x00, 0x61, 0x00, 0x00,
	0x00, 0x1b, 0x00, 0x00, 0x00, 0x06, 0x4b, 0x95, 0x04, 0x00, 0x4e, 0x00, 0x61, 0x00, 0x6d, 0x00,
	0x65, 0x00, 0x00, 0x00, 0x05, 0x01, 0x04, 0x00, 0x6e, 0x00, 0x61, 0x00, 0x6d, 0x00, 0x65, 0x00,
	0x02, 0x0d, 0x00, 0x00, 0x01, 0x04, 0x41, 0xff, 0xff, 0x35, 0x00, 0x00, 0x00, 0x8a, 0x6f, 0x04,
	0x00, 0x44, 0x00, 0x61, 0x00, 0x74, 0x00, 0x61, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x06,
	0x4b, 0x95, 0x04, 0x00, 0x4e, 0x00, 0x61, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x00, 0x00, 0x05, 0x01,
	0x05, 0x00, 0x76, 0x00, 0x61, 0x00, 0x6c, 0x00, 0x75, 0x00, 0x65, 0x00, 0x02, 0x0d, 0x01, 0x00,
	0x07, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xec, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
	0x6e, 0x00, 0x61, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
	0x76, 0x00, 0x61, 0x00, 0x6c, 0x00, 0x75, 0x00, 0x65, 0x00, 0x00, 0x00 };

/* Tests the libfwevt_template_initialize function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_template_initialize(
     void )
{
	libcerror_error_t *error           = NULL;
	libfwevt_template_t *wevt_template = NULL;
	int result                         = 0;

#if defined( HAVE_FWEVT_TEST_MEMORY )
	int number_of_malloc_fail_tests    = 2;
	int number_of_memset_fail_tests    = 1;
	int test_number                    = 0;
#endif

	/* Test regular cases
	 */
	result = libfwevt_template_initialize(
	          &wevt_template,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "wevt_template",
	 wevt_template );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_template_free(
	          &wevt_template,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "wevt_template",
	 wevt_template );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_template_initialize(
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

	wevt_template = (libfwevt_template_t *) 0x12345678UL;

	result = libfwevt_template_initialize(
	          &wevt_template,
	          &error );

	wevt_template = NULL;

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
		/* Test libfwevt_template_initialize with malloc failing
		 */
		fwevt_test_malloc_attempts_before_fail = test_number;

		result = libfwevt_template_initialize(
		          &wevt_template,
		          &error );

		if( fwevt_test_malloc_attempts_before_fail != -1 )
		{
			fwevt_test_malloc_attempts_before_fail = -1;

			if( wevt_template != NULL )
			{
				libfwevt_template_free(
				 &wevt_template,
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
			 "wevt_template",
			 wevt_template );

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
		/* Test libfwevt_template_initialize with memset failing
		 */
		fwevt_test_memset_attempts_before_fail = test_number;

		result = libfwevt_template_initialize(
		          &wevt_template,
		          &error );

		if( fwevt_test_memset_attempts_before_fail != -1 )
		{
			fwevt_test_memset_attempts_before_fail = -1;

			if( wevt_template != NULL )
			{
				libfwevt_template_free(
				 &wevt_template,
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
			 "wevt_template",
			 wevt_template );

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
	if( wevt_template != NULL )
	{
		libfwevt_template_free(
		 &wevt_template,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_template_free function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_template_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfwevt_template_free(
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

/* Tests the libfwevt_internal_template_free function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_internal_template_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfwevt_internal_template_free(
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

/* Tests the libfwevt_template_read function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_template_read(
     void )
{
	libcerror_error_t *error      = NULL;
	libfwevt_template_t *template = NULL;
	int result                    = 0;

	/* Initialize test
	 */
	result = libfwevt_template_initialize(
	          &template,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "template",
	 template );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_template_read(
	          template,
	          fwevt_test_template_data1,
	          268,
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
	result = libfwevt_template_read(
	          template,
	          fwevt_test_template_data1,
	          268,
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
	result = libfwevt_template_free(
	          &template,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "template",
	 template );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfwevt_template_initialize(
	          &template,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "template",
	 template );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_template_read(
	          NULL,
	          fwevt_test_template_data1,
	          268,
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

	result = libfwevt_template_read(
	          template,
	          NULL,
	          268,
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

	result = libfwevt_template_read(
	          template,
	          fwevt_test_template_data1,
	          (size_t) SSIZE_MAX + 1,
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

	/* Test data offset value out of bounds
	 */
	result = libfwevt_template_read(
	          template,
	          fwevt_test_template_data1,
	          268,
	          268,
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

	/* Test data value too small to contain header
	 */
	result = libfwevt_template_read(
	          template,
	          fwevt_test_template_data1,
	          40 - 1,
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

	/* Test libfwevt_template_read with malloc failing
	 */
	fwevt_test_malloc_attempts_before_fail = 0;

	result = libfwevt_template_read(
	          template,
	          fwevt_test_template_data1,
	          268,
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

	/* Test libfwevt_template_read with memcpy failing
	 */
	fwevt_test_memcpy_attempts_before_fail = 0;

	result = libfwevt_template_read(
	          template,
	          fwevt_test_template_data1,
	          268,
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
#endif /* defined( OPTIMIZATION_DISABLED ) */
#endif /* defined( HAVE_FWEVT_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libfwevt_template_free(
	          &template,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "template",
	 template );

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
	if( template != NULL )
	{
		libfwevt_template_free(
		 &template,
		 NULL );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

/* Tests the libfwevt_template_read_header function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_template_read_header(
     void )
{
	libcerror_error_t *error      = NULL;
	libfwevt_template_t *template = NULL;
	int result                    = 0;

	/* Initialize test
	 */
	result = libfwevt_template_initialize(
	          &template,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "template",
	 template );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_template_read_header(
	          (libfwevt_internal_template_t *) template,
	          fwevt_test_template_data1,
	          268,
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
	result = libfwevt_template_read_header(
	          NULL,
	          fwevt_test_template_data1,
	          268,
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

	result = libfwevt_template_read_header(
	          (libfwevt_internal_template_t *) template,
	          NULL,
	          268,
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

	result = libfwevt_template_read_header(
	          (libfwevt_internal_template_t *) template,
	          fwevt_test_template_data1,
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

	/* Test error case where signature is invalid
	 */
	byte_stream_copy_from_uint32_little_endian(
	 fwevt_test_template_data1,
	 0xffffffffUL );

	result = libfwevt_template_read_header(
	          (libfwevt_internal_template_t *) template,
	          fwevt_test_template_data1,
	          268,
	          &error );

	byte_stream_copy_from_uint32_little_endian(
	 fwevt_test_template_data1,
	 0x504d4554UL );

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
	result = libfwevt_template_free(
	          &template,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "template",
	 template );

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
	if( template != NULL )
	{
		libfwevt_template_free(
		 &template,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_template_read_template_items function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_template_read_template_items(
     void )
{
	libcerror_error_t *error      = NULL;
	libfwevt_template_t *template = NULL;
	int result                    = 0;

	/* Initialize test
	 */
	result = libfwevt_template_initialize(
	          &template,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "template",
	 template );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_template_read_template_items(
	          (libfwevt_internal_template_t *) template,
	          &( fwevt_test_template_data1[ 196 ] ),
	          268 - 196,
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
	result = libfwevt_template_read_template_items(
	          NULL,
	          &( fwevt_test_template_data1[ 196 ] ),
	          268 - 196,
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

	result = libfwevt_template_read_template_items(
	          (libfwevt_internal_template_t *) template,
	          NULL,
	          268 - 196,
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

	result = libfwevt_template_read_template_items(
	          (libfwevt_internal_template_t *) template,
	          &( fwevt_test_template_data1[ 196 ] ),
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
	result = libfwevt_template_free(
	          &template,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "template",
	 template );

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
	if( template != NULL )
	{
		libfwevt_template_free(
		 &template,
		 NULL );
	}
	return( 0 );
}

#endif /* #if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

/* Tests the libfwevt_template_get_offset function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_template_get_offset(
     void )
{
	libcerror_error_t *error           = NULL;
	libfwevt_template_t *wevt_template = NULL;
	uint32_t offset                    = 0;
	int offset_is_set                  = 0;
	int result                         = 0;

	/* Initialize test
	 */
	result = libfwevt_template_initialize(
	          &wevt_template,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "wevt_template",
	 wevt_template );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_template_get_offset(
	          wevt_template,
	          &offset,
	          &error );

	FWEVT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset_is_set = result;

	/* Test error cases
	 */
	result = libfwevt_template_get_offset(
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

	if( offset_is_set != 0 )
	{
		result = libfwevt_template_get_offset(
		          wevt_template,
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
	}
	/* Clean up
	 */
	result = libfwevt_template_free(
	          &wevt_template,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "wevt_template",
	 wevt_template );

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
	if( wevt_template != NULL )
	{
		libfwevt_template_free(
		 &wevt_template,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_template_get_size function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_template_get_size(
     void )
{
	libcerror_error_t *error           = NULL;
	libfwevt_template_t *wevt_template = NULL;
	uint32_t size                      = 0;
	int result                         = 0;
	int size_is_set                    = 0;

	/* Initialize test
	 */
	result = libfwevt_template_initialize(
	          &wevt_template,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "wevt_template",
	 wevt_template );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_template_get_size(
	          wevt_template,
	          &size,
	          &error );

	FWEVT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	size_is_set = result;

	/* Test error cases
	 */
	result = libfwevt_template_get_size(
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

	if( size_is_set != 0 )
	{
		result = libfwevt_template_get_size(
		          wevt_template,
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
	}
	/* Clean up
	 */
	result = libfwevt_template_free(
	          &wevt_template,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "wevt_template",
	 wevt_template );

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
	if( wevt_template != NULL )
	{
		libfwevt_template_free(
		 &wevt_template,
		 NULL );
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
	 "libfwevt_template_initialize",
	 fwevt_test_template_initialize );

	FWEVT_TEST_RUN(
	 "libfwevt_template_free",
	 fwevt_test_template_free );

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

	FWEVT_TEST_RUN(
	 "libfwevt_internal_template_free",
	 fwevt_test_internal_template_free );

#endif /* #if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	FWEVT_TEST_RUN(
	 "libfwevt_template_read",
	 fwevt_test_template_read );

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

	FWEVT_TEST_RUN(
	 "libfwevt_template_read_header",
	 fwevt_test_template_read_header );

	FWEVT_TEST_RUN(
	 "libfwevt_template_read_template_items",
	 fwevt_test_template_read_template_items );

#endif /* #if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	/* TODO: add tests for libfwevt_template_read_xml_document */

	/* TODO: add tests for libfwevt_template_set_ascii_codepage */

	/* TODO: add tests for libfwevt_template_set_data */

	FWEVT_TEST_RUN(
	 "libfwevt_template_get_offset",
	 fwevt_test_template_get_offset );

	/* TODO: add tests for libfwevt_template_set_offset */

	FWEVT_TEST_RUN(
	 "libfwevt_template_get_size",
	 fwevt_test_template_get_size );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

