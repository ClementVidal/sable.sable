#include <Sable/Core/Geometry/Rect2Df.h>

#include <Sable/Core/Geometry/Rect2Di.h>
#include <Sable/Core/Math/Primitives.h>

using namespace Sable;

CRect2Df::CRect2Df()
{

}

CRect2Df::CRect2Df( const CRect2Di& other )
{
	m_Position = CVector2f( other.GetPosition() );
	m_Size = CVector2f( other.GetSize() );
}

const CVector2f& CRect2Df::GetPosition() const
{
	return m_Position;
}

const CVector2f& CRect2Df::GetSize() const
{
	return m_Size;
}

/**
Initialize the rect using two points.
*/
Void CRect2Df::SetFromTwoPoints( const CVector2f& a, const CVector2f& b )
{
	m_Position = ( a + b ) / 2.0f;
	m_Size = CVector2f( MathAbs( a.GetX() - b.GetX() ), MathAbs( a.GetY() - b.GetY() ) );
}

CVector2f CRect2Df::GetUpperLeftCorner() const
{
    return GetCorner( 0 );
}

CVector2f CRect2Df::GetUpperRightCorner() const
{
    return GetCorner( 1 );
}

CVector2f CRect2Df::GetLowerRightCorner() const
{
	return GetCorner( 2 );
}

CVector2f CRect2Df::GetLowerLeftCorner() const
{
    return GetCorner( 3 );
}


CVector2f CRect2Df::GetCorner( UInt32 i ) const
{
	//UpperLeftCorner
	if( i == 0 )
	{
		return CVector2f( m_Position.GetX() - m_Size.GetX() / 2.0f, m_Position.GetY() + m_Size.GetY() / 2.0f );
	}
	//UpperRightCorner
	else if( i == 1 )
	{
		return CVector2f( m_Position.GetX() + m_Size.GetX() / 2.0f, m_Position.GetY() + m_Size.GetY() / 2.0f );
	}
	//LowerRightCorner
	else if( i == 2 )
	{
		return CVector2f( m_Position.GetX() + m_Size.GetX() / 2.0f, m_Position.GetY() - m_Size.GetY() / 2.0f );
	}
	//LowerLeftCorner
	else if( i == 3 )
	{
		return CVector2f( m_Position.GetX() - m_Size.GetX() / 2.0f, m_Position.GetY() - m_Size.GetY() / 2.0f );
	}

	return CVector2f::Zero;
}

Bool CRect2Df::IsInside( const CVector2f& point ) const
{
    if( !IsEmpty() )
    {
		if( !MathIsInRangeInclusive( point.GetX(), m_Position.GetX() - m_Size.GetX() / 2.0f, m_Position.GetX() + m_Size.GetX() / 2.0f ) )
            return FALSE;

		if( !MathIsInRangeInclusive( point.GetY(), m_Position.GetY() - m_Size.GetY() / 2.0f, m_Position.GetY() + m_Size.GetY() / 2.0f ) )
			return FALSE;

		return TRUE;

    }
	return FALSE;
}

Void CRect2Df::Contract( Float32 x, Float32 y )
{
    Contract( CVector2f( x, y ) ) ;
}

Void CRect2Df::Inflate( Float32 x, Float32 y )
{
    Inflate( CVector2f( x, y ) ) ;
}

Void CRect2Df::Inflate( const CVector2f& v )
{
	m_Size += v * 2.0f;
}

Void CRect2Df::Contract( const CVector2f& v )
{
	m_Size -= v * 2.0f;
}


Bool CRect2Df::IsEmpty() const
{
    return m_Size.GetX() == 0.0f && m_Size.GetY() == 0.0f;
}

Void CRect2Df::SetEmpty()
{
    m_Size.SetX( 0.0f );
    m_Size.SetY( 0.0f );
}