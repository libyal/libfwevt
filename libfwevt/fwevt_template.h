/*
 * The Windows Event Template (WEVT_TEMPLATE) definitions
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

#if !defined( _FWEVT_TEMPLATE_H )
#define _FWEVT_TEMPLATE_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct fwevt_template_manifest fwevt_template_manifest_t;

struct fwevt_template_manifest
{
	/* The signature
	 * Consists of 4 bytes
	 * Contains: "CRIM"
	 */
	uint8_t signature[ 4 ];

	/* The size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* The major version
	 * Consists of 2 bytes
	 */
	uint8_t major_version[ 2 ];

	/* The minor version
	 * Consists of 2 bytes
	 */
	uint8_t minor_version[ 2 ];

	/* The number of providers
	 * Consists of 4 bytes
	 */
	uint8_t number_of_providers[ 4 ];
};

typedef struct fwevt_template_provider_entry fwevt_template_provider_entry_t;

struct fwevt_template_provider_entry
{
	/* The identifier
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t identifier[ 16 ];

	/* The data offset
	 * Consists of 4 bytes
	 */
	uint8_t data_offset[ 4 ];
};

typedef struct fwevt_template_provider fwevt_template_provider_t;

struct fwevt_template_provider
{
	/* The signature
	 * Consists of 4 bytes
	 * Contains: "WEVT"
	 */
	uint8_t signature[ 4 ];

	/* The size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* The message-table identifier
	 * Consists of 4 bytes
	 */
	uint8_t message_identifier[ 4 ];

	/* The number of descriptors
	 * Consists of 4 bytes
	 */
	uint8_t number_of_descriptors[ 4 ];

	/* The number of unknowns
	 * Consists of 4 bytes
	 */
	uint8_t number_of_unknown2[ 4 ];
};

typedef struct fwevt_template_channels fwevt_template_channels_t;

struct fwevt_template_channels
{
	/* The signature
	 * Consists of 4 bytes
	 * Contains: "CHAN"
	 */
	uint8_t signature[ 4 ];

	/* The size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* The number of channels
	 * Consists of 4 bytes
	 */
	uint8_t number_of_channels[ 4 ];
};

typedef struct fwevt_template_channel fwevt_template_channel_t;

struct fwevt_template_channel
{
	/* The identifier
	 * Consists of 4 bytes
	 */
	uint8_t identifier[ 4 ];

	/* The name offset
	 * Consists of 4 bytes
	 */
	uint8_t name_offset[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The message-table identifier
	 * Consists of 4 bytes
	 */
	uint8_t message_identifier[ 4 ];
};

typedef struct fwevt_template_events fwevt_template_events_t;

struct fwevt_template_events
{
	/* The signature
	 * Consists of 4 bytes
	 * Contains: "EVNT"
	 */
	uint8_t signature[ 4 ];

	/* The size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* The number of events
	 * Consists of 4 bytes
	 */
	uint8_t number_of_events[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];
};

typedef struct fwevt_template_event fwevt_template_event_t;

struct fwevt_template_event
{
	/* The identifier
	 * Consists of 2 bytes
	 */
	uint8_t identifier[ 2 ];

	union
	{
		struct
		{
			/* Unknown
			 * Consists of 2 bytes
			 */
			uint8_t unknown1[ 2 ];

			/* The qualifiers
			 * Consists of 2 bytes
			 */
			uint8_t qualifiers[ 2 ];

			/* Unknown
			 * Consists of 2 bytes
			 */
			uint8_t unknown2[ 2 ];

		};
		struct
		{
			/* The version
			 * Consists of 1 byte
			 */
			uint8_t version;

			/* The channel
			 * Consists of 1 byte
			 */
			uint8_t channel;

			/* The level
			 * Consists of 1 byte
			 */
			uint8_t level;

			/* The opcode
			 * Consists of 1 byte
			 */
			uint8_t opcode;

			/* The task
			 * Consists of 2 bytes
			 */
			uint8_t task[ 2 ];
		};
	};

	/* The keywords
	 * Consists of 8 bytes
	 */
	uint8_t keywords[ 8 ];

	/* The message-table identifier
	 * Consists of 4 bytes
	 */
	uint8_t message_identifier[ 4 ];

	/* The template (definition) offset
	 * Consists of 4 bytes
	 */
	uint8_t template_offset[ 4 ];

	/* The opcode (definition) offset
	 * Consists of 4 bytes
	 */
	uint8_t opcode_offset[ 4 ];

	/* The level (definition) offset
	 * Consists of 4 bytes
	 */
	uint8_t level_offset[ 4 ];

	/* The task (definition) offset
	 * Consists of 4 bytes
	 */
	uint8_t task_offset[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4[ 4 ];

	/* The flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];
};

typedef struct fwevt_template_keywords fwevt_template_keywords_t;

struct fwevt_template_keywords
{
	/* The signature
	 * Consists of 4 bytes
	 * Contains: "CHAN"
	 */
	uint8_t signature[ 4 ];

	/* The size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* The number of keywords
	 * Consists of 4 bytes
	 */
	uint8_t number_of_keywords[ 4 ];
};

typedef struct fwevt_template_keyword fwevt_template_keyword_t;

struct fwevt_template_keyword
{
	/* The identifier (bitmask)
	 * Consists of 8 bytes
	 */
	uint8_t identifier[ 8 ];

	/* The message-table identifier
	 * Consists of 4 bytes
	 */
	uint8_t message_identifier[ 4 ];

	/* The data offset
	 * Consists of 4 bytes
	 */
	uint8_t data_offset[ 4 ];
};

typedef struct fwevt_template_levels fwevt_template_levels_t;

struct fwevt_template_levels
{
	/* The signature
	 * Consists of 4 bytes
	 * Contains: "LEVL"
	 */
	uint8_t signature[ 4 ];

	/* The size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* The number of levels
	 * Consists of 4 bytes
	 */
	uint8_t number_of_levels[ 4 ];
};

typedef struct fwevt_template_level fwevt_template_level_t;

struct fwevt_template_level
{
	/* The identifier
	 * Consists of 4 bytes
	 */
	uint8_t identifier[ 4 ];

	/* The message-table identifier
	 * Consists of 4 bytes
	 */
	uint8_t message_identifier[ 4 ];

	/* The data offset
	 * Consists of 4 bytes
	 */
	uint8_t data_offset[ 4 ];
};

typedef struct fwevt_template_maps fwevt_template_maps_t;

struct fwevt_template_maps
{
	/* The signature
	 * Consists of 4 bytes
	 * Contains: "MAPS"
	 */
	uint8_t signature[ 4 ];

	/* The size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* The number of maps
	 * Consists of 4 bytes
	 */
	uint8_t number_of_maps[ 4 ];

	/* The data offset
	 * Consists of 4 bytes
	 */
	uint8_t data_offset[ 4 ];
};

typedef struct fwevt_template_map fwevt_template_map_t;

struct fwevt_template_map
{
	/* TODO */
	uint8_t signature[ 4 ];
};

typedef struct fwevt_template_opcodes fwevt_template_opcodes_t;

struct fwevt_template_opcodes
{
	/* The signature
	 * Consists of 4 bytes
	 * Contains: "OPCO"
	 */
	uint8_t signature[ 4 ];

	/* The size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* The number of opcodes
	 * Consists of 4 bytes
	 */
	uint8_t number_of_opcodes[ 4 ];
};

typedef struct fwevt_template_opcode fwevt_template_opcode_t;

struct fwevt_template_opcode
{
	/* The identifier
	 * Consists of 4 bytes
	 */
	uint8_t identifier[ 4 ];

	/* The message-table identifier
	 * Consists of 4 bytes
	 */
	uint8_t message_identifier[ 4 ];

	/* The data offset
	 * Consists of 4 bytes
	 */
	uint8_t data_offset[ 4 ];
};

typedef struct fwevt_template_tasks fwevt_template_tasks_t;

struct fwevt_template_tasks
{
	/* The signature
	 * Consists of 4 bytes
	 * Contains: "TASK"
	 */
	uint8_t signature[ 4 ];

	/* The size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* The number of tasks
	 * Consists of 4 bytes
	 */
	uint8_t number_of_tasks[ 4 ];
};

typedef struct fwevt_template_task fwevt_template_task_t;

struct fwevt_template_task
{
	/* The identifier
	 * Consists of 4 bytes
	 */
	uint8_t identifier[ 4 ];

	/* The message-table identifier
	 * Consists of 4 bytes
	 */
	uint8_t message_identifier[ 4 ];

	/* Unknown
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t unknown1[ 16 ];

	/* The data offset
	 * Consists of 4 bytes
	 */
	uint8_t data_offset[ 4 ];
};

typedef struct fwevt_template_table fwevt_template_table_t;

struct fwevt_template_table
{
	/* The signature
	 * Consists of 4 bytes
	 * Contains: "TTBL"
	 */
	uint8_t signature[ 4 ];

	/* The size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* The number of templates
	 * Consists of 4 bytes
	 */
	uint8_t number_of_templates[ 4 ];
};

typedef struct fwevt_template_header fwevt_template_header_t;

struct fwevt_template_header
{
	/* The signature
	 * Consists of 4 bytes
	 * Contains: "TEMP"
	 */
	uint8_t signature[ 4 ];

	/* The size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* The number of (variable) descriptors
	 * Consists of 4 bytes
	 */
	uint8_t number_of_descriptors[ 4 ];

	/* The number of (variable) names
	 * Consists of 4 bytes
	 */
	uint8_t number_of_names[ 4 ];

	/* The template items offset
	 * Consists of 4 bytes
	 */
	uint8_t template_items_offset[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The template identifier
	 * Consists of 16 bytes
	 */
	uint8_t identifier[ 16 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _FWEVT_TEMPLATE_H ) */

