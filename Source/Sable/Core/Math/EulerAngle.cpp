#include <Sable/Core/Math/EulerAngle.h>

#include <Sable/Core/Math/Quaternion.h>
#include <Sable/Core/Math/Matrix4x4f.h>
#include <Sable/Core/Math/Matrix3x3f.h>

using namespace Sable;

CEulerAngle CEulerAngle::Zero = CEulerAngle( 0.0f, 0.0f, 0.0f );

CEulerAngle::CEulerAngle()
{
}

CEulerAngle::CEulerAngle( const CEulerAngle& other )
{
    x = other.GetPitch();
    y = other.GetYaw();
    z = other.GetRoll();
}

CEulerAngle CEulerAngle::operator+( const CEulerAngle& v) const 
{
    return CEulerAngle( x + v.GetPitch(), y + v.GetYaw(), z + v.GetRoll() );
}

CEulerAngle CEulerAngle::operator/( Float32 v ) const 
{
    return CEulerAngle( x/v, y/v, z/v );
}

CEulerAngle CEulerAngle::operator*( Float32 v ) const 
{
    return CEulerAngle( x*v, y*v, z*v );
}

CEulerAngle::operator CVector3f () const
{
    return CVector3f( x,y,z );
}

CEulerAngle::CEulerAngle( const CVector3f& v )
{
    x = v.GetX();
    y = v.GetY();
    z = v.GetZ();
}

CEulerAngle::CEulerAngle( const Float32 pitch, const Float32 yaw, const Float32 roll )
{
	x = pitch;
	y = yaw;
	z = roll;
}

CEulerAngle& CEulerAngle::operator=( const CEulerAngle& other )
{
	x = other.GetPitch();
	y = other.GetYaw();
	z = other.GetRoll();
    return *this;
}

CEulerAngle::~CEulerAngle()
{
}

CEulerAngle::CEulerAngle( const CMatrix3x3f& v )
{
    *this = CEulerAngle( CQuaternion( v ) );
}

CEulerAngle::CEulerAngle( const CQuaternion& q1)
{
	Float32 test = q1.GetX()*q1.GetY() + q1.GetZ()*q1.GetW();
	if (test > ( 0.5f - FLOAT32_ERROR_THRESHOLD ) ) 
    { 
        // singularity at north pole
		y = 2 * MathArcTan2(q1.GetX(),q1.GetW());
		z = MathPi/2;
		x = 0;
		return;
	}
	if (test < - ( 0.5f - FLOAT32_ERROR_THRESHOLD ) ) 
    { 
        // singularity at south pole
		y = -2 * MathArcTan2(q1.GetX(),q1.GetW());
		z = - MathPi/2;
		x = 0;
		return;
	}
    Float32 sqx = q1.GetX()*q1.GetX();
    Float32 sqy = q1.GetY()*q1.GetY();
    Float32 sqz = q1.GetZ()*q1.GetZ();

    y = MathArcTan2(2*q1.GetY()*q1.GetW()-2*q1.GetX()*q1.GetZ() , 1 - 2*sqy - 2*sqz);
	z = MathArcSin(2*test);
	x = MathArcTan2(2*q1.GetX()*q1.GetW()-2*q1.GetY()*q1.GetZ() , 1 - 2*sqx - 2*sqz);
}

CEulerAngle::CEulerAngle( const CVector3f& axis, Float32 angle )
{
    Float32 s=MathSin(angle);
    Float32 c=MathCos(angle);
    Float32 t=1-c;

    if ((axis.GetX()*axis.GetY()*t + axis.GetZ()*s) > 0.998) 
    { 
        // north pole singularity detected
        x = 2*MathArcTan2(axis.GetX()*MathSin(angle/2),MathCos(angle/2));
        y = MathPi/2;
        z = 0;
        return;
    }
    if ((axis.GetX()*axis.GetY()*t + axis.GetZ()*s) < -0.998) 
    { 
        // south pole singularity detected
        x = -2*MathArcTan2(axis.GetX()*MathSin(angle/2),MathCos(angle/2));
        y = -MathPi/2;
        z = 0;
        return;
    }

    y = MathArcTan2(axis.GetY() * s - axis.GetX() * axis.GetZ() * t , 1 - (axis.GetY()*axis.GetY() + axis.GetZ()*axis.GetZ() ) * t);
    z = MathArcSin(axis.GetX() * axis.GetY() * t + axis.GetZ() * s) ;
    x = MathArcTan2(axis.GetX() * s - axis.GetY() * axis.GetZ() * t , 1 - ( axis.GetX()*axis.GetX() + axis.GetZ()*axis.GetZ() ) * t);

    x = MathClampToZero( x );
    y = MathClampToZero( y );
    z = MathClampToZero( z );
}

Float32 CEulerAngle::GetPitch() const
{
    return x;
}

Float32 CEulerAngle::GetYaw() const
{
    return y;
}

Float32 CEulerAngle::GetRoll() const
{
    return z;
}

Void CEulerAngle::SetPitch( Float32 v )
{
    x = v;
}

Void CEulerAngle::SetYaw( Float32 v )
{
    y = v;
}

Void CEulerAngle::SetRoll( Float32 v )
{
    z = v;
}