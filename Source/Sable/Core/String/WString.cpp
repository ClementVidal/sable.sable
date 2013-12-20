#include <Sable/Core/String/WString.h>

#include <Sable/Core/Persistent/Archive.h>
#include <Sable/Core/String/Primitives.h>

#include <stdarg.h>

using namespace Sable;

CWString::CWString( const CWString& other )
{
    WString text = other.GetBuffer();

    if( text )
    {
        m_Length = (UInt32) other.GetLength();
        m_Buffer = Allocate( m_Length + 1 );

        StringCopy( text, m_Buffer, m_Length + 1 );
    }
    else
    {
        m_Buffer = NULL;
        m_Length = 0;
    }
}

CWString::CWString( WString text )
{
    if( text )
    {
        m_Length = (UInt32) ComputeLenght( text ) ;
        m_Buffer = Allocate( m_Length + 1 );
        StringCopy( text, m_Buffer, m_Length + 1 );
    }
    else
    {
        m_Buffer = NULL;
        m_Length = 0;
    }
}


CWString& CWString::operator=( const CWString& other )
{
    WString text = other.GetBuffer();

    Free( m_Buffer );

    if( text )
    {
        m_Length = (UInt32) other.GetLength() ;
        m_Buffer = Allocate( m_Length + 1 );
        StringCopy( text, m_Buffer, m_Length + 1 );
    }
    else
    {
        m_Buffer = NULL;
        m_Length = 0;
    }

    return *this;
}

CWString::~CWString(  )
{
    if( m_Buffer )
        Free( m_Buffer );
}

Bool CWString::ConvertToInteger( Int32& value )
{
/*    if(EOF == sscanf( m_Buffer, "%d", &value) )
    {
        return FALSE;
    }
*/

    DebugError("");
    return TRUE;
}

Void CWString::SetEmpty()
{
    Free( m_Buffer );
    m_Buffer = NULL;
    m_Length = 0;
}

Void CWString::WriteFormattedText( WString format, ... )
{
/*
    va_list args;
    va_start( args, format );

	m_Length = vsnprintf( NULL, 0, format, args );
    Free( m_Buffer );
    m_Buffer = Allocate( m_Length + 1);
    vsprintf( (WString) m_Buffer, format, args ); 

    va_end( args );
*/
    DebugError("");
}

Void CWString::Append( const CWString& other )
{
    WChar* newbuffer;
    UInt32 newlengh;

    newlengh = m_Length+ other.GetLength();

    newbuffer = Allocate( newlengh + 1 );

    StringCopy( m_Buffer, newbuffer, m_Length);
    StringCopy( other.GetBuffer(), newbuffer+m_Length, other.GetLength());

    newbuffer[newlengh] = 0;

    Free( m_Buffer );

    m_Buffer = newbuffer;
    m_Length= newlengh;
}

Void    CWString::Append( UInt32 other )
{
    CWString tmp;

    tmp.IntToString( other ,  10);

    Append( tmp );
}

Void CWString::SetFrom( WString buffer, UInt32 length )
{
    Free( m_Buffer );

    m_Buffer = Allocate( length + 1 );
    StringCopy( buffer, m_Buffer, length);
    m_Buffer[length] = 0;
    m_Length = length;
}

Void CWString::AllocateBuffer( UInt32 size )
{
    Free( m_Buffer );

    m_Buffer = Allocate( size );

    MemoryFill( m_Buffer, 0, size );

    m_Length = size;
}

Void    CWString::Append( Int32 other )
{
    CWString tmp;

    tmp.IntToString( other ,  10);

    Append( tmp );
}

CWString CWString::operator+( const CWString& other ) const
{
    CWString str( m_Buffer );
    str.Append( other );

    return str;
}

CWString CWString::operator+( WString text ) const
{
    CWString str( m_Buffer );
    str.Append( CWString( text ) );

    return str;
}

CWString CWString::operator+( const Void* text ) const
{
    WChar  buffer[16];
/*    sprintf( buffer, "%x", (UInt32)text );
    CWString str( m_Buffer );
    str.Append( buffer );
*/

    DebugError("");

    return buffer;
}

CWString CWString::operator+( const UInt32 other ) const
{
    CWString str( m_Buffer );

    str.Append( other );
    return str;
}

CWString CWString::operator+( const Int32 other ) const
{
    CWString str( m_Buffer );

    str.Append( other );
    return str;
}

Int32	CWString::Compare( WString other, UInt32 otherLenght ) const
{
    return CharArrayCompare( m_Buffer, m_Length, other, otherLenght ) ;
}


Int32	CWString::Compare( WString other) const
{
    UInt32 ol = ComputeLenght( other );

    return CharArrayCompare( m_Buffer, m_Length, other, ol ) ;
}

Int32	CWString::Compare( const CWString& other) const
{
    return Compare( other.GetBuffer(), other.GetLength() );
}

CWString& CWString::operator=( WString other )
{
    WString text = other;
    UInt32 textlenght;

    Free( m_Buffer );

    if( other )
    {
        textlenght = (UInt32) ComputeLenght( text ) + 1;
        m_Buffer = Allocate( textlenght ) ;
        StringCopy( text, m_Buffer, textlenght);

        m_Length = textlenght - 1;
    }
    else
    {
        m_Length = 0;
        m_Buffer  =NULL;
    }

    return *this;
}

UInt32 CWString::Find( WChar caract)
{
    for( Index index = 0; index < GetLength(); index++)
    {
        if( m_Buffer[index] == caract )
        {
            return index;
        }
    }

    return UINT32_MAX_VAL;
}

UInt32 CWString::ReverseFind( WChar caract )
{
    return CharArrayReverseFind( m_Buffer, m_Length, caract );
}

CWString	CWString::SubString( UInt32 offset, Int32 size ) const
{
    WChar * tempBuffer;
    UInt32  tempSize;
    CWString returnString;

    tempSize = size;
    if( size == -1 ) {
        tempSize = GetLength() - offset;
    } else if( size == 0 ) {
        return WT("");
    }

    tempBuffer = Allocate( tempSize + 1 );

    StringCopy( &m_Buffer[offset], tempBuffer, tempSize );
    tempBuffer[ tempSize ] = 0;

    returnString = tempBuffer;

    Free( tempBuffer );

    return returnString;
}

Float32 CWString::StringToFloat( ) const
{
    return StringToFloat32( GetBuffer()  );
}

Void CWString::Cut( UInt32 offset )
{
    m_Buffer[offset] = 0;

    *this = CWString(m_Buffer);
}


UInt32 CWString::ComputeLenght( WString buffer) const
{
    return StringGetLength( buffer );
}

Void    CWString::IntToString( Int32 value , UInt8 base  )
{
    WChar buffer[16];
    WChar tmpchar;
    Int32 quotient = value;
    Int32 tmp;
    Int32 nbcaract =0;
    // check that the base if valid
    if (base < 2 || base > 16) 
    { 
        return ; 
    }

    do 
    {
        tmp = quotient % base;
        buffer[nbcaract++] = "0123456789abcdef"[ tmp<0?(tmp-(tmp*2)):tmp ];
        quotient /= base;
    } 
    while ( quotient );

    // Only apply negative sign for base 10
    if ( value < 0 && base == 10) 
        buffer[nbcaract++] = '-';

     for( Int32 i=0, j=nbcaract-1; i<nbcaract/2; i++,j--)
     {
        tmpchar = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = tmpchar;
     }

     buffer[nbcaract] = 0;

    *this = buffer;
}

Void    CWString::IntToString( UInt32 value , UInt8 base  )
{
    WChar buffer[16];
    WChar tmpchar;
    UInt32 quotient = value;
    UInt32 tmp;
    UInt32 nbcaract =0;
    // check that the base if valid
    if (base < 2 || base > 16) 
    { 
        m_Buffer = NULL;
        m_Length = 0;
        return ; 
    }

    do 
    {
        tmp = quotient % base;
        buffer[nbcaract++] = "0123456789abcdef"[ tmp ];
        quotient /= base;
    } 
    while ( quotient );

    for( UInt32 i=0, j=nbcaract-1; i<nbcaract/2; i++,j--)
    {
        tmpchar = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = tmpchar;
    }

    buffer[nbcaract] = 0;

    *this = buffer;
}

Bool CWString::BeginBy( WString word ) const 
{
    Index index;
    UInt32 wordLength = StringGetLength( word );

    if( wordLength > GetLength() )
        return FALSE;

    for( index = 0; index < wordLength; index++ )
    {
        if( m_Buffer[ index ] != word[ index ] )
            return FALSE;
    }
    return TRUE;
}

WChar*	CWString::Allocate( UInt32 size ) const
{
    return (WChar*) MemoryAllocate( CoreManager.GetMemoryManager().GetBuddyHeap(),  size );
}

Void CWString::Free( WChar* ptr ) const
{
    MemoryFree( CoreManager.GetMemoryManager().GetBuddyHeap(), ptr );
}
