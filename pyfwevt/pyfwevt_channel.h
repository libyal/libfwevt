/*
 * Python object wrapper of libfwevt_channel_t
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

#if !defined( _PYFWEVT_CHANNEL_H )
#define _PYFWEVT_CHANNEL_H

#include <common.h>
#include <types.h>

#include "pyfwevt_libfwevt.h"
#include "pyfwevt_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfwevt_channel pyfwevt_channel_t;

struct pyfwevt_channel
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libfwevt channel
	 */
	libfwevt_channel_t *channel;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyfwevt_channel_object_methods[];
extern PyTypeObject pyfwevt_channel_type_object;

PyObject *pyfwevt_channel_new(
           libfwevt_channel_t *channel,
           PyObject *parent_object );

int pyfwevt_channel_init(
     pyfwevt_channel_t *pyfwevt_channel,
     PyObject *arguments,
     PyObject *keywords );

void pyfwevt_channel_free(
      pyfwevt_channel_t *pyfwevt_channel );

PyObject *pyfwevt_channel_get_identifier(
           pyfwevt_channel_t *pyfwevt_channel,
           PyObject *arguments );

PyObject *pyfwevt_channel_get_name(
           pyfwevt_channel_t *pyfwevt_channel,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFWEVT_CHANNEL_H ) */

