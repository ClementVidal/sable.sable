#include <Sable\Core\String\Primitives.h>

using namespace Sable;

/*
Char functions
*/
Bool Sable::CharIsWhiteSpace( Char c )
{
	return (c==' ' || c=='\t' || c=='\n' || c=='\r');
}

/**
Char array functions ( Not null terminated string )
*/
Int32 Sable::CharArrayCompare( const Char* a, UInt32 la, const Char* b, UInt32 lb )
{
    UInt32 index;
    Int32 result;
    const Char* ta = a;
    const Char* tb = b;

    result = 0;

    if( !b || !a )
        return 1;

    for ( index = 0; !result ; index++ )
    {
        result = *ta - *tb;
        if( !(*ta) || !(*tb) )
            break;

        ++ta;
        ++tb;
    }

    return result;
}

/**
Return an hash code that identify a given string
*/
HashValue Sable::CharArrayGetHashCode( const Char* s, UInt32 size )
{
	CCrc32 crc;

	crc.Compute( (Byte*) s, size );

	return crc.Get();
}


Float32 Sable::CharArrayToFloat32( const Char* s, UInt32 size )
{
    Char buffer[128];
    DebugAssert( size<128 );

    MemoryCopy( (Void*) s, buffer, size );
    Float32 f;
    buffer[size] = 0;
    f = (Float32) atof( (Char*)buffer );

    return f;
}

/**
Search for a given character in a Char buffer.
\param buffer input char buffer
\param len len in Char of the input buffer
\param caract searched character
\return the index of the first matching char or -1 if no char was found
*/
Int32 Sable::CharArrayReverseFind( const Char* buffer, UInt32 len, Char caract )
{
    UInt32 findPosition = len;

    for( Int32 index = findPosition; index >= 0; index--)
    {
        if( buffer[index] == caract )
        {
            return index;
        }
    }

    return -1;
}

/**
String functions
*/

Void Sable::StringAppend( String a, String b, Char* out, UInt32 size )
{
    strcpy( out, a );
    strcat( out, b );
}


UInt32 Sable::StringGetLength( String a )
{
    UInt32 
       lenght;

    if( a == NULL )
        return  0;

#if defined( SETUP_IMPLTYPE_MSW )

    __asm
       {
           mov edi, a
           mov ecx, 0xffff
           mov al, 0
           cld
           repne scasb
           jne notfound
           sub  cx, 0xffff
           neg cx
           dec cx
           mov eax, 1
           mov lenght, ecx
       notfound:

       }
#else

    lenght = (UInt32) strlen( a );

#endif

	return lenght;

}

Int32 Sable::StringSetFormattedText( Char* inBuffer, UInt32 size, String format, ... )
{
	Int32 n;
    va_list args;
    va_start( args, format );

    n = StringSetFormattedTextVaList( inBuffer, size, format, args ); 

    va_end( args );

	return n;
}

Int32 Sable::StringSetFormattedTextVaList( Char* inBuffer, UInt32 size, String format, va_list& args )
{
    return vsnprintf( inBuffer, size, format, args ); 
}


Void Sable::StringCopySubPart( String in, UInt32 offset, UInt32 count, Char* out, UInt32 len )
{
    DebugAssert( offset + count <= StringGetLength( in ) );
    DebugAssert( count < len );

    Char* start = ( (Char*)in +  offset );

    MemoryCopy( start, out, count );

    out[count] = 0;
}

/**
Compare two string.( behave like strcmp )
\return 0 if a == b 
*/
Int32 Sable::StringCompare( String a, String b )
{
    return CharArrayCompare( a, StringGetLength( a ), b, StringGetLength( b ) );
}

Void Sable::StringCopy( String src, Char* dst, UInt32 size )
{
    if( src != NULL )
    	strncpy( dst, src, size );
    else
        dst[0] = '\0';
}

Void Sable::StringToLower( String src, Char* dst, UInt32 size )
{
	UInt32 l = StringGetLength( src );
	UInt32 i;
	if( l >= size )
		return;

	if( src != dst )
		StringCopy(src, dst, size );

	for(i=0;i<l;i++)
	{
		dst[i] = tolower( src[i] );
	}
}

Void Sable::StringToUpper( String src, Char* dst, UInt32 size )
{
	UInt32 l = StringGetLength( src );
	UInt32 i;
	if( l >= size )
		return;

	if( src != dst )
		StringCopy(src, dst, size );

	for(i=0;i<l;i++)
	{
		dst[i] = toupper( src[i] );
	}
}

Int32 Sable::StringReverseFind( String buffer, Char caract )
{
    return CharArrayReverseFind( buffer, StringGetLength( buffer ), caract );
}

HashValue Sable::StringGetHashCode( String s  )
{
    return CharArrayGetHashCode( s, StringGetLength( s ) );
}

Int32 Sable::StringToInt32( String s )
{
    Int32 i;
    i = atoi( s );

    return i;
}

Float32 Sable::StringToFloat32( String s )
{
    Float32  f;
    f = (Float32) atof( s );
    return f;
}

String Sable::StringFromUInt32( UInt32 f, Char* s, UInt32 length )
{
    // should be enhanced by using buffer size control
    sprintf(s, "%d", f);
    return s;
}

String Sable::StringFromFloat32( Float32 f, Char* s, UInt32 length )
{
    // should be enhanced by using buffer size control
    sprintf(s, "%f", f);
    return s;
}



#ifdef SETUP_UNICODE

/**
Wide Char Array functions
*/
HashValue Sable::CharArrayGetHashCode( const WChar* ws, UInt32 size )
{
    HashValue hash = 5381;

    const Char* s = (Char*) ws;

    for (UInt32 i = 0; i < size*sizeof( WChar ); i++) 
    {
        hash = hash * 33 + s[i];
    }

    return hash;
}

Bool Sable::CharIsWhiteSpace( WChar c )
{
	return (c==WT(' ') || c== WT('\t') || c== WT('\n') || c==WT('\r') );
}

Float32 Sable::CharArrayToFloat32( const WChar* s, UInt32 size )
{
	WChar* stopString;
    return (Float32)wcstod( s, &stopString );
}

Int32 Sable::CharArrayCompare( const WChar* a, UInt32 la, const WChar* b, UInt32 lb )
{
    return wcscmp( a, b );
}

Int32 Sable::CharArrayReverseFind( const WChar* buffer, UInt32 len, WChar caract )
{
    DebugError("");
    return 0;//wcsrchr( buffer, caract );
}

/**
Wide String functions
*/

HashValue Sable::StringGetHashCode( WString s  )
{
    return CharArrayGetHashCode( s, StringGetLength( s ) );
}

UInt32 Sable::StringGetLength( WString a )
{
    return (UInt32)wcslen( a );
}

Int32 Sable::StringCompare( WString a, WString b )
{
    return wcscmp( a, b );
}

Int32 Sable::StringReverseFind( WString buffer, WChar caract )
{
    DebugError("");
    return 0;//wcsrchr( buffer, caract );
}

/**
Copy NULL terminated String pointed by src to dst which is of length size.

\param src Source buffer: null terminated string
\param dst Destination buffer
\param size Length of dst in element
*/
Void Sable::StringCopy( WString src, WChar* dst, UInt32 size )
{
    if( src != NULL )
    	wcscpy( dst, src );
    else
        dst[0] = WT('\0');
}

Int32 Sable::StringSetFormattedText( WChar* inBuffer, UInt32 size, WString format, ... )
{
	Int32 n;
    va_list args;
    va_start( args, format );

    n = StringSetFormattedTextVaList( inBuffer, size, format, args ); 

    va_end( args );

	return n;

}

Int32 Sable::StringSetFormattedTextVaList( WChar* inBuffer, UInt32 size, WString format, va_list& args )
{
    return vswprintf( inBuffer, size, format, args );
}

Void Sable::StringAppend( WString a, WString b, WChar* out, UInt32 size )
{
    StringSetFormattedText( out, size, WT("%s%s"), a, b );
}

Int32 Sable::StringToInt32( WString s )
{
	WChar* end;
	return (Int32)wcstol( s, &end, 10 );
}

Float32 Sable::StringToFloat32( WString s )
{
#if defined( SETUP_IMPLTYPE_MSW )
    return (Float32)_wtof( s );
#else
	WChar* end;
    return (Float32)wcstod( s, &end );
#endif

}

WString Sable::StringFromUInt32( UInt32 f, WChar* s, UInt32 length )
{
    // should be enhanced by using buffer size control
	swprintf(s, length, WT("%d"), f);
    return s;
}

WString Sable::StringFromFloat32( Float32 f, WChar* s, UInt32 length )
{
    // should be enhanced by using buffer size control
	swprintf(s, length, WT("%f"), f);
    return s;
}

/**
Conversion functions
*/
#ifndef SETUP_UNICODE

String Sable::WStringToString( WString w, String s, UInt32 count )
{
    StringCopy( w, s, count );
    return s;
}

WString Sable::StringToWString( String s, WString w, UInt32 count )
{
    StringCopy( s, w, count );
    return w;
}

#else


String Sable::WStringToString( WString w, Char* s, UInt32 count )
{
    if( w == NULL )
        return  0;

    size_t size;
#if defined( SETUP_IMPLTYPE_MSW )
    wcstombs_s( &size, s, count, w, _TRUNCATE );
#else
    wcstombs( s, w, count );
#endif
    return s;
}

WString Sable::StringToWString( String s, WChar* w, UInt32 count )
{
    if( s == NULL )
        return  0;

    size_t size;
#if defined( SETUP_IMPLTYPE_MSW )
    mbstowcs_s( &size, w, count, s, _TRUNCATE );
#else
    mbstowcs( w, s, count );
#endif
    return w;
}

#endif

#endif
