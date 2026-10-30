/*
 * OSS-Fuzz target for libfwevt template type
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

#include <stdlib.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libfwevt.h"

static const int codepages[ 3 ] = {
	1252,
	932,
	65001
};

static const size_t max_string_size = 8 * 1024 * 1024;

static int fuzzer_read_template(
     const uint8_t *data,
     size_t size,
     int ascii_codepage )
{
	libfwevt_template_item_t *item        = NULL;
	libfwevt_template_t *wevt_template    = NULL;
	libfwevt_xml_document_t *xml_document = NULL;
	uint8_t *utf8_name                    = NULL;
	uint8_t *utf8_string                  = NULL;
	uint8_t guid_data[ 16 ]               = { 0 };
	uint8_t input_data_type               = 0;
	size_t utf8_name_size                 = 0;
	size_t utf8_string_size               = 0;
	int number_of_items                   = 0;

	if( libfwevt_template_initialize(
	     &wevt_template,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libfwevt_template_set_ascii_codepage(
	     wevt_template,
	     ascii_codepage,
	     NULL ) != 1 )
	{
		goto on_error;
	}
	if( libfwevt_template_read(
	     wevt_template,
	     data,
	     size,
	     0,
	     NULL ) != 1 )
	{
		goto on_error;
	}
	if( libfwevt_xml_document_initialize(
	     &xml_document,
	     NULL ) == 1 )
	{
		if( libfwevt_template_read_xml_document(
		     wevt_template,
		     xml_document,
		     NULL ) == 1 )
		{
			if( libfwevt_xml_document_get_utf8_xml_string_size(
			     xml_document,
			     &utf8_string_size,
			     NULL ) == 1
			 && ( utf8_string_size > 0 )
			 && ( utf8_string_size < max_string_size ) )
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
		}
	}
	if( libfwevt_template_get_number_of_items(
	     wevt_template,
	     &number_of_items,
	     NULL ) == 1
	 && ( number_of_items > 0 ) )
	{
		if( libfwevt_template_get_item_by_index(
		     wevt_template,
		     0,
		     &item,
		     NULL ) == 1 )
		{
			libfwevt_template_item_get_input_data_type(
			 item,
			 &input_data_type,
			 NULL );

			if( libfwevt_template_item_get_utf8_name_size(
			     item,
			     &utf8_name_size,
			     NULL ) == 1
			 && ( utf8_name_size > 0 )
			 && ( utf8_name_size < max_string_size ) )
			{
				utf8_name = (uint8_t *) malloc( utf8_name_size );

				if( utf8_name != NULL )
				{
					libfwevt_template_item_get_utf8_name(
					 item,
					 utf8_name,
					 utf8_name_size,
					 NULL );
					free( utf8_name );

					utf8_name = NULL;
				}
			}
		}
	}
	libfwevt_template_get_identifier(
	 wevt_template,
	 guid_data,
	 16,
	 NULL );

on_error:
	if( utf8_string != NULL )
	{
		free( utf8_string );
	}
	if( utf8_name != NULL )
	{
		free( utf8_name );
	}
	if( xml_document != NULL )
	{
		libfwevt_xml_document_free(
		 &xml_document,
		 NULL );
	}
	if( wevt_template != NULL )
	{
		libfwevt_template_free(
		 &wevt_template,
		 NULL );
	}
	return( 0 );
}

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	size_t codepage_index = 0;

	/* Note the template read function can only be applied once
	 * therefore a separate template instance is used per codepage
	 */
	for( codepage_index = 0;
	     codepage_index < ( sizeof( codepages ) / sizeof( codepages[ 0 ] ) );
	     codepage_index++ )
	{
		fuzzer_read_template(
		 data,
		 size,
		 codepages[ codepage_index ] );
	}
	return( 0 );
}

} /* extern "C" */
