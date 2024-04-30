/*
 * Integer functions
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
#include <types.h>

#include "libfwevt_integer.h"
#include "libfwevt_libcerror.h"

/* Copies an integer from an UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
int libfwevt_integer_copy_from_utf16_stream(
     uint64_t *integer_value,
     const uint8_t *utf16_stream,
     size_t utf16_stream_size,
     libcerror_error_t **error )
{
	static char *function       = "libfwevt_integer_copy_from_utf16_stream";
	size_t utf16_stream_offset  = 0;
	uint64_t safe_integer_value = 0;
	uint8_t digit               = 0;

	if( integer_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid integer value.",
		 function );

		return( -1 );
	}
	if( utf16_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 stream.",
		 function );

		return( -1 );
	}
	if( ( utf16_stream_size < 2 )
	 || ( utf16_stream_size > SSIZE_MAX )
	 || ( ( utf16_stream_size % 2 ) != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: UTF-16 stream size value out of bounds.",
		 function );

		return( -1 );
	}
	for( utf16_stream_offset = 0;
	     utf16_stream_offset < utf16_stream_size;
	     utf16_stream_offset += 2 )
	{
		if( utf16_stream_offset >= 42 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported UTF-16 stream.",
			 function );

			return( -1 );
		}
		if( utf16_stream[ utf16_stream_offset + 1 ] != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported integer string.",
			 function );

			return( -1 );
		}
		digit = utf16_stream[ utf16_stream_offset ];

		if( digit == 0 )
		{
			break;
		}
		if( ( digit < (uint8_t) '0' )
		 || ( digit > (uint8_t) '9' ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid integer string.",
			 function );

			return( -1 );
		}
		safe_integer_value *= 10;
		safe_integer_value += digit - (uint8_t) '0';
	}
	if( ( utf16_stream[ utf16_stream_offset ] != 0 )
	 || ( utf16_stream[ utf16_stream_offset + 1 ] != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported integer string.",
		 function );

		return( -1 );
	}
	*integer_value = safe_integer_value;

	return( 1 );
}

/* Deterimes the size of the string of the integer as a signed decimal
 * The string size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_integer_as_signed_decimal_get_string_size(
     uint64_t integer_value,
     uint8_t integer_size,
     size_t *string_size,
     libcerror_error_t **error )
{
	static char *function        = "libfwevt_integer_as_signed_decimal_get_string_size";
	uint64_t divider             = 0;
	uint8_t is_negative          = 0;
	uint8_t number_of_characters = 0;
	int8_t bit_shift             = integer_size - 1;

	if( string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string size.",
		 function );

		return( -1 );
	}
	/* The string is at least a single digit with an end of string character
	 */
	number_of_characters = 2;

	is_negative = (uint8_t) ( integer_value >> bit_shift );

	if( is_negative != 0 )
	{
		number_of_characters += 1;

		integer_value &= ~( (uint64_t) 1 << bit_shift );

		if( integer_value == 0 )
		{
			integer_value |= (uint64_t) 1 << bit_shift;
		}
	}
	divider = 1;

	while( ( integer_value / divider ) >= 10 )
	{
		divider *= 10;

		number_of_characters += 1;
	}
	*string_size = number_of_characters;

	return( 1 );
}

/* Copies an integer as an unsigned decimal to an UTF-8 string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_integer_as_signed_decimal_copy_to_utf8_string_with_index(
     uint64_t integer_value,
     uint8_t integer_size,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     libcerror_error_t **error )
{
	static char *function         = "libfwevt_integer_as_signed_decimal_copy_to_utf8_string_with_index";
	size_t safe_utf8_string_index = 0;
	uint64_t divider              = 0;
	uint8_t is_negative           = 0;
	uint8_t number_of_characters  = 0;
	int8_t bit_shift              = integer_size - 1;

	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string index.",
		 function );

		return( -1 );
	}
	safe_utf8_string_index = *utf8_string_index;

	/* The string is at least a single digit with an end of string character
	 */
	number_of_characters = 2;

	is_negative = (uint8_t) ( integer_value >> bit_shift );

	if( is_negative != 0 )
	{
		number_of_characters += 1;

		integer_value &= ~( (uint64_t) 1 << bit_shift );

		if( integer_value == 0 )
		{
			integer_value |= (uint64_t) 1 << bit_shift;
		}
	}
	divider = 1;

	while( ( integer_value / divider ) >= 10 )
	{
		divider *= 10;

		number_of_characters += 1;
	}
	if( ( number_of_characters > utf8_string_size )
	 || ( safe_utf8_string_index > ( utf8_string_size - number_of_characters ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid UTF-8 string size value too small.",
		 function );

		return( -1 );
	}
	if( is_negative != 0 )
	{
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '-';
	}
	while( divider > 1 )
	{
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '0' + (uint8_t) ( integer_value / divider );

		integer_value %= divider;

		divider /= 10;
	}
	utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '0' + (uint8_t) ( integer_value / divider );
	utf8_string[ safe_utf8_string_index++ ] = 0;

	*utf8_string_index = safe_utf8_string_index;

	return( 1 );
}

/* Copies an integer as an unsigned decimal to an UTF-16 string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_integer_as_signed_decimal_copy_to_utf16_string_with_index(
     uint64_t integer_value,
     uint8_t integer_size,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     libcerror_error_t **error )
{
	static char *function          = "libfwevt_integer_as_signed_decimal_copy_to_utf16_string_with_index";
	size_t safe_utf16_string_index = 0;
	uint64_t divider               = 0;
	uint8_t is_negative            = 0;
	uint8_t number_of_characters   = 0;
	int8_t bit_shift               = integer_size - 1;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string index.",
		 function );

		return( -1 );
	}
	safe_utf16_string_index = *utf16_string_index;

	/* The string is at least a single digit with an end of string character
	 */
	number_of_characters = 2;

	is_negative = (uint8_t) ( integer_value >> bit_shift );

	if( is_negative != 0 )
	{
		number_of_characters += 1;

		integer_value &= ~( (uint64_t) 1 << bit_shift );

		if( integer_value == 0 )
		{
			integer_value |= (uint64_t) 1 << bit_shift;
		}
	}
	divider = 1;

	while( ( integer_value / divider ) >= 10 )
	{
		divider *= 10;

		number_of_characters += 1;
	}
	if( ( number_of_characters > utf16_string_size )
	 || ( safe_utf16_string_index > ( utf16_string_size - number_of_characters ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid UTF-16 string size value too small.",
		 function );

		return( -1 );
	}
	if( is_negative != 0 )
	{
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '-';
	}
	while( divider > 1 )
	{
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '0' + (uint16_t) ( integer_value / divider );

		integer_value %= divider;

		divider /= 10;
	}
	utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '0' + (uint16_t) ( integer_value / divider );
	utf16_string[ safe_utf16_string_index++ ] = 0;

	*utf16_string_index = safe_utf16_string_index;

	return( 1 );
}

/* Deterimes the size of the string of the integer as an unsigned decimal
 * The string size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_integer_as_unsigned_decimal_get_string_size(
     uint64_t integer_value,
     size_t *string_size,
     libcerror_error_t **error )
{
	static char *function        = "libfwevt_integer_as_decimal_get_string_size";
	uint64_t divider             = 0;
	uint8_t number_of_characters = 0;

	if( string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string size.",
		 function );

		return( -1 );
	}
	/* The string is at least a single digit with an end of string character
	 */
	number_of_characters = 2;

	divider = 1;

	while( ( integer_value / divider ) >= 10 )
	{
		divider *= 10;

		number_of_characters += 1;
	}
	*string_size = number_of_characters;

	return( 1 );
}

/* Copies an integer as an unsigned decimal to an UTF-8 string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_integer_as_unsigned_decimal_copy_to_utf8_string_with_index(
     uint64_t integer_value,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     libcerror_error_t **error )
{
	static char *function         = "libfwevt_integer_as_unsigned_decimal_copy_to_utf8_string_with_index";
	size_t safe_utf8_string_index = 0;
	uint64_t divider              = 0;
	uint8_t number_of_characters  = 0;

	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string index.",
		 function );

		return( -1 );
	}
	safe_utf8_string_index = *utf8_string_index;

	/* The string is at least a single digit with an end of string character
	 */
	number_of_characters = 2;

	divider = 1;

	while( ( integer_value / divider ) >= 10 )
	{
		divider *= 10;

		number_of_characters += 1;
	}
	if( ( number_of_characters > utf8_string_size )
	 || ( safe_utf8_string_index > ( utf8_string_size - number_of_characters ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid UTF-8 string size value too small.",
		 function );

		return( -1 );
	}
	while( divider > 1 )
	{
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '0' + (uint8_t) ( integer_value / divider );

		integer_value %= divider;

		divider /= 10;
	}
	utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '0' + (uint8_t) ( integer_value / divider );
	utf8_string[ safe_utf8_string_index++ ] = 0;

	*utf8_string_index = safe_utf8_string_index;

	return( 1 );
}

/* Copies an integer as an unsigned decimal to an UTF-16 string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_integer_as_unsigned_decimal_copy_to_utf16_string_with_index(
     uint64_t integer_value,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     libcerror_error_t **error )
{
	static char *function          = "libfwevt_integer_as_unsigned_decimal_copy_to_utf16_string_with_index";
	size_t safe_utf16_string_index = 0;
	uint64_t divider               = 0;
	uint8_t number_of_characters   = 0;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string index.",
		 function );

		return( -1 );
	}
	safe_utf16_string_index = *utf16_string_index;

	/* The string is at least a single digit with an end of string character
	 */
	number_of_characters = 2;

	divider = 1;

	while( ( integer_value / divider ) >= 10 )
	{
		divider *= 10;

		number_of_characters += 1;
	}
	if( ( number_of_characters > utf16_string_size )
	 || ( safe_utf16_string_index > ( utf16_string_size - number_of_characters ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid UTF-16 string size value too small.",
		 function );

		return( -1 );
	}
	while( divider > 1 )
	{
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '0' + (uint16_t) ( integer_value / divider );

		integer_value %= divider;

		divider /= 10;
	}
	utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '0' + (uint16_t) ( integer_value / divider );
	utf16_string[ safe_utf16_string_index++ ] = 0;

	*utf16_string_index = safe_utf16_string_index;

	return( 1 );
}

/* Copies an integer as hexadecimal to an UTF-8 string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_integer_as_hexadecimal_copy_to_utf8_string_with_index(
     uint64_t integer_value,
     uint8_t integer_size,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     libcerror_error_t **error )
{
	static char *function         = "libfwevt_integer_as_hexadecimal_copy_to_utf8_string_with_index";
	size_t safe_utf8_string_index = 0;
	uint8_t number_of_characters  = 0;
	uint8_t byte_value            = 0;
	int8_t bit_shift              = 0;

	if( integer_size == 32 )
	{
		number_of_characters = 11;
	}
	else if( integer_size == 64 )
	{
		number_of_characters = 19;
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported integer size.",
		 function );

		return( -1 );
	}
	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string index.",
		 function );

		return( -1 );
	}
	safe_utf8_string_index = *utf8_string_index;

	if( ( number_of_characters > utf8_string_size )
	 || ( safe_utf8_string_index > ( utf8_string_size - number_of_characters ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid UTF-8 string size value too small.",
		 function );

		return( -1 );
	}
	utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '0';
	utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'x';

	bit_shift = (uint8_t) ( integer_size - 4 );

	do
	{
		byte_value = (uint8_t) ( ( integer_value >> bit_shift ) & 0x0f );

		if( byte_value <= 9 )
		{
			utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '0' + byte_value;
		}
		else
		{
			utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'a' + byte_value - 10;
		}
		bit_shift -= 4;
	}
	while( bit_shift >= 0 );

	utf8_string[ safe_utf8_string_index++ ] = 0;

	*utf8_string_index = safe_utf8_string_index;

	return( 1 );
}

/* Copies an integer as hexadecimal to an UTF-16 string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_integer_as_hexadecimal_copy_to_utf16_string_with_index(
     uint64_t integer_value,
     uint8_t integer_size,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     libcerror_error_t **error )
{
	static char *function          = "libfwevt_integer_as_hexadecimal_copy_to_utf16_string_with_index";
	size_t safe_utf16_string_index = 0;
	uint8_t number_of_characters   = 0;
	uint8_t byte_value             = 0;
	int8_t bit_shift               = 0;

	if( integer_size == 32 )
	{
		number_of_characters = 11;
	}
	else if( integer_size == 64 )
	{
		number_of_characters = 19;
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported integer size.",
		 function );

		return( -1 );
	}
	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string index.",
		 function );

		return( -1 );
	}
	safe_utf16_string_index = *utf16_string_index;

	if( ( number_of_characters > utf16_string_size )
	 || ( safe_utf16_string_index > ( utf16_string_size - number_of_characters ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid UTF-16 string size value too small.",
		 function );

		return( -1 );
	}
	utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '0';
	utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'x';

	bit_shift = (uint16_t) ( integer_size - 4 );

	do
	{
		byte_value = (uint16_t) ( ( integer_value >> bit_shift ) & 0x0f );

		if( byte_value <= 9 )
		{
			utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '0' + byte_value;
		}
		else
		{
			utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'a' + byte_value - 10;
		}
		bit_shift -= 4;
	}
	while( bit_shift >= 0 );

	utf16_string[ safe_utf16_string_index++ ] = 0;

	*utf16_string_index = safe_utf16_string_index;

	return( 1 );
}

