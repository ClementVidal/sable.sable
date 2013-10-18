#ifndef _SABLE_CORE_MATH_VECTOR2F_
#define _SABLE_CORE_MATH_VECTOR2F_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Math/Tuple.h>


namespace Sable
{

class CVector2i;
class CMatrix3x3f;
class CPersistentArchive;

/** 
\ingroup CoreMath
Vector 2. 
*/
class CVector2f : private STuple2f
{

public:

	/** @name Constructor/Destructor*/
    //@{
	CVector2f();
	CVector2f( const CVector2i& other );
    CVector2f( const CVector2f& other );
	CVector2f( const Float32 px, const Float32  py);
	~CVector2f();
    //@}

	/** @name Operator*/
    //@{
	CVector2f& operator=( const CVector2f& other );
	Bool operator==( const CVector2f& V ) const;
	Bool operator!=( const CVector2f& V ) const;

	CVector2f    operator-( ) const ;
	
    CVector2f    operator+( const CVector2f& v) const;
	CVector2f    operator-( const CVector2f& v) const;
	CVector2f    operator*( const CVector2f& v) const;
	CVector2f    operator/( const CVector2f& v) const;
	
	CVector2f    operator-( const Float32 v) const;
	CVector2f    operator+( const Float32 v) const;
    CVector2f    operator*( const	 Float32 v) const;
	CVector2f    operator/( const Float32 v) const;
	
	CVector2f&   operator+=( const CVector2f& v);
	CVector2f&   operator-=( const CVector2f& v);
    CVector2f&   operator*=( const CVector2f& v);
	CVector2f&   operator/=( const CVector2f& v);
	CVector2f&   operator*=( const Float32 v);
	CVector2f&   operator/=( const Float32 v);
    //@}

	/** @name Accessors*/
    //@{
	Void	Set( const Float32 px, const Float32  py);
	Float32	GetLength() const;

    Float32 GetX() const;
    Float32 GetY() const;
    Void    SetX( Float32 v );
    Void    SetY( Float32 v );
    //@}

	/** @name Manipulator*/
    //@{
    Bool    Serialize( CPersistentArchive& ar );
	Void    Normalize();
	Void    TransformPosition( const CMatrix3x3f& m );
    Void    TransformVector( const CMatrix3x3f& m );
    //@}

    /** @name Constants*/
    //@{
    static CVector2f Zero;
    static CVector2f XAxis;
    static CVector2f YAxis;
    //@}

};

}

#endif


