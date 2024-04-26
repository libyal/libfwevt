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

#if !defined( _LIBFWEVT_XML_TAG_H )
#define _LIBFWEVT_XML_TAG_H

#include <common.h>
#include <types.h>

#include "libfwevt_extern.h"
#include "libfwevt_libcdata.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfwevt_internal_xml_tag libfwevt_internal_xml_tag_t;

struct libfwevt_internal_xml_tag
{
	/* The type
	 */
	uint8_t type;

	/* The name
	 */
	uint8_t *name;

	/* The name size
	 */
	size_t name_size;

	/* The value
	 */
	libfwevt_xml_value_t *value;

	/* The attributes array
	 */
	libcdata_array_t *attributes_array;

	/* The elements array
	 */
	libcdata_array_t *elements_array;

	/* The flags
	 */
	uint8_t flags;
};

int libfwevt_xml_tag_initialize(
     libfwevt_xml_tag_t **xml_tag,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_tag_free(
     libfwevt_xml_tag_t **xml_tag,
     libcerror_error_t **error );

int libfwevt_internal_xml_tag_free(
     libfwevt_internal_xml_tag_t **internal_xml_tag,
     libcerror_error_t **error );

int libfwevt_xml_tag_set_type(
     libfwevt_xml_tag_t *xml_tag,
     uint8_t type,
     libcerror_error_t **error );

int libfwevt_xml_tag_set_name_data(
     libfwevt_xml_tag_t *xml_tag,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfwevt_xml_tag_set_value_type(
     libfwevt_xml_tag_t *xml_tag,
     int value_type,
     libcerror_error_t **error );

int libfwevt_xml_tag_set_value_format_flags(
     libfwevt_xml_tag_t *xml_tag,
     uint32_t format_flags,
     libcerror_error_t **error );

int libfwevt_xml_tag_set_value_data(
     libfwevt_xml_tag_t *xml_tag,
     const uint8_t *data,
     size_t data_size,
     int encoding,
     libcerror_error_t **error );

int libfwevt_xml_tag_append_value_data(
     libfwevt_xml_tag_t *xml_tag,
     const uint8_t *data,
     size_t data_size,
     int encoding,
     int *value_entry_index,
     libcerror_error_t **error );

ssize_t libfwevt_xml_tag_set_value_strings_array(
         libfwevt_xml_tag_t *xml_tag,
         const uint8_t *strings_array_data,
         size_t strings_array_data_size,
         int encoding,
         libcerror_error_t **error );

int libfwevt_xml_tag_append_attribute(
     libfwevt_xml_tag_t *xml_tag,
     libfwevt_xml_tag_t *attribute_xml_tag,
     libcerror_error_t **error );

int libfwevt_xml_tag_append_element(
     libfwevt_xml_tag_t *xml_tag,
     libfwevt_xml_tag_t *element_xml_tag,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_utf8_name_size(
     libfwevt_xml_tag_t *xml_tag,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_utf8_name(
     libfwevt_xml_tag_t *xml_tag,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_utf16_name_size(
     libfwevt_xml_tag_t *xml_tag,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_utf16_name(
     libfwevt_xml_tag_t *xml_tag,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_value(
     libfwevt_xml_tag_t *xml_tag,
     libfwevt_xml_value_t **xml_value,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_utf8_value_size(
     libfwevt_xml_tag_t *xml_tag,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_utf8_value(
     libfwevt_xml_tag_t *xml_tag,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_utf16_value_size(
     libfwevt_xml_tag_t *xml_tag,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_utf16_value(
     libfwevt_xml_tag_t *xml_tag,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_number_of_attributes(
     libfwevt_xml_tag_t *xml_tag,
     int *number_of_attributes,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_attribute_by_index(
     libfwevt_xml_tag_t *xml_tag,
     int attribute_index,
     libfwevt_xml_tag_t **attribute_xml_tag,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_attribute_by_utf8_name(
     libfwevt_xml_tag_t *xml_tag,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfwevt_xml_tag_t **attribute_xml_tag,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_attribute_by_utf16_name(
     libfwevt_xml_tag_t *xml_tag,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfwevt_xml_tag_t **attribute_xml_tag,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_number_of_elements(
     libfwevt_xml_tag_t *xml_tag,
     int *number_of_elements,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_element_by_index(
     libfwevt_xml_tag_t *xml_tag,
     int element_index,
     libfwevt_xml_tag_t **element_xml_tag,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_element_by_utf8_name(
     libfwevt_xml_tag_t *xml_tag,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfwevt_xml_tag_t **element_xml_tag,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_element_by_utf16_name(
     libfwevt_xml_tag_t *xml_tag,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfwevt_xml_tag_t **element_xml_tag,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_flags(
     libfwevt_xml_tag_t *xml_tag,
     uint8_t *flags,
     libcerror_error_t **error );

int libfwevt_xml_tag_set_flags(
     libfwevt_xml_tag_t *xml_tag,
     uint8_t flags,
     libcerror_error_t **error );

int libfwevt_xml_tag_get_utf8_xml_value_string_size(
     libfwevt_internal_xml_tag_t *internal_xml_tag,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libfwevt_xml_tag_get_utf8_xml_value_string_with_index(
     libfwevt_internal_xml_tag_t *internal_xml_tag,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     libcerror_error_t **error );

int libfwevt_xml_tag_get_utf8_xml_string_size(
     libfwevt_xml_tag_t *xml_tag,
     int xml_tag_level,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libfwevt_xml_tag_get_utf8_xml_string_with_index(
     libfwevt_xml_tag_t *xml_tag,
     int xml_tag_level,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     libcerror_error_t **error );

int libfwevt_xml_tag_get_utf16_xml_value_string_size(
     libfwevt_internal_xml_tag_t *internal_xml_tag,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libfwevt_xml_tag_get_utf16_xml_value_string_with_index(
     libfwevt_internal_xml_tag_t *internal_xml_tag,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     libcerror_error_t **error );

int libfwevt_xml_tag_get_utf16_xml_string_size(
     libfwevt_xml_tag_t *xml_tag,
     int xml_tag_level,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libfwevt_xml_tag_get_utf16_xml_string_with_index(
     libfwevt_xml_tag_t *xml_tag,
     int xml_tag_level,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     libcerror_error_t **error );

#if defined( HAVE_DEBUG_OUTPUT )

int libfwevt_xml_tag_debug_print_name_string(
     libfwevt_internal_xml_tag_t *internal_xml_tag,
     libcerror_error_t **error );

int libfwevt_xml_tag_debug_print_value_string(
     libfwevt_internal_xml_tag_t *internal_xml_tag,
     libcerror_error_t **error );

int libfwevt_xml_tag_debug_print(
     libfwevt_xml_tag_t *xml_tag,
     int xml_tag_level,
     libcerror_error_t **error );

int libfwevt_xml_tag_name_debug_print(
     libfwevt_xml_tag_t *xml_tag,
     libcerror_error_t **error );

int libfwevt_xml_tag_value_debug_print(
     libfwevt_xml_tag_t *xml_tag,
     int value_entry_index,
     libcerror_error_t **error );

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWEVT_XML_TAG_H ) */

