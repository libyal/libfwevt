/*
 * Python object wrapper of libfwevt_event_t
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

#if !defined( _PYFWEVT_EVENT_H )
#define _PYFWEVT_EVENT_H

#include <common.h>
#include <types.h>

#include "pyfwevt_libfwevt.h"
#include "pyfwevt_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfwevt_event pyfwevt_event_t;

struct pyfwevt_event
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libfwevt event
	 */
	libfwevt_event_t *event;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyfwevt_event_object_methods[];
extern PyTypeObject pyfwevt_event_type_object;

PyObject *pyfwevt_event_new(
           libfwevt_event_t *event,
           PyObject *parent_object );

int pyfwevt_event_init(
     pyfwevt_event_t *pyfwevt_event,
     PyObject *arguments,
     PyObject *keywords );

void pyfwevt_event_free(
      pyfwevt_event_t *pyfwevt_event );

PyObject *pyfwevt_event_get_identifier(
           pyfwevt_event_t *pyfwevt_event,
           PyObject *arguments );

PyObject *pyfwevt_event_get_version(
           pyfwevt_event_t *pyfwevt_event,
           PyObject *arguments );

PyObject *pyfwevt_event_get_message_identifier(
           pyfwevt_event_t *pyfwevt_event,
           PyObject *arguments );

PyObject *pyfwevt_event_get_template_offset(
           pyfwevt_event_t *pyfwevt_event,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFWEVT_EVENT_H ) */

