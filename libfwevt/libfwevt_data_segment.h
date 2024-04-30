/*
 * Data segment functions
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

#if !defined( _LIBFWEVT_DATA_SEGMENT_H )
#define _LIBFWEVT_DATA_SEGMENT_H

#include <common.h>
#include <types.h>

#include "libfwevt_libcerror.h"
#include "libfwevt_libfdatetime.h"
#include "libfwevt_libfguid.h"
#include "libfwevt_libfwnt.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfwevt_data_segment libfwevt_data_segment_t;

struct libfwevt_data_segment
{
	/* The data
	 */
	uint8_t *data;

	/* The data size
	 */
	size_t data_size;

	/* The cached value type
	 */
	uint8_t cached_value_type;

	/* The cached value
	 */
	union
	{
		/* Cached 64-bit value
		 */
		uint64_t value_64bit;

		/* Cached GUID value
		 */
		libfguid_identifier_t *guid;

		/* Cached FILETIME value
		 */
		libfdatetime_filetime_t *filetime;

		/* Cached SYSTEMTIME value
		 */
		libfdatetime_systemtime_t *systemtime;

		/* Cached NT security identifier value
		 */
		libfwnt_security_identifier_t *security_identifier;
	};
};

int libfwevt_data_segment_initialize(
     libfwevt_data_segment_t **data_segment,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfwevt_data_segment_free(
     libfwevt_data_segment_t **data_segment,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWEVT_DATA_SEGMENT_H ) */

