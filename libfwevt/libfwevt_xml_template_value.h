/*
 * Binary XML template value functions
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

#if !defined( _LIBFWEVT_INTERNAL_XML_TEMPLATE_VALUE_H )
#define _LIBFWEVT_INTERNAL_XML_TEMPLATE_VALUE_H

#include <common.h>
#include <types.h>

#include "libfwevt_libcerror.h"
#include "libfwevt_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfwevt_internal_xml_template_value libfwevt_internal_xml_template_value_t;

struct libfwevt_internal_xml_template_value
{
	/* The type
	 */
	uint8_t type;

	/* The offset
	 */
	size_t offset;

	/* The size
	 */
	uint16_t size;

	/* The flags
	 */
	uint8_t flags;
};

int libfwevt_xml_template_value_initialize(
     libfwevt_xml_template_value_t **xml_template_value,
     libcerror_error_t **error );

int libfwevt_xml_template_value_free(
     libfwevt_xml_template_value_t **xml_template_value,
     libcerror_error_t **error );

int libfwevt_xml_template_value_get_type(
     libfwevt_xml_template_value_t *xml_template_value,
     uint8_t *type,
     libcerror_error_t **error );

int libfwevt_xml_template_value_set_type(
     libfwevt_xml_template_value_t *xml_template_value,
     uint8_t type,
     libcerror_error_t **error );

int libfwevt_xml_template_value_get_offset(
     libfwevt_xml_template_value_t *xml_template_value,
     size_t *offset,
     libcerror_error_t **error );

int libfwevt_xml_template_value_set_offset(
     libfwevt_xml_template_value_t *xml_template_value,
     size_t offset,
     libcerror_error_t **error );

int libfwevt_xml_template_value_get_size(
     libfwevt_xml_template_value_t *xml_template_value,
     uint16_t *size,
     libcerror_error_t **error );

int libfwevt_xml_template_value_set_size(
     libfwevt_xml_template_value_t *xml_template_value,
     uint16_t size,
     libcerror_error_t **error );

int libfwevt_xml_template_value_get_flags(
     libfwevt_xml_template_value_t *xml_template_value,
     uint8_t *flags,
     libcerror_error_t **error );

int libfwevt_xml_template_value_set_flags(
     libfwevt_xml_template_value_t *xml_template_value,
     uint8_t flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWEVT_INTERNAL_XML_TEMPLATE_VALUE_H ) */

