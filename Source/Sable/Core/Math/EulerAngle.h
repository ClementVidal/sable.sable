#ifndef _CORE_MATH_EULERANGLE_
#define _CORE_MATH_EULERANGLE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Math/Tuple.h>

namespace Sable
{

class CQuaternion;
class CMatrix4x4f;
class CMatrix3x3f;
class CVector3f;

/** 
\ingroup CoreMath
EulerAngle.
Note that angles are stored as follow:
x: rotation around x( Pitch )
y: rotation around y( Yaw/Heading )
z: rotation around z( Roll/Bank )
*/
class CEulerAngle : private STuple3f
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CEulerAngle();
	CEulerAngle( const Float32 pitch, const Float32 yaw, const Float32 roll );
    CEulerAngle( const CEulerAngle& other );
    CEulerAngle( const CQuaternion& q );
    CEulerAngle( const CVector3f& v );
    CEulerAngle( const CMatrix3x3f& v );
    CEulerAngle( const CVector3f& axis, Float32 angle );
    virtual ~CEulerAngle();
    //@}

    /** @name Operator*/
    //@{
    operator CVector3f () const;
    CEulerAngle& operator=( const CEulerAngle& other );
	CEulerAngle    operator+( const CEulerAngle& v) const ;
	CEulerAngle    operator/( Float32 v ) const ;
	CEulerAngle    operator*( Float32 v ) const ;
    //@}


    /** @ Accessor*/
    //@{
    Float32 GetPitch() const;
    Float32 GetYaw() const;
    Float32 GetRoll() const;
    Void	SetPitch( Float32 v );
    Void	SetYaw( Float32 v );
    Void	SetRoll( Float32 v );
    //@}

    /** @name Constants*/
    //@{
    static CEulerAngle Zero;
    //@}
};

}

#endif
