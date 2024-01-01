/*
 * Channel functions
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
#include "libfwevt_channel.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_libcnotify.h"
#include "libfwevt_libuna.h"
#include "libfwevt_types.h"

#include "fwevt_template.h"

/* Creates a channel
 * Make sure the value channel is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwevt_channel_initialize(
     libfwevt_channel_t **channel,
     libcerror_error_t **error )
{
	libfwevt_internal_channel_t *internal_channel = NULL;
	static char *function                         = "libfwevt_channel_initialize";

	if( channel == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid channel.",
		 function );

		return( -1 );
	}
	if( *channel != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid channel value already set.",
		 function );

		return( -1 );
	}
	internal_channel = memory_allocate_structure(
	                    libfwevt_internal_channel_t );

	if( internal_channel == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create channel.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_channel,
	     0,
	     sizeof( libfwevt_internal_channel_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear channel.",
		 function );

		goto on_error;
	}
	*channel = (libfwevt_channel_t *) internal_channel;

	return( 1 );

on_error:
	if( internal_channel != NULL )
	{
		memory_free(
		 internal_channel );
	}
	return( -1 );
}

/* Frees a channel
 * Returns 1 if successful or -1 on error
 */
int libfwevt_channel_free(
     libfwevt_channel_t **channel,
     libcerror_error_t **error )
{
	static char *function = "libfwevt_channel_free";

	if( channel == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid WEVT channel descriptor.",
		 function );

		return( -1 );
	}
	if( *channel != NULL )
	{
		*channel = NULL;
	}
	return( 1 );
}

/* Frees a channel
 * Returns 1 if successful or -1 on error
 */
int libfwevt_internal_channel_free(
     libfwevt_internal_channel_t **internal_channel,
     libcerror_error_t **error )
{
	static char *function = "libfwevt_internal_channel_free";

	if( internal_channel == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid WEVT channel descriptor.",
		 function );

		return( -1 );
	}
	if( *internal_channel != NULL )
	{
		if( ( *internal_channel )->name != NULL )
		{
			memory_free(
			 ( *internal_channel )->name );
		}
		memory_free(
		 *internal_channel );

		*internal_channel = NULL;
	}
	return( 1 );
}

/* Reads the channel
 * Returns 1 if successful or -1 on error
 */
int libfwevt_channel_read_data(
     libfwevt_channel_t *channel,
     const uint8_t *data,
     size_t data_size,
     size_t data_offset,
     libcerror_error_t **error )
{
	libfwevt_internal_channel_t *internal_channel = NULL;
	fwevt_template_channel_t *wevt_channel        = NULL;
	static char *function                         = "libfwevt_channel_read_data";
	uint32_t name_offset                          = 0;
	uint32_t name_size                            = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit                          = 0;
#endif

	if( channel == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid channel.",
		 function );

		return( -1 );
	}
	internal_channel = (libfwevt_internal_channel_t *) channel;

	if( internal_channel->name != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid channel - name value already set.",
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
	if( ( data_size < sizeof( fwevt_template_channel_t ) )
	 || ( data_offset > ( data_size - sizeof( fwevt_template_channel_t ) ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		return( -1 );
	}
	wevt_channel = (fwevt_template_channel_t *) &( data[ data_offset ] );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: channel data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) wevt_channel,
		 sizeof( fwevt_template_channel_t ),
		 0 );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	byte_stream_copy_to_uint32_little_endian(
	 wevt_channel->identifier,
	 internal_channel->identifier );

	byte_stream_copy_to_uint32_little_endian(
	 wevt_channel->name_offset,
	 name_offset );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: identifier\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 internal_channel->identifier );

		libcnotify_printf(
		 "%s: name offset\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 name_offset );

		byte_stream_copy_to_uint32_little_endian(
		 wevt_channel->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 wevt_channel->message_identifier,
		 value_32bit );
		libcnotify_printf(
		 "%s: message identifier\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( name_offset > 0 )
	{
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
			 "%s: name size\t\t\t\t\t: %" PRIu32 "\n",
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
			internal_channel->name = (uint8_t *) memory_allocate(
			                                      sizeof( uint8_t ) * name_size );

			if( internal_channel->name == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create name.",
				 function );

				goto on_error;
			}
			internal_channel->name_size = (size_t) name_size;

			if( memory_copy(
			     internal_channel->name,
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
				     internal_channel->name,
				     internal_channel->name_size,
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
	if( internal_channel->name != NULL )
	{
		memory_free(
		 internal_channel->name );

		internal_channel->name = NULL;
	}
	internal_channel->name_size = 0;

	return( -1 );
}

/* Retrieves the identifier
 * Returns 1 if successful or -1 on error
 */
int libfwevt_channel_get_identifier(
     libfwevt_channel_t *channel,
     uint32_t *identifier,
     libcerror_error_t **error )
{
	libfwevt_internal_channel_t *internal_channel = NULL;
	static char *function                         = "libfwevt_channel_get_identifier";

	if( channel == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid channel.",
		 function );

		return( -1 );
	}
	internal_channel = (libfwevt_internal_channel_t *) channel;

	if( identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid identifier.",
		 function );

		return( -1 );
	}
	*identifier = internal_channel->identifier;

	return( 1 );
}

/* Retrieves the size of the UTF-8 formatted name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfwevt_channel_get_utf8_name_size(
     libfwevt_channel_t *channel,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_channel_t *internal_channel = NULL;
	static char *function                         = "libfwevt_channel_get_utf8_name_size";

	if( channel == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid channel.",
		 function );

		return( -1 );
	}
	internal_channel = (libfwevt_internal_channel_t *) channel;

	if( ( internal_channel->name == NULL )
	 || ( internal_channel->name_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf8_string_size_from_utf16_stream(
	     internal_channel->name,
	     internal_channel->name_size,
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
int libfwevt_channel_get_utf8_name(
     libfwevt_channel_t *channel,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_channel_t *internal_channel = NULL;
	static char *function                         = "libfwevt_channel_get_utf8_name";

	if( channel == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid channel.",
		 function );

		return( -1 );
	}
	internal_channel = (libfwevt_internal_channel_t *) channel;

	if( ( internal_channel->name == NULL )
	 || ( internal_channel->name_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf8_string_copy_from_utf16_stream(
	     utf8_string,
	     utf8_string_size,
	     internal_channel->name,
	     internal_channel->name_size,
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
int libfwevt_channel_get_utf16_name_size(
     libfwevt_channel_t *channel,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_channel_t *internal_channel = NULL;
	static char *function                         = "libfwevt_channel_get_utf16_name_size";

	if( channel == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid channel.",
		 function );

		return( -1 );
	}
	internal_channel = (libfwevt_internal_channel_t *) channel;

	if( ( internal_channel->name == NULL )
	 || ( internal_channel->name_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf16_string_size_from_utf16_stream(
	     internal_channel->name,
	     internal_channel->name_size,
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
int libfwevt_channel_get_utf16_name(
     libfwevt_channel_t *channel,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_channel_t *internal_channel = NULL;
	static char *function                         = "libfwevt_channel_get_utf16_name";

	if( channel == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid channel.",
		 function );

		return( -1 );
	}
	internal_channel = (libfwevt_internal_channel_t *) channel;

	if( ( internal_channel->name == NULL )
	 || ( internal_channel->name_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf16_string_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     internal_channel->name,
	     internal_channel->name_size,
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

