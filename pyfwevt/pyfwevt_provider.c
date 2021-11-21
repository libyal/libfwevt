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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyfwevt_provider.h"
#include "pyfwevt_error.h"
#include "pyfwevt_libcerror.h"
#include "pyfwevt_libfwevt.h"
#include "pyfwevt_python.h"
#include "pyfwevt_unused.h"

PyMethodDef pyfwevt_provider_object_methods[] = {

	{ "get_number_of_channels",
	  (PyCFunction) pyfwevt_provider_get_number_of_channels,
	  METH_NOARGS,
	  "get_number_of_channels() -> Integer\n"
	  "\n"
	  "Retrieves the number of channels." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyfwevt_provider_object_get_set_definitions[] = {

	{ "number_of_channels",
	  (getter) pyfwevt_provider_get_number_of_channels,
	  (setter) 0,
	  "The number of channels.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyfwevt_provider_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyfwevt.provider",
	/* tp_basicsize */
	sizeof( pyfwevt_provider_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyfwevt_provider_free,
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
	"pyfwevt provider object (wraps libfwevt_provider_t)",
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
	pyfwevt_provider_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyfwevt_provider_object_get_set_definitions,
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
	(initproc) pyfwevt_provider_init,
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
	0
};

/* Creates a new provider object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_new(
           libfwevt_provider_t *provider,
           PyObject *parent_object )
{
	pyfwevt_provider_t *pyfwevt_provider = NULL;
	static char *function                = "pyfwevt_provider_new";

	if( provider == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid provider.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pyfwevt_provider = PyObject_New(
	                    struct pyfwevt_provider,
	                    &pyfwevt_provider_type_object );

	if( pyfwevt_provider == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize provider.",
		 function );

		goto on_error;
	}
	pyfwevt_provider->provider      = provider;
	pyfwevt_provider->parent_object = parent_object;

	if( pyfwevt_provider->parent_object != NULL )
	{
		Py_IncRef(
		 pyfwevt_provider->parent_object );
	}
	return( (PyObject *) pyfwevt_provider );

on_error:
	if( pyfwevt_provider != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyfwevt_provider );
	}
	return( NULL );
}

/* Initializes an provider object
 * Returns 0 if successful or -1 on error
 */
int pyfwevt_provider_init(
     pyfwevt_provider_t *pyfwevt_provider )
{
	static char *function = "pyfwevt_provider_init";

	if( pyfwevt_provider == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	/* Make sure libfwevt provider is set to NULL
	 */
	pyfwevt_provider->provider = NULL;

	PyErr_Format(
	 PyExc_NotImplementedError,
	 "%s: initialize of provider not supported.",
	 function );

	return( -1 );
}

/* Frees an provider object
 */
void pyfwevt_provider_free(
      pyfwevt_provider_t *pyfwevt_provider )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyfwevt_provider_free";
	int result                  = 0;

	if( pyfwevt_provider == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid provider.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyfwevt_provider );

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
	if( pyfwevt_provider->provider != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libfwevt_provider_free(
		          &( pyfwevt_provider->provider ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyfwevt_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libfwevt provider.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	if( pyfwevt_provider->parent_object != NULL )
	{
		Py_DecRef(
		 pyfwevt_provider->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyfwevt_provider );
}

/* Retrieves the number of channels
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_number_of_channels(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwevt_provider_get_number_of_channels";
	int number_of_channels   = 0;
	int result               = 0;

	PYFWEVT_UNREFERENCED_PARAMETER( arguments )

	if( pyfwevt_provider == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid provider.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_provider_get_number_of_channels(
	          pyfwevt_provider->provider,
	          &number_of_channels,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of channels.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_channels );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_channels );
#endif
	return( integer_object );
}

