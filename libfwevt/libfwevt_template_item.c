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
	static char *function = "libfwevt_template_item_read_data";

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
/* TODO implement */
	return( 1 );
}

