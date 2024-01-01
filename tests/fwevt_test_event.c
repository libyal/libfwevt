/*
 * Library event type test program
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

#include "../libfwevt/libfwevt_event.h"

uint8_t fwevt_test_event_data1[ 48 ] = {
	0x00, 0x12, 0x00, 0x0a, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
	0x00, 0x12, 0x00, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x44, 0x06, 0x05, 0x00, 0x74, 0x06, 0x05, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

/* Tests the libfwevt_event_initialize function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_event_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfwevt_event_t *event         = NULL;
	int result                      = 0;

#if defined( HAVE_FWEVT_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libfwevt_event_initialize(
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

	result = libfwevt_internal_event_free(
	          (libfwevt_internal_event_t **) &event,
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

	/* Test error cases
	 */
	result = libfwevt_event_initialize(
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

	event = (libfwevt_event_t *) 0x12345678UL;

	result = libfwevt_event_initialize(
	          &event,
	          &error );

	event = NULL;

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
		/* Test libfwevt_event_initialize with malloc failing
		 */
		fwevt_test_malloc_attempts_before_fail = test_number;

		result = libfwevt_event_initialize(
		          &event,
		          &error );

		if( fwevt_test_malloc_attempts_before_fail != -1 )
		{
			fwevt_test_malloc_attempts_before_fail = -1;

			if( event != NULL )
			{
				libfwevt_internal_event_free(
				 (libfwevt_internal_event_t **) &event,
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
			 "event",
			 event );

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
		/* Test libfwevt_event_initialize with memset failing
		 */
		fwevt_test_memset_attempts_before_fail = test_number;

		result = libfwevt_event_initialize(
		          &event,
		          &error );

		if( fwevt_test_memset_attempts_before_fail != -1 )
		{
			fwevt_test_memset_attempts_before_fail = -1;

			if( event != NULL )
			{
				libfwevt_internal_event_free(
				 (libfwevt_internal_event_t **) &event,
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
			 "event",
			 event );

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
	if( event != NULL )
	{
		libfwevt_internal_event_free(
		 (libfwevt_internal_event_t **) &event,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

/* Tests the libfwevt_event_free function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_event_free(
     void )
{
	libcerror_error_t *error = NULL;
	libfwevt_event_t *event  = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	event = (libfwevt_event_t *) 0x12345678UL;

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

	/* Test error cases
	 */
	result = libfwevt_event_free(
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

/* Tests the libfwevt_internal_event_free function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_internal_event_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfwevt_internal_event_free(
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

/* Tests the libfwevt_event_read_data function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_event_read_data(
     void )
{
	libcerror_error_t *error = NULL;
	libfwevt_event_t *event  = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libfwevt_event_initialize(
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

	/* Test regular cases
	 */
	result = libfwevt_event_read_data(
	          event,
	          fwevt_test_event_data1,
	          48,
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
	result = libfwevt_event_read_data(
	          NULL,
	          fwevt_test_event_data1,
	          48,
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

	result = libfwevt_event_read_data(
	          event,
	          NULL,
	          48,
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

	result = libfwevt_event_read_data(
	          event,
	          fwevt_test_event_data1,
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
	result = libfwevt_event_read_data(
	          event,
	          fwevt_test_event_data1,
	          48,
	          48,
	          &error );

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
	result = libfwevt_event_read_data(
	          event,
	          fwevt_test_event_data1,
	          47,
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
	result = libfwevt_internal_event_free(
	          (libfwevt_internal_event_t **) &event,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( event != NULL )
	{
		libfwevt_internal_event_free(
		 (libfwevt_internal_event_t **) &event,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

/* Tests the libfwevt_event_get_identifier function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_event_get_identifier(
     libfwevt_event_t *event )
{
	libcerror_error_t *error = NULL;
	uint32_t identifier      = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_event_get_identifier(
	          event,
	          &identifier,
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
	result = libfwevt_event_get_identifier(
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

	result = libfwevt_event_get_identifier(
	          event,
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

/* Tests the libfwevt_event_get_message_identifier function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_event_get_message_identifier(
     libfwevt_event_t *event )
{
	libcerror_error_t *error    = NULL;
	uint32_t message_identifier = 0;
	int result                  = 0;

	/* Test regular cases
	 */
	result = libfwevt_event_get_message_identifier(
	          event,
	          &message_identifier,
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
	result = libfwevt_event_get_message_identifier(
	          NULL,
	          &message_identifier,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_event_get_message_identifier(
	          event,
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

/* Tests the libfwevt_event_get_template_offset function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_event_get_template_offset(
     libfwevt_event_t *event )
{
	libcerror_error_t *error = NULL;
	uint32_t template_offset = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_event_get_template_offset(
	          event,
	          &template_offset,
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
	result = libfwevt_event_get_template_offset(
	          NULL,
	          &template_offset,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwevt_event_get_template_offset(
	          event,
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
#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

	libcerror_error_t *error = NULL;
	libfwevt_event_t *event  = NULL;
	int result               = 0;

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	FWEVT_TEST_UNREFERENCED_PARAMETER( argc )
	FWEVT_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

	FWEVT_TEST_RUN(
	 "libfwevt_event_initialize",
	 fwevt_test_event_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	FWEVT_TEST_RUN(
	 "libfwevt_event_free",
	 fwevt_test_event_free );

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

	FWEVT_TEST_RUN(
	 "libfwevt_internal_event_free",
	 fwevt_test_internal_event_free );

	FWEVT_TEST_RUN(
	 "libfwevt_event_read_data",
	 fwevt_test_event_read_data );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize event for tests
	 */
	result = libfwevt_event_initialize(
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

	result = libfwevt_event_read_data(
	          event,
	          fwevt_test_event_data1,
	          48,
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
	 "libfwevt_event_get_identifier",
	 fwevt_test_event_get_identifier,
	 event );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_event_get_message_identifier",
	 fwevt_test_event_get_message_identifier,
	 event );

	FWEVT_TEST_RUN_WITH_ARGS(
	 "libfwevt_event_get_template_offset",
	 fwevt_test_event_get_template_offset,
	 event );

	/* Clean up
	 */
	result = libfwevt_internal_event_free(
	          (libfwevt_internal_event_t **) &event,
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
	if( event != NULL )
	{
		libfwevt_internal_event_free(
		 (libfwevt_internal_event_t **) &event,
		 NULL );
	}
#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	return( EXIT_FAILURE );
}

