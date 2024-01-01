/*
 * Template functions
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

#if !defined( _LIBFWEVT_TEMPLATE_H )
#define _LIBFWEVT_TEMPLATE_H

#include <common.h>
#include <types.h>

#include "libfwevt_extern.h"
#include "libfwevt_libcdata.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfwevt_internal_template libfwevt_internal_template_t;

struct libfwevt_internal_template
{
	/* The offset
	 */
	uint32_t offset;

	/* The data
	 */
	uint8_t *data;

	/* The data size
	 */
	size_t data_size;

	/* The size
	 */
	uint32_t size;

	/* The number of descriptors
	 */
	uint32_t number_of_descriptors;

	/* The number of names
	 */
	uint32_t number_of_names;

	/* The templat items offset
	 */
	uint32_t template_items_offset;

	/* The (template) identifier
	 * Contains a GUID
	 */
	uint8_t identifier[ 16 ];

	/* The items array
	 */
	libcdata_array_t *items_array;

	/* The values array
	 */
	libcdata_array_t *values_array;

	/* The ASCII codepage
	 */
	int ascii_codepage;

	/* Value to indicate the template is managed
	 */
	uint8_t is_managed;
};

LIBFWEVT_EXTERN \
int libfwevt_template_initialize(
     libfwevt_template_t **wevt_template,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_free(
     libfwevt_template_t **wevt_template,
     libcerror_error_t **error );

int libfwevt_internal_template_free(
     libfwevt_internal_template_t **internal_template,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_read(
     libfwevt_template_t *wevt_template,
     const uint8_t *data,
     size_t data_size,
     size_t data_offset,
     libcerror_error_t **error );

int libfwevt_template_read_header(
     libfwevt_internal_template_t *internal_template,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfwevt_template_read_template_items(
     libfwevt_internal_template_t *internal_template,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_read_xml_document(
     libfwevt_template_t *wevt_template,
     libfwevt_xml_document_t *xml_document,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_set_ascii_codepage(
     libfwevt_template_t *wevt_template,
     int ascii_codepage,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_get_data(
     libfwevt_template_t *wevt_template,
     const uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_set_data(
     libfwevt_template_t *wevt_template,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_get_offset(
     libfwevt_template_t *wevt_template,
     uint32_t *offset,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_set_offset(
     libfwevt_template_t *wevt_template,
     uint32_t offset,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_get_size(
     libfwevt_template_t *wevt_template,
     uint32_t *size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_get_identifier(
     libfwevt_template_t *wevt_template,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_get_number_of_items(
     libfwevt_template_t *wevt_template,
     int *number_of_items,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_get_item_by_index(
     libfwevt_template_t *wevt_template,
     int item_index,
     libfwevt_template_item_t **item,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWEVT_TEMPLATE_H ) */

