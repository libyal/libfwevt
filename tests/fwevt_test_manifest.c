/*
 * Library manifest type test program
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

uint8_t fwevt_test_manifest_data1[ 634 ] = {
	0x43, 0x52, 0x49, 0x4d, 0x78, 0x02, 0x00, 0x00, 0x05, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x53, 0xea, 0xa2, 0x06, 0x6c, 0xfc, 0xe5, 0x42, 0x91, 0x76, 0x18, 0x74, 0x9a, 0xb2, 0xca, 0x13,
	0x24, 0x00, 0x00, 0x00, 0x57, 0x45, 0x56, 0x54, 0x54, 0x02, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
	0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00,
	0xbc, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x14, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x20, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
	0x2c, 0x02, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x38, 0x02, 0x00, 0x00, 0x54, 0x54, 0x42, 0x4c,
	0x50, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x54, 0x45, 0x4d, 0x50, 0x44, 0x01, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x58, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x33, 0x12, 0x8a, 0x27, 0x65, 0xf6, 0x52, 0x52, 0x0b, 0xa7, 0x2b, 0xca, 0x59, 0x74, 0x33, 0xa8,
	0x0f, 0x01, 0x01, 0x00, 0x01, 0xff, 0xff, 0xac, 0x00, 0x00, 0x00, 0x44, 0x82, 0x09, 0x00, 0x45,
	0x00, 0x76, 0x00, 0x65, 0x00, 0x6e, 0x00, 0x74, 0x00, 0x44, 0x00, 0x61, 0x00, 0x74, 0x00, 0x61,
	0x00, 0x00, 0x00, 0x02, 0x41, 0xff, 0xff, 0x41, 0x00, 0x00, 0x00, 0x8a, 0x6f, 0x04, 0x00, 0x44,
	0x00, 0x61, 0x00, 0x74, 0x00, 0x61, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x06, 0x4b, 0x95,
	0x04, 0x00, 0x4e, 0x00, 0x61, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x00, 0x00, 0x05, 0x01, 0x0b, 0x00,
	0x6d, 0x00, 0x65, 0x00, 0x74, 0x00, 0x72, 0x00, 0x69, 0x00, 0x63, 0x00, 0x5f, 0x00, 0x6e, 0x00,
	0x61, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x02, 0x0d, 0x00, 0x00, 0x01, 0x04, 0x41, 0xff, 0xff, 0x43,
	0x00, 0x00, 0x00, 0x8a, 0x6f, 0x04, 0x00, 0x44, 0x00, 0x61, 0x00, 0x74, 0x00, 0x61, 0x00, 0x00,
	0x00, 0x2b, 0x00, 0x00, 0x00, 0x06, 0x4b, 0x95, 0x04, 0x00, 0x4e, 0x00, 0x61, 0x00, 0x6d, 0x00,
	0x65, 0x00, 0x00, 0x00, 0x05, 0x01, 0x0c, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x74, 0x00, 0x72, 0x00,
	0x69, 0x00, 0x63, 0x00, 0x5f, 0x00, 0x76, 0x00, 0x61, 0x00, 0x6c, 0x00, 0x75, 0x00, 0x65, 0x00,
	0x02, 0x0d, 0x01, 0x00, 0x07, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9c, 0x01, 0x00, 0x00,
	0x1c, 0x00, 0x00, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x74, 0x00, 0x72, 0x00, 0x69, 0x00, 0x63, 0x00,
	0x5f, 0x00, 0x6e, 0x00, 0x61, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
	0x6d, 0x00, 0x65, 0x00, 0x74, 0x00, 0x72, 0x00, 0x69, 0x00, 0x63, 0x00, 0x5f, 0x00, 0x76, 0x00,
	0x61, 0x00, 0x6c, 0x00, 0x75, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x52, 0x56, 0x41,
	0x4c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x10, 0xd0, 0x01, 0x00, 0x00,
	0x48, 0x00, 0x65, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x6f, 0x00, 0x20, 0x00, 0x57, 0x00, 0x6f, 0x00,
	0x72, 0x00, 0x6c, 0x00, 0x64, 0x00, 0x20, 0x00, 0x4d, 0x00, 0x65, 0x00, 0x74, 0x00, 0x72, 0x00,
	0x69, 0x00, 0x63, 0x00, 0x20, 0x00, 0x50, 0x00, 0x72, 0x00, 0x6f, 0x00, 0x76, 0x00, 0x69, 0x00,
	0x64, 0x00, 0x65, 0x00, 0x72, 0x00, 0x00, 0x00, 0x4f, 0x50, 0x43, 0x4f, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x4c, 0x45, 0x56, 0x4c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x54, 0x41, 0x53, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4b, 0x45, 0x59, 0x57,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x45, 0x56, 0x4e, 0x54, 0x40, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0xb0, 0x78, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

/* Tests the libfwevt_manifest_initialize function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_manifest_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfwevt_manifest_t *manifest   = NULL;
	int result                      = 0;

#if defined( HAVE_FWEVT_TEST_MEMORY )
	int number_of_malloc_fail_tests = 2;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libfwevt_manifest_initialize(
	          &manifest,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "manifest",
	 manifest );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_manifest_free(
	          &manifest,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "manifest",
	 manifest );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_manifest_initialize(
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

	manifest = (libfwevt_manifest_t *) 0x12345678UL;

	result = libfwevt_manifest_initialize(
	          &manifest,
	          &error );

	manifest = NULL;

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
		/* Test libfwevt_manifest_initialize with malloc failing
		 */
		fwevt_test_malloc_attempts_before_fail = test_number;

		result = libfwevt_manifest_initialize(
		          &manifest,
		          &error );

		if( fwevt_test_malloc_attempts_before_fail != -1 )
		{
			fwevt_test_malloc_attempts_before_fail = -1;

			if( manifest != NULL )
			{
				libfwevt_manifest_free(
				 &manifest,
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
			 "manifest",
			 manifest );

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
		/* Test libfwevt_manifest_initialize with memset failing
		 */
		fwevt_test_memset_attempts_before_fail = test_number;

		result = libfwevt_manifest_initialize(
		          &manifest,
		          &error );

		if( fwevt_test_memset_attempts_before_fail != -1 )
		{
			fwevt_test_memset_attempts_before_fail = -1;

			if( manifest != NULL )
			{
				libfwevt_manifest_free(
				 &manifest,
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
			 "manifest",
			 manifest );

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
	if( manifest != NULL )
	{
		libfwevt_manifest_free(
		 &manifest,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_manifest_free function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_manifest_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfwevt_manifest_free(
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

/* Tests the libfwevt_manifest_read function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_manifest_read(
     void )
{
	libcerror_error_t *error      = NULL;
	libfwevt_manifest_t *manifest = NULL;
	int result                    = 0;

	/* Initialize test
	 */
	result = libfwevt_manifest_initialize(
	          &manifest,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "manifest",
	 manifest );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test to copy security identifier from byte stream
	 */
	result = libfwevt_manifest_read(
	          manifest,
	          fwevt_test_manifest_data1,
	          634,
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
	result = libfwevt_manifest_read(
	          NULL,
	          fwevt_test_manifest_data1,
	          634,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_manifest_read(
	          manifest,
	          NULL,
	          634,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_manifest_read(
	          manifest,
	          fwevt_test_manifest_data1,
	          0,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	result = libfwevt_manifest_read(
	          manifest,
	          fwevt_test_manifest_data1,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	/* Test error case where data size is too small for header
	 */
	result = libfwevt_manifest_read(
	          manifest,
	          fwevt_test_manifest_data1,
	          8,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test error case where data size is too small for provider descriptor
	 */
	result = libfwevt_manifest_read(
	          manifest,
	          fwevt_test_manifest_data1,
	          20,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* TODO add test where malloc fails in libfwevt_provider_initialize */

	/* Test error case where signature is invalid
	 */
	byte_stream_copy_from_uint32_little_endian(
	 fwevt_test_manifest_data1,
	 0xffffffffUL );

	result = libfwevt_manifest_read(
	          manifest,
	          fwevt_test_manifest_data1,
	          634,
	          &error );

	byte_stream_copy_from_uint32_little_endian(
	 fwevt_test_manifest_data1,
	 0x4d495243UL );

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
	result = libfwevt_manifest_free(
	          &manifest,
	          NULL );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "manifest",
	 manifest );

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
	if( manifest != NULL )
	{
		libfwevt_manifest_free(
		 &manifest,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_manifest_get_number_of_providers function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_manifest_get_number_of_providers(
     libfwevt_manifest_t *manifest )
{
	libcerror_error_t *error = NULL;
	int number_of_providers  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_manifest_get_number_of_providers(
	          manifest,
	          &number_of_providers,
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
	result = libfwevt_manifest_get_number_of_providers(
	          NULL,
	          &number_of_providers,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_manifest_get_number_of_providers(
	          manifest,
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

/* Tests the libfwevt_manifest_get_provider_by_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_manifest_get_provider_by_index(
     libfwevt_manifest_t *manifest )
{
	libcerror_error_t *error      = NULL;
	libfwevt_provider_t *provider = NULL;
	int number_of_providers       = 0;
	int result                    = 0;

	/* Initialize test
	 */
	result = libfwevt_manifest_get_number_of_providers(
	          manifest,
	          &number_of_providers,
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
	if( number_of_providers > 0 )
	{
		result = libfwevt_manifest_get_provider_by_index(
		          manifest,
		          0,
		          &provider,
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

		/* Clean up
		 */
		result = libfwevt_provider_free(
		          &provider,
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
	}
	/* Test error cases
	 */
	result = libfwevt_manifest_get_provider_by_index(
	          NULL,
	          0,
	          &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_manifest_get_provider_by_index(
	          manifest,
	          -1,
	          &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_manifest_get_provider_by_index(
	          manifest,
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
	if( provider != NULL )
	{
		libfwevt_provider_free(
		 &provider,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_manifest_get_provider_by_identifier function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_manifest_get_provider_by_identifier(
     libfwevt_manifest_t *manifest )
{
	uint8_t provider_identifier[ 16 ] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	libcerror_error_t *error          = NULL;
	libfwevt_provider_t *provider     = NULL;
	int result                        = 0;

	/* Test regular cases
	 */
	result = libfwevt_manifest_get_provider_by_identifier(
	          manifest,
	          provider_identifier,
	          16,
	          &provider,
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
		 "provider",
		 provider );

		/* Clean up
		 */
		result = libfwevt_provider_free(
		          &provider,
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
	}
	/* Test error cases
	 */
	result = libfwevt_manifest_get_provider_by_identifier(
	          NULL,
	          provider_identifier,
	          16,
	          &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_manifest_get_provider_by_identifier(
	          manifest,
	          NULL,
	          16,
	          &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_manifest_get_provider_by_identifier(
	          manifest,
	          provider_identifier,
	          0,
	          &provider,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_manifest_get_provider_by_identifier(
	          manifest,
	          provider_identifier,
	          16,
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
	if( provider != NULL )
	{
		libfwevt_provider_free(
		 &provider,
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
	libcerror_error_t *error      = NULL;
	libfwevt_manifest_t *manifest = NULL;
	int result                    = 0;

	FWEVT_TEST_UNREFERENCED_PARAMETER( argc )
	FWEVT_TEST_UNREFERENCED_PARAMETER( argv )

	FWEVT_TEST_RUN(
	 "libfwevt_manifest_initialize",
	 fwevt_test_manifest_initialize );

	FWEVT_TEST_RUN(
	 "libfwevt_manifest_free",
	 fwevt_test_manifest_free );

	FWEVT_TEST_RUN(
	 "libfwevt_manifest_read",
	 fwevt_test_manifest_read );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize manifest for tests
	 */
	result = libfwevt_manifest_initialize(
	          &manifest,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "manifest",
	 manifest );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_manifest_read(
	          manifest,
	          fwevt_test_manifest_data1,
	          634,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_manifest_get_number_of_providers",
	 fwevt_test_manifest_get_number_of_providers,
	 manifest );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_manifest_get_provider_by_index",
	 fwevt_test_manifest_get_provider_by_index,
	 manifest );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_manifest_get_provider_by_identifier",
	 fwevt_test_manifest_get_provider_by_identifier,
	 manifest );

	/* Clean up
	 */
	result = libfwevt_manifest_free(
	          &manifest,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "manifest",
	 manifest );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( manifest != NULL )
	{
		libfwevt_manifest_free(
		 &manifest,
		 NULL );
	}
	return( EXIT_FAILURE );
}

