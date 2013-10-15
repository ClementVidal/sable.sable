#include <Sable\Input\Mouse\Interface.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CMouseInterface );

CMouseInterface::CMouseInterface( CApplicationWindow& window )
{
	 m_ClampCoordinate = TRUE;
     m_AttachedWindow = &window;
}

CMouseInterface::~CMouseInterface()
{
}

Bool CMouseInterface::GetIsKeyDown( const EMouseEventData key ) const 
{
	return m_State.Buttons.GetBit( (UInt32) key ) ;
}

CApplicationWindow& CMouseInterface::GetAttachedWindow() const
{
    return *m_AttachedWindow;
}

CVector2f CMouseInterface::GetPosition() const
{
    CVector2f p( m_State.XPosition, m_State.YPosition );
    return p;
}

Void CMouseInterface::SetPosition( const CVector2f& pos )
{
	m_State.XPosition = pos.GetX();
	m_State.YPosition = pos.GetY();
}

Float32 CMouseInterface::GetYPosition( ) const
{
	return m_State.YPosition;
}

Float32 CMouseInterface::GetXPosition( ) const
{
	return m_State.XPosition;
}

Bool CMouseInterface::ClampCoordinate( ) const
{
	return m_ClampCoordinate;
}

Void CMouseInterface::ClampCoordinate( Bool onOff )
{
	m_ClampCoordinate = onOff;
}
