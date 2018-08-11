/*
 * Library provider type test program
 *
 * Copyright (C) 2011-2018, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
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

#include "../libfwevt/libfwevt_provider.h"

uint8_t fwevt_test_provider_identifier_data1[ 16 ] = {
	0x25, 0x96, 0x84, 0x54, 0x78, 0x54, 0x94, 0x49, 0xa5, 0xba, 0x3e, 0x3b, 0x03, 0x28, 0xc3, 0x0d };

uint8_t fwevt_test_provider_data1[ 32 ] = {
	0x57, 0x45, 0x56, 0x54, 0x2c, 0x5b, 0x05, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

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
	int number_of_malloc_fail_tests = 1;
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
				libfwevt_provider_free(
				 &provider,
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
				libfwevt_provider_free(
				 &provider,
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
/* TODO test memcpy failiing */

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
		libfwevt_provider_free(
		 &provider,
		 NULL );
	}
	return( 0 );
}

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

/* Tests the libfwevt_provider_read function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_provider_read(
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
	result = libfwevt_provider_read(
	          provider,
	          fwevt_test_provider_data1,
	          32,
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
	result = libfwevt_provider_read(
	          NULL,
	          fwevt_test_provider_data1,
	          32,
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

	result = libfwevt_provider_read(
	          provider,
	          NULL,
	          32,
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

	result = libfwevt_provider_read(
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
	result = libfwevt_provider_read(
	          provider,
	          fwevt_test_provider_data1,
	          32,
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

	/* Test data value too small
	 */
	result = libfwevt_provider_read(
	          provider,
	          fwevt_test_provider_data1,
	          19,
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

	/* Test data value too small
	 */
	result = libfwevt_provider_read(
	          provider,
	          fwevt_test_provider_data1,
	          27,
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

	/* Test data value too small
	 */
	result = libfwevt_provider_read(
	          provider,
	          fwevt_test_provider_data1,
	          31,
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
#ifdef TODO
/* TODO fix tests */
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
#endif

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

	FWEVT_TEST_RUN(
	 "libfwevt_provider_initialize",
	 fwevt_test_provider_initialize );

	FWEVT_TEST_RUN(
	 "libfwevt_provider_free",
	 fwevt_test_provider_free );

	FWEVT_TEST_RUN(
	 "libfwevt_provider_read",
	 fwevt_test_provider_read );

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

	result = libfwevt_provider_read(
	          provider,
	          fwevt_test_provider_data1,
	          32,
	          0,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* TODO: add tests for libfwevt_provider_read_channels */

	/* TODO: add tests for libfwevt_provider_read_events */

	/* TODO: add tests for libfwevt_provider_read_keywords */

	/* TODO: add tests for libfwevt_provider_read_levels */

	/* TODO: add tests for libfwevt_provider_read_maps */

	/* TODO: add tests for libfwevt_provider_read_opcodes */

	/* TODO: add tests for libfwevt_provider_read_tasks */

	/* TODO: add tests for libfwevt_provider_read_templates */

	/* TODO: add tests for libfwevt_provider_compare_identifier */

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_provider_get_number_of_channels",
	 fwevt_test_provider_get_number_of_channels,
	 provider );

	/* TODO: add tests for libfwevt_provider_get_channel */

	/* TODO: add tests for libfwevt_provider_get_number_of_events */

	/* TODO: add tests for libfwevt_provider_get_event */

	/* TODO: add tests for libfwevt_provider_get_event_by_identifier */

	/* TODO: add tests for libfwevt_provider_get_number_of_keywords */

	/* TODO: add tests for libfwevt_provider_get_keyword */

	/* TODO: add tests for libfwevt_provider_get_number_of_levels */

	/* TODO: add tests for libfwevt_provider_get_level */

	/* TODO: add tests for libfwevt_provider_get_number_of_maps */

	/* TODO: add tests for libfwevt_provider_get_map */

	/* TODO: add tests for libfwevt_provider_get_number_of_opcodes */

	/* TODO: add tests for libfwevt_provider_get_opcode */

	/* TODO: add tests for libfwevt_provider_get_number_of_tasks */

	/* TODO: add tests for libfwevt_provider_get_task */

	/* TODO: add tests for libfwevt_provider_get_number_of_templates */

	/* TODO: add tests for libfwevt_provider_get_template */

	/* TODO: add tests for libfwevt_provider_get_template_by_offset */

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

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

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
	return( EXIT_FAILURE );
}

