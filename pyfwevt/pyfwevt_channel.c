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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyfwevt_channel.h"
#include "pyfwevt_error.h"
#include "pyfwevt_libcerror.h"
#include "pyfwevt_libfwevt.h"
#include "pyfwevt_python.h"
#include "pyfwevt_unused.h"

PyMethodDef pyfwevt_channel_object_methods[] = {

	{ "get_identifier",
	  (PyCFunction) pyfwevt_channel_get_identifier,
	  METH_NOARGS,
	  "get_identifier() -> Integer\n"
	  "\n"
	  "Retrieves the identifier." },

	{ "get_name",
	  (PyCFunction) pyfwevt_channel_get_name,
	  METH_NOARGS,
	  "get_name() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the name." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyfwevt_channel_object_get_set_definitions[] = {

	{ "identifier",
	  (getter) pyfwevt_channel_get_identifier,
	  (setter) 0,
	  "The identifier.",
	  NULL },

	{ "name",
	  (getter) pyfwevt_channel_get_name,
	  (setter) 0,
	  "The name.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyfwevt_channel_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyfwevt.channel",
	/* tp_basicsize */
	sizeof( pyfwevt_channel_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyfwevt_channel_free,
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
	"pyfwevt channel object (wraps libfwevt_channel_t)",
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
	pyfwevt_channel_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyfwevt_channel_object_get_set_definitions,
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
	(initproc) pyfwevt_channel_init,
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

/* Creates a new channel object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_channel_new(
           libfwevt_channel_t *channel,
           PyObject *parent_object )
{
	pyfwevt_channel_t *pyfwevt_channel = NULL;
	static char *function              = "pyfwevt_channel_new";

	if( channel == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid channel.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pyfwevt_channel = PyObject_New(
	                   struct pyfwevt_channel,
	                   &pyfwevt_channel_type_object );

	if( pyfwevt_channel == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize channel.",
		 function );

		goto on_error;
	}
	pyfwevt_channel->channel       = channel;
	pyfwevt_channel->parent_object = parent_object;

	if( pyfwevt_channel->parent_object != NULL )
	{
		Py_IncRef(
		 pyfwevt_channel->parent_object );
	}
	return( (PyObject *) pyfwevt_channel );

on_error:
	if( pyfwevt_channel != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyfwevt_channel );
	}
	return( NULL );
}

/* Initializes a channel object
 * Returns 0 if successful or -1 on error
 */
int pyfwevt_channel_init(
     pyfwevt_channel_t *pyfwevt_channel,
     PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED,
     PyObject *keywords PYFWEVT_ATTRIBUTE_UNUSED )
{
	static char *function = "pyfwevt_channel_init";

	PYFWEVT_UNREFERENCED_PARAMETER( arguments )
	PYFWEVT_UNREFERENCED_PARAMETER( keywords )

	if( pyfwevt_channel == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid channel.",
		 function );

		return( -1 );
	}
	/* Make sure libfwevt channel is set to NULL
	 */
	pyfwevt_channel->channel = NULL;

	PyErr_Format(
	 PyExc_NotImplementedError,
	 "%s: initialize of channel not supported.",
	 function );

	return( -1 );
}

/* Frees a channel object
 */
void pyfwevt_channel_free(
      pyfwevt_channel_t *pyfwevt_channel )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyfwevt_channel_free";
	int result                  = 0;

	if( pyfwevt_channel == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid channel.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyfwevt_channel );

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
	if( pyfwevt_channel->channel != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libfwevt_channel_free(
		          &( pyfwevt_channel->channel ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyfwevt_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libfwevt channel.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	if( pyfwevt_channel->parent_object != NULL )
	{
		Py_DecRef(
		 pyfwevt_channel->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyfwevt_channel );
}

/* Retrieves the identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_channel_get_identifier(
           pyfwevt_channel_t *pyfwevt_channel,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwevt_channel_get_identifier";
	uint32_t value_32bit     = 0;
	int result               = 0;

	PYFWEVT_UNREFERENCED_PARAMETER( arguments )

	if( pyfwevt_channel == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid channel.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_channel_get_identifier(
	          pyfwevt_channel->channel,
	          &value_32bit,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve identifier.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = PyLong_FromUnsignedLong(
	                  (unsigned long) value_32bit );

	return( integer_object );
}

/* Retrieves the name
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_channel_get_name(
           pyfwevt_channel_t *pyfwevt_channel,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwevt_channel_get_name";
	char *utf8_string        = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	PYFWEVT_UNREFERENCED_PARAMETER( arguments )

	if( pyfwevt_channel == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid channel.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_channel_get_utf8_name_size(
	          pyfwevt_channel->channel,
	          &utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to determine size of name as UTF-8 string.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( utf8_string_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	utf8_string = (char *) PyMem_Malloc(
	                        sizeof( char ) * utf8_string_size );

	if( utf8_string == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 string.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_channel_get_utf8_name(
	          pyfwevt_channel->channel,
	          (uint8_t *) utf8_string,
	          utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve name as UTF-8 string.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8 otherwise it makes
	 * the end of string character is part of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 utf8_string,
	                 (Py_ssize_t) utf8_string_size - 1,
	                 NULL );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 string into Unicode object.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 utf8_string );

	return( string_object );

on_error:
	if( utf8_string != NULL )
	{
		PyMem_Free(
		 utf8_string );
	}
	return( NULL );
}

