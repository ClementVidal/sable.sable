#ifndef _CORE_MATH_QUATERNION_
#define _CORE_MATH_QUATERNION_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Math\Tuple.h>

namespace Sable
{

class CEulerAngle;
class CMatrix3x3f;
class CMatrix4x4f;

/** 
\ingroup CoreMath
Quaternion. 
*/
class CQuaternion : private STuple4f
{

public:

	/** @name Constructor/Destructor*/
    //@{
	CQuaternion();
	CQuaternion( const CQuaternion& other );
	CQuaternion( const CMatrix4x4f& m );
	CQuaternion( const CMatrix3x3f& m );
	CQuaternion( const CEulerAngle& e );
	CQuaternion( Float32 new_x, Float32 new_y, Float32 new_z, Float32 new_w );
	~CQuaternion();
    //@}

	/** @name Operator*/
    //@{
	CQuaternion     operator-( ) const ;
	CQuaternion&    operator=( const CQuaternion& other );
	CQuaternion     operator*( const CQuaternion v) const ;
	CQuaternion     operator/( Float32 v) const ;
	CQuaternion     operator+( const CQuaternion v) const ;
	CQuaternion     operator-( const CQuaternion v) const ;
	CQuaternion     operator*( Float32 v) const ;
    //@}

	/** @name Mutator*/
    //@{
	Void		SetFromIdentity();
	Void		SetFromMatrix( const CMatrix3x3f& m );
	Void		SetFromMatrix( const CMatrix4x4f& m );
	Void		SetFromMultiplication( const CQuaternion& q1, const CQuaternion& q2 );
	Void		SetFromAxisAndAngle( const CVector3f& Axe, const Float32 Angle ); 
	Void		SetFromEulerAngle( const CEulerAngle& angle ); 
	Float32		GetLength() const;
	Void		Normalize();
	Void		Lerp(const CQuaternion &q2,Float32 t);
	Void		Slerp(const CQuaternion &q2,Float32 t);
	Float32		DotProduct( const CQuaternion &q2 ) ;
	//@}

    /** @ Accessor*/
    //@{
    Float32 GetX() const;
    Float32 GetY() const;
    Float32 GetZ() const;
    Float32 GetW() const;
    Void SetX( Float32 v );
    Void SetY( Float32 v );
    Void SetZ( Float32 v );
    Void SetW( Float32 v );
    //@}
};

}

#endif


