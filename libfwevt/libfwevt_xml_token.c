/*
 * Windows Event Log binary XML token functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libfwevt_definitions.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_libcnotify.h"
#include "libfwevt_xml_token.h"

/* Creats a binary XML token
 * Make sure the value xml_token is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_token_initialize(
     libfwevt_xml_token_t **xml_token,
     libcerror_error_t **error )
{
	static char *function = "libfwevt_xml_token_initialize";

	if( xml_token == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML token.",
		 function );

		return( -1 );
	}
	if( *xml_token != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid binary XML token value already set.",
		 function );

		return( -1 );
	}
	*xml_token = memory_allocate_structure(
	              libfwevt_xml_token_t );

	if( *xml_token == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create binary XML token.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *xml_token,
	     0,
	     sizeof( libfwevt_xml_token_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear binary XML token.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *xml_token != NULL )
	{
		memory_free(
		 *xml_token );

		*xml_token = NULL;
	}
	return( -1 );
}

/* Frees a binary XML token
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_token_free(
     libfwevt_xml_token_t **xml_token,
     libcerror_error_t **error )
{
	static char *function = "libfwevt_xml_token_free";
	int result            = 1;

	if( xml_token == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML token.",
		 function );

		return( -1 );
	}
	if( *xml_token != NULL )
	{
		memory_free(
		 *xml_token );

		*xml_token = NULL;
	}
	return( result );
}

/* Reads the binary XML token
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_token_read_data(
     libfwevt_xml_token_t *xml_token,
     const uint8_t *chunk_data,
     size_t chunk_data_size,
     size_t chunk_data_offset,
     libcerror_error_t **error )
{
	static char *function  = "libfwevt_xml_token_read_data";
	uint8_t xml_token_type = 0;

	if( xml_token == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML token.",
		 function );

		return( -1 );
	}
	if( chunk_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid chunk data.",
		 function );

		return( -1 );
	}
	if( chunk_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid binary XML token data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( chunk_data_offset >= chunk_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid chunk data offset value out of bounds.",
		 function );

		return( -1 );
	}
	xml_token_type = chunk_data[ chunk_data_offset ];

	switch( xml_token_type )
	{
		case LIBFWEVT_XML_TOKEN_END_OF_FILE:
		case LIBFWEVT_XML_TOKEN_CLOSE_START_ELEMENT_TAG:
		case LIBFWEVT_XML_TOKEN_CLOSE_EMPTY_ELEMENT_TAG:
		case LIBFWEVT_XML_TOKEN_END_ELEMENT_TAG:
		case LIBFWEVT_XML_TOKEN_OPEN_START_ELEMENT_TAG:
		case LIBFWEVT_XML_TOKEN_OPEN_START_ELEMENT_TAG | LIBFWEVT_XML_TOKEN_FLAG_HAS_MORE_DATA:
		case LIBFWEVT_XML_TOKEN_VALUE:
		case LIBFWEVT_XML_TOKEN_VALUE | LIBFWEVT_XML_TOKEN_FLAG_HAS_MORE_DATA:
		case LIBFWEVT_XML_TOKEN_ATTRIBUTE:
		case LIBFWEVT_XML_TOKEN_ATTRIBUTE | LIBFWEVT_XML_TOKEN_FLAG_HAS_MORE_DATA:
		case LIBFWEVT_XML_TOKEN_CDATA_SECTION:
		case LIBFWEVT_XML_TOKEN_CDATA_SECTION | LIBFWEVT_XML_TOKEN_FLAG_HAS_MORE_DATA:
		case LIBFWEVT_XML_TOKEN_CHARACTER_REFERENCE:
		case LIBFWEVT_XML_TOKEN_CHARACTER_REFERENCE | LIBFWEVT_XML_TOKEN_FLAG_HAS_MORE_DATA:
		case LIBFWEVT_XML_TOKEN_ENTITY_REFERENCE:
		case LIBFWEVT_XML_TOKEN_ENTITY_REFERENCE | LIBFWEVT_XML_TOKEN_FLAG_HAS_MORE_DATA:
		case LIBFWEVT_XML_TOKEN_PI_TARGET:
		case LIBFWEVT_XML_TOKEN_PI_DATA:
		case LIBFWEVT_XML_TOKEN_TEMPLATE_INSTANCE:
		case LIBFWEVT_XML_TOKEN_NORMAL_SUBSTITUTION:
		case LIBFWEVT_XML_TOKEN_OPTIONAL_SUBSTITUTION:
		case LIBFWEVT_XML_TOKEN_FRAGMENT_HEADER:
			break;

		default:
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported binary XML token type: 0x%02" PRIx8 ".",
			 function,
			 xml_token_type );

			return( -1 );
	}
	xml_token->type = xml_token_type;

	return( 1 );
}

