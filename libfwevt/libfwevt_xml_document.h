/*
 * Windows Event Log binary XML document functions
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

#if !defined( _LIBFWEVT_XML_DOCUMENT_H )
#define _LIBFWEVT_XML_DOCUMENT_H

#include <common.h>
#include <types.h>

#include "libfwevt_extern.h"
#include "libfwevt_libcdata.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_types.h"
#include "libfwevt_xml_tag.h"
#include "libfwevt_xml_token.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfwevt_internal_xml_document libfwevt_internal_xml_document_t;

struct libfwevt_internal_xml_document
{
	/* The root XML tag
	 */
	libfwevt_xml_tag_t *root_xml_tag;

	/* The size
	 */
	size_t size;
};

LIBFWEVT_EXTERN \
int libfwevt_xml_document_initialize(
     libfwevt_xml_document_t **xml_document,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_document_free(
     libfwevt_xml_document_t **xml_document,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_document_get_root_xml_tag(
     libfwevt_xml_document_t *xml_document,
     libfwevt_xml_tag_t **root_xml_tag,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_document_read(
     libfwevt_xml_document_t *xml_document,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     int ascii_codepage,
     uint8_t flags,
     libcerror_error_t **error );

int libfwevt_xml_document_read_with_template_values(
     libfwevt_xml_document_t *xml_document,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     int ascii_codepage,
     uint8_t flags,
     libcdata_array_t *template_values_array,
     libcerror_error_t **error );

int libfwevt_xml_document_read_attribute(
     libfwevt_internal_xml_document_t *xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     int ascii_codepage,
     uint8_t flags,
     libcdata_array_t *template_values_array,
     libfwevt_xml_tag_t *xml_tag,
     int element_recursion_depth,
     int template_instance_recursion_depth,
     libcerror_error_t **error );

int libfwevt_xml_document_read_cdata_section(
     libfwevt_internal_xml_document_t *xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     libfwevt_xml_tag_t *xml_tag,
     libcerror_error_t **error );

int libfwevt_xml_document_read_character_reference(
     libfwevt_internal_xml_document_t *xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     libfwevt_xml_tag_t *xml_tag,
     libcerror_error_t **error );

int libfwevt_xml_document_read_element(
     libfwevt_internal_xml_document_t *xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     int ascii_codepage,
     uint8_t flags,
     libcdata_array_t *template_values_array,
     libfwevt_xml_tag_t *xml_tag,
     int element_recursion_depth,
     int template_instance_recursion_depth,
     libcerror_error_t **error );

int libfwevt_xml_document_read_entity_reference(
     libfwevt_internal_xml_document_t *xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     uint8_t flags,
     libfwevt_xml_tag_t *xml_tag,
     libcerror_error_t **error );

int libfwevt_xml_document_read_fragment(
     libfwevt_internal_xml_document_t *xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     int ascii_codepage,
     uint8_t flags,
     libcdata_array_t *template_values_array,
     libfwevt_xml_tag_t *xml_tag,
     int element_recursion_depth,
     int template_instance_recursion_depth,
     libcerror_error_t **error );

int libfwevt_xml_document_read_fragment_header(
     libfwevt_internal_xml_document_t *xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     libcerror_error_t **error );

int libfwevt_xml_document_read_name(
     libfwevt_internal_xml_document_t *xml_document,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     uint8_t flags,
     uint32_t *name_data_size,
     libfwevt_xml_tag_t *xml_tag,
     libcerror_error_t **error );

int libfwevt_xml_document_read_normal_substitution(
     libfwevt_internal_xml_document_t *xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     int ascii_codepage,
     uint8_t flags,
     libcdata_array_t *template_values_array,
     size_t *template_value_offset,
     libfwevt_xml_tag_t *xml_tag,
     int element_recursion_depth,
     int template_instance_recursion_depth,
     libcerror_error_t **error );

int libfwevt_xml_document_read_optional_substitution(
     libfwevt_internal_xml_document_t *xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     int ascii_codepage,
     uint8_t flags,
     libcdata_array_t *template_values_array,
     size_t *template_value_offset,
     libfwevt_xml_tag_t *xml_tag,
     int element_recursion_depth,
     int template_instance_recursion_depth,
     libcerror_error_t **error );

int libfwevt_xml_document_read_pi_data(
     libfwevt_internal_xml_document_t *xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     libfwevt_xml_tag_t *xml_tag,
     libcerror_error_t **error );

int libfwevt_xml_document_read_pi_target(
     libfwevt_internal_xml_document_t *xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     uint8_t flags,
     libfwevt_xml_tag_t *xml_tag,
     libcerror_error_t **error );

int libfwevt_xml_document_read_template_instance(
     libfwevt_internal_xml_document_t *xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     int ascii_codepage,
     uint8_t flags,
     libfwevt_xml_tag_t *xml_tag,
     int element_recursion_depth,
     int template_instance_recursion_depth,
     libcerror_error_t **error );

int libfwevt_xml_document_read_template_instance_values(
     libfwevt_internal_xml_document_t *xml_document,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     libcdata_array_t **template_values_array,
     size_t *template_values_size,
     libcerror_error_t **error );

int libfwevt_xml_document_read_value(
     libfwevt_internal_xml_document_t *xml_document,
     libfwevt_xml_token_t *xml_token,
     const uint8_t *binary_data,
     size_t binary_data_size,
     size_t binary_data_offset,
     libfwevt_xml_tag_t *xml_tag,
     libcerror_error_t **error );

int libfwevt_xml_document_substitute_template_value(
     libfwevt_internal_xml_document_t *xml_document,
     const uint8_t *binary_data,
     size_t binary_data_size,
     int ascii_codepage,
     uint8_t flags,
     libcdata_array_t *template_values_array,
     uint16_t template_value_index,
     uint8_t template_value_type,
     size_t *template_value_offset,
     libfwevt_xml_tag_t *xml_tag,
     int element_recursion_depth,
     int template_instance_recursion_depth,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_document_get_utf8_xml_string_size(
     libfwevt_xml_document_t *xml_document,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_document_get_utf8_xml_string(
     libfwevt_xml_document_t *xml_document,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_document_get_utf16_xml_string_size(
     libfwevt_xml_document_t *xml_document,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFWEVT_EXTERN \
int libfwevt_xml_document_get_utf16_xml_string(
     libfwevt_xml_document_t *xml_document,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( HAVE_DEBUG_OUTPUT )

LIBFWEVT_EXTERN \
int libfwevt_xml_document_debug_print(
     libfwevt_xml_document_t *xml_document,
     libcerror_error_t **error );

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWEVT_XML_DOCUMENT_H ) */

