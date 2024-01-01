/*
 * Template item functions
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
		if( ( *internal_template_item )->name != NULL )
		{
			memory_free(
			 ( *internal_template_item )->name );
		}
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
     size_t template_data_offset,
     libcerror_error_t **error )
{
	libfwevt_internal_template_item_t *internal_template_item = NULL;
	static char *function                                     = "libfwevt_template_item_read_data";
	uint32_t name_offset                                      = 0;
	uint32_t name_size                                        = 0;

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

	if( internal_template_item->name != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid template item - name value already set.",
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

	byte_stream_copy_to_uint16_little_endian(
	 &( data[ data_offset + 12 ] ),
	 internal_template_item->number_of_values );

	byte_stream_copy_to_uint16_little_endian(
	 &( data[ data_offset + 14 ] ),
	 internal_template_item->value_data_size );

	byte_stream_copy_to_uint32_little_endian(
	 &( data[ data_offset + 16 ] ),
	 name_offset );

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
		libfwevt_debug_print_input_data_type(
		 internal_template_item->input_data_type );
		libcnotify_printf(
		 ")\n" );

		libcnotify_printf(
		 "%s: output data type\t\t\t: 0x%02" PRIx8 " (",
		 function,
		 internal_template_item->output_data_type );
		libfwevt_debug_print_output_data_type(
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

		libcnotify_printf(
		 "%s: number of values\t\t\t: %" PRIu16 "\n",
		 function,
		 internal_template_item->number_of_values );

		libcnotify_printf(
		 "%s: value data size\t\t\t: %" PRIu16 "\n",
		 function,
		 internal_template_item->value_data_size );

		libcnotify_printf(
		 "%s: name offset\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 name_offset );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	internal_template_item->name_offset = name_offset;

	if( name_offset > 0 )
	{
		if( name_offset < template_data_offset )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid name offset value out of bounds.",
			 function );

			goto on_error;
		}
		name_offset -= template_data_offset;

		if( name_offset >= ( data_size - 4 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid name offset value out of bounds.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint32_little_endian(
		 &( data[ name_offset ] ),
		 name_size );

		if( ( data_size < name_size )
		 || ( name_offset > ( data_size - name_size ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid name size value out of bounds.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ name_offset ] ),
			 name_size,
			 0 );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: name size\t\t\t\t: %" PRIu32 "\n",
			 function,
			 name_size );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		if( name_size >= 4 )
		{
			name_offset += 4;
			name_size   -= 4;

			if( ( name_size == 0 )
			 || ( name_size > ( MEMORY_MAXIMUM_ALLOCATION_SIZE / sizeof( uint8_t ) ) ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid name size value out of bounds.",
				 function );

				goto on_error;
			}
			internal_template_item->name = (uint8_t *) memory_allocate(
			                                            sizeof( uint8_t ) * name_size );

			if( internal_template_item->name == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create name.",
				 function );

				goto on_error;
			}
			internal_template_item->name_size = (size_t) name_size;

			if( memory_copy(
			     internal_template_item->name,
			     &( data[ name_offset ] ),
			     (size_t) name_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy name.",
				 function );

				goto on_error;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				if( libfwevt_debug_print_utf16_string_value(
				     function,
				     "name\t\t\t\t\t",
				     internal_template_item->name,
				     internal_template_item->name_size,
				     LIBUNA_ENDIAN_LITTLE,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
					 "%s: unable to print UTF-16 string value.",
					 function );

					goto on_error;
				}
			}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
		}
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );

on_error:
	if( internal_template_item->name != NULL )
	{
		memory_free(
		 internal_template_item->name );

		internal_template_item->name = NULL;
	}
	internal_template_item->name_size = 0;

	return( -1 );
}

/* Retrieves the input data type
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_item_get_input_data_type(
     libfwevt_template_item_t *template_item,
     uint8_t *input_data_type,
     libcerror_error_t **error )
{
	libfwevt_internal_template_item_t *internal_template_item = NULL;
	static char *function                                     = "libfwevt_template_item_get_input_data_type";

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

	if( input_data_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid input data type.",
		 function );

		return( -1 );
	}
	*input_data_type = internal_template_item->input_data_type;

	return( 1 );
}

/* Retrieves the output data type
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_item_get_output_data_type(
     libfwevt_template_item_t *template_item,
     uint8_t *output_data_type,
     libcerror_error_t **error )
{
	libfwevt_internal_template_item_t *internal_template_item = NULL;
	static char *function                                     = "libfwevt_template_item_get_output_data_type";

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

	if( output_data_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid output data type.",
		 function );

		return( -1 );
	}
	*output_data_type = internal_template_item->output_data_type;

	return( 1 );
}

/* Retrieves the number of values
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_item_get_number_of_values(
     libfwevt_template_item_t *template_item,
     uint16_t *number_of_values,
     libcerror_error_t **error )
{
	libfwevt_internal_template_item_t *internal_template_item = NULL;
	static char *function                                     = "libfwevt_template_item_get_number_of_values";

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

	if( number_of_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of values.",
		 function );

		return( -1 );
	}
	*number_of_values = internal_template_item->number_of_values;

	return( 1 );
}

/* Retrieves the value data size
 * Returns 1 if successful or -1 on error
 */
int libfwevt_template_item_get_value_data_size(
     libfwevt_template_item_t *template_item,
     uint16_t *value_data_size,
     libcerror_error_t **error )
{
	libfwevt_internal_template_item_t *internal_template_item = NULL;
	static char *function                                     = "libfwevt_template_item_get_value_data_size";

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

	if( value_data_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value data size.",
		 function );

		return( -1 );
	}
	*value_data_size = internal_template_item->value_data_size;

	return( 1 );
}

/* Retrieves the size of the UTF-8 formatted name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfwevt_template_item_get_utf8_name_size(
     libfwevt_template_item_t *template_item,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_template_item_t *internal_template_item = NULL;
	static char *function                                     = "libfwevt_template_item_get_utf8_name_size";

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

	if( ( internal_template_item->name == NULL )
	 || ( internal_template_item->name_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf8_string_size_from_utf16_stream(
	     internal_template_item->name,
	     internal_template_item->name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 formatted name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfwevt_template_item_get_utf8_name(
     libfwevt_template_item_t *template_item,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_template_item_t *internal_template_item = NULL;
	static char *function                                     = "libfwevt_template_item_get_utf8_name";

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

	if( ( internal_template_item->name == NULL )
	 || ( internal_template_item->name_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf8_string_copy_from_utf16_stream(
	     utf8_string,
	     utf8_string_size,
	     internal_template_item->name,
	     internal_template_item->name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 formatted name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfwevt_template_item_get_utf16_name_size(
     libfwevt_template_item_t *template_item,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_template_item_t *internal_template_item = NULL;
	static char *function                                     = "libfwevt_template_item_get_utf16_name_size";

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

	if( ( internal_template_item->name == NULL )
	 || ( internal_template_item->name_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf16_string_size_from_utf16_stream(
	     internal_template_item->name,
	     internal_template_item->name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 formatted name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfwevt_template_item_get_utf16_name(
     libfwevt_template_item_t *template_item,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_template_item_t *internal_template_item = NULL;
	static char *function                                     = "libfwevt_template_item_get_utf16_name";

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

	if( ( internal_template_item->name == NULL )
	 || ( internal_template_item->name_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf16_string_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     internal_template_item->name,
	     internal_template_item->name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

