/*
 * Library to support the Windows XML Event Log (EVTX) data types
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

#if !defined( _LIBFWEVT_H )
#define _LIBFWEVT_H

#include <libfwevt/definitions.h>
#include <libfwevt/error.h>
#include <libfwevt/extern.h>
#include <libfwevt/features.h>
#include <libfwevt/types.h>

#include <stdio.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBFWEVT_EXTERN \
const char *libfwevt_get_version(
             void );

/* -------------------------------------------------------------------------
 * Error functions
 * ------------------------------------------------------------------------- */

/* Frees an error
 */
LIBFWEVT_EXTERN \
void libfwevt_error_free(
      libfwevt_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the amount of printed characters if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_error_fprint(
     libfwevt_error_t *error,
     FILE *stream );

/* Prints a descriptive string of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the amount of printed characters if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_error_sprint(
     libfwevt_error_t *error,
     char *string,
     size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the amount of printed characters if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_error_backtrace_fprint(
     libfwevt_error_t *error,
     FILE *stream );

/* Prints a backtrace of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the amount of printed characters if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_error_backtrace_sprint(
     libfwevt_error_t *error,
     char *string,
     size_t size );

/* -------------------------------------------------------------------------
 * Channel functions
 * ------------------------------------------------------------------------- */

/* Frees a channel
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_channel_free(
     libfwevt_channel_t **channel,
     libfwevt_error_t **error );

/* -------------------------------------------------------------------------
 * Event functions
 * ------------------------------------------------------------------------- */

/* Frees an event
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_event_free(
     libfwevt_event_t **event,
     libfwevt_error_t **error );

/* Retrieves the identifier
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_event_get_identifier(
     libfwevt_event_t *event,
     uint32_t *identifier,
     libfwevt_error_t **error );

/* Retrieves the message identifier
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_event_get_message_identifier(
     libfwevt_event_t *event,
     uint32_t *message_identifier,
     libfwevt_error_t **error );

/* Retrieves the template offset
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_event_get_template_offset(
     libfwevt_event_t *event,
     uint32_t *template_offset,
     libfwevt_error_t **error );

/* -------------------------------------------------------------------------
 * Keyword functions
 * ------------------------------------------------------------------------- */

/* Frees a keyword
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_keyword_free(
     libfwevt_keyword_t **keyword,
     libfwevt_error_t **error );

/* -------------------------------------------------------------------------
 * Level functions
 * ------------------------------------------------------------------------- */

/* Frees a level
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_level_free(
     libfwevt_level_t **level,
     libfwevt_error_t **error );

/* -------------------------------------------------------------------------
 * Manifest functions
 * ------------------------------------------------------------------------- */

/* Creates a manifest
 * Make sure the value channel is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_manifest_initialize(
     libfwevt_manifest_t **manifest,
     libfwevt_error_t **error );

/* Frees a manifest
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_manifest_free(
     libfwevt_manifest_t **manifest,
     libfwevt_error_t **error );

/* Reads the manifest
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_manifest_read(
     libfwevt_manifest_t *manifest,
     const uint8_t *data,
     size_t data_size,
     libfwevt_error_t **error );

/* Retrieves the number of providers
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_manifest_get_number_of_providers(
     libfwevt_manifest_t *manifest,
     int *number_of_providers,
     libfwevt_error_t **error );

/* Retrieves a specific provider
 *
 * This function is deprecated, use libfwevt_manifest_get_provider_by_index instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_DEPRECATED \
LIBFWEVT_EXTERN \
int libfwevt_manifest_get_provider(
     libfwevt_manifest_t *manifest,
     int provider_index,
     libfwevt_provider_t **provider,
     libfwevt_error_t **error );

/* Retrieves a specific provider
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_manifest_get_provider_by_index(
     libfwevt_manifest_t *manifest,
     int provider_index,
     libfwevt_provider_t **provider,
     libfwevt_error_t **error );

/* Retrieves a specific provider by identifier (GUID)
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_manifest_get_provider_by_identifier(
     libfwevt_manifest_t *manifest,
     const uint8_t *provider_identifier,
     size_t provider_identifier_size,
     libfwevt_provider_t **provider,
     libfwevt_error_t **error );

/* -------------------------------------------------------------------------
 * Map functions
 * ------------------------------------------------------------------------- */

/* Frees a map
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_map_free(
     libfwevt_map_t **map,
     libfwevt_error_t **error );

/* -------------------------------------------------------------------------
 * Opcode functions
 * ------------------------------------------------------------------------- */

/* Frees an opcode
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_opcode_free(
     libfwevt_opcode_t **opcode,
     libfwevt_error_t **error );

/* -------------------------------------------------------------------------
 * Provider functions
 * ------------------------------------------------------------------------- */

/* Frees a provider
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_provider_free(
     libfwevt_provider_t **provider,
     libfwevt_error_t **error );

/* Retrieves the number of channels
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_provider_get_number_of_channels(
     libfwevt_provider_t *provider,
     int *number_of_channels,
     libfwevt_error_t **error );

/* Retrieves a specific channel
 *
 * This function is deprecated, use libfwevt_provider_get_channel_by_index instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_DEPRECATED \
LIBFWEVT_EXTERN \
int libfwevt_provider_get_channel(
     libfwevt_provider_t *provider,
     int channel_index,
     libfwevt_channel_t **channel,
     libfwevt_error_t **error );

/* Retrieves a specific channel
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_provider_get_channel_by_index(
     libfwevt_provider_t *provider,
     int channel_index,
     libfwevt_channel_t **channel,
     libfwevt_error_t **error );

/* Retrieves the number of events
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_provider_get_number_of_events(
     libfwevt_provider_t *provider,
     int *number_of_events,
     libfwevt_error_t **error );

/* Retrieves a specific event
 *
 * This function is deprecated, use libfwevt_provider_get_event_by_index instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_DEPRECATED \
LIBFWEVT_EXTERN \
int libfwevt_provider_get_event(
     libfwevt_provider_t *provider,
     int event_index,
     libfwevt_event_t **event,
     libfwevt_error_t **error );

/* Retrieves a specific event
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_provider_get_event_by_index(
     libfwevt_provider_t *provider,
     int event_index,
     libfwevt_event_t **event,
     libfwevt_error_t **error );

/* Retrieves a specific event by identifier
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_provider_get_event_by_identifier(
     libfwevt_provider_t *provider,
     uint32_t event_identifier,
     libfwevt_event_t **event,
     libfwevt_error_t **error );

/* Retrieves the number of keywords
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_provider_get_number_of_keywords(
     libfwevt_provider_t *provider,
     int *number_of_keywords,
     libfwevt_error_t **error );

/* Retrieves a specific keyword
 *
 * This function is deprecated, use libfwevt_provider_get_keyword_by_index instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_DEPRECATED \
LIBFWEVT_EXTERN \
int libfwevt_provider_get_keyword(
     libfwevt_provider_t *provider,
     int keyword_index,
     libfwevt_keyword_t **keyword,
     libfwevt_error_t **error );

/* Retrieves a specific keyword
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_provider_get_keyword_by_index(
     libfwevt_provider_t *provider,
     int keyword_index,
     libfwevt_keyword_t **keyword,
     libfwevt_error_t **error );

/* Retrieves the number of levels
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_provider_get_number_of_levels(
     libfwevt_provider_t *provider,
     int *number_of_levels,
     libfwevt_error_t **error );

/* Retrieves a specific level
 *
 * This function is deprecated, use libfwevt_provider_get_level_by_index instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_DEPRECATED \
LIBFWEVT_EXTERN \
int libfwevt_provider_get_level(
     libfwevt_provider_t *provider,
     int level_index,
     libfwevt_level_t **level,
     libfwevt_error_t **error );

/* Retrieves a specific level
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_provider_get_level_by_index(
     libfwevt_provider_t *provider,
     int level_index,
     libfwevt_level_t **level,
     libfwevt_error_t **error );

/* Retrieves the number of maps
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_provider_get_number_of_maps(
     libfwevt_provider_t *provider,
     int *number_of_maps,
     libfwevt_error_t **error );

/* Retrieves a specific map
 *
 * This function is deprecated, use libfwevt_provider_get_map_by_index instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_DEPRECATED \
LIBFWEVT_EXTERN \
int libfwevt_provider_get_map(
     libfwevt_provider_t *provider,
     int map_index,
     libfwevt_map_t **map,
     libfwevt_error_t **error );

/* Retrieves a specific map
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_provider_get_map_by_index(
     libfwevt_provider_t *provider,
     int map_index,
     libfwevt_map_t **map,
     libfwevt_error_t **error );

/* Retrieves the number of opcodes
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_provider_get_number_of_opcodes(
     libfwevt_provider_t *provider,
     int *number_of_opcodes,
     libfwevt_error_t **error );

/* Retrieves a specific opcode
 *
 * This function is deprecated, use libfwevt_provider_get_opcode_by_index instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_DEPRECATED \
LIBFWEVT_EXTERN \
int libfwevt_provider_get_opcode(
     libfwevt_provider_t *provider,
     int opcode_index,
     libfwevt_opcode_t **opcode,
     libfwevt_error_t **error );

/* Retrieves a specific opcode
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_provider_get_opcode_by_index(
     libfwevt_provider_t *provider,
     int opcode_index,
     libfwevt_opcode_t **opcode,
     libfwevt_error_t **error );

/* Retrieves the number of tasks
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_provider_get_number_of_tasks(
     libfwevt_provider_t *provider,
     int *number_of_tasks,
     libfwevt_error_t **error );

/* Retrieves a specific task
 *
 * This function is deprecated, use libfwevt_provider_get_task_by_index instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_DEPRECATED \
LIBFWEVT_EXTERN \
int libfwevt_provider_get_task(
     libfwevt_provider_t *provider,
     int task_index,
     libfwevt_task_t **task,
     libfwevt_error_t **error );

/* Retrieves a specific task
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_provider_get_task_by_index(
     libfwevt_provider_t *provider,
     int task_index,
     libfwevt_task_t **task,
     libfwevt_error_t **error );

/* Retrieves the number of templates
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_provider_get_number_of_templates(
     libfwevt_provider_t *provider,
     int *number_of_templates,
     libfwevt_error_t **error );

/* Retrieves a specific template
 *
 * This function is deprecated, use libfwevt_provider_get_template_by_index instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_DEPRECATED \
LIBFWEVT_EXTERN \
int libfwevt_provider_get_template(
     libfwevt_provider_t *provider,
     int template_index,
     libfwevt_template_t **wevt_template,
     libfwevt_error_t **error );

/* Retrieves a specific template
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_provider_get_template_by_index(
     libfwevt_provider_t *provider,
     int template_index,
     libfwevt_template_t **wevt_template,
     libfwevt_error_t **error );

/* Retrieves a specific template by offset
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_provider_get_template_by_offset(
     libfwevt_provider_t *provider,
     uint32_t offset,
     libfwevt_template_t **wevt_template,
     libfwevt_error_t **error );

/* -------------------------------------------------------------------------
 * Task functions
 * ------------------------------------------------------------------------- */

/* Frees a task
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_task_free(
     libfwevt_task_t **task,
     libfwevt_error_t **error );

/* -------------------------------------------------------------------------
 * Template functions
 * ------------------------------------------------------------------------- */

/* Creates a template
 * Make sure the value template is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_template_initialize(
     libfwevt_template_t **wevt_template,
     libfwevt_error_t **error );

/* Frees a template
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_template_free(
     libfwevt_template_t **wevt_template,
     libfwevt_error_t **error );

/* Reads the template
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_template_read(
     libfwevt_template_t *wevt_template,
     const uint8_t *data,
     size_t data_size,
     size_t data_offset,
     libfwevt_error_t **error );

/* Reads the template XML document
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_template_read_xml_document(
     libfwevt_template_t *wevt_template,
     libfwevt_xml_document_t *xml_document,
     libfwevt_error_t **error );

/* Sets the ASCII codepage
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_template_set_ascii_codepage(
     libfwevt_template_t *wevt_template,
     int ascii_codepage,
     libfwevt_error_t **error );

/* Retrieves the data
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_template_get_data(
     libfwevt_template_t *wevt_template,
     const uint8_t **data,
     size_t *data_size,
     libfwevt_error_t **error );

/* Sets the data
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_template_set_data(
     libfwevt_template_t *wevt_template,
     const uint8_t *data,
     size_t data_size,
     libfwevt_error_t **error );

/* Retrieves the offset
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_template_get_offset(
     libfwevt_template_t *wevt_template,
     uint32_t *offset,
     libfwevt_error_t **error );

/* Sets the offset
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_template_set_offset(
     libfwevt_template_t *wevt_template,
     uint32_t offset,
     libfwevt_error_t **error );

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_template_get_size(
     libfwevt_template_t *wevt_template,
     uint32_t *size,
     libfwevt_error_t **error );

/* -------------------------------------------------------------------------
 * XML document functions
 * ------------------------------------------------------------------------- */

/* Creates an XML document
 * Make sure the value channel is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_document_initialize(
     libfwevt_xml_document_t **xml_document,
     libfwevt_error_t **error );

/* Frees an XML document
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_document_free(
     libfwevt_xml_document_t **xml_document,
     libfwevt_error_t **error );

/* Clones the binary XML document
 *
 * This function is deprecated and threre is no replacement.
 *
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_DEPRECATED \
LIBFWEVT_EXTERN \
int libfwevt_xml_document_clone(
     libfwevt_xml_document_t **destination_xml_document,
     libfwevt_xml_document_t *source_xml_document,
     libfwevt_error_t **error );

/* Retrieves the root XML tag
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_document_get_root_xml_tag(
     libfwevt_xml_document_t *xml_document,
     libfwevt_xml_tag_t **root_xml_tag,
     libfwevt_error_t **error );

/* Reads a binary XML document
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_document_read(
     libfwevt_xml_document_t *xml_document,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     int ascii_codepage,
     uint8_t flags,
     libfwevt_error_t **error );

/* Retrieves the size of the UTF-8 formatted string of the XML document
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_document_get_utf8_xml_string_size(
     libfwevt_xml_document_t *xml_document,
     size_t *utf8_string_size,
     libfwevt_error_t **error );

/* Retrieves the UTF-8 formatted string of the XML document
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_document_get_utf8_xml_string(
     libfwevt_xml_document_t *xml_document,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libfwevt_error_t **error );

/* Retrieves the size of the UTF-16 formatted string of the XML document
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_document_get_utf16_xml_string_size(
     libfwevt_xml_document_t *xml_document,
     size_t *utf16_string_size,
     libfwevt_error_t **error );

/* Retrieves the UTF-16 formatted string of the XML document
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_document_get_utf16_xml_string(
     libfwevt_xml_document_t *xml_document,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libfwevt_error_t **error );

#if defined( HAVE_DEBUG_OUTPUT )

/* Debug prints the XML document
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_document_debug_print(
     libfwevt_xml_document_t *xml_document,
     libfwevt_error_t **error );

#endif /* #if defined( HAVE_DEBUG_OUTPUT ) */

/* -------------------------------------------------------------------------
 * XML tag functions
 * ------------------------------------------------------------------------- */

/* Retrieves the size of the UTF-8 formatted name
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_utf8_name_size(
     libfwevt_xml_tag_t *xml_tag,
     size_t *utf8_string_size,
     libfwevt_error_t **error );

/* Retrieves the UTF-8 formatted name
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_utf8_name(
     libfwevt_xml_tag_t *xml_tag,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libfwevt_error_t **error );

/* Retrieves the size of the UTF-16 formatted name
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_utf16_name_size(
     libfwevt_xml_tag_t *xml_tag,
     size_t *utf16_string_size,
     libfwevt_error_t **error );

/* Retrieves the UTF-16 formatted name
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_utf16_name(
     libfwevt_xml_tag_t *xml_tag,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libfwevt_error_t **error );

/* Retrieves the size of the UTF-8 formatted value
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_utf8_value_size(
     libfwevt_xml_tag_t *xml_tag,
     size_t *utf8_string_size,
     libfwevt_error_t **error );

/* Retrieves the UTF-8 formatted value
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_utf8_value(
     libfwevt_xml_tag_t *xml_tag,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libfwevt_error_t **error );

/* Retrieves the size of the UTF-16 formatted value
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_utf16_value_size(
     libfwevt_xml_tag_t *xml_tag,
     size_t *utf16_string_size,
     libfwevt_error_t **error );

/* Retrieves the UTF-16 formatted value
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_utf16_value(
     libfwevt_xml_tag_t *xml_tag,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libfwevt_error_t **error );

/* Retrieves the number of attributes
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_number_of_attributes(
     libfwevt_xml_tag_t *xml_tag,
     int *number_of_attributes,
     libfwevt_error_t **error );

/* Retrieves a specific attribute
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_attribute_by_index(
     libfwevt_xml_tag_t *xml_tag,
     int attribute_index,
     libfwevt_xml_tag_t **attribute_xml_tag,
     libfwevt_error_t **error );

/* Retrieves the attribute for the specific UTF-8 encoded name
 * Returns 1 if successful, 0 if no such value or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_attribute_by_utf8_name(
     libfwevt_xml_tag_t *xml_tag,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfwevt_xml_tag_t **attribute_xml_tag,
     libfwevt_error_t **error );

/* Retrieves the attribute for the specific UTF-16 encoded name
 * Returns 1 if successful, 0 if no such value or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_attribute_by_utf16_name(
     libfwevt_xml_tag_t *xml_tag,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfwevt_xml_tag_t **attribute_xml_tag,
     libfwevt_error_t **error );

/* Retrieves the number of elements
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_number_of_elements(
     libfwevt_xml_tag_t *xml_tag,
     int *number_of_elements,
     libfwevt_error_t **error );

/* Retrieves a specific element
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_element_by_index(
     libfwevt_xml_tag_t *xml_tag,
     int element_index,
     libfwevt_xml_tag_t **element_xml_tag,
     libfwevt_error_t **error );

/* Retrieves the element for the specific UTF-8 encoded name
 * Returns 1 if successful, 0 if no such value or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_element_by_utf8_name(
     libfwevt_xml_tag_t *xml_tag,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libfwevt_xml_tag_t **element_xml_tag,
     libfwevt_error_t **error );

/* Retrieves the element for the specific UTF-16 encoded name
 * Returns 1 if successful, 0 if no such value or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_element_by_utf16_name(
     libfwevt_xml_tag_t *xml_tag,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libfwevt_xml_tag_t **element_xml_tag,
     libfwevt_error_t **error );

/* Retrieves the flags
 * Returns 1 if successful or -1 on error
 */
LIBFWEVT_EXTERN \
int libfwevt_xml_tag_get_flags(
     libfwevt_xml_tag_t *xml_tag,
     uint8_t *flags,
     libfwevt_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWEVT_H ) */

