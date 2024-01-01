/*
 * The internal extern definition
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

#if !defined( _LIBFWEVT_INTERNAL_EXTERN_H )
#define _LIBFWEVT_INTERNAL_EXTERN_H

#include <common.h>

/* Define HAVE_LOCAL_LIBFWEVT for local use of libfwevt
 */
#if !defined( HAVE_LOCAL_LIBFWEVT )

#include <libfwevt/extern.h>

#if defined( __CYGWIN__ ) || defined( __MINGW32__ )
#define LIBFWEVT_EXTERN_VARIABLE	extern
#else
#define LIBFWEVT_EXTERN_VARIABLE	LIBFWEVT_EXTERN
#endif

#else
#define LIBFWEVT_EXTERN		/* extern */
#define LIBFWEVT_EXTERN_VARIABLE	extern

#endif /* !defined( HAVE_LOCAL_LIBFWEVT ) */

#endif /* !defined( _LIBFWEVT_INTERNAL_EXTERN_H ) */

