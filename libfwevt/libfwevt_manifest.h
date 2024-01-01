/*
 * Manifest functions
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

#if !defined( _LIBFWEVT_MANIFEST_H )
#define _LIBFWEVT_MANIFEST_H

#include <common.h>
#include <types.h>

#include "libfwevt_extern.h"
#include "libfwevt_libcdata.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfwevt_internal_manifest libfwevt_internal_manifest_t;

struct libfwevt_internal_manifest
{
	/* The major version
	 */
	uint16_t major_version;

	/* The minor version
	 */
	uint16_t minor_version;

	/* The providers array
	 */
	libcdata_array_t *providers_array;
};

LIBFWEVT_EXTERN \
int libfwevt_manifest_initialize(
     libfwevt_manifest_t **manifest,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_manifest_free(
     libfwevt_manifest_t **manifest,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_manifest_read(
     libfwevt_manifest_t *manifest,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_manifest_get_number_of_providers(
     libfwevt_manifest_t *manifest,
     int *number_of_providers,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_manifest_get_provider_by_index(
     libfwevt_manifest_t *manifest,
     int provider_index,
     libfwevt_provider_t **provider,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_manifest_get_provider_by_identifier(
     libfwevt_manifest_t *manifest,
     const uint8_t *provider_identifier,
     size_t provider_identifier_size,
     libfwevt_provider_t **provider,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWEVT_MANIFEST_H ) */

