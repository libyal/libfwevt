/*
 * Map functions
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
#include <types.h>

#include "libfwevt_libcerror.h"
#include "libfwevt_libcnotify.h"
#include "libfwevt_map.h"
#include "libfwevt_types.h"

#include "fwevt_template.h"

/* Creates a map
 * Make sure the value map is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwevt_map_initialize(
     libfwevt_map_t **map,
     libcerror_error_t **error )
{
	libfwevt_internal_map_t *internal_map = NULL;
	static char *function                 = "libfwevt_map_initialize";

	if( map == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid map.",
		 function );

		return( -1 );
	}
	if( *map != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid map value already set.",
		 function );

		return( -1 );
	}
	internal_map = memory_allocate_structure(
	                libfwevt_internal_map_t );

	if( internal_map == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create map.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_map,
	     0,
	     sizeof( libfwevt_internal_map_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear map.",
		 function );

		goto on_error;
	}
	*map = (libfwevt_map_t *) internal_map;

	return( 1 );

on_error:
	if( internal_map != NULL )
	{
		memory_free(
		 internal_map );
	}
	return( -1 );
}

/* Frees a map
 * Returns 1 if successful or -1 on error
 */
int libfwevt_map_free(
     libfwevt_map_t **map,
     libcerror_error_t **error )
{
	libfwevt_internal_map_t *internal_map = NULL;
	static char *function                 = "libfwevt_map_free";

	if( map == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid map.",
		 function );

		return( -1 );
	}
	if( *map != NULL )
	{
		internal_map = (libfwevt_internal_map_t *) *map;
		*map         = NULL;

		memory_free(
		 internal_map );
	}
	return( 1 );
}

/* Reads the map
 * Returns 1 if successful or -1 on error
 */
int libfwevt_map_read(
     libfwevt_map_t *map,
     const uint8_t *data,
     size_t data_size,
     size_t data_offset,
     libcerror_error_t **error )
{
/* TODO
	libfwevt_internal_map_t *internal_map = NULL;
*/
	fwevt_template_map_t *wevt_map        = NULL;
	static char *function                 = "libfwevt_map_read";

	if( map == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid map.",
		 function );

		return( -1 );
	}
/* TODO
	internal_map = (libfwevt_internal_map_t *) map;
*/

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
	if( ( data_size < sizeof( fwevt_template_map_t ) )
	 || ( data_offset > ( data_size - sizeof( fwevt_template_map_t ) ) ) )
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
/* TODO implement map support */
	wevt_map = (fwevt_template_map_t *) &( data[ data_offset ] );
#endif

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c\n",
		 function,
		 wevt_map->signature[ 0 ],
		 wevt_map->signature[ 1 ],
		 wevt_map->signature[ 2 ],
		 wevt_map->signature[ 3 ] );
	}
#endif
/* TODO implement map support */

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );
}

