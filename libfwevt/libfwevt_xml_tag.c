/*
 * XML tag functions
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_WCTYPE_H )
#include <wctype.h>
#endif

#include "libfwevt_debug.h"
#include "libfwevt_definitions.h"
#include "libfwevt_libcdata.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_libcnotify.h"
#include "libfwevt_libuna.h"
#include "libfwevt_types.h"
#include "libfwevt_xml_tag.h"
#include "libfwevt_xml_value.h"

/* Creates a XML tag
 * Make sure the value xml_tag is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_initialize(
     libfwevt_xml_tag_t **xml_tag,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_initialize";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	if( *xml_tag != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid XML tag value already set.",
		 function );

		return( -1 );
	}
	internal_xml_tag = memory_allocate_structure(
	                    libfwevt_internal_xml_tag_t );

	if( internal_xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create XML tag.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_xml_tag,
	     0,
	     sizeof( libfwevt_internal_xml_tag_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear XML tag.",
		 function );

		memory_free(
		 internal_xml_tag );

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( internal_xml_tag->attributes_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create attributes array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_xml_tag->elements_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create elements array.",
		 function );

		goto on_error;
	}
	*xml_tag = (libfwevt_xml_tag_t *) internal_xml_tag;

	return( 1 );

on_error:
	if( internal_xml_tag != NULL )
	{
		if( internal_xml_tag->attributes_array != NULL )
		{
			libcdata_array_free(
			 &( internal_xml_tag->attributes_array ),
			 NULL,
			 NULL );
		}
		memory_free(
		 internal_xml_tag );
	}
	return( -1 );
}

/* Frees a XML tag
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_free(
     libfwevt_xml_tag_t **xml_tag,
     libcerror_error_t **error )
{
	static char *function = "libfwevt_xml_tag_free";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	if( *xml_tag != NULL )
	{
		*xml_tag = NULL;
	}
	return( 1 );
}

/* Frees a XML tag
 * Returns 1 if successful or -1 on error
 */
int libfwevt_internal_xml_tag_free(
     libfwevt_internal_xml_tag_t **internal_xml_tag,
     libcerror_error_t **error )
{
	static char *function = "libfwevt_internal_xml_tag_free";
	int result            = 1;

	if( internal_xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	if( *internal_xml_tag != NULL )
	{
		if( libcdata_array_free(
		     &( ( *internal_xml_tag )->elements_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_xml_tag_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free elements array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( ( *internal_xml_tag )->attributes_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_xml_tag_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free attributes array.",
			 function );

			result = -1;
		}
		if( ( *internal_xml_tag )->value != NULL )
		{
			if( libfwevt_internal_xml_value_free(
			     (libfwevt_internal_xml_value_t **) &( ( *internal_xml_tag )->value ),
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
		}
		if( ( *internal_xml_tag )->name != NULL )
		{
			memory_free(
			 ( *internal_xml_tag )->name );
		}
		memory_free(
		 *internal_xml_tag );

		*internal_xml_tag = NULL;
	}
	return( result );
}

/* Appends an attribute
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_append_attribute(
     libfwevt_xml_tag_t *xml_tag,
     libfwevt_xml_tag_t *attribute_xml_tag,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_append_attribute";
	int entry_index                               = 0;

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	if( libcdata_array_append_entry(
	     internal_xml_tag->attributes_array,
	     &entry_index,
	     (intptr_t *) attribute_xml_tag,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append attribute XML tag to array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Sets the type
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_set_type(
     libfwevt_xml_tag_t *xml_tag,
     uint8_t type,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_set_type";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	internal_xml_tag->type = type;

	return( 1 );
}

/* Sets UTF-16 little-endian encoded name data
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_set_name_data(
     libfwevt_xml_tag_t *xml_tag,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_set_name_data";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	if( internal_xml_tag->name != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid XML tag - name value already set.",
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
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_size > 0 )
	{
		internal_xml_tag->name = (uint8_t *) memory_allocate(
		                                      sizeof( uint8_t ) * data_size );

		if( internal_xml_tag->name == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create name.",
			 function );

			goto on_error;
		}
		internal_xml_tag->name_size = data_size;

		if( memory_copy(
		     internal_xml_tag->name,
		     data,
		     data_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy name.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( internal_xml_tag->name != NULL )
	{
		memory_free(
		 internal_xml_tag->name );

		internal_xml_tag->name = NULL;
	}
	internal_xml_tag->name_size = 0;

	return( -1 );
}

/* Sets the value type
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_set_value_type(
     libfwevt_xml_tag_t *xml_tag,
     int value_type,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_set_value_type";
	int current_value_type                        = 0;

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	if( internal_xml_tag->value == NULL )
	{
		if( libfwevt_xml_value_initialize(
		     &( internal_xml_tag->value ),
		     value_type,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create value.",
			 function );

			return( -1 );
		}
	}
	else
	{
		if( libfwevt_xml_value_get_type(
		     internal_xml_tag->value,
		     &current_value_type,
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
		if( value_type != current_value_type )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid value type value mismatch.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Sets the value format flags
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_set_value_format_flags(
     libfwevt_xml_tag_t *xml_tag,
     uint32_t format_flags,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_set_value_format_flags";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	if( libfwevt_xml_value_set_format_flags(
	     internal_xml_tag->value,
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

/* Sets the value data
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_set_value_data(
     libfwevt_xml_tag_t *xml_tag,
     const uint8_t *data,
     size_t data_size,
     int encoding,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_set_value_data";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	if( libfwevt_xml_value_set_data(
	     internal_xml_tag->value,
	     data,
	     data_size,
	     encoding,
	     LIBFVALUE_VALUE_DATA_FLAG_NON_MANAGED,
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

/* Appends the value data
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_append_value_data(
     libfwevt_xml_tag_t *xml_tag,
     const uint8_t *data,
     size_t data_size,
     int encoding,
     int *value_entry_index,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_append_value_data";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	if( libfwevt_xml_value_append_data(
	     internal_xml_tag->value,
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

/* Sets the value strings array
 * Returns the number of bytes read if successful or -1 on error
 */
ssize_t libfwevt_xml_tag_set_value_strings_array(
         libfwevt_xml_tag_t *xml_tag,
         const uint8_t *strings_array_data,
         size_t strings_array_data_size,
         int encoding,
         libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_set_value_strings_array";
	ssize_t read_count                            = 0;

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	read_count = libfwevt_xml_value_type_set_data_string(
		      internal_xml_tag->value,
		      strings_array_data,
		      strings_array_data_size,
		      encoding,
		      LIBFVALUE_VALUE_DATA_FLAG_NON_MANAGED,
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

/* Appends an element
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_append_element(
     libfwevt_xml_tag_t *xml_tag,
     libfwevt_xml_tag_t *element_xml_tag,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_append_element";
	int entry_index                               = 0;

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	if( libcdata_array_append_entry(
	     internal_xml_tag->elements_array,
	     &entry_index,
	     (intptr_t *) element_xml_tag,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append element XML tag to array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-8 formatted name
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_utf8_name_size(
     libfwevt_xml_tag_t *xml_tag,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_get_utf8_name_size";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	if( libuna_utf8_string_size_from_utf16_stream(
	     internal_xml_tag->name,
	     internal_xml_tag->name_size,
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
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_utf8_name(
     libfwevt_xml_tag_t *xml_tag,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_get_utf8_name";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	if( libuna_utf8_string_copy_from_utf16_stream(
	     utf8_string,
	     utf8_string_size,
	     internal_xml_tag->name,
	     internal_xml_tag->name_size,
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
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_utf16_name_size(
     libfwevt_xml_tag_t *xml_tag,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_get_utf16_name_size";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	if( libuna_utf16_string_size_from_utf16_stream(
	     internal_xml_tag->name,
	     internal_xml_tag->name_size,
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
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_utf16_name(
     libfwevt_xml_tag_t *xml_tag,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_get_utf16_name";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	if( libuna_utf16_string_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     internal_xml_tag->name,
	     internal_xml_tag->name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the value
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_value(
     libfwevt_xml_tag_t *xml_tag,
     libfwevt_xml_value_t **xml_value,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_get_value";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

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
	*xml_value = internal_xml_tag->value;

	return( 1 );
}

/* Retrieves the size of the UTF-8 formatted value
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_utf8_value_size(
     libfwevt_xml_tag_t *xml_tag,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_get_utf8_value_size";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	if( libfwevt_xml_value_get_utf8_string_size(
	     internal_xml_tag->value,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size of UTF-8 string of value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 formatted value
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_utf8_value(
     libfwevt_xml_tag_t *xml_tag,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_get_utf8_value";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	if( libfwevt_xml_value_copy_to_utf8_string(
	     internal_xml_tag->value,
	     utf8_string,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to copy value to UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 formatted value
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_utf16_value_size(
     libfwevt_xml_tag_t *xml_tag,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_get_utf16_value_size";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	if( libfwevt_xml_value_get_utf16_string_size(
	     internal_xml_tag->value,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size of UTF-16 string of value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 formatted value
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_utf16_value(
     libfwevt_xml_tag_t *xml_tag,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_get_utf16_value";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	if( libfwevt_xml_value_copy_to_utf16_string(
	     internal_xml_tag->value,
	     utf16_string,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to copy value to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the number of attributes
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_number_of_attributes(
     libfwevt_xml_tag_t *xml_tag,
     int *number_of_attributes,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_get_number_of_attributes";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	if( libcdata_array_get_number_of_entries(
	     internal_xml_tag->attributes_array,
	     number_of_attributes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of attributes.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific attribute
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_attribute_by_index(
     libfwevt_xml_tag_t *xml_tag,
     int attribute_index,
     libfwevt_xml_tag_t **attribute_xml_tag,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_get_attribute_by_index";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	if( libcdata_array_get_entry_by_index(
	     internal_xml_tag->attributes_array,
	     attribute_index,
	     (intptr_t **) attribute_xml_tag,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve attribute: %d.",
		 function,
		 attribute_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the attribute for the specific UTF-8 encoded name
 * Returns 1 if successful, 0 if no such value or -1 on error
 */
int libfwevt_xml_tag_get_attribute_by_utf8_name(
     libfwevt_xml_tag_t *xml_tag,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfwevt_xml_tag_t **attribute_xml_tag,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_attribute_xml_tag = NULL;
	libfwevt_internal_xml_tag_t *internal_xml_tag           = NULL;
	uint8_t *value_entry_data                               = NULL;
	static char *function                                   = "libfwevt_xml_tag_get_attribute_by_utf8_name";
	libuna_unicode_character_t name_character               = 0;
	libuna_unicode_character_t string_character             = 0;
	size_t name_index                                       = 0;
	size_t utf8_string_index                                = 0;
	size_t value_entry_data_size                            = 0;
	int attribute_index                                     = 0;
	int number_of_attributes                                = 0;

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

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
	if( utf8_string_length > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( attribute_xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid attribute XML tag.",
		 function );

		return( -1 );
	}
	if( *attribute_xml_tag != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: attribute XML tag already set.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_xml_tag->attributes_array,
	     &number_of_attributes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of attributes.",
		 function );

		return( -1 );
	}
	if( number_of_attributes == 0 )
	{
		return( 0 );
	}
	for( attribute_index = 0;
	     attribute_index < number_of_attributes;
	     attribute_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_xml_tag->attributes_array,
		     attribute_index,
		     (intptr_t **) &internal_attribute_xml_tag,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve attribute: %d.",
			 function,
			 attribute_index );

			return( -1 );
		}
		if( internal_attribute_xml_tag == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing attribute: %d.",
			 function,
			 attribute_index );

			return( -1 );
		}
/* TODO bounds check and clean up */
		value_entry_data      = internal_attribute_xml_tag->name;
		value_entry_data_size = internal_attribute_xml_tag->name_size;

		if( ( value_entry_data[ value_entry_data_size - 2 ] == 0 )
		 && ( value_entry_data[ value_entry_data_size - 1 ] == 0 ) )
		{
			value_entry_data_size -= 2;
		}
		name_index        = 0;
		utf8_string_index = 0;

/* TODO compare hash */
		while( name_index < value_entry_data_size )
		{
			if( utf8_string_index >= utf8_string_length )
			{
				break;
			}
			if( libuna_unicode_character_copy_from_utf16_stream(
			     &name_character,
			     value_entry_data,
			     value_entry_data_size,
			     &name_index,
			     LIBUNA_ENDIAN_LITTLE,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy key name to Unicode character.",
				 function );

				return( -1 );
			}
			if( libuna_unicode_character_copy_from_utf8(
			     &string_character,
			     utf8_string,
			     utf8_string_length,
			     &utf8_string_index,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy UTF-8 string to Unicode character.",
				 function );

				return( -1 );
			}
			if( towupper( (wint_t) name_character ) != towupper( (wint_t) string_character ) )
			{
				break;
			}
		}
		if( ( name_index == value_entry_data_size )
		 && ( utf8_string_index == utf8_string_length ) )
		{
			*attribute_xml_tag = (libfwevt_xml_tag_t *) internal_attribute_xml_tag;

			return( 1 );
		}
	}
	return( 0 );
}

/* Retrieves the attribute for the specific UTF-16 encoded name
 * Returns 1 if successful, 0 if no such value or -1 on error
 */
int libfwevt_xml_tag_get_attribute_by_utf16_name(
     libfwevt_xml_tag_t *xml_tag,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfwevt_xml_tag_t **attribute_xml_tag,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_attribute_xml_tag = NULL;
	libfwevt_internal_xml_tag_t *internal_xml_tag           = NULL;
	uint8_t *value_entry_data                               = NULL;
	static char *function                                   = "libfwevt_xml_tag_get_attribute_by_utf16_name";
	libuna_unicode_character_t name_character               = 0;
	libuna_unicode_character_t string_character             = 0;
	size_t name_index                                       = 0;
	size_t utf16_string_index                               = 0;
	size_t value_entry_data_size                            = 0;
	int attribute_index                                     = 0;
	int number_of_attributes                                = 0;

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

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
	if( utf16_string_length > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( attribute_xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid attribute XML tag.",
		 function );

		return( -1 );
	}
	if( *attribute_xml_tag != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: attribute XML tag already set.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_xml_tag->attributes_array,
	     &number_of_attributes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of attributes.",
		 function );

		return( -1 );
	}
	if( number_of_attributes == 0 )
	{
		return( 0 );
	}
	for( attribute_index = 0;
	     attribute_index < number_of_attributes;
	     attribute_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_xml_tag->attributes_array,
		     attribute_index,
		     (intptr_t **) &internal_attribute_xml_tag,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve attribute: %d.",
			 function,
			 attribute_index );

			return( -1 );
		}
		if( internal_attribute_xml_tag == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing attribute: %d.",
			 function,
			 attribute_index );

			return( -1 );
		}
/* TODO bounds check and clean up */
		value_entry_data      = internal_attribute_xml_tag->name;
		value_entry_data_size = internal_attribute_xml_tag->name_size;

		if( ( value_entry_data[ value_entry_data_size - 2 ] == 0 )
		 && ( value_entry_data[ value_entry_data_size - 1 ] == 0 ) )
		{
			value_entry_data_size -= 2;
		}
		name_index         = 0;
		utf16_string_index = 0;

/* TODO compare hash */
		while( name_index < value_entry_data_size )
		{
			if( utf16_string_index >= utf16_string_length )
			{
				break;
			}
			if( libuna_unicode_character_copy_from_utf16_stream(
			     &name_character,
			     value_entry_data,
			     value_entry_data_size,
			     &name_index,
			     LIBUNA_ENDIAN_LITTLE,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy key name to Unicode character.",
				 function );

				return( -1 );
			}
			if( libuna_unicode_character_copy_from_utf16(
			     &string_character,
			     utf16_string,
			     utf16_string_length,
			     &utf16_string_index,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy UTF-16 string to Unicode character.",
				 function );

				return( -1 );
			}
			if( towupper( (wint_t) name_character ) != towupper( (wint_t) string_character ) )
			{
				break;
			}
		}
		if( ( name_index == value_entry_data_size )
		 && ( utf16_string_index == utf16_string_length ) )
		{
			*attribute_xml_tag = (libfwevt_xml_tag_t *) internal_attribute_xml_tag;

			return( 1 );
		}
	}
	return( 0 );
}

/* Retrieves the number of elements
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_number_of_elements(
     libfwevt_xml_tag_t *xml_tag,
     int *number_of_elements,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_get_number_of_elements";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	if( libcdata_array_get_number_of_entries(
	     internal_xml_tag->elements_array,
	     number_of_elements,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific element
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_element_by_index(
     libfwevt_xml_tag_t *xml_tag,
     int element_index,
     libfwevt_xml_tag_t **element_xml_tag,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_get_element_by_index";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	if( libcdata_array_get_entry_by_index(
	     internal_xml_tag->elements_array,
	     element_index,
	     (intptr_t **) element_xml_tag,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element: %d.",
		 function,
		 element_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the element for the specific UTF-8 encoded name
 * Returns 1 if successful, 0 if no such value or -1 on error
 */
int libfwevt_xml_tag_get_element_by_utf8_name(
     libfwevt_xml_tag_t *xml_tag,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfwevt_xml_tag_t **element_xml_tag,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_element_xml_tag = NULL;
	libfwevt_internal_xml_tag_t *internal_xml_tag         = NULL;
	uint8_t *value_entry_data                             = NULL;
	static char *function                                 = "libfwevt_xml_tag_get_element_by_utf8_name";
	libuna_unicode_character_t name_character             = 0;
	libuna_unicode_character_t string_character           = 0;
	size_t name_index                                     = 0;
	size_t utf8_string_index                              = 0;
	size_t value_entry_data_size                          = 0;
	int element_index                                     = 0;
	int number_of_elements                                = 0;

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

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
	if( utf8_string_length > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( element_xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid element XML tag.",
		 function );

		return( -1 );
	}
	if( *element_xml_tag != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: element XML tag already set.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_xml_tag->elements_array,
	     &number_of_elements,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements.",
		 function );

		return( -1 );
	}
	if( number_of_elements == 0 )
	{
		return( 0 );
	}
	for( element_index = 0;
	     element_index < number_of_elements;
	     element_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_xml_tag->elements_array,
		     element_index,
		     (intptr_t **) &internal_element_xml_tag,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		if( internal_element_xml_tag == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
/* TODO bounds check and clean up */
		value_entry_data      = internal_element_xml_tag->name;
		value_entry_data_size = internal_element_xml_tag->name_size;

		if( ( value_entry_data[ value_entry_data_size - 2 ] == 0 )
		 && ( value_entry_data[ value_entry_data_size - 1 ] == 0 ) )
		{
			value_entry_data_size -= 2;
		}
		name_index        = 0;
		utf8_string_index = 0;

/* TODO compare hash */
		while( name_index < value_entry_data_size )
		{
			if( utf8_string_index >= utf8_string_length )
			{
				break;
			}
			if( libuna_unicode_character_copy_from_utf16_stream(
			     &name_character,
			     value_entry_data,
			     value_entry_data_size,
			     &name_index,
			     LIBUNA_ENDIAN_LITTLE,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy key name to Unicode character.",
				 function );

				return( -1 );
			}
			if( libuna_unicode_character_copy_from_utf8(
			     &string_character,
			     utf8_string,
			     utf8_string_length,
			     &utf8_string_index,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy UTF-8 string to Unicode character.",
				 function );

				return( -1 );
			}
			if( towupper( (wint_t) name_character ) != towupper( (wint_t) string_character ) )
			{
				break;
			}
		}
		if( ( name_index == value_entry_data_size )
		 && ( utf8_string_index == utf8_string_length ) )
		{
			*element_xml_tag = (libfwevt_xml_tag_t *) internal_element_xml_tag;

			return( 1 );
		}
	}
	return( 0 );
}

/* Retrieves the element for the specific UTF-16 encoded name
 * Returns 1 if successful, 0 if no such value or -1 on error
 */
int libfwevt_xml_tag_get_element_by_utf16_name(
     libfwevt_xml_tag_t *xml_tag,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfwevt_xml_tag_t **element_xml_tag,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_element_xml_tag = NULL;
	libfwevt_internal_xml_tag_t *internal_xml_tag         = NULL;
	uint8_t *value_entry_data                             = NULL;
	static char *function                                 = "libfwevt_xml_tag_get_element_by_utf16_name";
	libuna_unicode_character_t name_character             = 0;
	libuna_unicode_character_t string_character           = 0;
	size_t name_index                                     = 0;
	size_t utf16_string_index                             = 0;
	size_t value_entry_data_size                          = 0;
	int element_index                                     = 0;
	int number_of_elements                                = 0;

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

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
	if( utf16_string_length > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( element_xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid element XML tag.",
		 function );

		return( -1 );
	}
	if( *element_xml_tag != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: element XML tag already set.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_xml_tag->elements_array,
	     &number_of_elements,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements.",
		 function );

		return( -1 );
	}
	if( number_of_elements == 0 )
	{
		return( 0 );
	}
	for( element_index = 0;
	     element_index < number_of_elements;
	     element_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_xml_tag->elements_array,
		     element_index,
		     (intptr_t **) &internal_element_xml_tag,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		if( internal_element_xml_tag == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
/* TODO bounds check and clean up */
		value_entry_data      = internal_element_xml_tag->name;
		value_entry_data_size = internal_element_xml_tag->name_size;

		if( ( value_entry_data[ value_entry_data_size - 2 ] == 0 )
		 && ( value_entry_data[ value_entry_data_size - 1 ] == 0 ) )
		{
			value_entry_data_size -= 2;
		}
		name_index         = 0;
		utf16_string_index = 0;

/* TODO compare hash */
		while( name_index < value_entry_data_size )
		{
			if( utf16_string_index >= utf16_string_length )
			{
				break;
			}
			if( libuna_unicode_character_copy_from_utf16_stream(
			     &name_character,
			     value_entry_data,
			     value_entry_data_size,
			     &name_index,
			     LIBUNA_ENDIAN_LITTLE,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy key name to Unicode character.",
				 function );

				return( -1 );
			}
			if( libuna_unicode_character_copy_from_utf16(
			     &string_character,
			     utf16_string,
			     utf16_string_length,
			     &utf16_string_index,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy UTF-16 string to Unicode character.",
				 function );

				return( -1 );
			}
			if( towupper( (wint_t) name_character ) != towupper( (wint_t) string_character ) )
			{
				break;
			}
		}
		if( ( name_index == value_entry_data_size )
		 && ( utf16_string_index == utf16_string_length ) )
		{
			*element_xml_tag = (libfwevt_xml_tag_t *) internal_element_xml_tag;

			return( 1 );
		}
	}
	return( 0 );
}

/* Retrieves the flags
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_flags(
     libfwevt_xml_tag_t *xml_tag,
     uint8_t *flags,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_get_flags";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	if( flags == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid flags.",
		 function );

		return( -1 );
	}
	*flags = internal_xml_tag->flags;

	return( 1 );
}

/* Sets the flags
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_set_flags(
     libfwevt_xml_tag_t *xml_tag,
     uint8_t flags,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_set_flags";
	uint8_t supported_flags                       = 0;

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	supported_flags = LIBFWEVT_XML_TAG_FLAG_IS_TEMPLATE_DEFINITION;

	if( ( flags & ~( supported_flags ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags: 0x%02" PRIx8 ".",
		 function,
		 flags );

		return( -1 );
	}
	internal_xml_tag->flags = flags;

	return( 1 );
}

/* Retrieves the size of UTF-8 formatted string of the XML value
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_utf8_xml_value_string_size(
     libfwevt_internal_xml_tag_t *internal_xml_tag,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	uint8_t static_value_string[ 2 ];

	uint8_t *value_string        = NULL;
	static char *function        = "libfwevt_xml_tag_get_utf8_xml_value_string_size";
	size_t safe_utf8_string_size = 0;
	size_t value_string_index    = 0;
	size_t value_string_size     = 0;
	int number_of_value_entries  = 0;
	int result                   = 0;
	int value_entry_index        = 0;
	int value_type               = 0;

	if( internal_xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
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
	if( libfwevt_xml_value_get_type(
	     internal_xml_tag->value,
	     &value_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element value type.",
		 function );

		goto on_error;
	}
	if( libfwevt_xml_value_get_number_of_value_entries(
	     internal_xml_tag->value,
	     &number_of_value_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element value number of value entries.",
		 function );

		goto on_error;
	}
	for( value_entry_index = 0;
	     value_entry_index < number_of_value_entries;
	     value_entry_index++ )
	{
		result = libfwevt_xml_value_get_utf8_string_size_with_index(
			  internal_xml_tag->value,
			  value_entry_index,
			  &value_string_size,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-8 string size of element value entry: %d.",
			 function,
			 value_entry_index );

			goto on_error;
		}
		if( ( result == 0 )
		 && ( number_of_value_entries != 1 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing element value entry: %d.",
			 function,
			 value_entry_index );

			goto on_error;
		}
		if( result != 0 )
		{
			if( ( number_of_value_entries == 1 )
			 && ( value_string_size == 2 ) )
			{
				value_string_index = 0;

				if( libfwevt_xml_value_copy_to_utf8_string_with_index(
				     internal_xml_tag->value,
				     0,
				     static_value_string,
				     2,
				     &value_string_index,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy element value: 0 to UTF-8 string.",
					 function );

					goto on_error;
				}
				/* The value data consists of a single linefeed consider it empty
				 */
				if( static_value_string[ 0 ] == (uint8_t) '\n' )
				{
					value_string_size -= 1;
				}
			}
			else if( value_type == LIBFVALUE_VALUE_TYPE_STRING_UTF16 )
			{
				if( ( value_string_size == 0 )
				 || ( value_string_size > ( MEMORY_MAXIMUM_ALLOCATION_SIZE / sizeof( uint8_t ) ) ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: invalid value string size value out of bounds.",
					 function );

					goto on_error;
				}
				value_string = (uint8_t *) memory_allocate(
				                            sizeof( uint8_t ) * value_string_size );

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
				value_string_index = 0;

				if( libfwevt_xml_value_copy_to_utf8_string_with_index(
				     internal_xml_tag->value,
				     value_entry_index,
				     value_string,
				     value_string_size,
				     &value_string_index,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy element value: %d to UTF-8 string.",
					 function,
					 value_entry_index );

					goto on_error;
				}
				for( value_string_index = 0;
				     value_string_index < ( value_string_size - 1 );
				     value_string_index++ )
				{
					switch( value_string[ value_string_index ] )
					{
						/* Replace & by &amp; */
						case (uint8_t) '&':
							safe_utf8_string_size += 4;
							break;

						/* Replace < by &lt; and > by &gt; */
						case (uint8_t) '<':
						case (uint8_t) '>':
							safe_utf8_string_size += 3;
							break;

						/* Replace ' by &apos; and " by &quot; */
/* TODO disabled for now since Event Viewer does not uses it
						case (uint8_t) '\'':
						case (uint8_t) '"':
							safe_utf8_string_size += 5;
							break;
*/

						default:
							break;
					}
				}
				memory_free(
				 value_string );

				value_string = NULL;
			}
			if( value_string_size > 1 )
			{
				/* The size of:
				 *   value formatted as a string
				 */
				safe_utf8_string_size += value_string_size - 1;
			}
		}
	}
	if( safe_utf8_string_size != 0 )
	{
		/* The size of:
		 *   end-of-string character
		 */
		safe_utf8_string_size += 1;
	}
	*utf8_string_size = safe_utf8_string_size;

	return( 1 );

on_error:
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

/* Retrieves the UTF-8 formatted string of the XML value
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_utf8_xml_value_string_with_index(
     libfwevt_internal_xml_tag_t *internal_xml_tag,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     libcerror_error_t **error )
{
	uint8_t *value_string       = NULL;
	static char *function       = "libfwevt_xml_tag_get_utf8_xml_value_string_with_index";
	size_t string_index         = 0;
	size_t value_string_index   = 0;
	size_t value_string_size    = 0;
	int number_of_value_entries = 0;
	int result                  = 0;
	int value_entry_index       = 0;
	int value_type              = 0;

	if( internal_xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
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
	string_index = *utf8_string_index;

	if( libfwevt_xml_value_get_type(
	     internal_xml_tag->value,
	     &value_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element value type.",
		 function );

		goto on_error;
	}
	if( libfwevt_xml_value_get_number_of_value_entries(
	     internal_xml_tag->value,
	     &number_of_value_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element value number of value entries.",
		 function );

		goto on_error;
	}
	for( value_entry_index = 0;
	     value_entry_index < number_of_value_entries;
	     value_entry_index++ )
	{
		result = libfwevt_xml_value_get_utf8_string_size_with_index(
			  internal_xml_tag->value,
			  value_entry_index,
			  &value_string_size,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-8 string size of element value entry: %d.",
			 function,
			 value_entry_index );

			goto on_error;
		}
		if( ( result == 0 )
		 && ( number_of_value_entries != 1 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing element value entry: %d.",
			 function,
			 value_entry_index );

			goto on_error;
		}
		if( ( result != 0 )
		 && ( value_string_size > 1 ) )
		{
			if( value_type == LIBFVALUE_VALUE_TYPE_STRING_UTF16 )
			{
				if( ( value_string_size == 0 )
				 || ( value_string_size > ( MEMORY_MAXIMUM_ALLOCATION_SIZE / sizeof( uint8_t ) ) ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: invalid value string size value out of bounds.",
					 function );

					goto on_error;
				}
				value_string = (uint8_t *) memory_allocate(
				                            sizeof( uint8_t ) * value_string_size );

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
				value_string_index = 0;

				if( libfwevt_xml_value_copy_to_utf8_string_with_index(
				     internal_xml_tag->value,
				     value_entry_index,
				     value_string,
				     value_string_size,
				     &value_string_index,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy element value: %d to UTF-8 string.",
					 function,
					 value_entry_index );

					goto on_error;
				}
				for( value_string_index = 0;
				     value_string_index < ( value_string_size - 1 );
				     value_string_index++ )
				{
					switch( value_string[ value_string_index ] )
					{
						/* Replace & by &amp; */
						case (uint8_t) '&':
							if( ( string_index + 5 ) > utf8_string_size )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
								 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
								 "%s: UTF-8 string size too small.",
								 function );

								goto on_error;
							}
							utf8_string[ string_index++ ] = (uint8_t) '&';
							utf8_string[ string_index++ ] = (uint8_t) 'a';
							utf8_string[ string_index++ ] = (uint8_t) 'm';
							utf8_string[ string_index++ ] = (uint8_t) 'p';
							utf8_string[ string_index++ ] = (uint8_t) ';';

							break;

						/* Replace < by &lt; */
						case (uint8_t) '<':
							if( ( string_index + 4 ) > utf8_string_size )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
								 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
								 "%s: UTF-8 string size too small.",
								 function );

								goto on_error;
							}
							utf8_string[ string_index++ ] = (uint8_t) '&';
							utf8_string[ string_index++ ] = (uint8_t) 'l';
							utf8_string[ string_index++ ] = (uint8_t) 't';
							utf8_string[ string_index++ ] = (uint8_t) ';';

							break;

						/* Replace > by &gt; */
						case (uint8_t) '>':
							if( ( string_index + 4 ) > utf8_string_size )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
								 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
								 "%s: UTF-8 string size too small.",
								 function );

								goto on_error;
							}
							utf8_string[ string_index++ ] = (uint8_t) '&';
							utf8_string[ string_index++ ] = (uint8_t) 'g';
							utf8_string[ string_index++ ] = (uint8_t) 't';
							utf8_string[ string_index++ ] = (uint8_t) ';';

							break;

						/* Replace ' by &apos; */
/* TODO disabled for now since Event Viewer does not uses it
						case (uint8_t) '\'':
							if( ( string_index + 6 ) > utf8_string_size )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
								 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
								 "%s: UTF-8 string size too small.",
								 function );

								goto on_error;
							}
							utf8_string[ string_index++ ] = (uint8_t) '&';
							utf8_string[ string_index++ ] = (uint8_t) 'a';
							utf8_string[ string_index++ ] = (uint8_t) 'p';
							utf8_string[ string_index++ ] = (uint8_t) 'o';
							utf8_string[ string_index++ ] = (uint8_t) 's';
							utf8_string[ string_index++ ] = (uint8_t) ';';

							break;
*/

						/* Replace " by &quot; */
/* TODO disabled for now since Event Viewer does not uses it
						case (uint8_t) '"':
							if( ( string_index + 6 ) > utf8_string_size )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
								 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
								 "%s: UTF-8 string size too small.",
								 function );

								goto on_error;
							}
							utf8_string[ string_index++ ] = (uint8_t) '&';
							utf8_string[ string_index++ ] = (uint8_t) 'q';
							utf8_string[ string_index++ ] = (uint8_t) 'u';
							utf8_string[ string_index++ ] = (uint8_t) 'o';
							utf8_string[ string_index++ ] = (uint8_t) 't';
							utf8_string[ string_index++ ] = (uint8_t) ';';

							break;
*/

						default:
							if( ( string_index + 1 ) > utf8_string_size )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
								 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
								 "%s: UTF-8 string size too small.",
								 function );

								goto on_error;
							}
							utf8_string[ string_index++ ] = value_string[ value_string_index ];

							break;
					}
				}
				memory_free(
				 value_string );

				value_string = NULL;
			}
			else
			{
				if( libfwevt_xml_value_copy_to_utf8_string_with_index(
				     internal_xml_tag->value,
				     value_entry_index,
				     utf8_string,
				     utf8_string_size,
				     &string_index,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy value to UTF-8 string.",
					 function );

					goto on_error;
				}
				string_index--;
			}
		}
	}
	if( ( string_index + 1 ) > utf8_string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-8 string size too small.",
		 function );

		goto on_error;
	}
	utf8_string[ string_index++ ] = 0;

	*utf8_string_index = string_index;

	return( 1 );

on_error:
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

/* Retrieves the size of UTF-8 formatted string of the XML tag
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_utf8_xml_string_size(
     libfwevt_xml_tag_t *xml_tag,
     int xml_tag_level,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_attribute_xml_tag = NULL;
	libfwevt_internal_xml_tag_t *internal_xml_tag           = NULL;
	libfwevt_xml_tag_t *element_xml_tag                     = NULL;
	static char *function                                   = "libfwevt_xml_tag_get_utf8_xml_string_size";
	size_t attribute_name_size                              = 0;
	size_t element_name_size                                = 0;
	size_t safe_utf8_string_size                            = 0;
	size_t string_size                                      = 0;
	size_t value_string_size                                = 0;
	int attribute_index                                     = 0;
	int element_index                                       = 0;
	int number_of_attributes                                = 0;
	int number_of_elements                                  = 0;
	int value_type                                          = 0;

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

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
	     internal_xml_tag->attributes_array,
	     &number_of_attributes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of attributes.",
		 function );

		return( -1 );
	}
	/* The size of:
	 *   2 x ' ' character per indentation level
	 *   1 x '<' character
	 */
	safe_utf8_string_size = ( xml_tag_level * 2 ) + 1;

	if( internal_xml_tag->type == LIBFWEVT_XML_TAG_TYPE_NODE )
	{
		if( libcdata_array_get_number_of_entries(
		     internal_xml_tag->elements_array,
		     &number_of_elements,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of elements.",
			 function );

			return( -1 );
		}
		if( libuna_utf8_string_size_from_utf16_stream(
		     internal_xml_tag->name,
		     internal_xml_tag->name_size,
		     LIBUNA_ENDIAN_LITTLE,
		     &element_name_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-8 string size of element name.",
			 function );

			return( -1 );
		}
		/* The size of:
		 *   element name
		 */
		safe_utf8_string_size += element_name_size - 1;

		if( number_of_attributes > 0 )
		{
			for( attribute_index = 0;
			     attribute_index < number_of_attributes;
			     attribute_index++ )
			{
				if( libcdata_array_get_entry_by_index(
				     internal_xml_tag->attributes_array,
				     attribute_index,
				     (intptr_t **) &internal_attribute_xml_tag,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve attribute: %d.",
					 function,
					 attribute_index );

					return( -1 );
				}
				if( internal_attribute_xml_tag == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: missing attribute: %d.",
					 function,
					 attribute_index );

					return( -1 );
				}
				if( libuna_utf8_string_size_from_utf16_stream(
				     internal_attribute_xml_tag->name,
				     internal_attribute_xml_tag->name_size,
				     LIBUNA_ENDIAN_LITTLE,
				     &attribute_name_size,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve UTF-8 string size of attribute: %d name.",
					 function,
					 attribute_index );

					return( -1 );
				}
				/* The size of:
				 *   1 x ' ' character
				 *   attribute name
				 *   1 x '=' character
				 *   1 x '"' character
				 */
				safe_utf8_string_size += attribute_name_size + 2;

				if( libfwevt_xml_value_get_type(
				     internal_attribute_xml_tag->value,
				     &value_type,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve attribute value type.",
					 function );

					return( -1 );
				}
				if( libfwevt_xml_value_get_utf8_string_size_with_index(
				     internal_attribute_xml_tag->value,
				     0,
				     &string_size,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve UTF-8 string size of attribute: %d value.",
					 function,
					 attribute_index );

					return( -1 );
				}
				/* The size of:
				 *   attribute value formatted as a string
				 *   1 x '"' character
				 */
				safe_utf8_string_size += string_size;
			}
		}
		if( internal_xml_tag->value != NULL )
		{
			if( libfwevt_xml_tag_get_utf8_xml_value_string_size(
			     internal_xml_tag,
			     &value_string_size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve UTF-8 string size of element value.",
				 function );

				return( -1 );
			}
			if( value_string_size > 0 )
			{
				/* The size of:
				 *   1 x '>' character
				 *   value formatted as a string
				 *   1 x '<' character
				 *   1 x '/' character
				 *   element name
				 */
				safe_utf8_string_size += value_string_size + element_name_size + 1;
			}
			else
			{
				/* The size of:
				 *   1 x '/' character
				 */
				safe_utf8_string_size += 1;
			}
		}
		else if( number_of_elements > 0 )
		{
			for( element_index = 0;
			     element_index < number_of_elements;
			     element_index++ )
			{
				if( libcdata_array_get_entry_by_index(
				     internal_xml_tag->elements_array,
				     element_index,
				     (intptr_t **) &element_xml_tag,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve sub element: %d.",
					 function,
					 element_index );

					return( -1 );
				}
				if( libfwevt_xml_tag_get_utf8_xml_string_size(
				     element_xml_tag,
				     xml_tag_level + 1,
				     &string_size,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve UTF-8 string size of sub element: %d.",
					 function,
					 element_index );

					return( -1 );
				}
				/* The size of:
				 *   sub element formatted as a string
				 */
				safe_utf8_string_size += string_size - 1;
			}
			/* The size of:
			 *   1 x '>' character
			 *   1 x '\n' character
			 *   2 x ' ' character per indentation level
			 *   1 x '<' character
			 *   1 x '/' character
			 *   element name
			 */
			safe_utf8_string_size += ( xml_tag_level * 2 ) + element_name_size + 3;
		}
		else
		{
			/* The size of:
			 *   1 x '/' character
			 */
			safe_utf8_string_size += 1;
		}
	}
	else if( internal_xml_tag->type == LIBFWEVT_XML_TAG_TYPE_CDATA )
	{
		if( libfwevt_xml_value_get_utf8_string_size_with_index(
		     internal_xml_tag->value,
		     0,
		     &string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-8 string size of value.",
			 function );

			return( -1 );
		}
		/* The size of:
		 *   1 x "![CDATA["
		 *   value formatted as a string
		 *   1 x "]]"
		 */
		safe_utf8_string_size += string_size + 9;
	}
	else if( internal_xml_tag->type == LIBFWEVT_XML_TAG_TYPE_PI )
	{
		if( libuna_utf8_string_size_from_utf16_stream(
		     internal_xml_tag->name,
		     internal_xml_tag->name_size,
		     LIBUNA_ENDIAN_LITTLE,
		     &element_name_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-8 string size of element name.",
			 function );

			return( -1 );
		}
		/* The size of:
		 *   1 x '?' character
		 *   element name
		 */
		safe_utf8_string_size += element_name_size;

		if( libfwevt_xml_value_get_utf8_string_size_with_index(
		     internal_xml_tag->value,
		     0,
		     &string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-8 string size of value.",
			 function );

			return( -1 );
		}
		/* The size of:
		 *   1 x ' ' character
		 *   element name
		 *   1 x '?' character
		 */
		safe_utf8_string_size += string_size + 1;
	}
	/* The size of:
	 *   1 x '>' character
	 *   1 x '\n' character
	 *   1 x '\0' character
	 */
	safe_utf8_string_size += 3;

	*utf8_string_size = safe_utf8_string_size;

	return( 1 );
}

/* Retrieves the UTF-8 formatted string of the XML tag
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_utf8_xml_string_with_index(
     libfwevt_xml_tag_t *xml_tag,
     int xml_tag_level,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_attribute_xml_tag = NULL;
	libfwevt_internal_xml_tag_t *internal_xml_tag           = NULL;
	libfwevt_xml_tag_t *element_xml_tag                     = NULL;
	static char *function                                   = "libfwevt_xml_tag_get_utf8_xml_string_with_index";
	size_t string_index                                     = 0;
	size_t value_string_size                                = 0;
	int attribute_index                                     = 0;
	int element_index                                       = 0;
	int indentation_iterator                                = 0;
	int number_of_attributes                                = 0;
	int number_of_elements                                  = 0;
	int value_type                                          = 0;

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

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
	string_index = *utf8_string_index;

	if( ( string_index + ( xml_tag_level * 2 ) + 1 ) > utf8_string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-8 string size too small.",
		 function );

		return( -1 );
	}
	for( indentation_iterator = 0;
	     indentation_iterator < xml_tag_level;
	     indentation_iterator++ )
	{
		utf8_string[ string_index++ ] = (uint8_t) ' ';
		utf8_string[ string_index++ ] = (uint8_t) ' ';
	}
	utf8_string[ string_index++ ] = (uint8_t) '<';

	if( internal_xml_tag->type == LIBFWEVT_XML_TAG_TYPE_NODE )
	{
		if( libcdata_array_get_number_of_entries(
		     internal_xml_tag->attributes_array,
		     &number_of_attributes,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of attributes.",
			 function );

			return( -1 );
		}
		if( libcdata_array_get_number_of_entries(
		     internal_xml_tag->elements_array,
		     &number_of_elements,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of elements.",
			 function );

			return( -1 );
		}
		if( libuna_utf8_string_with_index_copy_from_utf16_stream(
		     utf8_string,
		     utf8_string_size,
		     &string_index,
		     internal_xml_tag->name,
		     internal_xml_tag->name_size,
		     LIBUNA_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy name to UTF-8 string.",
			 function );

			return( -1 );
		}
		string_index--;

		if( number_of_attributes > 0 )
		{
			for( attribute_index = 0;
			     attribute_index < number_of_attributes;
			     attribute_index++ )
			{
				if( libcdata_array_get_entry_by_index(
				     internal_xml_tag->attributes_array,
				     attribute_index,
				     (intptr_t **) &internal_attribute_xml_tag,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve attribute: %d.",
					 function,
					 attribute_index );

					return( -1 );
				}
				if( internal_attribute_xml_tag == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: missing attribute: %d.",
					 function,
					 attribute_index );

					return( -1 );
				}
				if( ( string_index + 1 ) > utf8_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-8 string size too small.",
					 function );

					return( -1 );
				}
				utf8_string[ string_index++ ] = (uint8_t) ' ';

				if( libuna_utf8_string_with_index_copy_from_utf16_stream(
				     utf8_string,
				     utf8_string_size,
				     &string_index,
				     internal_attribute_xml_tag->name,
				     internal_attribute_xml_tag->name_size,
				     LIBUNA_ENDIAN_LITTLE,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy attribute: %d name to UTF-8 string.",
					 function,
					 attribute_index );

					return( -1 );
				}
				string_index--;

				if( ( string_index + 2 ) > utf8_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-8 string size too small.",
					 function );

					return( -1 );
				}
				utf8_string[ string_index++ ] = (uint8_t) '=';
				utf8_string[ string_index++ ] = (uint8_t) '"';

				if( libfwevt_xml_value_get_type(
				     internal_attribute_xml_tag->value,
				     &value_type,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve attribute value type.",
					 function );

					return( -1 );
				}
				if( libfwevt_xml_value_copy_to_utf8_string_with_index(
				     internal_attribute_xml_tag->value,
				     0,
				     utf8_string,
				     utf8_string_size,
				     &string_index,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy attribute: %d value to UTF-8 string.",
					 function,
					 attribute_index );

					return( -1 );
				}
				string_index--;

				if( ( string_index + 1 ) > utf8_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-8 string size too small.",
					 function );

					return( -1 );
				}
				utf8_string[ string_index++ ] = (uint8_t) '"';
			}
		}
		if( internal_xml_tag->value != NULL )
		{
			if( libfwevt_xml_tag_get_utf8_xml_value_string_size(
			     internal_xml_tag,
			     &value_string_size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve UTF-8 string size of element value.",
				 function );

				return( -1 );
			}
			if( value_string_size > 0 )
			{
				if( ( string_index + 1 ) > utf8_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-8 string size too small.",
					 function );

					return( -1 );
				}
				utf8_string[ string_index++ ] = (uint8_t) '>';

				if( libfwevt_xml_tag_get_utf8_xml_value_string_with_index(
				     internal_xml_tag,
				     utf8_string,
				     utf8_string_size,
				     &string_index,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve UTF-8 string of element value.",
					 function );

					return( -1 );
				}
				string_index--;

				if( ( string_index + 2 ) > utf8_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-8 string size too small.",
					 function );

					return( -1 );
				}
				utf8_string[ string_index++ ] = (uint8_t) '<';
				utf8_string[ string_index++ ] = (uint8_t) '/';

				if( libuna_utf8_string_with_index_copy_from_utf16_stream(
				     utf8_string,
				     utf8_string_size,
				     &string_index,
				     internal_xml_tag->name,
				     internal_xml_tag->name_size,
				     LIBUNA_ENDIAN_LITTLE,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy name to UTF-8 string.",
					 function );

					return( -1 );
				}
				string_index--;
			}
			else
			{
				if( ( string_index + 1 ) > utf8_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-8 string size too small.",
					 function );

					return( -1 );
				}
				utf8_string[ string_index++ ] = (uint8_t) '/';
			}
		}
		else if( number_of_elements > 0 )
		{
			if( ( string_index + 2 ) > utf8_string_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-8 string size too small.",
				 function );

				return( -1 );
			}
			utf8_string[ string_index++ ] = (uint8_t) '>';
			utf8_string[ string_index++ ] = (uint8_t) '\n';

			for( element_index = 0;
			     element_index < number_of_elements;
			     element_index++ )
			{
				if( libcdata_array_get_entry_by_index(
				     internal_xml_tag->elements_array,
				     element_index,
				     (intptr_t **) &element_xml_tag,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve sub element: %d.",
					 function,
					 element_index );

					return( -1 );
				}
				if( libfwevt_xml_tag_get_utf8_xml_string_with_index(
				     element_xml_tag,
				     xml_tag_level + 1,
				     utf8_string,
				     utf8_string_size,
				     &string_index,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy sub element: %d to UTF-8 string.",
					 function,
					 element_index );

					return( -1 );
				}
				string_index--;
			}
			if( ( string_index + ( xml_tag_level * 2 ) ) > utf8_string_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-8 string size too small.",
				 function );

				return( -1 );
			}
			for( indentation_iterator = 0;
			     indentation_iterator < xml_tag_level;
			     indentation_iterator++ )
			{
				utf8_string[ string_index++ ] = (uint8_t) ' ';
				utf8_string[ string_index++ ] = (uint8_t) ' ';
			}
			if( ( string_index + 2 ) > utf8_string_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-8 string size too small.",
				 function );

				return( -1 );
			}
			utf8_string[ string_index++ ] = (uint8_t) '<';
			utf8_string[ string_index++ ] = (uint8_t) '/';

			if( libuna_utf8_string_with_index_copy_from_utf16_stream(
			     utf8_string,
			     utf8_string_size,
			     &string_index,
			     internal_xml_tag->name,
			     internal_xml_tag->name_size,
			     LIBUNA_ENDIAN_LITTLE,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy name to UTF-8 string.",
				 function );

				return( -1 );
			}
			string_index--;
		}
		else
		{
			if( ( string_index + 1 ) > utf8_string_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-8 string size too small.",
				 function );

				return( -1 );
			}
			utf8_string[ string_index++ ] = (uint8_t) '/';
		}
		if( ( string_index + 3 ) > utf8_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-8 string size too small.",
			 function );

			return( -1 );
		}
	}
	else if( internal_xml_tag->type == LIBFWEVT_XML_TAG_TYPE_CDATA )
	{
		if( ( string_index + 8 ) > utf8_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-8 string size too small.",
			 function );

			return( -1 );
		}
		utf8_string[ string_index++ ] = (uint8_t) '!';
		utf8_string[ string_index++ ] = (uint8_t) '[';
		utf8_string[ string_index++ ] = (uint8_t) 'C';
		utf8_string[ string_index++ ] = (uint8_t) 'D';
		utf8_string[ string_index++ ] = (uint8_t) 'A';
		utf8_string[ string_index++ ] = (uint8_t) 'T';
		utf8_string[ string_index++ ] = (uint8_t) 'A';
		utf8_string[ string_index++ ] = (uint8_t) '[';

		if( libfwevt_xml_value_copy_to_utf8_string_with_index(
		     internal_xml_tag->value,
		     0,
		     utf8_string,
		     utf8_string_size,
		     &string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy value to UTF-8 string.",
			 function );

			return( -1 );
		}
		string_index--;

		if( ( string_index + 2 ) > utf8_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-8 string size too small.",
			 function );

			return( -1 );
		}
		utf8_string[ string_index++ ] = (uint8_t) ']';
		utf8_string[ string_index++ ] = (uint8_t) ']';
	}
	else if( internal_xml_tag->type == LIBFWEVT_XML_TAG_TYPE_PI )
	{
		if( ( string_index + 1 ) > utf8_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-8 string size too small.",
			 function );

			return( -1 );
		}
		utf8_string[ string_index++ ] = (uint8_t) '?';

		if( libuna_utf8_string_with_index_copy_from_utf16_stream(
		     utf8_string,
		     utf8_string_size,
		     &string_index,
		     internal_xml_tag->name,
		     internal_xml_tag->name_size,
		     LIBUNA_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy name to UTF-8 string.",
			 function );

			return( -1 );
		}
		string_index--;

		if( ( string_index + 1 ) > utf8_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-8 string size too small.",
			 function );

			return( -1 );
		}
		utf8_string[ string_index++ ] = (uint8_t) ' ';

		if( libfwevt_xml_value_copy_to_utf8_string_with_index(
		     internal_xml_tag->value,
		     0,
		     utf8_string,
		     utf8_string_size,
		     &string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy value to UTF-8 string.",
			 function );

			return( -1 );
		}
		string_index--;

		if( ( string_index + 1 ) > utf8_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-8 string size too small.",
			 function );

			return( -1 );
		}
		utf8_string[ string_index++ ] = (uint8_t) '?';
	}
	utf8_string[ string_index++ ] = (uint8_t) '>';
	utf8_string[ string_index++ ] = (uint8_t) '\n';
	utf8_string[ string_index++ ] = 0;

	*utf8_string_index = string_index;

	return( 1 );
}

/* Retrieves the size of UTF-16 formatted string of the XML value
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_utf16_xml_value_string_size(
     libfwevt_internal_xml_tag_t *internal_xml_tag,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	uint16_t static_value_string[ 2 ];

	uint16_t *value_string        = NULL;
	static char *function         = "libfwevt_xml_tag_get_utf16_xml_value_string_size";
	size_t safe_utf16_string_size = 0;
	size_t value_string_index     = 0;
	size_t value_string_size      = 0;
	int number_of_value_entries   = 0;
	int result                    = 0;
	int value_entry_index         = 0;
	int value_type                = 0;

	if( internal_xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
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
	if( libfwevt_xml_value_get_type(
	     internal_xml_tag->value,
	     &value_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element value type.",
		 function );

		goto on_error;
	}
	if( libfwevt_xml_value_get_number_of_value_entries(
	     internal_xml_tag->value,
	     &number_of_value_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element value number of value entries.",
		 function );

		goto on_error;
	}
	for( value_entry_index = 0;
	     value_entry_index < number_of_value_entries;
	     value_entry_index++ )
	{
		result = libfwevt_xml_value_get_utf16_string_size_with_index(
			  internal_xml_tag->value,
			  value_entry_index,
			  &value_string_size,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-16 string size of element value entry: %d.",
			 function,
			 value_entry_index );

			goto on_error;
		}
		if( ( result == 0 )
		 && ( number_of_value_entries != 1 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing element value entry: %d.",
			 function,
			 value_entry_index );

			goto on_error;
		}
		if( result != 0 )
		{
			if( ( number_of_value_entries == 1 )
			 && ( value_string_size == 2 ) )
			{
				value_string_index = 0;

				if( libfwevt_xml_value_copy_to_utf16_string_with_index(
				     internal_xml_tag->value,
				     0,
				     static_value_string,
				     2,
				     &value_string_index,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy element value: 0 to UTF-16 string.",
					 function );

					goto on_error;
				}
				/* The value data consists of a single linefeed consider it empty
				 */
				if( static_value_string[ 0 ] == (uint16_t) '\n' )
				{
					value_string_size -= 1;
				}
			}
			else if( value_type == LIBFVALUE_VALUE_TYPE_STRING_UTF16 )
			{
				if( ( value_string_size == 0 )
				 || ( value_string_size > ( MEMORY_MAXIMUM_ALLOCATION_SIZE / sizeof( uint16_t ) ) ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: invalid value string size value out of bounds.",
					 function );

					goto on_error;
				}
				value_string = (uint16_t *) memory_allocate(
				                             sizeof( uint16_t ) * value_string_size );

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
				value_string_index = 0;

				if( libfwevt_xml_value_copy_to_utf16_string_with_index(
				     internal_xml_tag->value,
				     value_entry_index,
				     value_string,
				     value_string_size,
				     &value_string_index,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy element value: %d to UTF-16 string.",
					 function,
					 value_entry_index );

					goto on_error;
				}
				for( value_string_index = 0;
				     value_string_index < value_string_size;
				     value_string_index++ )
				{
					switch( value_string[ value_string_index ] )
					{
						/* Replace & by &amp; */
						case (uint16_t) '&':
							safe_utf16_string_size += 4;
							break;

						/* Replace < by &lt; and > by &gt; */
						case (uint16_t) '<':
						case (uint16_t) '>':
							safe_utf16_string_size += 3;
							break;

						/* Replace ' by &apos; and " by &quot; */
/* TODO disabled for now since Event Viewer does not uses it
						case (uint16_t) '\'':
						case (uint16_t) '"':
							safe_utf16_string_size += 5;
							break;
*/

						default:
							break;
					}
				}
				memory_free(
				 value_string );

				value_string = NULL;
			}
			if( value_string_size > 1 )
			{
				/* The size of:
				 *   value formatted as a string
				 */
				safe_utf16_string_size += value_string_size - 1;
			}
		}
	}
	if( safe_utf16_string_size != 0 )
	{
		/* The size of:
		 *   end-of-string character
		 */
		safe_utf16_string_size += 1;
	}
	*utf16_string_size = safe_utf16_string_size;

	return( 1 );

on_error:
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

/* Retrieves the UTF-16 formatted string of the XML value
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_utf16_xml_value_string_with_index(
     libfwevt_internal_xml_tag_t *internal_xml_tag,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     libcerror_error_t **error )
{
	uint16_t *value_string      = NULL;
	static char *function       = "libfwevt_xml_tag_get_utf16_xml_value_string_with_index";
	size_t string_index         = 0;
	size_t value_string_index   = 0;
	size_t value_string_size    = 0;
	int number_of_value_entries = 0;
	int result                  = 0;
	int value_entry_index       = 0;
	int value_type              = 0;

	if( internal_xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
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
	string_index = *utf16_string_index;

	if( libfwevt_xml_value_get_type(
	     internal_xml_tag->value,
	     &value_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element value type.",
		 function );

		goto on_error;
	}
	if( libfwevt_xml_value_get_number_of_value_entries(
	     internal_xml_tag->value,
	     &number_of_value_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element value number of value entries.",
		 function );

		goto on_error;
	}
	for( value_entry_index = 0;
	     value_entry_index < number_of_value_entries;
	     value_entry_index++ )
	{
		result = libfwevt_xml_value_get_utf16_string_size_with_index(
			  internal_xml_tag->value,
			  value_entry_index,
			  &value_string_size,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-16 string size of element value entry: %d.",
			 function,
			 value_entry_index );

			goto on_error;
		}
		if( ( result == 0 )
		 && ( number_of_value_entries != 1 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing element value entry: %d.",
			 function,
			 value_entry_index );

			goto on_error;
		}
		if( ( result != 0 )
		 && ( value_string_size > 1 ) )
		{
			if( value_type == LIBFVALUE_VALUE_TYPE_STRING_UTF16 )
			{
				if( ( value_string_size == 0 )
				 || ( value_string_size > ( MEMORY_MAXIMUM_ALLOCATION_SIZE / sizeof( uint16_t ) ) ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: invalid value string size value out of bounds.",
					 function );

					goto on_error;
				}
				value_string = (uint16_t *) memory_allocate(
				                             sizeof( uint16_t ) * value_string_size );

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
				value_string_index = 0;

				if( libfwevt_xml_value_copy_to_utf16_string_with_index(
				     internal_xml_tag->value,
				     value_entry_index,
				     value_string,
				     value_string_size,
				     &value_string_index,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy element value: %d to UTF-16 string.",
					 function,
					 value_entry_index );

					goto on_error;
				}
				for( value_string_index = 0;
				     value_string_index < ( value_string_size - 1 );
				     value_string_index++ )
				{
					switch( value_string[ value_string_index ] )
					{
						/* Replace & by &amp; */
						case (uint16_t) '&':
							if( ( string_index + 5 ) > utf16_string_size )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
								 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
								 "%s: UTF-16 string size too small.",
								 function );

								goto on_error;
							}
							utf16_string[ string_index++ ] = (uint16_t) '&';
							utf16_string[ string_index++ ] = (uint16_t) 'a';
							utf16_string[ string_index++ ] = (uint16_t) 'm';
							utf16_string[ string_index++ ] = (uint16_t) 'p';
							utf16_string[ string_index++ ] = (uint16_t) ';';

							break;

						/* Replace < by &lt; */
						case (uint16_t) '<':
							if( ( string_index + 4 ) > utf16_string_size )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
								 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
								 "%s: UTF-16 string size too small.",
								 function );

								goto on_error;
							}
							utf16_string[ string_index++ ] = (uint16_t) '&';
							utf16_string[ string_index++ ] = (uint16_t) 'l';
							utf16_string[ string_index++ ] = (uint16_t) 't';
							utf16_string[ string_index++ ] = (uint16_t) ';';

							break;

						/* Replace > by &gt; */
						case (uint16_t) '>':
							if( ( string_index + 4 ) > utf16_string_size )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
								 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
								 "%s: UTF-16 string size too small.",
								 function );

								goto on_error;
							}
							utf16_string[ string_index++ ] = (uint16_t) '&';
							utf16_string[ string_index++ ] = (uint16_t) 'g';
							utf16_string[ string_index++ ] = (uint16_t) 't';
							utf16_string[ string_index++ ] = (uint16_t) ';';

							break;

						/* Replace ' by &apos; */
/* TODO disabled for now since Event Viewer does not uses it
						case (uint16_t) '\'':
							if( ( string_index + 6 ) > utf16_string_size )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
								 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
								 "%s: UTF-16 string size too small.",
								 function );

								goto on_error;
							}
							utf16_string[ string_index++ ] = (uint16_t) '&';
							utf16_string[ string_index++ ] = (uint16_t) 'a';
							utf16_string[ string_index++ ] = (uint16_t) 'p';
							utf16_string[ string_index++ ] = (uint16_t) 'o';
							utf16_string[ string_index++ ] = (uint16_t) 's';
							utf16_string[ string_index++ ] = (uint16_t) ';';

							break;
*/

						/* Replace " by &quot; */
/* TODO disabled for now since Event Viewer does not uses it
						case (uint16_t) '"':
							if( ( string_index + 6 ) > utf16_string_size )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
								 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
								 "%s: UTF-16 string size too small.",
								 function );

								goto on_error;
							}
							utf16_string[ string_index++ ] = (uint16_t) '&';
							utf16_string[ string_index++ ] = (uint16_t) 'q';
							utf16_string[ string_index++ ] = (uint16_t) 'u';
							utf16_string[ string_index++ ] = (uint16_t) 'o';
							utf16_string[ string_index++ ] = (uint16_t) 't';
							utf16_string[ string_index++ ] = (uint16_t) ';';

							break;
*/

						default:
							if( ( string_index + 1 ) > utf16_string_size )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
								 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
								 "%s: UTF-16 string size too small.",
								 function );

								goto on_error;
							}
							utf16_string[ string_index++ ] = value_string[ value_string_index ];

							break;
					}
				}
				memory_free(
				 value_string );

				value_string = NULL;
			}
			else
			{
				if( libfwevt_xml_value_copy_to_utf16_string_with_index(
				     internal_xml_tag->value,
				     value_entry_index,
				     utf16_string,
				     utf16_string_size,
				     &string_index,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy value to UTF-16 string.",
					 function );

					goto on_error;
				}
				string_index--;
			}
		}
	}
	if( ( string_index + 1 ) > utf16_string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-16 string size too small.",
		 function );

		goto on_error;
	}
	utf16_string[ string_index++ ] = 0;

	*utf16_string_index = string_index;

	return( 1 );

on_error:
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

/* Retrieves the size of UTF-16 formatted string of the XML tag
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_utf16_xml_string_size(
     libfwevt_xml_tag_t *xml_tag,
     int xml_tag_level,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_attribute_xml_tag = NULL;
	libfwevt_internal_xml_tag_t *internal_xml_tag           = NULL;
	libfwevt_xml_tag_t *element_xml_tag                     = NULL;
	static char *function                                   = "libfwevt_xml_tag_get_utf16_xml_string_size";
	size_t attribute_name_size                              = 0;
	size_t element_name_size                                = 0;
	size_t safe_utf16_string_size                           = 0;
	size_t string_size                                      = 0;
	size_t value_string_size                                = 0;
	int attribute_index                                     = 0;
	int element_index                                       = 0;
	int number_of_attributes                                = 0;
	int number_of_elements                                  = 0;
	int value_type                                          = 0;

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

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
	     internal_xml_tag->attributes_array,
	     &number_of_attributes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of attributes.",
		 function );

		return( -1 );
	}
	/* The size of:
	 *   2 x ' ' character per indentation level
	 *   1 x '<' character
	 */
	safe_utf16_string_size = ( xml_tag_level * 2 ) + 1;

	if( internal_xml_tag->type == LIBFWEVT_XML_TAG_TYPE_NODE )
	{
		if( libcdata_array_get_number_of_entries(
		     internal_xml_tag->elements_array,
		     &number_of_elements,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of elements.",
			 function );

			return( -1 );
		}
		if( libuna_utf16_string_size_from_utf16_stream(
		     internal_xml_tag->name,
		     internal_xml_tag->name_size,
		     LIBUNA_ENDIAN_LITTLE,
		     &element_name_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve size of UTF-16 string of element name.",
			 function );

			return( -1 );
		}
		/* The size of:
		 *   element name
		 */
		safe_utf16_string_size += element_name_size - 1;

		if( number_of_attributes > 0 )
		{
			for( attribute_index = 0;
			     attribute_index < number_of_attributes;
			     attribute_index++ )
			{
				if( libcdata_array_get_entry_by_index(
				     internal_xml_tag->attributes_array,
				     attribute_index,
				     (intptr_t **) &internal_attribute_xml_tag,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve attribute: %d.",
					 function,
					 attribute_index );

					return( -1 );
				}
				if( internal_attribute_xml_tag == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: missing attribute: %d.",
					 function,
					 attribute_index );

					return( -1 );
				}
				if( libuna_utf16_string_size_from_utf16_stream(
				     internal_attribute_xml_tag->name,
				     internal_attribute_xml_tag->name_size,
				     LIBUNA_ENDIAN_LITTLE,
				     &attribute_name_size,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve UTF-16 string size of attribute: %d name.",
					 function,
					 attribute_index );

					return( -1 );
				}
				/* The size of:
				 *   1 x ' ' character
				 *   attribute name
				 *   1 x '=' character
				 *   1 x '"' character
				 */
				safe_utf16_string_size += attribute_name_size + 2;

				if( libfwevt_xml_value_get_type(
				     internal_attribute_xml_tag->value,
				     &value_type,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve attribute value type.",
					 function );

					return( -1 );
				}
				if( libfwevt_xml_value_get_utf16_string_size_with_index(
				     internal_attribute_xml_tag->value,
				     0,
				     &string_size,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve UTF-16 string size of attribute: %d value.",
					 function,
					 attribute_index );

					return( -1 );
				}
				/* The size of:
				 *   attribute value formatted as a string
				 *   1 x '"' character
				 */
				safe_utf16_string_size += string_size;
			}
		}
		if( internal_xml_tag->value != NULL )
		{
			if( libfwevt_xml_tag_get_utf16_xml_value_string_size(
			     internal_xml_tag,
			     &value_string_size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve UTF-16 string size of element value.",
				 function );

				return( -1 );
			}
			if( value_string_size > 0 )
			{
				/* The size of:
				 *   1 x '>' character
				 *   value formatted as a string
				 *   1 x '<' character
				 *   1 x '/' character
				 *   element name
				 */
				safe_utf16_string_size += value_string_size + element_name_size + 1;
			}
			else
			{
				/* The size of:
				 *   1 x '/' character
				 */
				safe_utf16_string_size += 1;
			}
		}
		else if( number_of_elements > 0 )
		{
			for( element_index = 0;
			     element_index < number_of_elements;
			     element_index++ )
			{
				if( libcdata_array_get_entry_by_index(
				     internal_xml_tag->elements_array,
				     element_index,
				     (intptr_t **) &element_xml_tag,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve sub element: %d.",
					 function,
					 element_index );

					return( -1 );
				}
				if( libfwevt_xml_tag_get_utf16_xml_string_size(
				     element_xml_tag,
				     xml_tag_level + 1,
				     &string_size,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve UTF-16 string size of sub element: %d.",
					 function,
					 element_index );

					return( -1 );
				}
				/* The size of:
				 *   sub element formatted as a string
				 */
				safe_utf16_string_size += string_size - 1;
			}
			/* The size of:
			 *   1 x '>' character
			 *   1 x '\n' character
			 *   2 x ' ' character per indentation level
			 *   1 x '<' character
			 *   1 x '/' character
			 *   element name
			 */
			safe_utf16_string_size += ( xml_tag_level * 2 ) + element_name_size + 3;
		}
		else
		{
			/* The size of:
			 *   1 x '/' character
			 */
			safe_utf16_string_size += 1;
		}
	}
	else if( internal_xml_tag->type == LIBFWEVT_XML_TAG_TYPE_CDATA )
	{
		if( libfwevt_xml_value_get_utf16_string_size_with_index(
		     internal_xml_tag->value,
		     0,
		     &string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-16 string size of value.",
			 function );

			return( -1 );
		}
		/* The size of:
		 *   1 x "![CDATA["
		 *   value formatted as a string
		 *   1 x "]]"
		 */
		safe_utf16_string_size += string_size + 9;
	}
	else if( internal_xml_tag->type == LIBFWEVT_XML_TAG_TYPE_PI )
	{
		if( libuna_utf16_string_size_from_utf16_stream(
		     internal_xml_tag->name,
		     internal_xml_tag->name_size,
		     LIBUNA_ENDIAN_LITTLE,
		     &element_name_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-16 string size of element name.",
			 function );

			return( -1 );
		}
		/* The size of:
		 *   1 x '?' character
		 *   element name
		 */
		safe_utf16_string_size += element_name_size;

		if( libfwevt_xml_value_get_utf16_string_size_with_index(
		     internal_xml_tag->value,
		     0,
		     &string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve UTF-16 string size of value.",
			 function );

			return( -1 );
		}
		/* The size of:
		 *   1 x ' ' character
		 *   element name
		 *   1 x '?' character
		 */
		safe_utf16_string_size += string_size + 1;
	}
	/* The size of:
	 *   1 x '>' character
	 *   1 x '\n' character
	 *   1 x '\0' character
	 */
	safe_utf16_string_size += 3;

	*utf16_string_size = safe_utf16_string_size;

	return( 1 );
}

/* Retrieves the UTF-16 formatted string of the XML tag
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_get_utf16_xml_string_with_index(
     libfwevt_xml_tag_t *xml_tag,
     int xml_tag_level,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_attribute_xml_tag = NULL;
	libfwevt_internal_xml_tag_t *internal_xml_tag           = NULL;
	libfwevt_xml_tag_t *element_xml_tag                     = NULL;
	static char *function                                   = "libfwevt_xml_tag_get_utf16_xml_string_with_index";
	size_t string_index                                     = 0;
	size_t value_string_size                                = 0;
	int attribute_index                                     = 0;
	int element_index                                       = 0;
	int indentation_iterator                                = 0;
	int number_of_attributes                                = 0;
	int number_of_elements                                  = 0;
	int value_type                                          = 0;

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

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
	string_index = *utf16_string_index;

	if( ( string_index + ( xml_tag_level * 2 ) + 1 ) > utf16_string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-16 string size too small.",
		 function );

		return( -1 );
	}
	for( indentation_iterator = 0;
	     indentation_iterator < xml_tag_level;
	     indentation_iterator++ )
	{
		utf16_string[ string_index++ ] = (uint16_t) ' ';
		utf16_string[ string_index++ ] = (uint16_t) ' ';
	}
	utf16_string[ string_index++ ] = (uint16_t) '<';

	if( internal_xml_tag->type == LIBFWEVT_XML_TAG_TYPE_NODE )
	{
		if( libcdata_array_get_number_of_entries(
		     internal_xml_tag->attributes_array,
		     &number_of_attributes,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of attributes.",
			 function );

			return( -1 );
		}
		if( libcdata_array_get_number_of_entries(
		     internal_xml_tag->elements_array,
		     &number_of_elements,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of elements.",
			 function );

			return( -1 );
		}
		if( libuna_utf16_string_with_index_copy_from_utf16_stream(
		     utf16_string,
		     utf16_string_size,
		     &string_index,
		     internal_xml_tag->name,
		     internal_xml_tag->name_size,
		     LIBUNA_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy name to UTF-16 string.",
			 function );

			return( -1 );
		}
		string_index--;

		if( number_of_attributes > 0 )
		{
			for( attribute_index = 0;
			     attribute_index < number_of_attributes;
			     attribute_index++ )
			{
				if( libcdata_array_get_entry_by_index(
				     internal_xml_tag->attributes_array,
				     attribute_index,
				     (intptr_t **) &internal_attribute_xml_tag,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve attribute: %d.",
					 function,
					 attribute_index );

					return( -1 );
				}
				if( internal_attribute_xml_tag == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: missing attribute: %d.",
					 function,
					 attribute_index );

					return( -1 );
				}
				if( ( string_index + 1 ) > utf16_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-16 string size too small.",
					 function );

					return( -1 );
				}
				utf16_string[ string_index++ ] = (uint16_t) ' ';

				if( libuna_utf16_string_with_index_copy_from_utf16_stream(
				     utf16_string,
				     utf16_string_size,
				     &string_index,
				     internal_attribute_xml_tag->name,
				     internal_attribute_xml_tag->name_size,
				     LIBUNA_ENDIAN_LITTLE,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy attribute: %d name to UTF-16 string.",
					 function,
					 attribute_index );

					return( -1 );
				}
				string_index--;

				if( ( string_index + 2 ) > utf16_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-16 string size too small.",
					 function );

					return( -1 );
				}
				utf16_string[ string_index++ ] = (uint16_t) '=';
				utf16_string[ string_index++ ] = (uint16_t) '"';

				if( libfwevt_xml_value_get_type(
				     internal_attribute_xml_tag->value,
				     &value_type,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve attribute value type.",
					 function );

					return( -1 );
				}
				if( libfwevt_xml_value_copy_to_utf16_string_with_index(
				     internal_attribute_xml_tag->value,
				     0,
				     utf16_string,
				     utf16_string_size,
				     &string_index,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy attribute: %d value to UTF-16 string.",
					 function,
					 attribute_index );

					return( -1 );
				}
				string_index--;

				if( ( string_index + 1 ) > utf16_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-16 string size too small.",
					 function );

					return( -1 );
				}
				utf16_string[ string_index++ ] = (uint16_t) '"';
			}
		}
		if( internal_xml_tag->value != NULL )
		{
			if( libfwevt_xml_tag_get_utf16_xml_value_string_size(
			     internal_xml_tag,
			     &value_string_size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve UTF-16 string size of element value.",
				 function );

				return( -1 );
			}
			if( value_string_size > 0 )
			{
				if( ( string_index + 1 ) > utf16_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-16 string size too small.",
					 function );

					return( -1 );
				}
				utf16_string[ string_index++ ] = (uint16_t) '>';

				if( libfwevt_xml_tag_get_utf16_xml_value_string_with_index(
				     internal_xml_tag,
				     utf16_string,
				     utf16_string_size,
				     &string_index,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve UTF-16 string of element value.",
					 function );

					return( -1 );
				}
				string_index--;

				if( ( string_index + 2 ) > utf16_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-16 string size too small.",
					 function );

					return( -1 );
				}
				utf16_string[ string_index++ ] = (uint16_t) '<';
				utf16_string[ string_index++ ] = (uint16_t) '/';

				if( libuna_utf16_string_with_index_copy_from_utf16_stream(
				     utf16_string,
				     utf16_string_size,
				     &string_index,
				     internal_xml_tag->name,
				     internal_xml_tag->name_size,
				     LIBUNA_ENDIAN_LITTLE,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy name to UTF-16 string.",
					 function );

					return( -1 );
				}
				string_index--;
			}
			else
			{
				if( ( string_index + 1 ) > utf16_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-16 string size too small.",
					 function );

					return( -1 );
				}
				utf16_string[ string_index++ ] = (uint16_t) '/';
			}
		}
		else if( number_of_elements > 0 )
		{
			if( ( string_index + 2 ) > utf16_string_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-16 string size too small.",
				 function );

				return( -1 );
			}
			utf16_string[ string_index++ ] = (uint16_t) '>';
			utf16_string[ string_index++ ] = (uint16_t) '\n';

			for( element_index = 0;
			     element_index < number_of_elements;
			     element_index++ )
			{
				if( libcdata_array_get_entry_by_index(
				     internal_xml_tag->elements_array,
				     element_index,
				     (intptr_t **) &element_xml_tag,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve sub element: %d.",
					 function,
					 element_index );

					return( -1 );
				}
				if( libfwevt_xml_tag_get_utf16_xml_string_with_index(
				     element_xml_tag,
				     xml_tag_level + 1,
				     utf16_string,
				     utf16_string_size,
				     &string_index,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy sub element: %d to UTF-16 string.",
					 function,
					 element_index );

					return( -1 );
				}
				string_index--;
			}
			if( ( string_index + ( xml_tag_level * 2 ) ) > utf16_string_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-16 string size too small.",
				 function );

				return( -1 );
			}
			for( indentation_iterator = 0;
			     indentation_iterator < xml_tag_level;
			     indentation_iterator++ )
			{
				utf16_string[ string_index++ ] = (uint16_t) ' ';
				utf16_string[ string_index++ ] = (uint16_t) ' ';
			}
			if( ( string_index + 2 ) > utf16_string_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-16 string size too small.",
				 function );

				return( -1 );
			}
			utf16_string[ string_index++ ] = (uint16_t) '<';
			utf16_string[ string_index++ ] = (uint16_t) '/';

			if( libuna_utf16_string_with_index_copy_from_utf16_stream(
			     utf16_string,
			     utf16_string_size,
			     &string_index,
			     internal_xml_tag->name,
			     internal_xml_tag->name_size,
			     LIBUNA_ENDIAN_LITTLE,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy name to UTF-16 string.",
				 function );

				return( -1 );
			}
			string_index--;
		}
		else
		{
			if( ( string_index + 1 ) > utf16_string_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: UTF-16 string size too small.",
				 function );

				return( -1 );
			}
			utf16_string[ string_index++ ] = (uint16_t) '/';
		}
		if( ( string_index + 3 ) > utf16_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string size too small.",
			 function );

			return( -1 );
		}
	}
	else if( internal_xml_tag->type == LIBFWEVT_XML_TAG_TYPE_CDATA )
	{
		if( ( string_index + 8 ) > utf16_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string size too small.",
			 function );

			return( -1 );
		}
		utf16_string[ string_index++ ] = (uint16_t) '!';
		utf16_string[ string_index++ ] = (uint16_t) '[';
		utf16_string[ string_index++ ] = (uint16_t) 'C';
		utf16_string[ string_index++ ] = (uint16_t) 'D';
		utf16_string[ string_index++ ] = (uint16_t) 'A';
		utf16_string[ string_index++ ] = (uint16_t) 'T';
		utf16_string[ string_index++ ] = (uint16_t) 'A';
		utf16_string[ string_index++ ] = (uint16_t) '[';

		if( libfwevt_xml_value_copy_to_utf16_string_with_index(
		     internal_xml_tag->value,
		     0,
		     utf16_string,
		     utf16_string_size,
		     &string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy value to UTF-16 string.",
			 function );

			return( -1 );
		}
		string_index--;

		if( ( string_index + 2 ) > utf16_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string size too small.",
			 function );

			return( -1 );
		}
		utf16_string[ string_index++ ] = (uint16_t) ']';
		utf16_string[ string_index++ ] = (uint16_t) ']';
	}
	else if( internal_xml_tag->type == LIBFWEVT_XML_TAG_TYPE_PI )
	{
		if( ( string_index + 1 ) > utf16_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string size too small.",
			 function );

			return( -1 );
		}
		utf16_string[ string_index++ ] = (uint16_t) '?';

		if( libuna_utf16_string_with_index_copy_from_utf16_stream(
		     utf16_string,
		     utf16_string_size,
		     &string_index,
		     internal_xml_tag->name,
		     internal_xml_tag->name_size,
		     LIBUNA_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy name to UTF-16 string.",
			 function );

			return( -1 );
		}
		string_index--;

		if( ( string_index + 1 ) > utf16_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string size too small.",
			 function );

			return( -1 );
		}
		utf16_string[ string_index++ ] = (uint16_t) ' ';

		if( libfwevt_xml_value_copy_to_utf16_string_with_index(
		     internal_xml_tag->value,
		     0,
		     utf16_string,
		     utf16_string_size,
		     &string_index,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy value to UTF-16 string.",
			 function );

			return( -1 );
		}
		string_index--;

		if( ( string_index + 1 ) > utf16_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string size too small.",
			 function );

			return( -1 );
		}
		utf16_string[ string_index++ ] = (uint16_t) '?';
	}
	utf16_string[ string_index++ ] = (uint16_t) '>';
	utf16_string[ string_index++ ] = (uint16_t) '\n';
	utf16_string[ string_index++ ] = 0;

	*utf16_string_index = string_index;

	return( 1 );
}

#if defined( HAVE_DEBUG_OUTPUT )

/* Debug prints the name
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_debug_print_name_string(
     libfwevt_internal_xml_tag_t *internal_xml_tag,
     libcerror_error_t **error )
{
	system_character_t *name_string = NULL;
	static char *function           = "libfwevt_xml_tag_debug_print_name_string";
	size_t name_string_size         = 0;
	int result                      = 0;

	if( internal_xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libuna_utf16_string_size_from_utf16_stream(
		  internal_xml_tag->name,
		  internal_xml_tag->name_size,
		  LIBUNA_ENDIAN_LITTLE,
		  &name_string_size,
		  error );
#else
	result = libuna_utf8_string_size_from_utf16_stream(
		  internal_xml_tag->name,
		  internal_xml_tag->name_size,
		  LIBUNA_ENDIAN_LITTLE,
		  &name_string_size,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of name string.",
		 function );

		goto on_error;
	}
	if( name_string_size > (size_t) ( SSIZE_MAX / sizeof( system_character_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid name string size value exceeds maximum.",
		 function );

		goto on_error;
	}
	name_string = system_string_allocate(
	               name_string_size );

	if( name_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create name string.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libuna_utf16_string_copy_from_utf16_stream(
		  (libuna_utf16_character_t *) name_string,
		  name_string_size,
		  internal_xml_tag->name,
		  internal_xml_tag->name_size,
		  LIBUNA_ENDIAN_LITTLE,
		  error );
#else
	result = libuna_utf8_string_copy_from_utf16_stream(
		  (libuna_utf8_character_t *) name_string,
		  name_string_size,
		  internal_xml_tag->name,
		  internal_xml_tag->name_size,
		  LIBUNA_ENDIAN_LITTLE,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set name string.",
		 function );

		goto on_error;
	}
	libcnotify_printf(
	 "%" PRIs_SYSTEM "",
	 name_string );

	memory_free(
	 name_string );

	return( 1 );

on_error:
	if( name_string != NULL )
	{
		memory_free(
		 name_string );
	}
	return( -1 );
}

/* Debug prints the XML value
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_debug_print_value_string(
     libfwevt_internal_xml_tag_t *internal_xml_tag,
     libcerror_error_t **error )
{
	system_character_t *value_string = NULL;
	static char *function            = "libfwevt_xml_tag_debug_print_value_string";
	size_t value_string_index        = 0;
	size_t value_string_size         = 0;
	int number_of_value_entries      = 0;
	int result                       = 0;
	int value_entry_index            = 0;
	int value_type                   = 0;

	if( internal_xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	if( libfwevt_xml_value_get_type(
	     internal_xml_tag->value,
	     &value_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element value type.",
		 function );

		goto on_error;
	}
	if( libfwevt_xml_value_get_number_of_value_entries(
	     internal_xml_tag->value,
	     &number_of_value_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element value number of value entries.",
		 function );

		goto on_error;
	}
	for( value_entry_index = 0;
	     value_entry_index < number_of_value_entries;
	     value_entry_index++ )
	{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfwevt_xml_value_get_utf16_string_size_with_index(
			  internal_xml_tag->value,
			  value_entry_index,
			  &value_string_size,
			  error );
#else
		result = libfwevt_xml_value_get_utf8_string_size_with_index(
			  internal_xml_tag->value,
			  value_entry_index,
			  &value_string_size,
			  error );
#endif
		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve string size of element value entry: %d.",
			 function,
			 value_entry_index );

			goto on_error;
		}
		if( ( result == 0 )
		 && ( number_of_value_entries != 1 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing element value entry: %d.",
			 function,
			 value_entry_index );

			goto on_error;
		}
		if( result != 0 )
		{
			if( value_type == LIBFVALUE_VALUE_TYPE_STRING_UTF16 )
			{
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
				value_string_index = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libfwevt_xml_value_copy_to_utf16_string_with_index(
				          internal_xml_tag->value,
				          value_entry_index,
				          (uint16_t *) value_string,
				          value_string_size,
				          &value_string_index,
				          error );
#else
				result = libfwevt_xml_value_copy_to_utf8_string_with_index(
				          internal_xml_tag->value,
				          value_entry_index,
				          (uint8_t *) value_string,
				          value_string_size,
				          &value_string_index,
				          error );
#endif
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy element value: %d to string.",
					 function,
					 value_entry_index );

					goto on_error;
				}
				for( value_string_index = 0;
				     value_string_index < ( value_string_size - 1 );
				     value_string_index++ )
				{
					switch( value_string[ value_string_index ] )
					{
						/* Replace & by &amp; */
						case (uint8_t) '&':
							libcnotify_printf(
							 "&amp;" );

							break;

						/* Replace < by &lt; */
						case (uint8_t) '<':
							libcnotify_printf(
							 "&lt;" );

							break;

						/* Replace > by &gt; */
						case (uint8_t) '>':
							libcnotify_printf(
							 "&gt;" );

							break;

						/* Replace ' by &apos; */
/* TODO disabled for now since Event Viewer does not uses it
						case (uint8_t) '\'':
							libcnotify_printf(
							 "&apos;" );

							break;
*/

						/* Replace " by &quot; */
/* TODO disabled for now since Event Viewer does not uses it
						case (uint8_t) '"':
							libcnotify_printf(
							 "&quot;" );

							break;
*/

						default:
			                                libcnotify_printf(
			                                 "%" PRIc_SYSTEM "",
			                                 value_string[ value_string_index ] );

							break;
					}
				}
				memory_free(
				 value_string );

				value_string = NULL;
			}
			else
			{
				if( libfwevt_debug_print_xml_value(
				     internal_xml_tag->value,
				     value_entry_index,
				     0,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
					 "%s: unable to print value.",
					 function );

					goto on_error;
				}
			}
		}
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

/* Debug prints the XML tag
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_debug_print(
     libfwevt_xml_tag_t *xml_tag,
     int xml_tag_level,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_attribute_xml_tag = NULL;
	libfwevt_internal_xml_tag_t *internal_xml_tag           = NULL;
	libfwevt_xml_tag_t *element_xml_tag                     = NULL;
	static char *function                                   = "libfwevt_xml_tag_debug_print";
	size_t value_string_size                                = 0;
	int attribute_index                                     = 0;
	int element_index                                       = 0;
	int indentation_iterator                                = 0;
	int number_of_attributes                                = 0;
	int number_of_elements                                  = 0;
	int value_type                                          = 0;

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	for( indentation_iterator = 0;
	     indentation_iterator < xml_tag_level;
	     indentation_iterator++ )
	{
		libcnotify_printf(
		 "  " );
	}
	libcnotify_printf(
	 "<" );

	if( internal_xml_tag->type == LIBFWEVT_XML_TAG_TYPE_NODE )
	{
		if( libcdata_array_get_number_of_entries(
		     internal_xml_tag->attributes_array,
		     &number_of_attributes,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of attributes.",
			 function );

			return( -1 );
		}
		if( libcdata_array_get_number_of_entries(
		     internal_xml_tag->elements_array,
		     &number_of_elements,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of elements.",
			 function );

			return( -1 );
		}
		if( libfwevt_xml_tag_debug_print_name_string(
		     internal_xml_tag,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print name.",
			 function );

			return( -1 );
		}
		if( number_of_attributes > 0 )
		{
			for( attribute_index = 0;
			     attribute_index < number_of_attributes;
			     attribute_index++ )
			{
				if( libcdata_array_get_entry_by_index(
				     internal_xml_tag->attributes_array,
				     attribute_index,
				     (intptr_t **) &internal_attribute_xml_tag,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve attribute: %d.",
					 function,
					 attribute_index );

					return( -1 );
				}
				if( internal_attribute_xml_tag == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: missing attribute: %d.",
					 function,
					 attribute_index );

					return( -1 );
				}
				libcnotify_printf(
				 " " );

				if( libfwevt_xml_tag_debug_print_name_string(
				     internal_attribute_xml_tag,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
					 "%s: unable to print attribute name.",
					 function );

					return( -1 );
				}
				libcnotify_printf(
				 "=\"" );

				if( libfwevt_xml_value_get_type(
				     internal_attribute_xml_tag->value,
				     &value_type,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve attribute value type.",
					 function );

					return( -1 );
				}
				if( libfwevt_debug_print_xml_value(
				     internal_attribute_xml_tag->value,
				     0,
				     0,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
					 "%s: unable to print attribute value.",
					 function );

					return( -1 );
				}
				libcnotify_printf(
				 "\"" );
			}
		}
		if( internal_xml_tag->value != NULL )
		{
			if( libfwevt_xml_tag_get_utf8_xml_value_string_size(
			     internal_xml_tag,
			     &value_string_size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve UTF-8 string size of element value.",
				 function );

				return( -1 );
			}
			if( value_string_size > 0 )
			{
				libcnotify_printf(
				 ">" );

				if( libfwevt_xml_tag_debug_print_value_string(
				     internal_xml_tag,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
					 "%s: unable to print element value.",
					 function );

					return( -1 );
				}
				libcnotify_printf(
				 "</" );

				if( libfwevt_xml_tag_debug_print_name_string(
				     internal_xml_tag,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
					 "%s: unable to print name.",
					 function );

					return( -1 );
				}
			}
			else
			{
				libcnotify_printf(
				 "/" );
			}
		}
		else if( number_of_elements > 0 )
		{
			libcnotify_printf(
			 ">\n" );

			for( element_index = 0;
			     element_index < number_of_elements;
			     element_index++ )
			{
				if( libcdata_array_get_entry_by_index(
				     internal_xml_tag->elements_array,
				     element_index,
				     (intptr_t **) &element_xml_tag,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve element: %d.",
					 function,
					 element_index );

					return( -1 );
				}
				if( libfwevt_xml_tag_debug_print(
				     element_xml_tag,
				     xml_tag_level + 1,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
					 "%s: unable to print element: %d.",
					 function,
					 element_index );

					return( -1 );
				}
			}
			for( indentation_iterator = 0;
			     indentation_iterator < xml_tag_level;
			     indentation_iterator++ )
			{
				libcnotify_printf(
				 "  " );
			}
			libcnotify_printf(
			 "</" );

			if( libfwevt_xml_tag_debug_print_name_string(
			     internal_xml_tag,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print name.",
				 function );

				return( -1 );
			}
		}
		else
		{
			libcnotify_printf(
			 "/" );
		}
	}
	else if( internal_xml_tag->type == LIBFWEVT_XML_TAG_TYPE_CDATA )
	{
		libcnotify_printf(
		 "![CDATA[" );

		if( libfwevt_debug_print_xml_value(
		     internal_xml_tag->value,
		     0,
		     0,
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
		libcnotify_printf(
		 "]]" );
	}
	else if( internal_xml_tag->type == LIBFWEVT_XML_TAG_TYPE_PI )
	{
		libcnotify_printf(
		 "?" );

		if( libfwevt_xml_tag_debug_print_name_string(
		     internal_xml_tag,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print name.",
			 function );

			return( -1 );
		}
		libcnotify_printf(
		 " " );

		if( libfwevt_debug_print_xml_value(
		     internal_xml_tag->value,
		     0,
		     0,
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
		libcnotify_printf(
		 "?" );
	}
	libcnotify_printf(
	 ">\n" );

	return( 1 );
}

/* Debug prints the XML tag name
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_name_debug_print(
     libfwevt_xml_tag_t *xml_tag,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_name_debug_print";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	libcnotify_printf(
	 "%s: name\t\t\t\t\t: ",
	 function );

	if( libfwevt_xml_tag_debug_print_name_string(
	     internal_xml_tag,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print name.",
		 function );

		return( -1 );
	}
	libcnotify_printf(
	 "\n" );

	libcnotify_printf(
	 "\n" );

	return( 1 );
}

/* Debug prints the XML tag value
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_tag_value_debug_print(
     libfwevt_xml_tag_t *xml_tag,
     int value_entry_index,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_tag_t *internal_xml_tag = NULL;
	static char *function                         = "libfwevt_xml_tag_value_debug_print";

	if( xml_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid XML tag.",
		 function );

		return( -1 );
	}
	internal_xml_tag = (libfwevt_internal_xml_tag_t *) xml_tag;

	libcnotify_printf(
	 "%s: value\t\t\t\t: ",
	 function );

	if( libfwevt_debug_print_xml_value(
	     internal_xml_tag->value,
	     value_entry_index,
	     0,
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
	libcnotify_printf(
	 "\n" );

	libcnotify_printf(
	 "\n" );

	return( 1 );
}

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

