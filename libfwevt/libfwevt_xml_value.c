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
#include <memory.h>
#include <types.h>

#include "libfwevt_libcerror.h"
#include "libfwevt_libfvalue.h"
#include "libfwevt_types.h"
#include "libfwevt_xml_value.h"

/* Creates a XML value
 * Make sure the value xml_value is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_initialize(
     libfwevt_xml_value_t **xml_value,
     int type,
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
	if( libfvalue_value_type_initialize(
	     &( internal_xml_value->value ),
	     type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create value.",
		 function );

		goto on_error;
	}
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
		if( libfvalue_value_free(
		     &( ( *internal_xml_value )->value ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free value.",
			 function );

			result = -1;
		}
		memory_free(
		 *internal_xml_value );

		*internal_xml_value = NULL;
	}
	return( result );
}

/* Sets the data
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_set_data(
     libfwevt_xml_value_t *xml_value,
     const uint8_t *data,
     size_t data_size,
     int encoding,
     uint8_t flags,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function = "libfwevt_xml_value_get_type";

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

	if( libfvalue_value_set_data(
	     internal_xml_value->value,
	     data,
	     data_size,
	     encoding,
	     flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set value data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Sets the format flags
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_set_format_flags(
     libfwevt_xml_value_t *xml_value,
     uint32_t format_flags,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_set_format_flags";

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

	if( libfvalue_value_set_format_flags(
	     internal_xml_value->value,
	     format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set value format flags.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Appends data
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_append_data(
     libfwevt_xml_value_t *xml_value,
     int *value_entry_index,
     const uint8_t *data,
     size_t data_size,
     int encoding,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_append_data";

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

	if( libfvalue_value_append_entry_data(
	     internal_xml_value->value,
	     value_entry_index,
	     data,
	     data_size,
	     encoding,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append value data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Sets the data of a variable sized string
 * This function will look for a end-of-string character as the indicator
 * of the end of the string upto data size
 * Returns data size of the string if successful or -1 on error
 */
ssize_t libfwevt_xml_value_type_set_data_string(
         libfwevt_xml_value_t *xml_value,
         const uint8_t *data,
         size_t data_size,
         int encoding,
         uint8_t flags,
         libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_type_set_data_string";
	ssize_t read_count                                = 0;

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

	read_count = libfvalue_value_type_set_data_string(
	              internal_xml_value->value,
		      data,
		      data_size,
		      encoding,
		      flags,
		      error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set value data.",
		 function );

		return( -1 );
	}
	return( read_count );
}

/* Retrieves the value type
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_get_type(
     libfwevt_xml_value_t *xml_value,
     int *value_type,
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

	if( libfvalue_value_get_type(
	     internal_xml_value->value,
	     value_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value type.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the number of values entries
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_value_get_number_of_value_entries(
     libfwevt_xml_value_t *xml_value,
     int *number_of_value_entries,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_get_number_of_value_entries";

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

	if( libfvalue_value_get_number_of_value_entries(
	     internal_xml_value->value,
	     number_of_value_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element value number of value entries.",
		 function );

		return( -1 );
	}
	return( 1 );
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

	if( libfvalue_value_get_data_size(
	     internal_xml_value->value,
	     data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value data size.",
		 function );

		return( -1 );
	}
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
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_copy_data";

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

	if( libfvalue_value_copy_data(
	     internal_xml_value->value,
	     data,
	     data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to value data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies the value data to a 8-bit integer
 * Returns 1 if successful, 0 if size value not be retrieved or -1 on error
 */
int libfwevt_xml_value_copy_to_8bit(
     libfwevt_xml_value_t *xml_value,
     uint8_t *value_8bit,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_copy_to_8bit";
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

	result = libfvalue_value_copy_to_8bit(
	          internal_xml_value->value,
	          0,
	          value_8bit,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value to 8-bit integer.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Copies the value data to a 32-bit integer
 * Returns 1 if successful, 0 if size value not be retrieved or -1 on error
 */
int libfwevt_xml_value_copy_to_32bit(
     libfwevt_xml_value_t *xml_value,
     uint32_t *value_32bit,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_copy_to_32bit";
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

	result = libfvalue_value_copy_to_32bit(
	          internal_xml_value->value,
	          0,
	          value_32bit,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value to 32-bit integer.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Copies the value data to a 64-bit integer
 * Returns 1 if successful, 0 if size value not be retrieved or -1 on error
 */
int libfwevt_xml_value_copy_to_64bit(
     libfwevt_xml_value_t *xml_value,
     uint64_t *value_64bit,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_copy_to_64bit";
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

	result = libfvalue_value_copy_to_64bit(
	          internal_xml_value->value,
	          0,
	          value_64bit,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value to 64-bit integer.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Retrieves the size of an UTF-8 encoded string of the value data
 * Returns 1 if successful, 0 if value could not be retrieved or -1 on error
 */
int libfwevt_xml_value_get_utf8_string_size_with_index(
     libfwevt_xml_value_t *xml_value,
     int value_entry_index,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_get_utf8_string_size_with_index";
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

	result = libfvalue_value_get_utf8_string_size(
	          internal_xml_value->value,
	          value_entry_index,
	          utf8_string_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to determine size UTF-8 string of value: %d.",
		 function,
		 value_entry_index );

		return( -1 );
	}
	return( result );
}

/* Copies the value data to an UTF-8 encoded string
 * Returns 1 if successful, 0 if value could not be retrieved or -1 on error
 */
int libfwevt_xml_value_copy_to_utf8_string_with_index(
     libfwevt_xml_value_t *xml_value,
     int value_entry_index,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_copy_to_utf8_string_with_index";
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

	result = libfvalue_value_copy_to_utf8_string_with_index(
	          internal_xml_value->value,
	          value_entry_index,
	          utf8_string,
	          utf8_string_size,
	          utf8_string_index,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value to UTF-8 string.",
		 function );

		return( -1 );
	}
	return( result );
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

	result = libfvalue_value_get_utf8_string_size(
	          internal_xml_value->value,
	          0,
	          utf8_string_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to determine size UTF-8 string.",
		 function );

		return( -1 );
	}
	else if( result == 0 )
	{
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
		*utf8_string_size = 0;
	}
	return( 1 );
}

/* Copies the value data to an UTF-8 encoded string
 * Returns 1 if successful, 0 if value could not be retrieved or -1 on error
 */
int libfwevt_xml_value_copy_to_utf8_string(
     libfwevt_xml_value_t *xml_value,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_copy_to_utf8_string";
	size_t utf8_string_index                          = 0;
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

	result = libfvalue_value_copy_to_utf8_string_with_index(
	          internal_xml_value->value,
	          0,
	          utf8_string,
	          utf8_string_size,
	          &utf8_string_index,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value: %d to UTF-8 string.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Retrieves the size of an UTF-16 encoded string of the value data
 * Returns 1 if successful, 0 if value could not be retrieved or -1 on error
 */
int libfwevt_xml_value_get_utf16_string_size_with_index(
     libfwevt_xml_value_t *xml_value,
     int value_entry_index,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_get_utf16_string_size_with_index";
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

	result = libfvalue_value_get_utf16_string_size(
	          internal_xml_value->value,
	          value_entry_index,
	          utf16_string_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to determine size UTF-16 string of value: %d.",
		 function,
		 value_entry_index );

		return( -1 );
	}
	return( result );
}

/* Copies the value data to an UTF-16 encoded string
 * Returns 1 if successful, 0 if value could not be retrieved or -1 on error
 */
int libfwevt_xml_value_copy_to_utf16_string_with_index(
     libfwevt_xml_value_t *xml_value,
     int value_entry_index,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_copy_to_utf16_string_with_index";
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

	result = libfvalue_value_copy_to_utf16_string_with_index(
	          internal_xml_value->value,
	          value_entry_index,
	          utf16_string,
	          utf16_string_size,
	          utf16_string_index,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value: %d to UTF-16 string.",
		 function,
		 value_entry_index );

		return( -1 );
	}
	return( result );
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

	result = libfvalue_value_get_utf16_string_size(
	          internal_xml_value->value,
	          0,
	          utf16_string_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to determine size UTF-16 string.",
		 function );

		return( -1 );
	}
	else if( result == 0 )
	{
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
		*utf16_string_size = 0;
	}
	return( 1 );
}

/* Copies the value data to an UTF-16 encoded string
 * Returns 1 if successful, 0 if value could not be retrieved or -1 on error
 */
int libfwevt_xml_value_copy_to_utf16_string(
     libfwevt_xml_value_t *xml_value,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_xml_value_copy_to_utf16_string";
	size_t utf16_string_index                         = 0;
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

	result = libfvalue_value_copy_to_utf16_string_with_index(
	          internal_xml_value->value,
	          0,
	          utf16_string,
	          utf16_string_size,
	          &utf16_string_index,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( result );
}

#if defined( HAVE_DEBUG_OUTPUT )

/* Prints the XML value
 * Returns 1 if successful or -1 on error
 */
int libfwevt_debug_print_xml_value(
     libfwevt_xml_value_t *xml_value,
     int value_entry_index,
     uint8_t flags,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_value_t *internal_xml_value = NULL;
	static char *function                             = "libfwevt_debug_print_xml_value";

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

	if( libfvalue_value_print(
	     internal_xml_value->value,
	     value_entry_index,
	     flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

