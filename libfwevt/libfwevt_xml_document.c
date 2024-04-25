/*
 * Windows Event Log binary XML document functions
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
#include <system_string.h>
#include <types.h>

#include "libfwevt_debug.h"
#include "libfwevt_definitions.h"
#include "libfwevt_libcdata.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_libcnotify.h"
#include "libfwevt_libfguid.h"
#include "libfwevt_libfvalue.h"
#include "libfwevt_types.h"
#include "libfwevt_xml_document.h"
#include "libfwevt_xml_template_value.h"
#include "libfwevt_xml_tag.h"
#include "libfwevt_xml_token.h"

/* Creates a binary XML document
 * Make sure the value xml_document is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_initialize(
     libfwevt_xml_document_t **xml_document,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_document_t *internal_xml_document = NULL;
	static char *function                                   = "libfwevt_xml_document_initialize";

	if( xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
	if( *xml_document != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid binary XML document value already set.",
		 function );

		return( -1 );
	}
	internal_xml_document = memory_allocate_structure(
	                         libfwevt_internal_xml_document_t );

	if( internal_xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create binary XML document.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_xml_document,
	     0,
	     sizeof( libfwevt_internal_xml_document_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear binary XML document.",
		 function );

		goto on_error;
	}
	*xml_document = (libfwevt_xml_document_t *) internal_xml_document;

	return( 1 );

on_error:
	if( internal_xml_document != NULL )
	{
		memory_free(
		 internal_xml_document );
	}
	return( -1 );
}

/* Frees a binary XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_free(
     libfwevt_xml_document_t **xml_document,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_document_t *internal_xml_document = NULL;
	static char *function                                   = "libfwevt_xml_document_free";
	int result                                              = 1;

	if( xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
	if( *xml_document != NULL )
	{
		internal_xml_document = (libfwevt_internal_xml_document_t *) *xml_document;
		*xml_document         = NULL;

		if( internal_xml_document->root_xml_tag != NULL )
		{
			if( libfwevt_internal_xml_tag_free(
			     (libfwevt_internal_xml_tag_t **) &( internal_xml_document->root_xml_tag ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free root XML tag.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 internal_xml_document );
	}
	return( result );
}

/* Retrieves the root XML tag
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_get_root_xml_tag(
     libfwevt_xml_document_t *xml_document,
     libfwevt_xml_tag_t **root_xml_tag,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_document_t *internal_xml_document = NULL;
	static char *function                                   = "libfwevt_xml_document_get_root_xml_tag";

	if( xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
	internal_xml_document = (libfwevt_internal_xml_document_t *) xml_document;

	if( root_xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid root XML tag.",
		 function );

		return( -1 );
	}
	*root_xml_tag = internal_xml_document->root_xml_tag;

	return( 1 );
}

/* Reads a binary XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_read(
     libfwevt_xml_document_t *xml_document,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     int ascii_codepage,
     uint8_t flags,
     libcerror_error_t **error )
{
	static char *function = "libfwevt_xml_document_read";

	if( libfwevt_xml_document_read_with_template_values(
	     xml_document,
	     binary_data,
	     binary_data_size,
	     binary_data_offset,
	     ascii_codepage,
	     flags,
	     NULL,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read XML document.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads a binary XML document with template values
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_read_with_template_values(
     libfwevt_xml_document_t *xml_document,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     int ascii_codepage,
     uint8_t flags,
     libcdata_array_t *template_values_array,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_document_t *internal_xml_document = NULL;
	libfwevt_xml_token_t *xml_token                         = NULL;
	static char *function                                   = "libfwevt_xml_document_read_with_template_values";
	uint8_t supported_flags                                 = 0;

	if( xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
	internal_xml_document = (libfwevt_internal_xml_document_t *) xml_document;

	if( internal_xml_document->root_xml_tag != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid binary XML document - root XML tag already set.",
		 function );

		return( -1 );
	}
	if( binary_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary data.",
		 function );

		return( -1 );
	}
	if( binary_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid binary XML document data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( binary_data_offset >= binary_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary data offset value out of bounds.",
		 function );

		return( -1 );
	}
	supported_flags = LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS
	                | LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DEPENDENCY_IDENTIFIERS;

	if( ( flags & ~( supported_flags ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags: 0x%02" PRIx8 ".",
		 function,
		 flags );

		return( -1 );
	}
	if( libfwevt_xml_token_initialize(
	     &xml_token,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create binary XML token.",
		 function );

		goto on_error;
	}
	while( binary_data_offset < binary_data_size )
	{
		if( libfwevt_xml_token_read_data(
		     xml_token,
		     binary_data,
		     binary_data_size,
		     binary_data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read binary XML token.",
			 function );

			goto on_error;
		}
/* TODO check for prologue */
/* TODO validate the order */
/* TODO check for Miscellaneous before end of file token */
		switch( xml_token->type & 0xbf )
		{
			case LIBFWEVT_XML_TOKEN_END_OF_FILE:
				if( ( binary_data_size < 1 )
				 || ( binary_data_offset >= ( binary_data_size - 1 ) ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: invalid binary XML document data size value too small.",
					 function );

					goto on_error;
				}
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: data offset\t\t: 0x%08" PRIzx "\n",
					 function,
					 binary_data_offset );

					libcnotify_printf(
					 "%s: end of file data:\n",
					 function );
					libcnotify_print_data(
					 &( binary_data[ binary_data_offset ] ),
					 1,
					 0 );
				}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: type\t\t\t: 0x%02" PRIx8 "\n",
					 function,
					 binary_data[ binary_data_offset ] );

					libcnotify_printf(
					 "\n" );
				}
#endif
				xml_token->size = 1;

				break;

			case LIBFWEVT_XML_TOKEN_FRAGMENT_HEADER:
				if( libfwevt_xml_document_read_fragment(
				     internal_xml_document,
				     xml_token,
				     binary_data,
				     binary_data_size,
				     binary_data_offset,
				     ascii_codepage,
				     flags,
				     template_values_array,
				     internal_xml_document->root_xml_tag,
				     0,
				     0,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read fragment header.",
					 function );

					goto on_error;
				}
				break;

			default:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: invalid binary XML token - unsupported type: 0x%02" PRIx8 ".",
				 function,
				 xml_token->type );

				goto on_error;
		}
		internal_xml_document->size += xml_token->size;
		binary_data_offset          += xml_token->size;

		if( xml_token->type == LIBFWEVT_XML_TOKEN_END_OF_FILE )
		{
			break;
		}
	}
	if( libfwevt_xml_token_free(
	     &xml_token,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free binary XML token.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( xml_token != NULL )
	{
		libfwevt_xml_token_free(
		 &xml_token,
		 NULL );
	}
	return( -1 );
}

/* Reads an attribute from a binary XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_read_attribute(
     libfwevt_internal_xml_document_t *internal_xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     int ascii_codepage,
     uint8_t flags,
     libcdata_array_t *template_values_array,
     libfwevt_xml_tag_t *xml_tag,
     int element_recursion_depth,
     int template_instance_recursion_depth,
     libcerror_error_t **error )
{
	libfwevt_xml_tag_t *attribute_xml_tag    = NULL;
	libfwevt_xml_token_t *xml_sub_token      = NULL;
	const uint8_t *xml_document_data         = NULL;
	static char *function                    = "libfwevt_xml_document_read_attribute";
	size_t additional_value_size             = 0;
	size_t template_value_offset             = 0;
	size_t trailing_data_size                = 0;
	size_t xml_document_data_offset          = 0;
	size_t xml_document_data_size            = 0;
	uint32_t attribute_name_offset           = 0;
	uint32_t attribute_name_size             = 0;
	int result                               = 0;
	int template_value_array_recursion_depth = 0;

	if( internal_xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
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
	if( ( xml_token->type & 0xbf ) != LIBFWEVT_XML_TOKEN_ATTRIBUTE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid binary XML token - unsupported type: 0x%02" PRIx8 ".",
		 function,
		 xml_token->type );

		return( -1 );
	}
	if( binary_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary data.",
		 function );

		return( -1 );
	}
	if( binary_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid binary XML document data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( binary_data_offset >= binary_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( flags & LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS ) != 0 )
	{
		additional_value_size = 4;

		if( ( binary_data_size < 4 )
		 || ( binary_data_offset > ( binary_data_size - 4 ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid binary data offset value out of bounds.",
			 function );

			return( -1 );
		}
	}
	xml_document_data      = &( binary_data[ binary_data_offset ] );
	xml_document_data_size = binary_data_size - binary_data_offset;

	if( libfwevt_xml_token_initialize(
	     &xml_sub_token,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create binary XML sub token.",
		 function );

		goto on_error;
	}
	do
	{
		if( ( template_value_array_recursion_depth < 0 )
		 || ( template_value_array_recursion_depth > LIBFWEVT_XML_DOCUMENT_TEMPLATE_VALUE_ARRAY_RECURSION_DEPTH ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid template value array recursion depth value out of bounds.",
			 function );

			goto on_error;
		}
		if( ( xml_document_data_size < ( additional_value_size + 1 ) )
		 || ( xml_document_data_offset > ( xml_document_data_size - ( additional_value_size + 1 ) ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid binary XML document data size value too small.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: data offset\t\t\t: 0x%08" PRIzx "\n",
			 function,
			 binary_data_offset + xml_document_data_offset );

			libcnotify_printf(
			 "%s: attribute data:\n",
			 function );
			libcnotify_print_data(
			 &( xml_document_data[ xml_document_data_offset ] ),
			 additional_value_size + 1,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: type\t\t\t\t: 0x%02" PRIx8 "\n",
			 function,
			 xml_document_data[ xml_document_data_offset ] );
		}
#endif
		xml_document_data_offset += 1;

		if( ( flags & LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS ) == 0 )
		{
			attribute_name_offset = (uint32_t) ( binary_data_offset + xml_document_data_offset );
		}
		else
		{
			if( ( xml_document_data_size < 4 )
			 || ( xml_document_data_offset >= ( xml_document_data_size - 4 ) ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid binary XML document data size value too small.",
				 function );

				goto on_error;
			}
			byte_stream_copy_to_uint32_little_endian(
			 &( xml_document_data[ xml_document_data_offset ] ),
			 attribute_name_offset );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: name offset\t\t\t: 0x%08" PRIx32 "\n",
				 function,
				 attribute_name_offset );
			}
#endif
			xml_document_data_offset += 4;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "\n" );
		}
#endif
		if( attribute_name_offset > ( binary_data_offset + xml_document_data_offset ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid attribute data offset value out of bounds.",
			 function );

			goto on_error;
		}
		if( ( binary_data_offset + xml_document_data_offset ) < attribute_name_offset )
		{
			trailing_data_size = attribute_name_offset - ( binary_data_offset - xml_document_data_offset );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: data offset\t\t: 0x%08" PRIzx "\n",
				 function,
				 binary_data_offset + xml_document_data_offset );

				libcnotify_printf(
				 "%s: trailing data:\n",
				 function );
				libcnotify_print_data(
				 &( xml_document_data[ xml_document_data_offset ] ),
				 trailing_data_size,
				 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
			}
#endif
			xml_document_data_offset += trailing_data_size;
		}
		if( libfwevt_xml_tag_initialize(
		     &attribute_xml_tag,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create attribute XML tag.",
			 function );

			goto on_error;
		}
		if( libfwevt_xml_document_read_name(
		     internal_xml_document,
		     binary_data,
		     binary_data_size,
		     attribute_name_offset,
		     flags,
		     &attribute_name_size,
		     attribute_xml_tag,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read attribute name.",
			 function );

			goto on_error;
		}
		if( ( binary_data_offset + xml_document_data_offset ) == attribute_name_offset )
		{
			xml_document_data_offset += attribute_name_size;
		}
		if( libfwevt_xml_token_read_data(
		     xml_sub_token,
		     binary_data,
		     binary_data_size,
		     binary_data_offset + xml_document_data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read binary XML sub token.",
			 function );

			goto on_error;
		}
		result = 1;

		switch( xml_sub_token->type & 0xbf )
		{
			case LIBFWEVT_XML_TOKEN_VALUE:
				if( template_value_offset != 0 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: invalid template value offset value out of bounds.",
					 function );

					goto on_error;
				}
				if( libfwevt_xml_document_read_value(
				     internal_xml_document,
				     xml_sub_token,
				     binary_data,
				     binary_data_size,
				     binary_data_offset + xml_document_data_offset,
				     attribute_xml_tag,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read value.",
					 function );

					goto on_error;
				}
				break;

			case LIBFWEVT_XML_TOKEN_NORMAL_SUBSTITUTION:
				result = libfwevt_xml_document_read_normal_substitution(
				          internal_xml_document,
				          xml_sub_token,
				          binary_data,
				          binary_data_size,
				          binary_data_offset + xml_document_data_offset,
				          ascii_codepage,
				          flags,
				          template_values_array,
				          &template_value_offset,
				          attribute_xml_tag,
				          element_recursion_depth,
				          template_instance_recursion_depth,
				          error );

				if( result == -1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read normal substitution.",
					 function );

					goto on_error;
				}
				break;

			case LIBFWEVT_XML_TOKEN_OPTIONAL_SUBSTITUTION:
				result = libfwevt_xml_document_read_optional_substitution(
					  internal_xml_document,
					  xml_sub_token,
					  binary_data,
					  binary_data_size,
					  binary_data_offset + xml_document_data_offset,
					  ascii_codepage,
					  flags,
					  template_values_array,
					  &template_value_offset,
					  attribute_xml_tag,
				          element_recursion_depth,
				          template_instance_recursion_depth,
					  error );

				if( result == -1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read optional substitution.",
					 function );

					goto on_error;
				}
				break;

			default:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: invalid binary XML sub token - unsupported type: 0x%02" PRIx8 ".",
				 function,
				 xml_sub_token->type );

				goto on_error;
		}
		if( result != 0 )
		{
			if( libfwevt_xml_tag_append_attribute(
			     xml_tag,
			     attribute_xml_tag,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append attribute to XML tag.",
				 function );

				goto on_error;
			}
			attribute_xml_tag = NULL;
		}
		xml_document_data_offset += xml_sub_token->size;

		template_value_array_recursion_depth++;
	}
	while( template_value_offset > 0 );

	xml_token->size = xml_document_data_offset;

	if( attribute_xml_tag != NULL )
	{
		if( libfwevt_internal_xml_tag_free(
		     (libfwevt_internal_xml_tag_t **) &attribute_xml_tag,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free attribute XML tag.",
			 function );

			goto on_error;
		}
	}
	if( libfwevt_xml_token_free(
	     &xml_sub_token,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free binary XML sub token.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( attribute_xml_tag != NULL )
	{
		libfwevt_internal_xml_tag_free(
		 (libfwevt_internal_xml_tag_t **) &attribute_xml_tag,
		 NULL );
	}
	if( xml_sub_token != NULL )
	{
		libfwevt_xml_token_free(
		 &xml_sub_token,
		 NULL );
	}
	return( -1 );
}

/* Reads a CDATA section from a binary XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_read_cdata_section(
     libfwevt_internal_xml_document_t *internal_xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     libfwevt_xml_tag_t *xml_tag,
     libcerror_error_t **error )
{
	const uint8_t *xml_document_data = NULL;
	static char *function            = "libfwevt_xml_document_read_cdata_section";
	size_t value_data_size           = 0;
	size_t xml_document_data_size    = 0;

	if( internal_xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
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
	if( xml_token->type != LIBFWEVT_XML_TOKEN_CDATA_SECTION )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid binary XML token - unsupported type: 0x%02" PRIx8 ".",
		 function,
		 xml_token->type );

		return( -1 );
	}
	if( binary_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary data.",
		 function );

		return( -1 );
	}
	if( binary_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid binary XML document data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( binary_data_offset >= binary_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	xml_document_data      = &( binary_data[ binary_data_offset ] );
	xml_document_data_size = binary_data_size - binary_data_offset;

	if( xml_document_data_size < 3 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary XML document data size value too small.",
		 function );

		return( -1 );
	}
	if( libfwevt_xml_tag_set_type(
	     xml_tag,
	     LIBFWEVT_XML_TAG_TYPE_CDATA,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set XML tag type.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data offset\t\t: 0x%08" PRIzx "\n",
		 function,
		 binary_data_offset );

		libcnotify_printf(
		 "%s: cdata section data:\n",
		 function );
		libcnotify_print_data(
		 xml_document_data,
		 3,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	byte_stream_copy_to_uint16_little_endian(
	 &( xml_document_data[ 1 ] ),
	 value_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: type\t\t\t: 0x%02" PRIx8 "\n",
		 function,
		 xml_document_data[ 0 ] );

		libcnotify_printf(
		 "%s: number of characters\t: %" PRIzd "\n",
		 function,
		 value_data_size );
	}
#endif
	xml_token->size     = 3;
	binary_data_offset += 3;

	value_data_size *= 2;

	if( ( value_data_size > binary_data_size )
	 || ( binary_data_offset >= ( binary_data_size - value_data_size ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid value data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data offset\t\t: 0x%08" PRIzx "\n",
		 function,
		 binary_data_offset );

		libcnotify_printf(
		 "%s: value data:\n",
		 function );
		libcnotify_print_data(
		 &( xml_document_data[ 3 ] ),
		 value_data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( libfwevt_xml_tag_set_value_type(
	     xml_tag,
	     LIBFVALUE_VALUE_TYPE_STRING_UTF16,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set value type.",
		 function );

		return( -1 );
	}
	if( libfwevt_xml_tag_set_value_data(
	     xml_tag,
	     &( binary_data[ binary_data_offset ] ),
	     value_data_size,
	     LIBFVALUE_CODEPAGE_UTF16_LITTLE_ENDIAN,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set value data.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libfwevt_xml_tag_value_debug_print(
		     xml_tag,
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print value.",
			 function );

			return( -1 );
		}
	}
#endif
	xml_token->size += value_data_size;

	return( 1 );
}

/* Reads a character entity reference from a binary XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_read_character_reference(
     libfwevt_internal_xml_document_t *internal_xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     libfwevt_xml_tag_t *xml_tag,
     libcerror_error_t **error )
{
	libfwevt_xml_tag_t *character_xml_tag     = NULL;
	uint16_t *character_value_string          = NULL;
	uint8_t *character_value_utf16_stream     = NULL;
	const uint8_t *xml_document_data          = NULL;
	static char *function                     = "libfwevt_xml_document_read_character_reference";
	size_t character_value_string_index       = 0;
	size_t character_value_string_size        = 0;
	size_t character_value_utf16_stream_index = 0;
	size_t character_value_utf16_stream_size  = 0;
	size_t xml_document_data_size             = 0;
	uint16_t character_value                  = 0;
	int value_entry_index                     = 0;

	if( internal_xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
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
	if( ( xml_token->type & 0xbf ) != LIBFWEVT_XML_TOKEN_ENTITY_REFERENCE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid binary XML token - unsupported type: 0x%02" PRIx8 ".",
		 function,
		 xml_token->type );

		return( -1 );
	}
	if( binary_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary data.",
		 function );

		return( -1 );
	}
	if( binary_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid binary XML document data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( binary_data_offset >= binary_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	xml_document_data      = &( binary_data[ binary_data_offset ] );
	xml_document_data_size = binary_data_size - binary_data_offset;

	if( xml_document_data_size < 3 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary XML document data size value too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data offset\t\t: 0x%08" PRIzx "\n",
		 function,
		 binary_data_offset );

		libcnotify_printf(
		 "%s: character reference data:\n",
		 function );
		libcnotify_print_data(
		 xml_document_data,
		 3,
		 0 );
	}
#endif
	byte_stream_copy_to_uint16_little_endian(
	 &( xml_document_data[ 1 ] ),
	 character_value );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: type\t\t\t: 0x%02" PRIx8 "\n",
		 function,
		 xml_document_data[ 0 ] );

		libcnotify_printf(
		 "%s: character value\t\t: 0x%04" PRIx16 "\n",
		 function,
		 character_value );

		libcnotify_printf(
		 "\n" );
	}
#endif
	xml_token->size = 3;

	if( libfvalue_string_size_from_integer(
	     &character_value_string_size,
	     (uint64_t) character_value,
	     16,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of character value string.",
		 function );

		goto on_error;
	}
	character_value_string_size += 3;

	if( character_value_string_size > ( MEMORY_MAXIMUM_ALLOCATION_SIZE / sizeof( uint16_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid character value string size value out of bounds.",
		 function );

		goto on_error;
	}
	character_value_string = (uint16_t *) memory_allocate(
	                                       sizeof( uint16_t ) * character_value_string_size );

	if( character_value_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create character value string.",
		 function );

		goto on_error;
	}
	character_value_string[ character_value_string_index++ ] = (uint16_t) '&';
	character_value_string[ character_value_string_index++ ] = (uint16_t) '#';

	if( libfvalue_utf16_string_with_index_copy_from_integer(
	     character_value_string,
	     character_value_string_size,
	     &character_value_string_index,
	     (uint64_t) character_value,
	     16,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy character value to UTF-16 string.",
		 function );

		goto on_error;
	}
	character_value_string[ character_value_string_size - 2 ] = (uint16_t) ';';
	character_value_string[ character_value_string_size - 1 ] = 0;

	if( libfwevt_xml_tag_set_value_type(
	     xml_tag,
	     LIBFVALUE_VALUE_TYPE_STRING_UTF16,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set value type.",
		 function );

		goto on_error;
	}
	/* Make sure the character value data is in UTF-16 litte-endian
	 */
	if( ( character_value_utf16_stream_size == 0 )
	 || ( character_value_utf16_stream_size > ( MEMORY_MAXIMUM_ALLOCATION_SIZE / 2 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid character value UTF-16 stream size value out of bounds.",
		 function );

		goto on_error;
	}
	character_value_utf16_stream_size = character_value_string_size * 2;

	character_value_utf16_stream = (uint8_t *) memory_allocate(
	                                            sizeof( uint8_t ) * character_value_utf16_stream_size );

	if( character_value_utf16_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create character value UTF-16 stream.",
		 function );

		goto on_error;
	}
	for( character_value_string_index = 0;
	     character_value_string_index < character_value_string_size;
	     character_value_string_index++ )
	{
		byte_stream_copy_from_uint16_little_endian(
		 &( character_value_utf16_stream[ character_value_utf16_stream_index ] ),
		 character_value_string[ character_value_string_index ] );

		character_value_utf16_stream_index += 2;
	}
	memory_free(
	 character_value_string );

	character_value_string = NULL;

	if( libfwevt_xml_tag_append_value_data(
	     xml_tag,
	     character_value_utf16_stream,
	     character_value_utf16_stream_size,
	     LIBFVALUE_CODEPAGE_UTF16_LITTLE_ENDIAN,
	     &value_entry_index,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append value data.",
		 function );

		goto on_error;
	}
	memory_free(
	 character_value_utf16_stream );

	character_value_utf16_stream = NULL;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libfwevt_xml_tag_value_debug_print(
		     xml_tag,
		     value_entry_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print value: %d.",
			 function,
			 value_entry_index );

			goto on_error;
		}
	}
#endif
	if( libfwevt_internal_xml_tag_free(
	     (libfwevt_internal_xml_tag_t **) &character_xml_tag,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free character XML tag.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( character_value_utf16_stream != NULL )
	{
		memory_free(
		 character_value_utf16_stream );
	}
	if( character_value_string != NULL )
	{
		memory_free(
		 character_value_string );
	}
	if( character_xml_tag != NULL )
	{
		libfwevt_internal_xml_tag_free(
		 (libfwevt_internal_xml_tag_t **) &character_xml_tag,
		 NULL );
	}
	return( -1 );
}

/* Reads an element from a binary XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_read_element(
     libfwevt_internal_xml_document_t *internal_xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     int ascii_codepage,
     uint8_t flags,
     libcdata_array_t *template_values_array,
     libfwevt_xml_tag_t *xml_tag,
     int element_recursion_depth,
     int template_instance_recursion_depth,
     libcerror_error_t **error )
{
	libfwevt_xml_tag_t *element_xml_tag      = NULL;
	libfwevt_xml_token_t *xml_sub_token      = NULL;
	const uint8_t *xml_document_data         = NULL;
	static char *function                    = "libfwevt_xml_document_read_element";
	size_t additional_value_size             = 0;
	size_t element_size_offset               = 0;
	size_t template_value_offset             = 0;
	size_t trailing_data_size                = 0;
	size_t xml_document_data_offset          = 0;
	size_t xml_document_data_size            = 0;
	uint32_t attribute_list_size             = 0;
	uint32_t element_name_offset             = 0;
	uint32_t element_name_size               = 0;
	uint32_t element_size                    = 0;
	int result                               = 0;
	int template_value_array_recursion_depth = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint16_t value_16bit                     = 0;
#endif

	if( internal_xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
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
	if( ( xml_token->type & 0xbf ) != LIBFWEVT_XML_TOKEN_OPEN_START_ELEMENT_TAG )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid binary XML token - unsupported type: 0x%02" PRIx8 ".",
		 function,
		 xml_token->type );

		return( -1 );
	}
	if( binary_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary data.",
		 function );

		return( -1 );
	}
	if( binary_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid binary XML document data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( binary_data_offset >= binary_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( element_recursion_depth < 0 )
	 || ( element_recursion_depth > LIBFWEVT_XML_DOCUMENT_ELEMENT_RECURSION_DEPTH ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid element recursion depth value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( flags & LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS ) != 0 )
	{
		additional_value_size = 4;
	}
	if( ( binary_data_size < ( 5 + additional_value_size ) )
	 || ( binary_data_offset > ( binary_data_size - 5 - additional_value_size ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary XML document data size value too small.",
		 function );

		goto on_error;
	}
	if( libfwevt_xml_token_initialize(
	     &xml_sub_token,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create binary XML sub token.",
		 function );

		goto on_error;
	}
	xml_document_data      = &( binary_data[ binary_data_offset ] );
	xml_document_data_size = binary_data_size - binary_data_offset;

	do
	{
		if( ( template_value_array_recursion_depth < 0 )
		 || ( template_value_array_recursion_depth > LIBFWEVT_XML_DOCUMENT_TEMPLATE_VALUE_ARRAY_RECURSION_DEPTH ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid template value array recursion depth value out of bounds.",
			 function );

			goto on_error;
		}
		if( libfwevt_xml_tag_initialize(
		     &element_xml_tag,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create element XML tag.",
			 function );

			goto on_error;
		}
		/* Note that the dependency identifier is an optional value.
		 */
		element_size_offset = 1;

		byte_stream_copy_to_uint32_little_endian(
		 &( xml_document_data[ element_size_offset ] ),
		 element_size );

		if( ( xml_document_data_size > 7 )
		 && ( element_size > ( xml_document_data_size - 7 ) ) )
		{
			element_size_offset = 3;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: data offset\t\t\t\t: 0x%08" PRIzx "\n",
			 function,
			 binary_data_offset );

			libcnotify_printf(
			 "%s: element data:\n",
			 function );
			libcnotify_print_data(
			 xml_document_data,
			 element_size_offset + 4 + additional_value_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
		byte_stream_copy_to_uint32_little_endian(
		 &( xml_document_data[ element_size_offset ] ),
		 element_size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: type\t\t\t\t: 0x%02" PRIx8 "\n",
			 function,
			 xml_document_data[ 0 ] );

			if( element_size_offset == 3 )
			{
				byte_stream_copy_to_uint16_little_endian(
				 &( xml_document_data[ 1 ] ),
				 value_16bit );
				libcnotify_printf(
				 "%s: dependency identifier\t\t: %" PRIi16 " (0x%04" PRIx16 ")\n",
				 function,
				 (int16_t) value_16bit,
				 value_16bit );
			}
			libcnotify_printf(
			 "%s: size\t\t\t\t: %" PRIu32 "\n",
			 function,
			 element_size );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		xml_document_data_offset = element_size_offset + 4;

		/* The first 5 or 7 bytes are not included in the element size
		 */
		if( ( flags & LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS ) == 0 )
		{
			element_name_offset = (uint32_t) ( binary_data_offset + xml_document_data_offset );
		}
		else
		{
			if( xml_document_data_offset >= ( xml_document_data_size - 4 ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid binary XML document data size value too small.",
				 function );

				goto on_error;
			}
			byte_stream_copy_to_uint32_little_endian(
			 &( xml_document_data[ xml_document_data_offset ] ),
			 element_name_offset );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: name offset\t\t\t\t: 0x%08" PRIx32 "\n",
				 function,
				 element_name_offset );
			}
#endif
			xml_document_data_offset += 4;
			element_size             -= 4;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "\n" );
		}
#endif
		if( element_name_offset > ( binary_data_offset + xml_document_data_offset ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid element data offset value out of bounds.",
			 function );

			goto on_error;
		}
		if( ( binary_data_offset + xml_document_data_offset ) < element_name_offset )
		{
			trailing_data_size = element_name_offset - ( binary_data_offset + xml_document_data_offset );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: data offset\t\t\t\t: 0x%08" PRIzx "\n",
				 function,
				 binary_data_offset + xml_document_data_offset );

				libcnotify_printf(
				 "%s: trailing data:\n",
				 function );
				libcnotify_print_data(
				 &( xml_document_data[ xml_document_data_offset ] ),
				 trailing_data_size,
				 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
			}
#endif
			xml_document_data_offset += trailing_data_size;
			element_size             -= (uint32_t) trailing_data_size;
		}
		if( libfwevt_xml_document_read_name(
		     internal_xml_document,
		     binary_data,
		     binary_data_size,
		     element_name_offset,
		     flags,
		     &element_name_size,
		     element_xml_tag,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read element name.",
			 function );

			goto on_error;
		}
		if( ( binary_data_offset + xml_document_data_offset ) == element_name_offset )
		{
			xml_document_data_offset += element_name_size;
			element_size             -= element_name_size;
		}
		if( ( xml_token->type & LIBFWEVT_XML_TOKEN_FLAG_HAS_MORE_DATA ) != 0 )
		{
			if( xml_document_data_offset >= ( xml_document_data_size - 4 ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid binary XML document data size value too small.",
				 function );

				goto on_error;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: data offset\t\t\t\t: 0x%08" PRIzx "\n",
				 function,
				 binary_data_offset + xml_document_data_offset );

				libcnotify_printf(
				 "%s: attribute list data:\n",
				 function );
				libcnotify_print_data(
				 &( xml_document_data[ xml_document_data_offset ] ),
				 4,
				 0 );
			}
#endif
			byte_stream_copy_to_uint32_little_endian(
			 &( xml_document_data[ xml_document_data_offset ] ),
			 attribute_list_size );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: attribute list size\t\t\t: %" PRIu32 "\n",
				 function,
				 attribute_list_size );

				libcnotify_printf(
				 "\n" );
			}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

			xml_document_data_offset += 4;
			element_size             -= 4;

			if( attribute_list_size > ( binary_data_size - ( binary_data_offset + xml_document_data_offset ) ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid attribute list size value out of bounds.",
				 function );

				goto on_error;
			}
			while( attribute_list_size > 0 )
			{
				if( libfwevt_xml_token_read_data(
				     xml_sub_token,
				     binary_data,
				     binary_data_size,
				     binary_data_offset + xml_document_data_offset,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read binary XML sub token.",
					 function );

					goto on_error;
				}
				if( libfwevt_xml_document_read_attribute(
				     internal_xml_document,
				     xml_sub_token,
				     binary_data,
				     binary_data_size,
				     binary_data_offset + xml_document_data_offset,
				     ascii_codepage,
				     flags,
				     template_values_array,
				     element_xml_tag,
				     element_recursion_depth,
				     template_instance_recursion_depth,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read attribute.",
					 function );

					goto on_error;
				}
				xml_document_data_offset += xml_sub_token->size;
				element_size             -= (uint32_t) xml_sub_token->size;

				if( attribute_list_size < xml_sub_token->size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: invalid attribute list size value too small.",
					 function );

					goto on_error;
				}
				attribute_list_size -= (uint32_t) xml_sub_token->size;
			}
		}
		if( libfwevt_xml_token_read_data(
		     xml_sub_token,
		     binary_data,
		     binary_data_size,
		     binary_data_offset + xml_document_data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read binary XML sub token.",
			 function );

			goto on_error;
		}
		if( ( xml_sub_token->type != LIBFWEVT_XML_TOKEN_CLOSE_START_ELEMENT_TAG )
		 && ( xml_sub_token->type != LIBFWEVT_XML_TOKEN_CLOSE_EMPTY_ELEMENT_TAG ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid binary XML token - unsupported type: 0x%02" PRIx8 ".",
			 function,
			 xml_token->type );

			goto on_error;
		}
		if( xml_document_data_offset >= xml_document_data_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid binary XML document data size value too small.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: data offset\t\t\t\t: 0x%08" PRIzx "\n",
			 function,
			 binary_data_offset + xml_document_data_offset );

			libcnotify_printf(
			 "%s: close element tag data:\n",
			 function );
			libcnotify_print_data(
			 &( xml_document_data[ xml_document_data_offset ] ),
			 1,
			 0 );
		}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: type\t\t\t\t: 0x%02" PRIx8 "\n",
			 function,
			 xml_document_data[ xml_document_data_offset ] );

			libcnotify_printf(
			 "\n" );
		}
#endif
		xml_document_data_offset += 1;
		element_size             -= 1;

		if( xml_sub_token->type == LIBFWEVT_XML_TOKEN_CLOSE_START_ELEMENT_TAG )
		{
			result = 1;

			while( element_size > 0 )
			{
				if( libfwevt_xml_token_read_data(
				     xml_sub_token,
				     binary_data,
				     binary_data_size,
				     binary_data_offset + xml_document_data_offset,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read binary XML sub token.",
					 function );

					goto on_error;
				}
				switch( xml_sub_token->type & 0xbf )
				{
					case LIBFWEVT_XML_TOKEN_OPEN_START_ELEMENT_TAG:
						if( libfwevt_xml_document_read_element(
						     internal_xml_document,
						     xml_sub_token,
						     binary_data,
						     binary_data_size,
						     binary_data_offset + xml_document_data_offset,
						     ascii_codepage,
						     flags,
						     template_values_array,
						     element_xml_tag,
						     element_recursion_depth + 1,
						     template_instance_recursion_depth,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_IO,
							 LIBCERROR_IO_ERROR_READ_FAILED,
							 "%s: unable to read element.",
							 function );

							goto on_error;
						}
						break;

					case LIBFWEVT_XML_TOKEN_CLOSE_EMPTY_ELEMENT_TAG:
					case LIBFWEVT_XML_TOKEN_END_ELEMENT_TAG:
						if( xml_document_data_offset >= xml_document_data_size )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_RUNTIME,
							 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
							 "%s: invalid binary XML document data size value too small.",
							 function );

							goto on_error;
						}
#if defined( HAVE_DEBUG_OUTPUT )
						if( libcnotify_verbose != 0 )
						{
							libcnotify_printf(
							 "%s: data offset\t\t\t\t: 0x%08" PRIzx "\n",
							 function,
							 binary_data_offset + xml_document_data_offset );

							libcnotify_printf(
							 "%s: end element tag data:\n",
							 function );
							libcnotify_print_data(
							 &( xml_document_data[ xml_document_data_offset ] ),
							 1,
							 0 );
						}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
						if( libcnotify_verbose != 0 )
						{
							libcnotify_printf(
							 "%s: type\t\t\t\t: 0x%02" PRIx8 "\n",
							 function,
							 xml_document_data[ xml_document_data_offset ] );

							libcnotify_printf(
							 "\n" );
						}
#endif
						xml_sub_token->size = 1;

						break;

					case LIBFWEVT_XML_TOKEN_CDATA_SECTION:
						if( template_value_offset != 0 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
							 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
							 "%s: invalid template value offset value out of bounds.",
							 function );

							goto on_error;
						}
						if( libfwevt_xml_document_read_cdata_section(
						     internal_xml_document,
						     xml_sub_token,
						     binary_data,
						     binary_data_size,
						     binary_data_offset + xml_document_data_offset,
						     element_xml_tag,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_IO,
							 LIBCERROR_IO_ERROR_READ_FAILED,
							 "%s: unable to read CDATA section.",
							 function );

							goto on_error;
						}
						break;

					case LIBFWEVT_XML_TOKEN_PI_TARGET:
						if( template_value_offset != 0 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
							 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
							 "%s: invalid template value offset value out of bounds.",
							 function );

							goto on_error;
						}
						if( libfwevt_xml_document_read_pi_target(
						     internal_xml_document,
						     xml_sub_token,
						     binary_data,
						     binary_data_size,
						     binary_data_offset + xml_document_data_offset,
						     flags,
						     element_xml_tag,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_IO,
							 LIBCERROR_IO_ERROR_READ_FAILED,
							 "%s: unable to read PI target.",
							 function );

							goto on_error;
						}
						break;

					case LIBFWEVT_XML_TOKEN_CHARACTER_REFERENCE:
						if( template_value_offset != 0 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
							 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
							 "%s: invalid template value offset value out of bounds.",
							 function );

							goto on_error;
						}
						if( libfwevt_xml_document_read_character_reference(
						     internal_xml_document,
						     xml_sub_token,
						     binary_data,
						     binary_data_size,
						     binary_data_offset + xml_document_data_offset,
						     element_xml_tag,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_IO,
							 LIBCERROR_IO_ERROR_READ_FAILED,
							 "%s: unable to read character reference.",
							 function );

							goto on_error;
						}
						break;

					case LIBFWEVT_XML_TOKEN_ENTITY_REFERENCE:
						if( template_value_offset != 0 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
							 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
							 "%s: invalid template value offset value out of bounds.",
							 function );

							goto on_error;
						}
						if( libfwevt_xml_document_read_entity_reference(
						     internal_xml_document,
						     xml_sub_token,
						     binary_data,
						     binary_data_size,
						     binary_data_offset + xml_document_data_offset,
						     flags,
						     element_xml_tag,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_IO,
							 LIBCERROR_IO_ERROR_READ_FAILED,
							 "%s: unable to read entity reference.",
							 function );

							goto on_error;
						}
						break;

					case LIBFWEVT_XML_TOKEN_VALUE:
						if( template_value_offset != 0 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
							 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
							 "%s: invalid template value offset value out of bounds.",
							 function );

							goto on_error;
						}
						if( libfwevt_xml_document_read_value(
						     internal_xml_document,
						     xml_sub_token,
						     binary_data,
						     binary_data_size,
						     binary_data_offset + xml_document_data_offset,
						     element_xml_tag,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_IO,
							 LIBCERROR_IO_ERROR_READ_FAILED,
							 "%s: unable to read value.",
							 function );

							goto on_error;
						}
						break;

					case LIBFWEVT_XML_TOKEN_NORMAL_SUBSTITUTION:
						result = libfwevt_xml_document_read_normal_substitution(
							  internal_xml_document,
							  xml_sub_token,
							  binary_data,
							  binary_data_size,
							  binary_data_offset + xml_document_data_offset,
							  ascii_codepage,
							  flags,
							  template_values_array,
							  &template_value_offset,
							  element_xml_tag,
							  element_recursion_depth,
							  template_instance_recursion_depth,
							  error );

						if( result == -1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_IO,
							 LIBCERROR_IO_ERROR_READ_FAILED,
							 "%s: unable to read normal substitution.",
							 function );

							goto on_error;
						}
						break;

					case LIBFWEVT_XML_TOKEN_OPTIONAL_SUBSTITUTION:
						result = libfwevt_xml_document_read_optional_substitution(
							  internal_xml_document,
							  xml_sub_token,
							  binary_data,
							  binary_data_size,
							  binary_data_offset + xml_document_data_offset,
							  ascii_codepage,
							  flags,
							  template_values_array,
							  &template_value_offset,
							  element_xml_tag,
						          element_recursion_depth,
							  template_instance_recursion_depth,
							  error );

						if( result == -1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_IO,
							 LIBCERROR_IO_ERROR_READ_FAILED,
							 "%s: unable to read optional substitution.",
							 function );

							goto on_error;
						}
						break;

					default:
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
						 "%s: invalid binary XML sub token - unsupported type: 0x%02" PRIx8 ".",
						 function,
						 xml_sub_token->type );

						goto on_error;
				}
				xml_document_data_offset += xml_sub_token->size;

				if( element_size < xml_sub_token->size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: invalid element size value too small.",
					 function );

					goto on_error;
				}
				element_size -= (uint32_t) xml_sub_token->size;

				if( ( xml_sub_token->type == LIBFWEVT_XML_TOKEN_CLOSE_EMPTY_ELEMENT_TAG )
				 || ( xml_sub_token->type == LIBFWEVT_XML_TOKEN_END_ELEMENT_TAG ) )
				{
					break;
				}
			}
		}
		else if( xml_sub_token->type == LIBFWEVT_XML_TOKEN_CLOSE_EMPTY_ELEMENT_TAG )
		{
			result = 1;
		}
		if( element_size > 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid element size value out of bounds.",
			 function );

			goto on_error;
		}
		if( result != 0 )
		{
			if( xml_tag != NULL )
			{
				if( libfwevt_xml_tag_append_element(
				     xml_tag,
				     element_xml_tag,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
					 "%s: unable to append element to XML tag.",
					 function );

					goto on_error;
				}
				element_xml_tag = NULL;
			}
			else if( internal_xml_document->root_xml_tag == NULL )
			{
				internal_xml_document->root_xml_tag = element_xml_tag;

				element_xml_tag = NULL;
			}
		}
		template_value_array_recursion_depth++;
	}
	while( template_value_offset > 0 );

	xml_token->size = xml_document_data_offset;

	if( element_xml_tag != NULL )
	{
		if( libfwevt_internal_xml_tag_free(
		     (libfwevt_internal_xml_tag_t **) &element_xml_tag,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free element XML tag.",
			 function );

			goto on_error;
		}
	}
	if( libfwevt_xml_token_free(
	     &xml_sub_token,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free binary XML sub token.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( ( element_xml_tag != NULL )
	 && ( element_xml_tag != internal_xml_document->root_xml_tag ) )
	{
		libfwevt_internal_xml_tag_free(
		 (libfwevt_internal_xml_tag_t **) &element_xml_tag,
		 NULL );
	}
	if( xml_sub_token != NULL )
	{
		libfwevt_xml_token_free(
		 &xml_sub_token,
		 NULL );
	}
	return( -1 );
}

/* Reads an entity reference from a binary XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_read_entity_reference(
     libfwevt_internal_xml_document_t *internal_xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     uint8_t flags,
     libfwevt_xml_tag_t *xml_tag,
     libcerror_error_t **error )
{
	libfwevt_xml_tag_t *entity_xml_tag = NULL;
	uint8_t *entity_name               = NULL;
	uint8_t *entity_value_utf16_stream = NULL;
	const uint8_t *xml_document_data   = NULL;
	static char *function              = "libfwevt_xml_document_read_entity_reference";
	size_t additional_value_size       = 0;
	size_t trailing_data_size          = 0;
	size_t utf8_string_size            = 0;
	size_t xml_document_data_offset    = 0;
	size_t xml_document_data_size      = 0;
	uint32_t entity_name_offset        = 0;
	uint32_t entity_name_size          = 0;
	uint8_t entity_name_match          = 0;
	int value_entry_index              = 0;

	if( internal_xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
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
	if( ( xml_token->type & 0xbf ) != LIBFWEVT_XML_TOKEN_ENTITY_REFERENCE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid binary XML token - unsupported type: 0x%02" PRIx8 ".",
		 function,
		 xml_token->type );

		return( -1 );
	}
	if( binary_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary data.",
		 function );

		return( -1 );
	}
	if( binary_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid binary XML document data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( binary_data_offset >= binary_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	if( ( flags & LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS ) != 0 )
	{
		additional_value_size = 4;
	}
	xml_document_data      = &( binary_data[ binary_data_offset ] );
	xml_document_data_size = binary_data_size - binary_data_offset;

	if( xml_document_data_size < ( 1 + additional_value_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary XML document data size value too small.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data offset\t\t: 0x%08" PRIzx "\n",
		 function,
		 binary_data_offset );

		libcnotify_printf(
		 "%s: entity reference data:\n",
		 function );
		libcnotify_print_data(
		 xml_document_data,
		 1 + additional_value_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: type\t\t\t: 0x%02" PRIx8 "\n",
		 function,
		 xml_document_data[ 0 ] );
	}
#endif
	xml_token->size          = 1;
	xml_document_data_offset = 1;

	if( ( flags & LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS ) == 0 )
	{
		entity_name_offset = (uint32_t) ( binary_data_offset + xml_document_data_offset );
	}
	else
	{
		if( ( xml_document_data_size < 4 )
		 || ( xml_document_data_offset >= ( xml_document_data_size - 4 ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid binary XML document data size value too small.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint32_little_endian(
		 &( xml_document_data[ xml_document_data_offset ] ),
		 entity_name_offset );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: name offset\t\t: 0x%08" PRIx32 "\n",
			 function,
			 entity_name_offset );
		}
#endif
		xml_token->size          += 4;
		xml_document_data_offset += 4;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	if( entity_name_offset > ( binary_data_offset + xml_document_data_offset ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid entity name offset value out of bounds.",
		 function );

		goto on_error;
	}
	if( ( binary_data_offset + xml_document_data_offset ) < entity_name_offset )
	{
		trailing_data_size = entity_name_offset - ( binary_data_offset + xml_document_data_offset );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: data offset\t\t: 0x%08" PRIzx "\n",
			 function,
			 binary_data_offset + xml_document_data_offset );

			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( xml_document_data[ xml_document_data_offset ] ),
			 trailing_data_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
		xml_token->size          += trailing_data_size;
		xml_document_data_offset += trailing_data_size;
	}
	if( libfwevt_xml_tag_initialize(
	     &entity_xml_tag,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create entity XML tag.",
		 function );

		goto on_error;
	}
	if( libfwevt_xml_document_read_name(
	     internal_xml_document,
	     binary_data,
	     binary_data_size,
	     entity_name_offset,
	     flags,
	     &entity_name_size,
	     entity_xml_tag,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read entity name.",
		 function );

		goto on_error;
	}
	if( ( binary_data_offset + xml_document_data_offset ) == entity_name_offset )
	{
		xml_token->size += entity_name_size;
	}
	if( libfwevt_xml_tag_get_utf8_name_size(
	     entity_xml_tag,
	     &utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string size of entity name.",
		 function );

		goto on_error;
	}
	if( ( utf8_string_size == 0 )
	 || ( utf8_string_size > ( MEMORY_MAXIMUM_ALLOCATION_SIZE / sizeof( uint8_t ) ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid UTF-8 string size value out of bounds.",
		 function );

		goto on_error;
	}
	entity_name = (uint8_t *) memory_allocate(
	                           sizeof( uint8_t ) * utf8_string_size );

	if( entity_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create entity name.",
		 function );

		goto on_error;
	}
	if( libfwevt_xml_tag_get_utf8_name(
	     entity_xml_tag,
	     entity_name,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy entity name to UTF-16 string.",
		 function );

		goto on_error;
	}
	if( libfwevt_xml_tag_set_value_type(
	     xml_tag,
	     LIBFVALUE_VALUE_TYPE_STRING_UTF16,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set value type.",
		 function );

		goto on_error;
	}
	/* Make sure the character value data is in UTF-16 litte-endian
	 */
	entity_value_utf16_stream = (uint8_t *) memory_allocate(
	                                         sizeof( uint8_t ) * 4 );

	if( entity_value_utf16_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create entity value UTF-16 stream.",
		 function );

		goto on_error;
	}
	if( utf8_string_size == 3 )
	{
		if( ( entity_name[ 0 ] == (uint8_t) 'g' )
		 && ( entity_name[ 1 ] == (uint8_t) 't' ) )
		{
			entity_value_utf16_stream[ 0 ] = (uint8_t) '>';
			entity_value_utf16_stream[ 1 ] = 0;

			entity_name_match = 1;
		}
		else if( ( entity_name[ 0 ] == (uint8_t) 'l' )
		      && ( entity_name[ 1 ] == (uint8_t) 't' ) )
		{
			entity_value_utf16_stream[ 0 ] = (uint8_t) '<';
			entity_value_utf16_stream[ 1 ] = 0;

			entity_name_match = 1;
		}
	}
	else if( utf8_string_size == 4 )
	{
		if( ( entity_name[ 0 ] == (uint8_t) 'a' )
		 && ( entity_name[ 1 ] == (uint8_t) 'm' )
		 && ( entity_name[ 2 ] == (uint8_t) 'p' ) )
		{
			entity_value_utf16_stream[ 0 ] = (uint8_t) '&';
			entity_value_utf16_stream[ 1 ] = 0;

			entity_name_match = 1;
		}
	}
	else if( utf8_string_size == 5 )
	{
		if( ( entity_name[ 0 ] == (uint8_t) 'a' )
		 && ( entity_name[ 1 ] == (uint8_t) 'p' )
		 && ( entity_name[ 2 ] == (uint8_t) 'o' )
		 && ( entity_name[ 3 ] == (uint8_t) 's' ) )
		{
			entity_value_utf16_stream[ 0 ] = (uint8_t) '\'';
			entity_value_utf16_stream[ 1 ] = 0;

			entity_name_match = 1;
		}
		else if( ( entity_name[ 0 ] == (uint8_t) 'q' )
		      && ( entity_name[ 1 ] == (uint8_t) 'u' )
		      && ( entity_name[ 2 ] == (uint8_t) 'o' )
		      && ( entity_name[ 3 ] == (uint8_t) 't' ) )
		{
			entity_value_utf16_stream[ 0 ] = (uint8_t) '"';
			entity_value_utf16_stream[ 1 ] = 0;

			entity_name_match = 1;
		}
	}
	if( entity_name_match == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported entity name: %s\n",
		 function,
		 entity_name );

		goto on_error;
	}
	entity_value_utf16_stream[ 2 ] = 0;
	entity_value_utf16_stream[ 3 ] = 0;

	memory_free(
	 entity_name );

	entity_name = NULL;

	if( libfwevt_xml_tag_append_value_data(
	     xml_tag,
	     entity_value_utf16_stream,
	     4,
	     LIBFVALUE_CODEPAGE_UTF16_LITTLE_ENDIAN,
	     &value_entry_index,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append value data.",
		 function );

		goto on_error;
	}
	memory_free(
	 entity_value_utf16_stream );

	entity_value_utf16_stream = NULL;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libfwevt_xml_tag_value_debug_print(
		     xml_tag,
		     value_entry_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print value: %d.",
			 function,
			 value_entry_index );

			goto on_error;
		}
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( libfwevt_internal_xml_tag_free(
	     (libfwevt_internal_xml_tag_t **) &entity_xml_tag,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free entity XML tag.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( entity_value_utf16_stream != NULL )
	{
		memory_free(
		 entity_value_utf16_stream );
	}
	if( entity_name != NULL )
	{
		memory_free(
		 entity_name );
	}
	if( entity_xml_tag != NULL )
	{
		libfwevt_internal_xml_tag_free(
		 (libfwevt_internal_xml_tag_t **) &entity_xml_tag,
		 NULL );
	}
	return( -1 );
}

/* Reads a fragment from a binary XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_read_fragment(
     libfwevt_internal_xml_document_t *internal_xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     int ascii_codepage,
     uint8_t flags,
     libcdata_array_t *template_values_array,
     libfwevt_xml_tag_t *xml_tag,
     int element_recursion_depth,
     int template_instance_recursion_depth,
     libcerror_error_t **error )
{
	libfwevt_xml_token_t *xml_sub_token = NULL;
	static char *function               = "libfwevt_xml_document_read_fragment";

	if( internal_xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
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
	if( libfwevt_xml_document_read_fragment_header(
	     internal_xml_document,
	     xml_token,
	     binary_data,
	     binary_data_size,
	     binary_data_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read fragment header.",
		 function );

		goto on_error;
	}
	binary_data_offset += xml_token->size;

	if( libfwevt_xml_token_initialize(
	     &xml_sub_token,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create binary XML sub token.",
		 function );

		goto on_error;
	}
	if( libfwevt_xml_token_read_data(
	     xml_sub_token,
	     binary_data,
	     binary_data_size,
	     binary_data_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read binary XML sub token.",
		 function );

		goto on_error;
	}
	switch( xml_sub_token->type & 0xbf )
	{
		case LIBFWEVT_XML_TOKEN_OPEN_START_ELEMENT_TAG:
			if( libfwevt_xml_document_read_element(
			     internal_xml_document,
			     xml_sub_token,
			     binary_data,
			     binary_data_size,
			     binary_data_offset,
			     ascii_codepage,
			     flags,
			     template_values_array,
			     xml_tag,
			     element_recursion_depth + 1,
			     template_instance_recursion_depth,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read element.",
				 function );

				goto on_error;
			}
			break;

		case LIBFWEVT_XML_TOKEN_TEMPLATE_INSTANCE:
			if( libfwevt_xml_document_read_template_instance(
			     internal_xml_document,
			     xml_sub_token,
			     binary_data,
			     binary_data_size,
			     binary_data_offset,
			     ascii_codepage,
			     flags,
			     xml_tag,
			     element_recursion_depth,
			     template_instance_recursion_depth + 1,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read document template instance.",
				 function );

				goto on_error;
			}
			break;

		default:
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid binary XML token - unsupported type: 0x%02" PRIx8 ".",
			 function,
			 xml_sub_token->type );

			goto on_error;
	}
	xml_token->size += xml_sub_token->size;

	if( libfwevt_xml_token_free(
	     &xml_sub_token,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free binary XML sub token.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( xml_sub_token != NULL )
	{
		libfwevt_xml_token_free(
		 &xml_sub_token,
		 NULL );
	}
	return( -1 );
}

/* Reads a fragment header from a binary XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_read_fragment_header(
     libfwevt_internal_xml_document_t *internal_xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     libcerror_error_t **error )
{
	static char *function            = "libfwevt_xml_document_read_fragment_header";
	size_t xml_document_data_size    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	const uint8_t *xml_document_data = NULL;
#endif

	if( internal_xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
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
	if( xml_token->type != LIBFWEVT_XML_TOKEN_FRAGMENT_HEADER )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid binary XML token - unsupported type: 0x%02" PRIx8 ".",
		 function,
		 xml_token->type );

		return( -1 );
	}
	if( binary_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary data.",
		 function );

		return( -1 );
	}
	if( binary_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid binary XML document data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( binary_data_offset >= binary_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary data offset value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	xml_document_data = &( binary_data[ binary_data_offset ] );
#endif

	xml_document_data_size = binary_data_size - binary_data_offset;

	if( xml_document_data_size < 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary XML document data size value too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data offset\t\t\t: 0x%08" PRIzx "\n",
		 function,
		 binary_data_offset );

		libcnotify_printf(
		 "%s: fragment header data:\n",
		 function );
		libcnotify_print_data(
		 xml_document_data,
		 4,
		 0 );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: type\t\t\t: 0x%02" PRIx8 "\n",
		 function,
		 xml_document_data[ 0 ] );

		libcnotify_printf(
		 "%s: major version\t\t: %" PRIu8 "\n",
		 function,
		 xml_document_data[ 1 ] );

		libcnotify_printf(
		 "%s: minor version\t\t: %" PRIu8 "\n",
		 function,
		 xml_document_data[ 2 ] );

		libcnotify_printf(
		 "%s: flags\t\t\t: 0x%02" PRIx8 "\n",
		 function,
		 xml_document_data[ 3 ] );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

/* TODO check values */
	xml_token->size = 4;
	
	return( 1 );
}

/* Reads a name from a binary XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_read_name(
     libfwevt_internal_xml_document_t *internal_xml_document,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     uint8_t flags,
     uint32_t *name_data_size,
     libfwevt_xml_tag_t *xml_tag,
     libcerror_error_t **error )
{
	const uint8_t *xml_document_data = NULL;
	static char *function            = "libfwevt_xml_document_read_name";
	size_t additional_value_size     = 0;
	size_t xml_document_data_offset  = 0;
	size_t xml_document_data_size    = 0;
	uint32_t name_size               = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit             = 0;
	uint16_t value_16bit             = 0;
#endif

	if( internal_xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
	if( binary_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary data.",
		 function );

		return( -1 );
	}
	if( ( binary_data_size < 4 )
	 || ( binary_data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary XML document data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( binary_data_offset >= binary_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( name_data_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name data size.",
		 function );

		return( -1 );
	}
	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	xml_document_data      = &( binary_data[ binary_data_offset ] );
	xml_document_data_size = binary_data_size - binary_data_offset;

	if( ( flags & LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS ) != 0 )
	{
		additional_value_size += 4;
	}
	if( ( additional_value_size + 4 ) > xml_document_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary XML document data size value too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data offset\t\t\t\t: 0x%08" PRIzx "\n",
		 function,
		 binary_data_offset );

		libcnotify_printf(
		 "%s: name header data:\n",
		 function );
		libcnotify_print_data(
		 xml_document_data,
		 additional_value_size + 4,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( ( flags & LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS ) != 0 )
	{
/* TODO determine if this used */
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 xml_document_data,
			 value_32bit );
			libcnotify_printf(
			 "%s: name unknown1\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
#endif
		xml_document_data_offset += 4;
	}
	byte_stream_copy_to_uint16_little_endian(
	 &( xml_document_data[ xml_document_data_offset + 2 ] ),
	 name_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint16_little_endian(
		 &( xml_document_data[ xml_document_data_offset ] ),
		 value_16bit );
		libcnotify_printf(
		 "%s: name hash\t\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "%s: name number of characters\t\t: %" PRIu16 "\n",
		 function,
		 name_size );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	xml_document_data_offset += 4;

	if( ( name_size == 0 )
	 || ( (size_t) name_size > ( ( MEMORY_MAXIMUM_ALLOCATION_SIZE - 1 ) / 2 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid name size value out of bounds.",
		 function );

		return( -1 );
	}
	name_size = ( name_size + 1 ) * 2;

	if( (size_t) name_size > ( xml_document_data_size - xml_document_data_offset ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary XML document data size value too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: name data:\n",
		 function );
		libcnotify_print_data(
		 &( xml_document_data[ xml_document_data_offset ] ),
		 name_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( libfwevt_xml_tag_set_name_data(
	     xml_tag,
	     &( xml_document_data[ xml_document_data_offset ] ),
	     name_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set name data.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libfwevt_xml_tag_name_debug_print(
		     xml_tag,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print name.",
			 function );

			return( -1 );
		}
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	*name_data_size = (uint32_t) ( xml_document_data_offset + name_size );

	return( 1 );
}

/* Reads a normal substitution from a binary XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_read_normal_substitution(
     libfwevt_internal_xml_document_t *internal_xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     int ascii_codepage,
     uint8_t flags,
     libcdata_array_t *template_values_array,
     size_t *template_value_offset,
     libfwevt_xml_tag_t *xml_tag,
     int element_recursion_depth,
     int template_instance_recursion_depth,
     libcerror_error_t **error )
{
	const uint8_t *xml_document_data = NULL;
	static char *function            = "libfwevt_xml_document_read_normal_substitution";
	size_t xml_document_data_size    = 0;
	uint16_t template_value_index    = 0;
	uint8_t template_value_type      = 0;
	int result                       = 0;

	if( internal_xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
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
	if( xml_token->type != LIBFWEVT_XML_TOKEN_NORMAL_SUBSTITUTION )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid binary XML token - unsupported type: 0x%02" PRIx8 ".",
		 function,
		 xml_token->type );

		return( -1 );
	}
	if( binary_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary data.",
		 function );

		return( -1 );
	}
	if( binary_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid binary XML document data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( binary_data_offset >= binary_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary data offset value out of bounds.",
		 function );

		return( -1 );
	}
	xml_document_data      = &( binary_data[ binary_data_offset ] );
	xml_document_data_size = binary_data_size - binary_data_offset;

	if( xml_document_data_size < 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary XML document data size value too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data offset\t\t: 0x%08" PRIzx "\n",
		 function,
		 binary_data_offset );

		libcnotify_printf(
		 "%s: normal substitution data:\n",
		 function );
		libcnotify_print_data(
		 xml_document_data,
		 4,
		 0 );
	}
#endif
	byte_stream_copy_to_uint16_little_endian(
	 &( xml_document_data[ 1 ] ),
	 template_value_index );

	template_value_type = xml_document_data[ 3 ];

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: type\t\t\t: 0x%02" PRIx8 "\n",
		 function,
		 xml_document_data[ 0 ] );

		libcnotify_printf(
		 "%s: identifier\t\t: %" PRIu16 "\n",
		 function,
		 template_value_index );

		libcnotify_printf(
		 "%s: value type\t\t: 0x%02" PRIx8 " (",
		 function,
		 template_value_type );
		libfwevt_debug_print_value_type(
		 template_value_type );
		libcnotify_printf(
		 ")\n" );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	xml_token->size = 4;

	result = libfwevt_xml_document_substitute_template_value(
	          internal_xml_document,
	          binary_data,
	          binary_data_size,
	          ascii_codepage,
	          flags,
	          template_values_array,
	          template_value_index,
	          template_value_type,
	          template_value_offset,
	          xml_tag,
	          element_recursion_depth,
	          template_instance_recursion_depth,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to substitute template value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads an optional substitution from a binary XML document
 * Returns 1 if successful, 0 if no substitution or -1 on error
 */
int libfwevt_xml_document_read_optional_substitution(
     libfwevt_internal_xml_document_t *internal_xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     int ascii_codepage,
     uint8_t flags,
     libcdata_array_t *template_values_array,
     size_t *template_value_offset,
     libfwevt_xml_tag_t *xml_tag,
     int element_recursion_depth,
     int template_instance_recursion_depth,
     libcerror_error_t **error )
{
	const uint8_t *xml_document_data = NULL;
	static char *function            = "libfwevt_xml_document_read_optional_substitution";
	size_t xml_document_data_size    = 0;
	uint16_t template_value_index    = 0;
	uint8_t template_value_type      = 0;
	int result                       = 0;

	if( internal_xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
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
	if( xml_token->type != LIBFWEVT_XML_TOKEN_OPTIONAL_SUBSTITUTION )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid binary XML token - unsupported type: 0x%02" PRIx8 ".",
		 function,
		 xml_token->type );

		return( -1 );
	}
	if( binary_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary data.",
		 function );

		return( -1 );
	}
	if( binary_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid binary XML document data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( binary_data_offset >= binary_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary data offset value out of bounds.",
		 function );

		return( -1 );
	}
	xml_document_data      = &( binary_data[ binary_data_offset ] );
	xml_document_data_size = binary_data_size - binary_data_offset;

	if( xml_document_data_size < 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary XML document data size value too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data offset\t\t: 0x%08" PRIzx "\n",
		 function,
		 binary_data_offset );

		libcnotify_printf(
		 "%s: optional substitution data:\n",
		 function );
		libcnotify_print_data(
		 xml_document_data,
		 4,
		 0 );
	}
#endif
	byte_stream_copy_to_uint16_little_endian(
	 &( xml_document_data[ 1 ] ),
	 template_value_index );

	template_value_type = xml_document_data[ 3 ];

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: type\t\t\t: 0x%02" PRIx8 "\n",
		 function,
		 xml_document_data[ 0 ] );

		libcnotify_printf(
		 "%s: identifier\t\t: %" PRIu16 "\n",
		 function,
		 template_value_index );

		libcnotify_printf(
		 "%s: value type\t\t: 0x%02" PRIx8 " (",
		 function,
		 template_value_type );
		libfwevt_debug_print_value_type(
		 template_value_type );
		libcnotify_printf(
		 ")\n" );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	xml_token->size = 4;

	result = libfwevt_xml_document_substitute_template_value(
	          internal_xml_document,
	          binary_data,
	          binary_data_size,
	          ascii_codepage,
	          flags,
	          template_values_array,
	          template_value_index,
	          template_value_type,
	          template_value_offset,
	          xml_tag,
	          element_recursion_depth,
	          template_instance_recursion_depth,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to substitute template value.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Reads a PI data from a binary XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_read_pi_data(
     libfwevt_internal_xml_document_t *internal_xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     libfwevt_xml_tag_t *xml_tag,
     libcerror_error_t **error )
{
	const uint8_t *xml_document_data = NULL;
	static char *function            = "libfwevt_xml_document_read_pi_data";
	size_t value_data_size           = 0;
	size_t xml_document_data_size    = 0;

	if( internal_xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
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
	if( xml_token->type != LIBFWEVT_XML_TOKEN_PI_DATA )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid binary XML token - unsupported type: 0x%02" PRIx8 ".",
		 function,
		 xml_token->type );

		return( -1 );
	}
	if( binary_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary data.",
		 function );

		return( -1 );
	}
	if( binary_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid binary XML document data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( binary_data_offset >= binary_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	xml_document_data      = &( binary_data[ binary_data_offset ] );
	xml_document_data_size = binary_data_size - binary_data_offset;

	if( xml_document_data_size < 3 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary XML document data size value too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data offset\t\t: 0x%08" PRIzx "\n",
		 function,
		 binary_data_offset );

		libcnotify_printf(
		 "%s: PI data:\n",
		 function );
		libcnotify_print_data(
		 xml_document_data,
		 3,
		 0 );
	}
#endif
	byte_stream_copy_to_uint16_little_endian(
	 &( xml_document_data[ 1 ] ),
	 value_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: type\t\t\t\t: 0x%02" PRIx8 "\n",
		 function,
		 xml_document_data[ 0 ] );

		libcnotify_printf(
		 "%s: number of characters\t\t: %" PRIzd "\n",
		 function,
		 value_data_size );
	}
#endif
	xml_token->size     = 3;
	binary_data_offset += 3;

	value_data_size *= 2;

	if( ( value_data_size > binary_data_size )
	 || ( binary_data_offset >= ( binary_data_size - value_data_size ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid value data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data offset\t\t: 0x%08" PRIzx "\n",
		 function,
		 binary_data_offset );

		libcnotify_printf(
		 "%s: value data:\n",
		 function );
		libcnotify_print_data(
		 &( xml_document_data[ 3 ] ),
		 value_data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( libfwevt_xml_tag_set_value_type(
	     xml_tag,
	     LIBFVALUE_VALUE_TYPE_STRING_UTF16,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set value type.",
		 function );

		return( -1 );
	}
	if( libfwevt_xml_tag_set_value_data(
	     xml_tag,
	     &( binary_data[ binary_data_offset ] ),
	     value_data_size,
	     LIBFVALUE_CODEPAGE_UTF16_LITTLE_ENDIAN,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set value data.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libfwevt_xml_tag_value_debug_print(
		     xml_tag,
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print value.",
			 function );

			return( -1 );
		}
	}
#endif
	xml_token->size += value_data_size;

	return( 1 );
}

/* Reads a PI target from a binary XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_read_pi_target(
     libfwevt_internal_xml_document_t *internal_xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     uint8_t flags,
     libfwevt_xml_tag_t *xml_tag,
     libcerror_error_t **error )
{
	libfwevt_xml_tag_t *pi_xml_tag      = NULL;
	libfwevt_xml_token_t *xml_sub_token = NULL;
	const uint8_t *xml_document_data    = NULL;
	static char *function               = "libfwevt_xml_document_read_pi_target";
	size_t additional_value_size        = 0;
	size_t trailing_data_size           = 0;
	size_t xml_document_data_offset     = 0;
	size_t xml_document_data_size       = 0;
	uint32_t pi_name_offset             = 0;
	uint32_t pi_name_size               = 0;

	if( internal_xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
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
	if( xml_token->type != LIBFWEVT_XML_TOKEN_PI_TARGET )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid binary XML token - unsupported type: 0x%02" PRIx8 ".",
		 function,
		 xml_token->type );

		return( -1 );
	}
	if( binary_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary data.",
		 function );

		return( -1 );
	}
	if( binary_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid binary XML document data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( binary_data_offset >= binary_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	if( ( flags & LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS ) != 0 )
	{
		additional_value_size = 4;
	}
	xml_document_data      = &( binary_data[ binary_data_offset ] );
	xml_document_data_size = binary_data_size - binary_data_offset;

	if( xml_document_data_size < ( 1 + additional_value_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary XML document data size value too small.",
		 function );

		return( -1 );
	}
	if( libfwevt_xml_tag_initialize(
	     &pi_xml_tag,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create PI XML tag.",
		 function );

		goto on_error;
	}
	if( libfwevt_xml_tag_set_type(
	     pi_xml_tag,
	     LIBFWEVT_XML_TAG_TYPE_PI,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set XML tag type.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data offset\t\t: 0x%08" PRIzx "\n",
		 function,
		 binary_data_offset );

		libcnotify_printf(
		 "%s: PI target data:\n",
		 function );
		libcnotify_print_data(
		 xml_document_data,
		 1 + additional_value_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: type\t\t\t: 0x%02" PRIx8 "\n",
		 function,
		 xml_document_data[ 0 ] );
	}
#endif
	xml_token->size          = 1;
	xml_document_data_offset = 1;

	if( ( flags & LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS ) == 0 )
	{
		/* TODO double check if this needs to be binary_data_offset + xml_document_data_offset + 1
		 */
		pi_name_offset = (uint32_t) ( binary_data_offset + xml_document_data_offset );
	}
	else
	{
		if( ( xml_document_data_size < 4 )
		 || ( xml_document_data_offset >= ( xml_document_data_size - 4 ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid binary XML document data size value too small.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint32_little_endian(
		 &( xml_document_data[ xml_document_data_offset ] ),
		 pi_name_offset );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: name offset\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 pi_name_offset );
		}
#endif
		xml_token->size           = 4;
		xml_document_data_offset += 4;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif

	/* TODO double check setting this to 5 but this is currently needed
	 * likely because of additional_value_size when LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DATA_OFFSETS is not set
	 */
	xml_token->size          = 5;
	xml_document_data_offset = 5;

	if( pi_name_offset > ( binary_data_offset + xml_document_data_offset ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid PI name offset value out of bounds.",
		 function );

		goto on_error;
	}
	if( ( binary_data_offset + xml_document_data_offset ) < pi_name_offset )
	{
		trailing_data_size = pi_name_offset - ( binary_data_offset + xml_document_data_offset );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: data offset\t\t: 0x%08" PRIzx "\n",
			 function,
			 binary_data_offset + 5 );

			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( xml_document_data[ 5 ] ),
			 trailing_data_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
		xml_token->size          += trailing_data_size;
		xml_document_data_offset += trailing_data_size;
	}
	if( libfwevt_xml_document_read_name(
	     internal_xml_document,
	     binary_data,
	     binary_data_size,
	     pi_name_offset,
	     flags,
	     &pi_name_size,
	     pi_xml_tag,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read PI name.",
		 function );

		goto on_error;
	}
	if( ( binary_data_offset + xml_document_data_offset ) == pi_name_offset )
	{
		xml_token->size          += pi_name_size;
		xml_document_data_offset += pi_name_size;
	}
	if( libfwevt_xml_token_initialize(
	     &xml_sub_token,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create binary XML sub token.",
		 function );

		goto on_error;
	}
	if( libfwevt_xml_token_read_data(
	     xml_sub_token,
	     binary_data,
	     binary_data_size,
	     binary_data_offset + xml_document_data_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read binary XML sub token.",
		 function );

		goto on_error;
	}
	if( libfwevt_xml_document_read_pi_data(
	     internal_xml_document,
	     xml_sub_token,
	     binary_data,
	     binary_data_size,
	     binary_data_offset + xml_document_data_offset,
	     pi_xml_tag,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read PI target.",
		 function );

		goto on_error;
	}
	xml_token->size += xml_sub_token->size;

	if( libfwevt_xml_token_free(
	     &xml_sub_token,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free binary XML sub token.",
		 function );

		goto on_error;
	}
	if( libfwevt_xml_tag_append_element(
	     xml_tag,
	     pi_xml_tag,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append PI to XML tag.",
		 function );

		goto on_error;
	}
	pi_xml_tag = NULL;

	return( 1 );

on_error:
	if( xml_sub_token != NULL )
	{
		libfwevt_xml_token_free(
		 &xml_sub_token,
		 NULL );
	}
	if( pi_xml_tag != NULL )
	{
		libfwevt_internal_xml_tag_free(
		 (libfwevt_internal_xml_tag_t **) &pi_xml_tag,
		 NULL );
	}
	return( -1 );
}

/* Reads a template instance from a binary XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_read_template_instance(
     libfwevt_internal_xml_document_t *internal_xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     int ascii_codepage,
     uint8_t flags,
     libfwevt_xml_tag_t *xml_tag,
     int element_recursion_depth,
     int template_instance_recursion_depth,
     libcerror_error_t **error )
{
	libcdata_array_t *template_values_array  = NULL;
	libfwevt_xml_token_t *xml_sub_token      = NULL;
	const uint8_t *xml_document_data         = NULL;
	static char *function                    = "libfwevt_xml_document_read_template_instance";
	size_t template_data_offset              = 0;
	size_t template_data_size                = 0;
	size_t template_values_data_offset       = 0;
	size_t template_values_data_size         = 0;
	size_t trailing_data_size                = 0;
	size_t xml_document_data_size            = 0;
	uint32_t template_definition_data_offset = 0;
	uint32_t template_definition_data_size   = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit                     = 0;
#endif

	if( internal_xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
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
	if( xml_token->type != LIBFWEVT_XML_TOKEN_TEMPLATE_INSTANCE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid binary XML token - unsupported type: 0x%02" PRIx8 ".",
		 function,
		 xml_token->type );

		return( -1 );
	}
	if( binary_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary data.",
		 function );

		return( -1 );
	}
	if( binary_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid binary XML document data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( binary_data_offset >= binary_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( template_instance_recursion_depth < 0 )
	 || ( template_instance_recursion_depth > LIBFWEVT_XML_DOCUMENT_TEMPLATE_INSTANCE_RECURSION_DEPTH ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid template instance recursion depth value out of bounds.",
		 function );

		return( -1 );
	}
	xml_document_data      = &( binary_data[ binary_data_offset ] );
	xml_document_data_size = binary_data_size - binary_data_offset;

	if( ( binary_data_size < 10 )
	 || ( binary_data_offset >= ( binary_data_size - 10 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary XML document data size value too small.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data offset\t\t: 0x%08" PRIzx "\n",
		 function,
		 binary_data_offset );

		libcnotify_printf(
		 "%s: template instance header data:\n",
		 function );
		libcnotify_print_data(
		 xml_document_data,
		 10,
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 &( xml_document_data[ 6 ] ),
	 template_definition_data_offset );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: type\t\t\t: 0x%02" PRIx8 "\n",
		 function,
		 xml_document_data[ 0 ] );

		libcnotify_printf(
		 "%s: unknown1\t\t\t: %" PRIu8 "\n",
		 function,
		 xml_document_data[ 1 ] );

		byte_stream_copy_to_uint32_little_endian(
		 &( xml_document_data[ 2 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown2\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: data offset\t\t: 0x%08" PRIx32 "\n",
		 function,
		 template_definition_data_offset );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	xml_token->size     = 10;
	binary_data_offset += 10;

	if( template_definition_data_offset >= binary_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid template definition data offset value out of bounds.",
		 function );

		goto on_error;
	}
	if( template_definition_data_offset > binary_data_offset )
	{
		trailing_data_size = template_definition_data_offset - binary_data_offset;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: data offset\t\t: 0x%08" PRIzx "\n",
			 function,
			 binary_data_offset );

			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( binary_data[ binary_data_offset ] ),
			 trailing_data_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
		xml_token->size    += trailing_data_size;
		binary_data_offset += trailing_data_size;
	}
	template_data_offset = template_definition_data_offset;

	if( ( binary_data_size < 24 )
	 || ( template_data_offset >= ( binary_data_size - 24 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary XML document data size value too small.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint32_little_endian(
	 &( binary_data[ template_data_offset + 20 ] ),
	 template_definition_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 &( binary_data[ template_data_offset ] ),
		 value_32bit );
		libcnotify_printf(
		 "%s: offset next\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( libfwevt_debug_print_guid_value(
		     function,
		     "identifier\t\t",
		     &( binary_data[ template_data_offset + 4 ] ),
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
		     LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print GUID value.",
			 function );

			return( -1 );
		}
		libcnotify_printf(
		 "%s: definition size\t\t: %" PRIu32 "\n",
		 function,
		 template_definition_data_size );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( template_definition_data_size > binary_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid template definition data size value out of bounds.",
		 function );

		goto on_error;
	}
	if( template_data_offset == binary_data_offset )
	{
		template_values_data_offset = 24 + template_definition_data_size;
	}
	else
	{
		template_values_data_offset = 0;
	}
	template_data_offset += 24;

	if( template_values_data_offset >= xml_document_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid template values data offset value out of bounds.",
		 function );

		goto on_error;
	}
	if( libfwevt_xml_document_read_template_instance_values(
	     internal_xml_document,
	     binary_data,
	     binary_data_size,
	     binary_data_offset + template_values_data_offset,
	     &template_values_array,
	     &template_values_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read document template instance values.",
		 function );

		goto on_error;
	}
	xml_token->size += template_values_data_size;

	if( libfwevt_xml_token_initialize(
	     &xml_sub_token,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create binary XML sub token.",
		 function );

		goto on_error;
	}
	if( libfwevt_xml_token_read_data(
	     xml_sub_token,
	     binary_data,
	     binary_data_size,
	     template_data_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read binary XML sub token.",
		 function );

		goto on_error;
	}
	if( libfwevt_xml_document_read_fragment_header(
	     internal_xml_document,
	     xml_sub_token,
	     binary_data,
	     binary_data_size,
	     template_data_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read fragment header.",
		 function );

		goto on_error;
	}
	template_data_offset += xml_sub_token->size;

	if( libfwevt_xml_token_read_data(
	     xml_sub_token,
	     binary_data,
	     binary_data_size,
	     template_data_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read binary XML sub token.",
		 function );

		goto on_error;
	}
	if( libfwevt_xml_document_read_element(
	     internal_xml_document,
	     xml_sub_token,
	     binary_data,
	     binary_data_size,
	     template_data_offset,
	     ascii_codepage,
	     flags,
	     template_values_array,
	     xml_tag,
	     element_recursion_depth + 1,
	     template_instance_recursion_depth,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read element.",
		 function );

		goto on_error;
	}
	template_data_offset += xml_sub_token->size;

	if( libfwevt_xml_token_read_data(
	     xml_sub_token,
	     binary_data,
	     binary_data_size,
	     template_data_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read binary XML sub token.",
		 function );

		goto on_error;
	}
	if( xml_sub_token->type != LIBFWEVT_XML_TOKEN_END_OF_FILE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid binary XML token - unsupported type: 0x%02" PRIx8 ".",
		 function,
		 xml_token->type );

		goto on_error;
	}
	if( binary_data_offset >= ( binary_data_size - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary XML document data size value too small.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data offset\t\t: 0x%08" PRIzx "\n",
		 function,
		 binary_data_offset );

		libcnotify_printf(
		 "%s: end of file data:\n",
		 function );
		libcnotify_print_data(
		 &( binary_data[ binary_data_offset ] ),
		 1,
		 0 );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: type\t\t\t: 0x%02" PRIx8 "\n",
		 function,
		 binary_data[ binary_data_offset ] );

		libcnotify_printf(
		 "\n" );
	}
#endif
	template_data_offset += 1;

	if( libfwevt_xml_token_free(
	     &xml_sub_token,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free binary XML sub token.",
		 function );

		goto on_error;
	}
	if( template_definition_data_offset == binary_data_offset )
	{
		template_data_size = template_data_offset
		                   - template_definition_data_offset;

		xml_token->size += template_data_size;

		/* The template data size does not include the first 33 bytes
		 * of the template definition
		 * In this case the template data size contains 24 of the 33 bytes
		 */
		if( template_definition_data_size < ( template_data_size - 24 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid template definition data size value too small.",
			 function );

			goto on_error;
		}
		template_definition_data_size -= (uint32_t) ( template_data_size - 24 );
	}
/* TODO check if template_definition_data_size is 0 */

	if( libcdata_array_free(
	     &template_values_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_xml_template_value_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free template values array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( template_values_array != NULL )
	{
		libcdata_array_free(
		 &template_values_array,
		 (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_xml_template_value_free,
		 NULL );
	}
	if( xml_sub_token != NULL )
	{
		libfwevt_xml_token_free(
		 &xml_sub_token,
		 NULL );
	}
	return( -1 );
}

/* Reads the template instance values from a binary XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_read_template_instance_values(
     libfwevt_internal_xml_document_t *internal_xml_document,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     libcdata_array_t **template_values_array,
     size_t *template_values_size,
     libcerror_error_t **error )
{
	libfwevt_xml_template_value_t *template_value = NULL;
	static char *function                         = "libfwevt_xml_document_read_template_instance_values";
	size_t safe_template_values_size              = 0;
	size_t template_value_definitions_data_size   = 0;
	size_t template_values_data_size              = 0;
	uint32_t number_of_template_values            = 0;
	uint32_t template_value_index                 = 0;
	uint16_t template_value_data_size             = 0;
	uint8_t template_value_type                   = 0;

	if( internal_xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
	if( ( binary_data_size < 4 )
	 || ( binary_data_offset >= ( binary_data_size - 4 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( template_values_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template values size.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data offset\t: 0x%08" PRIzx "\n",
		 function,
		 binary_data_offset );

		libcnotify_printf(
		 "%s: template instance data:\n",
		 function );
		libcnotify_print_data(
		 &( binary_data[ binary_data_offset ] ),
		 4,
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 &( binary_data[ binary_data_offset ] ),
	 number_of_template_values );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: number of values\t: %" PRIu32 "\n",
		 function,
		 number_of_template_values );

		libcnotify_printf(
		 "\n" );
	}
#endif
	safe_template_values_size = 4;
	binary_data_offset       += 4;

	template_value_definitions_data_size = number_of_template_values * 4;

	if( ( template_value_definitions_data_size > binary_data_size )
	 || ( binary_data_offset >= ( binary_data_size - template_value_definitions_data_size ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid template value definitions data size value out of bounds.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data offset\t: 0x%08" PRIzx "\n",
		 function,
		 binary_data_offset );

		libcnotify_printf(
		 "%s: template instance value descriptor data:\n",
		 function );
		libcnotify_print_data(
		 &( binary_data[ binary_data_offset ] ),
		 template_value_definitions_data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( libcdata_array_initialize(
	     template_values_array,
	     number_of_template_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create template values array.",
		 function );

		goto on_error;
	}
	for( template_value_index = 0;
	     template_value_index < number_of_template_values;
	     template_value_index++ )
	{
		byte_stream_copy_to_uint16_little_endian(
		 &( binary_data[ binary_data_offset ] ),
		 template_value_data_size );

		template_value_type = binary_data[ binary_data_offset + 2 ];

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value: %02" PRIu32 " size\t: %" PRIu16 "\n",
			 function,
			 template_value_index,
			 template_value_data_size );

			libcnotify_printf(
			 "%s: value: %02" PRIu32 " type\t: 0x%02" PRIx8 " (",
			 function,
			 template_value_index,
			 template_value_type );
			libfwevt_debug_print_value_type(
			 template_value_type );
			libcnotify_printf(
			 ")\n" );

			libcnotify_printf(
			 "%s: value: %02" PRIu32 " unknown1\t: 0x%02" PRIx8 "\n",
			 function,
			 template_value_index,
			 binary_data[ binary_data_offset + 3 ] );

			libcnotify_printf(
			 "\n" );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		safe_template_values_size += 4;
		binary_data_offset        += 4;

		template_values_data_size += template_value_data_size;

		if( libfwevt_xml_template_value_initialize(
		     &template_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create template value.",
			 function );

			goto on_error;
		}
		if( libfwevt_xml_template_value_set_type(
		     template_value,
		     template_value_type,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set template value type.",
			 function );

			libfwevt_xml_template_value_free(
			 &template_value,
			 NULL );

			goto on_error;
		}
		if( libfwevt_xml_template_value_set_size(
		     template_value,
		     template_value_data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set template value data size.",
			 function );

			libfwevt_xml_template_value_free(
			 &template_value,
			 NULL );

			goto on_error;
		}
		if( libcdata_array_set_entry_by_index(
		     *template_values_array,
		     (int) template_value_index,
		     (intptr_t *) template_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set template value: %" PRIu32 " in array.",
			 function,
			 template_value_index );

			libfwevt_xml_template_value_free(
			 &template_value,
			 NULL );

			goto on_error;
		}
		template_value = NULL;
	}
	if( ( template_values_data_size > binary_data_size )
	 || ( binary_data_offset >= ( binary_data_size - template_values_data_size ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid template values data size value out of bounds.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data offset\t: 0x%08" PRIzx "\n",
		 function,
		 binary_data_offset );

		libcnotify_printf(
		 "%s: values data:\n",
		 function );
		libcnotify_print_data(
		 &( binary_data[ binary_data_offset ] ),
		 template_values_data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	for( template_value_index = 0;
	     template_value_index < number_of_template_values;
	     template_value_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     *template_values_array,
		     (int) template_value_index,
		     (intptr_t **) &template_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve template value: %" PRIu32 " from array.",
			 function,
			 template_value_index );

			goto on_error;
		}
		if( libfwevt_xml_template_value_get_size(
		     template_value,
		     &template_value_data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve template value data size.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: data offset\t: 0x%08" PRIzx "\n",
			 function,
			 binary_data_offset );

			libcnotify_printf(
			 "%s: value: %02" PRIu32 " data:\n",
			 function,
			 template_value_index );
			libcnotify_print_data(
			 &( binary_data[ binary_data_offset ] ),
			 template_value_data_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
		/* Note that template_value_data_size is allowed to be 0.
		 * Don't set the template value offset in such a case.
		 */
		if( template_value_data_size == 0 )
		{
			continue;
		}
		if( libfwevt_xml_template_value_set_offset(
		     template_value,
		     binary_data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set template value data offset.",
			 function );

			goto on_error;
		}
		binary_data_offset += template_value_data_size;
	}
	*template_values_size = safe_template_values_size + template_values_data_size;

	return( 1 );

on_error:
	if( template_values_array != NULL )
	{
		libcdata_array_free(
		 template_values_array,
		 (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_xml_template_value_free,
		 NULL );
	}
	return( -1 );
}

/* Reads a value from a binary XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_read_value(
     libfwevt_internal_xml_document_t *internal_xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     libfwevt_xml_tag_t *xml_tag,
     libcerror_error_t **error )
{
	const uint8_t *xml_document_data = NULL;
	static char *function            = "libfwevt_xml_document_read_value";
	size_t value_data_size           = 0;
	size_t xml_document_data_size    = 0;
	uint8_t xml_value_type           = 0;
	int value_encoding               = 0;
	int value_entry_index            = 0;
	int value_type                   = 0;

	if( internal_xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
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
	if( ( xml_token->type & 0xbf ) != LIBFWEVT_XML_TOKEN_VALUE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid binary XML token - unsupported type: 0x%02" PRIx8 ".",
		 function,
		 xml_token->type );

		return( -1 );
	}
	if( binary_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary data.",
		 function );

		return( -1 );
	}
	if( binary_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid binary XML document data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( binary_data_offset >= binary_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	xml_document_data      = &( binary_data[ binary_data_offset ] );
	xml_document_data_size = binary_data_size - binary_data_offset;

	if( xml_document_data_size < 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary XML document data size value too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data offset\t\t\t\t: 0x%08" PRIzx "\n",
		 function,
		 binary_data_offset );

		libcnotify_printf(
		 "%s: value data:\n",
		 function );
		libcnotify_print_data(
		 xml_document_data,
		 4,
		 0 );
	}
#endif
	xml_value_type = xml_document_data[ 1 ];

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: type\t\t\t\t\t: 0x%02" PRIx8 "\n",
		 function,
		 xml_document_data[ 0 ] );

		libcnotify_printf(
		 "%s: value type\t\t\t\t: 0x%02" PRIx8 " (",
		 function,
		 xml_value_type );
		libfwevt_debug_print_value_type(
		 xml_value_type );
		libcnotify_printf(
		 ")\n" );
	}
#endif
	xml_token->size     = 4;
	binary_data_offset += 4;

	switch( xml_value_type )
	{
		case LIBFWEVT_VALUE_TYPE_STRING_UTF16:
			byte_stream_copy_to_uint16_little_endian(
			 &( xml_document_data[ 2 ] ),
			 value_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: number of characters\t\t\t: %" PRIzd "\n",
				 function,
				 value_data_size );
			}
#endif
			value_data_size *= 2;

			value_encoding = LIBFVALUE_CODEPAGE_UTF16_LITTLE_ENDIAN;
			value_type     = LIBFVALUE_VALUE_TYPE_STRING_UTF16;

			break;

		default:
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported value type: 0x%02" PRIx8 ".",
			 function,
			 value_type );

			return( -1 );
	}
	if( ( value_data_size > binary_data_size )
	 || ( binary_data_offset >= ( binary_data_size - value_data_size ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid value data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data offset\t\t\t\t: 0x%08" PRIzx "\n",
		 function,
		 binary_data_offset );

		libcnotify_printf(
		 "%s: value data:\n",
		 function );
		libcnotify_print_data(
		 &( binary_data[ binary_data_offset ] ),
		 value_data_size,
		 0 );
	}
#endif
	if( libfwevt_xml_tag_set_value_type(
	     xml_tag,
	     value_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set value type.",
		 function );

		return( -1 );
	}
	if( libfwevt_xml_tag_append_value_data(
	     xml_tag,
	     &( binary_data[ binary_data_offset ] ),
	     value_data_size,
	     value_encoding,
	     &value_entry_index,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append value data.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libfwevt_xml_tag_value_debug_print(
		     xml_tag,
		     value_entry_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print value: %d.",
			 function,
			 value_entry_index );

			return( -1 );
		}
	}
#endif
	xml_token->size += value_data_size;
	
	return( 1 );
}

/* Substitutes a substitution placeholder with a template value
 * Returns 1 if successful, 0 if no substitution or -1 on error
 */
int libfwevt_xml_document_substitute_template_value(
     libfwevt_internal_xml_document_t *internal_xml_document,
     const uint8_t *binary_data,
     size_t binary_data_size,
     int ascii_codepage,
     uint8_t flags,
     libcdata_array_t *template_values_array,
     uint16_t template_value_index,
     uint8_t template_value_type,
     size_t *template_value_offset,
     libfwevt_xml_tag_t *xml_tag,
     int element_recursion_depth,
     int template_instance_recursion_depth,
     libcerror_error_t **error )
{
	libfwevt_xml_template_value_t *template_value = NULL;
	libfwevt_xml_token_t *xml_sub_token           = NULL;
	const uint8_t *template_value_data            = NULL;
	static char *function                         = "libfwevt_xml_document_substitute_template_value";
	size_t binary_data_offset                     = 0;
	size_t safe_template_value_offset             = 0;
	size_t template_value_data_size               = 0;
	size_t template_value_size                    = 0;
	ssize_t read_count                            = 0;
	uint32_t value_format_flags                   = 0;
	uint16_t substitution_value_data_size         = 0;
	uint8_t substitution_value_type               = 0;
	uint8_t template_value_flags                  = 0;
	int value_encoding                            = 0;
	int value_type                                = 0;

	if( internal_xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
	if( template_value_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template value offset.",
		 function );

		return( -1 );
	}
	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     template_values_array,
	     (int) template_value_index,
	     (intptr_t **) &template_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve template value: %" PRIu16 " from array.",
		 function,
		 template_value_index );

		goto on_error;
	}
	if( libfwevt_xml_template_value_get_flags(
	     template_value,
	     &template_value_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve template value flags.",
		 function );

		goto on_error;
	}
	if( ( template_value_flags & LIBFWEVT_XML_TEMPLATE_VALUE_FLAG_IS_DEFINITION ) != 0 )
	{
		substitution_value_type = LIBFWEVT_VALUE_TYPE_STRING_UTF16;
	}
	else
	{
		if( libfwevt_xml_template_value_get_type(
		     template_value,
		     &substitution_value_type,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve template value type.",
			 function );

			goto on_error;
		}
	}
	if( libfwevt_xml_template_value_get_offset(
	     template_value,
	     &binary_data_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve template value data offset.",
		 function );

		goto on_error;
	}
	if( libfwevt_xml_template_value_get_size(
	     template_value,
	     &substitution_value_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve template value data size.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: value: %02" PRIu32 " offset\t: 0x%08" PRIzx "\n",
		 function,
		 template_value_index,
		 binary_data_offset );

		libcnotify_printf(
		 "%s: value: %02" PRIu32 " size\t\t: %" PRIu16 "\n",
		 function,
		 template_value_index,
		 substitution_value_data_size );

		libcnotify_printf(
		 "%s: value: %02" PRIu32 " type\t\t: 0x%02" PRIx8 " (",
		 function,
		 template_value_index,
		 substitution_value_type );
		libfwevt_debug_print_value_type(
		 substitution_value_type );
		libcnotify_printf(
		 ")\n" );

		libcnotify_printf(
		 "%s: value: %02" PRIu32 " data:\n",
		 function,
		 template_value_index );
		libcnotify_print_data(
		 &( binary_data[ binary_data_offset ] ),
		 substitution_value_data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	/* No substitution
	 */
	if( substitution_value_type == LIBFWEVT_VALUE_TYPE_NULL )
	{
		*template_value_offset = 0;

		return( 0 );
	}
#if defined( HAVE_VERBOSE_OUTPUT )
	if( template_value_type != substitution_value_type )
	{
		/* The size type can be substituded by a 32-bit or 64-bit hexadecimal integer
		 * The same applies to it's array type
		 */
		if( ( ( template_value_type & 0x7f ) != LIBFWEVT_VALUE_TYPE_SIZE )
		 || ( ( ( substitution_value_type & 0x7f ) != LIBFWEVT_VALUE_TYPE_HEXADECIMAL_INTEGER_32BIT )
		  &&  ( ( substitution_value_type & 0x7f ) != LIBFWEVT_VALUE_TYPE_HEXADECIMAL_INTEGER_64BIT ) ) )
		{
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: mismatch in value type ( 0x%02" PRIx8 " != 0x%02" PRIx8 " ).\n",
				 function,
				 template_value_type,
				 substitution_value_type );
			}
		}
	}
#endif /* defined( HAVE_VERBOSE_OUTPUT ) */

	if( substitution_value_type == LIBFWEVT_VALUE_TYPE_BINARY_XML )
	{
		if( libfwevt_xml_token_initialize(
		     &xml_sub_token,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create binary XML sub token.",
			 function );

			goto on_error;
		}
		if( libfwevt_xml_token_read_data(
		     xml_sub_token,
		     binary_data,
		     binary_data_size,
		     binary_data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read binary XML sub token.",
			 function );

			goto on_error;
		}
		switch( xml_sub_token->type & 0xbf )
		{
			case LIBFWEVT_XML_TOKEN_OPEN_START_ELEMENT_TAG:
				if( libfwevt_xml_document_read_element(
				     internal_xml_document,
				     xml_sub_token,
				     binary_data,
				     binary_data_size,
				     binary_data_offset,
				     ascii_codepage,
				     flags,
				     template_values_array,
				     xml_tag,
				     element_recursion_depth + 1,
				     template_instance_recursion_depth,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read element.",
					 function );

					goto on_error;
				}
				break;

			case LIBFWEVT_XML_TOKEN_FRAGMENT_HEADER:
				if( libfwevt_xml_document_read_fragment(
				     internal_xml_document,
				     xml_sub_token,
				     binary_data,
				     binary_data_size,
				     binary_data_offset,
				     ascii_codepage,
				     flags,
				     NULL,
				     xml_tag,
				     element_recursion_depth,
				     template_instance_recursion_depth,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read fragment header.",
					 function );

					goto on_error;
				}
				break;

			case LIBFWEVT_XML_TOKEN_TEMPLATE_INSTANCE:
				if( libfwevt_xml_document_read_template_instance(
				     internal_xml_document,
				     xml_sub_token,
				     binary_data,
				     binary_data_size,
				     binary_data_offset,
				     ascii_codepage,
				     flags,
				     xml_tag,
				     element_recursion_depth,
				     template_instance_recursion_depth + 1,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read document template instance.",
					 function );

					goto on_error;
				}
				break;

			default:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: invalid binary XML token - unsupported type: 0x%02" PRIx8 ".",
				 function,
				 xml_sub_token->type );

				goto on_error;
		}
		if( libfwevt_xml_token_free(
		     &xml_sub_token,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free binary XML sub token.",
			 function );

			goto on_error;
		}
	}
	else
	{
/* TODO for now the array types are kept separate to find undocumented values
 * when done apply ( substitution_value_type & 0x7f ) and remove the array types
 */
		switch( substitution_value_type )
		{
			case LIBFWEVT_VALUE_TYPE_STRING_UTF16:
			case LIBFWEVT_VALUE_TYPE_ARRAY_OF_STRING_UTF16:
				value_encoding = LIBFVALUE_CODEPAGE_UTF16_LITTLE_ENDIAN;
				value_type     = LIBFVALUE_VALUE_TYPE_STRING_UTF16;
				break;

			case LIBFWEVT_VALUE_TYPE_STRING_BYTE_STREAM:
			case LIBFWEVT_VALUE_TYPE_ARRAY_OF_STRING_BYTE_STREAM:
				value_encoding = ascii_codepage;
				value_type     = LIBFVALUE_VALUE_TYPE_STRING_BYTE_STREAM;
				break;

			case LIBFWEVT_VALUE_TYPE_INTEGER_8BIT:
			case LIBFWEVT_VALUE_TYPE_ARRAY_OF_INTEGER_8BIT:
				template_value_size = 1;
				value_encoding      = LIBFVALUE_ENDIAN_LITTLE;
				value_format_flags  = LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL_SIGNED;
				value_type          = LIBFVALUE_VALUE_TYPE_INTEGER_8BIT;
				break;

			case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_8BIT:
			case LIBFWEVT_VALUE_TYPE_ARRAY_OF_UNSIGNED_INTEGER_8BIT:
				template_value_size = 1;
				value_encoding      = LIBFVALUE_ENDIAN_LITTLE;
				value_format_flags  = LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL_UNSIGNED;
				value_type          = LIBFVALUE_VALUE_TYPE_UNSIGNED_INTEGER_8BIT;
				break;

			case LIBFWEVT_VALUE_TYPE_INTEGER_16BIT:
			case LIBFWEVT_VALUE_TYPE_ARRAY_OF_INTEGER_16BIT:
				template_value_size = 2;
				value_encoding      = LIBFVALUE_ENDIAN_LITTLE;
				value_format_flags  = LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL_SIGNED;
				value_type          = LIBFVALUE_VALUE_TYPE_INTEGER_16BIT;
				break;

			case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_16BIT:
			case LIBFWEVT_VALUE_TYPE_ARRAY_OF_UNSIGNED_INTEGER_16BIT:
				template_value_size = 2;
				value_encoding      = LIBFVALUE_ENDIAN_LITTLE;
				value_format_flags  = LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL_UNSIGNED;
				value_type          = LIBFVALUE_VALUE_TYPE_UNSIGNED_INTEGER_16BIT;
				break;

			case LIBFWEVT_VALUE_TYPE_INTEGER_32BIT:
			case LIBFWEVT_VALUE_TYPE_ARRAY_OF_INTEGER_32BIT:
				template_value_size = 4;
				value_encoding      = LIBFVALUE_ENDIAN_LITTLE;
				value_format_flags  = LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL_SIGNED;
				value_type          = LIBFVALUE_VALUE_TYPE_INTEGER_32BIT;
				break;

			case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_32BIT:
			case LIBFWEVT_VALUE_TYPE_ARRAY_OF_UNSIGNED_INTEGER_32BIT:
				template_value_size = 4;
				value_encoding      = LIBFVALUE_ENDIAN_LITTLE;
				value_format_flags  = LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL_UNSIGNED;
				value_type          = LIBFVALUE_VALUE_TYPE_UNSIGNED_INTEGER_32BIT;
				break;

			case LIBFWEVT_VALUE_TYPE_HEXADECIMAL_INTEGER_32BIT:
			case LIBFWEVT_VALUE_TYPE_ARRAY_OF_HEXADECIMAL_INTEGER_32BIT:
				template_value_size = 4;
				value_encoding      = LIBFVALUE_ENDIAN_LITTLE;
				value_format_flags  = LIBFVALUE_INTEGER_FORMAT_TYPE_HEXADECIMAL;
				value_type          = LIBFVALUE_VALUE_TYPE_UNSIGNED_INTEGER_32BIT;
				break;

			case LIBFWEVT_VALUE_TYPE_INTEGER_64BIT:
			case LIBFWEVT_VALUE_TYPE_ARRAY_OF_INTEGER_64BIT:
				template_value_size = 8;
				value_encoding      = LIBFVALUE_ENDIAN_LITTLE;
				value_format_flags  = LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL_SIGNED;
				value_type          = LIBFVALUE_VALUE_TYPE_INTEGER_64BIT;
				break;

			case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_64BIT:
			case LIBFWEVT_VALUE_TYPE_ARRAY_OF_UNSIGNED_INTEGER_64BIT:
				template_value_size = 8;
				value_encoding      = LIBFVALUE_ENDIAN_LITTLE;
				value_format_flags  = LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL_UNSIGNED;
				value_type          = LIBFVALUE_VALUE_TYPE_UNSIGNED_INTEGER_64BIT;
				break;

			case LIBFWEVT_VALUE_TYPE_HEXADECIMAL_INTEGER_64BIT:
			case LIBFWEVT_VALUE_TYPE_ARRAY_OF_HEXADECIMAL_INTEGER_64BIT:
				template_value_size = 8;
				value_encoding      = LIBFVALUE_ENDIAN_LITTLE;
				value_format_flags  = LIBFVALUE_INTEGER_FORMAT_TYPE_HEXADECIMAL;
				value_type          = LIBFVALUE_VALUE_TYPE_UNSIGNED_INTEGER_64BIT;
				break;

			case LIBFWEVT_VALUE_TYPE_FLOATING_POINT_32BIT:
			case LIBFWEVT_VALUE_TYPE_ARRAY_OF_FLOATING_POINT_32BIT:
				template_value_size = 4;
				value_encoding      = LIBFVALUE_ENDIAN_LITTLE;
				value_format_flags  = LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_DECIMAL;
				value_type          = LIBFVALUE_VALUE_TYPE_FLOATING_POINT_32BIT;
				break;

			case LIBFWEVT_VALUE_TYPE_FLOATING_POINT_64BIT:
			case LIBFWEVT_VALUE_TYPE_ARRAY_OF_FLOATING_POINT_64BIT:
				template_value_size = 8;
				value_encoding      = LIBFVALUE_ENDIAN_LITTLE;
				value_format_flags  = LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_DECIMAL;
				value_type          = LIBFVALUE_VALUE_TYPE_FLOATING_POINT_64BIT;
				break;

			case LIBFWEVT_VALUE_TYPE_BOOLEAN:
				template_value_size = 4;
				value_encoding      = LIBFVALUE_ENDIAN_LITTLE;
				value_format_flags  = LIBFVALUE_INTEGER_FORMAT_TYPE_BOOLEAN;
				value_type          = LIBFVALUE_VALUE_TYPE_BOOLEAN;
				break;

			case LIBFWEVT_VALUE_TYPE_BINARY_DATA:
				value_format_flags = LIBFVALUE_BINARY_DATA_FORMAT_TYPE_BASE16
				                   | LIBFVALUE_BINARY_DATA_FORMAT_FLAG_CASE_UPPER;
				value_type         = LIBFVALUE_VALUE_TYPE_BINARY_DATA;
				break;

			case LIBFWEVT_VALUE_TYPE_GUID:
			case LIBFWEVT_VALUE_TYPE_ARRAY_OF_GUID:
				template_value_size = 16;
				value_encoding      = LIBFVALUE_ENDIAN_LITTLE;
				value_format_flags  = LIBFVALUE_GUID_FORMAT_FLAG_USE_UPPER_CASE | LIBFVALUE_GUID_FORMAT_FLAG_USE_SURROUNDING_BRACES;
				value_type          = LIBFVALUE_VALUE_TYPE_GUID;
				break;

/* TODO how to deal with array types ? */
			case LIBFWEVT_VALUE_TYPE_SIZE:
				value_encoding     = LIBFVALUE_ENDIAN_LITTLE;
				value_format_flags = LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL_UNSIGNED;

				if( substitution_value_data_size == 4 )
				{
					value_type = LIBFVALUE_VALUE_TYPE_UNSIGNED_INTEGER_32BIT;
				}
				else if( substitution_value_data_size == 8 )
				{
					value_type = LIBFVALUE_VALUE_TYPE_UNSIGNED_INTEGER_64BIT;
				}
				else
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
					 "%s: unsupported value data size: %" PRIu16 ".",
					 function,
					 substitution_value_data_size );

					goto on_error;
				}
				break;

			case LIBFWEVT_VALUE_TYPE_FILETIME:
			case LIBFWEVT_VALUE_TYPE_ARRAY_OF_FILETIME:
				template_value_size = 8;
				value_encoding      = LIBFVALUE_ENDIAN_LITTLE;
				value_format_flags  = (uint32_t) ( LIBFVALUE_DATE_TIME_FORMAT_TYPE_ISO8601 | LIBFVALUE_DATE_TIME_FORMAT_FLAG_DATE_TIME_NANO_SECONDS | LIBFVALUE_DATE_TIME_FORMAT_FLAG_TIMEZONE_INDICATOR );
				value_type          = LIBFVALUE_VALUE_TYPE_FILETIME;
				break;

			case LIBFWEVT_VALUE_TYPE_SYSTEMTIME:
			case LIBFWEVT_VALUE_TYPE_ARRAY_OF_SYSTEMTIME:
				template_value_size = 16;
				value_encoding      = LIBFVALUE_ENDIAN_LITTLE;
				value_format_flags  = (uint32_t) ( LIBFVALUE_DATE_TIME_FORMAT_TYPE_ISO8601 | LIBFVALUE_DATE_TIME_FORMAT_FLAG_DATE_TIME_MILLI_SECONDS | LIBFVALUE_DATE_TIME_FORMAT_FLAG_TIMEZONE_INDICATOR );
				value_type          = LIBFVALUE_VALUE_TYPE_SYSTEMTIME;
				break;

			case LIBFWEVT_VALUE_TYPE_NT_SECURITY_IDENTIFIER:
				value_encoding = LIBFVALUE_ENDIAN_LITTLE;
				value_type     = LIBFVALUE_VALUE_TYPE_NT_SECURITY_IDENTIFIER;
				break;

			default:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported value type: 0x%02" PRIx8 ".",
				 function,
				 substitution_value_type );

				goto on_error;
		}
		if( libfwevt_xml_tag_set_value_type(
		     xml_tag,
		     value_type,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set value type.",
			 function );

			goto on_error;
		}
		if( value_format_flags != 0 )
		{
			if( libfwevt_xml_tag_set_value_format_flags(
			     xml_tag,
			     value_format_flags,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set value format flags.",
				 function );

				goto on_error;
			}
		}
		if( ( substitution_value_type & LIBFWEVT_VALUE_TYPE_ARRAY ) != 0 )
		{
			safe_template_value_offset = *template_value_offset;

			if( substitution_value_data_size > 0 )
			{
				if( safe_template_value_offset >= (size_t) substitution_value_data_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: invalid template value offset value out of bounds.",
					 function );

					goto on_error;
				}
				template_value_data      = &( binary_data[ binary_data_offset + safe_template_value_offset ] );
				template_value_data_size = substitution_value_data_size - (uint16_t) safe_template_value_offset;
			}
			/* An empty XML tag should be created if template_value_data_size == 0
			 */
			if( template_value_data_size > 0 )
			{
				if( ( substitution_value_type == LIBFWEVT_VALUE_TYPE_ARRAY_OF_STRING_BYTE_STREAM )
				 || ( substitution_value_type == LIBFWEVT_VALUE_TYPE_ARRAY_OF_STRING_UTF16 ) )
				{
					if( ( value_type == LIBFVALUE_VALUE_TYPE_STRING_UTF16 )
					 && ( ( template_value_data_size % 2 ) != 0 ) )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
						 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
						 "%s: invalid UTF-16 template value data size value out of bounds.",
						 function );

						goto on_error;
					}
					read_count = libfwevt_xml_tag_set_value_strings_array(
						      xml_tag,
						      template_value_data,
						      template_value_data_size,
						      value_encoding,
						      error );

					if( read_count == -1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
						 "%s: unable to set value data.",
						 function );

						goto on_error;
					}
					safe_template_value_offset += read_count;
				}
				else
				{
					if( template_value_size > template_value_data_size )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
						 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
						 "%s: invalid template value size value out of bounds.",
						 function );

						goto on_error;
					}
					if( libfwevt_xml_tag_set_value_data(
					     xml_tag,
					     template_value_data,
					     template_value_size,
					     value_encoding,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
						 "%s: unable to set value data.",
						 function );

						goto on_error;
					}
					safe_template_value_offset += template_value_size;
				}
			}
			if( safe_template_value_offset == substitution_value_data_size )
			{
				safe_template_value_offset = 0;
			}
		}
		else
		{
			if( ( template_value_size != 0 )
			 && ( template_value_size != substitution_value_data_size ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid substitution value data size value out of bounds.",
				 function );

				goto on_error;
			}
			else if( ( value_type == LIBFVALUE_VALUE_TYPE_STRING_UTF16 )
			      && ( ( substitution_value_data_size % 2 ) != 0 ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid UTF-16 substitution value data size value out of bounds.",
				 function );

				goto on_error;
			}
			if( libfwevt_xml_tag_set_value_data(
			     xml_tag,
			     &( binary_data[ binary_data_offset ] ),
			     (size_t) substitution_value_data_size,
			     value_encoding,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set value data.",
				 function );

				goto on_error;
			}
		}
		if( libfwevt_xml_tag_set_flags(
		     xml_tag,
		     LIBFWEVT_XML_TAG_FLAG_IS_TEMPLATE_DEFINITION,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set flags.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( libfwevt_xml_tag_value_debug_print(
			     xml_tag,
			     0,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print value.",
				 function );

				goto on_error;
			}
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
	}
	*template_value_offset = safe_template_value_offset;

	return( 1 );

on_error:
	if( xml_sub_token != NULL )
	{
		libfwevt_xml_token_free(
		 &xml_sub_token,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the size of the UTF-8 formatted string of the XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_get_utf8_xml_string_size(
     libfwevt_xml_document_t *xml_document,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_document_t *internal_xml_document = NULL;
	static char *function                                   = "libfwevt_xml_document_get_utf8_xml_string_size";

	if( xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML document.",
		 function );

		return( -1 );
	}
	internal_xml_document = (libfwevt_internal_xml_document_t *) xml_document;

	if( libfwevt_xml_tag_get_utf8_xml_string_size(
	     internal_xml_document->root_xml_tag,
	     0,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size of UTF-8 string of root XML tag.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 formatted string of the XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_get_utf8_xml_string(
     libfwevt_xml_document_t *xml_document,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_document_t *internal_xml_document = NULL;
	static char *function                                   = "libfwevt_xml_document_get_utf8_xml_string";
	size_t utf8_string_index                                = 0;

	if( xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML document.",
		 function );

		return( -1 );
	}
	internal_xml_document = (libfwevt_internal_xml_document_t *) xml_document;

	if( libfwevt_xml_tag_get_utf8_xml_string_with_index(
	     internal_xml_document->root_xml_tag,
	     0,
	     utf8_string,
	     utf8_string_size,
	     &utf8_string_index,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string of root XML tag.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 formatted string of the XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_get_utf16_xml_string_size(
     libfwevt_xml_document_t *xml_document,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_document_t *internal_xml_document = NULL;
	static char *function                                   = "libfwevt_xml_document_get_utf16_xml_string_size";

	if( xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML document.",
		 function );

		return( -1 );
	}
	internal_xml_document = (libfwevt_internal_xml_document_t *) xml_document;

	if( libfwevt_xml_tag_get_utf16_xml_string_size(
	     internal_xml_document->root_xml_tag,
	     0,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size of UTF-16 string of root XML tag.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 formatted string of the XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_get_utf16_xml_string(
     libfwevt_xml_document_t *xml_document,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_document_t *internal_xml_document = NULL;
	static char *function                                   = "libfwevt_xml_document_get_utf16_xml_string";
	size_t utf16_string_index                               = 0;

	if( xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML document.",
		 function );

		return( -1 );
	}
	internal_xml_document = (libfwevt_internal_xml_document_t *) xml_document;

	if( libfwevt_xml_tag_get_utf16_xml_string_with_index(
	     internal_xml_document->root_xml_tag,
	     0,
	     utf16_string,
	     utf16_string_size,
	     &utf16_string_index,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string of root XML tag.",
		 function );

		return( -1 );
	}
	return( 1 );
}

#if defined( HAVE_DEBUG_OUTPUT )

/* Debug prints the XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_document_debug_print(
     libfwevt_xml_document_t *xml_document,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_document_t *internal_xml_document = NULL;
	static char *function                                   = "libfwevt_xml_document_print";

	if( xml_document == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML document.",
		 function );

		return( -1 );
	}
	internal_xml_document = (libfwevt_internal_xml_document_t *) xml_document;

	if( libfwevt_xml_tag_debug_print(
	     internal_xml_document->root_xml_tag,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print root XML tag.",
		 function );

		return( -1 );
	}
	return( 1 );
}

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

