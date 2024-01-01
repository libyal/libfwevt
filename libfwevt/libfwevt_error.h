/*
 * Error functions
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

#if !defined( _LIBFWEVT_INTERNAL_ERROR_H )
#define _LIBFWEVT_INTERNAL_ERROR_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if !defined( HAVE_LOCAL_LIBFWEVT )
#include <libfwevt/error.h>
#endif

#include "libfwevt_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBFWEVT )

LIBFWEVT_EXTERN \
void libfwevt_error_free(
      libfwevt_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_error_fprint(
     libfwevt_error_t *error,
     FILE *stream );

LIBFWEVT_EXTERN \
int libfwevt_error_sprint(
     libfwevt_error_t *error,
     char *string,
     size_t size );

LIBFWEVT_EXTERN \
int libfwevt_error_backtrace_fprint(
     libfwevt_error_t *error,
     FILE *stream );

LIBFWEVT_EXTERN \
int libfwevt_error_backtrace_sprint(
     libfwevt_error_t *error,
     char *string,
     size_t size );

#endif /* !defined( HAVE_LOCAL_LIBFWEVT ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWEVT_INTERNAL_ERROR_H ) */

