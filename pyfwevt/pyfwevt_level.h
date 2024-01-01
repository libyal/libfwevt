/*
 * Python object wrapper of libfwevt_level_t
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

#if !defined( _PYFWEVT_LEVEL_H )
#define _PYFWEVT_LEVEL_H

#include <common.h>
#include <types.h>

#include "pyfwevt_libfwevt.h"
#include "pyfwevt_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfwevt_level pyfwevt_level_t;

struct pyfwevt_level
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libfwevt level
	 */
	libfwevt_level_t *level;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyfwevt_level_object_methods[];
extern PyTypeObject pyfwevt_level_type_object;

PyObject *pyfwevt_level_new(
           libfwevt_level_t *level,
           PyObject *parent_object );

int pyfwevt_level_init(
     pyfwevt_level_t *pyfwevt_level,
     PyObject *arguments,
     PyObject *keywords );

void pyfwevt_level_free(
      pyfwevt_level_t *pyfwevt_level );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFWEVT_LEVEL_H ) */

