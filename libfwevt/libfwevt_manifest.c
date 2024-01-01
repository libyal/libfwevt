/*
 * Map functions
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
#include <system_string.h>
#include <types.h>

#include "libfwevt_debug.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_libcnotify.h"
#include "libfwevt_libfguid.h"
#include "libfwevt_manifest.h"
#include "libfwevt_provider.h"
#include "libfwevt_types.h"

#include "fwevt_template.h"

/* Creates a manifest
 * Make sure the value manifest is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwevt_manifest_initialize(
     libfwevt_manifest_t **manifest,
     libcerror_error_t **error )
{
	libfwevt_internal_manifest_t *internal_manifest = NULL;
	static char *function                           = "libfwevt_manifest_initialize";

	if( manifest == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid manifest.",
		 function );

		return( -1 );
	}
	if( *manifest != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid manifest value already set.",
		 function );

		return( -1 );
	}
	internal_manifest = memory_allocate_structure(
	                     libfwevt_internal_manifest_t );

	if( internal_manifest == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create manifest.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_manifest,
	     0,
	     sizeof( libfwevt_internal_manifest_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear manifest.",
		 function );

		memory_free(
		 internal_manifest );

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( internal_manifest->providers_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create providers array.",
		 function );

		goto on_error;
	}
	*manifest = (libfwevt_manifest_t *) internal_manifest;

	return( 1 );

on_error:
	if( internal_manifest != NULL )
	{
		memory_free(
		 internal_manifest );
	}
	return( -1 );
}

/* Frees a manifest
 * Returns 1 if successful or -1 on error
 */
int libfwevt_manifest_free(
     libfwevt_manifest_t **manifest,
     libcerror_error_t **error )
{
	libfwevt_internal_manifest_t *internal_manifest = NULL;
	static char *function                           = "libfwevt_manifest_free";
	int result                                      = 1;

	if( manifest == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid manifest.",
		 function );

		return( -1 );
	}
	if( *manifest != NULL )
	{
		internal_manifest = (libfwevt_internal_manifest_t *) *manifest;
		*manifest         = NULL;

		if( libcdata_array_free(
		     &( internal_manifest->providers_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_provider_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free providers array.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_manifest );
	}
	return( result );
}

/* Reads the manifest
 * Returns 1 if successful or -1 on error
 */
int libfwevt_manifest_read(
     libfwevt_manifest_t *manifest,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	fwevt_template_manifest_t *wevt_manifest        = NULL;
	fwevt_template_provider_entry_t *provider_entry = NULL;
	libfwevt_internal_manifest_t *internal_manifest = NULL;
	libfwevt_provider_t *provider                   = NULL;
	static char *function                           = "libfwevt_manifest_read";
	size_t data_offset                              = 0;
	uint32_t number_of_providers                    = 0;
	uint32_t provider_data_offset                   = 0;
	uint32_t provider_index                         = 0;
	int entry_index                                 = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit                            = 0;
#endif

	if( manifest == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid manifest.",
		 function );

		return( -1 );
	}
	internal_manifest = (libfwevt_internal_manifest_t *) manifest;

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
	if( ( data_size < sizeof( fwevt_template_manifest_t ) )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
	wevt_manifest = (fwevt_template_manifest_t *) data;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: manifest data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) wevt_manifest,
		 sizeof( fwevt_template_manifest_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint16_little_endian(
	 wevt_manifest->major_version,
	 internal_manifest->major_version );

	byte_stream_copy_to_uint16_little_endian(
	 wevt_manifest->minor_version,
	 internal_manifest->minor_version );

	byte_stream_copy_to_uint32_little_endian(
	 wevt_manifest->number_of_providers,
	 number_of_providers );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t\t: %c%c%c%c\n",
		 function,
		 wevt_manifest->signature[ 0 ],
		 wevt_manifest->signature[ 1 ],
		 wevt_manifest->signature[ 2 ],
		 wevt_manifest->signature[ 3 ] );

		byte_stream_copy_to_uint32_little_endian(
		 wevt_manifest->size,
		 value_32bit );
		libcnotify_printf(
		 "%s: size\t\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: major version\t\t\t\t\t: %" PRIu16 "\n",
		 function,
		 internal_manifest->major_version );

		libcnotify_printf(
		 "%s: minor version\t\t\t\t\t: %" PRIu16 "\n",
		 function,
		 internal_manifest->minor_version );

		libcnotify_printf(
		 "%s: number of providers\t\t\t\t: %" PRIu32 "\n",
		 function,
		 number_of_providers );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( memory_compare(
	     wevt_manifest->signature,
	     "CRIM",
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported manifest signature.",
		 function );

		goto on_error;
	}
	data_offset = sizeof( fwevt_template_manifest_t );

	for( provider_index = 0;
	     provider_index < number_of_providers;
	     provider_index++ )
	{
		if( ( data_size - data_offset ) < sizeof( fwevt_template_provider_entry_t ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid data value too small.",
			 function );

			goto on_error;
		}
		provider_entry = (fwevt_template_provider_entry_t *) &( data[ data_offset ] );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: provider entry: %02" PRIu32 " data:\n",
			 function,
			 provider_index );
			libcnotify_print_data(
			 (uint8_t *) provider_entry,
			 sizeof( fwevt_template_provider_entry_t ),
			 0 );
		}
#endif
		byte_stream_copy_to_uint32_little_endian(
		 provider_entry->data_offset,
		 provider_data_offset );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: provider entry: %02" PRIu32 ":\n",
			 function,
			 provider_index );

			if( libfwevt_debug_print_guid_value(
			     function,
			     "identifier\t\t\t\t\t",
			     provider_entry->identifier,
			     16,
			     LIBFGUID_ENDIAN_LITTLE,
			     LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print GUID value.",
				 function );

				goto on_error;
			}
			libcnotify_printf(
			 "%s: data offset\t\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 provider_data_offset );

			libcnotify_printf(
			 "\n" );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		data_offset += sizeof( fwevt_template_provider_entry_t );

		if( libfwevt_provider_initialize(
		     &provider,
		     provider_entry->identifier,
		     16,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create provider: %" PRIu32 ".",
			 function,
			 provider_index );

			goto on_error;
		}
		if( libfwevt_provider_read_data(
		     provider,
		     data,
		     data_size,
		     (size_t) provider_data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read provider: %d.",
			 function,
			 provider_index );

			goto on_error;
		}
		if( libcdata_array_append_entry(
		     internal_manifest->providers_array,
		     &entry_index,
		     (intptr_t *) provider,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append provider: %" PRIu32 ".",
			 function,
			 provider_index );

			goto on_error;
		}
		provider = NULL;
	}
/* TODO refactor to read on demand ? */
	for( provider_index = 0;
	     provider_index < number_of_providers;
	     provider_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_manifest->providers_array,
		     provider_index,
		     (intptr_t **) &provider,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve provider: %d.",
			 function,
			 provider_index );

			provider = NULL;

			goto on_error;
		}
		if( libfwevt_provider_read_channels(
		     provider,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read channels.",
			 function );

			provider = NULL;

			goto on_error;
		}
		if( libfwevt_provider_read_events(
		     provider,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read events.",
			 function );

			provider = NULL;

			goto on_error;
		}
		if( libfwevt_provider_read_keywords(
		     provider,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read keywords.",
			 function );

			provider = NULL;

			goto on_error;
		}
		if( libfwevt_provider_read_levels(
		     provider,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read levels.",
			 function );

			provider = NULL;

			goto on_error;
		}
		if( libfwevt_provider_read_maps(
		     provider,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read maps.",
			 function );

			provider = NULL;

			goto on_error;
		}
		if( libfwevt_provider_read_opcodes(
		     provider,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read opcodes.",
			 function );

			provider = NULL;

			goto on_error;
		}
		if( libfwevt_provider_read_tasks(
		     provider,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read tasks.",
			 function );

			provider = NULL;

			goto on_error;
		}
		if( libfwevt_provider_read_templates(
		     provider,
		     data,
		     data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read templates.",
			 function );

			provider = NULL;

			goto on_error;
		}
	}
/* TODO end refactor */
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( number_of_providers > 0 )
		{
			libcnotify_printf(
			 "\n" );
		}
	}
#endif
	return( 1 );

on_error:
	if( provider != NULL )
	{
		libfwevt_internal_provider_free(
		 (libfwevt_internal_provider_t **) &provider,
		 NULL );
	}
	libcdata_array_empty(
	 internal_manifest->providers_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_internal_provider_free,
	 NULL );

	return( -1 );
}

/* Retrieves the number of providers
 * Returns 1 if successful or -1 on error
 */
int libfwevt_manifest_get_number_of_providers(
     libfwevt_manifest_t *manifest,
     int *number_of_providers,
     libcerror_error_t **error )
{
	libfwevt_internal_manifest_t *internal_manifest = NULL;
	static char *function                           = "libfwevt_manifest_get_number_of_providers";

	if( manifest == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid manifest.",
		 function );

		return( -1 );
	}
	internal_manifest = (libfwevt_internal_manifest_t *) manifest;

	if( libcdata_array_get_number_of_entries(
	     internal_manifest->providers_array,
	     number_of_providers,
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

/* Retrieves a specific provider
 * Returns 1 if successful or -1 on error
 */
int libfwevt_manifest_get_provider_by_index(
     libfwevt_manifest_t *manifest,
     int provider_index,
     libfwevt_provider_t **provider,
     libcerror_error_t **error )
{
	libfwevt_internal_manifest_t *internal_manifest = NULL;
	static char *function                           = "libfwevt_manifest_get_provider_by_index";

	if( manifest == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid manifest.",
		 function );

		return( -1 );
	}
	internal_manifest = (libfwevt_internal_manifest_t *) manifest;

	if( libcdata_array_get_entry_by_index(
	     internal_manifest->providers_array,
	     provider_index,
	     (intptr_t **) provider,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d.",
		 function,
		 provider_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific provider by identifier (GUID)
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfwevt_manifest_get_provider_by_identifier(
     libfwevt_manifest_t *manifest,
     const uint8_t *provider_identifier,
     size_t provider_identifier_size,
     libfwevt_provider_t **provider,
     libcerror_error_t **error )
{
	libfwevt_internal_manifest_t *internal_manifest = NULL;
	libfwevt_provider_t *safe_provider              = NULL;
	static char *function                           = "libfwevt_manifest_get_provider_by_identifier";
	int number_of_providers                         = 0;
	int provider_index                              = 0;
	int result                                      = 0;

	if( manifest == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid manifest.",
		 function );

		return( -1 );
	}
	internal_manifest = (libfwevt_internal_manifest_t *) manifest;

	if( provider_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider identifier.",
		 function );

		return( -1 );
	}
	if( provider_identifier_size != 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid provider identifier size value out of bounds.",
		 function );

		return( -1 );
	}
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
	*provider = NULL;

	if( libcdata_array_get_number_of_entries(
	     internal_manifest->providers_array,
	     &number_of_providers,
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
	for( provider_index = 0;
	     provider_index < number_of_providers;
	     provider_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_manifest->providers_array,
		     provider_index,
		     (intptr_t **) &safe_provider,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve entry: %d.",
			 function,
			 provider_index );

			return( -1 );
		}
		result = libfwevt_provider_compare_identifier(
		          safe_provider,
		          provider_identifier,
		          16,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GENERIC,
			 "%s: unable to compare identifier of provider: %d.",
			 function,
			 provider_index );

			return( -1 );
		}
		else if( result != 0 )
		{
			*provider = safe_provider;

			return( 1 );
		}
	}
	return( 0 );
}

