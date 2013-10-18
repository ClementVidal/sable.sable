#include <Sable/Core/Geometry/Rect2Di.h>

#include <Sable/Core/Math/Primitives.h>

using namespace Sable;


CRect2Di::CRect2Di( )
{

}

CRect2Di::CRect2Di( Int32 x, Int32 y, Int32 w, Int32 h )
{
	m_Position.Set( x, y );
	m_Size.Set( w, h );
}

CRect2Di::CRect2Di( const CVector2i& pos, const CVector2i& size )
{
	m_Position = pos;
	m_Size = size;
}

/**
Initialize the rect using two points.
*/
Void CRect2Di::SetFromTwoPoints( const CVector2i& a, const CVector2i& b )
{
	m_Position = ( a + b ) / 2;
	m_Size = CVector2i( MathAbs( a.GetX() - b.GetX() ), MathAbs( a.GetY() - b.GetY() ) );
}


CVector2i CRect2Di::GetUpperLeftCorner() const
{
	return GetCorner( 0 );
}

CVector2i CRect2Di::GetUpperRightCorner() const
{
	return GetCorner( 1 );
}

CVector2i CRect2Di::GetLowerRightCorner() const
{
	return GetCorner( 2 );
}

CVector2i CRect2Di::GetLowerLeftCorner() const
{
	return GetCorner( 3 );
}

CVector2i CRect2Di::GetCorner( UInt32 i ) const
{
	CVector2i coef[] = {	CVector2i( -1, 1 ), CVector2i( 1, 1 ),
							CVector2i( 1, -1 ), CVector2i( -1, -1 ) };

	DebugAssert( i >= 0 && i < 4 );
	return CVector2i( m_Position.GetX() + coef[i].GetX() * m_Size.GetX() / 2, m_Position.GetY() + coef[i].GetY() * m_Size.GetY() / 2 );
}

Void CRect2Di::SetPosition( const CVector2i& p )
{
	m_Position = p;
}

Void CRect2Di::SetSize( const CVector2i& s )
{
	m_Size = s;
}

const CVector2i& CRect2Di::GetPosition() const
{
	return m_Position;
}

const CVector2i& CRect2Di::GetSize() const
{
	return m_Size;
}

Bool CRect2Di::IsInside( const CVector2i& point ) const
{
	if( !IsEmpty() )
	{
		if( !MathIsInRangeInclusive( point.GetX(), m_Position.GetX() - m_Size.GetX() / 2, m_Position.GetX() + m_Size.GetX() / 2 ) )
			return FALSE;

		if( !MathIsInRangeInclusive( point.GetY(), m_Position.GetY() - m_Size.GetY() / 2, m_Position.GetY() + m_Size.GetY() / 2 ) )
			return FALSE;

		return TRUE;

	}
	return FALSE;
}

Void CRect2Di::Contract( Int32 x, Int32 y )
{
    Contract( CVector2i( x, y ) ) ;
}

Void CRect2Di::Inflate( Int32 x, Int32 y )
{
    Inflate( CVector2i( x, y ) ) ;
}

Void CRect2Di::Inflate( const CVector2i& v )
{
	m_Size += v * 2;
}

Void CRect2Di::Contract( const CVector2i& v )
{
	m_Size -= v * 2;
}


Bool CRect2Di::IsEmpty() const
{
    return m_Size.GetX() == 0 && m_Size.GetY() == 0;
}

Void CRect2Di::SetEmpty()
{
    m_Size.SetX( 0 );
    m_Size.SetY( 0 );
}

void CRect2Di::Add( const CRect2Di& r )
{
	CVector2i a,b;

	CVector2i ul1 = GetUpperLeftCorner();
	CVector2i ul2 = r.GetUpperLeftCorner();
	CVector2i lr1 = GetLowerRightCorner();
	CVector2i lr2 = r.GetLowerRightCorner();

	a.Set(	ul2.GetX() < ul1.GetX() ? ul2.GetX() : ul1.GetX(),
			ul2.GetY() > ul1.GetY() ? ul2.GetY() : ul1.GetY() );
	
	b.Set(	lr2.GetX() > lr1.GetX() ? lr2.GetX() : lr1.GetX(),
			lr2.GetY() < lr1.GetY() ? lr2.GetY() : lr1.GetY() );
	
	SetFromTwoPoints( a, b );
}