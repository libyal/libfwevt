/*
 * Library channel type test program
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

#include "../libfwevt/libfwevt_channel.h"

uint8_t fwevt_test_channel_data1[ 40 ] = {
	0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
	0x18, 0x00, 0x00, 0x00, 0x53, 0x00, 0x65, 0x00, 0x63, 0x00, 0x75, 0x00, 0x72, 0x00, 0x69, 0x00,
	0x74, 0x00, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

/* Tests the libfwevt_channel_initialize function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_channel_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfwevt_channel_t *channel     = NULL;
	int result                      = 0;

#if defined( HAVE_FWEVT_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libfwevt_channel_initialize(
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

	result = libfwevt_internal_channel_free(
	          (libfwevt_internal_channel_t **) &channel,
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

	/* Test error cases
	 */
	result = libfwevt_channel_initialize(
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

	channel = (libfwevt_channel_t *) 0x12345678UL;

	result = libfwevt_channel_initialize(
	          &channel,
	          &error );

	channel = NULL;

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
		/* Test libfwevt_channel_initialize with malloc failing
		 */
		fwevt_test_malloc_attempts_before_fail = test_number;

		result = libfwevt_channel_initialize(
		          &channel,
		          &error );

		if( fwevt_test_malloc_attempts_before_fail != -1 )
		{
			fwevt_test_malloc_attempts_before_fail = -1;

			if( channel != NULL )
			{
				libfwevt_internal_channel_free(
				 (libfwevt_internal_channel_t **) &channel,
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
			 "channel",
			 channel );

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
		/* Test libfwevt_channel_initialize with memset failing
		 */
		fwevt_test_memset_attempts_before_fail = test_number;

		result = libfwevt_channel_initialize(
		          &channel,
		          &error );

		if( fwevt_test_memset_attempts_before_fail != -1 )
		{
			fwevt_test_memset_attempts_before_fail = -1;

			if( channel != NULL )
			{
				libfwevt_internal_channel_free(
				 (libfwevt_internal_channel_t **) &channel,
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
			 "channel",
			 channel );

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
	if( channel != NULL )
	{
		libfwevt_internal_channel_free(
		 (libfwevt_internal_channel_t **) &channel,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

/* Tests the libfwevt_channel_free function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_channel_free(
     void )
{
	libcerror_error_t *error    = NULL;
	libfwevt_channel_t *channel = NULL;
	int result                  = 0;

	/* Test regular cases
	 */
	channel = (libfwevt_channel_t *) 0x12345678UL;

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

	/* Test error cases
	 */
	result = libfwevt_channel_free(
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

/* Tests the libfwevt_internal_channel_free function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_internal_channel_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfwevt_internal_channel_free(
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

/* Tests the libfwevt_channel_read_data function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_channel_read_data(
     void )
{
	libcerror_error_t *error    = NULL;
	libfwevt_channel_t *channel = NULL;
	int result                  = 0;

	/* Initialize test
	 */
	result = libfwevt_channel_initialize(
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

	/* Test regular cases
	 */
	result = libfwevt_channel_read_data(
	          channel,
	          fwevt_test_channel_data1,
	          40,
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
	result = libfwevt_channel_read_data(
	          NULL,
	          fwevt_test_channel_data1,
	          40,
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

	result = libfwevt_channel_read_data(
	          channel,
	          NULL,
	          40,
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

	result = libfwevt_channel_read_data(
	          channel,
	          fwevt_test_channel_data1,
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
	result = libfwevt_channel_read_data(
	          channel,
	          fwevt_test_channel_data1,
	          40,
	          40,
	          &error );

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
	result = libfwevt_channel_read_data(
	          channel,
	          fwevt_test_channel_data1,
	          15,
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

	/* Test channel data offset value out of bounds
	 */
	result = libfwevt_channel_read_data(
	          channel,
	          fwevt_test_channel_data1,
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

	/* Test channel data size value out of bounds
	 */
	result = libfwevt_channel_read_data(
	          channel,
	          fwevt_test_channel_data1,
	          39,
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
	result = libfwevt_internal_channel_free(
	          (libfwevt_internal_channel_t **) &channel,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( channel != NULL )
	{
		libfwevt_internal_channel_free(
		 (libfwevt_internal_channel_t **) &channel,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_channel_get_identifier function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_channel_get_identifier(
     libfwevt_channel_t *channel )
{
	libcerror_error_t *error = NULL;
	uint32_t identifier      = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_channel_get_identifier(
	          channel,
	          &identifier,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_UINT32(
	 "identifier",
	 identifier,
	 (uint32_t) 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_channel_get_identifier(
	          NULL,
	          &identifier,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_channel_get_identifier(
	          channel,
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

/* Tests the libfwevt_channel_get_utf8_name_size function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_channel_get_utf8_name_size(
     libfwevt_channel_t *channel )
{
	libcerror_error_t *error        = NULL;
	libfwevt_channel_t *empty_chan  = NULL;
	size_t utf8_string_size         = 0;
	int result                      = 0;

	/* Test regular cases
	 */
	result = libfwevt_channel_get_utf8_name_size(
	          channel,
	          &utf8_string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_size",
	 utf8_string_size,
	 (size_t) 9 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test empty channel (name not available)
	 */
	result = libfwevt_channel_initialize(
	          &empty_chan,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libfwevt_channel_get_utf8_name_size(
	          empty_chan,
	          &utf8_string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_internal_channel_free(
	          (libfwevt_internal_channel_t **) &empty_chan,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	/* Test error cases
	 */
	result = libfwevt_channel_get_utf8_name_size(
	          NULL,
	          &utf8_string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_channel_get_utf8_name_size(
	          channel,
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
	if( empty_chan != NULL )
	{
		libfwevt_internal_channel_free(
		 (libfwevt_internal_channel_t **) &empty_chan,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_channel_get_utf8_name function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_channel_get_utf8_name(
     libfwevt_channel_t *channel )
{
	uint8_t utf8_string[ 32 ];

	libcerror_error_t *error        = NULL;
	libfwevt_channel_t *empty_chan  = NULL;
	int result                      = 0;

	/* Test regular cases
	 */
	result = libfwevt_channel_get_utf8_name(
	          channel,
	          utf8_string,
	          32,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test empty channel (name not available)
	 */
	result = libfwevt_channel_initialize(
	          &empty_chan,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libfwevt_channel_get_utf8_name(
	          empty_chan,
	          utf8_string,
	          32,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_internal_channel_free(
	          (libfwevt_internal_channel_t **) &empty_chan,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	/* Test error cases
	 */
	result = libfwevt_channel_get_utf8_name(
	          NULL,
	          utf8_string,
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

	result = libfwevt_channel_get_utf8_name(
	          channel,
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

	result = libfwevt_channel_get_utf8_name(
	          channel,
	          utf8_string,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( empty_chan != NULL )
	{
		libfwevt_internal_channel_free(
		 (libfwevt_internal_channel_t **) &empty_chan,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_channel_get_utf16_name_size function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_channel_get_utf16_name_size(
     libfwevt_channel_t *channel )
{
	libcerror_error_t *error        = NULL;
	libfwevt_channel_t *empty_chan  = NULL;
	size_t utf16_string_size        = 0;
	int result                      = 0;

	/* Test regular cases
	 */
	result = libfwevt_channel_get_utf16_name_size(
	          channel,
	          &utf16_string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 9 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test empty channel (name not available)
	 */
	result = libfwevt_channel_initialize(
	          &empty_chan,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libfwevt_channel_get_utf16_name_size(
	          empty_chan,
	          &utf16_string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_internal_channel_free(
	          (libfwevt_internal_channel_t **) &empty_chan,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	/* Test error cases
	 */
	result = libfwevt_channel_get_utf16_name_size(
	          NULL,
	          &utf16_string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_channel_get_utf16_name_size(
	          channel,
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
	if( empty_chan != NULL )
	{
		libfwevt_internal_channel_free(
		 (libfwevt_internal_channel_t **) &empty_chan,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_channel_get_utf16_name function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_channel_get_utf16_name(
     libfwevt_channel_t *channel )
{
	uint16_t utf16_string[ 32 ];

	libcerror_error_t *error        = NULL;
	libfwevt_channel_t *empty_chan  = NULL;
	int result                      = 0;

	/* Test regular cases
	 */
	result = libfwevt_channel_get_utf16_name(
	          channel,
	          utf16_string,
	          32,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test empty channel (name not available)
	 */
	result = libfwevt_channel_initialize(
	          &empty_chan,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libfwevt_channel_get_utf16_name(
	          empty_chan,
	          utf16_string,
	          32,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_internal_channel_free(
	          (libfwevt_internal_channel_t **) &empty_chan,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	/* Test error cases
	 */
	result = libfwevt_channel_get_utf16_name(
	          NULL,
	          utf16_string,
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

	result = libfwevt_channel_get_utf16_name(
	          channel,
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

	result = libfwevt_channel_get_utf16_name(
	          channel,
	          utf16_string,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( empty_chan != NULL )
	{
		libfwevt_internal_channel_free(
		 (libfwevt_internal_channel_t **) &empty_chan,
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
#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )
	libcerror_error_t *error    = NULL;
	libfwevt_channel_t *channel = NULL;
	int result                  = 0;
#endif

	FWEVT_TEST_UNREFERENCED_PARAMETER( argc )
	FWEVT_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

	FWEVT_TEST_RUN(
	 "libfwevt_channel_initialize",
	 fwevt_test_channel_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	FWEVT_TEST_RUN(
	 "libfwevt_channel_free",
	 fwevt_test_channel_free );

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

	FWEVT_TEST_RUN(
	 "libfwevt_internal_channel_free",
	 fwevt_test_internal_channel_free );

	FWEVT_TEST_RUN(
	 "libfwevt_channel_read_data",
	 fwevt_test_channel_read_data );

	/* Set up channel for getter tests
	 */
	result = libfwevt_channel_initialize(
	          &channel,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libfwevt_channel_read_data(
	          channel,
	          fwevt_test_channel_data1,
	          40,
	          0,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_channel_get_identifier",
	 fwevt_test_channel_get_identifier,
	 channel );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_channel_get_utf8_name_size",
	 fwevt_test_channel_get_utf8_name_size,
	 channel );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_channel_get_utf8_name",
	 fwevt_test_channel_get_utf8_name,
	 channel );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_channel_get_utf16_name_size",
	 fwevt_test_channel_get_utf16_name_size,
	 channel );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_channel_get_utf16_name",
	 fwevt_test_channel_get_utf16_name,
	 channel );

	result = libfwevt_internal_channel_free(
	          (libfwevt_internal_channel_t **) &channel,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( channel != NULL )
	{
		libfwevt_internal_channel_free(
		 (libfwevt_internal_channel_t **) &channel,
		 NULL );
	}
#endif
	return( EXIT_FAILURE );
}

