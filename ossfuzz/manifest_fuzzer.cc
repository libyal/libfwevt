/*
 * OSS-Fuzz target for libfwevt manifest type
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

static const size_t max_string_size = 8 * 1024 * 1024;

static int fuzzer_read_channel(
     libfwevt_channel_t *channel )
{
	uint8_t *utf8_name      = NULL;
	size_t utf8_name_size   = 0;

	if( libfwevt_channel_get_utf8_name_size(
	     channel,
	     &utf8_name_size,
	     NULL ) == 1
	 && ( utf8_name_size > 0 )
	 && ( utf8_name_size < max_string_size ) )
	{
		utf8_name = (uint8_t *) malloc( utf8_name_size );

		if( utf8_name != NULL )
		{
			libfwevt_channel_get_utf8_name(
			 channel,
			 utf8_name,
			 utf8_name_size,
			 NULL );
			free( utf8_name );
		}
	}
	return( 0 );
}

static int fuzzer_read_template(
     libfwevt_template_t *wevt_template )
{
	libfwevt_template_item_t *item        = NULL;
	uint8_t input_data_type              = 0;
	int number_of_items                  = 0;

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
		}
	}
	return( 0 );
}

static int fuzzer_read_provider(
     libfwevt_provider_t *provider )
{
	libfwevt_channel_t *channel         = NULL;
	libfwevt_template_t *wevt_template  = NULL;
	int number_of_channels             = 0;
	int number_of_templates            = 0;

	if( libfwevt_provider_get_number_of_channels(
	     provider,
	     &number_of_channels,
	     NULL ) == 1
	 && ( number_of_channels > 0 ) )
	{
		if( libfwevt_provider_get_channel_by_index(
		     provider,
		     0,
		     &channel,
		     NULL ) == 1 )
		{
			fuzzer_read_channel(
			 channel );
		}
	}
	if( libfwevt_provider_get_number_of_templates(
	     provider,
	     &number_of_templates,
	     NULL ) == 1
	 && ( number_of_templates > 0 ) )
	{
		if( libfwevt_provider_get_template_by_index(
		     provider,
		     0,
		     &wevt_template,
		     NULL ) == 1 )
		{
			fuzzer_read_template(
			 wevt_template );
		}
	}
	return( 0 );
}

static int fuzzer_read_manifest(
     const uint8_t *data,
     size_t size,
     libfwevt_manifest_t *manifest )
{
	libfwevt_provider_t *provider                  = NULL;
	libfwevt_provider_t *provider_by_identifier    = NULL;
	int number_of_providers                        = 0;

	if( libfwevt_manifest_get_number_of_providers(
	     manifest,
	     &number_of_providers,
	     NULL ) == 1
	 && ( number_of_providers > 0 ) )
	{
		if( libfwevt_manifest_get_provider_by_index(
		     manifest,
		     0,
		     &provider,
		     NULL ) == 1 )
		{
			fuzzer_read_provider(
			 provider );
		}
	}
	/* Exercise the provider identifier (GUID) lookup using the first
	 * 16 bytes of the input as identifier
	 */
	if( size >= 16 )
	{
		libfwevt_manifest_get_provider_by_identifier(
		 manifest,
		 data,
		 16,
		 &provider_by_identifier,
		 NULL );
	}
	return( 0 );
}

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	libfwevt_manifest_t *manifest = NULL;

	if( libfwevt_manifest_initialize(
	     &manifest,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libfwevt_manifest_read(
	     manifest,
	     data,
	     size,
	     NULL ) == 1 )
	{
		fuzzer_read_manifest(
		 data,
		 size,
		 manifest );
	}
	libfwevt_manifest_free(
	 &manifest,
	 NULL );

	return( 0 );
}

} /* extern "C" */
