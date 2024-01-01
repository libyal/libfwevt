/*
 * Event functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libfwevt_event.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_libcnotify.h"
#include "libfwevt_libuna.h"
#include "libfwevt_types.h"

#include "fwevt_template.h"

/* Creates an event
 * Make sure the value event is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwevt_event_initialize(
     libfwevt_event_t **event,
     libcerror_error_t **error )
{
	libfwevt_internal_event_t *internal_event = NULL;
	static char *function                     = "libfwevt_event_initialize";

	if( event == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid event.",
		 function );

		return( -1 );
	}
	if( *event != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid event value already set.",
		 function );

		return( -1 );
	}
	internal_event = memory_allocate_structure(
	                  libfwevt_internal_event_t );

	if( internal_event == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create event.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_event,
	     0,
	     sizeof( libfwevt_internal_event_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear event.",
		 function );

		goto on_error;
	}
	*event = (libfwevt_event_t *) internal_event;

	return( 1 );

on_error:
	if( internal_event != NULL )
	{
		memory_free(
		 internal_event );
	}
	return( -1 );
}

/* Frees an event
 * Returns 1 if successful or -1 on error
 */
int libfwevt_event_free(
     libfwevt_event_t **event,
     libcerror_error_t **error )
{
	static char *function = "libfwevt_event_free";

	if( event == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid event.",
		 function );

		return( -1 );
	}
	if( *event != NULL )
	{
		*event = NULL;
	}
	return( 1 );
}

/* Frees an event
 * Returns 1 if successful or -1 on error
 */
int libfwevt_internal_event_free(
     libfwevt_internal_event_t **internal_event,
     libcerror_error_t **error )
{
	static char *function = "libfwevt_internal_event_free";

	if( internal_event == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid event.",
		 function );

		return( -1 );
	}
	if( *internal_event != NULL )
	{
		memory_free(
		 *internal_event );

		*internal_event = NULL;
	}
	return( 1 );
}

/* Reads the event
 * Returns 1 if successful or -1 on error
 */
int libfwevt_event_read_data(
     libfwevt_event_t *event,
     const uint8_t *data,
     size_t data_size,
     size_t data_offset,
     libcerror_error_t **error )
{
	libfwevt_internal_event_t *internal_event = NULL;
	fwevt_template_event_t *wevt_event        = NULL;
	static char *function                     = "libfwevt_event_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit                      = 0;
	uint32_t value_32bit                      = 0;
	uint16_t value_16bit                      = 0;
#endif

	if( event == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid event.",
		 function );

		return( -1 );
	}
	internal_event = (libfwevt_internal_event_t *) event;

	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_offset >= data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( data_size < sizeof( fwevt_template_event_t ) )
	 || ( data_offset > ( data_size - sizeof( fwevt_template_event_t ) ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		return( -1 );
	}
	wevt_event = (fwevt_template_event_t *) &( data[ data_offset ] );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: event data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) wevt_event,
		 sizeof( fwevt_template_event_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint16_little_endian(
	 wevt_event->identifier,
	 internal_event->identifier );

	byte_stream_copy_to_uint32_little_endian(
	 wevt_event->message_identifier,
	 internal_event->message_identifier );

	byte_stream_copy_to_uint32_little_endian(
	 wevt_event->template_offset,
	 internal_event->template_offset );

	byte_stream_copy_to_uint32_little_endian(
	 wevt_event->opcode_offset,
	 internal_event->opcode_offset );

	byte_stream_copy_to_uint32_little_endian(
	 wevt_event->level_offset,
	 internal_event->level_offset );

	byte_stream_copy_to_uint32_little_endian(
	 wevt_event->task_offset,
	 internal_event->task_offset );

	byte_stream_copy_to_uint32_little_endian(
	 wevt_event->flags,
	 internal_event->flags );

	internal_event->version = wevt_event->version;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: identifier\t\t\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 internal_event->identifier );

		libcnotify_printf(
		 "%s: version\t\t\t\t\t: %" PRIu8 "\n",
		 function,
		 wevt_event->version );

		libcnotify_printf(
		 "%s: channel\t\t\t\t\t: %" PRIu8 "\n",
		 function,
		 wevt_event->channel );

		libcnotify_printf(
		 "%s: level\t\t\t\t\t\t: %" PRIu8 "\n",
		 function,
		 wevt_event->level );

		libcnotify_printf(
		 "%s: opcode\t\t\t\t\t: %" PRIu8 "\n",
		 function,
		 wevt_event->opcode );

		byte_stream_copy_to_uint16_little_endian(
		 wevt_event->task,
		 value_16bit );
		libcnotify_printf(
		 "%s: task\t\t\t\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint64_little_endian(
		 wevt_event->keywords,
		 value_64bit );
		libcnotify_printf(
		 "%s: keywords\t\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		libcnotify_printf(
		 "%s: message identifier\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 internal_event->message_identifier );

		libcnotify_printf(
		 "%s: template offset\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 internal_event->template_offset );

		libcnotify_printf(
		 "%s: opcode offset\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 internal_event->opcode_offset );

		libcnotify_printf(
		 "%s: level offset\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 internal_event->level_offset );

		libcnotify_printf(
		 "%s: task offset\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 internal_event->task_offset );

		byte_stream_copy_to_uint32_little_endian(
		 wevt_event->unknown3,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown3\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 wevt_event->unknown4,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown4\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: flags\t\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 internal_event->flags );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

/* Retrieves the identifier
 * Returns 1 if successful or -1 on error
 */
int libfwevt_event_get_identifier(
     libfwevt_event_t *event,
     uint32_t *identifier,
     libcerror_error_t **error )
{
	libfwevt_internal_event_t *internal_event = NULL;
	static char *function                     = "libfwevt_event_get_identifier";

	if( event == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid event.",
		 function );

		return( -1 );
	}
	internal_event = (libfwevt_internal_event_t *) event;

	if( identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid identifier.",
		 function );

		return( -1 );
	}
	*identifier = (uint32_t) internal_event->identifier;

	return( 1 );
}

/* Retrieves the version
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfwevt_event_get_version(
     libfwevt_event_t *event,
     uint8_t *version,
     libcerror_error_t **error )
{
	libfwevt_internal_event_t *internal_event = NULL;
	static char *function                     = "libfwevt_event_get_version";

	if( event == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid event.",
		 function );

		return( -1 );
	}
	internal_event = (libfwevt_internal_event_t *) event;

	if( version == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid version.",
		 function );

		return( -1 );
	}
	*version = internal_event->version;

	return( 1 );
}

/* Retrieves the message identifier
 * Returns 1 if successful or -1 on error
 */
int libfwevt_event_get_message_identifier(
     libfwevt_event_t *event,
     uint32_t *message_identifier,
     libcerror_error_t **error )
{
	libfwevt_internal_event_t *internal_event = NULL;
	static char *function                     = "libfwevt_event_get_message_identifier";

	if( event == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid event.",
		 function );

		return( -1 );
	}
	internal_event = (libfwevt_internal_event_t *) event;

	if( message_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid message identifier.",
		 function );

		return( -1 );
	}
	*message_identifier = internal_event->message_identifier;

	return( 1 );
}

/* Retrieves the template offset
 * Returns 1 if successful or -1 on error
 */
int libfwevt_event_get_template_offset(
     libfwevt_event_t *event,
     uint32_t *template_offset,
     libcerror_error_t **error )
{
	libfwevt_internal_event_t *internal_event = NULL;
	static char *function                     = "libfwevt_event_get_template_offset";

	if( event == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid event.",
		 function );

		return( -1 );
	}
	internal_event = (libfwevt_internal_event_t *) event;

	if( template_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template offset.",
		 function );

		return( -1 );
	}
	*template_offset = internal_event->template_offset;

	return( 1 );
}

