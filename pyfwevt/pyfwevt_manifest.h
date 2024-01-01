/*
 * Python object wrapper of libfwevt_manifest_t
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

#if !defined( _PYFWEVT_MANIFEST_H )
#define _PYFWEVT_MANIFEST_H

#include <common.h>
#include <types.h>

#include "pyfwevt_libfwevt.h"
#include "pyfwevt_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfwevt_manifest pyfwevt_manifest_t;

struct pyfwevt_manifest
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libfwevt manifest
	 */
	libfwevt_manifest_t *manifest;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyfwevt_manifest_object_methods[];
extern PyTypeObject pyfwevt_manifest_type_object;

PyObject *pyfwevt_manifest_new(
           libfwevt_manifest_t *manifest,
           PyObject *parent_object );

int pyfwevt_manifest_init(
     pyfwevt_manifest_t *pyfwevt_manifest,
     PyObject *arguments,
     PyObject *keywords );

void pyfwevt_manifest_free(
      pyfwevt_manifest_t *pyfwevt_manifest );

PyObject *pyfwevt_manifest_copy_from_byte_stream(
           pyfwevt_manifest_t *pyfwevt_manifest,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfwevt_manifest_get_number_of_providers(
           pyfwevt_manifest_t *pyfwevt_manifest,
           PyObject *arguments );

PyObject *pyfwevt_manifest_get_provider_by_index(
           PyObject *pyfwevt_manifest,
           int provider_index );

PyObject *pyfwevt_manifest_get_provider(
           pyfwevt_manifest_t *pyfwevt_manifest,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfwevt_manifest_get_providers(
           pyfwevt_manifest_t *pyfwevt_manifest,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFWEVT_MANIFEST_H ) */

