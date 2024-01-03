/*
 * Template functions
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
#include "libfwevt_template.h"
#include "libfwevt_template_item.h"
#include "libfwevt_xml_document.h"
#include "libfwevt_xml_template_value.h"

#include "fwevt_template.h"

/* Creates a template
 * Make sure the value template is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_initialize(
     libfwevt_template_t **wevt_template,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_initialize";

	if( wevt_template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	if( *wevt_template != NULL )
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
	     &( internal_template->items_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create items array.",
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

	*wevt_template = (libfwevt_template_t *) internal_template;

	return( 1 );

on_error:
	if( internal_template != NULL )
	{
		if( internal_template->items_array != NULL )
		{
			libcdata_array_free(
			 &( internal_template->items_array ),
			 (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_template_item_free,
			 NULL );
		}
		memory_free(
		 internal_template );
	}
	return( -1 );
}

/* Frees a template
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_free(
     libfwevt_template_t **wevt_template,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_free";
	int result                                      = 1;

	if( wevt_template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	if( *wevt_template != NULL )
	{
		internal_template = (libfwevt_internal_template_t *) *wevt_template;

		if( internal_template->is_managed == 0 )
		{
			if( libfwevt_internal_template_free(
			     (libfwevt_internal_template_t **) wevt_template,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to free template.",
				 function );

				result = -1;
			}
		}
		*wevt_template = NULL;
	}
	return( result );
}

/* Frees a template
 * Returns 1 if successful or -1 on error
 */
int libfwevt_internal_template_free(
     libfwevt_internal_template_t **internal_template,
     libcerror_error_t **error )
{
	static char *function = "libfwevt_internal_template_free";
	int result            = 1;

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
	if( *internal_template != NULL )
	{
		if( ( *internal_template )->data != NULL )
		{
			memory_free(
			 ( *internal_template )->data );
		}
		if( libcdata_array_free(
		     &( ( *internal_template )->items_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_template_item_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to free items array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( ( *internal_template )->values_array ),
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
		 *internal_template );

		*internal_template = NULL;
	}
	return( result );
}

/* Reads the template
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_read(
     libfwevt_template_t *wevt_template,
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

	if( wevt_template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	internal_template = (libfwevt_internal_template_t *) wevt_template;

	if( internal_template->data != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid template - data value already set.",
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
	if( data_size > (size_t) SSIZE_MAX )
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
	if( ( internal_template->size == 0 )
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
	internal_template->offset = (uint32_t) data_offset;

	if( libfwevt_template_read_template_items(
	     internal_template,
	     &( data[ data_offset ] ),
	     (size_t) internal_template->size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read template template items.",
		 function );

		goto on_error;
	}
	if( (size_t) internal_template->size > MEMORY_MAXIMUM_ALLOCATION_SIZE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid template size value out of bounds.",
		 function );

		goto on_error;
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
		     wevt_template,
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
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

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
	static char *function = "libfwevt_template_read_header";

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
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
	if( ( data_size < sizeof( fwevt_template_header_t ) )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
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
	 ( (fwevt_template_header_t *) data )->template_items_offset,
	 internal_template->template_items_offset );

	if( memory_copy(
	     internal_template->identifier,
	     ( (fwevt_template_header_t *) data )->identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier.",
		 function );

		return( -1 );
	}
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
		 "%s: template items offset\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 internal_template->template_items_offset );

		byte_stream_copy_to_uint32_little_endian(
		 ( (fwevt_template_header_t *) data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		if( libfwevt_debug_print_guid_value(
		     function,
		     "identifier\t\t\t\t",
		     ( (fwevt_template_header_t *) data )->identifier,
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
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

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

		return( -1 );
	}
	return( 1 );
}

/* Reads the template items
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_read_template_items(
     libfwevt_internal_template_t *internal_template,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libfwevt_template_item_t *template_item       = NULL;
	libfwevt_xml_template_value_t *template_value = NULL;
	static char *function                         = "libfwevt_template_read_template_items";
	uint32_t template_items_data_offset           = 0;
	uint32_t first_template_item_name_offset      = 0;
	uint32_t template_item_name_offset            = 0;
	uint16_t template_value_data_size             = 0;
	uint8_t input_data_type                       = 0;
	int entry_index                               = 0;
	int template_value_index                      = 0;

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
	if( ( data_size < 20 )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( (size_t) internal_template->size > data_size )
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
		if( ( internal_template->template_items_offset != 0 )
		 && ( internal_template->template_items_offset != ( internal_template->offset + internal_template->size ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid template - template items offset value out of bounds.",
			 function );

			goto on_error;
		}
		return( 1 );
	}
	if( internal_template->template_items_offset < internal_template->offset )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid template - template items offset value out of bounds.",
		 function );

		goto on_error;
	}
	template_items_data_offset = internal_template->template_items_offset - internal_template->offset;

	if( ( template_items_data_offset < sizeof( fwevt_template_header_t ) )
	 || ( template_items_data_offset >= (size_t) internal_template->size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid template items data offset value out of bounds.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading template template items data at offset: %" PRIzd " (0x%08" PRIzx "):\n",
		 function,
		 internal_template->template_items_offset,
		 internal_template->template_items_offset );

		libcnotify_printf(
		 "%s: template template items data:\n",
		 function );
		libcnotify_print_data(
		 &( data[ template_items_data_offset ] ),
		 internal_template->size - template_items_data_offset,
		 0 );
	}
#endif
	do
	{
		if( libfwevt_template_item_initialize(
		     &template_item,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create template item.",
			 function );

			goto on_error;
		}
		if( libfwevt_template_item_read_data(
		     template_item,
		     data,
		     data_size,
		     (size_t) template_items_data_offset,
		     internal_template->offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read template item: %d.",
			 function,
			 template_value_index );

			goto on_error;
		}
		template_items_data_offset += 20;

		template_item_name_offset = ( (libfwevt_internal_template_item_t *) template_item )->name_offset;

		if( first_template_item_name_offset == 0 )
		{
			first_template_item_name_offset = template_item_name_offset;
		}
		input_data_type = ( (libfwevt_internal_template_item_t *) template_item )->input_data_type;

		if( libcdata_array_append_entry(
		     internal_template->items_array,
		     &entry_index,
		     (intptr_t *) template_item,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to append template item: %d to array.",
			 function,
			 template_value_index );

			goto on_error;
		}
		template_item = NULL;

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
		     input_data_type,
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
		     template_item_name_offset,
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
	while( ( internal_template->offset + template_items_data_offset ) < first_template_item_name_offset );

	return( 1 );

on_error:
	if( template_value != NULL )
	{
		libfwevt_xml_template_value_free(
		 &template_value,
		 NULL );
	}
	if( template_item != NULL )
	{
		libfwevt_internal_template_item_free(
		 (libfwevt_internal_template_item_t **) &template_item,
		 NULL );
	}
	libcdata_array_empty(
	 internal_template->values_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_xml_template_value_free,
	 NULL );

	libcdata_array_empty(
	 internal_template->items_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_template_item_free,
	 NULL );

	return( -1 );
}

/* Reads the template XML document
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_read_xml_document(
     libfwevt_template_t *wevt_template,
     libfwevt_xml_document_t *xml_document,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_read_xml_document";
	size_t binary_xml_data_size                     = 0;

	if( wevt_template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	internal_template = (libfwevt_internal_template_t *) wevt_template;

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
	if( internal_template->template_items_offset == 0 )
	{
		binary_xml_data_size = (size_t) internal_template->size;
	}
	else
	{
		if( internal_template->template_items_offset < internal_template->offset )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid template - template items offset value out of bounds.",
			 function );

			return( -1 );
		}
		binary_xml_data_size = internal_template->template_items_offset - internal_template->offset;
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
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( libfwevt_xml_document_read_with_template_values(
	     xml_document,
	     internal_template->data,
	     internal_template->data_size,
	     sizeof( fwevt_template_header_t ),
	     internal_template->ascii_codepage,
	     LIBFWEVT_XML_DOCUMENT_READ_FLAG_HAS_DEPENDENCY_IDENTIFIERS,
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
     libfwevt_template_t *wevt_template,
     int ascii_codepage,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_set_ascii_codepage";

	if( wevt_template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	internal_template = (libfwevt_internal_template_t *) wevt_template;

/* TODO check supported codepages ? */

	internal_template->ascii_codepage = ascii_codepage;

	return( 1 );
}

/* Retrieves the data
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_get_data(
     libfwevt_template_t *wevt_template,
     const uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_get_data";

	if( wevt_template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	internal_template = (libfwevt_internal_template_t *) wevt_template;

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
     libfwevt_template_t *wevt_template,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_set_data";

	if( wevt_template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	internal_template = (libfwevt_internal_template_t *) wevt_template;

	if( internal_template->data != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid template - data value already set.",
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
	if( ( data_size == 0 )
	 || ( data_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
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
	if( ( internal_template->size == 0 )
	 || ( (size_t) internal_template->size > data_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid template size value out of bounds.",
		 function );

		goto on_error;
	}
	internal_template->offset = 0;

	if( libfwevt_template_read_template_items(
	     internal_template,
	     data,
	     data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read template template items.",
		 function );

		goto on_error;
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
     libfwevt_template_t *wevt_template,
     uint32_t *offset,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_get_offset";

	if( wevt_template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	internal_template = (libfwevt_internal_template_t *) wevt_template;

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
     libfwevt_template_t *wevt_template,
     uint32_t offset,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_set_offset";

	if( wevt_template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	internal_template = (libfwevt_internal_template_t *) wevt_template;

	internal_template->offset = offset;

	return( 1 );
}

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_get_size(
     libfwevt_template_t *wevt_template,
     uint32_t *size,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_get_size";

	if( wevt_template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	internal_template = (libfwevt_internal_template_t *) wevt_template;

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

/* Retrieves the identifier
 * The identifier is a GUID stored in little-endian and is 16 bytes of size
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int libfwevt_template_get_identifier(
     libfwevt_template_t *wevt_template,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_get_identifier";

	if( wevt_template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	internal_template = (libfwevt_internal_template_t *) wevt_template;

	if( guid_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID data.",
		 function );

		return( -1 );
	}
	if( ( guid_data_size < 16 )
	 || ( guid_data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: GUID data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     guid_data,
	     internal_template->identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the number of items
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_get_number_of_items(
     libfwevt_template_t *wevt_template,
     int *number_of_items,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_get_number_of_items";

	if( wevt_template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	internal_template = (libfwevt_internal_template_t *) wevt_template;

	if( libcdata_array_get_number_of_entries(
	     internal_template->items_array,
	     number_of_items,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific item
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_get_item_by_index(
     libfwevt_template_t *wevt_template,
     int item_index,
     libfwevt_template_item_t **item,
     libcerror_error_t **error )
{
	libfwevt_internal_template_t *internal_template = NULL;
	static char *function                           = "libfwevt_template_get_item_by_index";

	if( wevt_template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	internal_template = (libfwevt_internal_template_t *) wevt_template;

	if( libcdata_array_get_entry_by_index(
	     internal_template->items_array,
	     item_index,
	     (intptr_t **) item,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d.",
		 function,
		 item_index );

		return( -1 );
	}
	return( 1 );
}

