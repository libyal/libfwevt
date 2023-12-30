/*
 * Template item functions
 *
 * Copyright (C) 2011-2023, Joachim Metz <joachim.metz@gmail.com>
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "libfwevt_debug.h"
#include "libfwevt_template_item.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_libcnotify.h"
#include "libfwevt_libuna.h"
#include "libfwevt_types.h"

/* Creates a template item
 * Make sure the value template_item is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_item_initialize(
     libfwevt_template_item_t **template_item,
     libcerror_error_t **error )
{
	libfwevt_internal_template_item_t *internal_template_item = NULL;
	static char *function                                     = "libfwevt_template_item_initialize";

	if( template_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template item.",
		 function );

		return( -1 );
	}
	if( *template_item != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid template item value already set.",
		 function );

		return( -1 );
	}
	internal_template_item = memory_allocate_structure(
	                          libfwevt_internal_template_item_t );

	if( internal_template_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create template item.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_template_item,
	     0,
	     sizeof( libfwevt_internal_template_item_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear template item.",
		 function );

		goto on_error;
	}
	*template_item = (libfwevt_template_item_t *) internal_template_item;

	return( 1 );

on_error:
	if( internal_template_item != NULL )
	{
		memory_free(
		 internal_template_item );
	}
	return( -1 );
}

/* Frees a template item
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_item_free(
     libfwevt_template_item_t **template_item,
     libcerror_error_t **error )
{
	static char *function = "libfwevt_template_item_free";

	if( template_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template item.",
		 function );

		return( -1 );
	}
	if( *template_item != NULL )
	{
		*template_item = NULL;
	}
	return( 1 );
}

/* Frees a template item
 * Returns 1 if successful or -1 on error
 */
int libfwevt_internal_template_item_free(
     libfwevt_internal_template_item_t **internal_template_item,
     libcerror_error_t **error )
{
	static char *function = "libfwevt_internal_template_item_free";

	if( internal_template_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template item.",
		 function );

		return( -1 );
	}
	if( *internal_template_item != NULL )
	{
		memory_free(
		 *internal_template_item );

		*internal_template_item = NULL;
	}
	return( 1 );
}

/* Reads the template item
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_item_read_data(
     libfwevt_template_item_t *template_item,
     const uint8_t *data,
     size_t data_size,
     size_t data_offset,
     libcerror_error_t **error )
{
	libfwevt_internal_template_item_t *internal_template_item = NULL;
	static char *function                                     = "libfwevt_template_item_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit                                      = 0;
	uint16_t value_16bit                                      = 0;
#endif

	if( template_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template item.",
		 function );

		return( -1 );
	}
	internal_template_item = (libfwevt_internal_template_item_t *) template_item;

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
	if( ( data_size < 20 )
	 || ( data_offset > ( data_size - 20 ) ) )
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
		 "%s: template item data:\n",
		 function );
		libcnotify_print_data(
		 &( data[ data_offset ] ),
		 20,
		 0 );
	}
#endif
/* TODO change xml template value to handle this type */
	internal_template_item->input_data_type = data[ data_offset + 4 ];

	internal_template_item->output_data_type = data[ data_offset + 5 ];

	byte_stream_copy_to_uint32_little_endian(
	 &( data[ data_offset + 16 ] ),
	 internal_template_item->name_offset );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 &( data[ data_offset ] ),
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: input data type\t\t\t: 0x%02" PRIx8 " (",
		 function,
		 internal_template_item->input_data_type );
		libfwevt_debug_print_value_type(
		 internal_template_item->input_data_type );
		libcnotify_printf(
		 ")\n" );

		libcnotify_printf(
		 "%s: output data type\t\t\t: 0x%02" PRIx8 " (",
		 function,
		 internal_template_item->output_data_type );
		libfwevt_debug_print_value_type(
		 internal_template_item->output_data_type );
		libcnotify_printf(
		 ")\n" );

		byte_stream_copy_to_uint16_little_endian(
		 &( data[ data_offset + 6 ] ),
		 value_16bit );
		libcnotify_printf(
		 "%s: unknown3\t\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( data[ data_offset + 8 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown4\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( data[ data_offset + 12 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown5\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: name offset\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 internal_template_item->name_offset );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

/* Reads the template item
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_item_read_name(
     libfwevt_template_item_t *template_item,
     const uint8_t *data,
     size_t data_size,
     size_t data_offset,
     libcerror_error_t **error )
{
	libfwevt_internal_template_item_t *internal_template_item = NULL;
	static char *function                                     = "libfwevt_template_item_read_name";
	uint16_t name_size                                        = 0;

	if( template_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template item.",
		 function );

		return( -1 );
	}
	internal_template_item = (libfwevt_internal_template_item_t *) template_item;

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
	if( ( data_size < 4 )
	 || ( data_offset > ( data_size - 4 ) ) )
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
		 "%s: template item name data:\n",
		 function );
		libcnotify_print_data(
		 &( data[ data_offset ] ),
		 20,
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 &( data[ data_offset ] ),
	 name_size );

	if( name_size > ( data_size - data_offset ) )
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
		 "%s: name data:\n",
		 function );
		libcnotify_print_data(
		 &( data[ data_offset ] ),
		 name_size,
		 0 );
	}
#endif
	if( name_size > 0 )
	{
		if( name_size < 4 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid name size value out of bounds.",
			 function );

			goto on_error;
		}
		name_size -= 4;
	}
	data_offset += 4;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: name size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 name_size );

		libcnotify_printf(
		 "%s: name data:\n",
		 function );
		libcnotify_print_data(
		 &( data[ data_offset ] ),
		 name_size,
		 0 );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	internal_template_item->name_size = name_size;

	return( 1 );

on_error:
	return( -1 );
}

