/*
 * Library provider type test program
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

#include "../libfwevt/libfwevt_provider.h"

uint8_t fwevt_test_provider_identifier_data1[ 16 ] = {
	0x53, 0xea, 0xa2, 0x06, 0x6c, 0xfc, 0xe5, 0x42, 0x91, 0x76, 0x18, 0x74, 0x9a, 0xb2, 0xca, 0x13 };

uint8_t fwevt_test_provider_data1[ 598 ] = {
	0x57, 0x45, 0x56, 0x54, 0x54, 0x02, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00,
	0x07, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0xbc, 0x01, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00, 0x08, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x02, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x20, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x2c, 0x02, 0x00, 0x00,
	0x04, 0x00, 0x00, 0x00, 0x38, 0x02, 0x00, 0x00, 0x54, 0x54, 0x42, 0x4c, 0x50, 0x01, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x54, 0x45, 0x4d, 0x50, 0x44, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00, 0x58, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x33, 0x12, 0x8a, 0x27,
	0x65, 0xf6, 0x52, 0x52, 0x0b, 0xa7, 0x2b, 0xca, 0x59, 0x74, 0x33, 0xa8, 0x0f, 0x01, 0x01, 0x00,
	0x01, 0xff, 0xff, 0xac, 0x00, 0x00, 0x00, 0x44, 0x82, 0x09, 0x00, 0x45, 0x00, 0x76, 0x00, 0x65,
	0x00, 0x6e, 0x00, 0x74, 0x00, 0x44, 0x00, 0x61, 0x00, 0x74, 0x00, 0x61, 0x00, 0x00, 0x00, 0x02,
	0x41, 0xff, 0xff, 0x41, 0x00, 0x00, 0x00, 0x8a, 0x6f, 0x04, 0x00, 0x44, 0x00, 0x61, 0x00, 0x74,
	0x00, 0x61, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x06, 0x4b, 0x95, 0x04, 0x00, 0x4e, 0x00,
	0x61, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x00, 0x00, 0x05, 0x01, 0x0b, 0x00, 0x6d, 0x00, 0x65, 0x00,
	0x74, 0x00, 0x72, 0x00, 0x69, 0x00, 0x63, 0x00, 0x5f, 0x00, 0x6e, 0x00, 0x61, 0x00, 0x6d, 0x00,
	0x65, 0x00, 0x02, 0x0d, 0x00, 0x00, 0x01, 0x04, 0x41, 0xff, 0xff, 0x43, 0x00, 0x00, 0x00, 0x8a,
	0x6f, 0x04, 0x00, 0x44, 0x00, 0x61, 0x00, 0x74, 0x00, 0x61, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x00,
	0x00, 0x06, 0x4b, 0x95, 0x04, 0x00, 0x4e, 0x00, 0x61, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x00, 0x00,
	0x05, 0x01, 0x0c, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x74, 0x00, 0x72, 0x00, 0x69, 0x00, 0x63, 0x00,
	0x5f, 0x00, 0x76, 0x00, 0x61, 0x00, 0x6c, 0x00, 0x75, 0x00, 0x65, 0x00, 0x02, 0x0d, 0x01, 0x00,
	0x07, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9c, 0x01, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
	0x6d, 0x00, 0x65, 0x00, 0x74, 0x00, 0x72, 0x00, 0x69, 0x00, 0x63, 0x00, 0x5f, 0x00, 0x6e, 0x00,
	0x61, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x6d, 0x00, 0x65, 0x00,
	0x74, 0x00, 0x72, 0x00, 0x69, 0x00, 0x63, 0x00, 0x5f, 0x00, 0x76, 0x00, 0x61, 0x00, 0x6c, 0x00,
	0x75, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x52, 0x56, 0x41, 0x4c, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x10, 0xd0, 0x01, 0x00, 0x00, 0x48, 0x00, 0x65, 0x00,
	0x6c, 0x00, 0x6c, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x57, 0x00, 0x6f, 0x00, 0x72, 0x00, 0x6c, 0x00,
	0x64, 0x00, 0x20, 0x00, 0x4d, 0x00, 0x65, 0x00, 0x74, 0x00, 0x72, 0x00, 0x69, 0x00, 0x63, 0x00,
	0x20, 0x00, 0x50, 0x00, 0x72, 0x00, 0x6f, 0x00, 0x76, 0x00, 0x69, 0x00, 0x64, 0x00, 0x65, 0x00,
	0x72, 0x00, 0x00, 0x00, 0x4f, 0x50, 0x43, 0x4f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x4c, 0x45, 0x56, 0x4c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x54, 0x41, 0x53, 0x4b,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4b, 0x45, 0x59, 0x57, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x45, 0x56, 0x4e, 0x54, 0x40, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0xb0, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

/* Tests the libfwevt_provider_initialize function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfwevt_provider_t *provider   = NULL;
	int result                      = 0;

#if defined( HAVE_FWEVT_TEST_MEMORY )
	int number_of_malloc_fail_tests = 16;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_internal_provider_free(
	          (libfwevt_internal_provider_t **) &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_provider_initialize(
	          NULL,
	          fwevt_test_provider_identifier_data1,
	          16,
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

	provider = (libfwevt_provider_t *) 0x12345678UL;

	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	provider = NULL;

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_provider_initialize(
	          &provider,
	          NULL,
	          16,
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

	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
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

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfwevt_provider_initialize with malloc failing
		 */
		fwevt_test_malloc_attempts_before_fail = test_number;

		result = libfwevt_provider_initialize(
		          &provider,
		          fwevt_test_provider_identifier_data1,
		          16,
		          &error );

		if( fwevt_test_malloc_attempts_before_fail != -1 )
		{
			fwevt_test_malloc_attempts_before_fail = -1;

			if( provider != NULL )
			{
				libfwevt_internal_provider_free(
				 (libfwevt_internal_provider_t **) &provider,
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
			 "provider",
			 provider );

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
		/* Test libfwevt_provider_initialize with memset failing
		 */
		fwevt_test_memset_attempts_before_fail = test_number;

		result = libfwevt_provider_initialize(
		          &provider,
		          fwevt_test_provider_identifier_data1,
		          16,
		          &error );

		if( fwevt_test_memset_attempts_before_fail != -1 )
		{
			fwevt_test_memset_attempts_before_fail = -1;

			if( provider != NULL )
			{
				libfwevt_internal_provider_free(
				 (libfwevt_internal_provider_t **) &provider,
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
			 "provider",
			 provider );

			FWEVT_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#if defined( OPTIMIZATION_DISABLED )

	/* Test libfwevt_provider_initialize with memcpy failing
	 */
	fwevt_test_memcpy_attempts_before_fail = 0;

	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	if( fwevt_test_memcpy_attempts_before_fail != -1 )
	{
		fwevt_test_memcpy_attempts_before_fail = -1;

		if( provider != NULL )
		{
			libfwevt_internal_provider_free(
			 (libfwevt_internal_provider_t **) &provider,
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
		 "provider",
		 provider );

		FWEVT_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( OPTIMIZATION_DISABLED ) */
#endif /* defined( HAVE_FWEVT_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( provider != NULL )
	{
		libfwevt_internal_provider_free(
		 (libfwevt_internal_provider_t **) &provider,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

/* Tests the libfwevt_provider_free function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfwevt_provider_free(
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

/* Tests the libfwevt_internal_provider_free function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_internal_provider_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfwevt_internal_provider_free(
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

/* Tests the libfwevt_provider_read_data function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_read_data(
     void )
{
	libcerror_error_t *error      = NULL;
	libfwevt_provider_t *provider = NULL;
	int result                    = 0;

	/* Initialize test
	 */
	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
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
	result = libfwevt_provider_read_data(
	          NULL,
	          fwevt_test_provider_data1,
	          598,
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

	result = libfwevt_provider_read_data(
	          provider,
	          NULL,
	          598,
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

	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
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
	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          598,
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
	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          20 - 1,
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

	/* Test data value too small to contain descriptors
	 */
	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          20 + 8 - 1,
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

	/* Test data value too small to contain unknown2 values
	 */
	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          20 + ( 7 * 8 ) + 4 - 1,
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

	/* Test error case where signature is invalid
	 */
	byte_stream_copy_from_uint32_little_endian(
	 fwevt_test_provider_data1,
	 0xffffffffUL );

	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          0,
	          &error );

	byte_stream_copy_from_uint32_little_endian(
	 fwevt_test_provider_data1,
	 0x54564557UL );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test error case where descriptor offset is out of bounds
	 */
	byte_stream_copy_from_uint32_little_endian(
	 &( fwevt_test_provider_data1[ 20 ] ),
	 0xffffffffUL );

	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          0,
	          &error );

	byte_stream_copy_from_uint32_little_endian(
	 &( fwevt_test_provider_data1[ 20 ] ),
	 0x0000006cUL );

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
	result = libfwevt_internal_provider_free(
	          (libfwevt_internal_provider_t **) &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "provider",
	 provider );

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
	if( provider != NULL )
	{
		libfwevt_internal_provider_free(
		 (libfwevt_internal_provider_t **) &provider,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_provider_read_channels function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_read_channels(
     void )
{
	libcerror_error_t *error      = NULL;
	libfwevt_provider_t *provider = NULL;
	uint32_t channels_offset      = 0;
	int result                    = 0;

	/* Initialize test
	 */
	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          0,
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
	result = libfwevt_provider_read_channels(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libfwevt_internal_provider_free(
	          (libfwevt_internal_provider_t **) &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
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
	result = libfwevt_provider_read_channels(
	          NULL,
	          fwevt_test_provider_data1,
	          598,
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

	result = libfwevt_provider_read_channels(
	          provider,
	          NULL,
	          598,
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

	result = libfwevt_provider_read_channels(
	          provider,
	          fwevt_test_provider_data1,
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

	channels_offset = ( (libfwevt_internal_provider_t *) provider )->channels_offset;

	( (libfwevt_internal_provider_t *) provider )->channels_offset = 598;

	result = libfwevt_provider_read_channels(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          &error );

	( (libfwevt_internal_provider_t *) provider )->channels_offset = channels_offset;

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
	result = libfwevt_internal_provider_free(
	          (libfwevt_internal_provider_t **) &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "provider",
	 provider );

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
	if( provider != NULL )
	{
		libfwevt_internal_provider_free(
		 (libfwevt_internal_provider_t **) &provider,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_provider_read_events function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_read_events(
     void )
{
	libcerror_error_t *error      = NULL;
	libfwevt_provider_t *provider = NULL;
	uint32_t events_offset        = 0;
	int result                    = 0;

	/* Initialize test
	 */
	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          0,
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
	result = libfwevt_provider_read_events(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libfwevt_internal_provider_free(
	          (libfwevt_internal_provider_t **) &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
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
	result = libfwevt_provider_read_events(
	          NULL,
	          fwevt_test_provider_data1,
	          598,
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

	result = libfwevt_provider_read_events(
	          provider,
	          NULL,
	          598,
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

	result = libfwevt_provider_read_events(
	          provider,
	          fwevt_test_provider_data1,
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

	events_offset = ( (libfwevt_internal_provider_t *) provider )->events_offset;

	( (libfwevt_internal_provider_t *) provider )->events_offset = 598;

	result = libfwevt_provider_read_events(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          &error );

	( (libfwevt_internal_provider_t *) provider )->events_offset = events_offset;

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
	result = libfwevt_internal_provider_free(
	          (libfwevt_internal_provider_t **) &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "provider",
	 provider );

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
	if( provider != NULL )
	{
		libfwevt_internal_provider_free(
		 (libfwevt_internal_provider_t **) &provider,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_provider_read_keywords function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_read_keywords(
     void )
{
	libcerror_error_t *error      = NULL;
	libfwevt_provider_t *provider = NULL;
	uint32_t keywords_offset      = 0;
	int result                    = 0;

	/* Initialize test
	 */
	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          0,
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
	result = libfwevt_provider_read_keywords(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libfwevt_internal_provider_free(
	          (libfwevt_internal_provider_t **) &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
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
	result = libfwevt_provider_read_keywords(
	          NULL,
	          fwevt_test_provider_data1,
	          598,
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

	result = libfwevt_provider_read_keywords(
	          provider,
	          NULL,
	          598,
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

	result = libfwevt_provider_read_keywords(
	          provider,
	          fwevt_test_provider_data1,
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

	keywords_offset = ( (libfwevt_internal_provider_t *) provider )->keywords_offset;

	( (libfwevt_internal_provider_t *) provider )->keywords_offset = 598;

	result = libfwevt_provider_read_keywords(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          &error );

	( (libfwevt_internal_provider_t *) provider )->keywords_offset = keywords_offset;

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
	result = libfwevt_internal_provider_free(
	          (libfwevt_internal_provider_t **) &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "provider",
	 provider );

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
	if( provider != NULL )
	{
		libfwevt_internal_provider_free(
		 (libfwevt_internal_provider_t **) &provider,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_provider_read_levels function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_read_levels(
     void )
{
	libcerror_error_t *error      = NULL;
	libfwevt_provider_t *provider = NULL;
	uint32_t levels_offset        = 0;
	int result                    = 0;

	/* Initialize test
	 */
	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          0,
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
	result = libfwevt_provider_read_levels(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libfwevt_internal_provider_free(
	          (libfwevt_internal_provider_t **) &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
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
	result = libfwevt_provider_read_levels(
	          NULL,
	          fwevt_test_provider_data1,
	          598,
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

	result = libfwevt_provider_read_levels(
	          provider,
	          NULL,
	          598,
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

	result = libfwevt_provider_read_levels(
	          provider,
	          fwevt_test_provider_data1,
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

	levels_offset = ( (libfwevt_internal_provider_t *) provider )->levels_offset;

	( (libfwevt_internal_provider_t *) provider )->levels_offset = 598;

	result = libfwevt_provider_read_levels(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          &error );

	( (libfwevt_internal_provider_t *) provider )->levels_offset = levels_offset;

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
	result = libfwevt_internal_provider_free(
	          (libfwevt_internal_provider_t **) &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "provider",
	 provider );

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
	if( provider != NULL )
	{
		libfwevt_internal_provider_free(
		 (libfwevt_internal_provider_t **) &provider,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_provider_read_maps function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_read_maps(
     void )
{
	libcerror_error_t *error      = NULL;
	libfwevt_provider_t *provider = NULL;
	uint32_t maps_offset          = 0;
	int result                    = 0;

	/* Initialize test
	 */
	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          0,
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
	result = libfwevt_provider_read_maps(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libfwevt_internal_provider_free(
	          (libfwevt_internal_provider_t **) &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
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
	result = libfwevt_provider_read_maps(
	          NULL,
	          fwevt_test_provider_data1,
	          598,
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

	result = libfwevt_provider_read_maps(
	          provider,
	          NULL,
	          598,
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

	result = libfwevt_provider_read_maps(
	          provider,
	          fwevt_test_provider_data1,
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

	maps_offset = ( (libfwevt_internal_provider_t *) provider )->maps_offset;

	( (libfwevt_internal_provider_t *) provider )->maps_offset = 598;

	result = libfwevt_provider_read_maps(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          &error );

	( (libfwevt_internal_provider_t *) provider )->maps_offset = maps_offset;

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
	result = libfwevt_internal_provider_free(
	          (libfwevt_internal_provider_t **) &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "provider",
	 provider );

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
	if( provider != NULL )
	{
		libfwevt_internal_provider_free(
		 (libfwevt_internal_provider_t **) &provider,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_provider_read_opcodes function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_read_opcodes(
     void )
{
	libcerror_error_t *error      = NULL;
	libfwevt_provider_t *provider = NULL;
	uint32_t opcodes_offset       = 0;
	int result                    = 0;

	/* Initialize test
	 */
	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          0,
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
	result = libfwevt_provider_read_opcodes(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libfwevt_internal_provider_free(
	          (libfwevt_internal_provider_t **) &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
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
	result = libfwevt_provider_read_opcodes(
	          NULL,
	          fwevt_test_provider_data1,
	          598,
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

	result = libfwevt_provider_read_opcodes(
	          provider,
	          NULL,
	          598,
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

	result = libfwevt_provider_read_opcodes(
	          provider,
	          fwevt_test_provider_data1,
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

	opcodes_offset = ( (libfwevt_internal_provider_t *) provider )->opcodes_offset;

	( (libfwevt_internal_provider_t *) provider )->opcodes_offset = 598;

	result = libfwevt_provider_read_opcodes(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          &error );

	( (libfwevt_internal_provider_t *) provider )->opcodes_offset = opcodes_offset;

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
	result = libfwevt_internal_provider_free(
	          (libfwevt_internal_provider_t **) &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "provider",
	 provider );

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
	if( provider != NULL )
	{
		libfwevt_internal_provider_free(
		 (libfwevt_internal_provider_t **) &provider,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_provider_read_tasks function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_read_tasks(
     void )
{
	libcerror_error_t *error      = NULL;
	libfwevt_provider_t *provider = NULL;
	uint32_t tasks_offset         = 0;
	int result                    = 0;

	/* Initialize test
	 */
	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          0,
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
	result = libfwevt_provider_read_tasks(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libfwevt_internal_provider_free(
	          (libfwevt_internal_provider_t **) &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
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
	result = libfwevt_provider_read_tasks(
	          NULL,
	          fwevt_test_provider_data1,
	          598,
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

	result = libfwevt_provider_read_tasks(
	          provider,
	          NULL,
	          598,
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

	result = libfwevt_provider_read_tasks(
	          provider,
	          fwevt_test_provider_data1,
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

	tasks_offset = ( (libfwevt_internal_provider_t *) provider )->tasks_offset;

	( (libfwevt_internal_provider_t *) provider )->tasks_offset = 598;

	result = libfwevt_provider_read_tasks(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          &error );

	( (libfwevt_internal_provider_t *) provider )->tasks_offset = tasks_offset;

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
	result = libfwevt_internal_provider_free(
	          (libfwevt_internal_provider_t **) &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "provider",
	 provider );

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
	if( provider != NULL )
	{
		libfwevt_internal_provider_free(
		 (libfwevt_internal_provider_t **) &provider,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_provider_read_templates function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_read_templates(
     void )
{
	libcerror_error_t *error      = NULL;
	libfwevt_provider_t *provider = NULL;
	uint32_t templates_offset     = 0;
	int result                    = 0;

	/* Initialize test
	 */
	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          0,
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
	result = libfwevt_provider_read_templates(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libfwevt_internal_provider_free(
	          (libfwevt_internal_provider_t **) &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
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
	result = libfwevt_provider_read_templates(
	          NULL,
	          fwevt_test_provider_data1,
	          598,
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

	result = libfwevt_provider_read_templates(
	          provider,
	          NULL,
	          598,
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

	result = libfwevt_provider_read_templates(
	          provider,
	          fwevt_test_provider_data1,
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

	templates_offset = ( (libfwevt_internal_provider_t *) provider )->templates_offset;

	( (libfwevt_internal_provider_t *) provider )->templates_offset = 598;

	result = libfwevt_provider_read_templates(
	          provider,
	          fwevt_test_provider_data1,
	          598,
	          &error );

	( (libfwevt_internal_provider_t *) provider )->templates_offset = templates_offset;

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
	result = libfwevt_internal_provider_free(
	          (libfwevt_internal_provider_t **) &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "provider",
	 provider );

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
	if( provider != NULL )
	{
		libfwevt_internal_provider_free(
		 (libfwevt_internal_provider_t **) &provider,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_provider_compare_identifier function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_compare_identifier(
     void )
{
	uint8_t identifier[ 16 ] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	libcerror_error_t *error      = NULL;
	libfwevt_provider_t *provider = NULL;
	int result                    = 0;

	/* Initialize test
	 */
	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_provider_compare_identifier(
	          provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_provider_compare_identifier(
	          provider,
	          identifier,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_provider_compare_identifier(
	          NULL,
	          fwevt_test_provider_identifier_data1,
	          16,
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

	result = libfwevt_provider_compare_identifier(
	          provider,
	          NULL,
	          16,
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

	result = libfwevt_provider_compare_identifier(
	          provider,
	          fwevt_test_provider_identifier_data1,
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
	result = libfwevt_internal_provider_free(
	          (libfwevt_internal_provider_t **) &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "provider",
	 provider );

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
	if( provider != NULL )
	{
		libfwevt_internal_provider_free(
		 (libfwevt_internal_provider_t **) &provider,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_provider_get_number_of_channels function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_get_number_of_channels(
     libfwevt_provider_t *provider )
{
	libcerror_error_t *error = NULL;
	int number_of_channels   = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_provider_get_number_of_channels(
	          provider,
	          &number_of_channels,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "number_of_channels",
	 number_of_channels,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_provider_get_number_of_channels(
	          NULL,
	          &number_of_channels,
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

	result = libfwevt_provider_get_number_of_channels(
	          provider,
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

/* Tests the libfwevt_provider_get_channel_by_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_get_channel_by_index(
     libfwevt_provider_t *provider )
{
	libcerror_error_t *error    = NULL;
	libfwevt_channel_t *channel = NULL;
	int number_of_channels      = 0;
	int result                  = 0;

	/* Initialize test
	 */
	result = libfwevt_provider_get_number_of_channels(
	          provider,
	          &number_of_channels,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "number_of_channels",
	 number_of_channels,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	if( number_of_channels > 0 )
	{
		result = libfwevt_provider_get_channel_by_index(
		          provider,
		          0,
		          &channel,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NOT_NULL(
		 "channel",
		 channel );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libfwevt_channel_free(
		          &channel,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "channel",
		 channel );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libfwevt_provider_get_channel_by_index(
	          NULL,
	          0,
	          &channel,
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

	result = libfwevt_provider_get_channel_by_index(
	          provider,
	          -1,
	          &channel,
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

	result = libfwevt_provider_get_channel_by_index(
	          provider,
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
	if( channel != NULL )
	{
		libfwevt_channel_free(
		 &channel,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_provider_get_number_of_events function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_get_number_of_events(
     libfwevt_provider_t *provider )
{
	libcerror_error_t *error = NULL;
	int number_of_events     = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_provider_get_number_of_events(
	          provider,
	          &number_of_events,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "number_of_events",
	 number_of_events,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_provider_get_number_of_events(
	          NULL,
	          &number_of_events,
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

	result = libfwevt_provider_get_number_of_events(
	          provider,
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

/* Tests the libfwevt_provider_get_event_by_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_get_event_by_index(
     libfwevt_provider_t *provider )
{
	libcerror_error_t *error = NULL;
	libfwevt_event_t *event  = NULL;
	int number_of_events     = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libfwevt_provider_get_number_of_events(
	          provider,
	          &number_of_events,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "number_of_events",
	 number_of_events,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	if( number_of_events > 0 )
	{
		result = libfwevt_provider_get_event_by_index(
		          provider,
		          0,
		          &event,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NOT_NULL(
		 "event",
		 event );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libfwevt_event_free(
		          &event,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "event",
		 event );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libfwevt_provider_get_event_by_index(
	          NULL,
	          0,
	          &event,
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

	result = libfwevt_provider_get_event_by_index(
	          provider,
	          -1,
	          &event,
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

	result = libfwevt_provider_get_event_by_index(
	          provider,
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
	if( event != NULL )
	{
		libfwevt_event_free(
		 &event,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_provider_get_event_by_identifier function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_get_event_by_identifier(
     libfwevt_provider_t *provider )
{
	libcerror_error_t *error = NULL;
	libfwevt_event_t *event  = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_provider_get_event_by_identifier(
	          provider,
	          0,
	          &event,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( result != 0 )
	{
		FWEVT_TEST_ASSERT_IS_NOT_NULL(
		 "event",
		 event );

		result = libfwevt_event_free(
		          &event,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "event",
		 event );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libfwevt_provider_get_event_by_identifier(
	          NULL,
	          0,
	          &event,
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

	result = libfwevt_provider_get_event_by_identifier(
	          provider,
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
	if( event != NULL )
	{
		libfwevt_event_free(
		 &event,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_provider_get_number_of_keywords function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_get_number_of_keywords(
     libfwevt_provider_t *provider )
{
	libcerror_error_t *error = NULL;
	int number_of_keywords   = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_provider_get_number_of_keywords(
	          provider,
	          &number_of_keywords,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "number_of_keywords",
	 number_of_keywords,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_provider_get_number_of_keywords(
	          NULL,
	          &number_of_keywords,
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

	result = libfwevt_provider_get_number_of_keywords(
	          provider,
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

/* Tests the libfwevt_provider_get_keyword_by_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_get_keyword_by_index(
     libfwevt_provider_t *provider )
{
	libcerror_error_t *error    = NULL;
	libfwevt_keyword_t *keyword = NULL;
	int number_of_keywords      = 0;
	int result                  = 0;

	/* Initialize test
	 */
	result = libfwevt_provider_get_number_of_keywords(
	          provider,
	          &number_of_keywords,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "number_of_keywords",
	 number_of_keywords,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	if( number_of_keywords > 0 )
	{
		result = libfwevt_provider_get_keyword_by_index(
		          provider,
		          0,
		          &keyword,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NOT_NULL(
		 "keyword",
		 keyword );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libfwevt_keyword_free(
		          &keyword,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "keyword",
		 keyword );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libfwevt_provider_get_keyword_by_index(
	          NULL,
	          0,
	          &keyword,
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

	result = libfwevt_provider_get_keyword_by_index(
	          provider,
	          -1,
	          &keyword,
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

	result = libfwevt_provider_get_keyword_by_index(
	          provider,
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
	if( keyword != NULL )
	{
		libfwevt_keyword_free(
		 &keyword,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_provider_get_number_of_levels function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_get_number_of_levels(
     libfwevt_provider_t *provider )
{
	libcerror_error_t *error = NULL;
	int number_of_levels     = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_provider_get_number_of_levels(
	          provider,
	          &number_of_levels,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "number_of_levels",
	 number_of_levels,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_provider_get_number_of_levels(
	          NULL,
	          &number_of_levels,
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

	result = libfwevt_provider_get_number_of_levels(
	          provider,
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

/* Tests the libfwevt_provider_get_level_by_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_get_level_by_index(
     libfwevt_provider_t *provider )
{
	libcerror_error_t *error = NULL;
	libfwevt_level_t *level  = NULL;
	int number_of_levels     = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libfwevt_provider_get_number_of_levels(
	          provider,
	          &number_of_levels,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "number_of_levels",
	 number_of_levels,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	if( number_of_levels > 0 )
	{
		result = libfwevt_provider_get_level_by_index(
		          provider,
		          0,
		          &level,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NOT_NULL(
		 "level",
		 level );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libfwevt_level_free(
		          &level,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "level",
		 level );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libfwevt_provider_get_level_by_index(
	          NULL,
	          0,
	          &level,
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

	result = libfwevt_provider_get_level_by_index(
	          provider,
	          -1,
	          &level,
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

	result = libfwevt_provider_get_level_by_index(
	          provider,
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
	if( level != NULL )
	{
		libfwevt_level_free(
		 &level,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_provider_get_number_of_maps function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_get_number_of_maps(
     libfwevt_provider_t *provider )
{
	libcerror_error_t *error = NULL;
	int number_of_maps       = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_provider_get_number_of_maps(
	          provider,
	          &number_of_maps,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "number_of_maps",
	 number_of_maps,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_provider_get_number_of_maps(
	          NULL,
	          &number_of_maps,
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

	result = libfwevt_provider_get_number_of_maps(
	          provider,
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

/* Tests the libfwevt_provider_get_map_by_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_get_map_by_index(
     libfwevt_provider_t *provider )
{
	libcerror_error_t *error = NULL;
	libfwevt_map_t *map      = NULL;
	int number_of_maps       = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libfwevt_provider_get_number_of_maps(
	          provider,
	          &number_of_maps,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "number_of_maps",
	 number_of_maps,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	if( number_of_maps > 0 )
	{
		result = libfwevt_provider_get_map_by_index(
		          provider,
		          0,
		          &map,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NOT_NULL(
		 "map",
		 map );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libfwevt_map_free(
		          &map,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "map",
		 map );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libfwevt_provider_get_map_by_index(
	          NULL,
	          0,
	          &map,
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

	result = libfwevt_provider_get_map_by_index(
	          provider,
	          -1,
	          &map,
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

	result = libfwevt_provider_get_map_by_index(
	          provider,
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
	if( map != NULL )
	{
		libfwevt_map_free(
		 &map,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_provider_get_number_of_opcodes function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_get_number_of_opcodes(
     libfwevt_provider_t *provider )
{
	libcerror_error_t *error = NULL;
	int number_of_opcodes    = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_provider_get_number_of_opcodes(
	          provider,
	          &number_of_opcodes,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "number_of_opcodes",
	 number_of_opcodes,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_provider_get_number_of_opcodes(
	          NULL,
	          &number_of_opcodes,
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

	result = libfwevt_provider_get_number_of_opcodes(
	          provider,
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

/* Tests the libfwevt_provider_get_opcode_by_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_get_opcode_by_index(
     libfwevt_provider_t *provider )
{
	libcerror_error_t *error  = NULL;
	libfwevt_opcode_t *opcode = NULL;
	int number_of_opcodes     = 0;
	int result                = 0;

	/* Initialize test
	 */
	result = libfwevt_provider_get_number_of_opcodes(
	          provider,
	          &number_of_opcodes,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "number_of_opcodes",
	 number_of_opcodes,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	if( number_of_opcodes > 0 )
	{
		result = libfwevt_provider_get_opcode_by_index(
		          provider,
		          0,
		          &opcode,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NOT_NULL(
		 "opcode",
		 opcode );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libfwevt_opcode_free(
		          &opcode,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "opcode",
		 opcode );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libfwevt_provider_get_opcode_by_index(
	          NULL,
	          0,
	          &opcode,
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

	result = libfwevt_provider_get_opcode_by_index(
	          provider,
	          -1,
	          &opcode,
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

	result = libfwevt_provider_get_opcode_by_index(
	          provider,
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
	if( opcode != NULL )
	{
		libfwevt_opcode_free(
		 &opcode,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_provider_get_number_of_tasks function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_get_number_of_tasks(
     libfwevt_provider_t *provider )
{
	libcerror_error_t *error = NULL;
	int number_of_tasks      = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_provider_get_number_of_tasks(
	          provider,
	          &number_of_tasks,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "number_of_tasks",
	 number_of_tasks,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_provider_get_number_of_tasks(
	          NULL,
	          &number_of_tasks,
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

	result = libfwevt_provider_get_number_of_tasks(
	          provider,
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

/* Tests the libfwevt_provider_get_task_by_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_get_task_by_index(
     libfwevt_provider_t *provider )
{
	libcerror_error_t *error = NULL;
	libfwevt_task_t *task    = NULL;
	int number_of_tasks      = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libfwevt_provider_get_number_of_tasks(
	          provider,
	          &number_of_tasks,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "number_of_tasks",
	 number_of_tasks,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	if( number_of_tasks > 0 )
	{
		result = libfwevt_provider_get_task_by_index(
		          provider,
		          0,
		          &task,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NOT_NULL(
		 "task",
		 task );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libfwevt_task_free(
		          &task,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "task",
		 task );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libfwevt_provider_get_task_by_index(
	          NULL,
	          0,
	          &task,
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

	result = libfwevt_provider_get_task_by_index(
	          provider,
	          -1,
	          &task,
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

	result = libfwevt_provider_get_task_by_index(
	          provider,
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
	if( task != NULL )
	{
		libfwevt_task_free(
		 &task,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_provider_get_number_of_templates function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_get_number_of_templates(
     libfwevt_provider_t *provider )
{
	libcerror_error_t *error = NULL;
	int number_of_templates  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_provider_get_number_of_templates(
	          provider,
	          &number_of_templates,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "number_of_templates",
	 number_of_templates,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_provider_get_number_of_templates(
	          NULL,
	          &number_of_templates,
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

	result = libfwevt_provider_get_number_of_templates(
	          provider,
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

/* Tests the libfwevt_provider_get_template_by_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_get_template_by_index(
     libfwevt_provider_t *provider )
{
	libcerror_error_t *error      = NULL;
	libfwevt_template_t *template = NULL;
	int number_of_templates       = 0;
	int result                    = 0;

	/* Initialize test
	 */
	result = libfwevt_provider_get_number_of_templates(
	          provider,
	          &number_of_templates,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "number_of_templates",
	 number_of_templates,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	if( number_of_templates > 0 )
	{
		result = libfwevt_provider_get_template_by_index(
		          provider,
		          0,
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
	}
	/* Test error cases
	 */
	result = libfwevt_provider_get_template_by_index(
	          NULL,
	          0,
	          &template,
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

	result = libfwevt_provider_get_template_by_index(
	          provider,
	          -1,
	          &template,
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

	result = libfwevt_provider_get_template_by_index(
	          provider,
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
	if( template != NULL )
	{
		libfwevt_template_free(
		 &template,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_provider_get_template_by_offset function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_get_template_by_offset(
     libfwevt_provider_t *provider )
{
	libcerror_error_t *error      = NULL;
	libfwevt_template_t *template = NULL;
	int result                    = 0;

	/* Test regular cases
	 */
	result = libfwevt_provider_get_template_by_offset(
	          provider,
	          0,
	          &template,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( result != 0 )
	{
		FWEVT_TEST_ASSERT_IS_NOT_NULL(
		 "template",
		 template );

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
	}
	/* Test error cases
	 */
	result = libfwevt_provider_get_template_by_offset(
	          NULL,
	          0,
	          &template,
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

	result = libfwevt_provider_get_template_by_offset(
	          provider,
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
	if( template != NULL )
	{
		libfwevt_template_free(
		 &template,
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
	libcerror_error_t *error      = NULL;
	libfwevt_provider_t *provider = NULL;
	int result                    = 0;

	FWEVT_TEST_UNREFERENCED_PARAMETER( argc )
	FWEVT_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

	FWEVT_TEST_RUN(
	 "libfwevt_provider_initialize",
	 fwevt_test_provider_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	FWEVT_TEST_RUN(
	 "libfwevt_provider_free",
	 fwevt_test_provider_free );

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

	FWEVT_TEST_RUN(
	 "libfwevt_internal_provider_free",
	 fwevt_test_internal_provider_free );

	FWEVT_TEST_RUN(
	 "libfwevt_provider_read_data",
	 fwevt_test_provider_read_data );

	FWEVT_TEST_RUN(
	 "libfwevt_provider_read_channels",
	 fwevt_test_provider_read_channels );

	FWEVT_TEST_RUN(
	 "libfwevt_provider_read_events",
	 fwevt_test_provider_read_events );

	FWEVT_TEST_RUN(
	 "libfwevt_provider_read_keywords",
	 fwevt_test_provider_read_keywords );

	FWEVT_TEST_RUN(
	 "libfwevt_provider_read_levels",
	 fwevt_test_provider_read_levels );

	FWEVT_TEST_RUN(
	 "libfwevt_provider_read_maps",
	 fwevt_test_provider_read_maps );

	FWEVT_TEST_RUN(
	 "libfwevt_provider_read_opcodes",
	 fwevt_test_provider_read_opcodes );

	FWEVT_TEST_RUN(
	 "libfwevt_provider_read_tasks",
	 fwevt_test_provider_read_tasks );

	FWEVT_TEST_RUN(
	 "libfwevt_provider_read_templates",
	 fwevt_test_provider_read_templates );

	FWEVT_TEST_RUN(
	 "libfwevt_provider_compare_identifier",
	 fwevt_test_provider_compare_identifier );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize provider for tests
	 */
	result = libfwevt_provider_initialize(
	          &provider,
	          fwevt_test_provider_identifier_data1,
	          16,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_provider_read_data(
	          provider,
	          fwevt_test_provider_data1,
	          598,
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
	 "libfwevt_provider_get_number_of_channels",
	 fwevt_test_provider_get_number_of_channels,
	 provider );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_provider_get_channel_by_index",
	 fwevt_test_provider_get_channel_by_index,
	 provider );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_provider_get_number_of_events",
	 fwevt_test_provider_get_number_of_events,
	 provider );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_provider_get_event_by_index",
	 fwevt_test_provider_get_event_by_index,
	 provider );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_provider_get_event_by_identifier",
	 fwevt_test_provider_get_event_by_identifier,
	 provider );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_provider_get_number_of_keywords",
	 fwevt_test_provider_get_number_of_keywords,
	 provider );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_provider_get_keyword_by_index",
	 fwevt_test_provider_get_keyword_by_index,
	 provider );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_provider_get_number_of_levels",
	 fwevt_test_provider_get_number_of_levels,
	 provider );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_provider_get_level_by_index",
	 fwevt_test_provider_get_level_by_index,
	 provider );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_provider_get_number_of_maps",
	 fwevt_test_provider_get_number_of_maps,
	 provider );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_provider_get_map_by_index",
	 fwevt_test_provider_get_map_by_index,
	 provider );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_provider_get_number_of_opcodes",
	 fwevt_test_provider_get_number_of_opcodes,
	 provider );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_provider_get_opcode_by_index",
	 fwevt_test_provider_get_opcode_by_index,
	 provider );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_provider_get_number_of_tasks",
	 fwevt_test_provider_get_number_of_tasks,
	 provider );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_provider_get_task_by_index",
	 fwevt_test_provider_get_task_by_index,
	 provider );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_provider_get_number_of_templates",
	 fwevt_test_provider_get_number_of_templates,
	 provider );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_provider_get_template_by_index",
	 fwevt_test_provider_get_template_by_index,
	 provider );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_provider_get_template_by_offset",
	 fwevt_test_provider_get_template_by_offset,
	 provider );

	/* Clean up
	 */
	result = libfwevt_internal_provider_free(
	          (libfwevt_internal_provider_t **) &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "provider",
	 provider );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */
#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( provider != NULL )
	{
		libfwevt_internal_provider_free(
		 (libfwevt_internal_provider_t **) &provider,
		 NULL );
	}
#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	return( EXIT_FAILURE );
}

