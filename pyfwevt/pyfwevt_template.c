/*
 * Python object wrapper of libfwevt_template_t
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
#include "pyfwevt_guid.h"
#include "pyfwevt_libcerror.h"
#include "pyfwevt_libfwevt.h"
#include "pyfwevt_python.h"
#include "pyfwevt_template.h"
#include "pyfwevt_template_item.h"
#include "pyfwevt_template_items.h"
#include "pyfwevt_unused.h"

PyMethodDef pyfwevt_template_object_methods[] = {

	{ "get_identifier",
	  (PyCFunction) pyfwevt_template_get_identifier,
	  METH_NOARGS,
	  "get_identifier() -> Unicode string\n"
	  "\n"
	  "Retrieves the identifier." },

	{ "get_number_of_items",
	  (PyCFunction) pyfwevt_template_get_number_of_items,
	  METH_NOARGS,
	  "get_number_of_items() -> Integer\n"
	  "\n"
	  "Retrieves the number of items." },

	{ "get_item",
	  (PyCFunction) pyfwevt_template_get_item,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_item(item_index) -> Object\n"
	  "\n"
	  "Retrieves the item specified by the index." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyfwevt_template_object_get_set_definitions[] = {

	{ "identifier",
	  (getter) pyfwevt_template_get_identifier,
	  (setter) 0,
	  "The identifier.",
	  NULL },

	{ "number_of_items",
	  (getter) pyfwevt_template_get_number_of_items,
	  (setter) 0,
	  "The number of items.",
	  NULL },

	{ "items",
	  (getter) pyfwevt_template_get_items,
	  (setter) 0,
	  "The items.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyfwevt_template_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyfwevt.template",
	/* tp_basicsize */
	sizeof( pyfwevt_template_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyfwevt_template_free,
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
	"pyfwevt template object (wraps libfwevt_template_t)",
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
	pyfwevt_template_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyfwevt_template_object_get_set_definitions,
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
	(initproc) pyfwevt_template_init,
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

/* Creates a new template object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_template_new(
           libfwevt_template_t *template,
           PyObject *parent_object )
{
	pyfwevt_template_t *pyfwevt_template = NULL;
	static char *function                = "pyfwevt_template_new";

	if( template == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid template.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pyfwevt_template = PyObject_New(
	                struct pyfwevt_template,
	                &pyfwevt_template_type_object );

	if( pyfwevt_template == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize template.",
		 function );

		goto on_error;
	}
	pyfwevt_template->template      = template;
	pyfwevt_template->parent_object = parent_object;

	if( pyfwevt_template->parent_object != NULL )
	{
		Py_IncRef(
		 pyfwevt_template->parent_object );
	}
	return( (PyObject *) pyfwevt_template );

on_error:
	if( pyfwevt_template != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyfwevt_template );
	}
	return( NULL );
}

/* Initializes a template object
 * Returns 0 if successful or -1 on error
 */
int pyfwevt_template_init(
     pyfwevt_template_t *pyfwevt_template,
     PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED,
     PyObject *keywords PYFWEVT_ATTRIBUTE_UNUSED )
{
	static char *function = "pyfwevt_template_init";

	PYFWEVT_UNREFERENCED_PARAMETER( arguments )
	PYFWEVT_UNREFERENCED_PARAMETER( keywords )

	if( pyfwevt_template == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	/* Make sure libfwevt template is set to NULL
	 */
	pyfwevt_template->template = NULL;

	PyErr_Format(
	 PyExc_NotImplementedError,
	 "%s: initialize of template not supported.",
	 function );

	return( -1 );
}

/* Frees a template object
 */
void pyfwevt_template_free(
      pyfwevt_template_t *pyfwevt_template )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyfwevt_template_free";
	int result                  = 0;

	if( pyfwevt_template == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid template.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyfwevt_template );

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
	if( pyfwevt_template->template != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libfwevt_template_free(
		          &( pyfwevt_template->template ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyfwevt_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libfwevt template.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	if( pyfwevt_template->parent_object != NULL )
	{
		Py_DecRef(
		 pyfwevt_template->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyfwevt_template );
}

/* Retrieves the identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_template_get_identifier(
           pyfwevt_template_t *pyfwevt_template,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	uint8_t uuid_data[ 16 ];

	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwevt_template_get_identifier";
	int result               = 0;

	PYFWEVT_UNREFERENCED_PARAMETER( arguments )

	if( pyfwevt_template == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid template.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_template_get_identifier(
	          pyfwevt_template->template,
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

/* Retrieves the number of items
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_template_get_number_of_items(
           pyfwevt_template_t *pyfwevt_template,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwevt_template_get_number_of_items";
	int number_of_items      = 0;
	int result               = 0;

	PYFWEVT_UNREFERENCED_PARAMETER( arguments )

	if( pyfwevt_template == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid template.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_template_get_number_of_items(
	          pyfwevt_template->template,
	          &number_of_items,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of items.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_items );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_items );
#endif
	return( integer_object );
}

/* Retrieves a specific item by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_template_get_item_by_index(
           PyObject *pyfwevt_template,
           int item_index )
{
	PyObject *item_object          = NULL;
	libcerror_error_t *error       = NULL;
	libfwevt_template_item_t *item = NULL;
	static char *function          = "pyfwevt_template_get_item_by_index";
	int result                     = 0;

	if( pyfwevt_template == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid template.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_template_get_item_by_index(
	          ( (pyfwevt_template_t *) pyfwevt_template )->template,
	          item_index,
	          &item,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve item: %d.",
		 function,
		 item_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	item_object = pyfwevt_template_item_new(
	               item,
	               pyfwevt_template );

	if( item_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create item object.",
		 function );

		goto on_error;
	}
	return( item_object );

on_error:
	if( item != NULL )
	{
		libfwevt_template_item_free(
		 &item,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_template_get_item(
           PyObject *pyfwevt_template,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *item_object       = NULL;
	static char *keyword_list[] = { "item_index", NULL };
	int item_index              = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &item_index ) == 0 )
	{
		return( NULL );
	}
	item_object = pyfwevt_template_get_item_by_index(
	               pyfwevt_template,
	               item_index );

	return( item_object );
}

/* Retrieves a sequence and iterator object for the items
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_template_get_items(
           pyfwevt_template_t *pyfwevt_template,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyfwevt_template_get_items";
	int number_of_items       = 0;
	int result                = 0;

	PYFWEVT_UNREFERENCED_PARAMETER( arguments )

	if( pyfwevt_template == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid template.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwevt_template_get_number_of_items(
	          pyfwevt_template->template,
	          &number_of_items,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwevt_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of items.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pyfwevt_template_items_new(
	                   (PyObject *) pyfwevt_template,
	                   &pyfwevt_template_get_item_by_index,
	                   number_of_items );

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

