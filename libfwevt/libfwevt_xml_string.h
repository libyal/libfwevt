/*
 * XML string functions
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

#if !defined( _LIBFWEVT_XML_STRING_H )
#define _LIBFWEVT_XML_STRING_H

#include <common.h>
#include <types.h>

#include "libfwevt_libcerror.h"
#include "libfwevt_libuna.h"

#if defined( __cplusplus )
extern "C" {
#endif

int libfwevt_utf8_xml_string_size_from_utf16_stream(
     const uint8_t *utf16_stream,
     size_t utf16_stream_size,
     int byte_order,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libfwevt_utf8_xml_string_with_index_copy_from_utf16_stream(
     libuna_utf8_character_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     const uint8_t *utf16_stream,
     size_t utf16_stream_size,
     int byte_order,
     libcerror_error_t **error );

int libfwevt_utf16_xml_string_size_from_utf16_stream(
     const uint8_t *utf16_stream,
     size_t utf16_stream_size,
     int byte_order,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libfwevt_utf16_xml_string_with_index_copy_from_utf16_stream(
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     const uint8_t *utf16_stream,
     size_t utf16_stream_size,
     int byte_order,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWEVT_XML_STRING_H ) */

