#include <Sable\Core\Math\Vector3f.h>

#include <Sable\Core\Math\Primitives.h>
#include <Sable\Core\Math\Matrix4x4f.h>

using namespace Sable;

CVector3f CVector3f::Zero = CVector3f( 0.0f, 0.0f, 0.0f );
CVector3f CVector3f::XAxis = CVector3f( 1.0f, 0.0f, 0.0f );
CVector3f CVector3f::YAxis = CVector3f( 0.0f, 1.0f, 0.0f );
CVector3f CVector3f::ZAxis = CVector3f( 0.0f, 0.0f, 1.0f );
CVector3f CVector3f::Axis[] = { CVector3f::XAxis, CVector3f::YAxis, CVector3f::ZAxis };

CVector3f::CVector3f()
{
	x = y = z = 0;
}

CVector3f::CVector3f( const CVector3f& other )
{
	x = other.GetX();
	y = other.GetY();
	z = other.GetZ();
}

CVector3f::CVector3f( const Float32 xyz )
{
	x = xyz;
	y = xyz;
	z = xyz;
}

CVector3f::CVector3f( const Float32* xyz )
{
	DebugAssert( xyz );
	x = xyz[0];
	y = xyz[1];
	z = xyz[2];
}

CVector3f::CVector3f(const Float32 px, const Float32 py, const Float32 pz)
{
	x = px;
	y = py;
	z = pz;
}

CVector3f& CVector3f::operator=( const CVector3f& other )
{
	x = other.GetX();
	y = other.GetY();
	z = other.GetZ();
	return *this;
}

Bool CVector3f::Serialize( CPersistentArchive& ar )
{
    ar.Serialize( x, WT("x"));
    ar.Serialize( y, WT("y"));
    ar.Serialize( z, WT("z"));

    return TRUE;
}

Float32 CVector3f::GetX() const
{
    return x;
}

Float32 CVector3f::GetY() const
{
    return y;
}

Float32 CVector3f::GetZ() const
{
    return z;
}

Void CVector3f::SetX( Float32 v )
{
    x = v;
}

Void CVector3f::SetY( Float32 v )
{
    y = v;
}

Void CVector3f::SetZ( Float32 v )
{
    z = v;
}


/**
Negate the vector as follow:<br>
v = -v;
*/
Void CVector3f::Negate()
{
	x = -x;
	y = -y;
	z = -z;
}

/**
Normalize the vector.
*/
Void CVector3f::Normalize()
{
	Float32 Norm = MathSqrt(x * x + y * y + z * z);
	x = x / Norm;
	y = y / Norm;
	z = z / Norm;
}

/**
Return true if the vector is normalized
\return TRUE or FALSE if normalized or not
*/
Bool CVector3f::IsNormalized( ) const
{
	return MathIsNearlyEqual( GetLength(), 1.0f );
}

/**
Implemented but not tested
*/
Void CVector3f::SetFromReflectionVector( const CVector3f& input, const CVector3f& normal )
{
	Float32
		dot;

	dot = input.DotProduct( normal );

	x = input.GetX() - 2 * dot * normal.GetX();
	y = input.GetY() - 2 * dot * normal.GetY();
	z = input.GetZ() - 2 * dot * normal.GetZ();
}

/**
Compute the do product of this vector by v.
\param[in] v The right operand ( this beeing the left one )
\return the cross product value
*/
Float32  CVector3f::DotProduct(const CVector3f& v) const
{
	return x*v.GetX() + y*v.GetY() + z*v.GetZ();
}

/**
Set this vector by the result of the dot product of v& by v2.
\param[in] v1 The left operand.
\param[in] v1 The right operand.
*/
Void CVector3f::CrossProduct( const CVector3f& v1, const CVector3f& v2) 
{
    x = v1.GetY() * v2.GetZ() - v1.GetZ() * v2.GetY();
    y = v1.GetZ() * v2.GetX() - v1.GetX() * v2.GetZ();
    z = v1.GetX() * v2.GetY() - v1.GetY() * v2.GetX();
}

/**
Compute the scalar triple product (http://en.wikipedia.org/wiki/Triple_product) defined as follow:
a . ( b x c ) where a is this vector
*/
Float32 CVector3f::ScalarTripleProduct( const CVector3f& b, const CVector3f& c )
{
    return DotProduct( b.CrossProduct( c ) );
}

/**
Return the value of the cross product between this and v.
\param[in] v The right operand.
\return the result vector of the cross product.
*/
CVector3f CVector3f::CrossProduct( const CVector3f& v) const
{
	return CVector3f( y * v.GetZ() - z * v.GetY(), z * v.GetX() - x * v.GetZ(), x * v.GetY() - y * v.GetX() );;
}

/**
Transform the vector by m and then divide by W component.
Use this method to transform a position in space.
\param[in] m The transformation matrix.
*/
Void CVector3f::TransformPosition( const CMatrix4x4f& m )
{
	CVector3f tmp = *this;
	Float32 w = 1.0f;

	x	= m._11*tmp.GetX() + m._21*tmp.GetY() + m._31*tmp.GetZ() + m._41*1 ;
	y	= m._12*tmp.GetX() + m._22*tmp.GetY() + m._32*tmp.GetZ() + m._42*1 ;
	z	= m._13*tmp.GetX() + m._23*tmp.GetY() + m._33*tmp.GetZ() + m._43*1 ;
	w	= m._14*tmp.GetX() + m._24*tmp.GetY() + m._34*tmp.GetZ() + m._44*1 ;

	if( w != 0.0f )
	{
		x	= x / w; 
		y	= y / w; 
		z	= z / w; 
	}
}

/**
Transform the vector by m.
Use this method to do general vector transformation.
\param[in] m The transformation matrix.
*/
Void	CVector3f::Transform( const CMatrix4x4f& m )
{
	CVector3f tmp = *this;

	x = m._11*tmp.GetX() + m._21*tmp.GetY() + m._31*tmp.GetZ();
	y = m._12*tmp.GetX() + m._22*tmp.GetY() + m._32*tmp.GetZ();
	z = m._13*tmp.GetX() + m._23*tmp.GetY() + m._33*tmp.GetZ();
}

/**
Compute the linear interpolation between this vector and v.
The interpolation is parameterized by t.
\param[in] v the second vector.
\param[in] t the parametrization value between [ O.O , 1.0 ]
\return The interpoled vector
*/
CVector3f CVector3f::LinearInterpolation( const CVector3f& v, Float32 t)
{
	DebugAssert( t >= 0.0f && t <= 1.0f );
	CVector3f r( x + t*(v.GetX() -x), y + t*(v.GetY() -y), z + t*(v.GetZ() -z) );

	return r;
}

/**
Compute the length of the vector
\return The length
*/
Float32	CVector3f::GetLength() const
{
	Float32 f = x*x + y*y + z*z;
	if( f == 0.0f )
		return 0.0f;

	return MathSqrt(x*x + y*y + z*z);
}

/**
Compute the sum of each component
\return The sum
*/
Float32	CVector3f::GetSum() const
{
	return x+y+z;
}


CVector3f	CVector3f::Reflect( const CVector3f& n)
{
	Float32 i_dot_n;

	i_dot_n = DotProduct(n);

    CVector3f R( x - 2*i_dot_n * n.GetX(), y - 2*i_dot_n * n.GetY(), z - 2*i_dot_n * n.GetZ() );

	return R;
}

/**
Set the values of the vector.
\param px x
\param py y
\param pz z
*/
Void	CVector3f::Set( Float32 px, Float32 py, Float32 pz)
{
	x = px;
	y = py;
	z = pz;
}

CVector3f CVector3f::operator-( ) const
{
	return CVector3f( -x, -y, -z );
}

CVector3f CVector3f::operator+( const Float32 v) const 
{
	return CVector3f(x+v,y+v,z+v);
}

CVector3f CVector3f::operator-( const Float32 v) const
{
	return CVector3f(x-v,y-v,z-v);
}

CVector3f CVector3f::operator*( const Float32 v) const 
{
	return CVector3f(x*v,y*v,z*v);
}

CVector3f CVector3f::operator/( const Float32 v) const 
{
	return CVector3f(x/v,y/v,z/v);
}

CVector3f CVector3f::operator+( const CVector3f& v) const 
{
	return CVector3f(x+v.GetX(),y+v.GetY(),z+v.GetZ() );
}

CVector3f CVector3f::operator-( const CVector3f& v) const
{
	return CVector3f(x-v.GetX(),y-v.GetY(),z-v.GetZ() );
}

CVector3f CVector3f::operator*( const CVector3f& v) const 
{
	return CVector3f(x+v.GetX(),y+v.GetY(),z+v.GetZ() );
}

CVector3f CVector3f::operator/( const CVector3f& v) const 
{
	return CVector3f(x/v.GetX(),y/v.GetY(),z/v.GetZ() );
}

CVector3f& CVector3f::operator+=( const Float32 v)  
{
	x+=v;
	y+=v;
	z+=v;

	return *this;
}

CVector3f& CVector3f::operator-=( const Float32 v)  
{
	x-=v;
	y-=v;
	z-=v;

	return *this;
}

CVector3f& CVector3f::operator*=( const Float32 v)
{
	x*=v;
	y*=v;
	z*=v;

	return *this;
}

CVector3f& CVector3f::operator/=( const Float32 v)
{
	x/=v;
	y/=v;
	z/=v;

	return *this;
}

CVector3f& CVector3f::operator+=( const CVector3f& v)
{
	x+=v.GetX();
	y+=v.GetY();
	z+=v.GetZ();

	return *this;
}

CVector3f& CVector3f::operator-=( const CVector3f& v)
{
	x-=v.GetX();
	y-=v.GetY();
	z-=v.GetZ();

	return *this;
}

CVector3f& CVector3f::operator*=( const CVector3f& v)
{
	x*=v.GetX();
	y*=v.GetY();
	z*=v.GetZ();

	return *this;
}

CVector3f& CVector3f::operator/=( const CVector3f& v)
{
	x/=v.GetX();
	y/=v.GetY();
	z/=v.GetZ();

	return *this;
}

Bool CVector3f::operator!=( const CVector3f& V )  const 
{
	if((x != V.GetX() ) || (y != V.GetY() ) || (z != V.GetZ() ))
		return TRUE;

	return FALSE;
}

Bool CVector3f::operator==( const CVector3f& V )  const 
{
	if((x == V.GetX() ) && (y == V.GetY() ) && (z == V.GetZ() ))
		return TRUE;

	return FALSE;
}

Float32 CVector3f::operator[]( const UInt32 i ) const 
{
    DebugAssert( i < 3 );
    return (&x)[i];
}


