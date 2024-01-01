/*
 * Windows Event Log binary XML token functions
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

#if !defined( _LIBFWEVT_XML_TOKEN_H )
#define _LIBFWEVT_XML_TOKEN_H

#include <common.h>
#include <types.h>

#include "libfwevt_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfwevt_xml_token libfwevt_xml_token_t;

struct libfwevt_xml_token
{
	/* The type
	 */
	uint8_t type;

	/* The size
	 */
	size_t size;
};

int libfwevt_xml_token_initialize(
     libfwevt_xml_token_t **xml_token,
     libcerror_error_t **error );

int libfwevt_xml_token_free(
     libfwevt_xml_token_t **xml_token,
     libcerror_error_t **error );

int libfwevt_xml_token_read_data(
     libfwevt_xml_token_t *xml_token,
     const uint8_t *chunk_data,
     size_t chunk_data_size,
     size_t chunk_data_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWEVT_XML_TOKEN_H ) */

