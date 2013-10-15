#include <Sable\Gui\Layout\WidgetItem.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CLayoutWidgetItem, CLayoutItem );

CLayoutWidgetItem::CLayoutWidgetItem( CWidget& widget ):
	CLayoutItem()
{
    m_Widget = &widget;
}

CLayoutWidgetItem::~CLayoutWidgetItem()
{
}

Void  CLayoutWidgetItem::SetPositionAndSize( const CVector2i& pos, const CVector2i& size )
{
    m_Widget->SetPosition( pos );
    m_Widget->SetSize( size );
}

CWidget& CLayoutWidgetItem::GetWidget() const
{
    return *m_Widget;
}

const CVector2i& CLayoutWidgetItem::GetSize()const
{
	return m_Widget->GetSize();
}

ESizePolicy CLayoutWidgetItem::GetVSizePolicy() const
{
	return m_Widget->GetVSizePolicy();
}

ESizePolicy CLayoutWidgetItem::GetHSizePolicy() const
{
	return m_Widget->GetHSizePolicy();
}

const CVector2i& CLayoutWidgetItem::GetStretchFactor() const
{
	return m_Widget->GetStretchFactor();
}