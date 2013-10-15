#ifndef _CORE_COMMON_STRING_
#define _CORE_COMMON_STRING_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Debug\Primitives.h>
#include <Sable\Core\Memory\Primitives.h>

namespace Sable
{

class CPersistentArchive;

/** 
\ingroup CoreString
String. 
*/
class CString 
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CString();
    CString( const CString& other );
    CString( String text );
	CString( WString text );
    virtual ~CString();
    //@}

    /** @name Operator - Cast*/
    //@{
    operator String();
    operator String() const ;
    //@}

    /** @name Operator - Copy*/
    //@{
    CString&    operator=( const CString& other );
    CString&    operator=( String other );
    //@}

    /** @name Operator - Comparator*/
    //@{
    Char       operator[]( const UInt32 i) const ;
    Bool        operator<( String other ) const;
    Bool        operator<( const CString& other ) const;
    Bool        operator==( const CString& other ) const;
    Bool        operator==( String other ) const;
    Bool        operator!=( String other ) const;
    Bool        operator!=( const CString& other ) const;
    //@}

    /** @name Operator - Concatenation*/
    //@{
    CString     operator+( const CString& other ) const;
    CString     operator+( const Void* other ) const;
    CString     operator+( String text ) const;
    CString     operator+( const UInt32 other ) const;
    CString     operator+( const Int32 other ) const;
    //@}

    /** @name Accessors*/
    //@{
    String		GetBuffer() const ;
    UInt32      GetLength() const ;
    //@}

    /** @name Manipulator*/
    //@{
    Void        WriteFormattedText( String format, ... );
    UInt32      ReverseFind( Char caract );
    UInt32      Find( Char caract );
    CString     SubString( UInt32 offset, Int32 size=-1 ) const;
    Void        Cut( UInt32 offset );
    Int32       Compare( String other) const ;
    Int32       Compare( const CString& other) const ;
    Void        Append( const CString& other );
    Void        Append( UInt32 other );
    Void        Append( Int32 other );
    Bool        BeginBy( String word ) const ;
    Void        IntToString( Int32 value , UInt8 base = 16 );
    Void        IntToString( UInt32 value , UInt8 base = 16 );
    Float32     StringToFloat( ) const;
    Bool        IsEmpty( ) const ;
    Bool        ConvertToInteger( Int32& value );
    Void        AllocateBuffer( UInt32 size );
    Void        SetEmpty();
    HashValue	GetHashCode() const;
    Void        SetFrom( String buffer, UInt32 length );
	Void		ToUpper();
	//@}

private:

    //Methods
    Char*              Allocate( const UInt32 size ) const;
    Void                Free( Char* ptr ) const;

    //Attributes
    Char*              m_Buffer;
    UInt16              m_Length;

};

Inline
Char CString::operator[]( const UInt32 i) const
{
    DebugAssert(i < m_Length);

    return m_Buffer[i];
}

Inline
Bool CString::operator<( const CString& other ) const
{
    return  ( Compare(other) < 0 );
}

Inline
Bool CString::operator<( String other ) const
{
    return  ( Compare(other) < 0 );
}

Inline
Bool CString::operator==( const CString& other ) const
{
    if( Compare( other ) == 0)
        return TRUE;
    return FALSE;
}

Inline
Bool CString::operator==( String other ) const
{
    if( Compare( other ) == 0)
        return TRUE;
    return FALSE;
}

Inline
Bool CString::operator!=( const CString& other ) const
{
    if( Compare( other ) != 0)
        return true;

    return false;
}

Inline
Bool CString::operator!=( String other ) const
{
    if( Compare( other ) != 0)
        return TRUE;
    return FALSE;
}

Inline
CString::CString()
{
    m_Buffer = NULL;
    m_Length = 0;
}

Inline
CString::operator String ()
{
    return m_Buffer;
}

Inline
CString::operator String () const
{
    return m_Buffer;
}

Inline
Bool CString::IsEmpty( ) const 
{
    return ( m_Length == 0 ) ;
}

Inline
String CString::GetBuffer() const 
{
    return m_Buffer;
}

Inline
UInt32 CString::GetLength() const 
{
    return m_Length;
}

}

#endif

