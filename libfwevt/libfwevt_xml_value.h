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

#if !defined( _LIBFWEVT_XML_VALUE_H )
#define _LIBFWEVT_XML_VALUE_H

#include <common.h>
#include <types.h>

#include "libfwevt_extern.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_libfvalue.h"
#include "libfwevt_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfwevt_internal_xml_value libfwevt_internal_xml_value_t;

struct libfwevt_internal_xml_value
{
	/* The value type
	 */
	int value_type;

	/* The value (value)
	 */
	libfvalue_value_t *value;
};

int libfwevt_xml_value_initialize(
     libfwevt_xml_value_t **xml_value,
     int type,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_value_free(
     libfwevt_xml_value_t **xml_value,
     libcerror_error_t **error );

int libfwevt_internal_xml_value_free(
     libfwevt_internal_xml_value_t **internal_xml_value,
     libcerror_error_t **error );

int libfwevt_xml_value_set_data(
     libfwevt_xml_value_t *xml_value,
     const uint8_t *data,
     size_t data_size,
     int encoding,
     uint8_t flags,
     libcerror_error_t **error );

int libfwevt_xml_value_set_format_flags(
     libfwevt_xml_value_t *xml_value,
     uint32_t format_flags,
     libcerror_error_t **error );

int libfwevt_xml_value_append_data(
     libfwevt_xml_value_t *xml_value,
     int *value_entry_index,
     const uint8_t *data,
     size_t data_size,
     int encoding,
     libcerror_error_t **error );

ssize_t libfwevt_xml_value_type_set_data_string(
         libfwevt_xml_value_t *xml_value,
         const uint8_t *data,
         size_t data_size,
         int encoding,
         uint8_t flags,
         libcerror_error_t **error );

int libfwevt_xml_value_get_type(
     libfwevt_xml_value_t *xml_value,
     int *value_type,
     libcerror_error_t **error );

int libfwevt_xml_value_get_number_of_value_entries(
     libfwevt_xml_value_t *xml_value,
     int *number_of_value_entries,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_value_get_data_size(
     libfwevt_xml_value_t *xml_value,
     size_t *data_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_value_copy_data(
     libfwevt_xml_value_t *xml_value,
     uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_value_copy_to_8bit(
     libfwevt_xml_value_t *xml_value,
     uint8_t *value_8bit,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_value_copy_to_32bit(
     libfwevt_xml_value_t *xml_value,
     uint32_t *value_32bit,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_value_copy_to_64bit(
     libfwevt_xml_value_t *xml_value,
     uint64_t *value_64bit,
     libcerror_error_t **error );

int libfwevt_xml_value_get_utf8_string_size_with_index(
     libfwevt_xml_value_t *xml_value,
     int value_entry_index,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libfwevt_xml_value_copy_to_utf8_string_with_index(
     libfwevt_xml_value_t *xml_value,
     int value_entry_index,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_value_get_utf8_string_size(
     libfwevt_xml_value_t *xml_value,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_value_copy_to_utf8_string(
     libfwevt_xml_value_t *xml_value,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int libfwevt_xml_value_get_utf16_string_size_with_index(
     libfwevt_xml_value_t *xml_value,
     int value_entry_index,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libfwevt_xml_value_copy_to_utf16_string_with_index(
     libfwevt_xml_value_t *xml_value,
     int value_entry_index,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_value_get_utf16_string_size(
     libfwevt_xml_value_t *xml_value,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_value_copy_to_utf16_string(
     libfwevt_xml_value_t *xml_value,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( HAVE_DEBUG_OUTPUT )

int libfwevt_debug_print_xml_value(
     libfwevt_xml_value_t *xml_value,
     int value_entry_index,
     uint8_t flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWEVT_XML_VALUE_H ) */

