/*
 * Channel functions
 *
 * Copyright (C) 2011-2022, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBFWEVT_CHANNEL_H )
#define _LIBFWEVT_CHANNEL_H

#include <common.h>
#include <types.h>

#include "libfwevt_extern.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfwevt_internal_channel libfwevt_internal_channel_t;

struct libfwevt_internal_channel
{
	/* The identifier
	 */
	uint32_t identifier;
};

int libfwevt_channel_initialize(
     libfwevt_channel_t **channel,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_channel_free(
     libfwevt_channel_t **channel,
     libcerror_error_t **error );

int libfwevt_internal_channel_free(
     libfwevt_internal_channel_t **internal_channel,
     libcerror_error_t **error );

int libfwevt_channel_read_data(
     libfwevt_channel_t *channel,
     const uint8_t *data,
     size_t data_size,
     size_t data_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWEVT_CHANNEL_H ) */

