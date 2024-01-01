/*
 * Binary XML template value functions
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
#include "libfwevt_types.h"
#include "libfwevt_xml_template_value.h"

/* Creates a binary XML template value
 * Make sure the value xml_template_value is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_template_value_initialize(
     libfwevt_xml_template_value_t **xml_template_value,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_template_value_t *internal_xml_template_value = NULL;
	static char *function                                               = "libfwevt_xml_template_value_initialize";

	if( xml_template_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML template value.",
		 function );

		return( -1 );
	}
	if( *xml_template_value != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid binary XML template value value already set.",
		 function );

		return( -1 );
	}
	internal_xml_template_value = memory_allocate_structure(
	                               libfwevt_internal_xml_template_value_t );

	if( internal_xml_template_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create binary XML template value.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_xml_template_value,
	     0,
	     sizeof( libfwevt_internal_xml_template_value_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear binary XML template value.",
		 function );


		goto on_error;
	}
	*xml_template_value = (libfwevt_xml_template_value_t *) internal_xml_template_value;

	return( 1 );

on_error:
	if( internal_xml_template_value != NULL )
	{
		memory_free(
		 internal_xml_template_value );
	}
	return( -1 );
}

/* Frees a binary XML template value
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_template_value_free(
     libfwevt_xml_template_value_t **xml_template_value,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_template_value_t *internal_xml_template_value = NULL;
	static char *function                                               = "libfwevt_xml_template_value_free";

	if( xml_template_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML template value.",
		 function );

		return( -1 );
	}
	if( *xml_template_value != NULL )
	{
		internal_xml_template_value = (libfwevt_internal_xml_template_value_t *) *xml_template_value;
		*xml_template_value         = NULL;

		memory_free(
		 internal_xml_template_value );
	}
	return( 1 );
}

/* Retrieves the type
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_template_value_get_type(
     libfwevt_xml_template_value_t *xml_template_value,
     uint8_t *type,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_template_value_t *internal_xml_template_value = NULL;
	static char *function                                               = "libfwevt_xml_template_value_get_type";

	if( xml_template_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML template value.",
		 function );

		return( -1 );
	}
	internal_xml_template_value = (libfwevt_internal_xml_template_value_t *) xml_template_value;

	if( type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid type.",
		 function );

		return( -1 );
	}
	*type = internal_xml_template_value->type;

	return( 1 );
}

/* Sets the type
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_template_value_set_type(
     libfwevt_xml_template_value_t *xml_template_value,
     uint8_t type,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_template_value_t *internal_xml_template_value = NULL;
	static char *function                                               = "libfwevt_xml_template_value_set_type";

	if( xml_template_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML template value.",
		 function );

		return( -1 );
	}
	internal_xml_template_value = (libfwevt_internal_xml_template_value_t *) xml_template_value;

	internal_xml_template_value->type = type;

	return( 1 );
}

/* Retrieves the offset
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_template_value_get_offset(
     libfwevt_xml_template_value_t *xml_template_value,
     size_t *offset,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_template_value_t *internal_xml_template_value = NULL;
	static char *function                                               = "libfwevt_xml_template_value_get_offset";

	if( xml_template_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML template value.",
		 function );

		return( -1 );
	}
	internal_xml_template_value = (libfwevt_internal_xml_template_value_t *) xml_template_value;

	if( offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
		 function );

		return( -1 );
	}
	*offset = internal_xml_template_value->offset;

	return( 1 );
}

/* Sets the offset
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_template_value_set_offset(
     libfwevt_xml_template_value_t *xml_template_value,
     size_t offset,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_template_value_t *internal_xml_template_value = NULL;
	static char *function                                               = "libfwevt_xml_template_value_set_offset";

	if( xml_template_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML template value.",
		 function );

		return( -1 );
	}
	internal_xml_template_value = (libfwevt_internal_xml_template_value_t *) xml_template_value;

	internal_xml_template_value->offset = offset;

	return( 1 );
}

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_template_value_get_size(
     libfwevt_xml_template_value_t *xml_template_value,
     uint16_t *size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_template_value_t *internal_xml_template_value = NULL;
	static char *function                                               = "libfwevt_xml_template_value_get_size";

	if( xml_template_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML template value.",
		 function );

		return( -1 );
	}
	internal_xml_template_value = (libfwevt_internal_xml_template_value_t *) xml_template_value;

	if( size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
	*size = internal_xml_template_value->size;

	return( 1 );
}

/* Sets the size
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_template_value_set_size(
     libfwevt_xml_template_value_t *xml_template_value,
     uint16_t size,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_template_value_t *internal_xml_template_value = NULL;
	static char *function                                               = "libfwevt_xml_template_value_set_size";

	if( xml_template_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML template value.",
		 function );

		return( -1 );
	}
	internal_xml_template_value = (libfwevt_internal_xml_template_value_t *) xml_template_value;

	internal_xml_template_value->size = size;

	return( 1 );
}

/* Retrieves the flags
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_template_value_get_flags(
     libfwevt_xml_template_value_t *xml_template_value,
     uint8_t *flags,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_template_value_t *internal_xml_template_value = NULL;
	static char *function                                               = "libfwevt_xml_template_value_get_flags";

	if( xml_template_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML template value.",
		 function );

		return( -1 );
	}
	internal_xml_template_value = (libfwevt_internal_xml_template_value_t *) xml_template_value;

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
	*flags = internal_xml_template_value->flags;

	return( 1 );
}

/* Sets the flags
 * Returns 1 if successful or -1 on error
 */
int libfwevt_xml_template_value_set_flags(
     libfwevt_xml_template_value_t *xml_template_value,
     uint8_t flags,
     libcerror_error_t **error )
{
	libfwevt_internal_xml_template_value_t *internal_xml_template_value = NULL;
	static char *function                                               = "libfwevt_xml_template_value_set_flags";

	if( xml_template_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML template value.",
		 function );

		return( -1 );
	}
	internal_xml_template_value = (libfwevt_internal_xml_template_value_t *) xml_template_value;

	internal_xml_template_value->flags = flags;

	return( 1 );
}

