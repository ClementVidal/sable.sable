#ifndef _CORE_COMMON_COLOR_
#define _CORE_COMMON_COLOR_

#include <Sable/Core/Common/DataTypes.h>

namespace Sable
{

class CPersistentArchive;
class CVector4f;

/** 
\ingroup CoreCommon
Color. 
*/
class CColor
{

public:

	/** @name Constructor/Destructor*/
    //@{
	CColor();
	CColor(const Float32 a, const Float32 r, const Float32 g, const Float32 b );
	CColor(const Float32 r, const Float32 g, const Float32 b);
	CColor( const CColor& other);
	~CColor();
    //@}

	/** @name Operator*/
    //@{
	Bool operator==( const CColor& other );
	Bool operator!=( const CColor& other );
	Bool operator<=( const CColor& other );
	CColor& operator=( const CColor& other );
	CColor& operator= ( UInt32 value );
	CColor operator*( Float32 v) const ;
	CColor operator*( const CColor& v) const ;
    CColor operator+( const CColor& v) const ;
    CColor operator-( const CColor& v) const ;
    CColor operator+( Float32 v) const ;
	CColor&   operator+=( const CColor& v);
	CColor&   operator+=( const CVector4f& v);
	Float32& operator[]( UInt32 i) const ;
	//@}

	/** @name Accessors*/
    //@{
    Void    SetR( Float32 c );
    Void    SetG( Float32 c );
    Void    SetB( Float32 b );
    Void    SetA( Float32 c );
    Float32    GetR( ) const;
    Float32    GetG( ) const;
    Float32    GetB( ) const;
    Float32    GetA( ) const;
	Void	Set(const Float32 a, const Float32 r, const Float32 g, const Float32 b);
    UInt32  GetUInt32Color() const;
	Void	SetFromUInt32Color( const UInt32 value );
    //@}

	/** @name Manipulator*/
    //@{
    Bool Serialize( CPersistentArchive& ar );
    Void Normalize();
    //@}

	/** @name Attributes*/
	//@{
	Float32 r;
	Float32 g;
	Float32 b;
	Float32 a;
	//@}

	/** @name Constants*/
	//@{
	static CColor Red;
	static CColor Green;
	static CColor Blue;
	static CColor Yellow;
	static CColor Black;
	static CColor White;
	static CColor Grey;
	//@}

};



}
#endif
