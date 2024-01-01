/*
 * Python bindings module for libfwevt (pyfwevt)
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
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyfwevt.h"
#include "pyfwevt_channel.h"
#include "pyfwevt_channels.h"
#include "pyfwevt_error.h"
#include "pyfwevt_event.h"
#include "pyfwevt_events.h"
#include "pyfwevt_keyword.h"
#include "pyfwevt_keywords.h"
#include "pyfwevt_level.h"
#include "pyfwevt_levels.h"
#include "pyfwevt_libcerror.h"
#include "pyfwevt_libfwevt.h"
#include "pyfwevt_manifest.h"
#include "pyfwevt_map.h"
#include "pyfwevt_maps.h"
#include "pyfwevt_opcode.h"
#include "pyfwevt_opcodes.h"
#include "pyfwevt_provider.h"
#include "pyfwevt_providers.h"
#include "pyfwevt_python.h"
#include "pyfwevt_task.h"
#include "pyfwevt_tasks.h"
#include "pyfwevt_template.h"
#include "pyfwevt_template_item.h"
#include "pyfwevt_template_items.h"
#include "pyfwevt_templates.h"
#include "pyfwevt_unused.h"

/* The pyfwevt module methods
 */
PyMethodDef pyfwevt_module_methods[] = {
	{ "get_version",
	  (PyCFunction) pyfwevt_get_version,
	  METH_NOARGS,
	  "get_version() -> String\n"
	  "\n"
	  "Retrieves the version." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

/* Retrieves the pyfwevt/libfwevt version
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwevt_get_version(
           PyObject *self PYFWEVT_ATTRIBUTE_UNUSED,
           PyObject *arguments PYFWEVT_ATTRIBUTE_UNUSED )
{
	const char *version_string   = NULL;
	size_t version_string_length = 0;

	PYFWEVT_UNREFERENCED_PARAMETER( self )
	PYFWEVT_UNREFERENCED_PARAMETER( arguments )

	Py_BEGIN_ALLOW_THREADS

	version_string = libfwevt_get_version();

	Py_END_ALLOW_THREADS

	version_string_length = narrow_string_length(
	                         version_string );

	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	return( PyUnicode_DecodeUTF8(
	         version_string,
	         (Py_ssize_t) version_string_length,
	         NULL ) );
}

#if PY_MAJOR_VERSION >= 3

/* The pyfwevt module definition
 */
PyModuleDef pyfwevt_module_definition = {
	PyModuleDef_HEAD_INIT,

	/* m_name */
	"pyfwevt",
	/* m_doc */
	"Python libfwevt module (pyfwevt).",
	/* m_size */
	-1,
	/* m_methods */
	pyfwevt_module_methods,
	/* m_reload */
	NULL,
	/* m_traverse */
	NULL,
	/* m_clear */
	NULL,
	/* m_free */
	NULL,
};

#endif /* PY_MAJOR_VERSION >= 3 */

/* Initializes the pyfwevt module
 */
#if PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC PyInit_pyfwevt(
                void )
#else
PyMODINIT_FUNC initpyfwevt(
                void )
#endif
{
	PyObject *module           = NULL;
	PyGILState_STATE gil_state = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libfwevt_notify_set_stream(
	 stderr,
	 NULL );
	libfwevt_notify_set_verbose(
	 1 );
#endif

	/* Create the module
	 * This function must be called before grabbing the GIL
	 * otherwise the module will segfault on a version mismatch
	 */
#if PY_MAJOR_VERSION >= 3
	module = PyModule_Create(
	          &pyfwevt_module_definition );
#else
	module = Py_InitModule3(
	          "pyfwevt",
	          pyfwevt_module_methods,
	          "Python libfwevt module (pyfwevt)." );
#endif
	if( module == NULL )
	{
#if PY_MAJOR_VERSION >= 3
		return( NULL );
#else
		return;
#endif
	}
#if PY_VERSION_HEX < 0x03070000
	PyEval_InitThreads();
#endif
	gil_state = PyGILState_Ensure();

	/* Setup the channel type object
	 */
	pyfwevt_channel_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_channel_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_channel_type_object );

	PyModule_AddObject(
	 module,
	 "channel",
	 (PyObject *) &pyfwevt_channel_type_object );

	/* Setup the channels type object
	 */
	pyfwevt_channels_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_channels_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_channels_type_object );

	PyModule_AddObject(
	 module,
	 "channels",
	 (PyObject *) &pyfwevt_channels_type_object );

	/* Setup the event type object
	 */
	pyfwevt_event_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_event_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_event_type_object );

	PyModule_AddObject(
	 module,
	 "event",
	 (PyObject *) &pyfwevt_event_type_object );

	/* Setup the events type object
	 */
	pyfwevt_events_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_events_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_events_type_object );

	PyModule_AddObject(
	 module,
	 "events",
	 (PyObject *) &pyfwevt_events_type_object );

	/* Setup the keyword type object
	 */
	pyfwevt_keyword_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_keyword_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_keyword_type_object );

	PyModule_AddObject(
	 module,
	 "keyword",
	 (PyObject *) &pyfwevt_keyword_type_object );

	/* Setup the keywords type object
	 */
	pyfwevt_keywords_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_keywords_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_keywords_type_object );

	PyModule_AddObject(
	 module,
	 "keywords",
	 (PyObject *) &pyfwevt_keywords_type_object );

	/* Setup the level type object
	 */
	pyfwevt_level_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_level_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_level_type_object );

	PyModule_AddObject(
	 module,
	 "level",
	 (PyObject *) &pyfwevt_level_type_object );

	/* Setup the levels type object
	 */
	pyfwevt_levels_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_levels_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_levels_type_object );

	PyModule_AddObject(
	 module,
	 "levels",
	 (PyObject *) &pyfwevt_levels_type_object );

	/* Setup the manifest type object
	 */
	pyfwevt_manifest_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_manifest_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_manifest_type_object );

	PyModule_AddObject(
	 module,
	 "manifest",
	 (PyObject *) &pyfwevt_manifest_type_object );

	/* Setup the map type object
	 */
	pyfwevt_map_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_map_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_map_type_object );

	PyModule_AddObject(
	 module,
	 "map",
	 (PyObject *) &pyfwevt_map_type_object );

	/* Setup the maps type object
	 */
	pyfwevt_maps_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_maps_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_maps_type_object );

	PyModule_AddObject(
	 module,
	 "maps",
	 (PyObject *) &pyfwevt_maps_type_object );

	/* Setup the opcode type object
	 */
	pyfwevt_opcode_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_opcode_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_opcode_type_object );

	PyModule_AddObject(
	 module,
	 "opcode",
	 (PyObject *) &pyfwevt_opcode_type_object );

	/* Setup the opcodes type object
	 */
	pyfwevt_opcodes_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_opcodes_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_opcodes_type_object );

	PyModule_AddObject(
	 module,
	 "opcodes",
	 (PyObject *) &pyfwevt_opcodes_type_object );

	/* Setup the provider type object
	 */
	pyfwevt_provider_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_provider_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_provider_type_object );

	PyModule_AddObject(
	 module,
	 "provider",
	 (PyObject *) &pyfwevt_provider_type_object );

	/* Setup the providers type object
	 */
	pyfwevt_providers_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_providers_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_providers_type_object );

	PyModule_AddObject(
	 module,
	 "providers",
	 (PyObject *) &pyfwevt_providers_type_object );

	/* Setup the task type object
	 */
	pyfwevt_task_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_task_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_task_type_object );

	PyModule_AddObject(
	 module,
	 "task",
	 (PyObject *) &pyfwevt_task_type_object );

	/* Setup the tasks type object
	 */
	pyfwevt_tasks_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_tasks_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_tasks_type_object );

	PyModule_AddObject(
	 module,
	 "tasks",
	 (PyObject *) &pyfwevt_tasks_type_object );

	/* Setup the template type object
	 */
	pyfwevt_template_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_template_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_template_type_object );

	PyModule_AddObject(
	 module,
	 "template",
	 (PyObject *) &pyfwevt_template_type_object );

	/* Setup the template item type object
	 */
	pyfwevt_template_item_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_template_item_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_template_item_type_object );

	PyModule_AddObject(
	 module,
	 "template_item",
	 (PyObject *) &pyfwevt_template_item_type_object );

	/* Setup the template items type object
	 */
	pyfwevt_template_items_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_template_items_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_template_items_type_object );

	PyModule_AddObject(
	 module,
	 "template_items",
	 (PyObject *) &pyfwevt_template_items_type_object );

	/* Setup the templates type object
	 */
	pyfwevt_templates_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwevt_templates_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwevt_templates_type_object );

	PyModule_AddObject(
	 module,
	 "templates",
	 (PyObject *) &pyfwevt_templates_type_object );

	PyGILState_Release(
	 gil_state );

#if PY_MAJOR_VERSION >= 3
	return( module );
#else
	return;
#endif

on_error:
	PyGILState_Release(
	 gil_state );

#if PY_MAJOR_VERSION >= 3
	return( NULL );
#else
	return;
#endif
}

