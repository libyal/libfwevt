/*
 * Template functions
 *
 * Copyright (C) 2011-2018, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBFWEVT_INTERNAL_TEMPLATE_H )
#define _LIBFWEVT_INTERNAL_TEMPLATE_H

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

	/* The instance values offset
	 */
	uint32_t instance_values_offset;

	/* The values array
	 */
	libcdata_array_t *values_array;

	/* The ASCII codepage
	 */
	int ascii_codepage;
};

LIBFWEVT_EXTERN \
int libfwevt_template_initialize(
     libfwevt_template_t **template,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_free(
     libfwevt_template_t **template,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_read(
     libfwevt_template_t *template,
     const uint8_t *data,
     size_t data_size,
     size_t data_offset,
     libcerror_error_t **error );

int libfwevt_template_read_header(
     libfwevt_internal_template_t *internal_template,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfwevt_template_read_instance_values(
     libfwevt_internal_template_t *internal_template,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_read_xml_document(
     libfwevt_template_t *template,
     libfwevt_xml_document_t *xml_document,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_set_ascii_codepage(
     libfwevt_template_t *template,
     int ascii_codepage,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_get_data(
     libfwevt_template_t *template,
     const uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_set_data(
     libfwevt_template_t *template,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_get_offset(
     libfwevt_template_t *template,
     uint32_t *offset,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_set_offset(
     libfwevt_template_t *template,
     uint32_t offset,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_template_get_size(
     libfwevt_template_t *template,
     uint32_t *size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWEVT_INTERNAL_TEMPLATE_H ) */

