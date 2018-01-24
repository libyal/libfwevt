/*
 * Debug functions
 *
 * Copyright (C) 2011-2018, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <types.h>

#include "libfwevt_debug.h"
#include "libfwevt_definitions.h"
#include "libfwevt_libcerror.h"
#include "libfwevt_libcnotify.h"

#if defined( HAVE_DEBUG_OUTPUT )

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

#endif

