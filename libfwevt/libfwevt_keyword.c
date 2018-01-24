/*
 * Keyword functions
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "libfwevt_keyword.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_libcnotify.h"
#include "libfwevt_libuna.h"
#include "libfwevt_types.h"

#include "fwevt_template.h"

/* Creates a keyword
 * Make sure the value keyword is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwevt_keyword_initialize(
     libfwevt_keyword_t **keyword,
     libcerror_error_t **error )
{
	libfwevt_internal_keyword_t *internal_keyword = NULL;
	static char *function                         = "libfwevt_keyword_initialize";

	if( keyword == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid keyword.",
		 function );

		return( -1 );
	}
	if( *keyword != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid keyword value already set.",
		 function );

		return( -1 );
	}
	internal_keyword = memory_allocate_structure(
	                    libfwevt_internal_keyword_t );

	if( internal_keyword == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create keyword.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_keyword,
	     0,
	     sizeof( libfwevt_internal_keyword_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear keyword.",
		 function );

		goto on_error;
	}
	*keyword = (libfwevt_keyword_t *) internal_keyword;

	return( 1 );

on_error:
	if( internal_keyword != NULL )
	{
		memory_free(
		 internal_keyword );
	}
	return( -1 );
}

/* Frees a keyword
 * Returns 1 if successful or -1 on error
 */
int libfwevt_keyword_free(
     libfwevt_keyword_t **keyword,
     libcerror_error_t **error )
{
	libfwevt_internal_keyword_t *internal_keyword = NULL;
	static char *function                         = "libfwevt_keyword_free";

	if( keyword == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid keyword.",
		 function );

		return( -1 );
	}
	if( *keyword != NULL )
	{
		internal_keyword = (libfwevt_internal_keyword_t *) *keyword;
		*keyword         = NULL;

		memory_free(
		 internal_keyword );
	}
	return( 1 );
}

/* Reads the keyword
 * Returns 1 if successful or -1 on error
 */
int libfwevt_keyword_read(
     libfwevt_keyword_t *keyword,
     const uint8_t *resource_data,
     size_t resource_data_size,
     size_t resource_data_offset,
     libcerror_error_t **error )
{
/* TODO
	libfwevt_internal_keyword_t *internal_keyword = NULL;
*/
	fwevt_template_keyword_t *wevt_keyword = NULL;
	static char *function                  = "libfwevt_keyword_read";
	uint32_t keyword_data_offset           = 0;
	uint32_t keyword_data_size             = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	system_character_t *value_string       = NULL;
	size_t value_string_size               = 0;
	uint64_t value_64bit                   = 0;
	uint32_t value_32bit                   = 0;
	int result                             = 0;
#endif

	if( keyword == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid keyword.",
		 function );

		return( -1 );
	}
/* TODO
	internal_keyword = (libfwevt_internal_keyword_t *) keyword;
*/

	if( resource_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource data.",
		 function );

		return( -1 );
	}
	if( resource_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid resource data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( resource_data_offset >= resource_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid resource data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( resource_data_size < sizeof( fwevt_template_keyword_t ) )
	 || ( resource_data_offset > ( resource_data_size - sizeof( fwevt_template_keyword_t ) ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid resource data value too small.",
		 function );

		return( -1 );
	}
	wevt_keyword = (fwevt_template_keyword_t *) &( resource_data[ resource_data_offset ] );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: keyword data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) wevt_keyword,
		 sizeof( fwevt_template_keyword_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 wevt_keyword->data_offset,
	 keyword_data_offset );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint64_little_endian(
		 wevt_keyword->identifier,
		 value_64bit );
		libcnotify_printf(
		 "%s: identifier\t\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		byte_stream_copy_to_uint32_little_endian(
		 wevt_keyword->message_identifier,
		 value_32bit );
		libcnotify_printf(
		 "%s: message identifier\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: data offset\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 keyword_data_offset );
	}
#endif
	if( keyword_data_offset > 0 )
	{
		if( keyword_data_offset >= resource_data_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid keyword data offset value out of bounds.",
			 function );

			goto on_error;
		}
		if( ( keyword_data_size > resource_data_size )
		 || ( ( keyword_data_offset + keyword_data_size ) > resource_data_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid keyword data size value out of bounds.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint32_little_endian(
		 &( resource_data[ keyword_data_offset ] ),
		 keyword_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: data:\n",
			 function );
			libcnotify_print_data(
			 &( resource_data[ keyword_data_offset ] ),
			 keyword_data_size,
			 0 );
		}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: data size\t\t\t\t\t: %" PRIu32 "\n",
			 function,
			 keyword_data_size );
		}
		keyword_data_offset += 4;
		keyword_data_size   -= 4;
#endif

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_size_from_utf16_stream(
				  &( resource_data[ keyword_data_offset ] ),
				  keyword_data_size,
				  LIBUNA_ENDIAN_LITTLE,
				  &value_string_size,
				  error );
#else
			result = libuna_utf8_string_size_from_utf16_stream(
				  &( resource_data[ keyword_data_offset ] ),
				  keyword_data_size,
				  LIBUNA_ENDIAN_LITTLE,
				  &value_string_size,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to determine size of data string.",
				 function );

				goto on_error;
			}
			if( ( value_string_size > (size_t) SSIZE_MAX )
			 || ( ( sizeof( system_character_t ) * value_string_size )  > (size_t) SSIZE_MAX ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid data string size value exceeds maximum.",
				 function );

				goto on_error;
			}
			value_string = system_string_allocate(
					value_string_size );

			if( value_string == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create data string.",
				 function );

				goto on_error;
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_copy_from_utf16_stream(
				  (libuna_utf16_character_t *) value_string,
				  value_string_size,
				  &( resource_data[ keyword_data_offset ] ),
				  keyword_data_size,
				  LIBUNA_ENDIAN_LITTLE,
				  error );
#else
			result = libuna_utf8_string_copy_from_utf16_stream(
				  (libuna_utf8_character_t *) value_string,
				  value_string_size,
				  &( resource_data[ keyword_data_offset ] ),
				  keyword_data_size,
				  LIBUNA_ENDIAN_LITTLE,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set data string.",
				 function );

				goto on_error;
			}
			libcnotify_printf(
			 "%s: name\t\t\t\t\t\t: %" PRIs_SYSTEM "\n",
			 function,
			 value_string );

			memory_free(
			 value_string );

			value_string = NULL;
		}
#endif
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
#if defined( HAVE_DEBUG_OUTPUT )
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
#endif
	return( -1 );
}

