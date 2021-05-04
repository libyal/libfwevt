/*
 * Library xml_document type test program
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
#include "fwevt_test_libuna.h"
#include "fwevt_test_macros.h"
#include "fwevt_test_memory.h"
#include "fwevt_test_unused.h"

#include "../libfwevt/libfwevt_xml_tag.h"

unsigned char fwevt_test_xml_document_data1[ 1236 ] = {
	0x0f, 0x01, 0x01, 0x00, 0x0c, 0x01, 0x28, 0xc0, 0x01, 0x0a, 0x26, 0x02, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x28, 0xc0, 0x01, 0x0a, 0x21, 0x39, 0x4f, 0xd0, 0x7d, 0x1d, 0xfe, 0x9d, 0xab, 0xda,
	0x32, 0x45, 0x4b, 0x03, 0x00, 0x00, 0x0f, 0x01, 0x01, 0x00, 0x41, 0x13, 0x00, 0x3f, 0x03, 0x00,
	0x00, 0x4d, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xba, 0x0c, 0x05, 0x00, 0x45, 0x00, 0x76,
	0x00, 0x65, 0x00, 0x6e, 0x00, 0x74, 0x00, 0x00, 0x00, 0x87, 0x00, 0x00, 0x00, 0x06, 0x6a, 0x02,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbc, 0x0f, 0x05, 0x00, 0x78, 0x00, 0x6d, 0x00, 0x6c, 0x00,
	0x6e, 0x00, 0x73, 0x00, 0x00, 0x00, 0x05, 0x01, 0x35, 0x00, 0x68, 0x00, 0x74, 0x00, 0x74, 0x00,
	0x70, 0x00, 0x3a, 0x00, 0x2f, 0x00, 0x2f, 0x00, 0x73, 0x00, 0x63, 0x00, 0x68, 0x00, 0x65, 0x00,
	0x6d, 0x00, 0x61, 0x00, 0x73, 0x00, 0x2e, 0x00, 0x6d, 0x00, 0x69, 0x00, 0x63, 0x00, 0x72, 0x00,
	0x6f, 0x00, 0x73, 0x00, 0x6f, 0x00, 0x66, 0x00, 0x74, 0x00, 0x2e, 0x00, 0x63, 0x00, 0x6f, 0x00,
	0x6d, 0x00, 0x2f, 0x00, 0x77, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x2f, 0x00, 0x32, 0x00, 0x30, 0x00,
	0x30, 0x00, 0x34, 0x00, 0x2f, 0x00, 0x30, 0x00, 0x38, 0x00, 0x2f, 0x00, 0x65, 0x00, 0x76, 0x00,
	0x65, 0x00, 0x6e, 0x00, 0x74, 0x00, 0x73, 0x00, 0x2f, 0x00, 0x65, 0x00, 0x76, 0x00, 0x65, 0x00,
	0x6e, 0x00, 0x74, 0x00, 0x02, 0x01, 0xff, 0xff, 0x8f, 0x02, 0x00, 0x00, 0xf8, 0x02, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x6f, 0x54, 0x06, 0x00, 0x53, 0x00, 0x79, 0x00, 0x73, 0x00, 0x74, 0x00,
	0x65, 0x00, 0x6d, 0x00, 0x00, 0x00, 0x02, 0x41, 0xff, 0xff, 0x48, 0x00, 0x00, 0x00, 0x1a, 0x03,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf1, 0x7b, 0x08, 0x00, 0x50, 0x00, 0x72, 0x00, 0x6f, 0x00,
	0x76, 0x00, 0x69, 0x00, 0x64, 0x00, 0x65, 0x00, 0x72, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00,
	0x06, 0x3d, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4b, 0x95, 0x04, 0x00, 0x4e, 0x00, 0x61,
	0x00, 0x6d, 0x00, 0x65, 0x00, 0x00, 0x00, 0x05, 0x01, 0x05, 0x00, 0x45, 0x00, 0x53, 0x00, 0x45,
	0x00, 0x4e, 0x00, 0x54, 0x00, 0x03, 0x41, 0x03, 0x00, 0x4d, 0x00, 0x00, 0x00, 0x69, 0x03, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xf5, 0x61, 0x07, 0x00, 0x45, 0x00, 0x76, 0x00, 0x65, 0x00, 0x6e,
	0x00, 0x74, 0x00, 0x49, 0x00, 0x44, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x06, 0x8a, 0x03,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0xda, 0x0a, 0x00, 0x51, 0x00, 0x75, 0x00, 0x61, 0x00,
	0x6c, 0x00, 0x69, 0x00, 0x66, 0x00, 0x69, 0x00, 0x65, 0x00, 0x72, 0x00, 0x73, 0x00, 0x00, 0x00,
	0x0e, 0x04, 0x00, 0x06, 0x02, 0x0e, 0x03, 0x00, 0x06, 0x04, 0x01, 0x00, 0x00, 0x1e, 0x00, 0x00,
	0x00, 0xbd, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0xce, 0x05, 0x00, 0x4c, 0x00, 0x65,
	0x00, 0x76, 0x00, 0x65, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x00, 0x00, 0x04, 0x04, 0x01,
	0x02, 0x00, 0x1c, 0x00, 0x00, 0x00, 0xe2, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x45, 0x7b,
	0x04, 0x00, 0x54, 0x00, 0x61, 0x00, 0x73, 0x00, 0x6b, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x02, 0x00,
	0x06, 0x04, 0x01, 0x05, 0x00, 0x24, 0x00, 0x00, 0x00, 0x05, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x6a, 0xcf, 0x08, 0x00, 0x4b, 0x00, 0x65, 0x00, 0x79, 0x00, 0x77, 0x00, 0x6f, 0x00, 0x72,
	0x00, 0x64, 0x00, 0x73, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x05, 0x00, 0x15, 0x04, 0x41, 0xff, 0xff,
	0x50, 0x00, 0x00, 0x00, 0x30, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3b, 0x8e, 0x0b, 0x00,
	0x54, 0x00, 0x69, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x43, 0x00, 0x72, 0x00, 0x65, 0x00, 0x61, 0x00,
	0x74, 0x00, 0x65, 0x00, 0x64, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x06, 0x59, 0x04, 0x00,
	0x00, 0x6a, 0x02, 0x00, 0x00, 0x3c, 0x7b, 0x0a, 0x00, 0x53, 0x00, 0x79, 0x00, 0x73, 0x00, 0x74,
	0x00, 0x65, 0x00, 0x6d, 0x00, 0x54, 0x00, 0x69, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x00, 0x00, 0x0e,
	0x06, 0x00, 0x11, 0x03, 0x01, 0x0a, 0x00, 0x2e, 0x00, 0x00, 0x00, 0x87, 0x04, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x46, 0x03, 0x0d, 0x00, 0x45, 0x00, 0x76, 0x00, 0x65, 0x00, 0x6e, 0x00, 0x74,
	0x00, 0x52, 0x00, 0x65, 0x00, 0x63, 0x00, 0x6f, 0x00, 0x72, 0x00, 0x64, 0x00, 0x49, 0x00, 0x44,
	0x00, 0x00, 0x00, 0x02, 0x0e, 0x0a, 0x00, 0x0a, 0x04, 0x01, 0xff, 0xff, 0x38, 0x00, 0x00, 0x00,
	0xbc, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0x61, 0x07, 0x00, 0x43, 0x00, 0x68, 0x00,
	0x61, 0x00, 0x6e, 0x00, 0x6e, 0x00, 0x65, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x02, 0x05, 0x01, 0x0b,
	0x00, 0x41, 0x00, 0x70, 0x00, 0x70, 0x00, 0x6c, 0x00, 0x69, 0x00, 0x63, 0x00, 0x61, 0x00, 0x74,
	0x00, 0x69, 0x00, 0x6f, 0x00, 0x6e, 0x00, 0x04, 0x01, 0xff, 0xff, 0x42, 0x00, 0x00, 0x00, 0xfb,
	0x04, 0x00, 0x00, 0x30, 0x04, 0x00, 0x00, 0x3b, 0x6e, 0x08, 0x00, 0x43, 0x00, 0x6f, 0x00, 0x6d,
	0x00, 0x70, 0x00, 0x75, 0x00, 0x74, 0x00, 0x65, 0x00, 0x72, 0x00, 0x00, 0x00, 0x02, 0x05, 0x01,
	0x0f, 0x00, 0x57, 0x00, 0x49, 0x00, 0x4e, 0x00, 0x2d, 0x00, 0x33, 0x00, 0x51, 0x00, 0x4d, 0x00,
	0x44, 0x00, 0x4a, 0x00, 0x47, 0x00, 0x4b, 0x00, 0x46, 0x00, 0x33, 0x00, 0x47, 0x00, 0x39, 0x00,
	0x04, 0x41, 0xff, 0xff, 0x42, 0x00, 0x00, 0x00, 0x44, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xa0, 0x2e, 0x08, 0x00, 0x53, 0x00, 0x65, 0x00, 0x63, 0x00, 0x75, 0x00, 0x72, 0x00, 0x69, 0x00,
	0x74, 0x00, 0x79, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x06, 0x67, 0x05, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x66, 0x4c, 0x06, 0x00, 0x55, 0x00, 0x73, 0x00, 0x65, 0x00, 0x72, 0x00, 0x49,
	0x00, 0x44, 0x00, 0x00, 0x00, 0x0e, 0x0c, 0x00, 0x13, 0x03, 0x04, 0x0e, 0x13, 0x00, 0x21, 0x04,
	0x00, 0x14, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x01, 0x00, 0x04, 0x00, 0x02, 0x00, 0x06,
	0x00, 0x02, 0x00, 0x06, 0x00, 0x02, 0x00, 0x06, 0x00, 0x08, 0x00, 0x15, 0x00, 0x08, 0x00, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00, 0x04, 0x00, 0x08, 0x00, 0x08, 0x00, 0x0a,
	0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xe5, 0x00, 0x21, 0x00, 0x04, 0x00, 0x01, 0x00, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x8d, 0x48, 0xa1, 0x2c, 0xa1, 0xca, 0x01, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x7a, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x01,
	0x01, 0x00, 0x0c, 0x01, 0x01, 0x46, 0xd3, 0xec, 0x14, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x46, 0xd3, 0xec, 0x25, 0x02, 0x67, 0x3e, 0xb6, 0x39, 0xd7, 0x7b, 0x70, 0x28, 0x1c, 0xe9,
	0x78, 0x00, 0x00, 0x00, 0x0f, 0x01, 0x01, 0x00, 0x01, 0xff, 0xff, 0x6c, 0x00, 0x00, 0x00, 0x3b,
	0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x82, 0x09, 0x00, 0x45, 0x00, 0x76, 0x00, 0x65,
	0x00, 0x6e, 0x00, 0x74, 0x00, 0x44, 0x00, 0x61, 0x00, 0x74, 0x00, 0x61, 0x00, 0x00, 0x00, 0x02,
	0x01, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x63, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8a,
	0x6f, 0x04, 0x00, 0x44, 0x00, 0x61, 0x00, 0x74, 0x00, 0x61, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x00,
	0x00, 0x81, 0x04, 0x01, 0x02, 0x00, 0x20, 0x00, 0x00, 0x00, 0x86, 0x06, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x21, 0xb8, 0x06, 0x00, 0x42, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x61, 0x00, 0x72, 0x00,
	0x79, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x02, 0x00, 0x0e, 0x04, 0x04, 0x00, 0x03, 0x00, 0x00, 0x00,
	0x32, 0x00, 0x81, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x00, 0x69, 0x00,
	0x6e, 0x00, 0x64, 0x00, 0x6f, 0x00, 0x77, 0x00, 0x73, 0x00, 0x00, 0x00, 0x32, 0x00, 0x31, 0x00,
	0x32, 0x00, 0x34, 0x00, 0x00, 0x00, 0x57, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x64, 0x00, 0x6f, 0x00,
	0x77, 0x00, 0x73, 0x00, 0x3a, 0x00, 0x20, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00 };

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

	xml_document = NULL;

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

/* Tests the libfwevt_xml_document_read function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_xml_document_read(
     void )
{
	libcerror_error_t *error              = NULL;
	libfwevt_xml_document_t *xml_document = NULL;
	int result                            = 0;

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
	result = libfwevt_xml_document_read(
	          xml_document,
	          fwevt_test_xml_document_data1,
	          1236,
	          0,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS | LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS,
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
	result = libfwevt_xml_document_read(
	          NULL,
	          fwevt_test_xml_document_data1,
	          1236,
	          0,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS | LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS,
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

	result = libfwevt_xml_document_read(
	          xml_document,
	          NULL,
	          1236,
	          0,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS | LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS,
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

	result = libfwevt_xml_document_read(
	          xml_document,
	          fwevt_test_xml_document_data1,
	          (size_t) SSIZE_MAX + 1,
	          0,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS | LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS,
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
	result = libfwevt_xml_document_read(
	          xml_document,
	          fwevt_test_xml_document_data1,
	          1236,
	          1236,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS | LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS,
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
	result = libfwevt_xml_document_read(
	          xml_document,
	          fwevt_test_xml_document_data1,
	          11,
	          0,
	          LIBUNA_CODEPAGE_WINDOWS_1252,
	          LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS | LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS,
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

	FWEVT_TEST_RUN(
	 "libfwevt_xml_document_read",
	 fwevt_test_xml_document_read );

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

