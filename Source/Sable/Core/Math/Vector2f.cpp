#include <Sable\Core\Math\Vector2f.h>

#include <Sable\Core\Math\Matrix3x3f.h>
#include <Sable\Core\Persistent\Archive.h>

using namespace Sable;

CVector2f CVector2f::Zero = CVector2f( 0.0f, 0.0f );
CVector2f CVector2f::XAxis = CVector2f( 1.0f, 0.0f );
CVector2f CVector2f::YAxis = CVector2f( 0.0f, 1.0f );

CVector2f::CVector2f()
{
	x = y =  0;
}

CVector2f::CVector2f( const CVector2f& other )
{
	x = other.GetX();
	y = other.GetY();
}

CVector2f::CVector2f( const CVector2i& other )
{
	x = (Float32) other.GetX();
	y = (Float32) other.GetY();
}

CVector2f::CVector2f( const Float32 px, const Float32  py)
{
	x = px;
	y = py;
}

Float32 CVector2f::GetX() const
{
    return x;
}

Float32 CVector2f::GetY() const
{
    return y;
}

Bool CVector2f::Serialize( CPersistentArchive& ar )
{
    ar.Serialize( x, WT("x") );
    ar.Serialize( y, WT("y") );
    return TRUE;
}

Void CVector2f::SetX( Float32 v )
{
    x = v;
}

Void CVector2f::SetY( Float32 v )
{
    y = v;
}

CVector2f CVector2f::operator-( ) const
{
    return CVector2f(-x,-y);
}

CVector2f CVector2f::operator+( const CVector2f& v) const
{
	return CVector2f(x+v.GetX(),y+v.GetY() );
}

CVector2f CVector2f::operator-( const CVector2f& v) const
{
	return CVector2f(x-v.GetX(),y-v.GetY() );
}

CVector2f CVector2f::operator*( const CVector2f& v) const
{
	return CVector2f(x*v.GetX(),y*v.GetY() );
}

CVector2f CVector2f::operator*( const Float32 v) const
{
	return CVector2f(x*v,y*v);
}

CVector2f CVector2f::operator/( const CVector2f& v) const
{
	return CVector2f(x/v.GetX(),y/v.GetY() );
}

CVector2f CVector2f::operator/( const Float32 v) const 
{
	return CVector2f(x/v,y/v);
}

CVector2f CVector2f::operator-( const Float32 v) const 
{
	return CVector2f(x-v,y-v);
}

CVector2f CVector2f::operator+( const Float32 v) const
{
	return CVector2f(x+v,y+v);
}

CVector2f& CVector2f::operator=( const CVector2f& other )
{
	x = other.GetX();
	y = other.GetY();
	return *this;
}

CVector2f& CVector2f::operator+=( const CVector2f& v)
{
    x += v.GetX();
    y += v.GetY();
    return *this;
}

CVector2f& CVector2f::operator-=( const CVector2f& v)
{
    x -= v.GetX();
    y -= v.GetY();
    return *this;
}

CVector2f& CVector2f::operator*=( const CVector2f& v)
{
    x *= v.GetX();
    y *= v.GetY();
    return *this;
}

CVector2f& CVector2f::operator/=( const CVector2f& v)
{
    x /= v.GetX();
    y /= v.GetY();
    return *this;
}

CVector2f& CVector2f::operator*=( const Float32 v )
{
	x *= v;
	y *= v;
	return *this;
}

CVector2f& CVector2f::operator/=( const Float32 v )
{
	x /= v;
	y /= v;
	return *this;
}

//Destructeur
CVector2f::~CVector2f()
{
}

Bool CVector2f::operator==( const CVector2f& V ) const
{
	if((x == V.GetX() ) && (y == V.GetY() ) )
		return TRUE;

	return FALSE;
}

Bool CVector2f::operator!=( const CVector2f& V ) const
{
	if((x != V.GetX() ) || (y != V.GetY() ) )
		return TRUE;

	return FALSE;
}

Void	CVector2f::Set( const Float32 px, const Float32  py)
{
	x = px;
	y = py;

}

Float32	CVector2f::GetLength() const
{
	return MathSqrt(x*x + y*y );
}

Void CVector2f::Normalize()
{
	Float32 
		Norm = MathSqrt(x * x + y * y );
	x = x / Norm;
	y = y / Norm;
}

Void CVector2f::TransformPosition( const CMatrix3x3f& m )
{
	CVector2f Tmp = *this;
	Float32 W = 1.0f;

	x	= m._11*Tmp.GetX() + m._21*Tmp.GetY() + m._31*1.0f ;
	y	= m._12*Tmp.GetX() + m._22*Tmp.GetY() + m._32*1.0f ;
	W	= m._13*Tmp.GetX() + m._23*Tmp.GetY() + m._33*1.0f ;

	x	= x / W; 
	y	= y / W; 
}


Void CVector2f::TransformVector( const CMatrix3x3f& m )
{
	CVector2f Tmp = *this;
	Float32 W = 1.0f;

	x	= m._11*Tmp.GetX() + m._21*Tmp.GetY();
	y	= m._12*Tmp.GetX() + m._22*Tmp.GetY();
}