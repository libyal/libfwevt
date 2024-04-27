/*
 * Date and time values functions
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

#include "libfwevt_date_time.h"
#include "libfwevt_libcerror.h"

#if !defined( LIBFWEVT_ATTRIBUTE_FALLTHROUGH )
#if defined( __GNUC__ ) && __GNUC__ >= 7
#define LIBFWEVT_ATTRIBUTE_FALLTHROUGH	__attribute__ ((fallthrough))
#else
#define LIBFWEVT_ATTRIBUTE_FALLTHROUGH
#endif
#endif

/* Copies an ISO 8601 UTF-8 formatted string to a FILETIME value
 * Returns 1 if successful or -1 on error
 */
int libfwevt_utf8_string_copy_to_filetime(
     const uint8_t *utf8_string,
     size_t utf8_string_size,
     uint64_t *filetime,
     libcerror_error_t **error )
{
	static char *function       = "libfwevt_utf8_string_copy_to_filetime";
	uint64_t safe_filetime      = 0;
	uint32_t fraction_of_second = 0;
	uint16_t current_year       = 0;
	uint16_t year               = 0;
	uint8_t day_of_month        = 0;
	uint8_t days_per_month      = 0;
	uint8_t hours               = 0;
	uint8_t minutes             = 0;
	uint8_t month               = 0;
	uint8_t is_leap_year        = 0;
	uint8_t seconds             = 0;
	size_t utf8_string_index    = 0;

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
	if( ( utf8_string_size < 31 )
	 || ( utf8_string_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid UTF-8 string size value out of bounds.",
		 function );

		return( -1 );
	}
	if( filetime == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid FILETIME value.",
		 function );

		return( -1 );
	}
	if( ( utf8_string[ 4 ] != (uint8_t) '-' )
	 || ( utf8_string[ 7 ] != (uint8_t) '-' )
	 || ( utf8_string[ 10 ] != (uint8_t) 'T' )
	 || ( utf8_string[ 13 ] != (uint8_t) ':' )
	 || ( utf8_string[ 16 ] != (uint8_t) ':' )
	 || ( utf8_string[ 19 ] != (uint8_t) '.' )
	 || ( utf8_string[ 29 ] != (uint8_t) 'Z' )
	 || ( utf8_string[ 30 ] != (uint8_t) 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported date time string.",
		 function );

		return( -1 );
	}
	for( utf8_string_index = 0;
	     utf8_string_index < 4;
	     utf8_string_index++ )
	{
		if( ( utf8_string[ utf8_string_index ] < (uint8_t) '0' )
		 || ( utf8_string[ utf8_string_index ] > (uint8_t) '9' ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid date time string - unsupported year value.",
			 function );

			return( -1 );
		}
		year *= 10;
		year += utf8_string[ utf8_string_index ] - (uint8_t) '0';
	}
	for( utf8_string_index = 5;
	     utf8_string_index < 7;
	     utf8_string_index++ )
	{
		if( ( utf8_string[ utf8_string_index ] < (uint8_t) '0' )
		 || ( utf8_string[ utf8_string_index ] > (uint8_t) '9' ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid date time string - unsupported month value.",
			 function );

			return( -1 );
		}
		month *= 10;
		month += utf8_string[ utf8_string_index ] - (uint8_t) '0';
	}
	for( utf8_string_index = 8;
	     utf8_string_index < 10;
	     utf8_string_index++ )
	{
		if( ( utf8_string[ utf8_string_index ] < (uint8_t) '0' )
		 || ( utf8_string[ utf8_string_index ] > (uint8_t) '9' ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid date time string - unsupported day of month value.",
			 function );

			return( -1 );
		}
		day_of_month *= 10;
		day_of_month += utf8_string[ utf8_string_index ] - (uint8_t) '0';
	}
	for( utf8_string_index = 11;
	     utf8_string_index < 13;
	     utf8_string_index++ )
	{
		if( ( utf8_string[ utf8_string_index ] < (uint8_t) '0' )
		 || ( utf8_string[ utf8_string_index ] > (uint8_t) '9' ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid date time string - unsupported hours value.",
			 function );

			return( -1 );
		}
		hours *= 10;
		hours += utf8_string[ utf8_string_index ] - (uint8_t) '0';
	}
	for( utf8_string_index = 14;
	     utf8_string_index < 16;
	     utf8_string_index++ )
	{
		if( ( utf8_string[ utf8_string_index ] < (uint8_t) '0' )
		 || ( utf8_string[ utf8_string_index ] > (uint8_t) '9' ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid date time string - unsupported minutes value.",
			 function );

			return( -1 );
		}
		minutes *= 10;
		minutes += utf8_string[ utf8_string_index ] - (uint8_t) '0';
	}
	for( utf8_string_index = 17;
	     utf8_string_index < 19;
	     utf8_string_index++ )
	{
		if( ( utf8_string[ utf8_string_index ] < (uint8_t) '0' )
		 || ( utf8_string[ utf8_string_index ] > (uint8_t) '9' ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid date time string - unsupported seconds value.",
			 function );

			return( -1 );
		}
		seconds *= 10;
		seconds += utf8_string[ utf8_string_index ] - (uint8_t) '0';
	}
	for( utf8_string_index = 20;
	     utf8_string_index < 29;
	     utf8_string_index++ )
	{
		if( ( utf8_string[ utf8_string_index ] < (uint8_t) '0' )
		 || ( utf8_string[ utf8_string_index ] > (uint8_t) '9' ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid date time string - unsupported fraction of second value.",
			 function );

			return( -1 );
		}
		fraction_of_second *= 10;
		fraction_of_second += utf8_string[ utf8_string_index ] - (uint8_t) '0';
	}
	if( year < 1600 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported year value: %" PRIu16 ".",
		 function,
		 year );

		return( -1 );
	}
	if( ( ( ( year % 4 ) == 0 )
	  &&  ( ( year % 100 ) != 0 ) )
	 || ( ( year % 400 ) == 0 ) )
	{
		is_leap_year = 1;
	}
	switch( month )
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			days_per_month = 31;
			break;

		case 2:
			if( is_leap_year != 0 )
			{
				days_per_month = 29;
			}
			else
			{
				days_per_month = 28;
			}
			break;

		case 4:
		case 6:
		case 9:
		case 11:
			days_per_month = 30;
			break;

		default:
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported month value: %" PRIu8 ".",
			 function,
			 month );

			return( -1 );
	}
	if( ( day_of_month < 1 )
	 || ( day_of_month > days_per_month ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported day of month value: %" PRIu8 ".",
		 function,
		 day_of_month );

		return( -1 );
	}
	if( hours > 23 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported hours value: %" PRIu8 ".",
		 function,
		 hours );

		return( -1 );
	}
	if( minutes > 59 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported minutes value: %" PRIu8 ".",
		 function,
		 minutes );

		return( -1 );
	}
	if( seconds > 59 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported seconds value: %" PRIu8 ".",
		 function,
		 seconds );

		return( -1 );
	}
	current_year = 1600;

	while( current_year < ( year - 100 ) )
	{
		if( ( current_year % 400 ) == 0 )
		{
			safe_filetime += 36525;
		}
		else
		{
			safe_filetime += 36524;
		}
		current_year += 100;
	}
	while( current_year < year )
	{
		if( ( ( ( current_year % 4 ) == 0 )
		  &&  ( ( current_year % 100 ) != 0 ) )
		 || ( ( current_year % 400 ) == 0 ) )
		{
			safe_filetime += 366;
		}
		else
		{
			safe_filetime += 365;
		}
		current_year += 1;
	}
	/* Do not include the number of days in 1600 */
	safe_filetime -= 366;

	switch( month )
	{
		case 12:
			safe_filetime += 30;

		LIBFWEVT_ATTRIBUTE_FALLTHROUGH;
		case 11:
			safe_filetime += 31;

		LIBFWEVT_ATTRIBUTE_FALLTHROUGH;
		case 10:
			safe_filetime += 30;

		LIBFWEVT_ATTRIBUTE_FALLTHROUGH;
		case 9:
			safe_filetime += 31;

		LIBFWEVT_ATTRIBUTE_FALLTHROUGH;
		case 8:
			safe_filetime += 31;

		LIBFWEVT_ATTRIBUTE_FALLTHROUGH;
		case 7:
			safe_filetime += 30;

		LIBFWEVT_ATTRIBUTE_FALLTHROUGH;
		case 6:
			safe_filetime += 31;

		LIBFWEVT_ATTRIBUTE_FALLTHROUGH;
		case 5:
			safe_filetime += 30;

		LIBFWEVT_ATTRIBUTE_FALLTHROUGH;
		case 4:
			safe_filetime += 31;

		LIBFWEVT_ATTRIBUTE_FALLTHROUGH;
		case 3:
			if( is_leap_year != 0 )
			{
				safe_filetime += 29;
			}
			else
			{
				safe_filetime += 28;
			}

		LIBFWEVT_ATTRIBUTE_FALLTHROUGH;
		case 2:
			safe_filetime += 31;

		LIBFWEVT_ATTRIBUTE_FALLTHROUGH;
		default:
			safe_filetime += day_of_month - 1;
	}
	safe_filetime *= 24;
	safe_filetime += hours;
	safe_filetime *= 60;
	safe_filetime += minutes;
	safe_filetime *= 60;
	safe_filetime += seconds;
	safe_filetime *= 1000000000;
	safe_filetime += fraction_of_second;
	safe_filetime /= 100;

	*filetime = safe_filetime;

	return( 1 );
}

