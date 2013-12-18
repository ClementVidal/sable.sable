#ifndef _DUNE_CORE_STRING_PRIMITIVES_
#define _DUNE_CORE_STRING_PRIMITIVES_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Setup.h>
#include <stdarg.h>

/** 
\file Sable\Core\String\Primitives.h
Basic string primitives
*/

namespace Sable
{


// Char functions

/**
\ingroup CoreString
Return TRUE is c is any kind of white space ( tab, space, new line, carriage return )
*/
Bool        CharIsWhiteSpace( Char c );

// Char array functions ( Not null terminated string )

/**
\ingroup CoreString
Compare two char array
*/
Int32       CharArrayCompare( const Char* a, UInt32 la, const Char* b, UInt32 lb );

/**
\ingroup CoreString
Generate an hash code for a given char array
\deprecated Should be more efficient
*/
HashValue  CharArrayGetHashCode( const Char* s, UInt32 size );

/**
\ingroup CoreString
Convert a char array to a Float32
*/
Float32     CharArrayToFloat32( const Char* s, UInt32 len );

/**
\ingroup CoreString
Return the index of caract in buffer by doing a search starting from the end
*/
Int32      CharArrayReverseFind( const Char* buffer, UInt32 len, Char caract );

// String functions

/**
\ingroup CoreString
Concatenate string b to string a
*/
Void        StringAppend( String a, String b, Char* out, UInt32 size );

/**
\ingroup CoreString
Output formatted text to inBuffer using variables arguments
*/
Int32        StringSetFormattedText( Char* inBuffer, UInt32 size, String format, ... );

/**
\ingroup CoreString
Output formatted text to inBuffer using va_arg
*/
Int32        StringSetFormattedTextVaList( Char* inBuffer, UInt32 size, String format, va_list& args  );

/**
\ingroup CoreString
Copy a sub part of a string
*/
Void        StringCopySubPart( String in, UInt32 offset, UInt32 count, Char* out, UInt32 len );

/**
\ingroup CoreString
Copy a string
*/
Void        StringCopy( String src, Char* dst, UInt32 size );

/**
\ingroup CoreString
Compare two string
*/
Int32       StringCompare( String a, String b );

/**
\ingroup CoreString
Return the length of a string ( without null terminated char )
*/
UInt32      StringGetLength( String a );

/**
\ingroup CoreString
Generate an hash code for a given char array
\deprecated Should be more efficient
*/
HashValue  StringGetHashCode( String s  );

/**
\ingroup CoreString
Convert a UInt32 to a string
*/
String      StringFromUInt32( UInt32 f, Char* s, UInt32 length );

/**
\ingroup CoreString
Convert a Float32 to a string
*/
String      StringFromFloat32( Float32 f, Char* s, UInt32 length );

/**
\ingroup CoreString
Convert a string to a Float32
*/
Float32     StringToFloat32( String s );

/**
\ingroup CoreString
Convert a string to a Int32
*/
Int32       StringToInt32( String s );

/**
\ingroup CoreString
Return the index of caract in buffer by doing a search starting from the end
*/
Int32      StringReverseFind( String buffer, Char caract );


#ifdef SETUP_UNICODE

// Wide Char functions

/**
\ingroup CoreString
Return TRUE is c is any kind of white space ( tab, space, new line, carriage return )
*/
Bool        CharIsWhiteSpace( WChar c );

// Wide Char Array functions

/**
\ingroup CoreString
Return an hash code that identify a given string
\param s The string
\param size The character count in that string
*/
HashValue CharArrayGetHashCode( const WChar* ws, UInt32 size );

/**
\ingroup CoreString
Return the index of caract in buffer by doing a search starting from the end
*/
Int32      CharArrayReverseFind( const WChar* buffer, UInt32 len, WChar caract );

/**
\ingroup CoreString
Compare two char array
*/
Int32       CharArrayCompare( const WChar* a, UInt32 la, const WChar* b, UInt32 lb );

/**
\ingroup CoreString
Convert a char array to a FLoat32
*/
Float32     CharArrayToFloat32( const WChar* s, UInt32 len );

// Wide String functions

/**
\ingroup CoreString
Generate an hash code for a given char array
*/
HashValue  StringGetHashCode( WString s );

/**
\ingroup CoreString
Convert a Float32 to a String
*/
WString     StringFromFloat32( Float32 f, WChar* s, UInt32 length );

/**
\ingroup CoreString
Convert a UInt32 to a String
*/
WString     StringFromUInt32( UInt32 f, WChar* s, UInt32 length );

/**
\ingroup CoreString
Copy two string
*/
Void        StringCopy( WString src, WChar* dst, UInt32 size );

/**
\ingroup CoreString
Convert a string to a string with only lower characters
*/
Void        StringToLower( String src, Char* dst, UInt32 size );

/**
\ingroup CoreString
Convert a string to uppercase
*/
Void		StringToUpper( String src, Char* dst, UInt32 size );

/**
\ingroup CoreString
Return the index of caract in buffer by doing a search starting from the end
*/
Int32      StringReverseFind( WString buffer, WChar caract );

/**
\ingroup CoreString
Convert a Float32 to a string
*/
Float32     StringToFloat32( WString s );

/**
\ingroup CoreString
Convert a Int32 to a string
*/
Int32     StringToInt32( WString s );

/**
\ingroup CoreString
Return the length of a string
*/
UInt32      StringGetLength( WString a );

/**
\ingroup CoreString
Compare two string
*/
Int32       StringCompare( WString a, WString b );

/**
\ingroup CoreString
Output formatted text to a string using variable arguments
*/
Int32        StringSetFormattedText( WChar* inBuffer, UInt32 size, WString format, ... );

/**
\ingroup CoreString
Output formatted text to a string using va_list
*/
Int32        StringSetFormattedTextVaList( WChar* inBuffer, UInt32 size, WString format, va_list& args );

/**
\ingroup CoreString
Concatenate two string
*/
Void        StringAppend( WString a, WString b, WChar* out, UInt32 size );

#endif

// Conversion function

/**
\ingroup CoreString
Convert a WideString to a String
*/
String      WStringToString( WString w, Char* s, UInt32 count );

/**
\ingroup CoreString
Convert a String to a WideString
*/
WString     StringToWString( String s, WChar* w, UInt32 count );

}

#endif

