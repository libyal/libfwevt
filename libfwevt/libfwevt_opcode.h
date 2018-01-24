/*
 * Opcode functions
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

#if !defined( _LIBFWEVT_INTERNAL_OPCODE_H )
#define _LIBFWEVT_INTERNAL_OPCODE_H

#include <common.h>
#include <types.h>

#include "libfwevt_extern.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfwevt_internal_opcode libfwevt_internal_opcode_t;

struct libfwevt_internal_opcode
{
	/* The identifier
	 */
	uint16_t identifier;
};

LIBFWEVT_EXTERN \
int libfwevt_opcode_initialize(
     libfwevt_opcode_t **opcode,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_opcode_free(
     libfwevt_opcode_t **opcode,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_opcode_read(
     libfwevt_opcode_t *opcode,
     const uint8_t *data,
     size_t data_size,
     size_t data_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWEVT_INTERNAL_OPCODE_H ) */

