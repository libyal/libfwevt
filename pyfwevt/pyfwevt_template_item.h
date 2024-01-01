/*
 * Python object wrapper of libfwevt_template_item_t
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

#if !defined( _PYFWEVT_TEMPLATE_ITEM_H )
#define _PYFWEVT_TEMPLATE_ITEM_H

#include <common.h>
#include <types.h>

#include "pyfwevt_libfwevt.h"
#include "pyfwevt_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfwevt_template_item pyfwevt_template_item_t;

struct pyfwevt_template_item
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libfwevt template_item
	 */
	libfwevt_template_item_t *template_item;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyfwevt_template_item_object_methods[];
extern PyTypeObject pyfwevt_template_item_type_object;

PyObject *pyfwevt_template_item_new(
           libfwevt_template_item_t *template_item,
           PyObject *parent_object );

int pyfwevt_template_item_init(
     pyfwevt_template_item_t *pyfwevt_template_item,
     PyObject *arguments,
     PyObject *keywords );

void pyfwevt_template_item_free(
      pyfwevt_template_item_t *pyfwevt_template_item );

PyObject *pyfwevt_template_item_get_input_data_type(
           pyfwevt_template_item_t *pyfwevt_template_item,
           PyObject *arguments );

PyObject *pyfwevt_template_item_get_output_data_type(
           pyfwevt_template_item_t *pyfwevt_template_item,
           PyObject *arguments );

PyObject *pyfwevt_template_item_get_number_of_values(
           pyfwevt_template_item_t *pyfwevt_template_item,
           PyObject *arguments );

PyObject *pyfwevt_template_item_get_value_data_size(
           pyfwevt_template_item_t *pyfwevt_template_item,
           PyObject *arguments );

PyObject *pyfwevt_template_item_get_name(
           pyfwevt_template_item_t *pyfwevt_template_item,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFWEVT_TEMPLATE_ITEM_H ) */

