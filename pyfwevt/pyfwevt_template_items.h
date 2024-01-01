/*
 * Python object definition of the sequence and iterator object of template items
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

#if !defined( _PYFWEVT_TEMPLATE_ITEMS_H )
#define _PYFWEVT_TEMPLATE_ITEMS_H

#include <common.h>
#include <types.h>

#include "pyfwevt_libfwevt.h"
#include "pyfwevt_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfwevt_template_items pyfwevt_template_items_t;

struct pyfwevt_template_items
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

extern PyTypeObject pyfwevt_template_items_type_object;

PyObject *pyfwevt_template_items_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items );

int pyfwevt_template_items_init(
     pyfwevt_template_items_t *sequence_object,
     PyObject *arguments,
     PyObject *keywords );

void pyfwevt_template_items_free(
      pyfwevt_template_items_t *sequence_object );

Py_ssize_t pyfwevt_template_items_len(
            pyfwevt_template_items_t *sequence_object );

PyObject *pyfwevt_template_items_getitem(
           pyfwevt_template_items_t *sequence_object,
           Py_ssize_t item_index );

PyObject *pyfwevt_template_items_iter(
           pyfwevt_template_items_t *sequence_object );

PyObject *pyfwevt_template_items_iternext(
           pyfwevt_template_items_t *sequence_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFWEVT_TEMPLATE_ITEMS_H ) */

