#ifndef _CORE_COMMON_WSTRING_
#define _CORE_COMMON_WSTRING_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Debug/Primitives.h>
#include <Sable/Core/Memory/Primitives.h>

namespace Sable
{

class CPersistentArchive;

/** 
\ingroup CoreString
Wide WString. 
*/
class CWString 
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CWString();
    CWString( const CWString& other );
    CWString( WString text );
    virtual ~CWString();
    //@}

    /** @name Operator - Cast*/
    //@{
    operator WString ();
    operator WString () const ;
    //@}

    /** @name Operator - Copy*/
    //@{
    CWString&    operator=( const CWString& other );
    CWString&    operator=( WString other );
    //@}

    /** @name Operator - Comparator*/
    //@{
    WChar       operator[]( const UInt32 i) const ;
    Bool        operator<( WString other ) const;
    Bool        operator<( const CWString& other ) const;
    Bool        operator==( const CWString& other ) const;
    Bool        operator==( WString other ) const;
    Bool        operator!=( WString other ) const;
    Bool        operator!=( const CWString& other ) const;
    //@}

    /** @name Operator - Concatenation*/
    //@{
    CWString     operator+( const CWString& other ) const;
    CWString     operator+( const Void* other ) const;
    CWString     operator+( WString text ) const;
    CWString     operator+( const UInt32 other ) const;
    CWString     operator+( const Int32 other ) const;
    //@}

    /** @name Accessors*/
    //@{
    WString    GetBuffer() const ;
    UInt32     GetLength() const ;
    //@}

    /** @name Manipulator*/
    //@{
    Void        WriteFormattedText( WString format, ... );
    UInt32      ReverseFind( WChar caract );
    UInt32      Find( WChar caract );
    CWString    SubString( UInt32 offset, Int32 size=-1 ) const;
    Void        Cut( UInt32 offset );
    Int32       Compare( WString other) const ;
    Int32       Compare( const CWString& other) const ;
    Void        Append( const CWString& other );
    Void        Append( UInt32 other );
    Void        Append( Int32 other );
    Bool        BeginBy( WString word ) const ;
    Void        IntToString( Int32 value , UInt8 base = 16 );
    Void        IntToString( UInt32 value , UInt8 base = 16 );
    Float32     StringToFloat( ) const;
    Bool        IsEmpty( ) const ;
    Bool        ConvertToInteger( Int32& value );
    Void        AllocateBuffer( UInt32 size );
    Void        SetEmpty();
    Void        SetFrom( WString buffer, UInt32 length );
    //@}

private:

    //Methods
    UInt32              ComputeLenght( WString buffer) const ;
    Int32               Compare( WString other, const UInt32 otherLenght ) const;
    WChar*              Allocate( const UInt32 size ) const;
    Void                Free( WChar* ptr ) const;

    //Attributes
    WChar*              m_Buffer;
    UInt16              m_Length;

};

Inline
WChar CWString::operator[]( const UInt32 i) const
{
    DebugAssert(i < m_Length);

    return m_Buffer[i];
}

Inline
Bool CWString::operator<( const CWString& other ) const
{
    return  ( Compare(other) < 0 );
}

Inline
Bool CWString::operator<( WString other ) const
{
    return  ( Compare(other) < 0 );
}

Inline
Bool CWString::operator==( const CWString& other ) const
{
    if( Compare( other ) == 0)
        return TRUE;
    return FALSE;
}

Inline
Bool CWString::operator==( WString other ) const
{
    if( Compare( other ) == 0)
        return TRUE;
    return FALSE;
}

Inline
Bool CWString::operator!=( const CWString& other ) const
{
    if( Compare( other ) != 0)
        return true;

    return false;
}

Inline
Bool CWString::operator!=( WString other ) const
{
    if( Compare( other ) != 0)
        return TRUE;
    return FALSE;
}

Inline
CWString::CWString()
{
    m_Buffer = NULL;
    m_Length = 0;
}

Inline
CWString::operator WString ()
{
    return m_Buffer;
}

Inline
CWString::operator WString () const
{
    return m_Buffer;
}

Inline
Bool CWString::IsEmpty( ) const 
{
    return ( m_Length == 0 ) ;
}

Inline
WString CWString::GetBuffer() const 
{
    return m_Buffer;
}

Inline
UInt32 CWString::GetLength() const 
{
    return m_Length;
}


}

#endif

