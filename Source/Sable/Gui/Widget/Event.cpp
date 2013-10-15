#include <Sable\Gui\Widget\Event.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CWidgetEvent, CManagedObject );

CWidgetEvent::CWidgetEvent( EType type, const CVector2i& pos, UInt32 data, CWidget* source )
{
   m_Type = type;
   m_Skip = FALSE;
   m_CursorPos = pos;
}

CWidgetEvent::~CWidgetEvent()
{
}

Bool CWidgetEvent::GetIsSkiped() const
{
	return m_Skip;
}

CWidgetEvent::EType CWidgetEvent::GetType() const
{
	return m_Type;
}

UInt32	CWidgetEvent::GetData() const
{
	return m_Data;
}

const CVector2i&	CWidgetEvent::GetCursorPos() const
{
	return m_CursorPos;
}

Void CWidgetEvent::Skip() 
{
	m_Skip = TRUE;
}