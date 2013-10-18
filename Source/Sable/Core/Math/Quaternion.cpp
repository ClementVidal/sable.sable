#include <Sable/Core/Math/Quaternion.h>

#include <Sable/Core/Math/Matrix4x4f.h>
#include <Sable/Core/Persistent/Archive.h>

using namespace Sable;

CQuaternion::CQuaternion()
{
}

CQuaternion::CQuaternion( const CEulerAngle& ea )
{
    SetFromEulerAngle( ea );
}

CQuaternion::CQuaternion( const CQuaternion& other )
{
	x = other.GetX();
	y = other.GetY();
	z = other.GetZ();
	w = other.GetW();
}

CQuaternion::CQuaternion( const CMatrix4x4f& m )
{
    SetFromMatrix( m );
}

CQuaternion::CQuaternion( const CMatrix3x3f& m )
{
    SetFromMatrix( m );
}


CQuaternion& CQuaternion::operator=( const CQuaternion& other )
{
	x = other.GetX();
	y = other.GetY();
	z = other.GetZ();
	w = other.GetW();
	return *this;
}

CQuaternion::CQuaternion( Float32 new_x, Float32 new_y, Float32 new_z, Float32 new_w )
{
	x = new_x;
	y = new_y;
	z = new_z;
	w = new_w;
}

CQuaternion::~CQuaternion()
{
}

CQuaternion CQuaternion::operator-( ) const 
{
	return CQuaternion( -GetX(), -GetY(), -GetZ(), -GetW() );
}

CQuaternion CQuaternion::operator/( Float32 v) const 
{
	return CQuaternion( GetX() / v, GetY() / v, GetZ() / v, GetW() / v );
}

CQuaternion CQuaternion::operator+( const CQuaternion v) const
{
	return CQuaternion( GetX() + v.GetX(), GetY() + v.GetY(), GetZ() + v.GetZ(), GetW() + v.GetW() );
}

CQuaternion CQuaternion::operator-( const CQuaternion v) const
{
	return CQuaternion( GetX() - v.GetX(), GetY() - v.GetY(), GetZ() - v.GetZ(), GetW() - v.GetW() );
}

CQuaternion CQuaternion::operator*( const CQuaternion v) const
{
	CQuaternion res;

	//w1*w2 - v1.DotProduct( v2 ) 
	//w * v.w - ( x*v.GetX() *
	res.w = w * v.w - x*v.GetX() - y*v.GetY() - z*v.GetZ(); 

	//w1*v2 + w2*v1 + v1 x v2
	res.SetX( w*v.GetX() + v.w*x + y*v.GetZ() - z*v.GetY() );
	res.SetY( w*v.GetY() + v.w*y + z*v.GetX() - x*v.GetZ() );
	res.SetZ( w*v.GetZ() + v.w*z + x*v.GetY() - y*v.GetX() );

	return res;
}

Void CQuaternion::SetFromIdentity()
{
	x=y=z= 0.0f;
	w=1.0f;
}

Void CQuaternion::SetFromMultiplication( const CQuaternion& q1, const CQuaternion& q2 )
{

}

Void CQuaternion::SetFromMatrix( const CMatrix4x4f& m )
{
    SetFromMatrix( m.GetRotationComponent() );
}

Void CQuaternion::SetFromMatrix( const CMatrix3x3f& m )
{
	if ( m._11 + m._22 + m._33 > 0.0f ) 
	{
		Float32 s = MathSqrt( m._11 + m._22 + m._33 + 1.0f ) * 2.0f;
		w = 0.25f * s;
		x = ( m._32 - m._23 ) / s;
		y = ( m._13 - m._31 ) / s;
		z = ( m._12 - m._21 ) / s;
	} 
	else if ( m._11 > m._22 && m._11 > m._33 ) 
	{
		Float32 s = MathSqrt( m._11 - m._22 - m._33 + 1.0f ) * 2.0f;
        w = ( m._32 - m._23 ) / s;
        x = 0.25f * s;
        y = ( m._12 + m._21 ) / s;
        z = ( m._13 - m._31 ) / s;
	} 
	else if ( m._22 > m._33 ) 
	{
		Float32 s = MathSqrt( - m._11 + m._22 - m._33 + 1.0f ) * 2.0f;
		w = ( m._13 - m._31 ) / s;
		x = ( m._12 + m._21 ) / s;
		y = 0.25f * s;
		z = ( m._23 + m._32 ) / s;
	} 
	else 
	{
		Float32 s = MathSqrt( - m._11 - m._22 + m._33 + 1.0f ) * 2.0f;
		w = ( m._21 - m._12 ) * s;
		x = ( m._13 + m._31 ) * s;
		y = ( m._23 + m._32 ) * s;
		z = 0.25f * s;
	}
}

Void CQuaternion::SetFromAxisAndAngle( const CVector3f& Axe, const Float32 Angle )
{

}

Void CQuaternion::SetFromEulerAngle( const CEulerAngle& angle )
{
    Float32 c1 = MathCos(angle.GetYaw() / 2);
    Float32 c2 = MathCos(angle.GetRoll() / 2);
    Float32 c3 = MathCos(angle.GetPitch() / 2);
    Float32 s1 = MathSin(angle.GetYaw() / 2);
    Float32 s2 = MathSin(angle.GetRoll() / 2);
    Float32 s3 = MathSin(angle.GetPitch() / 2);

    w = c1 * c2 * c3 - s1 * s2 * s3;
    x = s1 * s2 * c3 + c1 * c2 * s3;
    y = s1 * c2 * c3 + c1 * s2 * s3;
    z = c1 * s2 * c3 - s1 * c2 * s3;
}

Void CQuaternion::Normalize()
{
	Float32 norm = GetLength();

	w = w / norm;
	x = x / norm;
	y = y / norm;
	z = z / norm;
}

Float32 CQuaternion::GetLength() const
{
	return MathSqrt( x*x + y*y + z*z + w*w );
}


Float32 CQuaternion::GetX() const
{
    return x;
}

Void CQuaternion::Lerp(const CQuaternion &q2,Float32 t) 
{ 
	DebugAssert( t >= 0.0f && t <= 1.0f );

	CQuaternion q1 = *this;
	*this = q1 * (1.0f-t) + q2 * t;
	Normalize();
}

CQuaternion CQuaternion::operator*( Float32 v ) const 
{
	return CQuaternion( GetX() * v, GetY() * v, GetZ() * v, GetW() * v );
}

Float32 CQuaternion::DotProduct( const CQuaternion &q2 ) 
{
	return x*q2.GetX() + y*q2.GetY() + z*q2.GetZ() + w*q2.GetW();
}

Void CQuaternion::Slerp(const CQuaternion &q2,Float32 t) 
{
	CQuaternion q3;
	CQuaternion q1 = *this;

	DebugAssert( t >= 0.0f && t <= 1.0f );

	Float32 dot = DotProduct( q2 );

	/*	dot = cos(theta)
		if (dot < 0), q1 and q2 are more than 90 degrees apart,
		so we can invert one to reduce spinning	*/
	if( dot < 0.0f )
	{
		dot = -dot;
		q3 = -q2;
	} 
	else 
	{
		q3 = q2;
	}
	
	if( dot < 0.95f )
	{
		Float32 angle = MathArcCos( dot );
		*this = ( q1 * MathSin( angle*(1-t) ) + q3 * MathSin(angle*t ) ) / MathSin(angle);
	} 
	else// if the angle is small, use linear interpolation	
	{							
		Lerp( q3,t);	
	}
}

Float32 CQuaternion::GetY() const
{
    return y;
}

Float32 CQuaternion::GetZ() const
{
    return z;
}

Float32 CQuaternion::GetW() const
{
    return w;
}

Void CQuaternion::SetX( Float32 v )
{
    x = v;
}

Void CQuaternion::SetY( Float32 v )
{
    y = v;
}

Void CQuaternion::SetZ( Float32 v )
{
    z = v;
}
Void CQuaternion::SetW( Float32 v )
{
    w = v;
}
