/*
 * Data segment functions
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
#include <memory.h>
#include <types.h>

#include "libfwevt_data_segment.h"
#include "libfwevt_definitions.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_libfdatetime.h"
#include "libfwevt_libfguid.h"
#include "libfwevt_libfwnt.h"

/* Creates a data segment
 * Make sure the value data_segment is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwevt_data_segment_initialize(
     libfwevt_data_segment_t **data_segment,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libfwevt_data_segment_initialize";

	if( data_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data segment.",
		 function );

		return( -1 );
	}
	if( *data_segment != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid data segment value already set.",
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
	if( data_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
	*data_segment = memory_allocate_structure(
	                 libfwevt_data_segment_t );

	if( *data_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data segment.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *data_segment,
	     0,
	     sizeof( libfwevt_data_segment_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear data segment.",
		 function );

		memory_free(
		 *data_segment );

		*data_segment = NULL;

		return( -1 );
	}
	if( data_size > 0 )
	{
		( *data_segment)->data = (uint8_t *) memory_allocate(
		                                      sizeof( uint8_t ) * data_size );

		if( ( *data_segment)->data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create data.",
			 function );

			goto on_error;
		}
		( *data_segment)->data_size = data_size;

		if( memory_copy(
		     ( *data_segment)->data,
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
	}
	return( 1 );

on_error:
	if( *data_segment != NULL )
	{
		if( ( *data_segment )->data != NULL )
		{
			memory_free(
			 ( *data_segment )->data );
		}
		memory_free(
		 *data_segment );

		*data_segment = NULL;
	}
	return( -1 );
}

/* Frees a data segment
 * Returns 1 if successful or -1 on error
 */
int libfwevt_data_segment_free(
     libfwevt_data_segment_t **data_segment,
     libcerror_error_t **error )
{
	static char *function = "libfwevt_data_segment_free";
	int result            = 1;

	if( data_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data segment.",
		 function );

		return( -1 );
	}
	if( *data_segment != NULL )
	{
		switch( ( *data_segment )->cached_value_type & 0x7f )
		{
			case LIBFWEVT_VALUE_TYPE_GUID:
				if( libfguid_identifier_free(
				     &( ( *data_segment )->guid ),
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free GUID.",
					 function );

					result = -1;
				}
				break;

			case LIBFWEVT_VALUE_TYPE_FILETIME:
				if( libfdatetime_filetime_free(
				     &( ( *data_segment )->filetime ),
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free FILETIME.",
					 function );

					result = -1;
				}
				break;

			case LIBFWEVT_VALUE_TYPE_SYSTEMTIME:
				if( libfdatetime_systemtime_free(
				     &( ( *data_segment )->systemtime ),
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free SYSTEMTIME.",
					 function );

					result = -1;
				}
				break;

			case LIBFWEVT_VALUE_TYPE_NT_SECURITY_IDENTIFIER:
				if( libfwnt_security_identifier_free(
				     &( ( *data_segment )->security_identifier ),
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free NT security identifier.",
					 function );

					result = -1;
				}
				break;
		}
		if( ( *data_segment )->data != NULL )
		{
			memory_free(
			 ( *data_segment )->data );
		}
		memory_free(
		 *data_segment );

		*data_segment = NULL;
	}
	return( result );
}

