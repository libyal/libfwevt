/*
 * Python object wrapper of libfwevt_map_t
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

#if !defined( _PYFWEVT_MAP_H )
#define _PYFWEVT_MAP_H

#include <common.h>
#include <types.h>

#include "pyfwevt_libfwevt.h"
#include "pyfwevt_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfwevt_map pyfwevt_map_t;

struct pyfwevt_map
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libfwevt map
	 */
	libfwevt_map_t *map;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyfwevt_map_object_methods[];
extern PyTypeObject pyfwevt_map_type_object;

PyObject *pyfwevt_map_new(
           libfwevt_map_t *map,
           PyObject *parent_object );

int pyfwevt_map_init(
     pyfwevt_map_t *pyfwevt_map );

void pyfwevt_map_free(
      pyfwevt_map_t *pyfwevt_map );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFWEVT_MAP_H ) */

