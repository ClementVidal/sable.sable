#include <Sable/Core/Math/Complex.h>

using namespace Sable;

CComplex::CComplex()
{
	m_Real = m_Img =  0;
}

CComplex::CComplex( const CComplex& other )
{
	m_Real = other.GetReal();
	m_Img = other.GetImg();
}

CComplex::CComplex( const Float32 px, const Float32  py)
{
	m_Real = px;
	m_Img = py;
}

CComplex::~CComplex()
{
}

Float32 CComplex::GetReal() const
{
    return m_Real;
}

Float32 CComplex::GetImg() const
{
    return m_Img;
}

Void CComplex::SetReal( Float32 v )
{
    m_Real = v;
}

Void CComplex::SetImg( Float32 v )
{
    m_Img = v;
}

Void	CComplex::Set( const Float32 px, const Float32  py)
{
	m_Real = px;
	m_Img = py;
}

CComplex    CComplex::operator+( const CComplex& v) const 
{
	return CComplex( GetReal() + v.GetReal(), GetImg() + v.GetImg());
}

CComplex    CComplex::operator-( const CComplex& v) const
{
	return CComplex( GetReal() - v.GetReal(), GetImg() - v.GetImg());
}

CComplex    CComplex::operator*( const CComplex& v) const 
{
	Float32 r  = m_Real*v.GetReal() - m_Img*v.GetImg();
	Float32 i = m_Real*v.GetImg() + m_Img*v.GetReal();

	return CComplex( r, i );
}

Float32  CComplex::GetLength() const
{
	return MathSqrt( m_Real*m_Real + m_Img*m_Img );
}