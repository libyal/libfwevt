/*
 * Debug functions
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
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "libfwevt_debug.h"
#include "libfwevt_definitions.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_libcnotify.h"
#include "libfwevt_libfguid.h"
#include "libfwevt_libuna.h"

#if defined( HAVE_DEBUG_OUTPUT )

/* Prints the input data type
 */
void libfwevt_debug_print_input_data_type(
      uint8_t input_data_type )
{
	switch( input_data_type )
	{
		case 0x01:
			libcnotify_printf(
			 "win:UnicodeString" );
			break;

		case 0x02:
			libcnotify_printf(
			 "win:AnsiString" );
			break;

		case 0x03:
			libcnotify_printf(
			 "win:Int8" );
			break;

		case 0x04:
			libcnotify_printf(
			 "win:UInt8" );
			break;

		case 0x05:
			libcnotify_printf(
			 "win:Int16" );
			break;

		case 0x06:
			libcnotify_printf(
			 "win:UInt16" );
			break;

		case 0x07:
			libcnotify_printf(
			 "win:Int32" );
			break;

		case 0x08:
			libcnotify_printf(
			 "win:UInt32" );
			break;

		case 0x09:
			libcnotify_printf(
			 "win:Int64" );
			break;

		case 0x0a:
			libcnotify_printf(
			 "win:UInt64" );
			break;

		case 0x0b:
			libcnotify_printf(
			 "win:Float" );
			break;

		case 0x0c:
			libcnotify_printf(
			 "win:Double" );
			break;

		case 0x0d:
			libcnotify_printf(
			 "win:Boolean" );
			break;

		case 0x0e:
			libcnotify_printf(
			 "win:Binary" );
			break;

		case 0x0f:
			libcnotify_printf(
			 "win:GUID" );
			break;

		case 0x10:
			libcnotify_printf(
			 "win:Pointer" );
			break;

		case 0x11:
			libcnotify_printf(
			 "win:FILETIME" );
			break;

		case 0x12:
			libcnotify_printf(
			 "win:SYSTEMTIME" );
			break;

		case 0x13:
			libcnotify_printf(
			 "win:SID" );
			break;

		case 0x14:
			libcnotify_printf(
			 "win:HexInt32" );
			break;

		case 0x15:
			libcnotify_printf(
			 "win:HexInt64" );
			break;

		default:
			libcnotify_printf(
			 "UNKNOWN" );
			break;
	}
}

/* Prints the output data type
 */
void libfwevt_debug_print_output_data_type(
      uint8_t output_data_type )
{
	switch( output_data_type )
	{
		case 0x01:
			libcnotify_printf(
			 "xs:string" );
			break;

		case 0x02:
			libcnotify_printf(
			 "xs:dateTime" );
			break;

		case 0x03:
			libcnotify_printf(
			 "xs:byte" );
			break;

		case 0x04:
			libcnotify_printf(
			 "xs:unsignedByte" );
			break;

		case 0x05:
			libcnotify_printf(
			 "xs:short" );
			break;

		case 0x06:
			libcnotify_printf(
			 "xs:unsignedShort" );
			break;

		case 0x07:
			libcnotify_printf(
			 "xs:int" );
			break;

		case 0x08:
			libcnotify_printf(
			 "xs:unsignedInt" );
			break;

		case 0x09:
			libcnotify_printf(
			 "xs:long" );
			break;

		case 0x0a:
			libcnotify_printf(
			 "xs:unsignedLong" );
			break;

		case 0x0b:
			libcnotify_printf(
			 "xs:float" );
			break;

		case 0x0c:
			libcnotify_printf(
			 "xs:double" );
			break;

		case 0x0d:
			libcnotify_printf(
			 "xs:boolean" );
			break;

		case 0x0e:
			libcnotify_printf(
			 "xs:GUID" );
			break;

		case 0x0f:
			libcnotify_printf(
			 "xs:hexBinary" );
			break;

		case 0x11:
			libcnotify_printf(
			 "win:HexInt16" );
			break;

		case 0x12:
			libcnotify_printf(
			 "win:HexInt32" );
			break;

		case 0x13:
			libcnotify_printf(
			 "win:HexInt64" );
			break;

		case 0x14:
			libcnotify_printf(
			 "win:PID" );
			break;

		case 0x15:
			libcnotify_printf(
			 "win:TID" );
			break;

		case 0x16:
			libcnotify_printf(
			 "win:Port" );
			break;

		case 0x17:
			libcnotify_printf(
			 "win:IPv4" );
			break;

		case 0x18:
			libcnotify_printf(
			 "win:IPv6" );
			break;

		case 0x19:
			libcnotify_printf(
			 "win:SocketAddress" );
			break;

		case 0x1b:
			libcnotify_printf(
			 "win:ETWTIME" );
			break;

		case 0x1c:
			libcnotify_printf(
			 "win:Xml" );
			break;

		case 0x1d:
			libcnotify_printf(
			 "win:ErrorCode" );
			break;

		case 0x1e:
			libcnotify_printf(
			 "win:Win32Error" );
			break;

		case 0x1f:
			libcnotify_printf(
			 "win:NTSTATUS" );
			break;

		case 0x20:
			libcnotify_printf(
			 "win:HResult" );
			break;

		case 0x21:
			libcnotify_printf(
			 "win:DateTimeCultureInsensitive" );
			break;

		case 0x22:
			libcnotify_printf(
			 "win:Json" );
			break;

		case 0x23:
			libcnotify_printf(
			 "win:Utf8" );
			break;

		case 0x24:
			libcnotify_printf(
			 "win:Pkcs7WithTypeInfo" );
			break;

		default:
			libcnotify_printf(
			 "UNKNOWN" );
			break;
	}
}

/* Prints the value type
 */
void libfwevt_debug_print_value_type(
      uint8_t value_type )
{
	switch( value_type & 0x7f )
	{
		case LIBFWEVT_VALUE_TYPE_NULL:
			libcnotify_printf(
			 "NULL" );
			break;

		case LIBFWEVT_VALUE_TYPE_STRING_UTF16:
			libcnotify_printf(
			 "UTF-16 string" );
			break;

		case LIBFWEVT_VALUE_TYPE_STRING_BYTE_STREAM:
			libcnotify_printf(
			 "Byte stream string" );
			break;

		case LIBFWEVT_VALUE_TYPE_INTEGER_8BIT:
			libcnotify_printf(
			 "Integer 8-bit signed" );
			break;

		case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_8BIT:
			libcnotify_printf(
			 "Integer 8-bit unsigned" );
			break;

		case LIBFWEVT_VALUE_TYPE_INTEGER_16BIT:
			libcnotify_printf(
			 "Integer 16-bit signed" );
			break;

		case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_16BIT:
			libcnotify_printf(
			 "Integer 16-bit unsigned" );
			break;

		case LIBFWEVT_VALUE_TYPE_INTEGER_32BIT:
			libcnotify_printf(
			 "Integer 32-bit signed" );
			break;

		case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_32BIT:
			libcnotify_printf(
			 "Integer 32-bit unsigned" );
			break;

		case LIBFWEVT_VALUE_TYPE_INTEGER_64BIT:
			libcnotify_printf(
			 "Integer 64-bit signed" );
			break;

		case LIBFWEVT_VALUE_TYPE_UNSIGNED_INTEGER_64BIT:
			libcnotify_printf(
			 "Integer 64-bit unsigned" );
			break;

		case LIBFWEVT_VALUE_TYPE_FLOATING_POINT_32BIT:
			libcnotify_printf(
			 "Floating point 32-bit (single precision)" );
			break;

		case LIBFWEVT_VALUE_TYPE_FLOATING_POINT_64BIT:
			libcnotify_printf(
			 "Floating point 64-bit (double precision)" );
			break;

		case LIBFWEVT_VALUE_TYPE_BOOLEAN:
			libcnotify_printf(
			 "Boolean" );
			break;

		case LIBFWEVT_VALUE_TYPE_BINARY_DATA:
			libcnotify_printf(
			 "Binary data" );
			break;

		case LIBFWEVT_VALUE_TYPE_GUID:
			libcnotify_printf(
			 "GUID" );
			break;

		case LIBFWEVT_VALUE_TYPE_SIZE:
			libcnotify_printf(
			 "Size" );
			break;

		case LIBFWEVT_VALUE_TYPE_FILETIME:
			libcnotify_printf(
			 "Filetime" );
			break;

		case LIBFWEVT_VALUE_TYPE_SYSTEMTIME:
			libcnotify_printf(
			 "Systemtime" );
			break;

		case LIBFWEVT_VALUE_TYPE_NT_SECURITY_IDENTIFIER:
			libcnotify_printf(
			 "NT Security Identifier (SID)" );
			break;

		case LIBFWEVT_VALUE_TYPE_HEXADECIMAL_INTEGER_32BIT:
			libcnotify_printf(
			 "Hexadecimal integer 32-bit" );
			break;

		case LIBFWEVT_VALUE_TYPE_HEXADECIMAL_INTEGER_64BIT:
			libcnotify_printf(
			 "Hexadecimal integer 64-bit" );
			break;

		case LIBFWEVT_VALUE_TYPE_BINARY_XML:
			libcnotify_printf(
			 "Binary XML" );
			break;

		default:
			libcnotify_printf(
			 "UNKNOWN" );
			break;
	}
}

/* Prints a GUID/UUID value
 * Returns 1 if successful or -1 on error
 */
int libfwevt_debug_print_guid_value(
     const char *function_name,
     const char *value_name,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int byte_order,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
        system_character_t guid_string[ 48 ];

        libfguid_identifier_t *guid = NULL;
	static char *function       = "libfwevt_debug_print_guid_value";

	if( libfguid_identifier_initialize(
	     &guid,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create GUID.",
		 function );

		goto on_error;
	}
	if( libfguid_identifier_copy_from_byte_stream(
	     guid,
	     byte_stream,
	     byte_stream_size,
	     byte_order,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy byte stream to GUID.",
		 function );

		goto on_error;
	}
	if( libfguid_identifier_copy_to_utf8_string(
	     guid,
	     (uint8_t *) guid_string,
	     48,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy GUID to string.",
		 function );

		goto on_error;
	}
	libcnotify_printf(
	 "%s: %s: %s\n",
	 function_name,
	 value_name,
	 guid_string );

	if( libfguid_identifier_free(
	     &guid,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free GUID.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
	return( -1 );
}

/* Prints an UTF-16 string value
 * Returns 1 if successful or -1 on error
 */
int libfwevt_debug_print_utf16_string_value(
     const char *function_name,
     const char *value_name,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int byte_order,
     libcerror_error_t **error )
{
	system_character_t *string = NULL;
	static char *function      = "libfwevt_debug_print_utf16_string_value";
	size_t string_size         = 0;
	int result                 = 0;

	if( ( byte_stream == NULL )
	 || ( byte_stream_size == 0 ) )
	{
		libcnotify_printf(
		 "%s: %s: \n",
		 function_name,
		 value_name );

		return( 1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libuna_utf16_string_size_from_utf16_stream(
		  byte_stream,
		  byte_stream_size,
		  byte_order,
		  &string_size,
		  error );
#else
	result = libuna_utf8_string_size_from_utf16_stream(
		  byte_stream,
		  byte_stream_size,
		  byte_order,
		  &string_size,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of string.",
		 function );

		goto on_error;
	}
	if( string_size > (size_t) ( SSIZE_MAX / sizeof( system_character_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		goto on_error;
	}
	string = system_string_allocate(
	          string_size );

	if( string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create string.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libuna_utf16_string_copy_from_utf16_stream(
		  (libuna_utf16_character_t *) string,
		  string_size,
		  byte_stream,
		  byte_stream_size,
		  byte_order,
		  error );
#else
	result = libuna_utf8_string_copy_from_utf16_stream(
		  (libuna_utf8_character_t *) string,
		  string_size,
		  byte_stream,
		  byte_stream_size,
		  byte_order,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set string.",
		 function );

		goto on_error;
	}
	libcnotify_printf(
	 "%s: %s: %" PRIs_SYSTEM "\n",
	 function_name,
	 value_name,
	 string );

	memory_free(
	 string );

	return( 1 );

on_error:
	if( string != NULL )
	{
		memory_free(
		 string );
	}
	return( -1 );
}

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

