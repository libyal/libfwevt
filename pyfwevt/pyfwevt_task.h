/*
 * Python object wrapper of libfwevt_task_t
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

#if !defined( _PYFWEVT_TASK_H )
#define _PYFWEVT_TASK_H

#include <common.h>
#include <types.h>

#include "pyfwevt_libfwevt.h"
#include "pyfwevt_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfwevt_task pyfwevt_task_t;

struct pyfwevt_task
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libfwevt task
	 */
	libfwevt_task_t *task;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyfwevt_task_object_methods[];
extern PyTypeObject pyfwevt_task_type_object;

PyObject *pyfwevt_task_new(
           libfwevt_task_t *task,
           PyObject *parent_object );

int pyfwevt_task_init(
     pyfwevt_task_t *pyfwevt_task,
     PyObject *arguments,
     PyObject *keywords );

void pyfwevt_task_free(
      pyfwevt_task_t *pyfwevt_task );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFWEVT_TASK_H ) */

