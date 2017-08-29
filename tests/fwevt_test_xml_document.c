/*
 * Library xml_document type test program
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

#include "../libfwevt/libfwevt_xml_tag.h"

/* Tests the libfwevt_xml_document_initialize function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_document_initialize(
     void )
{
	libcerror_error_t *error              = NULL;
	libfwevt_xml_document_t *xml_document = NULL;
	int result                            = 0;

#if defined( HAVE_FWEVT_TEST_MEMORY )
	int number_of_malloc_fail_tests       = 1;
	int number_of_memset_fail_tests       = 1;
	int test_number                       = 0;
#endif

	/* Test regular cases
	 */
	result = libfwevt_xml_document_initialize(
	          &xml_document,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_document",
	 xml_document );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_document_free(
	          &xml_document,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "xml_document",
	 xml_document );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_xml_document_initialize(
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

	xml_document = (libfwevt_xml_document_t *) 0x12345678UL;

	result = libfwevt_xml_document_initialize(
	          &xml_document,
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

	xml_document = NULL;

#if defined( HAVE_FWEVT_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfwevt_xml_document_initialize with malloc failing
		 */
		fwevt_test_malloc_attempts_before_fail = test_number;

		result = libfwevt_xml_document_initialize(
		          &xml_document,
		          &error );

		if( fwevt_test_malloc_attempts_before_fail != -1 )
		{
			fwevt_test_malloc_attempts_before_fail = -1;

			if( xml_document != NULL )
			{
				libfwevt_xml_document_free(
				 &xml_document,
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
			 "xml_document",
			 xml_document );

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
		/* Test libfwevt_xml_document_initialize with memset failing
		 */
		fwevt_test_memset_attempts_before_fail = test_number;

		result = libfwevt_xml_document_initialize(
		          &xml_document,
		          &error );

		if( fwevt_test_memset_attempts_before_fail != -1 )
		{
			fwevt_test_memset_attempts_before_fail = -1;

			if( xml_document != NULL )
			{
				libfwevt_xml_document_free(
				 &xml_document,
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
			 "xml_document",
			 xml_document );

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
	if( xml_document != NULL )
	{
		libfwevt_xml_document_free(
		 &xml_document,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_document_free function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_document_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfwevt_xml_document_free(
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

/* Tests the libfwevt_xml_document_clone function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_document_clone(
     void )
{
	libcerror_error_t *error                          = NULL;
	libfwevt_xml_document_t *destination_xml_document = NULL;
	libfwevt_xml_document_t *source_xml_document      = NULL;
	int result                                        = 0;

	/* Initialize test
	 */
	result = libfwevt_xml_document_initialize(
	          &source_xml_document,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "source_xml_document",
	 source_xml_document );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_xml_document_clone(
	          &destination_xml_document,
	          source_xml_document,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "destination_xml_document",
	 destination_xml_document );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_document_free(
	          &destination_xml_document,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "destination_xml_document",
	 destination_xml_document );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwevt_xml_document_clone(
	          &destination_xml_document,
	          NULL,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "destination_xml_document",
	 destination_xml_document );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwevt_xml_document_clone(
	          NULL,
	          source_xml_document,
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
	result = libfwevt_xml_document_free(
	          &source_xml_document,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "source_xml_document",
	 source_xml_document );

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
	if( destination_xml_document != NULL )
	{
		libfwevt_xml_document_free(
		 &destination_xml_document,
		 NULL );
	}
	if( source_xml_document != NULL )
	{
		libfwevt_xml_document_free(
		 &source_xml_document,
		 NULL );
	}
	return( 0 );
}

#if !defined( LIBFWEVT_DLL_IMPORT )

/* Tests the libfwevt_xml_document_get_root_xml_tag function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_document_get_root_xml_tag(
     void )
{
	libcerror_error_t *error              = NULL;
	libfwevt_xml_document_t *xml_document = NULL;
	libfwevt_xml_tag_t *root_xml_tag      = 0;
	int result                            = 0;
	int root_xml_tag_is_set               = 0;

	/* Initialize test
	 */
	result = libfwevt_xml_document_initialize(
	          &xml_document,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_document",
	 xml_document );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_xml_document_get_root_xml_tag(
	          xml_document,
	          &root_xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	root_xml_tag_is_set = result;

	if( root_xml_tag_is_set != 0 )
	{
		FWEVT_TEST_ASSERT_IS_NOT_NULL(
		 "root_xml_tag",
		 root_xml_tag );

		result = libfwevt_xml_tag_free(
		          &root_xml_tag,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libfwevt_xml_document_get_root_xml_tag(
	          NULL,
	          &root_xml_tag,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "root_xml_tag",
	 root_xml_tag );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( root_xml_tag_is_set != 0 )
	{
		result = libfwevt_xml_document_get_root_xml_tag(
		          xml_document,
		          NULL,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "root_xml_tag",
		 root_xml_tag );

		FWEVT_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Clean up
	 */
	result = libfwevt_xml_document_free(
	          &xml_document,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "xml_document",
	 xml_document );

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
	if( root_xml_tag != NULL )
	{
		libfwevt_xml_tag_free(
		 &root_xml_tag,
		 NULL );
	}
	if( xml_document != NULL )
	{
		libfwevt_xml_document_free(
		 &xml_document,
		 NULL );
	}
	return( 0 );
}

#endif /* !defined( LIBFWEVT_DLL_IMPORT ) */

/* Tests the libfwevt_xml_document_get_utf8_xml_string_size function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_document_get_utf8_xml_string_size(
     void )
{
	libcerror_error_t *error              = NULL;
	libfwevt_xml_document_t *xml_document = NULL;
	size_t utf8_xml_string_size           = 0;
	int result                            = 0;
	int utf8_xml_string_size_is_set       = 0;

	/* Initialize test
	 */
	result = libfwevt_xml_document_initialize(
	          &xml_document,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_document",
	 xml_document );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_xml_document_get_utf8_xml_string_size(
	          xml_document,
	          &utf8_xml_string_size,
	          &error );

	FWEVT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_xml_string_size_is_set = result;

	/* Test error cases
	 */
	result = libfwevt_xml_document_get_utf8_xml_string_size(
	          NULL,
	          &utf8_xml_string_size,
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

	if( utf8_xml_string_size_is_set != 0 )
	{
		result = libfwevt_xml_document_get_utf8_xml_string_size(
		          xml_document,
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
	result = libfwevt_xml_document_free(
	          &xml_document,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "xml_document",
	 xml_document );

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
	if( xml_document != NULL )
	{
		libfwevt_xml_document_free(
		 &xml_document,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_document_get_utf8_xml_string function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_document_get_utf8_xml_string(
     void )
{
	uint8_t utf8_xml_string[ 512 ];

	libcerror_error_t *error              = NULL;
	libfwevt_xml_document_t *xml_document = NULL;
	int result                            = 0;
	int utf8_xml_string_is_set            = 0;

	/* Initialize test
	 */
	result = libfwevt_xml_document_initialize(
	          &xml_document,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_document",
	 xml_document );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_xml_document_get_utf8_xml_string(
	          xml_document,
	          utf8_xml_string,
	          512,
	          &error );

	FWEVT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_xml_string_is_set = result;

	/* Test error cases
	 */
	result = libfwevt_xml_document_get_utf8_xml_string(
	          NULL,
	          utf8_xml_string,
	          512,
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

	if( utf8_xml_string_is_set != 0 )
	{
		result = libfwevt_xml_document_get_utf8_xml_string(
		          xml_document,
		          NULL,
		          512,
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

		result = libfwevt_xml_document_get_utf8_xml_string(
		          xml_document,
		          utf8_xml_string,
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

		result = libfwevt_xml_document_get_utf8_xml_string(
		          xml_document,
		          utf8_xml_string,
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
	}
	/* Clean up
	 */
	result = libfwevt_xml_document_free(
	          &xml_document,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "xml_document",
	 xml_document );

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
	if( xml_document != NULL )
	{
		libfwevt_xml_document_free(
		 &xml_document,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_document_get_utf16_xml_string_size function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_document_get_utf16_xml_string_size(
     void )
{
	libcerror_error_t *error              = NULL;
	libfwevt_xml_document_t *xml_document = NULL;
	size_t utf16_xml_string_size          = 0;
	int result                            = 0;
	int utf16_xml_string_size_is_set      = 0;

	/* Initialize test
	 */
	result = libfwevt_xml_document_initialize(
	          &xml_document,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_document",
	 xml_document );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_xml_document_get_utf16_xml_string_size(
	          xml_document,
	          &utf16_xml_string_size,
	          &error );

	FWEVT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_xml_string_size_is_set = result;

	/* Test error cases
	 */
	result = libfwevt_xml_document_get_utf16_xml_string_size(
	          NULL,
	          &utf16_xml_string_size,
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

	if( utf16_xml_string_size_is_set != 0 )
	{
		result = libfwevt_xml_document_get_utf16_xml_string_size(
		          xml_document,
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
	result = libfwevt_xml_document_free(
	          &xml_document,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "xml_document",
	 xml_document );

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
	if( xml_document != NULL )
	{
		libfwevt_xml_document_free(
		 &xml_document,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwevt_xml_document_get_utf16_xml_string function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_document_get_utf16_xml_string(
     void )
{
	uint16_t utf16_xml_string[ 512 ];

	libcerror_error_t *error              = NULL;
	libfwevt_xml_document_t *xml_document = NULL;
	int result                            = 0;
	int utf16_xml_string_is_set           = 0;

	/* Initialize test
	 */
	result = libfwevt_xml_document_initialize(
	          &xml_document,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "xml_document",
	 xml_document );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwevt_xml_document_get_utf16_xml_string(
	          xml_document,
	          utf16_xml_string,
	          512,
	          &error );

	FWEVT_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_xml_string_is_set = result;

	/* Test error cases
	 */
	result = libfwevt_xml_document_get_utf16_xml_string(
	          NULL,
	          utf16_xml_string,
	          512,
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

	if( utf16_xml_string_is_set != 0 )
	{
		result = libfwevt_xml_document_get_utf16_xml_string(
		          xml_document,
		          NULL,
		          512,
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

		result = libfwevt_xml_document_get_utf16_xml_string(
		          xml_document,
		          utf16_xml_string,
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

		result = libfwevt_xml_document_get_utf16_xml_string(
		          xml_document,
		          utf16_xml_string,
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
	}
	/* Clean up
	 */
	result = libfwevt_xml_document_free(
	          &xml_document,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "xml_document",
	 xml_document );

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
	if( xml_document != NULL )
	{
		libfwevt_xml_document_free(
		 &xml_document,
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
	 "libfwevt_xml_document_initialize",
	 fwevt_test_xml_document_initialize );

	FWEVT_TEST_RUN(
	 "libfwevt_xml_document_free",
	 fwevt_test_xml_document_free );

#ifdef TODO

	FWEVT_TEST_RUN(
	 "libfwevt_xml_document_clone",
	 fwevt_test_xml_document_clone );

#if !defined( LIBFWEVT_DLL_IMPORT )

	FWEVT_TEST_RUN(
	 "libfwevt_xml_document_get_root_xml_tag",
	 fwevt_test_xml_document_get_root_xml_tag );

#endif /* !defined( LIBFWEVT_DLL_IMPORT ) */

	/* TODO: add tests for libfwevt_xml_document_read */

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

	/* TODO: add tests for libfwevt_xml_document_read_with_template_values */

	/* TODO: add tests for libfwevt_xml_document_read_attribute */

	/* TODO: add tests for libfwevt_xml_document_read_cdata_section */

	/* TODO: add tests for libfwevt_xml_document_read_character_reference */

	/* TODO: add tests for libfwevt_xml_document_read_element */

	/* TODO: add tests for libfwevt_xml_document_read_entity_reference */

	/* TODO: add tests for libfwevt_xml_document_read_fragment */

	/* TODO: add tests for libfwevt_xml_document_read_fragment_header */

	/* TODO: add tests for libfwevt_xml_document_read_name */

	/* TODO: add tests for libfwevt_xml_document_read_normal_substitution */

	/* TODO: add tests for libfwevt_xml_document_read_optional_substitution */

	/* TODO: add tests for libfwevt_xml_document_read_pi_data */

	/* TODO: add tests for libfwevt_xml_document_read_pi_target */

	/* TODO: add tests for libfwevt_xml_document_read_template_instance */

	/* TODO: add tests for libfwevt_xml_document_read_template_instance_values */

	/* TODO: add tests for libfwevt_xml_document_read_value */

	/* TODO: add tests for libfwevt_xml_document_substitute_template_value */

#endif /* #if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	FWEVT_TEST_RUN(
	 "libfwevt_xml_document_get_utf8_xml_string_size",
	 fwevt_test_xml_document_get_utf8_xml_string_size );

	FWEVT_TEST_RUN(
	 "libfwevt_xml_document_get_utf8_xml_string",
	 fwevt_test_xml_document_get_utf8_xml_string );

	FWEVT_TEST_RUN(
	 "libfwevt_xml_document_get_utf16_xml_string_size",
	 fwevt_test_xml_document_get_utf16_xml_string_size );

	FWEVT_TEST_RUN(
	 "libfwevt_xml_document_get_utf16_xml_string",
	 fwevt_test_xml_document_get_utf16_xml_string );

	/* TODO: add tests for libfwevt_xml_document_debug_print */

#endif /* TODO */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

