/*
 * Integer functions
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

#if !defined( _LIBFWEVT_INTEGER_H )
#define _LIBFWEVT_INTEGER_H

#include <common.h>
#include <types.h>

#include "libfwevt_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

int libfwevt_integer_copy_from_utf16_stream(
     uint64_t *integer_value,
     const uint8_t *utf16_stream,
     size_t utf16_stream_size,
     libcerror_error_t **error );

int libfwevt_integer_as_signed_decimal_get_string_size(
     uint64_t integer_value,
     uint8_t integer_size,
     size_t *string_size,
     libcerror_error_t **error );

int libfwevt_integer_as_signed_decimal_copy_to_utf8_string_with_index(
     uint64_t integer_value,
     uint8_t integer_size,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     libcerror_error_t **error );

int libfwevt_integer_as_signed_decimal_copy_to_utf16_string_with_index(
     uint64_t integer_value,
     uint8_t integer_size,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     libcerror_error_t **error );

int libfwevt_integer_as_unsigned_decimal_get_string_size(
     uint64_t integer_value,
     size_t *string_size,
     libcerror_error_t **error );

int libfwevt_integer_as_unsigned_decimal_copy_to_utf8_string_with_index(
     uint64_t integer_value,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     libcerror_error_t **error );

int libfwevt_integer_as_unsigned_decimal_copy_to_utf16_string_with_index(
     uint64_t integer_value,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     libcerror_error_t **error );

int libfwevt_integer_as_hexadecimal_copy_to_utf8_string_with_index(
     uint64_t integer_value,
     uint8_t integer_size,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     libcerror_error_t **error );

int libfwevt_integer_as_hexadecimal_copy_to_utf16_string_with_index(
     uint64_t integer_value,
     uint8_t integer_size,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWEVT_INTEGER_H ) */

