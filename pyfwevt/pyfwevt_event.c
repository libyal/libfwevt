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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyfwevt_error.h"
#include "pyfwevt_event.h"
#include "pyfwevt_libcerror.h"
#include "pyfwevt_libfwevt.h"
#include "pyfwevt_python.h"
#include "pyfwevt_unused.h"

PyMethodDef pyfwevt_event_object_methods[] = {

	{ "get_identifier",
	  (PyCFunction) pyfwevt_event_get_identifier,
	  METH_NOARGS,
	  "get_identifier() -> Integer\n"
	  "\n"
	  "Retrieves the identifier." },

	{ "get_version",
	  (PyCFunction) pyfwevt_event_get_version,
	  METH_NOARGS,
	  "get_version() -> Integer or None\n"
	  "\n"
	  "Retrieves the version." },

	{ "get_message_identifier",
	  (PyCFunction) pyfwevt_event_get_message_identifier,
	  METH_NOARGS,
	  "get_message_identifier() -> Integer\n"
	  "\n"
	  "Retrieves the message identifier." },

	{ "get_template_offset",
	  (PyCFunction) pyfwevt_event_get_template_offset,
	  METH_NOARGS,
	  "get_template_offset() -> Integer\n"
	  "\n"
	  "Retrieves the template offset." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyfwevt_event_object_get_set_definitions[] = {

	{ "identifier",
	  (getter) pyfwevt_event_get_identifier,
	  (setter) 0,
	  "The identifier.",
	  NULL },

	{ "version",
	  (getter) pyfwevt_event_get_version,
	  (setter) 0,
	  "The version.",
	  NULL },

	{ "message_identifier",
	  (getter) pyfwevt_event_get_message_identifier,
	  (setter) 0,
	  "The message identifier.",
	  NULL },

	{ "template_offset",
	  (getter) pyfwevt_event_get_template_offset,
	  (setter) 0,
	  "The template offset.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyfwevt_event_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyfwevt.event",
	/* tp_basicsize */
	sizeof( pyfwevt_event_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyfwevt_event_free,
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
	"pyfwevt event object (wraps libfwevt_event_t)",
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
	pyfwevt_event_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyfwevt_event_object_get_set_definitions,
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
	(initproc) pyfwevt_event_init,
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

/* Creates a new event object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_event_new(
           libfwevt_event_t *event,
           PyObject *parent_object )
{
	pyfwevt_event_t *pyfwevt_event = NULL;
	static char *function          = "pyfwevt_event_new";

	if( event == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid event.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pyfwevt_event = PyObject_New(
	                 struct pyfwevt_event,
	                 &pyfwevt_event_type_object );

	if( pyfwevt_event == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize event.",
		 function );

		goto on_error;
	}
	pyfwevt_event->event         = event;
	pyfwevt_event->parent_object = parent_object;

	if( pyfwevt_event->parent_object != NULL )
	{
		Py_IncRef(
		 pyfwevt_event->parent_object );
	}
	return( (PyObject *) pyfwevt_event );

on_error:
	if( pyfwevt_event != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyfwevt_event );
	}
	return( NULL );
}

/* Initializes an event object
 * Returns 0 if successful or -1 on error
 */
int pyfwevt_event_init(
     pyfwevt_event_t *pyfwevt_event,
     PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED,
     PyObject *keywords PYFWEVT_ATTRIBUTE_UNUSED )
{
	static char *function = "pyfwevt_event_init";

	PYFWEVT_UNREFERENCED_PARAMETER( arguments )
	PYFWEVT_UNREFERENCED_PARAMETER( keywords )

	if( pyfwevt_event == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid event.",
		 function );

		return( -1 );
	}
	/* Make sure libfwevt event is set to NULL
	 */
	pyfwevt_event->event = NULL;

	PyErr_Format(
	 PyExc_NotImplementedError,
	 "%s: initialize of event not supported.",
	 function );

	return( -1 );
}

/* Frees an event object
 */
void pyfwevt_event_free(
      pyfwevt_event_t *pyfwevt_event )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyfwevt_event_free";
	int result                  = 0;

	if( pyfwevt_event == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid event.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyfwevt_event );

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
	if( pyfwevt_event->event != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libfwevt_event_free(
		          &( pyfwevt_event->event ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyfwevt_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libfwevt event.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	if( pyfwevt_event->parent_object != NULL )
	{
		Py_DecRef(
		 pyfwevt_event->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyfwevt_event );
}

/* Retrieves the identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_event_get_identifier(
           pyfwevt_event_t *pyfwevt_event,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwevt_event_get_identifier";
	uint32_t value_32bit     = 0;
	int result               = 0;

	PYFWEVT_UNREFERENCED_PARAMETER( arguments )

	if( pyfwevt_event == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid event.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_event_get_identifier(
	          pyfwevt_event->event,
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

/* Retrieves the version
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_event_get_version(
           pyfwevt_event_t *pyfwevt_event,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwevt_event_get_version";
	uint8_t version          = 0;
	int result               = 0;

	PYFWEVT_UNREFERENCED_PARAMETER( arguments )

	if( pyfwevt_event == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid event.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_event_get_version(
	          pyfwevt_event->event,
	          &version,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve version.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) version );
#else
	integer_object = PyInt_FromLong(
	                  (long) version );
#endif
	return( integer_object );
}

/* Retrieves the message identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_event_get_message_identifier(
           pyfwevt_event_t *pyfwevt_event,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwevt_event_get_message_identifier";
	uint32_t value_32bit     = 0;
	int result               = 0;

	PYFWEVT_UNREFERENCED_PARAMETER( arguments )

	if( pyfwevt_event == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid event.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_event_get_message_identifier(
	          pyfwevt_event->event,
	          &value_32bit,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve message identifier.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = PyLong_FromUnsignedLong(
	                  (unsigned long) value_32bit );

	return( integer_object );
}

/* Retrieves the template offset
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_event_get_template_offset(
           pyfwevt_event_t *pyfwevt_event,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwevt_event_get_template_offset";
	uint32_t value_32bit     = 0;
	int result               = 0;

	PYFWEVT_UNREFERENCED_PARAMETER( arguments )

	if( pyfwevt_event == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid event.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_event_get_template_offset(
	          pyfwevt_event->event,
	          &value_32bit,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve template offset.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = PyLong_FromUnsignedLong(
	                  (unsigned long) value_32bit );

	return( integer_object );
}

