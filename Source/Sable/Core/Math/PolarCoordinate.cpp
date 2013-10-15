#include <Sable\Core\Math\PolarCoordinate.h>

using namespace Sable;

CPolarCoordinate::CPolarCoordinate()
{
	x = y = z = 0;
}

CPolarCoordinate::CPolarCoordinate( Float32 azimuth, Float32 zenith, Float32 radius )
{
	Set( azimuth, zenith, radius );
}

CPolarCoordinate::CPolarCoordinate( const CVector3f& v )
{
	SetFromCartesianCoordinate( v );
}

CPolarCoordinate CPolarCoordinate::operator+( const CPolarCoordinate& v) const
{
	Float32 az = GetAzimuth()+v.GetAzimuth();
	Float32 ze = GetZenith()+v.GetZenith();

	if( az > MathPi*2.0f )
		az = az - (MathPi*2.0f);
	else if( az < 0.0f )
		az = (MathPi*2.0f) - az;

	if( ze > MathPi  )
		ze = ze - (MathPi );
	else if( ze < 0.0f )
		ze = (MathPi ) - ze;

	DebugAssert( az >= 0.0f && az <= MathPi * 2.0f );
	DebugAssert( ze >= 0.0f && ze <= MathPi );

	CPolarCoordinate tmp( GetAzimuth()+v.GetAzimuth(), GetZenith()+v.GetZenith(), GetRadius() );
	return tmp;
}

Void CPolarCoordinate::Normalize()
{
	x = 0.0f;
}

CVector3f CPolarCoordinate::ConvertToCartesianCoordinate() const
{
	Float32 tx = x * MathCos( y ) * MathCos( z );
	Float32 ty = x * MathSin( z );
	Float32 tz = x * MathSin( y ) * MathCos( z );
	
	return CVector3f( tx, ty, tz );
}

Void CPolarCoordinate::SetFromCartesianCoordinate( const CVector3f& vector )
{
	x = vector.GetLength();
	y = MathArcTan2( vector.GetX(), vector.GetZ() );
	z = MathArcCos( vector.GetY() / x );
}

Void CPolarCoordinate::Set( Float32 azimuth, Float32 zenith, Float32 radius )
{
	x = radius;
	y = azimuth;
	z = zenith;
}

Float32	CPolarCoordinate::GetAzimuth() const
{
	return y;
}

Float32 CPolarCoordinate::GetZenith() const
{
	return z;
}

Float32	CPolarCoordinate::GetRadius() const
{
	return x;
}

CPolarCoordinate& CPolarCoordinate::operator+=( const CPolarCoordinate& v)
{
	Float32 ty = y;
	Float32 tz = z;

	ty += v.GetAzimuth();
	tz += v.GetZenith();

	if( ty > MathPi*2.0f )
		ty = ty - (MathPi*2.0f);
	else if( ty < 0.0f )
		ty = (MathPi*2.0f) + ty;

	if( tz > MathPi*2.0f )
		tz = tz - (MathPi*2.0f );
	else if( tz < 0.0f )
		tz = (MathPi*2.0f) + tz;

	DebugAssert( ty >= 0.0f && ty <= MathPi*2.0f );
	DebugAssert( tz >= 0.0f && tz <= MathPi*2.0f );

	y = ty;
	z = tz;

	return *this;
}