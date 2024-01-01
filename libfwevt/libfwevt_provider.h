/*
 * Provider functions
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

#if !defined( _LIBFWEVT_PROVIDER_H )
#define _LIBFWEVT_PROVIDER_H

#include <common.h>
#include <types.h>

#include "libfwevt_channel.h"
#include "libfwevt_extern.h"
#include "libfwevt_event.h"
#include "libfwevt_keyword.h"
#include "libfwevt_level.h"
#include "libfwevt_libcdata.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_map.h"
#include "libfwevt_opcode.h"
#include "libfwevt_task.h"
#include "libfwevt_template.h"
#include "libfwevt_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfwevt_internal_provider libfwevt_internal_provider_t;

struct libfwevt_internal_provider
{
	/* The channels offset
	 */
	uint32_t channels_offset;

	/* The events offset
	 */
	uint32_t events_offset;

	/* The keywords offset
	 */
	uint32_t keywords_offset;

	/* The levels offset
	 */
	uint32_t levels_offset;

	/* The maps offset
	 */
	uint32_t maps_offset;

	/* The opcodes offset
	 */
	uint32_t opcodes_offset;

	/* The tasks offset
	 */
	uint32_t tasks_offset;

	/* The templates offset
	 */
	uint32_t templates_offset;

	/* The (provider) identifier
	 * Contains a GUID
	 */
	uint8_t identifier[ 16 ];

	/* The channels array
	 */
	libcdata_array_t *channels_array;

	/* The events array
	 */
	libcdata_array_t *events_array;

	/* The keywords array
	 */
	libcdata_array_t *keywords_array;

	/* The levels array
	 */
	libcdata_array_t *levels_array;

	/* The maps array
	 */
	libcdata_array_t *maps_array;

	/* The opcodes array
	 */
	libcdata_array_t *opcodes_array;

	/* The tasks array
	 */
	libcdata_array_t *tasks_array;

	/* The templates array
	 */
	libcdata_array_t *templates_array;
};

int libfwevt_provider_initialize(
     libfwevt_provider_t **provider,
     const uint8_t *identifier,
     size_t identifier_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_provider_free(
     libfwevt_provider_t **provider,
     libcerror_error_t **error );

int libfwevt_internal_provider_free(
     libfwevt_internal_provider_t **internal_provider,
     libcerror_error_t **error );

int libfwevt_provider_read_data(
     libfwevt_provider_t *provider,
     const uint8_t *data,
     size_t data_size,
     size_t data_offset,
     libcerror_error_t **error );

int libfwevt_provider_read_channels(
     libfwevt_provider_t *provider,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfwevt_provider_read_events(
     libfwevt_provider_t *provider,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfwevt_provider_read_keywords(
     libfwevt_provider_t *provider,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfwevt_provider_read_levels(
     libfwevt_provider_t *provider,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfwevt_provider_read_maps(
     libfwevt_provider_t *provider,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfwevt_provider_read_opcodes(
     libfwevt_provider_t *provider,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfwevt_provider_read_tasks(
     libfwevt_provider_t *provider,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libfwevt_provider_read_templates(
     libfwevt_provider_t *provider,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_provider_get_identifier(
     libfwevt_provider_t *provider,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

int libfwevt_provider_compare_identifier(
     libfwevt_provider_t *provider,
     const uint8_t *identifier,
     size_t identifier_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_provider_get_number_of_channels(
     libfwevt_provider_t *provider,
     int *number_of_channels,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_provider_get_channel_by_index(
     libfwevt_provider_t *provider,
     int channel_index,
     libfwevt_channel_t **channel,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_provider_get_number_of_events(
     libfwevt_provider_t *provider,
     int *number_of_events,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_provider_get_event_by_index(
     libfwevt_provider_t *provider,
     int event_index,
     libfwevt_event_t **event,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_provider_get_event_by_identifier(
     libfwevt_provider_t *provider,
     uint32_t event_identifier,
     libfwevt_event_t **event,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_provider_get_number_of_keywords(
     libfwevt_provider_t *provider,
     int *number_of_keywords,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_provider_get_keyword_by_index(
     libfwevt_provider_t *provider,
     int keyword_index,
     libfwevt_keyword_t **keyword,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_provider_get_number_of_levels(
     libfwevt_provider_t *provider,
     int *number_of_levels,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_provider_get_level_by_index(
     libfwevt_provider_t *provider,
     int level_index,
     libfwevt_level_t **level,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_provider_get_number_of_maps(
     libfwevt_provider_t *provider,
     int *number_of_maps,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_provider_get_map_by_index(
     libfwevt_provider_t *provider,
     int map_index,
     libfwevt_map_t **map,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_provider_get_number_of_opcodes(
     libfwevt_provider_t *provider,
     int *number_of_opcodes,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_provider_get_opcode_by_index(
     libfwevt_provider_t *provider,
     int opcode_index,
     libfwevt_opcode_t **opcode,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_provider_get_number_of_tasks(
     libfwevt_provider_t *provider,
     int *number_of_tasks,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_provider_get_task_by_index(
     libfwevt_provider_t *provider,
     int task_index,
     libfwevt_task_t **task,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_provider_get_number_of_templates(
     libfwevt_provider_t *provider,
     int *number_of_templates,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_provider_get_template_by_index(
     libfwevt_provider_t *provider,
     int template_index,
     libfwevt_template_t **wevt_template,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_provider_get_template_by_offset(
     libfwevt_provider_t *provider,
     uint32_t offset,
     libfwevt_template_t **wevt_template,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWEVT_PROVIDER_H ) */

