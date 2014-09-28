/*
 * Library to support the Windows XML Event Log (EVTX) data types
 *
 * Copyright (c) 2011-2014, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modisoy
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

#if !defined( _LIBFWEVT_H )
#define _LIBFWEVT_H

#include <libfwevt/definitions.h>
#include <libfwevt/error.h>
#include <libfwevt/extern.h>
#include <libfwevt/features.h>
#include <libfwevt/types.h>

#include <stdio.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBFWEVT_EXTERN \
const char *libfwevt_get_version(
             void );

/* -------------------------------------------------------------------------
 * Error functions
 * ------------------------------------------------------------------------- */

/* Frees an error
 */
LIBFWEVT_EXTERN \
void libfwevt_error_free(
      libfwevt_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the amount of printed characters if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_error_fprint(
     libfwevt_error_t *error,
     FILE *stream );

/* Prints a descriptive string of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the amount of printed characters if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_error_sprint(
     libfwevt_error_t *error,
     char *string,
     size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the amount of printed characters if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_error_backtrace_fprint(
     libfwevt_error_t *error,
     FILE *stream );

/* Prints a backtrace of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the amount of printed characters if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_error_backtrace_sprint(
     libfwevt_error_t *error,
     char *string,
     size_t size );

#if defined( __cplusplus )
}
#endif

#endif

