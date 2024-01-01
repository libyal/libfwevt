/*
 * Library task type test program
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

#include "../libfwevt/libfwevt_task.h"

uint8_t fwevt_test_task_data1[ 100 ] = {
	0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00,
	0x53, 0x00, 0x45, 0x00, 0x5f, 0x00, 0x41, 0x00, 0x44, 0x00, 0x54, 0x00, 0x5f, 0x00, 0x53, 0x00,
	0x59, 0x00, 0x53, 0x00, 0x54, 0x00, 0x45, 0x00, 0x4d, 0x00, 0x5f, 0x00, 0x53, 0x00, 0x45, 0x00,
	0x43, 0x00, 0x55, 0x00, 0x52, 0x00, 0x49, 0x00, 0x54, 0x00, 0x59, 0x00, 0x53, 0x00, 0x54, 0x00,
	0x41, 0x00, 0x54, 0x00, 0x45, 0x00, 0x43, 0x00, 0x48, 0x00, 0x41, 0x00, 0x4e, 0x00, 0x47, 0x00,
	0x45, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

/* Tests the libfwevt_task_initialize function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_task_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfwevt_task_t *task           = NULL;
	int result                      = 0;

#if defined( HAVE_FWEVT_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libfwevt_task_initialize(
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

	result = libfwevt_internal_task_free(
	          (libfwevt_internal_task_t **) &task,
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

	/* Test error cases
	 */
	result = libfwevt_task_initialize(
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

	task = (libfwevt_task_t *) 0x12345678UL;

	result = libfwevt_task_initialize(
	          &task,
	          &error );

	task = NULL;

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
		/* Test libfwevt_task_initialize with malloc failing
		 */
		fwevt_test_malloc_attempts_before_fail = test_number;

		result = libfwevt_task_initialize(
		          &task,
		          &error );

		if( fwevt_test_malloc_attempts_before_fail != -1 )
		{
			fwevt_test_malloc_attempts_before_fail = -1;

			if( task != NULL )
			{
				libfwevt_internal_task_free(
				 (libfwevt_internal_task_t **) &task,
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
			 "task",
			 task );

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
		/* Test libfwevt_task_initialize with memset failing
		 */
		fwevt_test_memset_attempts_before_fail = test_number;

		result = libfwevt_task_initialize(
		          &task,
		          &error );

		if( fwevt_test_memset_attempts_before_fail != -1 )
		{
			fwevt_test_memset_attempts_before_fail = -1;

			if( task != NULL )
			{
				libfwevt_internal_task_free(
				 (libfwevt_internal_task_t **) &task,
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
			 "task",
			 task );

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
	if( task != NULL )
	{
		libfwevt_internal_task_free(
		 (libfwevt_internal_task_t **) &task,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

/* Tests the libfwevt_task_free function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_task_free(
     void )
{
	libcerror_error_t *error = NULL;
	libfwevt_task_t *task    = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	task = (libfwevt_task_t *) 0x12345678UL;

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

	/* Test error cases
	 */
	result = libfwevt_task_free(
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

/* Tests the libfwevt_internal_task_free function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_internal_task_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfwevt_internal_task_free(
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

/* Tests the libfwevt_task_read_data function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_task_read_data(
     void )
{
	libcerror_error_t *error = NULL;
	libfwevt_task_t *task    = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libfwevt_task_initialize(
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

	/* Test regular cases
	 */
	result = libfwevt_task_read_data(
	          task,
	          fwevt_test_task_data1,
	          100,
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
	result = libfwevt_task_read_data(
	          NULL,
	          fwevt_test_task_data1,
	          100,
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

	result = libfwevt_task_read_data(
	          task,
	          NULL,
	          100,
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

	result = libfwevt_task_read_data(
	          task,
	          fwevt_test_task_data1,
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
	result = libfwevt_task_read_data(
	          task,
	          fwevt_test_task_data1,
	          100,
	          100,
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
	result = libfwevt_task_read_data(
	          task,
	          fwevt_test_task_data1,
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

	/* Test task data offset value out of bounds
	 */
	result = libfwevt_task_read_data(
	          task,
	          fwevt_test_task_data1,
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

	/* Test task data size value out of bounds
	 */
	result = libfwevt_task_read_data(
	          task,
	          fwevt_test_task_data1,
	          99,
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
	result = libfwevt_internal_task_free(
	          (libfwevt_internal_task_t **) &task,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( task != NULL )
	{
		libfwevt_internal_task_free(
		 (libfwevt_internal_task_t **) &task,
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
	 "libfwevt_task_initialize",
	 fwevt_test_task_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	FWEVT_TEST_RUN(
	 "libfwevt_task_free",
	 fwevt_test_task_free );

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

	FWEVT_TEST_RUN(
	 "libfwevt_internal_task_free",
	 fwevt_test_internal_task_free );

	FWEVT_TEST_RUN(
	 "libfwevt_task_read_data",
	 fwevt_test_task_read_data );

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

