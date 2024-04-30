/*
 * Floating point (IEEE 754) functions
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
#include <types.h>

#include "libfwevt_floating_point.h"
#include "libfwevt_libcerror.h"

/* Deterimes the size of the string of a 32-bit floating point
 * The string size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_float32_get_string_size(
     uint32_t value_32bit,
     size_t *string_size,
     libcerror_error_t **error )
{
	static char *function        = "libfwevt_float32_get_string_size";
	uint8_t is_indeterminate     = 0;
	uint8_t is_infinite          = 0;
	uint8_t is_not_a_number      = 0;
	uint8_t is_negative          = 0;
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
	is_negative = (uint8_t) ( value_32bit >> 31 );

	if( is_negative != 0 )
	{
		value_32bit &= ~( (uint32_t) 1 << 31 );
	}
	if( value_32bit == 0x7f800000UL )
	{
		is_infinite = 1;
	}
	else if( ( is_negative != 0 )
	      && ( value_32bit == 0x7fc00000UL ) )
	{
		is_indeterminate = 1;
	}
	else if( ( value_32bit >= 0x7f800001UL )
	      && ( value_32bit <= 0x7fffffffUL ) )
	{
		is_not_a_number = 1;
	}
	if( is_indeterminate != 0 )
	{
		/* "Ind" + end-of-string character */
		number_of_characters = 4;
	}
	else if( is_infinite != 0 )
	{
		/* "Inf" + end-of-string character */
		number_of_characters = 4;
	}
	else if( is_not_a_number != 0 )
	{
		/* "Nan" + end-of-string character */
		number_of_characters = 4;
	}
	else
	{
		/* "[-]0.000000e[+-]000" + end-of-string character */
		if( is_negative != 0 )
		{
			number_of_characters = 15;
		}
		else
		{
			number_of_characters = 14;
		}
	}
	*string_size = number_of_characters;

	return( 1 );
}

/* Copies a 32-bit floating point to an UTF-8 string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_float32_copy_to_utf8_string_with_index(
     uint32_t value_32bit,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     libcerror_error_t **error )
{
	byte_stream_float32_t value_float32;

	static char *function         = "libfwevt_float32_copy_to_utf8_string_with_index";
	size_t safe_utf8_string_index = 0;
	uint32_t divider              = 0;
	uint32_t value_fraction       = 0;
	int16_t exponent10            = 0;
	int16_t exponent2             = 0;
	uint8_t digit_index           = 0;
	uint8_t exponent_sign         = 0;
	uint8_t is_indeterminate      = 0;
	uint8_t is_infinite           = 0;
	uint8_t is_not_a_number       = 0;
	uint8_t is_negative           = 0;
	uint8_t number_of_characters  = 0;
	double exponent_value         = 0.0;
	double value_float            = 0.0;

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

	is_negative = (uint8_t) ( value_32bit >> 31 );

	if( is_negative != 0 )
	{
		value_32bit &= ~( (uint32_t) 1 << 31 );
	}
	if( value_32bit == 0x7f800000UL )
	{
		is_infinite = 1;
	}
	else if( ( is_negative != 0 )
	      && ( value_32bit == 0x7fc00000UL ) )
	{
		is_indeterminate = 1;
	}
	else if( ( value_32bit >= 0x7f800001UL )
	      && ( value_32bit <= 0x7fffffffUL ) )
	{
		is_not_a_number = 1;
	}
	else if( value_32bit != 0 )
	{
		value_float32.integer = value_32bit;
		value_float           = (double) value_float32.floating_point;

		exponent2 = (int16_t) ( value_32bit >> 23 );

		if( exponent2 == 0 )
		{
			exponent2 = -126;
		}
		else
		{
			exponent2 -= 127;
		}
	}
	if( is_indeterminate != 0 )
	{
		/* "Ind" + end-of-string character */
		number_of_characters = 4;
	}
	else if( is_infinite != 0 )
	{
		/* "Inf" + end-of-string character */
		number_of_characters = 4;
	}
	else if( is_not_a_number != 0 )
	{
		/* "Nan" + end-of-string character */
		number_of_characters = 4;
	}
	else
	{
		/* "[-]0.000000e[+-]000" + end-of-string character */
		if( is_negative != 0 )
		{
			number_of_characters = 15;
		}
		else
		{
			number_of_characters = 14;
		}
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
	if( is_indeterminate != 0 )
	{
		/* "Ind" + end-of-string character */
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'I';
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'n';
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'd';
	}
	else if( is_infinite != 0 )
	{
		/* "Inf" + end-of-string character */
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'I';
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'n';
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'f';
	}
	else if( is_not_a_number != 0 )
	{
		/* "Nan" + end-of-string character */
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'N';
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'a';
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'N';
	}
	else
	{
		/* "[-]0.000000e[+-]000" + end-of-string character */
		if( is_negative != 0 )
		{
			utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '-';
		}
		if( exponent2 < 0 )
		{
			exponent_sign = (uint8_t) '-';
			exponent2    *= -1;
		}
		else
		{
			exponent_sign = (uint8_t) '+';
		}
		exponent_value = 1.0;
		exponent10     = 0;

		while( exponent2 > 0 )
		{
			exponent_value *= 2;
			exponent2--;

			if( exponent_value >= 10.0 )
			{
				exponent_value /= 10.0;
				exponent10++;

				if( exponent_sign == (uint8_t) '-' )
				{
					value_float *= 10.0;
				}
				else
				{
					value_float /= 10.0;
				}
			}
		}
		if( value_float != 0.0 )
		{
			while( ( value_float < 1.0 )
			    || ( value_float >= 10.0 ) )
			{
				exponent10++;

				if( exponent_sign == (uint8_t) '-' )
				{
					value_float *= 10;
				}
				else
				{
					value_float /= 10;
				}
			}
		}
		for( digit_index = 0;
		     digit_index < 7;
		     digit_index++ )
		{
			value_fraction *= 10;
			value_fraction += (uint8_t) value_float;

			value_float -= (uint8_t) value_float;
			value_float *= 10.0;
		}
		if( value_float >= 5.0 )
		{
			value_fraction += 1;
		}
		divider = 1000000;

		for( digit_index = 0;
		     digit_index < 7;
		     digit_index++ )
		{
			utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '0' + (uint8_t) ( value_fraction / divider );

			if( digit_index == 0 )
			{
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '.';
			}
			value_fraction %= divider;
			divider        /= 10;
		}
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'e';
		utf8_string[ safe_utf8_string_index++ ] = exponent_sign;

		divider = 100;

		for( digit_index = 0;
		     digit_index < 3;
		     digit_index++ )
		{
			utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '0' + (uint8_t) ( exponent10 / divider );

			exponent10 %= divider;
			divider    /= 10;
		}
	}
	utf8_string[ safe_utf8_string_index++ ] = 0;

	*utf8_string_index = safe_utf8_string_index;

	return( 1 );
}

/* Copies a 32-bit floating point to an UTF-16 string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_float32_copy_to_utf16_string_with_index(
     uint32_t value_32bit,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     libcerror_error_t **error )
{
	byte_stream_float32_t value_float32;

	static char *function          = "libfwevt_float32_copy_to_utf16_string_with_index";
	size_t safe_utf16_string_index = 0;
	uint32_t divider               = 0;
	uint32_t value_fraction        = 0;
	uint16_t exponent_sign         = 0;
	int16_t exponent10             = 0;
	int16_t exponent2              = 0;
	uint8_t digit_index            = 0;
	uint8_t is_indeterminate       = 0;
	uint8_t is_infinite            = 0;
	uint8_t is_not_a_number        = 0;
	uint8_t is_negative            = 0;
	uint8_t number_of_characters   = 0;
	double exponent_value          = 0.0;
	double value_float             = 0.0;

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

	is_negative = (uint8_t) ( value_32bit >> 31 );

	if( is_negative != 0 )
	{
		value_32bit &= ~( (uint32_t) 1 << 31 );
	}
	if( value_32bit == 0x7f800000UL )
	{
		is_infinite = 1;
	}
	else if( ( is_negative != 0 )
	      && ( value_32bit == 0x7fc00000UL ) )
	{
		is_indeterminate = 1;
	}
	else if( ( value_32bit >= 0x7f800001UL )
	      && ( value_32bit <= 0x7fffffffUL ) )
	{
		is_not_a_number = 1;
	}
	else if( value_32bit != 0 )
	{
		value_float32.integer = value_32bit;
		value_float           = (double) value_float32.floating_point;

		exponent2 = (int16_t) ( value_32bit >> 23 );

		if( exponent2 == 0 )
		{
			exponent2 = -126;
		}
		else
		{
			exponent2 -= 127;
		}
	}
	if( is_indeterminate != 0 )
	{
		/* "Ind" + end-of-string character */
		number_of_characters = 4;
	}
	else if( is_infinite != 0 )
	{
		/* "Inf" + end-of-string character */
		number_of_characters = 4;
	}
	else if( is_not_a_number != 0 )
	{
		/* "Nan" + end-of-string character */
		number_of_characters = 4;
	}
	else
	{
		/* "[-]0.000000e[+-]000" + end-of-string character */
		if( is_negative != 0 )
		{
			number_of_characters = 15;
		}
		else
		{
			number_of_characters = 14;
		}
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
	if( is_indeterminate != 0 )
	{
		/* "Ind" + end-of-string character */
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'I';
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'n';
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'd';
	}
	else if( is_infinite != 0 )
	{
		/* "Inf" + end-of-string character */
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'I';
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'n';
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'f';
	}
	else if( is_not_a_number != 0 )
	{
		/* "Nan" + end-of-string character */
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'N';
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'a';
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'N';
	}
	else
	{
		/* "[-]0.000000e[+-]000" + end-of-string character */
		if( is_negative != 0 )
		{
			utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '-';
		}
		if( exponent2 < 0 )
		{
			exponent_sign = (uint16_t) '-';
			exponent2    *= -1;
		}
		else
		{
			exponent_sign = (uint16_t) '+';
		}
		exponent_value = 1.0;
		exponent10     = 0;

		while( exponent2 > 0 )
		{
			exponent_value *= 2;
			exponent2--;

			if( exponent_value >= 10.0 )
			{
				exponent_value /= 10.0;
				exponent10++;

				if( exponent_sign == (uint16_t) '-' )
				{
					value_float *= 10.0;
				}
				else
				{
					value_float /= 10.0;
				}
			}
		}
		if( value_float != 0.0 )
		{
			while( ( value_float < 1.0 )
			    || ( value_float >= 10.0 ) )
			{
				exponent10++;

				if( exponent_sign == (uint16_t) '-' )
				{
					value_float *= 10;
				}
				else
				{
					value_float /= 10;
				}
			}
		}
		for( digit_index = 0;
		     digit_index < 7;
		     digit_index++ )
		{
			value_fraction *= 10;
			value_fraction += (uint8_t) value_float;

			value_float -= (uint8_t) value_float;
			value_float *= 10.0;
		}
		if( value_float >= 5.0 )
		{
			value_fraction += 1;
		}
		divider = 1000000;

		for( digit_index = 0;
		     digit_index < 7;
		     digit_index++ )
		{
			utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '0' + (uint16_t) ( value_fraction / divider );

			if( digit_index == 0 )
			{
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '.';
			}
			value_fraction %= divider;
			divider        /= 10;
		}
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'e';
		utf16_string[ safe_utf16_string_index++ ] = exponent_sign;

		divider = 100;

		for( digit_index = 0;
		     digit_index < 3;
		     digit_index++ )
		{
			utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '0' + (uint16_t) ( exponent10 / divider );

			exponent10 %= divider;
			divider    /= 10;
		}
	}
	utf16_string[ safe_utf16_string_index++ ] = 0;

	*utf16_string_index = safe_utf16_string_index;

	return( 1 );
}

/* Deterimes the size of the string of a 64-bit floating point
 * The string size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_float64_get_string_size(
     uint64_t value_64bit,
     size_t *string_size,
     libcerror_error_t **error )
{
	static char *function        = "libfwevt_float64_get_string_size";
	uint8_t is_indeterminate     = 0;
	uint8_t is_infinite          = 0;
	uint8_t is_not_a_number      = 0;
	uint8_t is_negative          = 0;
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
	is_negative = (uint8_t) ( value_64bit >> 63 );

	if( is_negative != 0 )
	{
		value_64bit &= ~( (uint64_t) 1 << 63 );
	}
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
	if( value_64bit == 0x7ff0000000000000UL )
#else
	if( value_64bit == 0x7ff0000000000000ULL )
#endif
	{
		is_infinite = 1;
	}
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
	else if( ( is_negative != 0 )
	      && ( value_64bit == 0x7ff8000000000000UL ) )
#else
	else if( ( is_negative != 0 )
	      && ( value_64bit == 0x7ff8000000000000ULL ) )
#endif
	{
		is_indeterminate = 1;
	}
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
	else if( ( value_64bit >= 0x7ff0000000000001UL )
	      && ( value_64bit <= 0x7fffffffffffffffUL ) )
#else
	else if( ( value_64bit >= 0x7ff0000000000001ULL )
	      && ( value_64bit <= 0x7fffffffffffffffULL ) )
#endif
	{
		is_not_a_number = 1;
	}
	if( is_indeterminate != 0 )
	{
		/* "Ind" + end-of-string character */
		number_of_characters = 4;
	}
	else if( is_infinite != 0 )
	{
		/* "Inf" + end-of-string character */
		number_of_characters = 4;
	}
	else if( is_not_a_number != 0 )
	{
		/* "Nan" + end-of-string character */
		number_of_characters = 4;
	}
	else
	{
		/* "[-]0.000000e[+-]000" + end-of-string character */
		if( is_negative != 0 )
		{
			number_of_characters = 15;
		}
		else
		{
			number_of_characters = 14;
		}
	}
	*string_size = number_of_characters;

	return( 1 );
}

/* Copies a 64-bit floating point to an UTF-8 string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_float64_copy_to_utf8_string_with_index(
     uint64_t value_64bit,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     libcerror_error_t **error )
{
	byte_stream_float64_t value_float64;

	static char *function         = "libfwevt_float64_copy_to_utf8_string_with_index";
	size_t safe_utf8_string_index = 0;
	uint64_t divider              = 0;
	uint64_t value_fraction       = 0;
	int16_t exponent10            = 0;
	int16_t exponent2             = 0;
	uint8_t digit_index           = 0;
	uint8_t exponent_sign         = 0;
	uint8_t is_indeterminate      = 0;
	uint8_t is_infinite           = 0;
	uint8_t is_not_a_number       = 0;
	uint8_t is_negative           = 0;
	uint8_t number_of_characters  = 0;
	double exponent_value         = 0.0;
	double value_float            = 0.0;

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

	is_negative = (uint8_t) ( value_64bit >> 63 );

	if( is_negative != 0 )
	{
		value_64bit &= ~( (uint64_t) 1 << 63 );
	}
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
	if( value_64bit == 0x7ff0000000000000UL )
#else
	if( value_64bit == 0x7ff0000000000000ULL )
#endif
	{
		is_infinite = 1;
	}
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
	else if( ( is_negative != 0 )
	      && ( value_64bit == 0x7ff8000000000000UL ) )
#else
	else if( ( is_negative != 0 )
	      && ( value_64bit == 0x7ff8000000000000ULL ) )
#endif
	{
		is_indeterminate = 1;
	}
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
	else if( ( value_64bit >= 0x7ff0000000000001UL )
	      && ( value_64bit <= 0x7fffffffffffffffUL ) )
#else
	else if( ( value_64bit >= 0x7ff0000000000001ULL )
	      && ( value_64bit <= 0x7fffffffffffffffULL ) )
#endif
	{
		is_not_a_number = 1;
	}
	else if( value_64bit != 0 )
	{
		value_float64.integer = value_64bit;
		value_float           = (double) value_float64.floating_point;

		exponent2 = (int16_t) ( value_64bit >> 52 );

		if( exponent2 == 0 )
		{
			exponent2 = -1023;
		}
		else
		{
			exponent2 -= 1023;
		}
	}
	if( is_indeterminate != 0 )
	{
		/* "Ind" + end-of-string character */
		number_of_characters = 4;
	}
	else if( is_infinite != 0 )
	{
		/* "Inf" + end-of-string character */
		number_of_characters = 4;
	}
	else if( is_not_a_number != 0 )
	{
		/* "Nan" + end-of-string character */
		number_of_characters = 4;
	}
	else
	{
		/* "[-]0.000000e[+-]000" + end-of-string character */
		if( is_negative != 0 )
		{
			number_of_characters = 15;
		}
		else
		{
			number_of_characters = 14;
		}
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
	if( is_indeterminate != 0 )
	{
		/* "Ind" + end-of-string character */
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'I';
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'n';
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'd';
	}
	else if( is_infinite != 0 )
	{
		/* "Inf" + end-of-string character */
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'I';
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'n';
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'f';
	}
	else if( is_not_a_number != 0 )
	{
		/* "Nan" + end-of-string character */
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'N';
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'a';
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'N';
	}
	else
	{
		/* "[-]0.000000e[+-]000" + end-of-string character */
		if( is_negative != 0 )
		{
			utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '-';
		}
		if( exponent2 < 0 )
		{
			exponent_sign = (uint8_t) '-';
			exponent2    *= -1;
		}
		else
		{
			exponent_sign = (uint8_t) '+';
		}
		exponent_value = 1.0;
		exponent10     = 0;

		while( exponent2 > 0 )
		{
			exponent_value *= 2;
			exponent2--;

			if( exponent_value >= 10.0 )
			{
				exponent_value /= 10.0;
				exponent10++;

				if( exponent_sign == (uint8_t) '-' )
				{
					value_float *= 10.0;
				}
				else
				{
					value_float /= 10.0;
				}
			}
		}
		if( value_float != 0.0 )
		{
			while( ( value_float < 1.0 )
			    || ( value_float >= 10.0 ) )
			{
				exponent10++;

				if( exponent_sign == (uint8_t) '-' )
				{
					value_float *= 10;
				}
				else
				{
					value_float /= 10;
				}
			}
		}
		for( digit_index = 0;
		     digit_index < 7;
		     digit_index++ )
		{
			value_fraction *= 10;
			value_fraction += (uint8_t) value_float;

			value_float -= (uint8_t) value_float;
			value_float *= 10.0;
		}
		if( value_float >= 5.0 )
		{
			value_fraction += 1;
		}
		divider = 1000000;

		for( digit_index = 0;
		     digit_index < 7;
		     digit_index++ )
		{
			utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '0' + (uint8_t) ( value_fraction / divider );

			if( digit_index == 0 )
			{
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '.';
			}
			value_fraction %= divider;
			divider        /= 10;
		}
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'e';
		utf8_string[ safe_utf8_string_index++ ] = exponent_sign;

		divider = 100;

		for( digit_index = 0;
		     digit_index < 3;
		     digit_index++ )
		{
			utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '0' + (uint8_t) ( exponent10 / divider );

			exponent10 %= divider;
			divider    /= 10;
		}
	}
	utf8_string[ safe_utf8_string_index++ ] = 0;

	*utf8_string_index = safe_utf8_string_index;

	return( 1 );
}

/* Copies a 64-bit floating point to an UTF-16 string
 * The string size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwevt_float64_copy_to_utf16_string_with_index(
     uint64_t value_64bit,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     libcerror_error_t **error )
{
	byte_stream_float64_t value_float64;

	static char *function          = "libfwevt_float64_copy_to_utf16_string_with_index";
	size_t safe_utf16_string_index = 0;
	uint64_t divider               = 0;
	uint64_t value_fraction        = 0;
	uint16_t exponent_sign         = 0;
	int16_t exponent10             = 0;
	int16_t exponent2              = 0;
	uint8_t digit_index            = 0;
	uint8_t is_indeterminate       = 0;
	uint8_t is_infinite            = 0;
	uint8_t is_not_a_number        = 0;
	uint8_t is_negative            = 0;
	uint8_t number_of_characters   = 0;
	double exponent_value          = 0.0;
	double value_float             = 0.0;

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

	is_negative = (uint8_t) ( value_64bit >> 63 );

	if( is_negative != 0 )
	{
		value_64bit &= ~( (uint64_t) 1 << 63 );
	}
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
	if( value_64bit == 0x7ff0000000000000UL )
#else
	if( value_64bit == 0x7ff0000000000000ULL )
#endif
	{
		is_infinite = 1;
	}
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
	else if( ( is_negative != 0 )
	      && ( value_64bit == 0x7ff8000000000000UL ) )
#else
	else if( ( is_negative != 0 )
	      && ( value_64bit == 0x7ff8000000000000ULL ) )
#endif
	{
		is_indeterminate = 1;
	}
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
	else if( ( value_64bit >= 0x7ff0000000000001UL )
	      && ( value_64bit <= 0x7fffffffffffffffUL ) )
#else
	else if( ( value_64bit >= 0x7ff0000000000001ULL )
	      && ( value_64bit <= 0x7fffffffffffffffULL ) )
#endif
	{
		is_not_a_number = 1;
	}
	else if( value_64bit != 0 )
	{
		value_float64.integer = value_64bit;
		value_float           = (double) value_float64.floating_point;

		exponent2 = (int16_t) ( value_64bit >> 52 );

		if( exponent2 == 0 )
		{
			exponent2 = -1023;
		}
		else
		{
			exponent2 -= 1023;
		}
	}
	if( is_indeterminate != 0 )
	{
		/* "Ind" + end-of-string character */
		number_of_characters = 4;
	}
	else if( is_infinite != 0 )
	{
		/* "Inf" + end-of-string character */
		number_of_characters = 4;
	}
	else if( is_not_a_number != 0 )
	{
		/* "Nan" + end-of-string character */
		number_of_characters = 4;
	}
	else
	{
		/* "[-]0.000000e[+-]000" + end-of-string character */
		if( is_negative != 0 )
		{
			number_of_characters = 15;
		}
		else
		{
			number_of_characters = 14;
		}
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
	if( is_indeterminate != 0 )
	{
		/* "Ind" + end-of-string character */
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'I';
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'n';
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'd';
	}
	else if( is_infinite != 0 )
	{
		/* "Inf" + end-of-string character */
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'I';
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'n';
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'f';
	}
	else if( is_not_a_number != 0 )
	{
		/* "Nan" + end-of-string character */
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'N';
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'a';
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'N';
	}
	else
	{
		/* "[-]0.000000e[+-]000" + end-of-string character */
		if( is_negative != 0 )
		{
			utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '-';
		}
		if( exponent2 < 0 )
		{
			exponent_sign = (uint16_t) '-';
			exponent2    *= -1;
		}
		else
		{
			exponent_sign = (uint16_t) '+';
		}
		exponent_value = 1.0;
		exponent10     = 0;

		while( exponent2 > 0 )
		{
			exponent_value *= 2;
			exponent2--;

			if( exponent_value >= 10.0 )
			{
				exponent_value /= 10.0;
				exponent10++;

				if( exponent_sign == (uint16_t) '-' )
				{
					value_float *= 10.0;
				}
				else
				{
					value_float /= 10.0;
				}
			}
		}
		if( value_float != 0.0 )
		{
			while( ( value_float < 1.0 )
			    || ( value_float >= 10.0 ) )
			{
				exponent10++;

				if( exponent_sign == (uint16_t) '-' )
				{
					value_float *= 10;
				}
				else
				{
					value_float /= 10;
				}
			}
		}
		for( digit_index = 0;
		     digit_index < 7;
		     digit_index++ )
		{
			value_fraction *= 10;
			value_fraction += (uint8_t) value_float;

			value_float -= (uint8_t) value_float;
			value_float *= 10.0;
		}
		if( value_float >= 5.0 )
		{
			value_fraction += 1;
		}
		divider = 1000000;

		for( digit_index = 0;
		     digit_index < 7;
		     digit_index++ )
		{
			utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '0' + (uint16_t) ( value_fraction / divider );

			if( digit_index == 0 )
			{
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '.';
			}
			value_fraction %= divider;
			divider        /= 10;
		}
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'e';
		utf16_string[ safe_utf16_string_index++ ] = exponent_sign;

		divider = 100;

		for( digit_index = 0;
		     digit_index < 3;
		     digit_index++ )
		{
			utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '0' + (uint16_t) ( exponent10 / divider );

			exponent10 %= divider;
			divider    /= 10;
		}
	}
	utf16_string[ safe_utf16_string_index++ ] = 0;

	*utf16_string_index = safe_utf16_string_index;

	return( 1 );
}

