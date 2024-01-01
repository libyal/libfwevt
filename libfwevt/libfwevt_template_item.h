/*
 * Template item functions
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

#if !defined( _LIBFWEVT_TEMPLATE_ITEM_H )
#define _LIBFWEVT_TEMPLATE_ITEM_H

#include <common.h>
#include <types.h>

#include "libfwevt_extern.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfwevt_internal_template_item libfwevt_internal_template_item_t;

struct libfwevt_internal_template_item
{
	/* The input data type
	 */
	uint8_t input_data_type;

	/* The output data type
	 */
	uint8_t output_data_type;

	/* The number of values
	 */
	uint16_t number_of_values;

	/* The value data size
	 */
	uint16_t value_data_size;

	/* The name offset
	 */
	uint32_t name_offset;

	/* The name
	 */
	uint8_t *name;

	/* The name size
	 */
	uint16_t name_size;
};

int libfwevt_template_item_initialize(
     libfwevt_template_item_t **template_item,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_item_free(
     libfwevt_template_item_t **template_item,
     libcerror_error_t **error );

int libfwevt_internal_template_item_free(
     libfwevt_internal_template_item_t **internal_template_item,
     libcerror_error_t **error );

int libfwevt_template_item_read_data(
     libfwevt_template_item_t *template_item,
     const uint8_t *data,
     size_t data_size,
     size_t data_offset,
     size_t template_data_offset,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_item_get_input_data_type(
     libfwevt_template_item_t *template_item,
     uint8_t *input_data_type,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_item_get_output_data_type(
     libfwevt_template_item_t *template_item,
     uint8_t *output_data_type,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_item_get_number_of_values(
     libfwevt_template_item_t *template_item,
     uint16_t *number_of_values,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_item_get_value_data_size(
     libfwevt_template_item_t *template_item,
     uint16_t *value_data_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_item_get_utf8_name_size(
     libfwevt_template_item_t *template_item,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_item_get_utf8_name(
     libfwevt_template_item_t *template_item,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_item_get_utf16_name_size(
     libfwevt_template_item_t *template_item,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_item_get_utf16_name(
     libfwevt_template_item_t *template_item,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWEVT_TEMPLATE_ITEM_H ) */

