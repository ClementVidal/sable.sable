#include <Sable\Core\Math\Vector2i.h>

#include <Sable\Core\Persistent\Archive.h>

using namespace Sable;

CVector2i CVector2i::Zero = CVector2i( 0, 0 );

CVector2i::CVector2i()
{
	x = y =  0;
}

CVector2i::CVector2i( const CVector2i& other )
{
	x = other.GetX();
	y = other.GetY();
}

CVector2i::CVector2i( const CVector2f& other )
{
	x = (Int32) other.GetX();
	y = (Int32) other.GetY();
}

CVector2i::CVector2i( Int32 px, Int32  py)
{
	x = px;
	y = py;
}

Int32 CVector2i::GetX() const
{
    return x;
}

Int32 CVector2i::GetY() const
{
    return y;
}

Bool CVector2i::Serialize( CPersistentArchive& ar )
{
    ar.Serialize( x, WT("x") );
    ar.Serialize( y, WT("y") );
    return TRUE;
}

Float32 CVector2i::GetLength() const
{
	return MathSqrt( (Float32) (x*x + y*y) );
}

Void CVector2i::SetX( Int32 v )
{
    x = v;
}

Void CVector2i::SetY( Int32 v )
{
    y = v;
}

CVector2i CVector2i::operator-( ) const
{
    return CVector2i(-x,-y);
}

CVector2i CVector2i::operator+( const CVector2i& v) const
{
	return CVector2i(x+v.GetX(),y+v.GetY() );
}

CVector2i CVector2i::operator-( const CVector2i& v) const
{
	return CVector2i(x-v.GetX(),y-v.GetY() );
}

CVector2i CVector2i::operator*( const CVector2i& v) const
{
	return CVector2i(x*v.GetX(),y*v.GetY() );
}

CVector2i CVector2i::operator*( const Int32 v) const
{
	return CVector2i(x*v,y*v);
}

CVector2i CVector2i::operator/( const CVector2i& v) const
{
	return CVector2i(x/v.GetX(),y/v.GetY() );
}

CVector2f CVector2i::operator/( const CVector2f& v) const
{
	return CVector2f((Float32)x/v.GetX(),(Float32)y/v.GetY() );
}

CVector2i CVector2i::operator/( const Int32 v) const 
{
	return CVector2i(x/v,y/v);
}

CVector2i CVector2i::operator-( const Int32 v) const 
{
	return CVector2i(x-v,y-v);
}

CVector2i& CVector2i::operator=( const CVector2i& other )
{
	x = other.GetX();
	y = other.GetY();
	return *this;
}

CVector2i& CVector2i::operator+=( const CVector2i& v)
{
    x += v.GetX();
    y += v.GetY();
    return *this;
}

CVector2i& CVector2i::operator-=( const CVector2i& v)
{
    x -= v.GetX();
    y -= v.GetY();
    return *this;
}

CVector2i& CVector2i::operator*=( const CVector2i& v)
{
    x *= v.GetX();
    y *= v.GetY();
    return *this;
}

CVector2i& CVector2i::operator/=( const CVector2i& v)
{
    x /= v.GetX();
    y /= v.GetY();
    return *this;
}


//Destructeur
CVector2i::~CVector2i()
{
}

Bool CVector2i::operator==( const CVector2i& V ) const
{
	if((x == V.GetX() ) && (y == V.GetY() ) )
		return TRUE;

	return FALSE;
}

Bool CVector2i::operator!=( const CVector2i& V ) const
{
	if((x != V.GetX() ) || (y != V.GetY() ) )
		return TRUE;

	return FALSE;
}

Void	CVector2i::Set( const Int32 px, const Int32  py)
{
	x = px;
	y = py;

}