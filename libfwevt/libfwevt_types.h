/*
 * The internal type definitions
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

#if !defined( _LIBFWEVT_INTERNAL_TYPES_H )
#define _LIBFWEVT_INTERNAL_TYPES_H

#include <common.h>
#include <types.h>

/* Define HAVE_LOCAL_LIBFWEVT for local use of libfwevt
 * The definitions in <libfwevt/types.h> are copied here
 * for local use of libfwevt
 */
#if defined( HAVE_LOCAL_LIBFWEVT )

/* The following type definitions hide internal data structures
 */
#if defined( HAVE_DEBUG_OUTPUT ) && !defined( WINAPI )
typedef struct libfwevt_channel {}		libfwevt_channel_t;
typedef struct libfwevt_event {}		libfwevt_event_t;
typedef struct libfwevt_keyword {}		libfwevt_keyword_t;
typedef struct libfwevt_level {}		libfwevt_level_t;
typedef struct libfwevt_manifest {}		libfwevt_manifest_t;
typedef struct libfwevt_map {}			libfwevt_map_t;
typedef struct libfwevt_opcode {}		libfwevt_opcode_t;
typedef struct libfwevt_provider {}		libfwevt_provider_t;
typedef struct libfwevt_task {}			libfwevt_task_t;
typedef struct libfwevt_template {}		libfwevt_template_t;
typedef struct libfwevt_template_item {}	libfwevt_template_item_t;
typedef struct libfwevt_xml_document {}		libfwevt_xml_document_t;
typedef struct libfwevt_xml_tag {}		libfwevt_xml_tag_t;
typedef struct libfwevt_xml_template_value {}	libfwevt_xml_template_value_t;
typedef struct libfwevt_xml_value {}		libfwevt_xml_value_t;

#else
typedef intptr_t libfwevt_channel_t;
typedef intptr_t libfwevt_event_t;
typedef intptr_t libfwevt_keyword_t;
typedef intptr_t libfwevt_level_t;
typedef intptr_t libfwevt_manifest_t;
typedef intptr_t libfwevt_map_t;
typedef intptr_t libfwevt_opcode_t;
typedef intptr_t libfwevt_provider_t;
typedef intptr_t libfwevt_task_t;
typedef intptr_t libfwevt_template_t;
typedef intptr_t libfwevt_template_item_t;
typedef intptr_t libfwevt_xml_document_t;
typedef intptr_t libfwevt_xml_tag_t;
typedef intptr_t libfwevt_xml_template_value_t;
typedef intptr_t libfwevt_xml_value_t;

#endif /* defined( HAVE_DEBUG_OUTPUT ) && !defined( WINAPI ) */

#endif /* defined( HAVE_LOCAL_LIBFWEVT ) */

#endif /* !defined( _LIBFWEVT_INTERNAL_TYPES_H ) */

