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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyfwevt_error.h"
#include "pyfwevt_libcerror.h"
#include "pyfwevt_libfwevt.h"
#include "pyfwevt_manifest.h"
#include "pyfwevt_provider.h"
#include "pyfwevt_providers.h"
#include "pyfwevt_python.h"
#include "pyfwevt_unused.h"

PyMethodDef pyfwevt_manifest_object_methods[] = {

	{ "copy_from_byte_stream",
	  (PyCFunction) pyfwevt_manifest_copy_from_byte_stream,
	  METH_VARARGS | METH_KEYWORDS,
	  "copy_from_byte_stream(byte_stream)\n"
	  "\n"
	  "Copies the manifest from the byte stream." },

	{ "get_number_of_providers",
	  (PyCFunction) pyfwevt_manifest_get_number_of_providers,
	  METH_NOARGS,
	  "get_number_of_providers() -> Integer\n"
	  "\n"
	  "Retrieves the number of providers." },

	{ "get_provider",
	  (PyCFunction) pyfwevt_manifest_get_provider,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_provider(provider_index) -> Object\n"
	  "\n"
	  "Retrieves the provider specified by the index." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyfwevt_manifest_object_get_set_definitions[] = {

	{ "number_of_providers",
	  (getter) pyfwevt_manifest_get_number_of_providers,
	  (setter) 0,
	  "The number of providers.",
	  NULL },

	{ "providers",
	  (getter) pyfwevt_manifest_get_providers,
	  (setter) 0,
	  "The providers.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyfwevt_manifest_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyfwevt.manifest",
	/* tp_basicsize */
	sizeof( pyfwevt_manifest_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyfwevt_manifest_free,
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
	"pyfwevt manifest object (wraps libfwevt_manifest_t)",
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
	pyfwevt_manifest_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyfwevt_manifest_object_get_set_definitions,
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
	(initproc) pyfwevt_manifest_init,
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

/* Creates a new manifest object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_manifest_new(
           libfwevt_manifest_t *manifest,
           PyObject *parent_object )
{
	pyfwevt_manifest_t *pyfwevt_manifest = NULL;
	static char *function                = "pyfwevt_manifest_new";

	if( manifest == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid manifest.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pyfwevt_manifest = PyObject_New(
	                    struct pyfwevt_manifest,
	                    &pyfwevt_manifest_type_object );

	if( pyfwevt_manifest == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize manifest.",
		 function );

		goto on_error;
	}
	pyfwevt_manifest->manifest = manifest;
	pyfwevt_manifest->parent_object       = parent_object;

	if( pyfwevt_manifest->parent_object != NULL )
	{
		Py_IncRef(
		 pyfwevt_manifest->parent_object );
	}
	return( (PyObject *) pyfwevt_manifest );

on_error:
	if( pyfwevt_manifest != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyfwevt_manifest );
	}
	return( NULL );
}

/* Initializes a manifest object
 * Returns 0 if successful or -1 on error
 */
int pyfwevt_manifest_init(
     pyfwevt_manifest_t *pyfwevt_manifest,
     PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED,
     PyObject *keywords PYFWEVT_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwevt_manifest_init";

	PYFWEVT_UNREFERENCED_PARAMETER( arguments )
	PYFWEVT_UNREFERENCED_PARAMETER( keywords )

	if( pyfwevt_manifest == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid manifest.",
		 function );

		return( -1 );
	}
	/* Make sure libfwevt manifest is set to NULL
	 */
	pyfwevt_manifest->manifest = NULL;

	if( libfwevt_manifest_initialize(
	     &( pyfwevt_manifest->manifest ),
	     &error ) != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize manifest.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 0 );
}

/* Frees a manifest object
 */
void pyfwevt_manifest_free(
      pyfwevt_manifest_t *pyfwevt_manifest )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyfwevt_manifest_free";
	int result                  = 0;

	if( pyfwevt_manifest == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid manifest.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyfwevt_manifest );

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
	if( pyfwevt_manifest->manifest != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libfwevt_manifest_free(
		          &( pyfwevt_manifest->manifest ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyfwevt_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libfwevt manifest.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	if( pyfwevt_manifest->parent_object != NULL )
	{
		Py_DecRef(
		 pyfwevt_manifest->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyfwevt_manifest );
}

/* Copies the manifest from a byte stream
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_manifest_copy_from_byte_stream(
           pyfwevt_manifest_t *pyfwevt_manifest,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *bytes_object      = NULL;
	libcerror_error_t *error    = NULL;
	const char *byte_stream     = NULL;
	static char *function       = "pyfwevt_manifest_copy_from_byte_stream";
	static char *keyword_list[] = { "byte_stream", NULL };
	Py_ssize_t byte_stream_size = 0;
	int result                  = 0;

	if( pyfwevt_manifest == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid manifest.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O",
	     keyword_list,
	     &bytes_object ) == 0 )
	{
		return( NULL );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	result = PyObject_IsInstance(
	          bytes_object,
	          (PyObject *) &PyBytes_Type );
#else
	result = PyObject_IsInstance(
	          bytes_object,
	          (PyObject *) &PyString_Type );
#endif
	if( result == -1 )
	{
		pyfwevt_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if object is of type bytes.",
		 function );

		return( NULL );
	}
	else if( result == 0 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported bytes object type",
		 function );

		return( NULL );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	byte_stream = PyBytes_AsString(
	               bytes_object );

	byte_stream_size = PyBytes_Size(
	                    bytes_object );
#else
	byte_stream = PyString_AsString(
	               bytes_object );

	byte_stream_size = PyString_Size(
	                    bytes_object );
#endif
	if( ( byte_stream_size < 0 )
	 || ( byte_stream_size > (Py_ssize_t) SSIZE_MAX ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid byte stream size value out of bounds.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_manifest_read(
	          pyfwevt_manifest->manifest,
	          (uint8_t *) byte_stream,
	          (size_t) byte_stream_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to copy manifest from byte stream.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the number of providers
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_manifest_get_number_of_providers(
           pyfwevt_manifest_t *pyfwevt_manifest,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwevt_manifest_get_number_of_providers";
	int number_of_providers  = 0;
	int result               = 0;

	PYFWEVT_UNREFERENCED_PARAMETER( arguments )

	if( pyfwevt_manifest == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid manifest.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_manifest_get_number_of_providers(
	          pyfwevt_manifest->manifest,
	          &number_of_providers,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of providers.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_providers );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_providers );
#endif
	return( integer_object );
}

/* Retrieves a specific provider by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_manifest_get_provider_by_index(
           PyObject *pyfwevt_manifest,
           int provider_index )
{
	PyObject *provider_object     = NULL;
	libcerror_error_t *error      = NULL;
	libfwevt_provider_t *provider = NULL;
	static char *function         = "pyfwevt_manifest_get_provider_by_index";
	int result                    = 0;

	if( pyfwevt_manifest == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid manifest.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_manifest_get_provider_by_index(
	          ( (pyfwevt_manifest_t *) pyfwevt_manifest )->manifest,
	          provider_index,
	          &provider,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve provider: %d.",
		 function,
		 provider_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	provider_object = pyfwevt_provider_new(
	                   provider,
	                   pyfwevt_manifest );

	if( provider_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create provider object.",
		 function );

		goto on_error;
	}
	return( provider_object );

on_error:
	if( provider != NULL )
	{
		libfwevt_provider_free(
		 &provider,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific provider
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_manifest_get_provider(
           pyfwevt_manifest_t *pyfwevt_manifest,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *provider_object   = NULL;
	static char *keyword_list[] = { "provider_index", NULL };
	int provider_index          = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &provider_index ) == 0 )
	{
		return( NULL );
	}
	provider_object = pyfwevt_manifest_get_provider_by_index(
	                   (PyObject *) pyfwevt_manifest,
	                   provider_index );

	return( provider_object );
}

/* Retrieves a sequence and iterator object for the providers
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_manifest_get_providers(
           pyfwevt_manifest_t *pyfwevt_manifest,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyfwevt_manifest_get_providers";
	int number_of_providers   = 0;
	int result                = 0;

	PYFWEVT_UNREFERENCED_PARAMETER( arguments )

	if( pyfwevt_manifest == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid manifest.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_manifest_get_number_of_providers(
	          pyfwevt_manifest->manifest,
	          &number_of_providers,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of providers.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pyfwevt_providers_new(
	                   (PyObject *) pyfwevt_manifest,
	                   &pyfwevt_manifest_get_provider_by_index,
	                   number_of_providers );

	if( sequence_object == NULL )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to create sequence object.",
		 function );

		return( NULL );
	}
	return( sequence_object );
}

