/*
 * XML value functions
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

#include "libfwevt_data_segment.h"
#include "libfwevt_date_time.h"
#include "libfwevt_definitions.h"
#include "libfwevt_floating_point.h"
#include "libfwevt_integer.h"
#include "libfwevt_libcdata.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_libfdatetime.h"
#include "libfwevt_libfguid.h"
#include "libfwevt_libfwnt.h"
#include "libfwevt_libuna.h"
#include "libfwevt_types.h"
#include "libfwevt_xml_string.h"
#include "libfwevt_xml_value.h"

/* Creates a XML value
 * Make sure the value xml_value is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_initialize(
     libfwevt_xml_value_t **xml_value,
     uint8_t value_type,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_initialize";

	if( xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	if( *xml_value != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid XML value already set.",
		 function );

		return( -1 );
	}
	internal_xml_value = memory_allocate_structure(
	                      libfwevt_internal_xml_value_t );

	if( internal_xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create XML value.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_xml_value,
	     0,
	     sizeof( libfwevt_internal_xml_value_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear XML value.",
		 function );

		memory_free(
		 internal_xml_value );

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( internal_xml_value->data_segments ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data segments array.",
		 function );

		goto on_error;
	}
	internal_xml_value->value_type = value_type;

	*xml_value = (libfwevt_xml_value_t *) internal_xml_value;

	return( 1 );

on_error:
	if( internal_xml_value != NULL )
	{
		memory_free(
		 internal_xml_value );
	}
	return( -1 );
}

/* Frees a XML value
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_free(
     libfwevt_xml_value_t **xml_value,
     libcerror_error_t **error )
{
	static char *function = "libfwevt_xml_value_free";

	if( xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	if( *xml_value != NULL )
	{
		*xml_value = NULL;
	}
	return( 1 );
}

/* Frees a XML value
 * Returns 1 if successful or -1 on error
 */
int libfwevt_internal_xml_value_free(
     libfwevt_internal_xml_value_t **internal_xml_value,
     libcerror_error_t **error )
{
	static char *function = "libfwevt_internal_xml_value_free";
	int result            = 1;

	if( internal_xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	if( *internal_xml_value != NULL )
	{
		if( libcdata_array_free(
		     &( ( *internal_xml_value )->data_segments ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_data_segment_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free data segments array.",
			 function );

			result = -1;
		}
		memory_free(
		 *internal_xml_value );

		*internal_xml_value = NULL;
	}
	return( result );
}

/* Retrieves the value type
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_get_type(
     libfwevt_xml_value_t *xml_value,
     uint8_t *value_type,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_get_type";

	if( xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	internal_xml_value = (libfwevt_internal_xml_value_t *) xml_value;

	if( value_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value type.",
		 function );

		return( -1 );
	}
	*value_type = internal_xml_value->value_type;

	return( 1 );
}

/* Retrieves the number of data segments
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_get_number_of_data_segments(
     libfwevt_xml_value_t *xml_value,
     int *number_of_data_segments,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_get_number_of_data_segments";

	if( xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	internal_xml_value = (libfwevt_internal_xml_value_t *) xml_value;

	if( libcdata_array_get_number_of_entries(
	     internal_xml_value->data_segments,
	     number_of_data_segments,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of data segments.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific data segment and initialized its cached value
 * Returns 1 if successful or -1 on error
 */
int libfwevt_internal_xml_value_get_data_segment_with_cached_value(
     libfwevt_internal_xml_value_t *internal_xml_value,
     int data_segment_index,
     libfwevt_data_segment_t **data_segment,
     libcerror_error_t **error )
{
	libfwevt_data_segment_t *safe_data_segment = NULL;
	static char *function                      = "libfwevt_internal_xml_value_get_data_segment_with_cached_value";

	if( internal_xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
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
	if( libcdata_array_get_entry_by_index(
	     internal_xml_value->data_segments,
	     data_segment_index,
	     (intptr_t **) &safe_data_segment,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data segment: %d.",
		 function,
		 data_segment_index );

		return( -1 );
	}
	if( safe_data_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing data segment: %d.",
		 function,
		 data_segment_index );

		return( -1 );
	}
	if( safe_data_segment->cached_value_type == 0 )
	{
		switch( internal_xml_value->value_type & 0x7f )
		{
			case LIBFWEVT_VALUE_TYPE_INTEGER_8BIT:
			case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_8BIT:
				if( safe_data_segment->data_size != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
					 "%s: invalid data segment: %d - unsupported data size.",
					 function,
					 safe_data_segment );

					return( -1 );
				}
				safe_data_segment->value_64bit = safe_data_segment->data[ 0 ];

				break;

			case LIBFWEVT_VALUE_TYPE_INTEGER_16BIT:
			case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_16BIT:
				if( safe_data_segment->data_size != 2 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
					 "%s: invalid data segment: %d - unsupported data size.",
					 function,
					 safe_data_segment );

					return( -1 );
				}
				byte_stream_copy_to_uint16_little_endian(
				 safe_data_segment->data,
				 safe_data_segment->value_64bit );

				break;

			case LIBFWEVT_VALUE_TYPE_INTEGER_32BIT:
			case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_32BIT:
			case LIBFWEVT_VALUE_TYPE_HEXADECIMAL_INTEGER_32BIT:
			case LIBFWEVT_VALUE_TYPE_FLOATING_POINT_32BIT:
			case LIBFWEVT_VALUE_TYPE_BOOLEAN:
				if( safe_data_segment->data_size != 4 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
					 "%s: invalid data segment: %d - unsupported data size.",
					 function,
					 safe_data_segment );

					return( -1 );
				}
				byte_stream_copy_to_uint32_little_endian(
				 safe_data_segment->data,
				 safe_data_segment->value_64bit );

				break;

			case LIBFWEVT_VALUE_TYPE_INTEGER_64BIT:
			case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_64BIT:
			case LIBFWEVT_VALUE_TYPE_HEXADECIMAL_INTEGER_64BIT:
			case LIBFWEVT_VALUE_TYPE_FLOATING_POINT_64BIT:
				if( safe_data_segment->data_size != 8 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
					 "%s: invalid data segment: %d - unsupported data size.",
					 function,
					 safe_data_segment );

					return( -1 );
				}
				byte_stream_copy_to_uint64_little_endian(
				 safe_data_segment->data,
				 safe_data_segment->value_64bit );

				break;

			case LIBFWEVT_VALUE_TYPE_GUID:
				if( libfguid_identifier_initialize(
				     &( safe_data_segment->guid ),
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create GUID.",
					 function );

					return( -1 );
				}
				if( libfguid_identifier_copy_from_byte_stream(
				     safe_data_segment->guid,
				     safe_data_segment->data,
				     safe_data_segment->data_size,
				     LIBFGUID_ENDIAN_LITTLE,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy byte stream to GUID.",
					 function );

					return( -1 );
				}
				break;

			case LIBFWEVT_VALUE_TYPE_FILETIME:
				if( libfdatetime_filetime_initialize(
				     &( safe_data_segment->filetime ),
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create FILETIME.",
					 function );

					return( -1 );
				}
				if( libfdatetime_filetime_copy_from_byte_stream(
				     safe_data_segment->filetime,
				     safe_data_segment->data,
				     safe_data_segment->data_size,
				     LIBFDATETIME_ENDIAN_LITTLE,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy byte stream to FILETIME.",
					 function );

					return( -1 );
				}
				break;

			case LIBFWEVT_VALUE_TYPE_SYSTEMTIME:
				if( libfdatetime_systemtime_initialize(
				     &( safe_data_segment->systemtime ),
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create SYSTEMTIME.",
					 function );

					return( -1 );
				}
				if( libfdatetime_systemtime_copy_from_byte_stream(
				     safe_data_segment->systemtime,
				     safe_data_segment->data,
				     safe_data_segment->data_size,
				     LIBFDATETIME_ENDIAN_LITTLE,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy byte stream to SYSTEMTIME.",
					 function );

					return( -1 );
				}
				break;

			case LIBFWEVT_VALUE_TYPE_NT_SECURITY_IDENTIFIER:
				if( libfwnt_security_identifier_initialize(
				     &( safe_data_segment->security_identifier ),
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create NT security identifier.",
					 function );

					return( -1 );
				}
				if( libfwnt_security_identifier_copy_from_byte_stream(
				     safe_data_segment->security_identifier,
				     safe_data_segment->data,
				     safe_data_segment->data_size,
				     LIBFWNT_ENDIAN_LITTLE,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy byte stream to NT security identifier.",
					 function );

					return( -1 );
				}
				break;
		}
		safe_data_segment->cached_value_type = internal_xml_value->value_type & 0x7f;
	}
	*data_segment = safe_data_segment;

	return( 1 );
}

/* Appends a data segment
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_append_data_segment(
     libfwevt_xml_value_t *xml_value,
     const uint8_t *data,
     size_t data_size,
     int *data_segment_index,
     libcerror_error_t **error )
{
	libfwevt_data_segment_t *data_segment             = NULL;
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_append_data_segment";

	if( xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	internal_xml_value = (libfwevt_internal_xml_value_t *) xml_value;

	if( libfwevt_data_segment_initialize(
	     &data_segment,
	     data,
	     data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data segment.",
		 function );

		goto on_error;
	}
	if( libcdata_array_append_entry(
	     internal_xml_value->data_segments,
	     data_segment_index,
	     (intptr_t *) data_segment,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append data segment to array.",
		 function );

		return( -1 );
	}
	internal_xml_value->data_size += data_size;

	return( 1 );

on_error:
	if( data_segment != NULL )
	{
		libfwevt_data_segment_free(
		 &data_segment,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the data size
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_get_data_size(
     libfwevt_xml_value_t *xml_value,
     size_t *data_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_get_data_size";

	if( xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	internal_xml_value = (libfwevt_internal_xml_value_t *) xml_value;

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
	*data_size = internal_xml_value->data_size;

	return( 1 );
}

/* Copies the data
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_copy_data(
     libfwevt_xml_value_t *xml_value,
     uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libfwevt_data_segment_t *data_segment             = NULL;
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_copy_data";
	size_t data_offset                                = 0;
	int data_segment_index                            = 0;
	int number_of_data_segments                       = 0;

	if( xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	internal_xml_value = (libfwevt_internal_xml_value_t *) xml_value;

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
	if( ( data_size < internal_xml_value->data_size )
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
	if( libcdata_array_get_number_of_entries(
	     internal_xml_value->data_segments,
	     &number_of_data_segments,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of data segments.",
		 function );

		return( -1 );
	}
	for( data_segment_index = 0;
	     data_segment_index < number_of_data_segments;
	     data_segment_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_xml_value->data_segments,
		     data_segment_index,
		     (intptr_t **) &data_segment,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data segment: %d.",
			 function,
			 data_segment_index );

			return( -1 );
		}
		if( data_segment == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing data segment: %d.",
			 function,
			 data_segment_index );

			return( -1 );
		}
		if( data_segment->data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid data segment: %d - missing data.",
			 function,
			 data_segment_index );

			return( -1 );
		}
		if( ( data_segment->data_size > data_size )
		 || ( data_offset > ( data_size - data_segment->data_size ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid data segment: %d - data size value out of bounds.",
			 function,
			 data_segment_index );

			return( -1 );
		}
		if( memory_copy(
		     &( data[ data_offset ] ),
		     data_segment->data,
		     data_segment->data_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy data segment: %d.",
			 function,
			 data_segment_index );

			return( -1 );
		}
		data_offset += data_segment->data_size;
	}
	return( 1 );
}

/* Retrieves the value data as a 8-bit integer value
 * Returns 1 if successful, 0 if value not be retrieved or -1 on error
 */
int libfwevt_value_get_data_as_8bit_integer(
     libfwevt_xml_value_t *xml_value,
     uint8_t *value_8bit,
     libcerror_error_t **error )
{
	libfwevt_data_segment_t *data_segment             = NULL;
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_value_get_data_as_8bit_integer";

	if( xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	internal_xml_value = (libfwevt_internal_xml_value_t *) xml_value;

	if( value_8bit == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value 8-bit.",
		 function );

		return( -1 );
	}
	if( ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_INTEGER_8BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_8BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_INTEGER_16BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_16BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_INTEGER_32BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_32BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_INTEGER_64BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_64BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_STRING_UTF16 ) )
	{
		return( 0 );
	}
	if( libfwevt_internal_xml_value_get_data_segment_with_cached_value(
	     internal_xml_value,
	     0,
	     &data_segment,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data segment: 0.",
		 function );

		return( -1 );
	}
	if( data_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing data segment: 0.",
		 function );

		return( -1 );
	}
	if( internal_xml_value->value_type == LIBFWEVT_VALUE_TYPE_STRING_UTF16 )
	{
		if( libfwevt_integer_copy_from_utf16_stream(
		     &( data_segment->value_64bit ),
		     data_segment->data,
		     data_segment->data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to determine integer value from UTF-16 string data segment: 0.",
			 function );

			return( -1 );
		}
		data_segment->cached_value_type = internal_xml_value->value_type;
	}
	if( data_segment->value_64bit > (uint64_t) UINT8_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data segment: 0 - integer value out of bounds.",
		 function );

		return( -1 );
	}
	*value_8bit = (uint8_t) data_segment->value_64bit;

	return( 1 );
}

/* Retrieves the value data as a 32-bit integer value
 * Returns 1 if successful, 0 if value not be retrieved or -1 on error
 */
int libfwevt_value_get_data_as_32bit_integer(
     libfwevt_xml_value_t *xml_value,
     uint32_t *value_32bit,
     libcerror_error_t **error )
{
	libfwevt_data_segment_t *data_segment             = NULL;
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_value_get_data_as_32bit_integer";

	if( xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	internal_xml_value = (libfwevt_internal_xml_value_t *) xml_value;

	if( value_32bit == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value 32-bit.",
		 function );

		return( -1 );
	}
	if( ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_INTEGER_8BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_8BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_INTEGER_16BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_16BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_INTEGER_32BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_32BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_INTEGER_64BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_64BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_STRING_UTF16 ) )
	{
		return( 0 );
	}
	if( libfwevt_internal_xml_value_get_data_segment_with_cached_value(
	     internal_xml_value,
	     0,
	     &data_segment,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data segment: 0.",
		 function );

		return( -1 );
	}
	if( data_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing data segment: 0.",
		 function );

		return( -1 );
	}
	if( internal_xml_value->value_type == LIBFWEVT_VALUE_TYPE_STRING_UTF16 )
	{
		if( libfwevt_integer_copy_from_utf16_stream(
		     &( data_segment->value_64bit ),
		     data_segment->data,
		     data_segment->data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to determine integer value from UTF-16 string data segment: 0.",
			 function );

			return( -1 );
		}
		data_segment->cached_value_type = internal_xml_value->value_type;
	}
	if( data_segment->value_64bit > (uint64_t) UINT32_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data segment: 0 - integer value out of bounds.",
		 function );

		return( -1 );
	}
	*value_32bit = (uint32_t) data_segment->value_64bit;

	return( 1 );
}

/* Retrieves the value data as a 64-bit integer value
 * Returns 1 if successful, 0 if value not be retrieved or -1 on error
 */
int libfwevt_value_get_data_as_64bit_integer(
     libfwevt_xml_value_t *xml_value,
     uint64_t *value_64bit,
     libcerror_error_t **error )
{
	libfwevt_data_segment_t *data_segment             = NULL;
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_value_get_data_as_64bit_integer";

	if( xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	internal_xml_value = (libfwevt_internal_xml_value_t *) xml_value;

	if( value_64bit == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value 64-bit.",
		 function );

		return( -1 );
	}
	if( ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_INTEGER_8BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_8BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_INTEGER_16BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_16BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_INTEGER_32BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_32BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_INTEGER_64BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_64BIT )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_STRING_UTF16 ) )
	{
		return( 0 );
	}
	if( libfwevt_internal_xml_value_get_data_segment_with_cached_value(
	     internal_xml_value,
	     0,
	     &data_segment,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data segment: 0.",
		 function );

		return( -1 );
	}
	if( data_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing data segment: 0.",
		 function );

		return( -1 );
	}
	if( internal_xml_value->value_type == LIBFWEVT_VALUE_TYPE_STRING_UTF16 )
	{
		if( libfwevt_integer_copy_from_utf16_stream(
		     &( data_segment->value_64bit ),
		     data_segment->data,
		     data_segment->data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to determine integer value from UTF-16 string data segment: 0.",
			 function );

			return( -1 );
		}
		data_segment->cached_value_type = internal_xml_value->value_type;
	}
	*value_64bit = data_segment->value_64bit;

	return( 1 );
}

/* Retrieves the value data as a 64-bit FILETIME value
 * Returns 1 if successful, 0 if value not be retrieved or -1 on error
 */
int libfwevt_value_get_data_as_filetime(
     libfwevt_xml_value_t *xml_value,
     uint64_t *filetime,
     libcerror_error_t **error )
{
	libfwevt_data_segment_t *data_segment             = NULL;
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_value_get_data_as_filetime";
	uint64_t safe_filetime                            = 0;

	if( xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	internal_xml_value = (libfwevt_internal_xml_value_t *) xml_value;

	if( filetime == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid FILETIME value.",
		 function );

		return( -1 );
	}
	if( ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_FILETIME )
	 && ( internal_xml_value->value_type != LIBFWEVT_VALUE_TYPE_STRING_UTF16 ) )
	{
		return( 0 );
	}
	if( libcdata_array_get_entry_by_index(
	     internal_xml_value->data_segments,
	     0,
	     (intptr_t **) &data_segment,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data segment: 0.",
		 function );

		return( -1 );
	}
	if( data_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing data segment: 0.",
		 function );

		return( -1 );
	}
	if( data_segment->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data segment: 0 - missing data.",
		 function );

		return( -1 );
	}
	if( internal_xml_value->value_type == LIBFWEVT_VALUE_TYPE_STRING_UTF16 )
	{
		if( libfwevt_filetime_copy_from_utf16_stream(
		     &safe_filetime,
		     data_segment->data,
		     data_segment->data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy data segment: 0 to FILTEIME.",
			 function );

			return( -1 );
		}
	}
	else
	{
		if( data_segment->data_size != 8 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid data segment: 0 - unsupported data size.",
			 function );

			return( -1 );
		}
		byte_stream_copy_to_uint64_little_endian(
		 data_segment->data,
		 safe_filetime );
	}
	*filetime = safe_filetime;

	return( 1 );
}

/* Retrieves the size of the data segment formatted as an UTF-8 string
 * The string size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_internal_xml_value_get_data_segment_as_utf8_string_size(
     libfwevt_internal_xml_value_t *internal_xml_value,
     int data_segment_index,
     libfwevt_data_segment_t *data_segment,
     size_t *utf8_string_size,
     uint8_t escape_characters,
     libcerror_error_t **error )
{
	static char *function        = "libfwevt_internal_xml_value_get_data_segment_as_utf8_string_size";
	size_t base16_stream_size    = 0;
	size_t safe_utf8_string_size = 0;
	uint32_t format_flags        = 0;
	int result                   = 0;

	if( internal_xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
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
	if( utf8_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string size.",
		 function );

		return( -1 );
	}
	switch( internal_xml_value->value_type & 0x7f )
	{
		case LIBFWEVT_VALUE_TYPE_STRING_UTF16:
			if( data_segment->data_size == 0 )
			{
				result = 1;
			}
			else if( escape_characters == 0 )
			{
				result = libuna_utf8_string_size_from_utf16_stream(
				          data_segment->data,
				          data_segment->data_size,
				          LIBUNA_ENDIAN_LITTLE,
				          &safe_utf8_string_size,
				          error );
			}
			else
			{
				result = libfwevt_utf8_xml_string_size_from_utf16_stream(
				          data_segment->data,
				          data_segment->data_size,
				          LIBUNA_ENDIAN_LITTLE,
				          &safe_utf8_string_size,
				          error );
			}
			break;

		case LIBFWEVT_VALUE_TYPE_STRING_BYTE_STREAM:
			if( data_segment->data_size == 0 )
			{
				result = 1;
			}
			else
			{
/* TODO pass codepage */
				result = libuna_utf8_string_size_from_byte_stream(
				          data_segment->data,
				          data_segment->data_size,
				          LIBUNA_CODEPAGE_WINDOWS_1252,
				          &safe_utf8_string_size,
				          error );
			}
/* TODO add support for escape_characters */
			break;

		case LIBFWEVT_VALUE_TYPE_INTEGER_8BIT:
			result = libfwevt_integer_as_signed_decimal_get_string_size(
			          data_segment->value_64bit,
			          8,
			          &safe_utf8_string_size,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_INTEGER_16BIT:
			result = libfwevt_integer_as_signed_decimal_get_string_size(
			          data_segment->value_64bit,
			          16,
			          &safe_utf8_string_size,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_INTEGER_32BIT:
			result = libfwevt_integer_as_signed_decimal_get_string_size(
			          data_segment->value_64bit,
			          32,
			          &safe_utf8_string_size,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_INTEGER_64BIT:
			result = libfwevt_integer_as_signed_decimal_get_string_size(
			          data_segment->value_64bit,
			          64,
			          &safe_utf8_string_size,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_8BIT:
		case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_16BIT:
		case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_32BIT:
		case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_64BIT:
			result = libfwevt_integer_as_unsigned_decimal_get_string_size(
			          data_segment->value_64bit,
			          &safe_utf8_string_size,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_FLOATING_POINT_32BIT:
			result = libfwevt_float32_get_string_size(
			          (uint32_t) data_segment->value_64bit,
			          &safe_utf8_string_size,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_FLOATING_POINT_64BIT:
			result = libfwevt_float64_get_string_size(
			          data_segment->value_64bit,
			          &safe_utf8_string_size,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_BOOLEAN:
			if( data_segment->value_64bit == 0 )
			{
				safe_utf8_string_size += 6;
			}
			else
			{
				safe_utf8_string_size += 5;
			}
			result = 1;

			break;

		case LIBFWEVT_VALUE_TYPE_BINARY_DATA:
			if( data_segment->data_size == 0 )
			{
				result = 1;
			}
			else
			{
				format_flags = LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE;

				result = libuna_base16_stream_size_from_byte_stream(
				          data_segment->data,
				          data_segment->data_size,
				          &base16_stream_size,
				          format_flags,
				          error );

				if( result == 1 )
				{
					safe_utf8_string_size += base16_stream_size + 1;
				}
			}
			break;

		case LIBFWEVT_VALUE_TYPE_GUID:
			result = libfguid_identifier_get_string_size(
			          data_segment->guid,
			          &safe_utf8_string_size,
			          LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE | LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_FILETIME:
			result = libfdatetime_filetime_get_string_size(
			          data_segment->filetime,
			          &safe_utf8_string_size,
			          LIBFDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS | LIBFDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_SYSTEMTIME:
			result = libfdatetime_systemtime_get_string_size(
			          data_segment->systemtime,
			          &safe_utf8_string_size,
			          LIBFDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS | LIBFDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_NT_SECURITY_IDENTIFIER:
			result = libfwnt_security_identifier_get_string_size(
			          data_segment->security_identifier,
			          &safe_utf8_string_size,
				  0,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_HEXADECIMAL_INTEGER_32BIT:
			safe_utf8_string_size = 11;

			result = 1;
			break;

		case LIBFWEVT_VALUE_TYPE_HEXADECIMAL_INTEGER_64BIT:
			safe_utf8_string_size = 19;

			result = 1;
			break;

		default:
			break;
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to determine size UTF-8 string of data segment: %d.",
		 function,
		 data_segment_index );

		return( -1 );
	}
	*utf8_string_size = safe_utf8_string_size;

	return( 1 );
}

/* Retrieves the data segment formatted as an UTF-8 string
 * Returns 1 if successful or -1 on error
 */
int libfwevt_internal_xml_value_get_data_segment_as_utf8_string(
     libfwevt_internal_xml_value_t *internal_xml_value,
     int data_segment_index,
     libfwevt_data_segment_t *data_segment,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     uint8_t escape_characters,
     libcerror_error_t **error )
{
	static char *function         = "libfwevt_internal_xml_value_get_data_segment_as_utf8_string";
	size_t base16_stream_index    = 0;
	size_t safe_utf8_string_index = 0;
	uint32_t format_flags         = 0;
	uint8_t number_of_characters  = 0;
	int result                    = 0;

	if( internal_xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
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
	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string index.",
		 function );

		return( -1 );
	}
	switch( internal_xml_value->value_type & 0x7f )
	{
		case LIBFWEVT_VALUE_TYPE_STRING_UTF16:
			if( data_segment->data_size == 0 )
			{
				result = 1;
			}
			else if( escape_characters == 0 )
			{
				result = libuna_utf8_string_with_index_copy_from_utf16_stream(
				          utf8_string,
				          utf8_string_size,
				          utf8_string_index,
				          data_segment->data,
				          data_segment->data_size,
				          LIBUNA_ENDIAN_LITTLE,
				          error );
			}
			else
			{
				result = libfwevt_utf8_xml_string_with_index_copy_from_utf16_stream(
				          utf8_string,
				          utf8_string_size,
				          utf8_string_index,
				          data_segment->data,
				          data_segment->data_size,
				          LIBUNA_ENDIAN_LITTLE,
				          error );
			}
			break;

		case LIBFWEVT_VALUE_TYPE_STRING_BYTE_STREAM:
/* TODO pass codepage */
			result = libuna_utf8_string_with_index_copy_from_byte_stream(
			          utf8_string,
			          utf8_string_size,
			          utf8_string_index,
			          data_segment->data,
			          data_segment->data_size,
			          LIBUNA_CODEPAGE_WINDOWS_1252,
			          error );
/* TODO add support for escape_characters */
			break;

		case LIBFWEVT_VALUE_TYPE_INTEGER_8BIT:
			result = libfwevt_integer_as_signed_decimal_copy_to_utf8_string_with_index(
			          data_segment->value_64bit,
			          8,
			          utf8_string,
			          utf8_string_size,
			          utf8_string_index,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_INTEGER_16BIT:
			result = libfwevt_integer_as_signed_decimal_copy_to_utf8_string_with_index(
			          data_segment->value_64bit,
			          16,
			          utf8_string,
			          utf8_string_size,
			          utf8_string_index,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_INTEGER_32BIT:
			result = libfwevt_integer_as_signed_decimal_copy_to_utf8_string_with_index(
			          data_segment->value_64bit,
			          32,
			          utf8_string,
			          utf8_string_size,
			          utf8_string_index,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_INTEGER_64BIT:
			result = libfwevt_integer_as_signed_decimal_copy_to_utf8_string_with_index(
			          data_segment->value_64bit,
			          64,
			          utf8_string,
			          utf8_string_size,
			          utf8_string_index,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_8BIT:
		case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_16BIT:
		case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_32BIT:
		case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_64BIT:
			result = libfwevt_integer_as_unsigned_decimal_copy_to_utf8_string_with_index(
			          data_segment->value_64bit,
			          utf8_string,
			          utf8_string_size,
			          utf8_string_index,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_FLOATING_POINT_32BIT:
			result = libfwevt_float32_copy_to_utf8_string_with_index(
			          (uint32_t) data_segment->value_64bit,
			          utf8_string,
			          utf8_string_size,
			          utf8_string_index,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_FLOATING_POINT_64BIT:
			result = libfwevt_float64_copy_to_utf8_string_with_index(
			          data_segment->value_64bit,
			          utf8_string,
			          utf8_string_size,
			          utf8_string_index,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_BOOLEAN:
			if( data_segment->value_64bit == 0 )
			{
				number_of_characters = 6;
			}
			else
			{
				number_of_characters = 5;
			}
			safe_utf8_string_index = *utf8_string_index;

			if( ( number_of_characters > utf8_string_size )
			 || ( safe_utf8_string_index > ( utf8_string_size - number_of_characters ) ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: invalid UTF-8 string size value too small.",
				 function );

				return( -1 );
			}
			if( data_segment->value_64bit == 0 )
			{
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'f';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'a';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'l';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 's';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'e';
			}
			else
			{
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 't';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'r';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'u';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'e';
			}
			utf8_string[ safe_utf8_string_index++ ] = 0;

			*utf8_string_index = safe_utf8_string_index;

			result = 1;

			break;

		case LIBFWEVT_VALUE_TYPE_BINARY_DATA:
			base16_stream_index = *utf8_string_index;
			format_flags        = LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE;

			result = libuna_base16_stream_with_index_copy_from_byte_stream(
			          (uint8_t *) utf8_string,
			          utf8_string_size,
			          &base16_stream_index,
			          data_segment->data,
			          data_segment->data_size,
			          format_flags,
			          error );

			if( result == 1 )
			{
				*utf8_string_index = base16_stream_index + 1;
			}
			break;

		case LIBFWEVT_VALUE_TYPE_GUID:
			result = libfguid_identifier_copy_to_utf8_string_with_index(
			          data_segment->guid,
			          utf8_string,
			          utf8_string_size,
			          utf8_string_index,
			          LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE | LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_FILETIME:
			result = libfdatetime_filetime_copy_to_utf8_string_with_index(
			          data_segment->filetime,
			          utf8_string,
			          utf8_string_size,
			          utf8_string_index,
			          LIBFDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS | LIBFDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_SYSTEMTIME:
			result = libfdatetime_systemtime_copy_to_utf8_string_with_index(
			          data_segment->systemtime,
			          utf8_string,
			          utf8_string_size,
			          utf8_string_index,
			          LIBFDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS | LIBFDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_NT_SECURITY_IDENTIFIER:
			result = libfwnt_security_identifier_copy_to_utf8_string_with_index(
			          data_segment->security_identifier,
			          utf8_string,
			          utf8_string_size,
			          utf8_string_index,
				  0,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_HEXADECIMAL_INTEGER_32BIT:
			result = libfwevt_integer_as_hexadecimal_copy_to_utf8_string_with_index(
			          data_segment->value_64bit,
			          32,
			          utf8_string,
			          utf8_string_size,
			          utf8_string_index,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_HEXADECIMAL_INTEGER_64BIT:
			result = libfwevt_integer_as_hexadecimal_copy_to_utf8_string_with_index(
			          data_segment->value_64bit,
			          64,
			          utf8_string,
			          utf8_string_size,
			          utf8_string_index,
			          error );
			break;

		default:
			break;
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy data segment: %d to UTF-8 string.",
		 function,
		 data_segment_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the value data formatted as an UTF-8 string
 * The string size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_internal_xml_value_get_data_as_utf8_string_size(
     libfwevt_internal_xml_value_t *internal_xml_value,
     size_t *utf8_string_size,
     uint8_t escape_characters,
     libcerror_error_t **error )
{
	libfwevt_data_segment_t *data_segment = NULL;
	static char *function                 = "libfwevt_internal_xml_value_get_data_as_utf8_string_size";
	size_t data_segment_size              = 0;
	size_t safe_utf8_string_size          = 0;
	int data_segment_index                = 0;
	int number_of_data_segments           = 0;

	if( internal_xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	if( utf8_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string size.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_xml_value->data_segments,
	     &number_of_data_segments,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of data segments.",
		 function );

		return( -1 );
	}
	for( data_segment_index = 0;
	     data_segment_index < number_of_data_segments;
	     data_segment_index++ )
	{
		if( libfwevt_internal_xml_value_get_data_segment_with_cached_value(
		     internal_xml_value,
		     data_segment_index,
		     &data_segment,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data segment: %d.",
			 function,
			 data_segment_index );

			return( -1 );
		}
		if( libfwevt_internal_xml_value_get_data_segment_as_utf8_string_size(
		     internal_xml_value,
		     data_segment_index,
		     data_segment,
		     &data_segment_size,
		     escape_characters,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-8 string size of element data segment: %d.",
			 function,
			 data_segment_index );

			return( -1 );
		}
		if( data_segment_size > 1 )
		{
			safe_utf8_string_size += data_segment_size - 1;
		}
	}
	if( ( number_of_data_segments == 1 )
	 && ( data_segment != NULL )
	 && ( safe_utf8_string_size == 1 ) )
	{
		if( ( data_segment->data_size >= 2 )
		 && ( data_segment->data[ 0 ] == '\n' )
		 && ( data_segment->data[ 1 ] == 0 ) )
		{
			/* The value data consists of a single linefeed consider it empty
			 */
			safe_utf8_string_size = 0;
		}
	}
	if( safe_utf8_string_size > 0 )
	{
		safe_utf8_string_size++;
	}
	*utf8_string_size = safe_utf8_string_size;

	return( 1 );
}

/* Retrieves the data formatted as an UTF-8 string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_internal_xml_value_get_data_as_utf8_string_with_index(
     libfwevt_internal_xml_value_t *internal_xml_value,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     uint8_t escape_characters,
     libcerror_error_t **error )
{
	libfwevt_data_segment_t *data_segment = NULL;
	static char *function                 = "libfwevt_internal_xml_value_get_data_as_utf8_string_with_index";
	size_t safe_utf8_string_index         = 0;
	int data_segment_index                = 0;
	int number_of_data_segments           = 0;

	if( internal_xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string index.",
		 function );

		return( -1 );
	}
	safe_utf8_string_index = *utf8_string_index;

	if( libcdata_array_get_number_of_entries(
	     internal_xml_value->data_segments,
	     &number_of_data_segments,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of data segments.",
		 function );

		return( -1 );
	}
	for( data_segment_index = 0;
	     data_segment_index < number_of_data_segments;
	     data_segment_index++ )
	{
		if( libfwevt_internal_xml_value_get_data_segment_with_cached_value(
		     internal_xml_value,
		     data_segment_index,
		     &data_segment,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data segment: %d.",
			 function,
			 data_segment_index );

			return( -1 );
		}
		if( libfwevt_internal_xml_value_get_data_segment_as_utf8_string(
		     internal_xml_value,
		     data_segment_index,
		     data_segment,
		     utf8_string,
		     utf8_string_size,
		     &safe_utf8_string_index,
		     escape_characters,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy data segment: %d to UTF-8 string.",
			 function,
			 data_segment_index );

			return( -1 );
		}
		safe_utf8_string_index--;
	}
	if( ( number_of_data_segments == 1 )
	 && ( data_segment != NULL )
	 && ( safe_utf8_string_index == 1 ) )
	{
		if( ( data_segment->data_size >= 2 )
		 && ( data_segment->data[ 0 ] == '\n' )
		 && ( data_segment->data[ 1 ] == 0 ) )
		{
			/* The value data consists of a single linefeed consider it empty
			 */
			safe_utf8_string_index = 0;
		}
	}
	if( safe_utf8_string_index > 0 )
	{
		if( safe_utf8_string_index >= utf8_string_size  )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: invalid UTF-8 string size value too small.",
			 function );

			return( -1 );
		}
		utf8_string[ safe_utf8_string_index++ ] = 0;
	}
	*utf8_string_index = safe_utf8_string_index;

	return( 1 );
}

/* Retrieves the size of an UTF-8 encoded string of the value data
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_get_utf8_string_size(
     libfwevt_xml_value_t *xml_value,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_get_utf8_string_size";

	if( xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	internal_xml_value = (libfwevt_internal_xml_value_t *) xml_value;

	if( libfwevt_internal_xml_value_get_data_as_utf8_string_size(
	     internal_xml_value,
	     utf8_string_size,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size of UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies the value data to an UTF-8 encoded string
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_copy_to_utf8_string(
     libfwevt_xml_value_t *xml_value,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libfwevt_xml_value_copy_to_utf8_string";

	if( libfwevt_xml_value_get_data_as_utf8_string(
	     xml_value,
	     utf8_string,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size of UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the value data formatted as an UTF-8 string
 * The string size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_get_data_as_utf8_string_size(
     libfwevt_xml_value_t *xml_value,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_get_data_as_utf8_string_size";

	if( xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	internal_xml_value = (libfwevt_internal_xml_value_t *) xml_value;

	if( libfwevt_internal_xml_value_get_data_as_utf8_string_size(
	     internal_xml_value,
	     utf8_string_size,
	     0,
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

/* Retrieves the data formatted as an UTF-8 string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_get_data_as_utf8_string(
     libfwevt_xml_value_t *xml_value,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_get_data_as_utf8_string";
	size_t utf8_string_index                          = 0;

	if( xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	internal_xml_value = (libfwevt_internal_xml_value_t *) xml_value;

	if( libfwevt_internal_xml_value_get_data_as_utf8_string_with_index(
	     internal_xml_value,
	     utf8_string,
	     utf8_string_size,
	     &utf8_string_index,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size of UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the data segment formatted as an UTF-16 string
 * The string size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_internal_xml_value_get_data_segment_as_utf16_string_size(
     libfwevt_internal_xml_value_t *internal_xml_value,
     int data_segment_index,
     libfwevt_data_segment_t *data_segment,
     size_t *utf16_string_size,
     uint8_t escape_characters,
     libcerror_error_t **error )
{
	static char *function         = "libfwevt_internal_xml_value_get_data_segment_as_utf16_string_size";
	size_t base16_stream_size     = 0;
	size_t safe_utf16_string_size = 0;
	uint32_t format_flags         = 0;
	int result                    = 0;

	if( internal_xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
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
	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	switch( internal_xml_value->value_type & 0x7f )
	{
		case LIBFWEVT_VALUE_TYPE_STRING_UTF16:
			if( data_segment->data_size == 0 )
			{
				result = 1;
			}
			else if( escape_characters == 0 )
			{
				result = libuna_utf16_string_size_from_utf16_stream(
				          data_segment->data,
				          data_segment->data_size,
				          LIBUNA_ENDIAN_LITTLE,
				          &safe_utf16_string_size,
				          error );
			}
			else
			{
				result = libfwevt_utf16_xml_string_size_from_utf16_stream(
				          data_segment->data,
				          data_segment->data_size,
				          LIBUNA_ENDIAN_LITTLE,
				          &safe_utf16_string_size,
				          error );
			}
			break;

		case LIBFWEVT_VALUE_TYPE_STRING_BYTE_STREAM:
			if( data_segment->data_size == 0 )
			{
				result = 1;
			}
			else
			{
/* TODO pass codepage */
				result = libuna_utf16_string_size_from_byte_stream(
				          data_segment->data,
				          data_segment->data_size,
				          LIBUNA_CODEPAGE_WINDOWS_1252,
				          &safe_utf16_string_size,
				          error );
			}
/* TODO add support for escape_characters */
			break;

		case LIBFWEVT_VALUE_TYPE_INTEGER_8BIT:
			result = libfwevt_integer_as_signed_decimal_get_string_size(
			          data_segment->value_64bit,
			          8,
			          &safe_utf16_string_size,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_INTEGER_16BIT:
			result = libfwevt_integer_as_signed_decimal_get_string_size(
			          data_segment->value_64bit,
			          16,
			          &safe_utf16_string_size,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_INTEGER_32BIT:
			result = libfwevt_integer_as_signed_decimal_get_string_size(
			          data_segment->value_64bit,
			          32,
			          &safe_utf16_string_size,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_INTEGER_64BIT:
			result = libfwevt_integer_as_signed_decimal_get_string_size(
			          data_segment->value_64bit,
			          64,
			          &safe_utf16_string_size,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_8BIT:
		case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_16BIT:
		case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_32BIT:
		case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_64BIT:
			result = libfwevt_integer_as_unsigned_decimal_get_string_size(
			          data_segment->value_64bit,
			          &safe_utf16_string_size,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_FLOATING_POINT_32BIT:
			result = libfwevt_float32_get_string_size(
			          (uint32_t) data_segment->value_64bit,
			          &safe_utf16_string_size,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_FLOATING_POINT_64BIT:
			result = libfwevt_float64_get_string_size(
			          data_segment->value_64bit,
			          &safe_utf16_string_size,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_BOOLEAN:
			if( data_segment->value_64bit == 0 )
			{
				safe_utf16_string_size += 6;
			}
			else
			{
				safe_utf16_string_size += 5;
			}
			result = 1;

			break;

		case LIBFWEVT_VALUE_TYPE_BINARY_DATA:
			if( data_segment->data_size == 0 )
			{
				result = 1;
			}
			else
			{
				format_flags = LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE;

				if( _BYTE_STREAM_HOST_IS_ENDIAN_BIG )
				{
					format_flags |= LIBUNA_BASE16_VARIANT_ENCODING_UTF16_BIG_ENDIAN;
				}
				else if( _BYTE_STREAM_HOST_IS_ENDIAN_LITTLE )
				{
					format_flags |= LIBUNA_BASE16_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN;
				}
				result = libuna_base16_stream_size_from_byte_stream(
				          data_segment->data,
				          data_segment->data_size,
				          &base16_stream_size,
				          format_flags,
				          error );

				if( result == 1 )
				{
					safe_utf16_string_size += ( base16_stream_size / 2 ) + 1;
				}
			}
			break;

		case LIBFWEVT_VALUE_TYPE_GUID:
			result = libfguid_identifier_get_string_size(
			          data_segment->guid,
			          &safe_utf16_string_size,
			          LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE | LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_FILETIME:
			result = libfdatetime_filetime_get_string_size(
			          data_segment->filetime,
			          &safe_utf16_string_size,
			          LIBFDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS | LIBFDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_SYSTEMTIME:
			result = libfdatetime_systemtime_get_string_size(
			          data_segment->systemtime,
			          &safe_utf16_string_size,
			          LIBFDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS | LIBFDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_NT_SECURITY_IDENTIFIER:
			result = libfwnt_security_identifier_get_string_size(
			          data_segment->security_identifier,
			          &safe_utf16_string_size,
				  0,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_HEXADECIMAL_INTEGER_32BIT:
			safe_utf16_string_size = 11;

			result = 1;
			break;

		case LIBFWEVT_VALUE_TYPE_HEXADECIMAL_INTEGER_64BIT:
			safe_utf16_string_size = 19;

			result = 1;
			break;

		default:
			break;
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to determine size UTF-16 string of data segment: %d.",
		 function,
		 data_segment_index );

		return( -1 );
	}
	*utf16_string_size = safe_utf16_string_size;

	return( 1 );
}

/* Retrieves the data segment formatted as an UTF-16 string
 * Returns 1 if successful or -1 on error
 */
int libfwevt_internal_xml_value_get_data_segment_as_utf16_string(
     libfwevt_internal_xml_value_t *internal_xml_value,
     int data_segment_index,
     libfwevt_data_segment_t *data_segment,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     uint8_t escape_characters,
     libcerror_error_t **error )
{
	static char *function          = "libfwevt_internal_xml_value_get_data_segment_as_utf16_string";
	size_t base16_stream_index     = 0;
	size_t safe_utf16_string_index = 0;
	uint32_t format_flags          = 0;
	uint8_t number_of_characters   = 0;
	int result                     = 0;

	if( internal_xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
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
	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string index.",
		 function );

		return( -1 );
	}
	if( libfwevt_internal_xml_value_get_data_segment_with_cached_value(
	     internal_xml_value,
	     data_segment_index,
	     &data_segment,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data segment: %d.",
		 function,
		 data_segment_index );

		return( -1 );
	}
	switch( internal_xml_value->value_type & 0x7f )
	{
		case LIBFWEVT_VALUE_TYPE_STRING_UTF16:
			if( data_segment->data_size == 0 )
			{
				result = 1;
			}
			else if( escape_characters == 0 )
			{
				result = libuna_utf16_string_with_index_copy_from_utf16_stream(
				          utf16_string,
				          utf16_string_size,
				          utf16_string_index,
				          data_segment->data,
				          data_segment->data_size,
				          LIBUNA_ENDIAN_LITTLE,
				          error );
			}
			else
			{
				result = libfwevt_utf16_xml_string_with_index_copy_from_utf16_stream(
				          utf16_string,
				          utf16_string_size,
				          utf16_string_index,
				          data_segment->data,
				          data_segment->data_size,
				          LIBUNA_ENDIAN_LITTLE,
				          error );
			}
			break;

		case LIBFWEVT_VALUE_TYPE_STRING_BYTE_STREAM:
/* TODO pass codepage */
			result = libuna_utf16_string_with_index_copy_from_byte_stream(
			          utf16_string,
			          utf16_string_size,
			          utf16_string_index,
			          data_segment->data,
			          data_segment->data_size,
			          LIBUNA_CODEPAGE_WINDOWS_1252,
			          error );
/* TODO add support for escape_characters */
			break;

		case LIBFWEVT_VALUE_TYPE_INTEGER_8BIT:
			result = libfwevt_integer_as_signed_decimal_copy_to_utf16_string_with_index(
			          data_segment->value_64bit,
			          8,
			          utf16_string,
			          utf16_string_size,
			          utf16_string_index,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_INTEGER_16BIT:
			result = libfwevt_integer_as_signed_decimal_copy_to_utf16_string_with_index(
			          data_segment->value_64bit,
			          16,
			          utf16_string,
			          utf16_string_size,
			          utf16_string_index,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_INTEGER_32BIT:
			result = libfwevt_integer_as_signed_decimal_copy_to_utf16_string_with_index(
			          data_segment->value_64bit,
			          32,
			          utf16_string,
			          utf16_string_size,
			          utf16_string_index,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_INTEGER_64BIT:
			result = libfwevt_integer_as_signed_decimal_copy_to_utf16_string_with_index(
			          data_segment->value_64bit,
			          64,
			          utf16_string,
			          utf16_string_size,
			          utf16_string_index,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_8BIT:
		case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_16BIT:
		case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_32BIT:
		case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_64BIT:
			result = libfwevt_integer_as_unsigned_decimal_copy_to_utf16_string_with_index(
			          data_segment->value_64bit,
			          utf16_string,
			          utf16_string_size,
			          utf16_string_index,
			          error );
			break;


		case LIBFWEVT_VALUE_TYPE_FLOATING_POINT_32BIT:
			result = libfwevt_float32_copy_to_utf16_string_with_index(
			          (uint32_t) data_segment->value_64bit,
			          utf16_string,
			          utf16_string_size,
			          utf16_string_index,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_FLOATING_POINT_64BIT:
			result = libfwevt_float64_copy_to_utf16_string_with_index(
			          data_segment->value_64bit,
			          utf16_string,
			          utf16_string_size,
			          utf16_string_index,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_BOOLEAN:
			if( data_segment->value_64bit == 0 )
			{
				number_of_characters = 6;
			}
			else
			{
				number_of_characters = 5;
			}
			safe_utf16_string_index = *utf16_string_index;

			if( ( number_of_characters > utf16_string_size )
			 || ( safe_utf16_string_index > ( utf16_string_size - number_of_characters ) ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: invalid UTF-16 string size value too small.",
				 function );

				return( -1 );
			}
			if( data_segment->value_64bit == 0 )
			{
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'f';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'a';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'l';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 's';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'e';
			}
			else
			{
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 't';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'r';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'u';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'e';
			}
			utf16_string[ safe_utf16_string_index++ ] = 0;

			*utf16_string_index = safe_utf16_string_index;

			result = 1;

			break;

		case LIBFWEVT_VALUE_TYPE_BINARY_DATA:
			base16_stream_index = *utf16_string_index * 2;
			format_flags        = LIBUNA_BASE16_VARIANT_CASE_UPPER | LIBUNA_BASE16_VARIANT_CHARACTER_LIMIT_NONE;

			if( _BYTE_STREAM_HOST_IS_ENDIAN_BIG )
			{
				format_flags |= LIBUNA_BASE16_VARIANT_ENCODING_UTF16_BIG_ENDIAN;
			}
			else if( _BYTE_STREAM_HOST_IS_ENDIAN_LITTLE )
			{
				format_flags |= LIBUNA_BASE16_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN;
			}
			result = libuna_base16_stream_with_index_copy_from_byte_stream(
			          (uint8_t *) utf16_string,
			          utf16_string_size * 2,
			          &base16_stream_index,
			          data_segment->data,
			          data_segment->data_size,
			          format_flags,
			          error );

			if( result == 1 )
			{
				*utf16_string_index = ( base16_stream_index / 2 ) + 1;
			}
			break;

		case LIBFWEVT_VALUE_TYPE_GUID:
			result = libfguid_identifier_copy_to_utf16_string_with_index(
			          data_segment->guid,
			          utf16_string,
			          utf16_string_size,
			          utf16_string_index,
			          LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE | LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_FILETIME:
			result = libfdatetime_filetime_copy_to_utf16_string_with_index(
			          data_segment->filetime,
			          utf16_string,
			          utf16_string_size,
			          utf16_string_index,
			          LIBFDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS | LIBFDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_SYSTEMTIME:
			result = libfdatetime_systemtime_copy_to_utf16_string_with_index(
			          data_segment->systemtime,
			          utf16_string,
			          utf16_string_size,
			          utf16_string_index,
			          LIBFDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS | LIBFDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_NT_SECURITY_IDENTIFIER:
			result = libfwnt_security_identifier_copy_to_utf16_string_with_index(
			          data_segment->security_identifier,
			          utf16_string,
			          utf16_string_size,
			          utf16_string_index,
				  0,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_HEXADECIMAL_INTEGER_32BIT:
			result = libfwevt_integer_as_hexadecimal_copy_to_utf16_string_with_index(
			          data_segment->value_64bit,
			          32,
			          utf16_string,
			          utf16_string_size,
			          utf16_string_index,
			          error );
			break;

		case LIBFWEVT_VALUE_TYPE_HEXADECIMAL_INTEGER_64BIT:
			result = libfwevt_integer_as_hexadecimal_copy_to_utf16_string_with_index(
			          data_segment->value_64bit,
			          64,
			          utf16_string,
			          utf16_string_size,
			          utf16_string_index,
			          error );
			break;

		default:
			break;
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy data segment: %d to UTF-16 string.",
		 function,
		 data_segment_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the value data formatted as an UTF-16 string
 * The string size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_internal_xml_value_get_data_as_utf16_string_size(
     libfwevt_internal_xml_value_t *internal_xml_value,
     size_t *utf16_string_size,
     uint8_t escape_characters,
     libcerror_error_t **error )
{
	libfwevt_data_segment_t *data_segment = NULL;
	static char *function                 = "libfwevt_internal_xml_value_get_data_as_utf16_string_size";
	size_t data_segment_size              = 0;
	size_t safe_utf16_string_size         = 0;
	int data_segment_index                = 0;
	int number_of_data_segments           = 0;

	if( internal_xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_xml_value->data_segments,
	     &number_of_data_segments,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of data segments.",
		 function );

		return( -1 );
	}
	for( data_segment_index = 0;
	     data_segment_index < number_of_data_segments;
	     data_segment_index++ )
	{
		if( libfwevt_internal_xml_value_get_data_segment_with_cached_value(
		     internal_xml_value,
		     data_segment_index,
		     &data_segment,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data segment: %d.",
			 function,
			 data_segment_index );

			return( -1 );
		}
		if( libfwevt_internal_xml_value_get_data_segment_as_utf16_string_size(
		     internal_xml_value,
		     data_segment_index,
		     data_segment,
		     &data_segment_size,
		     escape_characters,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-16 string size of element data segment: %d.",
			 function,
			 data_segment_index );

			return( -1 );
		}
		if( data_segment_size > 1 )
		{
			safe_utf16_string_size += data_segment_size - 1;
		}
	}
	if( ( number_of_data_segments == 1 )
	 && ( data_segment != NULL )
	 && ( safe_utf16_string_size == 1 ) )
	{
		if( ( data_segment->data_size >= 2 )
		 && ( data_segment->data[ 0 ] == '\n' )
		 && ( data_segment->data[ 1 ] == 0 ) )
		{
			/* The value data consists of a single linefeed consider it empty
			 */
			safe_utf16_string_size = 0;
		}
	}
	if( safe_utf16_string_size > 0 )
	{
		safe_utf16_string_size++;
	}
	*utf16_string_size = safe_utf16_string_size;

	return( 1 );
}

/* Retrieves the data formatted as an UTF-16 string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_internal_xml_value_get_data_as_utf16_string_with_index(
     libfwevt_internal_xml_value_t *internal_xml_value,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     uint8_t escape_characters,
     libcerror_error_t **error )
{
	libfwevt_data_segment_t *data_segment = NULL;
	static char *function                 = "libfwevt_internal_xml_value_get_data_as_utf16_string_with_index";
	size_t safe_utf16_string_index        = 0;
	int data_segment_index                = 0;
	int number_of_data_segments           = 0;

	if( internal_xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string index.",
		 function );

		return( -1 );
	}
	safe_utf16_string_index = *utf16_string_index;

	if( libcdata_array_get_number_of_entries(
	     internal_xml_value->data_segments,
	     &number_of_data_segments,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of data segments.",
		 function );

		return( -1 );
	}
	for( data_segment_index = 0;
	     data_segment_index < number_of_data_segments;
	     data_segment_index++ )
	{
		if( libfwevt_internal_xml_value_get_data_segment_with_cached_value(
		     internal_xml_value,
		     data_segment_index,
		     &data_segment,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data segment: %d.",
			 function,
			 data_segment_index );

			return( -1 );
		}
		if( libfwevt_internal_xml_value_get_data_segment_as_utf16_string(
		     internal_xml_value,
		     data_segment_index,
		     data_segment,
		     utf16_string,
		     utf16_string_size,
		     &safe_utf16_string_index,
		     escape_characters,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy data segment: %d to UTF-16 string.",
			 function,
			 data_segment_index );

			return( -1 );
		}
		safe_utf16_string_index--;
	}
	if( ( number_of_data_segments == 1 )
	 && ( data_segment != NULL )
	 && ( safe_utf16_string_index == 1 ) )
	{
		if( ( data_segment->data_size >= 2 )
		 && ( data_segment->data[ 0 ] == '\n' )
		 && ( data_segment->data[ 1 ] == 0 ) )
		{
			/* The value data consists of a single linefeed consider it empty
			 */
			safe_utf16_string_index = 0;
		}
	}
	if( safe_utf16_string_index > 0 )
	{
		if( safe_utf16_string_index >= utf16_string_size  )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: invalid UTF-16 string size value too small.",
			 function );

			return( -1 );
		}
		utf16_string[ safe_utf16_string_index++ ] = 0;
	}
	*utf16_string_index = safe_utf16_string_index;

	return( 1 );
}

/* Retrieves the size of an UTF-16 encoded string of the value data
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_get_utf16_string_size(
     libfwevt_xml_value_t *xml_value,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_get_utf16_string_size";

	if( xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	internal_xml_value = (libfwevt_internal_xml_value_t *) xml_value;

	if( libfwevt_internal_xml_value_get_data_as_utf16_string_size(
	     internal_xml_value,
	     utf16_string_size,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size of UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies the value data to an UTF-16 encoded string
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_copy_to_utf16_string(
     libfwevt_xml_value_t *xml_value,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libfwevt_xml_value_copy_to_utf16_string";

	if( libfwevt_xml_value_get_data_as_utf16_string(
	     xml_value,
	     utf16_string,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size of UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the value data formatted as an UTF-16 string
 * The string size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_get_data_as_utf16_string_size(
     libfwevt_xml_value_t *xml_value,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_get_data_as_utf16_string_size";

	if( xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	internal_xml_value = (libfwevt_internal_xml_value_t *) xml_value;

	if( libfwevt_internal_xml_value_get_data_as_utf16_string_size(
	     internal_xml_value,
	     utf16_string_size,
	     0,
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

/* Retrieves the data formatted as an UTF-16 string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_get_data_as_utf16_string(
     libfwevt_xml_value_t *xml_value,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_get_data_as_utf16_string";
	size_t utf16_string_index                         = 0;

	if( xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	internal_xml_value = (libfwevt_internal_xml_value_t *) xml_value;

	if( libfwevt_internal_xml_value_get_data_as_utf16_string_with_index(
	     internal_xml_value,
	     utf16_string,
	     utf16_string_size,
	     &utf16_string_index,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size of UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

#if defined( HAVE_DEBUG_OUTPUT )

/* Prints the value
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_debug_print(
     libfwevt_xml_value_t *xml_value,
     uint8_t escape_characters,
     libcerror_error_t **error )
{
	system_character_t *value_string                  = NULL;
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_debug_print";
	size_t value_string_index                         = 0;
	size_t value_string_size                          = 0;
	int result                                        = 0;

	if( xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	internal_xml_value = (libfwevt_internal_xml_value_t *) xml_value;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfwevt_internal_xml_value_get_data_as_utf16_string_size(
		  internal_xml_value,
		  &value_string_size,
		  escape_characters,
		  error );
#else
	result = libfwevt_internal_xml_value_get_data_as_utf8_string_size(
		  internal_xml_value,
		  &value_string_size,
		  escape_characters,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of value string.",
		 function );

		goto on_error;
	}
	if( value_string_size > 0 )
	{
		if( value_string_size > (size_t) ( SSIZE_MAX / sizeof( system_character_t ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid name string size value exceeds maximum.",
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
			 "%s: unable to create value string.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfwevt_internal_xml_value_get_data_as_utf16_string_with_index(
			  internal_xml_value,
			  (libuna_utf16_character_t *) value_string,
			  value_string_size,
			  &value_string_index,
			  escape_characters,
			  error );
#else
		result = libfwevt_internal_xml_value_get_data_as_utf8_string_with_index(
			  internal_xml_value,
			  (libuna_utf8_character_t *) value_string,
			  value_string_size,
			  &value_string_index,
			  escape_characters,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%" PRIs_SYSTEM "",
		 value_string );

		memory_free(
		 value_string );
	}
	return( 1 );

on_error:
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

/* Prints the value of a specific data segment
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_debug_print_data_segment(
     libfwevt_xml_value_t *xml_value,
     int data_segment_index,
     uint8_t escape_characters,
     libcerror_error_t **error )
{
	libfwevt_data_segment_t *data_segment             = NULL;
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	system_character_t *value_string                  = NULL;
	static char *function                             = "libfwevt_xml_value_debug_print_data_segment";
	size_t value_string_index                         = 0;
	size_t value_string_size                          = 0;
	int result                                        = 0;

	if( xml_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML value.",
		 function );

		return( -1 );
	}
	internal_xml_value = (libfwevt_internal_xml_value_t *) xml_value;

	if( libfwevt_internal_xml_value_get_data_segment_with_cached_value(
	     internal_xml_value,
	     data_segment_index,
	     &data_segment,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data segment: %d.",
		 function,
		 data_segment_index );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfwevt_internal_xml_value_get_data_segment_as_utf16_string_size(
		  internal_xml_value,
		  data_segment_index,
	          data_segment,
		  &value_string_size,
		  escape_characters,
		  error );
#else
	result = libfwevt_internal_xml_value_get_data_segment_as_utf8_string_size(
		  internal_xml_value,
		  data_segment_index,
	          data_segment,
		  &value_string_size,
		  escape_characters,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of value string of data segment: %d.",
		 function,
		 data_segment_index );

		goto on_error;
	}
	if( value_string_size > 0 )
	{
		if( value_string_size > (size_t) ( SSIZE_MAX / sizeof( system_character_t ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid name string size value exceeds maximum.",
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
			 "%s: unable to create value string.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfwevt_internal_xml_value_get_data_segment_as_utf16_string(
			  internal_xml_value,
			  data_segment_index,
		          data_segment,
			  (libuna_utf16_character_t *) value_string,
			  value_string_size,
			  &value_string_index,
		          escape_characters,
			  error );
#else
		result = libfwevt_internal_xml_value_get_data_segment_as_utf8_string(
			  internal_xml_value,
			  data_segment_index,
		          data_segment,
			  (libuna_utf8_character_t *) value_string,
			  value_string_size,
			  &value_string_index,
		          escape_characters,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value string of data segment: %d.",
			 function,
			 data_segment_index );

			goto on_error;
		}
		libcnotify_printf(
		 "%" PRIs_SYSTEM "",
		 value_string );

		memory_free(
		 value_string );
	}
	return( 1 );

on_error:
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

