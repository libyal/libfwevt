/*
 * Python object wrapper of libfwevt_provider_t
 *
 * Copyright (C) 2011-2021, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _PYFWEVT_PROVIDER_H )
#define _PYFWEVT_PROVIDER_H

#include <common.h>
#include <types.h>

#include "pyfwevt_libfwevt.h"
#include "pyfwevt_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfwevt_provider pyfwevt_provider_t;

struct pyfwevt_provider
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libfwevt provider
	 */
	libfwevt_provider_t *provider;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyfwevt_provider_object_methods[];
extern PyTypeObject pyfwevt_provider_type_object;

PyObject *pyfwevt_provider_new(
           libfwevt_provider_t *provider,
           PyObject *parent_object );

int pyfwevt_provider_init(
     pyfwevt_provider_t *pyfwevt_provider );

void pyfwevt_provider_free(
      pyfwevt_provider_t *pyfwevt_provider );

PyObject *pyfwevt_provider_get_number_of_channels(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments );

PyObject *pyfwevt_provider_get_channel_by_index(
           PyObject *pyfwevt_provider,
           int channel_index );

PyObject *pyfwevt_provider_get_channel(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfwevt_provider_get_channels(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments );

PyObject *pyfwevt_provider_get_number_of_events(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments );

PyObject *pyfwevt_provider_get_event_by_index(
           PyObject *pyfwevt_provider,
           int event_index );

PyObject *pyfwevt_provider_get_event(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfwevt_provider_get_events(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFWEVT_PROVIDER_H ) */

