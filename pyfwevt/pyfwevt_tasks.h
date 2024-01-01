/*
 * Python object definition of the sequence and iterator object of tasks
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

#if !defined( _PYFWEVT_TASKS_H )
#define _PYFWEVT_TASKS_H

#include <common.h>
#include <types.h>

#include "pyfwevt_libfwevt.h"
#include "pyfwevt_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfwevt_tasks pyfwevt_tasks_t;

struct pyfwevt_tasks
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

extern PyTypeObject pyfwevt_tasks_type_object;

PyObject *pyfwevt_tasks_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items );

int pyfwevt_tasks_init(
     pyfwevt_tasks_t *sequence_object,
     PyObject *arguments,
     PyObject *keywords );

void pyfwevt_tasks_free(
      pyfwevt_tasks_t *sequence_object );

Py_ssize_t pyfwevt_tasks_len(
            pyfwevt_tasks_t *sequence_object );

PyObject *pyfwevt_tasks_getitem(
           pyfwevt_tasks_t *sequence_object,
           Py_ssize_t item_index );

PyObject *pyfwevt_tasks_iter(
           pyfwevt_tasks_t *sequence_object );

PyObject *pyfwevt_tasks_iternext(
           pyfwevt_tasks_t *sequence_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFWEVT_TASKS_H ) */

