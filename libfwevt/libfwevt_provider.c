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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libfwevt_channel.h"
#include "libfwevt_event.h"
#include "libfwevt_keyword.h"
#include "libfwevt_level.h"
#include "libfwevt_libcdata.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_libcnotify.h"
#include "libfwevt_libfguid.h"
#include "libfwevt_libuna.h"
#include "libfwevt_map.h"
#include "libfwevt_opcode.h"
#include "libfwevt_provider.h"
#include "libfwevt_task.h"
#include "libfwevt_template.h"
#include "libfwevt_types.h"

#include "fwevt_template.h"

/* Creates a provider
 * Make sure the value provider is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_initialize(
     libfwevt_provider_t **provider,
     const uint8_t *identifier,
     size_t identifier_size,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_initialize";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	if( *provider != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid provider value already set.",
		 function );

		return( -1 );
	}
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
	if( identifier_size != 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid identifier size value out of bounds.",
		 function );

		return( -1 );
	}
	internal_provider = memory_allocate_structure(
	                     libfwevt_internal_provider_t );

	if( internal_provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create provider.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_provider,
	     0,
	     sizeof( libfwevt_internal_provider_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear provider.",
		 function );

		memory_free(
		 internal_provider );

		return( -1 );
	}
	if( memory_copy(
	     internal_provider->identifier,
	     identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_provider->channels_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create channels array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_provider->events_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create events array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_provider->keywords_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create keywords array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_provider->levels_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create levels array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_provider->maps_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create maps array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_provider->opcodes_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create opcodes array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_provider->tasks_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create tasks array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_provider->templates_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create templates array.",
		 function );

		goto on_error;
	}
	*provider = (libfwevt_provider_t *) internal_provider;

	return( 1 );

on_error:
	if( internal_provider != NULL )
	{
		if( internal_provider->tasks_array != NULL )
		{
			libcdata_array_free(
			 &( internal_provider->tasks_array ),
			 NULL,
			 NULL );
		}
		if( internal_provider->opcodes_array != NULL )
		{
			libcdata_array_free(
			 &( internal_provider->opcodes_array ),
			 NULL,
			 NULL );
		}
		if( internal_provider->maps_array != NULL )
		{
			libcdata_array_free(
			 &( internal_provider->maps_array ),
			 NULL,
			 NULL );
		}
		if( internal_provider->levels_array != NULL )
		{
			libcdata_array_free(
			 &( internal_provider->levels_array ),
			 NULL,
			 NULL );
		}
		if( internal_provider->keywords_array != NULL )
		{
			libcdata_array_free(
			 &( internal_provider->keywords_array ),
			 NULL,
			 NULL );
		}
		if( internal_provider->events_array != NULL )
		{
			libcdata_array_free(
			 &( internal_provider->events_array ),
			 NULL,
			 NULL );
		}
		if( internal_provider->channels_array != NULL )
		{
			libcdata_array_free(
			 &( internal_provider->channels_array ),
			 NULL,
			 NULL );
		}
		memory_free(
		 internal_provider );
	}
	return( -1 );
}

/* Frees a provider
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_free(
     libfwevt_provider_t **provider,
     libcerror_error_t **error )
{
	static char *function = "libfwevt_provider_free";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	if( *provider != NULL )
	{
		*provider = NULL;
	}
	return( 1 );
}

/* Frees a provider
 * Returns 1 if successful or -1 on error
 */
int libfwevt_internal_provider_free(
     libfwevt_internal_provider_t **internal_provider,
     libcerror_error_t **error )
{
	static char *function = "libfwevt_internal_provider_free";
	int result            = 1;

	if( internal_provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	if( *internal_provider != NULL )
	{
		if( libcdata_array_free(
		     &( ( *internal_provider )->channels_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_channel_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free channels array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( ( *internal_provider )->events_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_event_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free events array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( ( *internal_provider )->keywords_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_keyword_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free keywords array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( ( *internal_provider )->levels_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_level_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free levels array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( ( *internal_provider )->maps_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_map_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free maps array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( ( *internal_provider )->opcodes_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_opcode_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free opcodes array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( ( *internal_provider )->tasks_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_task_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free tasks array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( ( *internal_provider )->templates_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_template_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free templates array.",
			 function );

			result = -1;
		}
		memory_free(
		 *internal_provider );

		*internal_provider = NULL;
	}
	return( result );
}

/* Reads the provider
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_read_data(
     libfwevt_provider_t *provider,
     const uint8_t *data,
     size_t data_size,
     size_t data_offset,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	fwevt_template_provider_t *wevt_provider        = NULL;
	static char *function                           = "libfwevt_provider_read_data";
	uint32_t descriptor_index                       = 0;
	uint32_t descriptor_offset                      = 0;
	uint32_t descriptor_type                        = 0;
	uint32_t number_of_descriptors                  = 0;
	uint32_t number_of_unknown2                     = 0;
	uint32_t unknown2_index                         = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit                            = 0;
#endif

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

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
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( data_size - data_offset ) < sizeof( fwevt_template_provider_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
	wevt_provider = (fwevt_template_provider_t *) &( data[ data_offset ] );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading event provider data at offset: %" PRIzd " (0x%08" PRIzx "):\n",
		 function,
		 data_offset,
		 data_offset );

		libcnotify_printf(
		 "%s: event provider data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) wevt_provider,
		 sizeof( fwevt_template_provider_t ),
		 0 );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	byte_stream_copy_to_uint32_little_endian(
	 wevt_provider->number_of_descriptors,
	 number_of_descriptors );

	byte_stream_copy_to_uint32_little_endian(
	 wevt_provider->number_of_unknown2,
	 number_of_unknown2 );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t\t: %c%c%c%c\n",
		 function,
		 wevt_provider->signature[ 0 ],
		 wevt_provider->signature[ 1 ],
		 wevt_provider->signature[ 2 ],
		 wevt_provider->signature[ 3 ] );

		byte_stream_copy_to_uint32_little_endian(
		 wevt_provider->size,
		 value_32bit );
		libcnotify_printf(
		 "%s: size\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 wevt_provider->message_identifier,
		 value_32bit );
		libcnotify_printf(
		 "%s: message identifier\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: number of descriptors\t\t\t: %" PRIu32 "\n",
		 function,
		 number_of_descriptors );

		libcnotify_printf(
		 "%s: number of unknown2\t\t\t\t: %" PRIu32 "\n",
		 function,
		 number_of_unknown2 );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	data_offset += sizeof( fwevt_template_provider_t );

	if( memory_compare(
	     wevt_provider->signature,
	     "WEVT",
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported event provider signature.",
		 function );

		return( -1 );
	}
	if( number_of_descriptors > 0 )
	{
		if( ( number_of_descriptors > ( (uint32_t) UINT32_MAX / 8 ) )
		 || ( ( number_of_descriptors * 8 ) > ( data_size - data_offset ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid number of descriptors value out of bounds.",
			 function );

			return( -1 );
		}
		for( descriptor_index = 0;
		     descriptor_index < number_of_descriptors;
		     descriptor_index++ )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: descriptor: %02" PRIu32 " data:\n",
				 function,
				 descriptor_index );
				libcnotify_print_data(
				 &( data[ data_offset ] ),
				 8,
				 0 );
			}
#endif
			byte_stream_copy_to_uint32_little_endian(
			 &( data[ data_offset ] ),
			 descriptor_offset );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: descriptor: %02" PRIu32 " offset\t\t\t: 0x%08" PRIx32 "\n",
				 function,
				 descriptor_index,
				 descriptor_offset );

				byte_stream_copy_to_uint32_little_endian(
				 &( data[ data_offset + 4 ] ),
				 value_32bit );
				libcnotify_printf(
				 "%s: descriptor: %02" PRIu32 " unknown1\t\t\t: %" PRIu32 "\n",
				 function,
				 descriptor_index,
				 value_32bit );
			}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

			data_offset += 8;

			if( descriptor_offset >= ( data_size - 4 ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid descriptor offset value out of bounds.",
				 function );

				return( -1 );
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: descriptor: %02" PRIu32 " type\t\t\t: %c%c%c%c\n",
				 function,
				 descriptor_index,
				 data[ descriptor_offset ],
				 data[ descriptor_offset + 1 ],
				 data[ descriptor_offset + 2 ],
				 data[ descriptor_offset + 3 ] );
			}
#endif
			byte_stream_copy_to_uint32_big_endian(
			 &( data[ descriptor_offset ] ),
			 descriptor_type );

			switch( descriptor_type )
			{
				/* CHAN */
				case 0x4348414e:
					internal_provider->channels_offset = descriptor_offset;
					break;

				/* EVTN */
				case 0x45564e54:
					internal_provider->events_offset = descriptor_offset;
					break;

				/* KEYW */
				case 0x4b455957:
					internal_provider->keywords_offset = descriptor_offset;
					break;

				/* LEVL */
				case 0x4c45564c:
					internal_provider->levels_offset = descriptor_offset;
					break;

				/* MAPS */
				case 0x4d415053:
					internal_provider->maps_offset = descriptor_offset;
					break;

				/* TASK */
				case 0x5441534b:
					internal_provider->tasks_offset = descriptor_offset;
					break;

				/* TTBL */
				case 0x5454424c:
					internal_provider->templates_offset = descriptor_offset;
					break;

				/* OPCO */
				case 0x4f50434f:
					internal_provider->opcodes_offset = descriptor_offset;
					break;
			}
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "\n" );
		}
#endif
	}
	if( number_of_unknown2 > 0 )
	{
		if( ( number_of_unknown2 > ( (uint32_t) UINT32_MAX / 4 ) )
		 || ( ( number_of_unknown2 * 4 ) > ( data_size - data_offset ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid number of unknown2 value out of bounds.",
			 function );

			return( -1 );
		}
		for( unknown2_index = 0;
		     unknown2_index < number_of_unknown2;
		     unknown2_index++ )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 &( data[ data_offset ] ),
				 value_32bit );
				libcnotify_printf(
				 "%s: unknown2: %02" PRIu32 " value\t\t\t\t: 0x%08" PRIx32 "\n",
				 function,
				 unknown2_index,
				 value_32bit );
			}
#endif
			data_offset += 4;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "\n" );
		}
#endif
	}
	return( 1 );
}

/* Reads the provider channels
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_read_channels(
     libfwevt_provider_t *provider,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	fwevt_template_channels_t *wevt_channels        = NULL;
	libfwevt_channel_t *channel                     = NULL;
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_read_channels";
	size_t data_offset                              = 0;
	uint32_t channel_index                          = 0;
	uint32_t channels_data_size                     = 0;
	uint32_t number_of_channels                     = 0;
	int entry_index                                 = 0;

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

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
	if( (size_t) internal_provider->channels_offset >= data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( data_size - (size_t) internal_provider->channels_offset ) < sizeof( fwevt_template_channels_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		return( -1 );
	}
	if( internal_provider->channels_offset == 0 )
	{
		return( 1 );
	}
	data_offset   = (size_t) internal_provider->channels_offset;
	wevt_channels = (fwevt_template_channels_t *) &( data[ data_offset ] );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading channels data at offset: %" PRIzd " (0x%08" PRIzx "):\n",
		 function,
		 data_offset,
		 data_offset );

		libcnotify_printf(
		 "%s: channels data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) wevt_channels,
		 sizeof( fwevt_template_channels_t ),
		 0 );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	byte_stream_copy_to_uint32_little_endian(
	 wevt_channels->size,
	 channels_data_size );

	byte_stream_copy_to_uint32_little_endian(
	 wevt_channels->number_of_channels,
	 number_of_channels );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c\n",
		 function,
		 wevt_channels->signature[ 0 ],
		 wevt_channels->signature[ 1 ],
		 wevt_channels->signature[ 2 ],
		 wevt_channels->signature[ 3 ] );

		libcnotify_printf(
		 "%s: size\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 channels_data_size );

		libcnotify_printf(
		 "%s: number of channels\t\t\t: %" PRIu32 "\n",
		 function,
		 number_of_channels );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	data_offset += sizeof( fwevt_template_channels_t );

	if( memory_compare(
	     wevt_channels->signature,
	     "CHAN",
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported channels signature.",
		 function );

		goto on_error;
	}
	if( number_of_channels > ( ( data_size - data_offset ) / sizeof( fwevt_template_channel_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		goto on_error;
	}
	if( channels_data_size > 0 )
	{
		if( ( channels_data_size < sizeof( fwevt_template_channels_t ) )
		 || ( channels_data_size >= data_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid channels data size value out of bounds.",
			 function );

			goto on_error;
		}
		channels_data_size -= sizeof( fwevt_template_channels_t );
	}
	for( channel_index = 0;
	     channel_index < number_of_channels;
	     channel_index++ )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: reading channel: %03" PRIu32 " at offset: %" PRIzd " (0x%08" PRIzx "):\n",
			 function,
			 channel_index,
			 data_offset,
			 data_offset );
		}
#endif
		if( libfwevt_channel_initialize(
		     &channel,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create channel: %" PRIu32 ".",
			 function,
			 channel_index );

			goto on_error;
		}
		if( libfwevt_channel_read_data(
		     channel,
		     data,
		     data_size,
		     data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read channel: %" PRIu32 ".",
			 function,
			 channel_index );

			goto on_error;
		}
		if( channels_data_size < sizeof( fwevt_template_channel_t ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid channels data size value out of bounds.",
			 function );

			goto on_error;
		}
		data_offset        += sizeof( fwevt_template_channel_t );
		channels_data_size -= sizeof( fwevt_template_channel_t );

		if( libcdata_array_append_entry(
		     internal_provider->channels_array,
		     &entry_index,
		     (intptr_t *) channel,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append channel: %" PRIu32 " to array.",
			 function,
			 channel_index );

			goto on_error;
		}
		channel = NULL;
	}
/* TODO count data size ?
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( channels_data_size > 0 )
		{
			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ data_offset ] ),
			 channels_data_size,
			 0 );
		}
	}
#endif
*/
	return( 1 );

on_error:
	if( channel != NULL )
	{
		libfwevt_internal_channel_free(
		 (libfwevt_internal_channel_t **) &channel,
		 NULL );
	}
	libcdata_array_empty(
	 internal_provider->channels_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_channel_free,
	 NULL );

	return( -1 );
}

/* Reads the provider events
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_read_events(
     libfwevt_provider_t *provider,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	fwevt_template_events_t *wevt_events            = NULL;
	libfwevt_event_t *event                         = NULL;
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_read_events";
	size_t data_offset                              = 0;
	uint32_t event_index                            = 0;
	uint32_t events_data_size                       = 0;
	uint32_t number_of_events                       = 0;
	int entry_index                                 = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit                            = 0;
#endif

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

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
	if( (size_t) internal_provider->events_offset >= data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( data_size - (size_t) internal_provider->events_offset ) < sizeof( fwevt_template_events_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		return( -1 );
	}
	if( internal_provider->events_offset == 0 )
	{
		return( 1 );
	}
	data_offset = (size_t) internal_provider->events_offset;
	wevt_events = (fwevt_template_events_t *) &( data[ data_offset ] );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading events data at offset: %" PRIzd " (0x%08" PRIzx "):\n",
		 function,
		 data_offset,
		 data_offset );

		libcnotify_printf(
		 "%s: events data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) wevt_events,
		 sizeof( fwevt_template_events_t ),
		 0 );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	byte_stream_copy_to_uint32_little_endian(
	 wevt_events->size,
	 events_data_size );

	byte_stream_copy_to_uint32_little_endian(
	 wevt_events->number_of_events,
	 number_of_events );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c\n",
		 function,
		 wevt_events->signature[ 0 ],
		 wevt_events->signature[ 1 ],
		 wevt_events->signature[ 2 ],
		 wevt_events->signature[ 3 ] );

		libcnotify_printf(
		 "%s: size\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 events_data_size );

		libcnotify_printf(
		 "%s: number of events\t\t\t\t: %" PRIu32 "\n",
		 function,
		 number_of_events );

		byte_stream_copy_to_uint32_little_endian(
		 wevt_events->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	data_offset += sizeof( fwevt_template_events_t );

	if( memory_compare(
	     wevt_events->signature,
	     "EVNT",
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported events signature.",
		 function );

		goto on_error;
	}
	if( number_of_events > ( ( data_size - data_offset ) / sizeof( fwevt_template_event_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		goto on_error;
	}
	if( events_data_size > 0 )
	{
		if( ( events_data_size < sizeof( fwevt_template_events_t ) )
		 || ( events_data_size >= data_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid events data size value out of bounds.",
			 function );

			goto on_error;
		}
		events_data_size -= sizeof( fwevt_template_events_t );
	}
	for( event_index = 0;
	     event_index < number_of_events;
	     event_index++ )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: reading event: %03" PRIu32 " at offset: %" PRIzd " (0x%08" PRIzx "):\n",
			 function,
			 event_index,
			 data_offset,
			 data_offset );
		}
#endif
		if( libfwevt_event_initialize(
		     &event,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create event: %" PRIu32 ".",
			 function,
			 event_index );

			goto on_error;
		}
		if( libfwevt_event_read_data(
		     event,
		     data,
		     data_size,
		     data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read event: %" PRIu32 ".",
			 function,
			 event_index );

			goto on_error;
		}
		if( events_data_size < sizeof( fwevt_template_event_t ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid events data size value out of bounds.",
			 function );

			goto on_error;
		}
		data_offset      += sizeof( fwevt_template_event_t );
		events_data_size -= sizeof( fwevt_template_event_t );

		if( libcdata_array_append_entry(
		     internal_provider->events_array,
		     &entry_index,
		     (intptr_t *) event,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append event: %" PRIu32 " to array.",
			 function,
			 event_index );

			goto on_error;
		}
		event = NULL;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( events_data_size > 0 )
		{
			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ data_offset ] ),
			 events_data_size,
			 0 );
		}
	}
#endif
	return( 1 );

on_error:
	if( event != NULL )
	{
		libfwevt_internal_event_free(
		 (libfwevt_internal_event_t **) &event,
		 NULL );
	}
	libcdata_array_empty(
	 internal_provider->events_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_event_free,
	 NULL );

	return( -1 );
}

/* Reads the provider keywords
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_read_keywords(
     libfwevt_provider_t *provider,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	fwevt_template_keywords_t *keywords             = NULL;
	libfwevt_internal_provider_t *internal_provider = NULL;
	libfwevt_keyword_t *keyword                     = NULL;
	static char *function                           = "libfwevt_provider_read_keywords";
	size_t data_offset                              = 0;
	uint32_t keyword_index                          = 0;
	uint32_t keywords_data_size                     = 0;
	uint32_t number_of_keywords                     = 0;
	int entry_index                                 = 0;

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

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
	if( (size_t) internal_provider->keywords_offset >= data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( data_size - (size_t) internal_provider->keywords_offset ) < sizeof( fwevt_template_keywords_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		return( -1 );
	}
	if( internal_provider->keywords_offset == 0 )
	{
		return( 1 );
	}
	data_offset = (size_t) internal_provider->keywords_offset;
	keywords    = (fwevt_template_keywords_t *) &( data[ data_offset ] );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading keywords data at offset: %" PRIzd " (0x%08" PRIzx "):\n",
		 function,
		 data_offset,
		 data_offset );

		libcnotify_printf(
		 "%s: keywords data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) keywords,
		 sizeof( fwevt_template_keywords_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 keywords->size,
	 keywords_data_size );

	byte_stream_copy_to_uint32_little_endian(
	 keywords->number_of_keywords,
	 number_of_keywords );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c\n",
		 function,
		 keywords->signature[ 0 ],
		 keywords->signature[ 1 ],
		 keywords->signature[ 2 ],
		 keywords->signature[ 3 ] );

		libcnotify_printf(
		 "%s: size\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 keywords_data_size );

		libcnotify_printf(
		 "%s: number of keywords\t\t\t: %" PRIu32 "\n",
		 function,
		 number_of_keywords );

		libcnotify_printf(
		 "\n" );
	}
#endif
	data_offset += sizeof( fwevt_template_keywords_t );

	if( memory_compare(
	     keywords->signature,
	     "KEYW",
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported keywords signature.",
		 function );

		goto on_error;
	}
	if( number_of_keywords > ( ( data_size - data_offset ) / sizeof( fwevt_template_keyword_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		goto on_error;
	}
	if( keywords_data_size > 0 )
	{
		if( ( keywords_data_size < sizeof( fwevt_template_keywords_t ) )
		 || ( keywords_data_size >= data_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid keywords data size value out of bounds.",
			 function );

			goto on_error;
		}
		keywords_data_size -= sizeof( fwevt_template_keywords_t );
	}
	for( keyword_index = 0;
	     keyword_index < number_of_keywords;
	     keyword_index++ )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: reading keyword: %03" PRIu32 " at offset: %" PRIzd " (0x%08" PRIzx "):\n",
			 function,
			 keyword_index,
			 data_offset,
			 data_offset );
		}
#endif
		if( libfwevt_keyword_initialize(
		     &keyword,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create keyword: %" PRIu32 ".",
			 function,
			 keyword_index );

			goto on_error;
		}
		if( libfwevt_keyword_read_data(
		     keyword,
		     data,
		     data_size,
		     data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read keyword: %" PRIu32 ".",
			 function,
			 keyword_index );

			goto on_error;
		}
		if( keywords_data_size < sizeof( fwevt_template_keyword_t ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid keywords data size value out of bounds.",
			 function );

			goto on_error;
		}
		data_offset        += sizeof( fwevt_template_keyword_t );
		keywords_data_size -= sizeof( fwevt_template_keyword_t );

		if( libcdata_array_append_entry(
		     internal_provider->keywords_array,
		     &entry_index,
		     (intptr_t *) keyword,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append keyword: %" PRIu32 " to array.",
			 function,
			 keyword_index );

			goto on_error;
		}
		keyword = NULL;
	}
/* TODO count data size ?
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( keywords_data_size > 0 )
		{
			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ data_offset ] ),
			 keywords_data_size,
			 0 );
		}
	}
#endif
*/
	return( 1 );

on_error:
	if( keyword != NULL )
	{
		libfwevt_internal_keyword_free(
		 (libfwevt_internal_keyword_t **) &keyword,
		 NULL );
	}
	libcdata_array_empty(
	 internal_provider->keywords_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_keyword_free,
	 NULL );

	return( -1 );
}

/* Reads the provider levels
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_read_levels(
     libfwevt_provider_t *provider,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	fwevt_template_levels_t *levels                 = NULL;
	libfwevt_internal_provider_t *internal_provider = NULL;
	libfwevt_level_t *level                         = NULL;
	static char *function                           = "libfwevt_provider_read_levels";
	size_t data_offset                              = 0;
	uint32_t level_index                            = 0;
	uint32_t levels_data_size                       = 0;
	uint32_t number_of_levels                       = 0;
	int entry_index                                 = 0;

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

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
	if( (size_t) internal_provider->levels_offset >= data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( data_size - (size_t) internal_provider->levels_offset ) < sizeof( fwevt_template_levels_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		return( -1 );
	}
	if( internal_provider->levels_offset == 0 )
	{
		return( 1 );
	}
	data_offset = (size_t) internal_provider->levels_offset;
	levels      = (fwevt_template_levels_t *) &( data[ data_offset ] );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading levels data at offset: %" PRIzd " (0x%08" PRIzx "):\n",
		 function,
		 data_offset,
		 data_offset );

		libcnotify_printf(
		 "%s: levels data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) levels,
		 sizeof( fwevt_template_levels_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 levels->size,
	 levels_data_size );

	byte_stream_copy_to_uint32_little_endian(
	 levels->number_of_levels,
	 number_of_levels );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c\n",
		 function,
		 levels->signature[ 0 ],
		 levels->signature[ 1 ],
		 levels->signature[ 2 ],
		 levels->signature[ 3 ] );

		libcnotify_printf(
		 "%s: size\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 levels_data_size );

		libcnotify_printf(
		 "%s: number of levels\t\t\t\t: %" PRIu32 "\n",
		 function,
		 number_of_levels );

		libcnotify_printf(
		 "\n" );
	}
#endif
	data_offset += sizeof( fwevt_template_levels_t );

	if( memory_compare(
	     levels->signature,
	     "LEVL",
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported levels signature.",
		 function );

		goto on_error;
	}
	if( number_of_levels > ( ( data_size - data_offset ) / sizeof( fwevt_template_level_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		goto on_error;
	}
	if( levels_data_size > 0 )
	{
		if( ( levels_data_size < sizeof( fwevt_template_levels_t ) )
		 || ( levels_data_size >= data_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid levels data size value out of bounds.",
			 function );

			goto on_error;
		}
		levels_data_size -= sizeof( fwevt_template_levels_t );
	}
	for( level_index = 0;
	     level_index < number_of_levels;
	     level_index++ )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: reading level: %03" PRIu32 " at offset: %" PRIzd " (0x%08" PRIzx "):\n",
			 function,
			 level_index,
			 data_offset,
			 data_offset );
		}
#endif
		if( libfwevt_level_initialize(
		     &level,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create level: %" PRIu32 ".",
			 function,
			 level_index );

			goto on_error;
		}
		if( libfwevt_level_read_data(
		     level,
		     data,
		     data_size,
		     data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read level: %" PRIu32 ".",
			 function,
			 level_index );

			goto on_error;
		}
		if( levels_data_size < sizeof( fwevt_template_level_t ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid levels data size value out of bounds.",
			 function );

			goto on_error;
		}
		data_offset      += sizeof( fwevt_template_level_t );
		levels_data_size -= sizeof( fwevt_template_level_t );

		if( libcdata_array_append_entry(
		     internal_provider->levels_array,
		     &entry_index,
		     (intptr_t *) level,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append level: %" PRIu32 " to array.",
			 function,
			 level_index );

			goto on_error;
		}
		level = NULL;
	}
/* TODO count data size ?
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( levels_data_size > 0 )
		{
			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ data_offset ] ),
			 levels_data_size,
			 0 );
		}
	}
#endif
*/
	return( 1 );

on_error:
	if( level != NULL )
	{
		libfwevt_internal_level_free(
		 (libfwevt_internal_level_t **) &level,
		 NULL );
	}
	libcdata_array_empty(
	 internal_provider->levels_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_level_free,
	 NULL );

	return( -1 );
}

/* Reads the provider maps
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_read_maps(
     libfwevt_provider_t *provider,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	fwevt_template_maps_t *maps                     = NULL;
	libfwevt_internal_provider_t *internal_provider = NULL;
	libfwevt_map_t *map                             = NULL;
	const uint8_t *map_offsets_data                 = NULL;
	static char *function                           = "libfwevt_provider_read_maps";
	size_t data_offset                              = 0;
	size_t maps_header_size                         = 0;
	uint32_t map_index                              = 0;
	uint32_t map_offset                             = 0;
	uint32_t maps_data_size                         = 0;
	uint32_t number_of_maps                         = 0;
	int entry_index                                 = 0;

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

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
	if( (size_t) internal_provider->maps_offset >= data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( data_size - (size_t) internal_provider->maps_offset ) < sizeof( fwevt_template_maps_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		return( -1 );
	}
	if( internal_provider->maps_offset == 0 )
	{
		return( 1 );
	}
	data_offset = (size_t) internal_provider->maps_offset;
	maps        = (fwevt_template_maps_t *) &( data[ data_offset ] );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading maps data at offset: %" PRIzd " (0x%08" PRIzx "):\n",
		 function,
		 data_offset,
		 data_offset );

		libcnotify_printf(
		 "%s: maps data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) maps,
		 sizeof( fwevt_template_maps_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 maps->size,
	 maps_data_size );

	byte_stream_copy_to_uint32_little_endian(
	 maps->number_of_maps,
	 number_of_maps );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t\t: %c%c%c%c\n",
		 function,
		 maps->signature[ 0 ],
		 maps->signature[ 1 ],
		 maps->signature[ 2 ],
		 maps->signature[ 3 ] );

		libcnotify_printf(
		 "%s: size\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 maps_data_size );

		libcnotify_printf(
		 "%s: number of maps\t\t\t\t: %" PRIu32 "\n",
		 function,
		 number_of_maps );

		libcnotify_printf(
		 "\n" );
	}
#endif
	data_offset += sizeof( fwevt_template_maps_t );

	if( memory_compare(
	     maps->signature,
	     "MAPS",
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported maps signature.",
		 function );

		goto on_error;
	}
	if( number_of_maps > 1 )
	{
		map_offsets_data = &( data[ data_offset ] );

		if( ( number_of_maps - 1 ) > ( ( data_size - data_offset ) / sizeof( uint32_t ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: invalid data value too small.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: map descriptor offsets data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ data_offset ] ),
			 ( number_of_maps - 1 ) * sizeof( uint32_t ),
			 0 );

			for( map_index = 0;
			     map_index < number_of_maps - 1;
			     map_index++ )
			{
				byte_stream_copy_to_uint32_little_endian(
				 &( data[ data_offset ] ),
				 map_offset );

				data_offset += 4;

				libcnotify_printf(
				 "%s: map: %03" PRIu32 " descriptor offset\t\t\t: 0x%08" PRIx32 "\n",
				 function,
				 map_index,
				 map_offset );
			}
			libcnotify_printf(
			 "\n" );
		}
#else
		data_offset += ( number_of_maps - 1 ) * sizeof( uint32_t );
#endif
	}
	if( number_of_maps > 0 )
	{
		if( number_of_maps > ( ( data_size - data_offset ) / sizeof( fwevt_template_map_t ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: invalid data value too small.",
			 function );

			goto on_error;
		}
		if( maps_data_size > 0 )
		{
			maps_header_size = sizeof( fwevt_template_maps_t )
					 + ( number_of_maps * sizeof( uint32_t ) );

			if( ( maps_data_size < maps_header_size )
			 || ( maps_data_size >= data_size ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid maps data size value out of bounds.",
				 function );

				goto on_error;
			}
			maps_data_size -= (uint32_t) maps_header_size;
		}
		for( map_index = 0;
		     map_index < number_of_maps;
		     map_index++ )
		{
			if( map_index == 0 )
			{
				map_offset = (uint32_t) data_offset;
			}
			else
			{
				if( map_offsets_data == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: invalid map offsets data value.",
					 function );

					goto on_error;
				}
				byte_stream_copy_to_uint32_little_endian(
				 map_offsets_data,
				 map_offset );

				map_offsets_data += 4;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: reading map: %03" PRIu32 " at offset: %" PRIu32 " (0x%08" PRIx32 "):\n",
				 function,
				 map_index,
				 map_offset,
				 map_offset );
			}
#endif
			if( libfwevt_map_initialize(
			     &map,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create map: %" PRIu32 ".",
				 function,
				 map_index );

				goto on_error;
			}
			if( libfwevt_map_read_data(
			     map,
			     data,
			     data_size,
			     (size_t) map_offset,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read map: %" PRIu32 ".",
				 function,
				 map_index );

				goto on_error;
			}
			if( maps_data_size < sizeof( fwevt_template_map_t ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid maps data size value out of bounds.",
				 function );

				goto on_error;
			}
			maps_data_size -= sizeof( fwevt_template_map_t );

			if( libcdata_array_append_entry(
			     internal_provider->maps_array,
			     &entry_index,
			     (intptr_t *) map,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append map: %" PRIu32 " to array.",
				 function,
				 map_index );

				goto on_error;
			}
			map = NULL;
		}
	}
/* TODO count data size ?
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( maps_data_size > 0 )
		{
			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ data_offset ] ),
			 maps_data_size,
			 0 );
		}
	}
#endif
*/
	return( 1 );

on_error:
	if( map != NULL )
	{
		libfwevt_internal_map_free(
		 (libfwevt_internal_map_t **) &map,
		 NULL );
	}
	libcdata_array_empty(
	 internal_provider->maps_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_map_free,
	 NULL );

	return( -1 );
}

/* Reads the provider opcodes
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_read_opcodes(
     libfwevt_provider_t *provider,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	fwevt_template_opcodes_t *opcodes               = NULL;
	libfwevt_internal_provider_t *internal_provider = NULL;
	libfwevt_opcode_t *opcode                       = NULL;
	static char *function                           = "libfwevt_provider_read_opcodes";
	size_t data_offset                              = 0;
	uint32_t number_of_opcodes                      = 0;
	uint32_t opcode_index                           = 0;
	uint32_t opcodes_data_size                      = 0;
	int entry_index                                 = 0;

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

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
	if( (size_t) internal_provider->opcodes_offset >= data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( data_size - (size_t) internal_provider->opcodes_offset ) < sizeof( fwevt_template_opcodes_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		return( -1 );
	}
	if( internal_provider->opcodes_offset == 0 )
	{
		return( 1 );
	}
	data_offset = (size_t) internal_provider->opcodes_offset;
	opcodes     = (fwevt_template_opcodes_t *) &( data[ data_offset ] );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading opcodes data at offset: %" PRIzd " (0x%08" PRIzx "):\n",
		 function,
		 data_offset,
		 data_offset );

		libcnotify_printf(
		 "%s: opcodes data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) opcodes,
		 sizeof( fwevt_template_opcodes_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 opcodes->size,
	 opcodes_data_size );

	byte_stream_copy_to_uint32_little_endian(
	 opcodes->number_of_opcodes,
	 number_of_opcodes );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c\n",
		 function,
		 opcodes->signature[ 0 ],
		 opcodes->signature[ 1 ],
		 opcodes->signature[ 2 ],
		 opcodes->signature[ 3 ] );

		libcnotify_printf(
		 "%s: size\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 opcodes_data_size );

		libcnotify_printf(
		 "%s: number of opcodes\t\t\t: %" PRIu32 "\n",
		 function,
		 number_of_opcodes );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	data_offset += sizeof( fwevt_template_opcodes_t );

	if( memory_compare(
	     opcodes->signature,
	     "OPCO",
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported opcodes signature.",
		 function );

		goto on_error;
	}
	if( number_of_opcodes > ( ( data_size - data_offset ) / sizeof( fwevt_template_opcode_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		goto on_error;
	}
	if( opcodes_data_size > 0 )
	{
		if( ( opcodes_data_size < sizeof( fwevt_template_opcodes_t ) )
		 || ( opcodes_data_size >= data_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid opcodes data size value out of bounds.",
			 function );

			goto on_error;
		}
		opcodes_data_size -= sizeof( fwevt_template_opcodes_t );
	}
	for( opcode_index = 0;
	     opcode_index < number_of_opcodes;
	     opcode_index++ )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: reading opcode: %03" PRIu32 " at offset: %" PRIzd " (0x%08" PRIzx "):\n",
			 function,
			 opcode_index,
			 data_offset,
			 data_offset );
		}
#endif
		if( libfwevt_opcode_initialize(
		     &opcode,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create opcode: %" PRIu32 ".",
			 function,
			 opcode_index );

			goto on_error;
		}
		if( libfwevt_opcode_read_data(
		     opcode,
		     data,
		     data_size,
		     data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read opcode: %" PRIu32 ".",
			 function,
			 opcode_index );

			goto on_error;
		}
		if( opcodes_data_size < sizeof( fwevt_template_opcode_t ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid opcodes data size value out of bounds.",
			 function );

			goto on_error;
		}
		data_offset       += sizeof( fwevt_template_opcode_t );
		opcodes_data_size -= sizeof( fwevt_template_opcode_t );

		if( libcdata_array_append_entry(
		     internal_provider->opcodes_array,
		     &entry_index,
		     (intptr_t *) opcode,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append opcode: %" PRIu32 " to array.",
			 function,
			 opcode_index );

			goto on_error;
		}
		opcode = NULL;
	}
/* TODO count data size ?
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( opcodes_data_size > 0 )
		{
			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ data_offset ] ),
			 opcodes_data_size,
			 0 );
		}
	}
#endif
*/
	return( 1 );

on_error:
	if( opcode != NULL )
	{
		libfwevt_internal_opcode_free(
		 (libfwevt_internal_opcode_t **) &opcode,
		 NULL );
	}
	libcdata_array_empty(
	 internal_provider->opcodes_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_opcode_free,
	 NULL );

	return( -1 );
}

/* Reads the provider tasks
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_read_tasks(
     libfwevt_provider_t *provider,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	fwevt_template_tasks_t *tasks                   = NULL;
	libfwevt_internal_provider_t *internal_provider = NULL;
	libfwevt_task_t *task                           = NULL;
	static char *function                           = "libfwevt_provider_read_tasks";
	size_t data_offset                              = 0;
	uint32_t number_of_tasks                        = 0;
	uint32_t task_index                             = 0;
	uint32_t tasks_data_size                        = 0;
	int entry_index                                 = 0;

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

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
	if( (size_t) internal_provider->tasks_offset >= data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( data_size - (size_t) internal_provider->tasks_offset ) < sizeof( fwevt_template_tasks_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		return( -1 );
	}
	if( internal_provider->tasks_offset == 0 )
	{
		return( 1 );
	}
	data_offset = (size_t) internal_provider->tasks_offset;
	tasks       = (fwevt_template_tasks_t *) &( data[ data_offset ] );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading tasks data at offset: %" PRIzd " (0x%08" PRIzx "):\n",
		 function,
		 data_offset,
		 data_offset );

		libcnotify_printf(
		 "%s: tasks data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) tasks,
		 sizeof( fwevt_template_tasks_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 tasks->size,
	 tasks_data_size );

	byte_stream_copy_to_uint32_little_endian(
	 tasks->number_of_tasks,
	 number_of_tasks );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t\t: %c%c%c%c\n",
		 function,
		 tasks->signature[ 0 ],
		 tasks->signature[ 1 ],
		 tasks->signature[ 2 ],
		 tasks->signature[ 3 ] );

		libcnotify_printf(
		 "%s: size\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 tasks_data_size );

		libcnotify_printf(
		 "%s: number of tasks\t\t\t\t: %" PRIu32 "\n",
		 function,
		 number_of_tasks );

		libcnotify_printf(
		 "\n" );
	}
#endif
	data_offset += sizeof( fwevt_template_tasks_t );

	if( memory_compare(
	     tasks->signature,
	     "TASK",
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported tasks signature.",
		 function );

		goto on_error;
	}
	if( number_of_tasks > ( ( data_size - data_offset ) / sizeof( fwevt_template_task_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		goto on_error;
	}
	if( tasks_data_size > 0 )
	{
		if( ( tasks_data_size < sizeof( fwevt_template_task_t ) )
		 || ( tasks_data_size >= data_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid tasks data size value out of bounds.",
			 function );

			goto on_error;
		}
		tasks_data_size -= sizeof( fwevt_template_task_t );
	}
	for( task_index = 0;
	     task_index < number_of_tasks;
	     task_index++ )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: reading task: %03" PRIu32 " at offset: %" PRIzd " (0x%08" PRIzx "):\n",
			 function,
			 task_index,
			 data_offset,
			 data_offset );
		}
#endif
		if( libfwevt_task_initialize(
		     &task,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create task: %" PRIu32 ".",
			 function,
			 task_index );

			goto on_error;
		}
		if( libfwevt_task_read_data(
		     task,
		     data,
		     data_size,
		     data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read task: %" PRIu32 ".",
			 function,
			 task_index );

			goto on_error;
		}
		if( tasks_data_size < sizeof( fwevt_template_task_t ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid tasks data size value out of bounds.",
			 function );

			goto on_error;
		}
		data_offset     += sizeof( fwevt_template_task_t );
		tasks_data_size -= sizeof( fwevt_template_task_t );

		if( libcdata_array_append_entry(
		     internal_provider->tasks_array,
		     &entry_index,
		     (intptr_t *) task,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append task: %" PRIu32 " to array.",
			 function,
			 task_index );

			goto on_error;
		}
		task = NULL;
	}
/* TODO count data size ?
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( tasks_data_size > 0 )
		{
			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ data_offset ] ),
			 tasks_data_size,
			 0 );
		}
	}
#endif
*/
	return( 1 );

on_error:
	if( task != NULL )
	{
		libfwevt_internal_task_free(
		 (libfwevt_internal_task_t **) &task,
		 NULL );
	}
	libcdata_array_empty(
	 internal_provider->tasks_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_task_free,
	 NULL );

	return( -1 );
}

/* Reads the provider template table
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_read_templates(
     libfwevt_provider_t *provider,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	libfwevt_template_t *wevt_template              = NULL;
	fwevt_template_table_t *template_table          = NULL;
	static char *function                           = "libfwevt_provider_read_templates";
	size_t data_offset                              = 0;
	uint32_t number_of_templates                    = 0;
	uint32_t template_index                         = 0;
	uint32_t template_size                          = 0;
	uint32_t template_table_size                    = 0;
	int entry_index                                 = 0;

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

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
	if( (size_t) internal_provider->templates_offset >= data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( data_size - (size_t) internal_provider->templates_offset ) < sizeof( fwevt_template_table_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		return( -1 );
	}
	if( internal_provider->templates_offset == 0 )
	{
		return( 1 );
	}
	data_offset    = (size_t) internal_provider->templates_offset;
	template_table = (fwevt_template_table_t *) &( data[ data_offset ] );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading template table data at offset: %" PRIzd " (0x%08" PRIzx "):\n",
		 function,
		 data_offset,
		 data_offset );

		libcnotify_printf(
		 "%s: template table data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) template_table,
		 sizeof( fwevt_template_table_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 template_table->size,
	 template_table_size );

	byte_stream_copy_to_uint32_little_endian(
	 template_table->number_of_templates,
	 number_of_templates );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c\n",
		 function,
		 template_table->signature[ 0 ],
		 template_table->signature[ 1 ],
		 template_table->signature[ 2 ],
		 template_table->signature[ 3 ] );

		libcnotify_printf(
		 "%s: size\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 template_table_size );

		libcnotify_printf(
		 "%s: number of templates\t\t\t: %" PRIu32 "\n",
		 function,
		 number_of_templates );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	data_offset += sizeof( fwevt_template_table_t );

	if( memory_compare(
	     template_table->signature,
	     "TTBL",
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported template table signature.",
		 function );

		goto on_error;
	}
	if( number_of_templates > ( ( data_size - data_offset ) / sizeof( fwevt_template_header_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		goto on_error;
	}
	if( template_table_size > 0 )
	{
		if( ( template_table_size < sizeof( fwevt_template_table_t ) )
		 || ( template_table_size >= data_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid template table data size value out of bounds.",
			 function );

			goto on_error;
		}
		template_table_size -= sizeof( fwevt_template_table_t );
	}
	for( template_index = 0;
	     template_index < number_of_templates;
	     template_index++ )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: reading template: %03" PRIu32 " at offset: %" PRIzd " (0x%08" PRIzx "):\n",
			 function,
			 template_index,
			 data_offset,
			 data_offset );
		}
#endif
		if( libfwevt_template_initialize(
		     &wevt_template,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create template: %" PRIu32 ".",
			 function,
			 template_index );

			goto on_error;
		}
		( (libfwevt_internal_template_t *) wevt_template )->is_managed = 1;

/* TODO handle ASCII codepage */
		if( libfwevt_template_read(
		     wevt_template,
		     data,
		     data_size,
		     data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read template: %" PRIu32 ".",
			 function,
			 template_index );

			goto on_error;
		}
		if( libfwevt_template_get_size(
		     wevt_template,
		     &template_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve template size.",
			 function );

			goto on_error;
		}
		if( template_table_size < template_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid templates data size value out of bounds.",
			 function );

			goto on_error;
		}
		data_offset         += template_size;
		template_table_size -= template_size;

		if( libcdata_array_append_entry(
		     internal_provider->templates_array,
		     &entry_index,
		     (intptr_t *) wevt_template,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to set templates: %" PRIu32 " to array.",
			 function,
			 template_index );

			goto on_error;
		}
		wevt_template = NULL;
	}
/* TODO count data size ?
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( template_table_size > 0 )
		{
			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ data_offset ] ),
			 template_table_size,
			 0 );
		}
	}
#endif
*/
	return( 1 );

on_error:
	if( wevt_template != NULL )
	{
		libfwevt_internal_template_free(
		 (libfwevt_internal_template_t **) &wevt_template,
		 NULL );
	}
	libcdata_array_empty(
	 internal_provider->templates_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_template_free,
	 NULL );

	return( -1 );
}

/* Retrieves the identifier
 * The identifier is a GUID stored in little-endian and is 16 bytes of size
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int libfwevt_provider_get_identifier(
     libfwevt_provider_t *provider,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_get_identifier";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

	if( guid_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID data.",
		 function );

		return( -1 );
	}
	if( ( guid_data_size < 16 )
	 || ( guid_data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: GUID data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     guid_data,
	     internal_provider->identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Compares the provider with the identifier
 * Returns 1 if identifier matches, 0 if not or -1 on error
 */
int libfwevt_provider_compare_identifier(
     libfwevt_provider_t *provider,
     const uint8_t *identifier,
     size_t identifier_size,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_compare_identifier";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

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
	if( identifier_size != 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid identifier size value out of bounds.",
		 function );

		return( -1 );
	}
	if( memory_compare(
	     internal_provider->identifier,
	     identifier,
	     16 ) == 0 )
	{
		return( 1 );
	}
	return( 0 );
}

/* Retrieves the number of channels
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_get_number_of_channels(
     libfwevt_provider_t *provider,
     int *number_of_channels,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_get_number_of_channels";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

	if( libcdata_array_get_number_of_entries(
	     internal_provider->channels_array,
	     number_of_channels,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific channel
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_get_channel_by_index(
     libfwevt_provider_t *provider,
     int channel_index,
     libfwevt_channel_t **channel,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_get_channel_by_index";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

	if( libcdata_array_get_entry_by_index(
	     internal_provider->channels_array,
	     channel_index,
	     (intptr_t **) channel,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d.",
		 function,
		 channel_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the number of events
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_get_number_of_events(
     libfwevt_provider_t *provider,
     int *number_of_events,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_get_number_of_events";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

	if( libcdata_array_get_number_of_entries(
	     internal_provider->events_array,
	     number_of_events,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific event
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_get_event_by_index(
     libfwevt_provider_t *provider,
     int event_index,
     libfwevt_event_t **event,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_get_event_by_index";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

	if( libcdata_array_get_entry_by_index(
	     internal_provider->events_array,
	     event_index,
	     (intptr_t **) event,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d.",
		 function,
		 event_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific event by identifier
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfwevt_provider_get_event_by_identifier(
     libfwevt_provider_t *provider,
     uint32_t event_identifier,
     libfwevt_event_t **event,
     libcerror_error_t **error )
{
	libfwevt_event_t *safe_event                    = NULL;
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_get_event_by_identifier";
	uint32_t identifier                             = 0;
	int event_index                                 = 0;
	int number_of_events                            = 0;

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

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
	*event = NULL;

	if( libcdata_array_get_number_of_entries(
	     internal_provider->events_array,
	     &number_of_events,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	for( event_index = 0;
	     event_index < number_of_events;
	     event_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_provider->events_array,
		     event_index,
		     (intptr_t **) &safe_event,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry: %d.",
			 function,
			 event_index );

			return( -1 );
		}
/* TODO refactor to compare function */
		if( libfwevt_event_get_identifier(
		     safe_event,
		     &identifier,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve event identifier: %d.",
			 function,
			 event_index );

			return( -1 );
		}
		if( event_identifier == identifier )
		{
			*event = safe_event;

			return( 1 );
		}
	}
	return( 0 );
}

/* Retrieves the number of keywords
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_get_number_of_keywords(
     libfwevt_provider_t *provider,
     int *number_of_keywords,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_get_number_of_keywords";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

	if( libcdata_array_get_number_of_entries(
	     internal_provider->keywords_array,
	     number_of_keywords,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific keyword
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_get_keyword_by_index(
     libfwevt_provider_t *provider,
     int keyword_index,
     libfwevt_keyword_t **keyword,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_get_keyword_by_index";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

	if( libcdata_array_get_entry_by_index(
	     internal_provider->keywords_array,
	     keyword_index,
	     (intptr_t **) keyword,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d.",
		 function,
		 keyword_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the number of levels
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_get_number_of_levels(
     libfwevt_provider_t *provider,
     int *number_of_levels,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_get_number_of_levels";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

	if( libcdata_array_get_number_of_entries(
	     internal_provider->levels_array,
	     number_of_levels,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific level
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_get_level_by_index(
     libfwevt_provider_t *provider,
     int level_index,
     libfwevt_level_t **level,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_get_level_by_index";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

	if( libcdata_array_get_entry_by_index(
	     internal_provider->levels_array,
	     level_index,
	     (intptr_t **) level,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d.",
		 function,
		 level_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the number of maps
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_get_number_of_maps(
     libfwevt_provider_t *provider,
     int *number_of_maps,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_get_number_of_maps";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

	if( libcdata_array_get_number_of_entries(
	     internal_provider->maps_array,
	     number_of_maps,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific map
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_get_map_by_index(
     libfwevt_provider_t *provider,
     int map_index,
     libfwevt_map_t **map,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_get_map_by_index";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

	if( libcdata_array_get_entry_by_index(
	     internal_provider->maps_array,
	     map_index,
	     (intptr_t **) map,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d.",
		 function,
		 map_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the number of opcodes
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_get_number_of_opcodes(
     libfwevt_provider_t *provider,
     int *number_of_opcodes,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_get_number_of_opcodes";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

	if( libcdata_array_get_number_of_entries(
	     internal_provider->opcodes_array,
	     number_of_opcodes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific opcode
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_get_opcode_by_index(
     libfwevt_provider_t *provider,
     int opcode_index,
     libfwevt_opcode_t **opcode,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_get_opcode_by_index";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

	if( libcdata_array_get_entry_by_index(
	     internal_provider->opcodes_array,
	     opcode_index,
	     (intptr_t **) opcode,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d.",
		 function,
		 opcode_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the number of tasks
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_get_number_of_tasks(
     libfwevt_provider_t *provider,
     int *number_of_tasks,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_get_number_of_tasks";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

	if( libcdata_array_get_number_of_entries(
	     internal_provider->tasks_array,
	     number_of_tasks,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific task
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_get_task_by_index(
     libfwevt_provider_t *provider,
     int task_index,
     libfwevt_task_t **task,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_get_task_by_index";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

	if( libcdata_array_get_entry_by_index(
	     internal_provider->tasks_array,
	     task_index,
	     (intptr_t **) task,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d.",
		 function,
		 task_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the number of templates
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_get_number_of_templates(
     libfwevt_provider_t *provider,
     int *number_of_templates,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_get_number_of_templates";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

	if( libcdata_array_get_number_of_entries(
	     internal_provider->templates_array,
	     number_of_templates,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific template
 * Returns 1 if successful or -1 on error
 */
int libfwevt_provider_get_template_by_index(
     libfwevt_provider_t *provider,
     int template_index,
     libfwevt_template_t **wevt_template,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	static char *function                           = "libfwevt_provider_get_template_by_index";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

	if( libcdata_array_get_entry_by_index(
	     internal_provider->templates_array,
	     template_index,
	     (intptr_t **) wevt_template,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d.",
		 function,
		 template_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific template by offset
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfwevt_provider_get_template_by_offset(
     libfwevt_provider_t *provider,
     uint32_t offset,
     libfwevt_template_t **wevt_template,
     libcerror_error_t **error )
{
	libfwevt_internal_provider_t *internal_provider = NULL;
	libfwevt_template_t *safe_wevt_template         = NULL;
	static char *function                           = "libfwevt_provider_get_template_by_offset";
	uint32_t template_offset                        = 0;
	int number_of_templates                         = 0;
	int template_index                              = 0;

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libfwevt_internal_provider_t *) provider;

	if( wevt_template == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template.",
		 function );

		return( -1 );
	}
	*wevt_template = NULL;

	if( libcdata_array_get_number_of_entries(
	     internal_provider->templates_array,
	     &number_of_templates,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	for( template_index = 0;
	     template_index < number_of_templates;
	     template_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_provider->templates_array,
		     template_index,
		     (intptr_t **) &safe_wevt_template,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry: %d.",
			 function,
			 template_index );

			return( -1 );
		}
		if( libfwevt_template_get_offset(
		     safe_wevt_template,
		     &template_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve template offset: %d.",
			 function,
			 template_index );

			return( -1 );
		}
		if( offset == template_offset )
		{
			*wevt_template = safe_wevt_template;

			return( 1 );
		}
	}
	return( 0 );
}

