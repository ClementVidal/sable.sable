#include <Sable\Core\String\String.h>

#include <Sable\Core\String\String.h>

#include <Sable\Core\Persistent\Archive.h>

#include <stdarg.h>

using namespace Sable;

CString::CString( const CString& other )
{
    String text = other.GetBuffer();

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

CString::CString( WString text )
{
	if( text )
	{
		m_Length = (UInt32) StringGetLength( text ) ;
		m_Buffer = Allocate( m_Length + 1 );
		WStringToString( text, m_Buffer, m_Length + 1);
	}
	else
	{
		m_Buffer = NULL;
		m_Length = 0;
	}
}

CString::CString( String text )
{
    if( text )
    {
        m_Length = (UInt32) StringGetLength( text ) ;
        m_Buffer = Allocate( m_Length + 1 );
        StringCopy( text, m_Buffer, m_Length + 1 );
    }
    else
    {
        m_Buffer = NULL;
        m_Length = 0;
    }
}


CString& CString::operator=( const CString& other )
{
    String text = other.GetBuffer();

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

CString::~CString(  )
{
    if( m_Buffer )
        Free( m_Buffer );
}

Bool CString::ConvertToInteger( Int32& value )
{
    if(EOF == sscanf( m_Buffer, "%d", &value) )
    {
        return FALSE;
    }

    return TRUE;
}

Void CString::SetEmpty()
{
    Free( m_Buffer );
    m_Buffer = NULL;
    m_Length = 0;
}

Void CString::ToUpper()
{
	StringToUpper( m_Buffer, m_Buffer, m_Length );
}

Void CString::WriteFormattedText( String format, ... )
{
    va_list args;
    va_start( args, format );

	m_Length = vsnprintf( NULL, 0, format, args );
    Free( m_Buffer );
    m_Buffer = Allocate( m_Length + 1);
    vsprintf( m_Buffer, format, args ); 

    va_end( args );
}

Void CString::Append( const CString& other )
{
    Char* newbuffer;
    UInt32 newlengh;

    newlengh = m_Length+ other.GetLength();

    newbuffer = Allocate( newlengh + 1 );

    StringCopy( m_Buffer, newbuffer, m_Length + 1);
    StringCopy( other.GetBuffer(), newbuffer+m_Length, other.GetLength() + 1);

    newbuffer[newlengh] = 0;

    Free( m_Buffer );

    m_Buffer = newbuffer;
    m_Length= newlengh;
}

Void    CString::Append( UInt32 other )
{
    CString tmp;

    tmp.IntToString( other ,  10);

    Append( tmp );
}

Void CString::SetFrom( String buffer, UInt32 length )
{
    Free( m_Buffer );

    m_Buffer = Allocate( length + 1 );
    StringCopy( buffer, m_Buffer, length);
    m_Buffer[length] = 0;
    m_Length = length;
}

Void CString::AllocateBuffer( UInt32 size )
{
    Free( m_Buffer );

    m_Buffer = Allocate( size );

    MemoryFill( m_Buffer, 0, size );
}

Void    CString::Append( Int32 other )
{
    CString tmp;

    tmp.IntToString( other ,  10);

    Append( tmp );
}

CString CString::operator+( const CString& other ) const
{
    CString str( m_Buffer );
    str.Append( other );

    return str;
}

CString CString::operator+( String text ) const
{
    CString str( m_Buffer );
    str.Append( CString( text ) );

    return str;
}

CString CString::operator+( const Void* text ) const
{
    Char
        buffer[16];
    sprintf( buffer, "%x", (UInt32)text );
    CString str( m_Buffer );
    str.Append( buffer );

    return str;
}

CString CString::operator+( const UInt32 other ) const
{
    CString str( m_Buffer );

    str.Append( other );
    return str;
}

CString CString::operator+( const Int32 other ) const
{
    CString str( m_Buffer );

    str.Append( other );
    return str;
}

Int32	CString::Compare( String other) const
{
    return StringCompare( m_Buffer, other) ;
}

Int32	CString::Compare( const CString& other) const
{
    return StringCompare( m_Buffer, other.GetBuffer() );
}

CString& CString::operator=( String other )
{
    String text = other;
    UInt32 textlenght;

    Free( m_Buffer );

    if( other )
    {
        textlenght = (UInt32) StringGetLength( text ) + 1;
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

UInt32 CString::Find( Char caract)
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

UInt32 CString::ReverseFind( Char caract )
{
    return CharArrayReverseFind( m_Buffer, m_Length, caract );
}

CString	CString::SubString( UInt32 offset, Int32 size ) const
{
    Char
        * tempBuffer;
    UInt32
        tempSize;
    CString
        returnString;

    tempSize = size;
    if( size == -1 ) {
        tempSize = GetLength() - offset;
    } else if( size == 0 ) {
        return "";
    }

    tempBuffer = Allocate( tempSize + 1 );

    StringCopy( &m_Buffer[offset], tempBuffer, tempSize );
    tempBuffer[ tempSize ] = 0;

    returnString = tempBuffer;

    Free( tempBuffer );

    return returnString;
}

Float32 CString::StringToFloat( ) const
{
    return StringToFloat32( GetBuffer()  );
}

Void CString::Cut( UInt32 offset )
{
    m_Buffer[offset] = 0;

    *this = CString(m_Buffer);
}


Void    CString::IntToString( Int32 value , UInt8 base  )
{
    Char buffer[16];
    Char tmpchar;
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

Void    CString::IntToString( UInt32 value , UInt8 base  )
{
    Char buffer[16];
    Char tmpchar;
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
        buffer[nbcaract++] = "0123456789abcdef"[ tmp<0?(tmp-(tmp*2)):tmp ];
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

HashValue CString::GetHashCode() const
{
  return CharArrayGetHashCode( m_Buffer, m_Length);
}

Bool CString::BeginBy( String word ) const 
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

Char*	CString::Allocate( UInt32 size ) const
{
    return (Char*) MemoryAllocate( CoreManager.GetMemoryManager().GetBuddyHeap(),  size );
}

Void CString::Free( Char* ptr ) const
{
    MemoryFree( CoreManager.GetMemoryManager().GetBuddyHeap(), ptr );
}