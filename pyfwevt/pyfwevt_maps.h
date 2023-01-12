/*
 * Python object definition of the sequence and iterator object of maps
 *
 * Copyright (C) 2011-2023, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _PYFWEVT_MAPS_H )
#define _PYFWEVT_MAPS_H

#include <common.h>
#include <types.h>

#include "pyfwevt_libfwevt.h"
#include "pyfwevt_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfwevt_maps pyfwevt_maps_t;

struct pyfwevt_maps
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The parent object
	 */
	PyObject *parent_object;

	/* The get item by index callback function
	 */
	PyObject* (*get_item_by_index)(
	             PyObject *parent_object,
	             int index );

	/* The current index
	 */
	int current_index;

	/* The number of items
	 */
	int number_of_items;
};

extern PyTypeObject pyfwevt_maps_type_object;

PyObject *pyfwevt_maps_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items );

int pyfwevt_maps_init(
     pyfwevt_maps_t *sequence_object,
     PyObject *arguments,
     PyObject *keywords );

void pyfwevt_maps_free(
      pyfwevt_maps_t *sequence_object );

Py_ssize_t pyfwevt_maps_len(
            pyfwevt_maps_t *sequence_object );

PyObject *pyfwevt_maps_getitem(
           pyfwevt_maps_t *sequence_object,
           Py_ssize_t item_index );

PyObject *pyfwevt_maps_iter(
           pyfwevt_maps_t *sequence_object );

PyObject *pyfwevt_maps_iternext(
           pyfwevt_maps_t *sequence_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFWEVT_MAPS_H ) */

