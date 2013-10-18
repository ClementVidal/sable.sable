#ifndef _SABLE_CORE_MATH_VECTOR4_
#define _SABLE_CORE_MATH_VECTOR4_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Math/Tuple.h>

namespace Sable
{

class CVector3f;
class CVector2f;
class CMatrix4x4f;
class CColor;

/** 
\ingroup CoreMath
Vector 4. 
*/
class CVector4f : private STuple4f
{

public:

	/** @name Constructor/Destructor*/
    //@{
	CVector4f();
	CVector4f( Float32 px, Float32  py, Float32  pz, Float32 pw );
	CVector4f( const CVector3f& v, Float32 pw );
	CVector4f( const CVector2f& v, Float32 z, Float32 w );
	//@}

	/** @name Operator*/
    //@{
	CVector4f& operator=( const CVector4f& other );
	CVector4f& operator=( const CVector3f& other );
	Bool operator==( const CVector4f& V ) const;
	Bool operator!=( const CVector4f& V ) const;
	Bool operator<=( const CVector4f& V ) const;

	CVector4f    operator*( const Float32 v) const ;
	CVector4f    operator+( const CVector4f& v) const ;
	CVector4f    operator-( const CVector4f& v) const ;
	//@}

    /** @ Accessor*/
    //@{
	Void        Set( const Float32 px, const Float32  py, const Float32  pz, const Float32 pw);
	Void        Set( const CVector3f& v, const Float32 pw);
	Void        Set( const CColor& c );
	Void        SetToZero();
    Float32     GetX() const;
    Float32     GetY() const;
    Float32     GetZ() const;
    Float32     GetW() const;
    Void        SetX( Float32 v );
    Void        SetY( Float32 v );
    Void        SetZ( Float32 v );
    Void        SetW( Float32 v );
	Float32		GetSum() const;
    //@}

	/** @name Mutator*/
    //@{
	Void		Transform( const CMatrix4x4f& m );
	Void		Normalize();
	Float32		DotProduct( const CVector4f& v);
    Bool		Serialize( CPersistentArchive& ar );
	//@}

	/** @name Constants*/
	//@{
	static CVector4f Zero;
	//@}

};

}

#endif


