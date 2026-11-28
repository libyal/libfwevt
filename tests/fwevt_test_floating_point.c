/*
 * Library floating point functions test program
 *
 * Copyright (C) 2011-2026, Joachim Metz <joachim.metz@gmail.com>
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
#include <file_stream.h>
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fwevt_test_libcerror.h"
#include "fwevt_test_libfwevt.h"
#include "fwevt_test_macros.h"
#include "fwevt_test_unused.h"

#include "../libfwevt/libfwevt_floating_point.h"

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

/* Tests the libfwevt_float32_get_string_size function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_float32_get_string_size(
     void )
{
	libcerror_error_t *error = NULL;
	size_t string_size       = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_float32_get_string_size(
	          0,
	          &string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "string_size",
	 string_size,
	 (size_t) 14 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Negative normal float (-1.0f = 0xbf800000)
	 */
	result = libfwevt_float32_get_string_size(
	          0xbf800000UL,
	          &string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_SIZE( "string_size", string_size, (size_t) 15 );
	FWEVT_TEST_ASSERT_IS_NULL( "error", error );

	/* Positive infinity (0x7f800000)
	 */
	result = libfwevt_float32_get_string_size(
	          0x7f800000UL,
	          &string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_SIZE( "string_size", string_size, (size_t) 4 );
	FWEVT_TEST_ASSERT_IS_NULL( "error", error );

	/* Indeterminate (0xffc00000)
	 */
	result = libfwevt_float32_get_string_size(
	          0xffc00000UL,
	          &string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_SIZE( "string_size", string_size, (size_t) 4 );
	FWEVT_TEST_ASSERT_IS_NULL( "error", error );

	/* NaN (0x7fc00001)
	 */
	result = libfwevt_float32_get_string_size(
	          0x7fc00001UL,
	          &string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_SIZE( "string_size", string_size, (size_t) 4 );
	FWEVT_TEST_ASSERT_IS_NULL( "error", error );

	/* Test error cases
	 */
	result = libfwevt_float32_get_string_size(
	          0,
	          NULL,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfwevt_float32_copy_to_utf8_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_float32_copy_to_utf8_string_with_index(
     void )
{
	uint8_t utf8_string[ 32 ];
	uint32_t test_values[ 9 ] = {
		0x00000000UL, /* +0.0 */
		0x3fc00000UL, /* 1.5 */
		0x42f6e979UL, /* 123.456 (positive exponent, rounding) */
		0xbc23d70aUL, /* -0.01 (negative value & negative exponent) */
		0x3a83126fUL, /* 0.001 (small positive, negative exponent) */
		0x00000001UL, /* subnormal */
		0x7f800000UL, /* Inf */
		0xffc00000UL, /* Ind */
		0x7fc00001UL  /* NaN */
	};

	libcerror_error_t *error = NULL;
	size_t utf8_string_index = 0;
	int result               = 0;
	int value_index          = 0;

	/* Test regular cases
	 */
	for( value_index = 0;
	     value_index < 9;
	     value_index++ )
	{
		utf8_string_index = 0;

		result = libfwevt_float32_copy_to_utf8_string_with_index(
		          test_values[ value_index ],
		          utf8_string,
		          32,
		          &utf8_string_index,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Verify special string outputs
	 */
	utf8_string_index = 0;
	result = libfwevt_float32_copy_to_utf8_string_with_index(
	          0x7f800000UL, utf8_string, 32, &utf8_string_index, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "compare", narrow_string_compare( (char *) utf8_string, "Inf", 4 ), 0 );

	utf8_string_index = 0;
	result = libfwevt_float32_copy_to_utf8_string_with_index(
	          0xffc00000UL, utf8_string, 32, &utf8_string_index, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "compare", narrow_string_compare( (char *) utf8_string, "Ind", 4 ), 0 );

	utf8_string_index = 0;
	result = libfwevt_float32_copy_to_utf8_string_with_index(
	          0x7fc00001UL, utf8_string, 32, &utf8_string_index, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_INT( "compare", narrow_string_compare( (char *) utf8_string, "NaN", 4 ), 0 );

	/* Test error cases
	 */
	utf8_string_index = 0;
	result = libfwevt_float32_copy_to_utf8_string_with_index(
	          0, NULL, 32, &utf8_string_index, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "error", error );
	libcerror_error_free( &error );

	result = libfwevt_float32_copy_to_utf8_string_with_index(
	          0, utf8_string, (size_t) SSIZE_MAX + 1, &utf8_string_index, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "error", error );
	libcerror_error_free( &error );

	result = libfwevt_float32_copy_to_utf8_string_with_index(
	          0, utf8_string, 32, NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "error", error );
	libcerror_error_free( &error );

	result = libfwevt_float32_copy_to_utf8_string_with_index(
	          0, utf8_string, 4, &utf8_string_index, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "error", error );
	libcerror_error_free( &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfwevt_float32_copy_to_utf16_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_float32_copy_to_utf16_string_with_index(
     void )
{
	uint16_t utf16_string[ 32 ];
	uint32_t test_values[ 9 ] = {
		0x00000000UL,
		0x3fc00000UL,
		0x42f6e979UL,
		0xbc23d70aUL,
		0x3a83126fUL,
		0x00000001UL,
		0x7f800000UL,
		0xffc00000UL,
		0x7fc00001UL
	};

	libcerror_error_t *error  = NULL;
	size_t utf16_string_index = 0;
	int result                = 0;
	int value_index           = 0;

	/* Test regular cases
	 */
	for( value_index = 0;
	     value_index < 9;
	     value_index++ )
	{
		utf16_string_index = 0;

		result = libfwevt_float32_copy_to_utf16_string_with_index(
		          test_values[ value_index ],
		          utf16_string,
		          32,
		          &utf16_string_index,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	utf16_string_index = 0;
	result = libfwevt_float32_copy_to_utf16_string_with_index(
	          0, NULL, 32, &utf16_string_index, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "error", error );
	libcerror_error_free( &error );

	result = libfwevt_float32_copy_to_utf16_string_with_index(
	          0, utf16_string, (size_t) SSIZE_MAX + 1, &utf16_string_index, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "error", error );
	libcerror_error_free( &error );

	result = libfwevt_float32_copy_to_utf16_string_with_index(
	          0, utf16_string, 32, NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "error", error );
	libcerror_error_free( &error );

	result = libfwevt_float32_copy_to_utf16_string_with_index(
	          0, utf16_string, 4, &utf16_string_index, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "error", error );
	libcerror_error_free( &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfwevt_float64_get_string_size function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_float64_get_string_size(
     void )
{
	libcerror_error_t *error = NULL;
	size_t string_size       = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwevt_float64_get_string_size(
	          0,
	          &string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWEVT_TEST_ASSERT_EQUAL_SIZE(
	 "string_size",
	 string_size,
	 (size_t) 14 );

	FWEVT_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Negative normal double (-1.0)
	 */
	result = libfwevt_float64_get_string_size(
	          0xbff0000000000000ULL,
	          &string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_SIZE( "string_size", string_size, (size_t) 15 );
	FWEVT_TEST_ASSERT_IS_NULL( "error", error );

	/* Positive infinity
	 */
	result = libfwevt_float64_get_string_size(
	          0x7ff0000000000000ULL,
	          &string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_SIZE( "string_size", string_size, (size_t) 4 );
	FWEVT_TEST_ASSERT_IS_NULL( "error", error );

	/* Indeterminate
	 */
	result = libfwevt_float64_get_string_size(
	          0xfff8000000000000ULL,
	          &string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_SIZE( "string_size", string_size, (size_t) 4 );
	FWEVT_TEST_ASSERT_IS_NULL( "error", error );

	/* NaN
	 */
	result = libfwevt_float64_get_string_size(
	          0x7ff8000000000001ULL,
	          &string_size,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, 1 );
	FWEVT_TEST_ASSERT_EQUAL_SIZE( "string_size", string_size, (size_t) 4 );
	FWEVT_TEST_ASSERT_IS_NULL( "error", error );

	/* Test error cases
	 */
	result = libfwevt_float64_get_string_size(
	          0,
	          NULL,
	          &error );

	FWEVT_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWEVT_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfwevt_float64_copy_to_utf8_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_float64_copy_to_utf8_string_with_index(
     void )
{
	uint8_t utf8_string[ 32 ];
	uint64_t test_values[ 9 ] = {
		0x0000000000000000ULL, /* +0.0 */
		0x3ff8000000000000ULL, /* 1.5 */
		0x405edd2f1a9fbe77ULL, /* 123.456 */
		0xbf847ae147ae147bULL, /* -0.01 */
		0x3f50624dd2f1a9fcULL, /* 0.001 */
		0x0000000000000001ULL, /* subnormal */
		0x7ff0000000000000ULL, /* Inf */
		0xfff8000000000000ULL, /* Ind */
		0x7ff8000000000001ULL  /* NaN */
	};

	libcerror_error_t *error = NULL;
	size_t utf8_string_index = 0;
	int result               = 0;
	int value_index          = 0;

	/* Test regular cases
	 */
	for( value_index = 0;
	     value_index < 9;
	     value_index++ )
	{
		utf8_string_index = 0;

		result = libfwevt_float64_copy_to_utf8_string_with_index(
		          test_values[ value_index ],
		          utf8_string,
		          32,
		          &utf8_string_index,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	utf8_string_index = 0;
	result = libfwevt_float64_copy_to_utf8_string_with_index(
	          0, NULL, 32, &utf8_string_index, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "error", error );
	libcerror_error_free( &error );

	result = libfwevt_float64_copy_to_utf8_string_with_index(
	          0, utf8_string, (size_t) SSIZE_MAX + 1, &utf8_string_index, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "error", error );
	libcerror_error_free( &error );

	result = libfwevt_float64_copy_to_utf8_string_with_index(
	          0, utf8_string, 32, NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "error", error );
	libcerror_error_free( &error );

	result = libfwevt_float64_copy_to_utf8_string_with_index(
	          0, utf8_string, 4, &utf8_string_index, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "error", error );
	libcerror_error_free( &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libfwevt_float64_copy_to_utf16_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int fwevt_test_float64_copy_to_utf16_string_with_index(
     void )
{
	uint16_t utf16_string[ 32 ];
	uint64_t test_values[ 9 ] = {
		0x0000000000000000ULL,
		0x3ff8000000000000ULL,
		0x405edd2f1a9fbe77ULL,
		0xbf847ae147ae147bULL,
		0x3f50624dd2f1a9fcULL,
		0x0000000000000001ULL,
		0x7ff0000000000000ULL,
		0xfff8000000000000ULL,
		0x7ff8000000000001ULL
	};

	libcerror_error_t *error  = NULL;
	size_t utf16_string_index = 0;
	int result                = 0;
	int value_index           = 0;

	/* Test regular cases
	 */
	for( value_index = 0;
	     value_index < 9;
	     value_index++ )
	{
		utf16_string_index = 0;

		result = libfwevt_float64_copy_to_utf16_string_with_index(
		          test_values[ value_index ],
		          utf16_string,
		          32,
		          &utf16_string_index,
		          &error );

		FWEVT_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		FWEVT_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	utf16_string_index = 0;
	result = libfwevt_float64_copy_to_utf16_string_with_index(
	          0, NULL, 32, &utf16_string_index, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "error", error );
	libcerror_error_free( &error );

	result = libfwevt_float64_copy_to_utf16_string_with_index(
	          0, utf16_string, (size_t) SSIZE_MAX + 1, &utf16_string_index, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "error", error );
	libcerror_error_free( &error );

	result = libfwevt_float64_copy_to_utf16_string_with_index(
	          0, utf16_string, 32, NULL, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "error", error );
	libcerror_error_free( &error );

	result = libfwevt_float64_copy_to_utf16_string_with_index(
	          0, utf16_string, 4, &utf16_string_index, &error );
	FWEVT_TEST_ASSERT_EQUAL_INT( "result", result, -1 );
	FWEVT_TEST_ASSERT_IS_NOT_NULL( "error", error );
	libcerror_error_free( &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc FWEVT_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] FWEVT_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc FWEVT_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] FWEVT_TEST_ATTRIBUTE_UNUSED )
#endif
{
	FWEVT_TEST_UNREFERENCED_PARAMETER( argc )
	FWEVT_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

	FWEVT_TEST_RUN(
	 "libfwevt_float32_get_string_size",
	 fwevt_test_float32_get_string_size );

	FWEVT_TEST_RUN(
	 "libfwevt_float32_copy_to_utf8_string_with_index",
	 fwevt_test_float32_copy_to_utf8_string_with_index );

	FWEVT_TEST_RUN(
	 "libfwevt_float32_copy_to_utf16_string_with_index",
	 fwevt_test_float32_copy_to_utf16_string_with_index );

	FWEVT_TEST_RUN(
	 "libfwevt_float64_get_string_size",
	 fwevt_test_float64_get_string_size );

	FWEVT_TEST_RUN(
	 "libfwevt_float64_copy_to_utf8_string_with_index",
	 fwevt_test_float64_copy_to_utf8_string_with_index );

	FWEVT_TEST_RUN(
	 "libfwevt_float64_copy_to_utf16_string_with_index",
	 fwevt_test_float64_copy_to_utf16_string_with_index );

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBFWEVT_DLL_IMPORT ) */
}

