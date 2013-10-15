#include <Sable\Gui\Layout\Layout.h>

#include <Sable\Gui\Layout\WidgetItem.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CLayout, CLayoutItem );

CLayout::CLayout():
	CLayoutItem()
{
}

CLayout::~CLayout()
{
}

const CVector2i& CLayout::GetSize() const
{
	return m_Size;
}

Void CLayout::SetSize( const CVector2i& s )
{
	m_Size = s;
}

Void CLayout::SetVSizePolicy( ESizePolicy p )
{
	m_VSizePolicy = p;
}

Void CLayout::SetHSizePolicy( ESizePolicy p )
{
	m_HSizePolicy = p;
}

Void CLayout::SetStretchFactor( const CVector2i& s )
{
	m_StretchFactor = s;
}

ESizePolicy CLayout::GetHSizePolicy() const
{
	return m_HSizePolicy;
}

ESizePolicy CLayout::GetVSizePolicy() const
{
	return m_VSizePolicy;
}

const CVector2i& CLayout::GetStretchFactor() const
{
	return m_StretchFactor;
}

Void  CLayout::SetPositionAndSize( const CVector2i& pos, const CVector2i& size )
{
    Apply( pos, size );
}

Void  CLayout::AddLayout( CLayout& layout )
{
    AddChild( layout );
}

Void  CLayout::AddWidget( CWidget& widget )
{
    CLayoutWidgetItem* item = NEWOBJ( CLayoutWidgetItem, ( widget ) );
    AddChild( *item );
}