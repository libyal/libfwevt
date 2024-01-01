/*
 * Python object wrapper of libfwevt_level_t
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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyfwevt_error.h"
#include "pyfwevt_level.h"
#include "pyfwevt_libcerror.h"
#include "pyfwevt_libfwevt.h"
#include "pyfwevt_python.h"
#include "pyfwevt_unused.h"

PyMethodDef pyfwevt_level_object_methods[] = {

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyfwevt_level_object_get_set_definitions[] = {

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyfwevt_level_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyfwevt.level",
	/* tp_basicsize */
	sizeof( pyfwevt_level_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyfwevt_level_free,
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
	"pyfwevt level object (wraps libfwevt_level_t)",
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
	pyfwevt_level_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyfwevt_level_object_get_set_definitions,
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
	(initproc) pyfwevt_level_init,
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

/* Creates a new level object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_level_new(
           libfwevt_level_t *level,
           PyObject *parent_object )
{
	pyfwevt_level_t *pyfwevt_level = NULL;
	static char *function          = "pyfwevt_level_new";

	if( level == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid level.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pyfwevt_level = PyObject_New(
	                 struct pyfwevt_level,
	                 &pyfwevt_level_type_object );

	if( pyfwevt_level == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize level.",
		 function );

		goto on_error;
	}
	pyfwevt_level->level         = level;
	pyfwevt_level->parent_object = parent_object;

	if( pyfwevt_level->parent_object != NULL )
	{
		Py_IncRef(
		 pyfwevt_level->parent_object );
	}
	return( (PyObject *) pyfwevt_level );

on_error:
	if( pyfwevt_level != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyfwevt_level );
	}
	return( NULL );
}

/* Initializes a level object
 * Returns 0 if successful or -1 on error
 */
int pyfwevt_level_init(
     pyfwevt_level_t *pyfwevt_level,
     PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED,
     PyObject *keywords PYFWEVT_ATTRIBUTE_UNUSED )
{
	static char *function = "pyfwevt_level_init";

	if( pyfwevt_level == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid level.",
		 function );

		return( -1 );
	}
	/* Make sure libfwevt level is set to NULL
	 */
	pyfwevt_level->level = NULL;

	PyErr_Format(
	 PyExc_NotImplementedError,
	 "%s: initialize of level not supported.",
	 function );

	return( -1 );
}

/* Frees a level object
 */
void pyfwevt_level_free(
      pyfwevt_level_t *pyfwevt_level )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyfwevt_level_free";
	int result                  = 0;

	if( pyfwevt_level == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid level.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyfwevt_level );

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
	if( pyfwevt_level->level != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libfwevt_level_free(
		          &( pyfwevt_level->level ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyfwevt_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libfwevt level.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	if( pyfwevt_level->parent_object != NULL )
	{
		Py_DecRef(
		 pyfwevt_level->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyfwevt_level );
}

