/*
 * Python object wrapper of libfwevt_provider_t
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
#include "pyfwevt_channels.h"
#include "pyfwevt_error.h"
#include "pyfwevt_event.h"
#include "pyfwevt_events.h"
#include "pyfwevt_guid.h"
#include "pyfwevt_keyword.h"
#include "pyfwevt_keywords.h"
#include "pyfwevt_level.h"
#include "pyfwevt_levels.h"
#include "pyfwevt_libcerror.h"
#include "pyfwevt_libfwevt.h"
#include "pyfwevt_map.h"
#include "pyfwevt_maps.h"
#include "pyfwevt_opcode.h"
#include "pyfwevt_opcodes.h"
#include "pyfwevt_provider.h"
#include "pyfwevt_python.h"
#include "pyfwevt_task.h"
#include "pyfwevt_tasks.h"
#include "pyfwevt_template.h"
#include "pyfwevt_templates.h"
#include "pyfwevt_unused.h"

PyMethodDef pyfwevt_provider_object_methods[] = {

	{ "get_identifier",
	  (PyCFunction) pyfwevt_provider_get_identifier,
	  METH_NOARGS,
	  "get_identifier() -> Unicode string\n"
	  "\n"
	  "Retrieves the identifier." },

	{ "get_number_of_channels",
	  (PyCFunction) pyfwevt_provider_get_number_of_channels,
	  METH_NOARGS,
	  "get_number_of_channels() -> Integer\n"
	  "\n"
	  "Retrieves the number of channels." },

	{ "get_channel",
	  (PyCFunction) pyfwevt_provider_get_channel,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_channel(channel_index) -> Object\n"
	  "\n"
	  "Retrieves the channel specified by the index." },

	{ "get_number_of_events",
	  (PyCFunction) pyfwevt_provider_get_number_of_events,
	  METH_NOARGS,
	  "get_number_of_events() -> Integer\n"
	  "\n"
	  "Retrieves the number of events." },

	{ "get_event",
	  (PyCFunction) pyfwevt_provider_get_event,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_event(event_index) -> Object\n"
	  "\n"
	  "Retrieves the event specified by the index." },

	{ "get_number_of_keywords",
	  (PyCFunction) pyfwevt_provider_get_number_of_keywords,
	  METH_NOARGS,
	  "get_number_of_keywords() -> Integer\n"
	  "\n"
	  "Retrieves the number of keywords." },

	{ "get_keyword",
	  (PyCFunction) pyfwevt_provider_get_keyword,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_keyword(keyword_index) -> Object\n"
	  "\n"
	  "Retrieves the keyword specified by the index." },

	{ "get_number_of_levels",
	  (PyCFunction) pyfwevt_provider_get_number_of_levels,
	  METH_NOARGS,
	  "get_number_of_levels() -> Integer\n"
	  "\n"
	  "Retrieves the number of levels." },

	{ "get_level",
	  (PyCFunction) pyfwevt_provider_get_level,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_level(level_index) -> Object\n"
	  "\n"
	  "Retrieves the level specified by the index." },

	{ "get_number_of_maps",
	  (PyCFunction) pyfwevt_provider_get_number_of_maps,
	  METH_NOARGS,
	  "get_number_of_maps() -> Integer\n"
	  "\n"
	  "Retrieves the number of maps." },

	{ "get_map",
	  (PyCFunction) pyfwevt_provider_get_map,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_map(map_index) -> Object\n"
	  "\n"
	  "Retrieves the map specified by the index." },

	{ "get_number_of_opcodes",
	  (PyCFunction) pyfwevt_provider_get_number_of_opcodes,
	  METH_NOARGS,
	  "get_number_of_opcodes() -> Integer or None\n"
	  "\n"
	  "Retrieves the template by offset." },

	{ "get_opcode",
	  (PyCFunction) pyfwevt_provider_get_opcode,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_opcode(opcode_index) -> Object\n"
	  "\n"
	  "Retrieves the opcode specified by the index." },

	{ "get_number_of_tasks",
	  (PyCFunction) pyfwevt_provider_get_number_of_tasks,
	  METH_NOARGS,
	  "get_number_of_tasks() -> Integer\n"
	  "\n"
	  "Retrieves the number of tasks." },

	{ "get_task",
	  (PyCFunction) pyfwevt_provider_get_task,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_task(task_index) -> Object\n"
	  "\n"
	  "Retrieves the task specified by the index." },

	{ "get_number_of_templates",
	  (PyCFunction) pyfwevt_provider_get_number_of_templates,
	  METH_NOARGS,
	  "get_number_of_templates() -> Integer\n"
	  "\n"
	  "Retrieves the number of templates." },

	{ "get_template",
	  (PyCFunction) pyfwevt_provider_get_template,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_template(template_index) -> Object\n"
	  "\n"
	  "Retrieves the template specified by the index." },

	{ "get_template_by_offset",
	  (PyCFunction) pyfwevt_provider_get_template_by_offset,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_template_by_offset(template_offset) -> Object or None\n"
	  "\n"
	  "Retrieves the template specified by the offset." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyfwevt_provider_object_get_set_definitions[] = {

	{ "identifier",
	  (getter) pyfwevt_provider_get_identifier,
	  (setter) 0,
	  "The identifier.",
	  NULL },

	{ "number_of_channels",
	  (getter) pyfwevt_provider_get_number_of_channels,
	  (setter) 0,
	  "The number of channels.",
	  NULL },

	{ "channels",
	  (getter) pyfwevt_provider_get_channels,
	  (setter) 0,
	  "The channels.",
	  NULL },

	{ "number_of_events",
	  (getter) pyfwevt_provider_get_number_of_events,
	  (setter) 0,
	  "The number of events.",
	  NULL },

	{ "events",
	  (getter) pyfwevt_provider_get_events,
	  (setter) 0,
	  "The events.",
	  NULL },

	{ "number_of_keywords",
	  (getter) pyfwevt_provider_get_number_of_keywords,
	  (setter) 0,
	  "The number of keywords.",
	  NULL },

	{ "keywords",
	  (getter) pyfwevt_provider_get_keywords,
	  (setter) 0,
	  "The keywords.",
	  NULL },

	{ "number_of_levels",
	  (getter) pyfwevt_provider_get_number_of_levels,
	  (setter) 0,
	  "The number of levels.",
	  NULL },

	{ "levels",
	  (getter) pyfwevt_provider_get_levels,
	  (setter) 0,
	  "The levels.",
	  NULL },

	{ "number_of_maps",
	  (getter) pyfwevt_provider_get_number_of_maps,
	  (setter) 0,
	  "The number of maps.",
	  NULL },

	{ "maps",
	  (getter) pyfwevt_provider_get_maps,
	  (setter) 0,
	  "The maps.",
	  NULL },

	{ "number_of_opcodes",
	  (getter) pyfwevt_provider_get_number_of_opcodes,
	  (setter) 0,
	  "The template by offset.",
	  NULL },

	{ "opcodes",
	  (getter) pyfwevt_provider_get_opcodes,
	  (setter) 0,
	  "The opcodes.",
	  NULL },

	{ "number_of_tasks",
	  (getter) pyfwevt_provider_get_number_of_tasks,
	  (setter) 0,
	  "The number of tasks.",
	  NULL },

	{ "tasks",
	  (getter) pyfwevt_provider_get_tasks,
	  (setter) 0,
	  "The tasks.",
	  NULL },

	{ "number_of_templates",
	  (getter) pyfwevt_provider_get_number_of_templates,
	  (setter) 0,
	  "The number of templates.",
	  NULL },

	{ "templates",
	  (getter) pyfwevt_provider_get_templates,
	  (setter) 0,
	  "The templates.",
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
	0,
	/* tp_version_tag */
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

/* Initializes a provider object
 * Returns 0 if successful or -1 on error
 */
int pyfwevt_provider_init(
     pyfwevt_provider_t *pyfwevt_provider,
     PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED,
     PyObject *keywords PYFWEVT_ATTRIBUTE_UNUSED )
{
	static char *function = "pyfwevt_provider_init";

	PYFWEVT_UNREFERENCED_PARAMETER( arguments )
	PYFWEVT_UNREFERENCED_PARAMETER( keywords )

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

/* Frees a provider object
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

/* Retrieves the identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_identifier(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	uint8_t uuid_data[ 16 ];

	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwevt_provider_get_identifier";
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

	result = libfwevt_provider_get_identifier(
	          pyfwevt_provider->provider,
	          uuid_data,
	          16,
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
	string_object = pyfwevt_string_new_from_guid(
	                 uuid_data,
	                 16 );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UUID into Unicode object.",
		 function );

		return( NULL );
	}
	return( string_object );
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

/* Retrieves a specific channel by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_channel_by_index(
           PyObject *pyfwevt_provider,
           int channel_index )
{
	PyObject *channel_object    = NULL;
	libcerror_error_t *error    = NULL;
	libfwevt_channel_t *channel = NULL;
	static char *function       = "pyfwevt_provider_get_channel_by_index";
	int result                  = 0;

	if( pyfwevt_provider == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid provider.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_provider_get_channel_by_index(
	          ( (pyfwevt_provider_t *) pyfwevt_provider )->provider,
	          channel_index,
	          &channel,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve channel: %d.",
		 function,
		 channel_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	channel_object = pyfwevt_channel_new(
	                  channel,
	                  pyfwevt_provider );

	if( channel_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create channel object.",
		 function );

		goto on_error;
	}
	return( channel_object );

on_error:
	if( channel != NULL )
	{
		libfwevt_channel_free(
		 &channel,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific channel
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_channel(
           PyObject *pyfwevt_provider,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *channel_object    = NULL;
	static char *keyword_list[] = { "channel_index", NULL };
	int channel_index           = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &channel_index ) == 0 )
	{
		return( NULL );
	}
	channel_object = pyfwevt_provider_get_channel_by_index(
	                  pyfwevt_provider,
	                  channel_index );

	return( channel_object );
}

/* Retrieves a sequence and iterator object for the channels
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_channels(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyfwevt_provider_get_channels";
	int number_of_channels    = 0;
	int result                = 0;

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
	sequence_object = pyfwevt_channels_new(
	                   (PyObject *) pyfwevt_provider,
	                   &pyfwevt_provider_get_channel_by_index,
	                   number_of_channels );

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

/* Retrieves the number of events
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_number_of_events(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwevt_provider_get_number_of_events";
	int number_of_events     = 0;
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

	result = libfwevt_provider_get_number_of_events(
	          pyfwevt_provider->provider,
	          &number_of_events,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of events.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_events );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_events );
#endif
	return( integer_object );
}

/* Retrieves a specific event by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_event_by_index(
           PyObject *pyfwevt_provider,
           int event_index )
{
	PyObject *event_object   = NULL;
	libcerror_error_t *error = NULL;
	libfwevt_event_t *event  = NULL;
	static char *function    = "pyfwevt_provider_get_event_by_index";
	int result               = 0;

	if( pyfwevt_provider == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid provider.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_provider_get_event_by_index(
	          ( (pyfwevt_provider_t *) pyfwevt_provider )->provider,
	          event_index,
	          &event,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve event: %d.",
		 function,
		 event_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	event_object = pyfwevt_event_new(
	                event,
	                pyfwevt_provider );

	if( event_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create event object.",
		 function );

		goto on_error;
	}
	return( event_object );

on_error:
	if( event != NULL )
	{
		libfwevt_event_free(
		 &event,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific event
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_event(
           PyObject *pyfwevt_provider,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *event_object      = NULL;
	static char *keyword_list[] = { "event_index", NULL };
	int event_index             = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &event_index ) == 0 )
	{
		return( NULL );
	}
	event_object = pyfwevt_provider_get_event_by_index(
	                pyfwevt_provider,
	                event_index );

	return( event_object );
}

/* Retrieves a sequence and iterator object for the events
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_events(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyfwevt_provider_get_events";
	int number_of_events      = 0;
	int result                = 0;

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

	result = libfwevt_provider_get_number_of_events(
	          pyfwevt_provider->provider,
	          &number_of_events,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of events.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pyfwevt_events_new(
	                   (PyObject *) pyfwevt_provider,
	                   &pyfwevt_provider_get_event_by_index,
	                   number_of_events );

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

/* Retrieves the number of keywords
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_number_of_keywords(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwevt_provider_get_number_of_keywords";
	int number_of_keywords   = 0;
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

	result = libfwevt_provider_get_number_of_keywords(
	          pyfwevt_provider->provider,
	          &number_of_keywords,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of keywords.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_keywords );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_keywords );
#endif
	return( integer_object );
}

/* Retrieves a specific keyword by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_keyword_by_index(
           PyObject *pyfwevt_provider,
           int keyword_index )
{
	PyObject *keyword_object    = NULL;
	libcerror_error_t *error    = NULL;
	libfwevt_keyword_t *keyword = NULL;
	static char *function       = "pyfwevt_provider_get_keyword_by_index";
	int result                  = 0;

	if( pyfwevt_provider == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid provider.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_provider_get_keyword_by_index(
	          ( (pyfwevt_provider_t *) pyfwevt_provider )->provider,
	          keyword_index,
	          &keyword,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve keyword: %d.",
		 function,
		 keyword_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	keyword_object = pyfwevt_keyword_new(
	                  keyword,
	                  pyfwevt_provider );

	if( keyword_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create keyword object.",
		 function );

		goto on_error;
	}
	return( keyword_object );

on_error:
	if( keyword != NULL )
	{
		libfwevt_keyword_free(
		 &keyword,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific keyword
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_keyword(
           PyObject *pyfwevt_provider,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *keyword_object    = NULL;
	static char *keyword_list[] = { "keyword_index", NULL };
	int keyword_index           = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &keyword_index ) == 0 )
	{
		return( NULL );
	}
	keyword_object = pyfwevt_provider_get_keyword_by_index(
	                  pyfwevt_provider,
	                  keyword_index );

	return( keyword_object );
}

/* Retrieves a sequence and iterator object for the keywords
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_keywords(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyfwevt_provider_get_keywords";
	int number_of_keywords    = 0;
	int result                = 0;

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

	result = libfwevt_provider_get_number_of_keywords(
	          pyfwevt_provider->provider,
	          &number_of_keywords,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of keywords.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pyfwevt_keywords_new(
	                   (PyObject *) pyfwevt_provider,
	                   &pyfwevt_provider_get_keyword_by_index,
	                   number_of_keywords );

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

/* Retrieves the number of levels
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_number_of_levels(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwevt_provider_get_number_of_levels";
	int number_of_levels     = 0;
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

	result = libfwevt_provider_get_number_of_levels(
	          pyfwevt_provider->provider,
	          &number_of_levels,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of levels.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_levels );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_levels );
#endif
	return( integer_object );
}

/* Retrieves a specific level by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_level_by_index(
           PyObject *pyfwevt_provider,
           int level_index )
{
	PyObject *level_object   = NULL;
	libcerror_error_t *error = NULL;
	libfwevt_level_t *level  = NULL;
	static char *function    = "pyfwevt_provider_get_level_by_index";
	int result               = 0;

	if( pyfwevt_provider == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid provider.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_provider_get_level_by_index(
	          ( (pyfwevt_provider_t *) pyfwevt_provider )->provider,
	          level_index,
	          &level,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve level: %d.",
		 function,
		 level_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	level_object = pyfwevt_level_new(
	                level,
	                pyfwevt_provider );

	if( level_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create level object.",
		 function );

		goto on_error;
	}
	return( level_object );

on_error:
	if( level != NULL )
	{
		libfwevt_level_free(
		 &level,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific level
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_level(
           PyObject *pyfwevt_provider,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *level_object      = NULL;
	static char *keyword_list[] = { "level_index", NULL };
	int level_index             = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &level_index ) == 0 )
	{
		return( NULL );
	}
	level_object = pyfwevt_provider_get_level_by_index(
	                pyfwevt_provider,
	                level_index );

	return( level_object );
}

/* Retrieves a sequence and iterator object for the levels
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_levels(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyfwevt_provider_get_levels";
	int number_of_levels      = 0;
	int result                = 0;

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

	result = libfwevt_provider_get_number_of_levels(
	          pyfwevt_provider->provider,
	          &number_of_levels,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of levels.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pyfwevt_levels_new(
	                   (PyObject *) pyfwevt_provider,
	                   &pyfwevt_provider_get_level_by_index,
	                   number_of_levels );

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

/* Retrieves the number of maps
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_number_of_maps(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwevt_provider_get_number_of_maps";
	int number_of_maps       = 0;
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

	result = libfwevt_provider_get_number_of_maps(
	          pyfwevt_provider->provider,
	          &number_of_maps,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of maps.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_maps );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_maps );
#endif
	return( integer_object );
}

/* Retrieves a specific map by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_map_by_index(
           PyObject *pyfwevt_provider,
           int map_index )
{
	PyObject *map_object     = NULL;
	libcerror_error_t *error = NULL;
	libfwevt_map_t *map      = NULL;
	static char *function    = "pyfwevt_provider_get_map_by_index";
	int result               = 0;

	if( pyfwevt_provider == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid provider.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_provider_get_map_by_index(
	          ( (pyfwevt_provider_t *) pyfwevt_provider )->provider,
	          map_index,
	          &map,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve map: %d.",
		 function,
		 map_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	map_object = pyfwevt_map_new(
	              map,
	              pyfwevt_provider );

	if( map_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create map object.",
		 function );

		goto on_error;
	}
	return( map_object );

on_error:
	if( map != NULL )
	{
		libfwevt_map_free(
		 &map,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific map
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_map(
           PyObject *pyfwevt_provider,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *map_object        = NULL;
	static char *keyword_list[] = { "map_index", NULL };
	int map_index               = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &map_index ) == 0 )
	{
		return( NULL );
	}
	map_object = pyfwevt_provider_get_map_by_index(
	              pyfwevt_provider,
	              map_index );

	return( map_object );
}

/* Retrieves a sequence and iterator object for the maps
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_maps(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyfwevt_provider_get_maps";
	int number_of_maps        = 0;
	int result                = 0;

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

	result = libfwevt_provider_get_number_of_maps(
	          pyfwevt_provider->provider,
	          &number_of_maps,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of maps.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pyfwevt_maps_new(
	                   (PyObject *) pyfwevt_provider,
	                   &pyfwevt_provider_get_map_by_index,
	                   number_of_maps );

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

/* Retrieves the number of opcodes
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_number_of_opcodes(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwevt_provider_get_number_of_opcodes";
	int number_of_opcodes    = 0;
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

	result = libfwevt_provider_get_number_of_opcodes(
	          pyfwevt_provider->provider,
	          &number_of_opcodes,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve template by offset.",
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
	                  (long) number_of_opcodes );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_opcodes );
#endif
	return( integer_object );
}

/* Retrieves a specific opcode by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_opcode_by_index(
           PyObject *pyfwevt_provider,
           int opcode_index )
{
	PyObject *opcode_object   = NULL;
	libcerror_error_t *error  = NULL;
	libfwevt_opcode_t *opcode = NULL;
	static char *function     = "pyfwevt_provider_get_opcode_by_index";
	int result                = 0;

	if( pyfwevt_provider == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid provider.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_provider_get_opcode_by_index(
	          ( (pyfwevt_provider_t *) pyfwevt_provider )->provider,
	          opcode_index,
	          &opcode,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve oppcode: %d.",
		 function,
		 opcode_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	opcode_object = pyfwevt_opcode_new(
	                 opcode,
	                 pyfwevt_provider );

	if( opcode_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create opcode object.",
		 function );

		goto on_error;
	}
	return( opcode_object );

on_error:
	if( opcode != NULL )
	{
		libfwevt_opcode_free(
		 &opcode,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific opcode
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_opcode(
           PyObject *pyfwevt_provider,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *opcode_object     = NULL;
	static char *keyword_list[] = { "opcode_index", NULL };
	int opcode_index            = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &opcode_index ) == 0 )
	{
		return( NULL );
	}
	opcode_object = pyfwevt_provider_get_opcode_by_index(
	                 pyfwevt_provider,
	                 opcode_index );

	return( opcode_object );
}

/* Retrieves a sequence and iterator object for the opcodes
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_opcodes(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyfwevt_provider_get_opcodes";
	int number_of_opcodes     = 0;
	int result                = 0;

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

	result = libfwevt_provider_get_number_of_opcodes(
	          pyfwevt_provider->provider,
	          &number_of_opcodes,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of opcodes.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pyfwevt_opcodes_new(
	                   (PyObject *) pyfwevt_provider,
	                   &pyfwevt_provider_get_opcode_by_index,
	                   number_of_opcodes );

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

/* Retrieves the number of tasks
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_number_of_tasks(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwevt_provider_get_number_of_tasks";
	int number_of_tasks      = 0;
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

	result = libfwevt_provider_get_number_of_tasks(
	          pyfwevt_provider->provider,
	          &number_of_tasks,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve .",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_tasks );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_tasks );
#endif
	return( integer_object );
}

/* Retrieves a specific task by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_task_by_index(
           PyObject *pyfwevt_provider,
           int task_index )
{
	PyObject *task_object    = NULL;
	libcerror_error_t *error = NULL;
	libfwevt_task_t *task    = NULL;
	static char *function    = "pyfwevt_provider_get_task_by_index";
	int result               = 0;

	if( pyfwevt_provider == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid provider.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_provider_get_task_by_index(
	          ( (pyfwevt_provider_t *) pyfwevt_provider )->provider,
	          task_index,
	          &task,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve task: %d.",
		 function,
		 task_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	task_object = pyfwevt_task_new(
	               task,
	               pyfwevt_provider );

	if( task_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create task object.",
		 function );

		goto on_error;
	}
	return( task_object );

on_error:
	if( task != NULL )
	{
		libfwevt_task_free(
		 &task,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific task
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_task(
           PyObject *pyfwevt_provider,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *task_object       = NULL;
	static char *keyword_list[] = { "task_index", NULL };
	int task_index              = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &task_index ) == 0 )
	{
		return( NULL );
	}
	task_object = pyfwevt_provider_get_task_by_index(
	               pyfwevt_provider,
	               task_index );

	return( task_object );
}

/* Retrieves a sequence and iterator object for the tasks
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_tasks(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyfwevt_provider_get_tasks";
	int number_of_tasks       = 0;
	int result                = 0;

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

	result = libfwevt_provider_get_number_of_tasks(
	          pyfwevt_provider->provider,
	          &number_of_tasks,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of tasks.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pyfwevt_tasks_new(
	                   (PyObject *) pyfwevt_provider,
	                   &pyfwevt_provider_get_task_by_index,
	                   number_of_tasks );

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

/* Retrieves the number of templates
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_number_of_templates(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwevt_provider_get_number_of_templates";
	int number_of_templates  = 0;
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

	result = libfwevt_provider_get_number_of_templates(
	          pyfwevt_provider->provider,
	          &number_of_templates,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve .",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_templates );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_templates );
#endif
	return( integer_object );
}

/* Retrieves a specific template by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_template_by_index(
           PyObject *pyfwevt_provider,
           int template_index )
{
	PyObject *template_object     = NULL;
	libcerror_error_t *error      = NULL;
	libfwevt_template_t *template = NULL;
	static char *function         = "pyfwevt_provider_get_template_by_index";
	int result                    = 0;

	if( pyfwevt_provider == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid provider.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_provider_get_template_by_index(
	          ( (pyfwevt_provider_t *) pyfwevt_provider )->provider,
	          template_index,
	          &template,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve template: %d.",
		 function,
		 template_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	template_object = pyfwevt_template_new(
	                   template,
	                   pyfwevt_provider );

	if( template_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create template object.",
		 function );

		goto on_error;
	}
	return( template_object );

on_error:
	if( template != NULL )
	{
		libfwevt_template_free(
		 &template,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific template
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_template(
           PyObject *pyfwevt_provider,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *template_object   = NULL;
	static char *keyword_list[] = { "template_index", NULL };
	int template_index          = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &template_index ) == 0 )
	{
		return( NULL );
	}
	template_object = pyfwevt_provider_get_template_by_index(
	                   pyfwevt_provider,
	                   template_index );

	return( template_object );
}

/* Retrieves a specific template
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_template_by_offset(
           PyObject *pyfwevt_provider,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *template_object     = NULL;
	libcerror_error_t *error      = NULL;
	libfwevt_template_t *template = NULL;
	static char *function         = "pyfwevt_provider_get_template_by_offset";
	static char *keyword_list[]   = { "template_offset", NULL };
	unsigned long template_offset = 0;
	int result                    = 0;

	if( pyfwevt_provider == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid provider.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "k",
	     keyword_list,
	     &template_offset ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_provider_get_template_by_offset(
	          ( (pyfwevt_provider_t *) pyfwevt_provider )->provider,
	          (uint32_t) template_offset,
	          &template,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve template at offset: %" PRIu32 " (0x%08" PRIx32 ").",
		 function,
		 (uint32_t) template_offset,
		 (uint32_t) template_offset );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	template_object = pyfwevt_template_new(
	                   template,
	                   pyfwevt_provider );

	if( template_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create template object.",
		 function );

		goto on_error;
	}
	return( template_object );

on_error:
	if( template != NULL )
	{
		libfwevt_template_free(
		 &template,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a sequence and iterator object for the templates
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_provider_get_templates(
           pyfwevt_provider_t *pyfwevt_provider,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyfwevt_provider_get_templates";
	int number_of_templates   = 0;
	int result                = 0;

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

	result = libfwevt_provider_get_number_of_templates(
	          pyfwevt_provider->provider,
	          &number_of_templates,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of templates.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pyfwevt_templates_new(
	                   (PyObject *) pyfwevt_provider,
	                   &pyfwevt_provider_get_template_by_index,
	                   number_of_templates );

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

