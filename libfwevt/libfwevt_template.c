/*
 * Template functions
 *
 * Copyright (C) 2011-2018, Joachim Metz <joachim.metz@gmail.com>
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
#include "libfwevt_template.h"
#include "libfwevt_xml_document.h"
#include "libfwevt_xml_template_value.h"

#include "fwevt_template.h"

/* Creates a template
 * Make sure the value template is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_initialize(
     libfwevt_template_t **template,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_initialize";

	if( template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	if( *template != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid template value already set.",
		 function );

		return( -1 );
	}
	internal_template = memory_allocate_structure(
	                     libfwevt_internal_template_t );

	if( internal_template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create template.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_template,
	     0,
	     sizeof( libfwevt_internal_template_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear template.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_template->values_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create values array.",
		 function );

		goto on_error;
	}
	internal_template->ascii_codepage = 1252;

	*template = (libfwevt_template_t *) internal_template;

	return( 1 );

on_error:
	if( internal_template != NULL )
	{
		memory_free(
		 internal_template );
	}
	return( -1 );
}

/* Frees a template
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_free(
     libfwevt_template_t **template,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_free";
	int result                                      = 1;

	if( template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	if( *template != NULL )
	{
		internal_template = (libfwevt_internal_template_t *) *template;
		*template         = NULL;

		if( internal_template->data != NULL )
		{
			memory_free(
			 internal_template->data );
		}
		if( libcdata_array_free(
		     &( internal_template->values_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_xml_template_value_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to free values array.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_template );
	}
	return( result );
}

/* Reads the template
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_read(
     libfwevt_template_t *template,
     const uint8_t *data,
     size_t data_size,
     size_t data_offset,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_read";

#if defined( HAVE_DEBUG_OUTPUT )
	libfwevt_xml_document_t *xml_document           = NULL;
#endif

	if( template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	internal_template = (libfwevt_internal_template_t *) template;

	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) UINT32_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_offset >= data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( libfwevt_template_read_header(
	     internal_template,
	     &( data[ data_offset ] ),
	     data_size - data_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read template header.",
		 function );

		goto on_error;
	}
	if( ( (size_t) internal_template->size > data_size )
	 || ( (size_t) internal_template->size > ( data_size - data_offset ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid template size value out of bounds.",
		 function );

		goto on_error;
	}
	if( internal_template->data != NULL )
	{
		memory_free(
		 internal_template->data );

		internal_template->data      = NULL;
		internal_template->data_size = 0;
	}
	internal_template->data = (uint8_t *) memory_allocate(
	                                       sizeof( uint8_t ) * internal_template->size );

	if( internal_template->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     internal_template->data,
	     &( data[ data_offset ] ),
	     (size_t) internal_template->size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy data.",
		 function );

		goto on_error;
	}
	internal_template->data_size = (size_t) internal_template->size;
	internal_template->offset    = (uint32_t) data_offset;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libfwevt_xml_document_initialize(
		     &xml_document,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create XML document.",
			 function );

			goto on_error;
		}
		if( libfwevt_template_read_xml_document(
		     template,
		     xml_document,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read binary XML document.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: XML document:\n",
		 function );

		if( libfwevt_xml_document_debug_print(
		     xml_document,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print XML document.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "\n" );

		if( libfwevt_xml_document_free(
		     &xml_document,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to free XML document.",
			 function );

			goto on_error;
		}
	}
#endif
	return( 1 );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( xml_document != NULL )
	{
		libfwevt_xml_document_free(
		 &xml_document,
		 NULL );
	}
#endif
	if( internal_template->data != NULL )
	{
		memory_free(
		 internal_template->data );

		internal_template->data = NULL;
	}
	return( -1 );
}

/* Reads the template header
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_read_header(
     libfwevt_internal_template_t *internal_template,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function       = "libfwevt_template_read_header";

#if defined( HAVE_DEBUG_OUTPUT )
	system_character_t guid_string[ 48 ];

	libfguid_identifier_t *guid = NULL;
	uint32_t value_32bit        = 0;
	int result                  = 0;
#endif

	if( internal_template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) UINT32_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_size < sizeof( fwevt_template_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: template header data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( fwevt_template_header_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 ( (fwevt_template_header_t *) data )->size,
	 internal_template->size );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fwevt_template_header_t *) data )->number_of_descriptors,
	 internal_template->number_of_descriptors );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fwevt_template_header_t *) data )->number_of_names,
	 internal_template->number_of_names );

	byte_stream_copy_to_uint32_little_endian(
	 ( (fwevt_template_header_t *) data )->instance_values_offset,
	 internal_template->instance_values_offset );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c\n",
		 function,
		 ( (fwevt_template_header_t *) data )->signature[ 0 ],
		 ( (fwevt_template_header_t *) data )->signature[ 1 ],
		 ( (fwevt_template_header_t *) data )->signature[ 2 ],
		 ( (fwevt_template_header_t *) data )->signature[ 3 ] );

		libcnotify_printf(
		 "%s: size\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 internal_template->size );

		libcnotify_printf(
		 "%s: number of descriptors\t\t\t: %" PRIu32 "\n",
		 function,
		 internal_template->number_of_descriptors );

		libcnotify_printf(
		 "%s: number of names\t\t\t\t: %" PRIu32 "\n",
		 function,
		 internal_template->number_of_names );

		libcnotify_printf(
		 "%s: instance values offset\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 internal_template->instance_values_offset );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fwevt_template_header_t *) data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		if( libfguid_identifier_initialize(
		     &guid,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create GUID.",
			 function );

			goto on_error;
		}
		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     ( (fwevt_template_header_t *) data )->identifier,
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to GUID.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfguid_identifier_copy_to_utf16_string(
			  guid,
			  (uint16_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#else
		result = libfguid_identifier_copy_to_utf8_string(
			  guid,
			  (uint8_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy GUID to string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: identifier\t\t\t\t: %" PRIs_SYSTEM "\n",
		 function,
		 guid_string );

		if( libfguid_identifier_free(
		     &guid,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free GUID.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "\n" );
	}
#endif
	if( memory_compare(
	     ( (fwevt_template_header_t *) data )->signature,
	     "TEMP",
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported template signature.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
#endif
	return( -1 );
}

/* Reads the template instance values
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_read_instance_values(
     libfwevt_internal_template_t *internal_template,
     libcerror_error_t **error )
{
	libfwevt_xml_template_value_t *template_value = NULL;
	static char *function                         = "libfwevt_template_read_instance_values";
	uint32_t instance_values_data_offset          = 0;
	uint32_t first_template_value_data_offset     = 0;
	uint32_t template_value_data_offset           = 0;
	uint16_t template_value_data_size             = 0;
	uint8_t template_value_type                   = 0;
	int entry_index                               = 0;
	int template_value_index                      = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit                          = 0;
	uint16_t value_16bit                          = 0;
#endif

	if( internal_template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	if( internal_template->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid template - missing data.",
		 function );

		return( -1 );
	}
	if( (size_t) internal_template->size > internal_template->data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid template - size value out of bounds.",
		 function );

		goto on_error;
	}
	if( internal_template->number_of_descriptors == 0 )
	{
		/* The data offset should either be 0 or point to the end of the data
		 */
		if( ( internal_template->instance_values_offset != 0 )
		 && ( internal_template->instance_values_offset != ( internal_template->offset + internal_template->size ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid template - instance values offset value out of bounds.",
			 function );

			goto on_error;
		}
		return( 1 );
	}
	if( internal_template->instance_values_offset < internal_template->offset )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid template - instance values offset value out of bounds.",
		 function );

		goto on_error;
	}
	instance_values_data_offset = internal_template->instance_values_offset - internal_template->offset;

	if( ( instance_values_data_offset < sizeof( fwevt_template_header_t ) )
	 || ( instance_values_data_offset >= (size_t) internal_template->size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid instance values data offset value out of bounds.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading template instance values data at offset: %" PRIzd " (0x%08" PRIzx "):\n",
		 function,
		 internal_template->instance_values_offset,
		 internal_template->instance_values_offset );

		libcnotify_printf(
		 "%s: template instance values data:\n",
		 function );
		libcnotify_print_data(
		 &( internal_template->data[ instance_values_data_offset ] ),
		 internal_template->size - instance_values_data_offset,
		 0 );
	}
#endif
	do
	{
		if( ( instance_values_data_offset + 20 ) > internal_template->data_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid template - data too small.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value: %02d header data:\n",
			 function,
			 template_value_index );
			libcnotify_print_data(
			 &( internal_template->data[ instance_values_data_offset ] ),
			 20,
			 0 );
		}
#endif
/* TODO change xml template value to handle this type */
		template_value_type = internal_template->data[ instance_values_data_offset + 4 ];

		byte_stream_copy_to_uint32_little_endian(
		 &( internal_template->data[ instance_values_data_offset + 16 ] ),
		 template_value_data_offset );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 &( internal_template->data[ instance_values_data_offset ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: value: %02d unknown1\t\t: 0x%08" PRIx32 "\n",
			 function,
			 template_value_index,
			 value_32bit );

			libcnotify_printf(
			 "%s: value: %02d type\t\t\t: 0x%02" PRIx8 " (",
			 function,
			 template_value_index,
			 template_value_type );
			libfwevt_debug_print_value_type(
			 template_value_type );
			libcnotify_printf(
			 ")\n" );

			libcnotify_printf(
			 "%s: value: %02d unknown2\t\t: 0x%02" PRIx8 "\n",
			 function,
			 template_value_index,
			 internal_template->data[ instance_values_data_offset + 5 ] );

			byte_stream_copy_to_uint16_little_endian(
			 &( internal_template->data[ instance_values_data_offset + 6 ] ),
			 value_16bit );
			libcnotify_printf(
			 "%s: value: %02d unknown3\t\t: 0x%04" PRIx16 "\n",
			 function,
			 template_value_index,
			 value_16bit );

			byte_stream_copy_to_uint32_little_endian(
			 &( internal_template->data[ instance_values_data_offset + 8 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: value: %02d unknown4\t\t: 0x%08" PRIx32 "\n",
			 function,
			 template_value_index,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 &( internal_template->data[ instance_values_data_offset + 12 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: value: %02d unknown5\t\t: 0x%08" PRIx32 "\n",
			 function,
			 template_value_index,
			 value_32bit );

			libcnotify_printf(
			 "%s: value: %02d offset\t\t: 0x%08" PRIx32 "\n",
			 function,
			 template_value_index,
			 template_value_data_offset );
		}
#endif
		instance_values_data_offset += 20;

		if( template_value_data_offset < internal_template->offset )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid template value data offset value out of bounds.",
			 function );

			goto on_error;
		}
		template_value_data_offset -= internal_template->offset;

		if( template_value_data_offset >= internal_template->data_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid template value data offset value out of bounds.",
			 function );

			goto on_error;
		}
		if( ( template_value_data_offset + 4 ) > internal_template->data_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid template - data too small.",
			 function );

			goto on_error;
		}
		if( first_template_value_data_offset == 0 )
		{
			first_template_value_data_offset = template_value_data_offset;
		}
		byte_stream_copy_to_uint32_little_endian(
		 &( internal_template->data[ template_value_data_offset ] ),
		 template_value_data_size );

		if( ( template_value_data_offset + template_value_data_size ) > internal_template->data_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid template - data too small.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value: %02d value data:\n",
			 function,
			 template_value_index );
			libcnotify_print_data(
			 &( internal_template->data[ template_value_data_offset ] ),
			 template_value_data_size,
			 0 );
		}
#endif
		if( template_value_data_size > 0 )
		{
			if( template_value_data_size < 4 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid template value data size value out of bounds.",
				 function );

				goto on_error;
			}
			template_value_data_size -= 4;
		}
		template_value_data_offset += 4;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value: %02d size\t\t: %" PRIu32 "\n",
			 function,
			 template_value_index,
			 template_value_data_size );

			libcnotify_printf(
			 "%s: value: %02d data:\n",
			 function,
			 template_value_index );
			libcnotify_print_data(
			 &( internal_template->data[ template_value_data_offset ] ),
			 template_value_data_size,
			 0 );

			libcnotify_printf(
			 "\n" );
		}
#endif
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
		if( libfwevt_xml_template_value_set_flags(
		     template_value,
		     LIBFWEVT_XML_TEMPLATE_VALUE_FLAG_IS_DEFINITION,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set template value flags.",
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

			goto on_error;
		}
		if( libfwevt_xml_template_value_set_offset(
		     template_value,
		     template_value_data_offset,
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

			goto on_error;
		}
		if( libcdata_array_append_entry(
		     internal_template->values_array,
		     &entry_index,
		     (intptr_t *) template_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to append template value: %d to array.",
			 function,
			 template_value_index );

			goto on_error;
		}
		template_value = NULL;

		template_value_index++;
	}
	while( instance_values_data_offset < first_template_value_data_offset );

	return( 1 );

on_error:
	if( template_value != NULL )
	{
		libfwevt_xml_template_value_free(
		 &template_value,
		 NULL );
	}
	libcdata_array_empty(
	 internal_template->values_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_xml_template_value_free,
	 NULL );

	return( -1 );
}

/* Reads the template XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_read_xml_document(
     libfwevt_template_t *template,
     libfwevt_xml_document_t *xml_document,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_read_xml_document";
	size_t binary_xml_data_size                     = 0;

	if( template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	internal_template = (libfwevt_internal_template_t *) template;

	if( internal_template->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid template - missing data.",
		 function );

		return( -1 );
	}
	if( (size_t) internal_template->size > internal_template->data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid template - size value out of bounds.",
		 function );

		return( -1 );
	}
	if( internal_template->instance_values_offset == 0 )
	{
		binary_xml_data_size = (size_t) internal_template->size;
	}
	else
	{
		if( internal_template->instance_values_offset < internal_template->offset )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid template - instance values offset value out of bounds.",
			 function );

			return( -1 );
		}
		binary_xml_data_size = internal_template->instance_values_offset - internal_template->offset;
	}
	if( binary_xml_data_size < sizeof( fwevt_template_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary XML data size value out of bounds.",
		 function );

		goto on_error;
	}
	binary_xml_data_size -= sizeof( fwevt_template_header_t );

	if( ( binary_xml_data_size == 0 )
	 || ( binary_xml_data_size > internal_template->data_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary XML data size value out of bounds.",
		 function );

		goto on_error;
	}
	if( libfwevt_template_read_instance_values(
	     internal_template,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read template instance values.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading template binary XML document data at offset: %" PRIzd " (0x%08" PRIzx "):\n",
		 function,
		 internal_template->offset + sizeof( fwevt_template_header_t ),
		 internal_template->offset + sizeof( fwevt_template_header_t ) );

		libcnotify_printf(
		 "%s: template binary XML document data:\n",
		 function );
		libcnotify_print_data(
		 &( internal_template->data[ sizeof( fwevt_template_header_t ) ] ),
		 binary_xml_data_size,
		 0 );
	}
#endif
	if( libfwevt_xml_document_read_with_template_values(
	     xml_document,
	     internal_template->data,
	     internal_template->data_size,
	     sizeof( fwevt_template_header_t ),
	     internal_template->ascii_codepage,
	     0,
	     internal_template->values_array,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read binary XML document.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	libcdata_array_empty(
	 internal_template->values_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_xml_template_value_free,
	 NULL );

	return( -1 );
}

/* Sets the ASCII codepage
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_set_ascii_codepage(
     libfwevt_template_t *template,
     int ascii_codepage,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_set_ascii_codepage";

	if( template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	internal_template = (libfwevt_internal_template_t *) template;

/* TODO check supported codepages ? */

	internal_template->ascii_codepage = ascii_codepage;

	return( 1 );
}

/* Retrieves the data
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_get_data(
     libfwevt_template_t *template,
     const uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_get_data";

	if( template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	internal_template = (libfwevt_internal_template_t *) template;

	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data size.",
		 function );

		return( -1 );
	}
	*data      = internal_template->data;
	*data_size = internal_template->data_size;

	return( 1 );
}

/* Sets the data
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_set_data(
     libfwevt_template_t *template,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_set_data";

	if( template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	internal_template = (libfwevt_internal_template_t *) template;

	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) UINT32_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( libfwevt_template_read_header(
	     internal_template,
	     data,
	     data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read template header.",
		 function );

		goto on_error;
	}
	if( (size_t) internal_template->size > data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid template size value out of bounds.",
		 function );

		goto on_error;
	}
	if( internal_template->data != NULL )
	{
		memory_free(
		 internal_template->data );

		internal_template->data      = NULL;
		internal_template->data_size = 0;
	}
	internal_template->data = (uint8_t *) memory_allocate(
	                                       sizeof( uint8_t ) * data_size );

	if( internal_template->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     internal_template->data,
	     data,
	     data_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy data.",
		 function );

		goto on_error;
	}
	internal_template->data_size = data_size;

	return( 1 );

on_error:
	if( internal_template->data != NULL )
	{
		memory_free(
		 internal_template->data );

		internal_template->data = NULL;
	}
	internal_template->data_size = 0;

	return( -1 );
}

/* Retrieves the offset
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_get_offset(
     libfwevt_template_t *template,
     uint32_t *offset,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_get_offset";

	if( template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	internal_template = (libfwevt_internal_template_t *) template;

	if( offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
		 function );

		return( -1 );
	}
	*offset = internal_template->offset;

	return( 1 );
}

/* Sets the offset
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_set_offset(
     libfwevt_template_t *template,
     uint32_t offset,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_set_offset";

	if( template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	internal_template = (libfwevt_internal_template_t *) template;

	internal_template->offset = offset;

	return( 1 );
}

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_get_size(
     libfwevt_template_t *template,
     uint32_t *size,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_get_size";

	if( template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	internal_template = (libfwevt_internal_template_t *) template;

	if( size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
	*size = internal_template->size;

	return( 1 );
}

