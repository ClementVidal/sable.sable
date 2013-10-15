#include <Sable\Core\Common\Color.h>

#include <Sable\Core\Persistent\Archive.h>
#include <Sable\Core\Math\Vector4f.h>

using namespace Sable;


CColor CColor::Red = CColor( 1.0f, 1.0f, 0.0f, 0.0f );
CColor CColor::Green = CColor( 1.0f, 0.0f, 1.0f, 0.0f );
CColor CColor::Blue = CColor( 1.0f, 0.0f, 0.0f, 1.0f );
CColor CColor::Yellow = CColor( 1.0f, 1.0f, 1.0f, 0.0f );
CColor CColor::Black = CColor( 1.0f, 0.0f, 0.0f, 0.0f );
CColor CColor::White = CColor( 1.0f, 1.0f, 1.0f, 1.0f );
CColor CColor::Grey = CColor( 1.0f, 0.5f, 0.5f, 0.5f );

CColor::CColor()
{
	this->a = 1.0;
	this->r = 0;
	this->g = 0;
	this->b = 0;
}

CColor::CColor(const Float32 a, const Float32 r, const Float32 g, const Float32 b)
{
	this->a = a;
	this->r = r;
	this->g = g;
	this->b = b;
}

CColor::CColor(const Float32 r, const Float32 g, const Float32 b)
{
	this->a = 1.0f;
	this->r = r;
	this->g = g;
	this->b = b;
}


CColor::CColor( const CColor& other)
{
	this->a = other.a;
	this->r = other.r;
	this->g = other.g;
	this->b = other.b;
}

CColor& CColor::operator=( const CColor& other )
{
	this->a = other.a;
	this->r = other.r;
	this->g = other.g;
	this->b = other.b;

	return *this;
}

Bool CColor::operator==( const CColor& other )
{
    return ( r == other.r ) && ( g == other.g ) && ( b == other.b ) &&( a == other.a );
}

Bool CColor::operator!=( const CColor& other )
{
    return ( r != other.r ) || ( g != other.g ) || ( b != other.b ) || ( a != other.a );
}

Bool CColor::operator<=( const CColor& other )
{
	return ( r <= other.r ) && ( g <= other.g ) && ( b <= other.b ) && ( a <= other.a );
}

CColor& CColor::operator= ( UInt32 value )
{
	SetFromUInt32Color( value );
	return *this;
}

CColor CColor::operator*( Float32 v) const
{
	return CColor(a*v, r*v, g*v, b*v);
}

CColor CColor::operator*( const CColor& v) const 
{
	return CColor(a*v.a, r*v.r, g*v.g, b*v.b);
}

CColor CColor::operator+( const CColor& v) const 
{
	return CColor(a+v.a, r+v.r, g+v.g, b+v.b);
}

CColor CColor::operator-( const CColor& v) const 
{
	return CColor(a-v.a, r-v.r, g-v.g, b-v.b);
}

CColor CColor::operator+( Float32 v) const 
{
	return CColor(a+v, r+v, g+v, b+v);
}
Float32& CColor::operator[]( UInt32 i) const
{
    DebugAssert( i < 4 );
    return ((Float32*)this)[i];
}

CColor::~CColor()
{
}

Void CColor::SetFromUInt32Color( const UInt32 value )
{
	a = ( ( value & 0xff000000 ) >> 24 ) / 255.0f ;
	r = ( ( value & 0x00ff0000 ) >> 16 ) / 255.0f ;
	g = ( ( value & 0x0000ff00 ) >> 8 ) / 255.0f ;
	b = ( ( value & 0xff0000ff ) >> 0 ) / 255.0f ;
}

void CColor::Set(const Float32 a, const Float32 r, const Float32 g, const Float32 b)
{
	this->a = a;
	this->r = r;
	this->g = g;
	this->b = b;
}

Bool CColor::Serialize( CPersistentArchive& ar )
{
    UInt16 version = 0;

    ar.Serialize( a, WT("a") );
    ar.Serialize( r, WT("r") );
    ar.Serialize( g, WT("g") );
    ar.Serialize( b, WT("b") );

    return TRUE;
}

Void CColor::Normalize()
{
    a = (a<=1.0f)?a:1.0f;
    r = (r<=1.0f)?r:1.0f;
    g = (g<=1.0f)?g:1.0f;
    b = (b<=1.0f)?b:1.0f;

	a = (a>=0.0f)?a:0.0f;
	r = (r>=0.0f)?r:0.0f;
	g = (g>=0.0f)?g:0.0f;
	b = (b>=0.0f)?b:0.0f;
}

UInt32  CColor::GetUInt32Color() const
{
	UInt32  Col =0;

	UInt32	aComp = (UInt32)(a*255) << 24;
	UInt32	rComp = (UInt32)(r*255)	<< 16;
	UInt32	gComp = (UInt32)(g*255) <<	8;
	UInt32	bComp = (UInt32)(b*255) <<	0;

	Col = aComp | rComp | gComp | bComp;
	return Col;
}

CColor& CColor::operator+=( const CColor& v)
{
	r += v.r;
	g += v.g;
	b += v.b;
	a += v.a;
	return *this;
}

CColor& CColor::operator+=( const CVector4f& v)
{
	r += v.GetX();
	g += v.GetY();
	b += v.GetZ();
	a += v.GetW();
	return *this;
}

Void CColor::SetR( Float32 c )
{
    r = c;
}

Void CColor::SetG( Float32 c )
{
    g = c;
}

Void CColor::SetB( Float32 c )
{
    b = c;
}

Void CColor::SetA( Float32 c )
{
    a = c;
}

Float32 CColor::GetR( ) const
{
    return r;
}

Float32 CColor::GetG( ) const
{
    return g;
}

Float32 CColor::GetB( ) const
{
    return b;
}

Float32 CColor::GetA( ) const
{
    return a;
}