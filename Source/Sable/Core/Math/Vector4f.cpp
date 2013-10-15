#include <Sable\Core\Math\Vector4f.h>

#include <Sable\Core\Math\Primitives.h>
#include <Sable\Core\Math\Vector3f.h>

using namespace Sable;

CVector4f CVector4f::Zero = CVector4f( 0.0f, 0.0f, 0.0f, 0.0f );

CVector4f::CVector4f()
{

}

CVector4f::CVector4f( Float32 px, Float32  py, Float32  pz, Float32 pw )
{
	x = px;
	y = py;
	z = pz;
	w = pw;	
}

CVector4f::CVector4f( const CVector2f& v, Float32 pz, Float32 pw )
{
	x = v.GetX();
	y = v.GetY();
	z = pz;
	w = pw;	
}

CVector4f::CVector4f( const CVector3f& v, Float32 pw )
{
	x = v.GetX();
	y = v.GetY();
	z = v.GetZ();
	w = pw;	
}

CVector4f& CVector4f::operator=( const CVector4f& other )
{
	x = other.GetX();
	y = other.GetY();
	z = other.GetZ();
	w = other.GetW();
	return *this;
}

CVector4f& CVector4f::operator=( const CVector3f& other )
{
	x = other.GetX();
	y = other.GetY();
	z = other.GetZ();
	w = 1.0f;
	return *this;
}

CVector4f CVector4f::operator*( const Float32 v) const 
{
	return CVector4f( x * v, y * v, z * v, w * v );
}

CVector4f CVector4f::operator+( const CVector4f& v) const
{
	return CVector4f( x + v.GetX(), y + v.GetY(), z + v.GetZ(), w + v.GetW() );
}

CVector4f CVector4f::operator-( const CVector4f& v) const
{
	return CVector4f( x - v.GetX(), y - v.GetY(), z - v.GetZ(), w - v.GetW() );
}

/**
Transform the vector by m.
Use this method to do general vector transformation.
\param[in] m The transformation matrix.
*/
Void CVector4f::Transform( const CMatrix4x4f& m)
{
	CVector4f tmp = *this;

	x	= m._11*tmp.GetX() + m._21*tmp.GetY() + m._31*tmp.GetZ() + m._41*tmp.GetW();
	y	= m._12*tmp.GetX() + m._22*tmp.GetY() + m._32*tmp.GetZ() + m._42*tmp.GetW();
	z	= m._13*tmp.GetX() + m._23*tmp.GetY() + m._33*tmp.GetZ() + m._43*tmp.GetW();
	w	= m._14*tmp.GetX() + m._24*tmp.GetY() + m._34*tmp.GetZ() + m._44*tmp.GetW();
}

Void CVector4f::SetToZero()
{
	x = y = z = w = 0;
}

Bool CVector4f::operator==( const CVector4f& V ) const
{
	return GetX() == V.GetX() && GetY() == V.GetY() && GetZ() == V.GetZ() && GetW() == V.GetW();
}

Bool CVector4f::operator!=( const CVector4f& V ) const
{
	return GetX() != V.GetX() || GetY() != V.GetY() || GetZ() != V.GetZ() || GetW() != V.GetW();
}

Bool CVector4f::operator<=( const CVector4f& other ) const
{
	return ( x <= other.x ) && ( y <= other.y ) && ( z <= other.z ) && ( w <= other.w );
}

//Normalisation
Void CVector4f::Normalize()
{
	Float32 Norm = MathSqrt(x * x + y * y + z * z + w * w);
	x = x / Norm;
	y = y / Norm;
	z = z / Norm;
	w = w / Norm;
}

Float32  CVector4f::DotProduct(const CVector4f& v)
{
	return x*v.GetX() + y*v.GetY() + z*v.GetZ() + w*v.GetW() ;
}

Void	CVector4f::Set( const Float32 px, const Float32  py, const Float32  pz, const Float32 pw)
{
	x = px;
	y = py;
	z = pz;
	w = pw;
}

Void  CVector4f::Set( const CColor& c )
{
	x = c.GetR();
	y = c.GetG();
	z = c.GetB();
	w = c.GetA();
}

Void	CVector4f::Set( const CVector3f& v, const Float32 pw)
{
	x = v.GetX();
	y = v.GetY();
	z = v.GetZ();
	w = pw;
}

Float32 CVector4f::GetX() const
{
    return x;
}

Float32 CVector4f::GetY() const
{
    return y;
}

Float32 CVector4f::GetZ() const
{
    return z;
}

Float32 CVector4f::GetW() const
{
    return w;
}

Void CVector4f::SetX( Float32 v )
{
    x = v;
}

Void CVector4f::SetY( Float32 v )
{
    y = v;
}

Void CVector4f::SetZ( Float32 v )
{
    z = v;
}
Void CVector4f::SetW( Float32 v )
{
    w = v;
}

/**
Compute the sum of each component
\return The sum
*/
Float32	CVector4f::GetSum() const
{
	return x+y+z+w;
}

Bool CVector4f::Serialize( CPersistentArchive& ar )
{
	ar.Serialize( x, WT("x"));
	ar.Serialize( y, WT("y"));
	ar.Serialize( z, WT("z"));
	ar.Serialize( w, WT("w"));

	return TRUE;
}
