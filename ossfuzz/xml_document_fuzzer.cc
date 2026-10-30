/*
 * OSS-Fuzz target for libfwevt xml_document type
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

#include <stddef.h>
#include <stdint.h>

#include <limits.h>
#include <stdlib.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libfwevt.h"

#define MAXIMUM_STRING_SIZE	8 * 1024 * 1024

static const int test_codepages[ 3 ] = {
	1252,
	932,
	65001
};

static const uint8_t test_flags[ 3 ] = {
	LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS,
	LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS | LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DEPENDENCY_IDENTIFIERS,
	0
};

static int fuzzer_read_xml_document(
     const uint8_t *data,
     size_t size,
     size_t binary_data_offset,
     int ascii_codepage,
     uint8_t flags )
{
	libfwevt_xml_document_t *xml_document = NULL;
	libfwevt_xml_tag_t *root_xml_tag      = NULL;
	uint16_t *utf16_string                = NULL;
	uint8_t *utf8_name                    = NULL;
	uint8_t *utf8_string                  = NULL;
	size_t utf8_name_size                 = 0;
	size_t utf8_string_size               = 0;
	size_t utf16_string_size              = 0;
	int result                            = 0;

	if( libfwevt_xml_document_initialize(
	     &xml_document,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	libfwevt_xml_document_read(
	 xml_document,
	 data,
	 size,
	 binary_data_offset,
	 ascii_codepage,
	 flags,
	 NULL );

	result = libfwevt_xml_document_get_utf8_xml_string_size(
	          xml_document,
	          &utf8_string_size,
	          NULL );

	if( ( result == 1 )
	 && ( utf8_string_size > 0 )
	 && ( utf8_string_size < MAXIMUM_STRING_SIZE ) )
	{
		utf8_string = (uint8_t *) malloc( utf8_string_size );

		if( utf8_string != NULL )
		{
			libfwevt_xml_document_get_utf8_xml_string(
			 xml_document,
			 utf8_string,
			 utf8_string_size,
			 NULL );

			free( utf8_string );

			utf8_string = NULL;
		}
	}
	result = libfwevt_xml_document_get_utf16_xml_string_size(
	          xml_document,
	          &utf16_string_size,
	          NULL );

	if( ( result == 1 )
	 && ( utf16_string_size > 0 )
	 && ( utf16_string_size < MAXIMUM_STRING_SIZE ) )
	{
		/* Note the string size is measured in UTF-16 characters (uint16_t values)
		 * the buffer must be large enough in bytes to hold them
		 */
		utf16_string = (uint16_t *) malloc( utf16_string_size * sizeof( uint16_t ) );

		if( utf16_string != NULL )
		{
			libfwevt_xml_document_get_utf16_xml_string(
			 xml_document,
			 utf16_string,
			 utf16_string_size,
			 NULL );

			free( utf16_string );

			utf16_string = NULL;
		}
	}
	if( libfwevt_xml_document_get_root_xml_tag(
	     xml_document,
	     &root_xml_tag,
	     NULL ) == 1 )
	{
		result = libfwevt_xml_tag_get_utf8_name_size(
		          root_xml_tag,
		          &utf8_name_size,
		          NULL );

		if( ( result == 1 )
		 && ( utf8_name_size > 0 )
		 && ( utf8_name_size < MAXIMUM_STRING_SIZE ) )
		{
			utf8_name = (uint8_t *) malloc( utf8_name_size );

			if( utf8_name != NULL )
			{
				libfwevt_xml_tag_get_utf8_name(
				 root_xml_tag,
				 utf8_name,
				 utf8_name_size,
				 NULL );

				free( utf8_name );

				utf8_name = NULL;
			}
		}
	}
	if( utf8_name != NULL )
	{
		free( utf8_name );
	}
	if( utf16_string != NULL )
	{
		free( utf16_string );
	}
	if( utf8_string != NULL )
	{
		free( utf8_string );
	}
	libfwevt_xml_document_free(
	 &xml_document,
	 NULL );

	return( 0 );
}

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	size_t binary_data_offset  = 0;
	size_t test_codepage_index = 0;
	size_t test_flags_index    = 0;

	/* A binary XML document starts with a fragment header token.
	 * In some test vectors the document is located at a non-zero
	 * offset within the data, e.g. when the binary XML document
	 * is part of a template, so look for the first fragment header
	 * token.
	 */
	if( ( size > 0 )
	 && ( ( data[ 0 ] & 0xbf ) != LIBFWEVT_XML_TOKEN_FRAGMENT_HEADER ) )
	{
		for( binary_data_offset = 1;
		     binary_data_offset < size;
		     binary_data_offset++ )
		{
			if( ( data[ binary_data_offset ] & 0xbf ) == LIBFWEVT_XML_TOKEN_FRAGMENT_HEADER )
			{
				break;
			}
		}
		if( binary_data_offset >= size )
		{
			binary_data_offset = 0;
		}
	}
	for( test_codepage_index = 0;
	     test_codepage_index < ( sizeof( test_codepages ) / sizeof( test_codepages[ 0 ] ) );
	     test_codepage_index++ )
	{
		for( test_flags_index = 0;
		     test_flags_index < ( sizeof( test_flags ) / sizeof( test_flags[ 0 ] ) );
		     test_flags_index++ )
		{
			fuzzer_read_xml_document(
			 data,
			 size,
			 binary_data_offset,
			 test_codepages[ test_codepage_index ],
			 test_flags[ test_flags_index ] );
		}
	}
	return( 0 );
}

} /* extern "C" */
