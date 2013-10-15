
template< UInt32 Count >
Bool CStaticString<Count>::operator<( const CStaticString& other ) const
{
    return  ( Compare(other) < 0 );
}

template< UInt32 Count >
Bool CStaticString<Count>::operator<( String other ) const
{
    return  ( Compare(other) < 0 );
}

template< UInt32 Count >
Bool CStaticString<Count>::operator==( const CStaticString& other ) const
{
    if( Compare( other ) == 0)
        return TRUE;
    return FALSE;
}

template< UInt32 Count >
Bool CStaticString<Count>::operator==( String other ) const
{
    if( Compare( other ) == 0)
        return TRUE;
    return FALSE;
}

template< UInt32 Count >
Bool CStaticString<Count>::operator!=( const CStaticString& other ) const
{
    if( Compare( other ) != 0 )
        return true;

    return false;
}

template< UInt32 Count >
Bool CStaticString<Count>::operator!=( String other ) const
{
    if( Compare( other ) != 0)
        return TRUE;
    return FALSE;
}

template< UInt32 Count >
Int32 CStaticString<Count>::Compare( String other) const
{
    return StringCompare( m_Buffer, other );
}

template< UInt32 Count >
Int32 CStaticString<Count>::Compare( const CStaticString& other) const
{
    return Sable::StringCompare( m_Buffer, other.m_Buffer );
}

template< UInt32 Count >
CStaticString<Count>::CStaticString()
{
    m_Buffer[0] = '\0';
    m_Length = 0;
}

template< UInt32 Count >
CStaticString<Count>::operator String ()
{
    return m_Buffer;
}

template< UInt32 Count >
CStaticString<Count>::operator String () const
{
    return m_Buffer;
}

template< UInt32 Count >
String CStaticString<Count>::GetBuffer() const 
{
    return m_Buffer;
}

template< UInt32 Count >
UInt32 CStaticString<Count>::GetLength() const 
{
    return m_Length;
}

template< UInt32 Count >
CStaticString<Count>::CStaticString( const CStaticString& other )
{
    (*this) = (String) other.m_Buffer;
}

template< UInt32 Count >
CStaticString<Count>::CStaticString( String text )
{
    (*this) = (String) text;
}

template< UInt32 Count >
CStaticString<Count>::CStaticString( WString text )
{
    Char tmp[Count];
    WStringToString( text, tmp, Count );

    (*this) = (String) tmp;
}

template< UInt32 Count >
CStaticString<Count>::~CStaticString(  )
{
    m_Buffer[0] = '\0';
    m_Length = 0;
}

template< UInt32 Count >
Void CStaticString<Count>::WriteFormattedText( String format, ... )
{
    va_list args;
    va_start( args, format );

	StringSetFormattedTextVaList( m_Buffer, GetCapacity(), format, args );

    va_end( args );
}

template< UInt32 Count >
UInt32 CStaticString<Count>::GetCapacity( ) const
{
    return Count;
}

template< UInt32 Count >
CStaticString<Count>& CStaticString<Count>::operator=( const CStaticString& other )
{
    (*this) = (String) other.GetBuffer();

    return *this;
}

template< UInt32 Count >
CStaticString<Count>& CStaticString<Count>::operator=( String other )
{
    String text = other;
    UInt32 textlenght;

    if( other )
    {
        textlenght = (UInt32) Sable::StringGetLength( text ) + 1;

        DebugAssert( textlenght <= GetCapacity() );
        Sable::StringCopy( text, m_Buffer, Count);

        m_Length = textlenght - 1;
    }
    else
    {
        m_Length = 0;
        m_Buffer[0] = '\0';
    }

    return *this;
}

template< UInt32 Count >
Bool CStaticString<Count>::IsEmpty() const
{
	return ( m_Length == 0 );
}

template< UInt32 Count >
Void CStaticString<Count>::SetEmpty()
{
	m_Length = 0;
	m_Buffer[0] = 0;
}
