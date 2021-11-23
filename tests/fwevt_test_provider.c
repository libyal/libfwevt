/*
 * Library provider type test program
 *
 * Copyright (C) 2011-2021, Joachim Metz <joachim.metz@gmail.com>
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

#include "../libfwevt/libfwevt_provider.h"

uint8_t fwevt_test_provider_identifier_data1[ 16 ] = {
	0x25, 0x96, 0x84, 0x54, 0x78, 0x54, 0x94, 0x49, 0xa5, 0xba, 0x3e, 0x3b, 0x03, 0x28, 0xc3, 0x0d };

uint8_t fwevt_test_provider_data1[ 32 ] = {
	0x57, 0x45, 0x56, 0x54, 0x2c, 0x5b, 0x05, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

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

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "number_of_channels",
		 number_of_channels,
		 0 );

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

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "number_of_events",
		 number_of_events,
		 0 );

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

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "number_of_keywords",
		 number_of_keywords,
		 0 );

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

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "number_of_levels",
		 number_of_levels,
		 0 );

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

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "number_of_maps",
		 number_of_maps,
		 0 );

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

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "number_of_opcodes",
		 number_of_opcodes,
		 0 );

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

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "number_of_tasks",
		 number_of_tasks,
		 0 );

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

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "number_of_templates",
		 number_of_templates,
		 0 );

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

	/* TODO: add tests for libfwevt_provider_get_event_by_identifier */

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
		libfwevt_provider_free(
		 &provider,
		 NULL );
	}
#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	return( EXIT_FAILURE );
}

