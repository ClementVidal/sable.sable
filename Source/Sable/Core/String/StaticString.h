#ifndef _SABLE_CORE_COMMON_STATICSTRING_
#define _SABLE_CORE_COMMON_STATICSTRING_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Debug\Primitives.h>
#include <Sable\Core\String\Primitives.h>

namespace Sable
{

class CPersistentArchive;

/** 
\ingroup CoreString
String. 
*/
template< UInt32 Count >
class CStaticString 
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CStaticString();
    CStaticString( const CStaticString& other );
    CStaticString( String text );
    CStaticString( WString text );
    ~CStaticString();
    //@}

    /** @name Operator - Cast*/
    //@{
    operator String();
    operator String() const ;
    //@}

    /** @name Operator - Copy*/
    //@{
    CStaticString&    operator=( const CStaticString& other );
    CStaticString&    operator=( String other );
    //@}

    /** @name Operator - Comparator*/
    //@{
    Bool        operator<( String other ) const;
    Bool        operator<( const CStaticString& other ) const;
    Bool        operator==( const CStaticString& other ) const;
    Bool        operator==( String other ) const;
    Bool        operator!=( String other ) const;
    Bool        operator!=( const CStaticString& other ) const;
    //@}

    /** @name Operator - Concatenation*/
    //@{
    //@}

    /** @name Accessors*/
    //@{
	Void		SetEmpty();
	Bool		IsEmpty() const;
    UInt32      GetCapacity( ) const;
    String      GetBuffer() const ;
    UInt32      GetLength() const ;
    //@}

    /** @name Manipulator*/
    //@{
    Void        WriteFormattedText( String format, ... );
    //@}

private:

    //Methods
    Int32       Compare( String other) const ;
    Int32       Compare( const CStaticString& other) const ;

    //Attributes
    Char               m_Buffer[Count];
    UInt16             m_Length;

};

#include <Sable\Core\String\StaticString.hpp>

typedef CStaticString<64>	CStringIdentifier;

}

#endif

