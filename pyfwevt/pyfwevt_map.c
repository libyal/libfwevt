/*
 * Python object wrapper of libfwevt_map_t
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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyfwevt_error.h"
#include "pyfwevt_libcerror.h"
#include "pyfwevt_libfwevt.h"
#include "pyfwevt_map.h"
#include "pyfwevt_python.h"
#include "pyfwevt_unused.h"

PyMethodDef pyfwevt_map_object_methods[] = {

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyfwevt_map_object_get_set_definitions[] = {

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyfwevt_map_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyfwevt.map",
	/* tp_basicsize */
	sizeof( pyfwevt_map_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyfwevt_map_free,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	0,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
	/* tp_flags */
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pyfwevt map object (wraps libfwevt_map_t)",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	0,
	/* tp_iternext */
	0,
	/* tp_methods */
	pyfwevt_map_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyfwevt_map_object_get_set_definitions,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pyfwevt_map_init,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0,
	/* tp_version_tag */
	0
};

/* Creates a new map object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_map_new(
           libfwevt_map_t *map,
           PyObject *parent_object )
{
	pyfwevt_map_t *pyfwevt_map = NULL;
	static char *function      = "pyfwevt_map_new";

	if( map == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid map.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pyfwevt_map = PyObject_New(
	               struct pyfwevt_map,
	               &pyfwevt_map_type_object );

	if( pyfwevt_map == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize map.",
		 function );

		goto on_error;
	}
	pyfwevt_map->map           = map;
	pyfwevt_map->parent_object = parent_object;

	if( pyfwevt_map->parent_object != NULL )
	{
		Py_IncRef(
		 pyfwevt_map->parent_object );
	}
	return( (PyObject *) pyfwevt_map );

on_error:
	if( pyfwevt_map != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyfwevt_map );
	}
	return( NULL );
}

/* Initializes a map object
 * Returns 0 if successful or -1 on error
 */
int pyfwevt_map_init(
     pyfwevt_map_t *pyfwevt_map,
     PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED,
     PyObject *keywords PYFWEVT_ATTRIBUTE_UNUSED )
{
	static char *function = "pyfwevt_map_init";

	PYFWEVT_UNREFERENCED_PARAMETER( arguments )
	PYFWEVT_UNREFERENCED_PARAMETER( keywords )

	if( pyfwevt_map == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid map.",
		 function );

		return( -1 );
	}
	/* Make sure libfwevt map is set to NULL
	 */
	pyfwevt_map->map = NULL;

	PyErr_Format(
	 PyExc_NotImplementedError,
	 "%s: initialize of map not supported.",
	 function );

	return( -1 );
}

/* Frees a map object
 */
void pyfwevt_map_free(
      pyfwevt_map_t *pyfwevt_map )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyfwevt_map_free";
	int result                  = 0;

	if( pyfwevt_map == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid map.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyfwevt_map );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( pyfwevt_map->map != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libfwevt_map_free(
		          &( pyfwevt_map->map ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyfwevt_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libfwevt map.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	if( pyfwevt_map->parent_object != NULL )
	{
		Py_DecRef(
		 pyfwevt_map->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyfwevt_map );
}

