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

#include "libfwevt_data_segment.h"
#include "libfwevt_extern.h"
#include "libfwevt_libcdata.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_libcnotify.h"
#include "libfwevt_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfwevt_internal_xml_value libfwevt_internal_xml_value_t;

struct libfwevt_internal_xml_value
{
	/* The value type
	 */
	uint8_t value_type;

	/* The data segments
	 */
	libcdata_array_t *data_segments;

	/* The data size
	 */
	size_t data_size;
};

int libfwevt_xml_value_initialize(
     libfwevt_xml_value_t **xml_value,
     uint8_t value_type,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_value_free(
     libfwevt_xml_value_t **xml_value,
     libcerror_error_t **error );

int libfwevt_internal_xml_value_free(
     libfwevt_internal_xml_value_t **internal_xml_value,
     libcerror_error_t **error );

int libfwevt_xml_value_get_type(
     libfwevt_xml_value_t *xml_value,
     uint8_t *value_type,
     libcerror_error_t **error );

int libfwevt_xml_value_get_number_of_data_segments(
     libfwevt_xml_value_t *xml_value,
     int *number_of_data_segments,
     libcerror_error_t **error );

int libfwevt_internal_xml_value_get_data_segment_with_cached_value(
     libfwevt_internal_xml_value_t *internal_xml_value,
     int data_segment_index,
     libfwevt_data_segment_t **data_segment,
     libcerror_error_t **error );

int libfwevt_xml_value_append_data_segment(
     libfwevt_xml_value_t *xml_value,
     const uint8_t *data,
     size_t data_size,
     int *data_segment_index,
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
int libfwevt_value_get_data_as_8bit_integer(
     libfwevt_xml_value_t *xml_value,
     uint8_t *value_8bit,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_value_get_data_as_32bit_integer(
     libfwevt_xml_value_t *xml_value,
     uint32_t *value_32bit,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_value_get_data_as_64bit_integer(
     libfwevt_xml_value_t *xml_value,
     uint64_t *value_64bit,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_value_get_data_as_filetime(
     libfwevt_xml_value_t *xml_value,
     uint64_t *filetime,
     libcerror_error_t **error );

int libfwevt_internal_xml_value_get_data_segment_as_utf8_string_size(
     libfwevt_internal_xml_value_t *internal_xml_value,
     int data_segment_index,
     libfwevt_data_segment_t *data_segment,
     size_t *utf8_string_size,
     uint8_t escape_characters,
     libcerror_error_t **error );

int libfwevt_internal_xml_value_get_data_segment_as_utf8_string(
     libfwevt_internal_xml_value_t *internal_xml_value,
     int data_segment_index,
     libfwevt_data_segment_t *data_segment,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     uint8_t escape_characters,
     libcerror_error_t **error );

int libfwevt_internal_xml_value_get_data_as_utf8_string_size(
     libfwevt_internal_xml_value_t *internal_xml_value,
     size_t *utf8_string_size,
     uint8_t escape_characters,
     libcerror_error_t **error );

int libfwevt_internal_xml_value_get_data_as_utf8_string_with_index(
     libfwevt_internal_xml_value_t *internal_xml_value,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     uint8_t escape_characters,
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

LIBFWEVT_EXTERN \
int libfwevt_xml_value_get_data_as_utf8_string_size(
     libfwevt_xml_value_t *xml_value,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_value_get_data_as_utf8_string(
     libfwevt_xml_value_t *xml_value,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int libfwevt_internal_xml_value_get_data_segment_as_utf16_string_size(
     libfwevt_internal_xml_value_t *internal_xml_value,
     int data_segment_index,
     libfwevt_data_segment_t *data_segment,
     size_t *utf16_string_size,
     uint8_t escape_characters,
     libcerror_error_t **error );

int libfwevt_internal_xml_value_get_data_segment_as_utf16_string(
     libfwevt_internal_xml_value_t *internal_xml_value,
     int data_segment_index,
     libfwevt_data_segment_t *data_segment,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     uint8_t escape_characters,
     libcerror_error_t **error );

int libfwevt_internal_xml_value_get_data_as_utf16_string_size(
     libfwevt_internal_xml_value_t *internal_xml_value,
     size_t *utf16_string_size,
     uint8_t escape_characters,
     libcerror_error_t **error );

int libfwevt_internal_xml_value_get_data_as_utf16_string_with_index(
     libfwevt_internal_xml_value_t *internal_xml_value,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     uint8_t escape_characters,
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

LIBFWEVT_EXTERN \
int libfwevt_xml_value_get_data_as_utf16_string_size(
     libfwevt_xml_value_t *xml_value,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_value_get_data_as_utf16_string(
     libfwevt_xml_value_t *xml_value,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( HAVE_DEBUG_OUTPUT )

int libfwevt_xml_value_debug_print(
     libfwevt_xml_value_t *xml_value,
     uint8_t escape_characters,
     libcerror_error_t **error );

int libfwevt_xml_value_debug_print_data_segment(
     libfwevt_xml_value_t *xml_value,
     int data_segment_index,
     uint8_t escape_characters,
     libcerror_error_t **error );

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWEVT_XML_VALUE_H ) */

