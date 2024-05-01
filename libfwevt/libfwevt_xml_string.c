/*
 * XML string functions
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

#include "libfwevt_libcerror.h"
#include "libfwevt_libuna.h"
#include "libfwevt_xml_string.h"

/* Determines the size of an UTF-8 XML string from an UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
int libfwevt_utf8_xml_string_size_from_utf16_stream(
     const uint8_t *utf16_stream,
     size_t utf16_stream_size,
     int byte_order,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	static char *function                        = "libfwevt_utf8_xml_string_size_from_utf16_stream";
	libuna_unicode_character_t unicode_character = 0;
	size_t safe_utf8_string_size                 = 0;
	size_t utf16_stream_index                    = 0;
	int read_byte_order                          = 0;
	int result                                   = 0;

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
	if( utf16_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( utf16_stream_size % 2 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-16 stream value.",
		 function );

		return( -1 );
	}
	if( utf8_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string size.",
		 function );

		return( -1 );
	}
	if( utf16_stream_size == 0 )
	{
		return( 1 );
	}
	/* Check if UTF-16 stream is in big or little endian
	 */
	if( utf16_stream_size >= 2 )
	{
		if( ( utf16_stream[ 0 ] == 0xfe )
		 && ( utf16_stream[ 1 ] == 0xff ) )
		{
			read_byte_order    = LIBUNA_ENDIAN_BIG;
			utf16_stream_index = 2;
		}
		else if( ( utf16_stream[ 0 ] == 0xff )
		      && ( utf16_stream[ 1 ] == 0xfe ) )
		{
			read_byte_order    = LIBUNA_ENDIAN_LITTLE;
			utf16_stream_index = 2;
		}
		if( byte_order == 0 )
		{
			byte_order = read_byte_order;
		}
	}
	while( ( utf16_stream_index + 1 ) < utf16_stream_size )
	{
		/* Convert the UTF-16 stream bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf16_stream(
		     &unicode_character,
		     utf16_stream,
		     utf16_stream_size,
		     &utf16_stream_index,
		     byte_order,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-16 stream.",
			 function );

			return( -1 );
		}
		switch( unicode_character )
		{
			/* Replace & by &amp; */
			case (libuna_unicode_character_t) '&':
				safe_utf8_string_size += 5;
				break;

			/* Replace < by &lt; and > by &gt; */
			case (libuna_unicode_character_t) '<':
			case (libuna_unicode_character_t) '>':
				safe_utf8_string_size += 4;
				break;

			/* Replace ' by &apos; and " by &quot; */
/* TODO disabled for now since Event Viewer does not uses it
			case (libuna_unicode_character_t) '\'':
			case (libuna_unicode_character_t) '"':
				safe_utf8_string_size += 6;
				break;
*/

			default:
				/* Determine how many UTF-8 character bytes are required
				 */
				if( ( byte_order & LIBUNA_UTF16_STREAM_ALLOW_UNPAIRED_SURROGATE ) == 0 )
				{
					result = libuna_unicode_character_size_to_utf8(
						  unicode_character,
						  &safe_utf8_string_size,
						  error );
				}
				else
				{
					result = libuna_unicode_character_size_to_utf8_rfc2279(
						  unicode_character,
						  &safe_utf8_string_size,
						  error );
				}
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_CONVERSION,
					 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
					 "%s: unable to unable to determine size of Unicode character in UTF-8.",
					 function );

					return( -1 );
				}
				break;
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Check if the string is terminated with an end-of-string character
	 */
	if( unicode_character != 0 )
	{
		safe_utf8_string_size++;
	}
	*utf8_string_size = safe_utf8_string_size;

	return( 1 );
}

/* Copies an UTF-8 XML string from an UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
int libfwevt_utf8_xml_string_with_index_copy_from_utf16_stream(
     libuna_utf8_character_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     const uint8_t *utf16_stream,
     size_t utf16_stream_size,
     int byte_order,
     libcerror_error_t **error )
{
	static char *function                        = "libfwevt_utf8_xml_string_with_index_copy_from_utf16_stream";
	libuna_unicode_character_t unicode_character = 0;
	size_t safe_utf8_string_index                = 0;
	size_t utf16_stream_index                    = 0;
	int read_byte_order                          = 0;
	int result                                   = 0;

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
	if( utf16_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( utf16_stream_size == 0 )
	 || ( ( utf16_stream_size % 2 ) != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-16 stream value.",
		 function );

		return( -1 );
	}
	/* Check if UTF-16 stream is in big or little endian
	 */
	if( utf16_stream_size >= 2 )
	{
		if( ( utf16_stream[ 0 ] == 0xfe )
		 && ( utf16_stream[ 1 ] == 0xff ) )
		{
			read_byte_order    = LIBUNA_ENDIAN_BIG;
			utf16_stream_index = 2;
		}
		else if( ( utf16_stream[ 0 ] == 0xff )
		      && ( utf16_stream[ 1 ] == 0xfe ) )
		{
			read_byte_order    = LIBUNA_ENDIAN_LITTLE;
			utf16_stream_index = 2;
		}
		if( byte_order == 0 )
		{
			byte_order = read_byte_order;
		}
	}
	safe_utf8_string_index = *utf8_string_index;

	while( ( utf16_stream_index + 1 ) < utf16_stream_size )
	{
		/* Convert the UTF-16 stream bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf16_stream(
		     &unicode_character,
		     utf16_stream,
		     utf16_stream_size,
		     &utf16_stream_index,
		     byte_order,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-16 stream.",
			 function );

			return( -1 );
		}
		switch( unicode_character )
		{
			/* Replace & by &amp; */
			case (libuna_unicode_character_t) '&':
				if( ( safe_utf8_string_index + 5 ) > utf8_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-8 string size too small.",
					 function );

					return( -1 );
				}
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '&';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'a';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'm';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'p';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) ';';

				break;

			/* Replace < by &lt; */
			case (libuna_unicode_character_t) '<':
				if( ( safe_utf8_string_index + 4 ) > utf8_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-8 string size too small.",
					 function );

					return( -1 );
				}
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '&';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'l';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 't';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) ';';

				break;

			/* Replace > by &gt; */
			case (libuna_unicode_character_t) '>':
				if( ( safe_utf8_string_index + 4 ) > utf8_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-8 string size too small.",
					 function );

					return( -1 );
				}
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '&';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'g';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 't';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) ';';

				break;

			/* Replace ' by &apos; */
/* TODO disabled for now since Event Viewer does not uses it
			case (libuna_unicode_character_t) '\'':
				if( ( safe_utf8_string_index + 6 ) > utf8_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-8 string size too small.",
					 function );

					return( -1 );
				}
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '&';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'a';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'p';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'o';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 's';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) ';';

				break;
*/

			/* Replace " by &quot; */
/* TODO disabled for now since Event Viewer does not uses it
			case (libuna_unicode_character_t) '"':
				if( ( safe_utf8_string_index + 6 ) > utf8_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-8 string size too small.",
					 function );

					return( -1 );
				}
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '&';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'q';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'u';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'o';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 't';
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) ';';

				break;
*/

			default:
				/* Convert the Unicode character into UTF-8 character bytes
				 */
				if( ( byte_order & LIBUNA_UTF16_STREAM_ALLOW_UNPAIRED_SURROGATE ) == 0 )
				{
					result = libuna_unicode_character_copy_to_utf8(
						  unicode_character,
						  utf8_string,
						  utf8_string_size,
						  &safe_utf8_string_index,
						  error );
				}
				else
				{
					result = libuna_unicode_character_copy_to_utf8_rfc2279(
						  unicode_character,
						  utf8_string,
						  utf8_string_size,
						  &safe_utf8_string_index,
						  error );
				}
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_CONVERSION,
					 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
					 "%s: unable to copy Unicode character to UTF-8.",
					 function );

					return( -1 );
				}
				break;
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Check if the string is terminated with an end-of-string character
	 */
	if( unicode_character != 0 )
	{
		if( safe_utf8_string_index >= utf8_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-8 string too small.",
			 function );

			return( -1 );
		}
		utf8_string[ safe_utf8_string_index ] = 0;

		safe_utf8_string_index++;
	}
	*utf8_string_index = safe_utf8_string_index;

	return( 1 );
}

/* Determines the size of an UTF-16 XML string from an UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
int libfwevt_utf16_xml_string_size_from_utf16_stream(
     const uint8_t *utf16_stream,
     size_t utf16_stream_size,
     int byte_order,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function                        = "libfwevt_utf16_xml_string_size_from_utf16_stream";
	libuna_unicode_character_t unicode_character = 0;
	size_t safe_utf16_string_size                = 0;
	size_t utf16_stream_index                    = 0;
	int read_byte_order                          = 0;
	int result                                   = 0;

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
	if( utf16_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( utf16_stream_size % 2 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-16 stream value.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	if( utf16_stream_size == 0 )
	{
		return( 1 );
	}
	/* Check if UTF-16 stream is in big or little endian
	 */
	if( utf16_stream_size >= 2 )
	{
		if( ( utf16_stream[ 0 ] == 0x0ff )
		 && ( utf16_stream[ 1 ] == 0x0fe ) )
		{
			read_byte_order    = LIBUNA_ENDIAN_LITTLE;
			utf16_stream_index = 2;
		}
		else if( ( utf16_stream[ 0 ] == 0x0fe )
		      && ( utf16_stream[ 1 ] == 0x0ff ) )
		{
			read_byte_order    = LIBUNA_ENDIAN_BIG;
			utf16_stream_index = 2;
		}
		if( byte_order == 0 )
		{
			byte_order = read_byte_order;
		}
	}
	while( ( utf16_stream_index + 1 ) < utf16_stream_size )
	{
		/* Convert the UTF-16 stream bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf16_stream(
		     &unicode_character,
		     utf16_stream,
		     utf16_stream_size,
		     &utf16_stream_index,
		     byte_order,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-16 stream.",
			 function );

			return( -1 );
		}
		switch( unicode_character )
		{
			/* Replace & by &amp; */
			case (libuna_unicode_character_t) '&':
				safe_utf16_string_size += 5;
				break;

			/* Replace < by &lt; and > by &gt; */
			case (libuna_unicode_character_t) '<':
			case (libuna_unicode_character_t) '>':
				safe_utf16_string_size += 4;
				break;

			/* Replace ' by &apos; and " by &quot; */
/* TODO disabled for now since Event Viewer does not uses it
			case (libuna_unicode_character_t) '\'':
			case (libuna_unicode_character_t) '"':
				safe_utf16_string_size += 6;
				break;
*/

			default:
				/* Determine how many UTF-16 character bytes are required
				 */
				if( ( byte_order & LIBUNA_UTF16_STREAM_ALLOW_UNPAIRED_SURROGATE ) == 0 )
				{
					result = libuna_unicode_character_size_to_utf16(
						  unicode_character,
						  &safe_utf16_string_size,
						  error );
				}
				else
				{
					result = libuna_unicode_character_size_to_ucs2(
						  unicode_character,
						  &safe_utf16_string_size,
						  error );
				}
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_CONVERSION,
					 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
					 "%s: unable to unable to determine size of Unicode character in UTF-16.",
					 function );

					return( -1 );
				}
				break;
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Check if the string is terminated with an end-of-string character
	 */
	if( unicode_character != 0 )
	{
		safe_utf16_string_size++;
	}
	*utf16_string_size = safe_utf16_string_size;

	return( 1 );
}

/* Copies an UTF-16 XML string from an UTF-16 stream
 * Returns 1 if successful or -1 on error
 */
int libfwevt_utf16_xml_string_with_index_copy_from_utf16_stream(
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     const uint8_t *utf16_stream,
     size_t utf16_stream_size,
     int byte_order,
     libcerror_error_t **error )
{
	static char *function                        = "libfwevt_utf16_xml_string_with_index_copy_from_utf16_stream";
	libuna_unicode_character_t unicode_character = 0;
	size_t safe_utf16_string_index               = 0;
	size_t utf16_stream_index                    = 0;
	int read_byte_order                          = 0;
	int result                                   = 0;

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
	if( utf16_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( utf16_stream_size == 0 )
	 || ( ( utf16_stream_size % 2 ) != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: missing UTF-16 stream value.",
		 function );

		return( -1 );
	}
	/* Check if UTF-16 stream is in big or little endian
	 */
	if( utf16_stream_size >= 2 )
	{
		if( ( utf16_stream[ 0 ] == 0x0ff )
		 && ( utf16_stream[ 1 ] == 0x0fe ) )
		{
			read_byte_order    = LIBUNA_ENDIAN_LITTLE;
			utf16_stream_index = 2;
		}
		else if( ( utf16_stream[ 0 ] == 0x0fe )
		      && ( utf16_stream[ 1 ] == 0x0ff ) )
		{
			read_byte_order    = LIBUNA_ENDIAN_BIG;
			utf16_stream_index = 2;
		}
		if( byte_order == 0 )
		{
			byte_order = read_byte_order;
		}
	}
	safe_utf16_string_index = *utf16_string_index;

	while( ( utf16_stream_index + 1 ) < utf16_stream_size )
	{
		/* Convert the UTF-16 stream bytes into an Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf16_stream(
		     &unicode_character,
		     utf16_stream,
		     utf16_stream_size,
		     &utf16_stream_index,
		     byte_order,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_INPUT_FAILED,
			 "%s: unable to copy Unicode character from UTF-16 stream.",
			 function );

			return( -1 );
		}
		switch( unicode_character )
		{
			/* Replace & by &amp; */
			case (libuna_unicode_character_t) '&':
				if( ( safe_utf16_string_index + 5 ) > utf16_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-16 string size too small.",
					 function );

					return( -1 );
				}
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '&';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'a';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'm';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'p';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) ';';

				break;

			/* Replace < by &lt; */
			case (libuna_unicode_character_t) '<':
				if( ( safe_utf16_string_index + 4 ) > utf16_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-16 string size too small.",
					 function );

					return( -1 );
				}
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '&';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'l';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 't';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) ';';

				break;

			/* Replace > by &gt; */
			case (libuna_unicode_character_t) '>':
				if( ( safe_utf16_string_index + 4 ) > utf16_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-16 string size too small.",
					 function );

					return( -1 );
				}
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '&';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'g';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 't';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) ';';

				break;

			/* Replace ' by &apos; */
/* TODO disabled for now since Event Viewer does not uses it
			case (libuna_unicode_character_t) '\'':
				if( ( safe_utf16_string_index + 6 ) > utf16_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-16 string size too small.",
					 function );

					return( -1 );
				}
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '&';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'a';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'p';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'o';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 's';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) ';';

				break;
*/

			/* Replace " by &quot; */
/* TODO disabled for now since Event Viewer does not uses it
			case (libuna_unicode_character_t) '"':
				if( ( safe_utf16_string_index + 6 ) > utf16_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: UTF-16 string size too small.",
					 function );

					return( -1 );
				}
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '&';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'q';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'u';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'o';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 't';
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) ';';

				break;
*/

			default:
				/* Convert the Unicode character into UTF-16 character bytes
				 */
				if( ( byte_order & LIBUNA_UTF16_STREAM_ALLOW_UNPAIRED_SURROGATE ) == 0 )
				{
					result = libuna_unicode_character_copy_to_utf16(
						  unicode_character,
						  utf16_string,
						  utf16_string_size,
						  &safe_utf16_string_index,
						  error );
				}
				else
				{
					result = libuna_unicode_character_copy_to_ucs2(
						  unicode_character,
						  utf16_string,
						  utf16_string_size,
						  &safe_utf16_string_index,
						  error );
				}
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_CONVERSION,
					 LIBCERROR_CONVERSION_ERROR_OUTPUT_FAILED,
					 "%s: unable to copy Unicode character to UTF-16.",
					 function );

					return( -1 );
				}
				break;
		}
		if( unicode_character == 0 )
		{
			break;
		}
	}
	/* Check if the string is terminated with an end-of-string character
	 */
	if( unicode_character != 0 )
	{
		if( safe_utf16_string_index >= utf16_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string too small.",
			 function );

			return( -1 );
		}
		utf16_string[ safe_utf16_string_index ] = 0;

		safe_utf16_string_index++;
	}
	*utf16_string_index = safe_utf16_string_index;

	return( 1 );
}

