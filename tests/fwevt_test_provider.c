/*
 * Library provider type test program
 *
 * Copyright (C) 2011-2017, Joachim Metz <joachim.metz@gmail.com>
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

	/* TODO: add tests for libfwevt_provider_initialize */

	FWEVT_TEST_RUN(
	 "libfwevt_provider_free",
	 fwevt_test_provider_free );

	/* TODO: add tests for libfwevt_provider_read */

	/* TODO: add tests for libfwevt_provider_read_channels */

	/* TODO: add tests for libfwevt_provider_read_events */

	/* TODO: add tests for libfwevt_provider_read_keywords */

	/* TODO: add tests for libfwevt_provider_read_levels */

	/* TODO: add tests for libfwevt_provider_read_maps */

	/* TODO: add tests for libfwevt_provider_read_opcodes */

	/* TODO: add tests for libfwevt_provider_read_tasks */

	/* TODO: add tests for libfwevt_provider_read_templates */

	/* TODO: add tests for libfwevt_provider_compare_identifier */

	/* TODO: add tests for libfwevt_provider_get_number_of_channels */

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

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

