#include <Sable\Gui\Widget\Widget.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CWidget, CNode );

CWidget::CWidget( ) :
	CNode( )
{
    m_Depth = 0;
	m_ChildCount = 0;

    m_Size = CVector2i( 32, 32 );
	m_Position = CVector2i( 0, 0 );
	m_StretchFactor = CVector2i( 1, 1 );

    m_HasFocus = FALSE;

	m_Show = TRUE;

}

CWidget::~CWidget()
{
}


Void CWidget::OnAddChild( CWidget& child )
{

}

Void CWidget::SendEvent( CWidgetEvent& event )
{
	OnEvent( event );
}

Bool CWidget::Serialize( CPersistentArchive& ar )
{
    UInt32 i;
    UInt32 childCount = GetChildCount();
    Int16 version = 0;

    if( ar.BeginScope( WT("CWidget"), version ) == version )
    {
        ar.Serialize( m_Position, WT("Pos") );
        ar.Serialize( m_Size, WT("Size") );
        ar.Serialize( m_Show, WT("Show") );
        ar.Serialize( m_Depth, WT("Depth") );
        ar.Serialize( m_CustomShader, WT("Shader") );
 
        ar.EndScope();
    }

    return CNode::Serialize( ar );
}

CWidget& CWidget::SetDepth( UInt32 d, Bool recursive )
{
    m_Depth = d;
	if( recursive )
	{
		CNode* child = GetChild();
		while( child )
		{
			if( child->GetTypeInfo().IsKindOf( CWidget::GetStaticTypeInfo() ) )
			{
				((CWidget*)child)->SetDepth( m_Depth + 1, recursive );
			}
			child = child->GetSibling();
		}
	}

	return *this;
}

UInt32 CWidget::GetDepth() const
{
    return m_Depth;
}

Void CWidget::Render(CRenderer& renderer, CShader& shader)
{
}

CLayout* CWidget::GetLayout() const
{
    return m_Layout;
}

Void CWidget::SetLayout( CLayout* layout )
{
    m_Layout = layout;
}

const CVector2i& CWidget::GetSize() const
{
    return m_Size;
}

const CVector2i& CWidget::GetPosition() const 
{
    return m_Position;
}

Bool CWidget::IsVisible() const
{
    return m_Show;
}

Void CWidget::SetFocus(const Bool focus)
{
	m_HasFocus = focus;
}

Bool CWidget::HasFocus()const
{
	return m_HasFocus;
}

Void CWidget::OnMove( const CVector2i& pos  )
{

}

Void CWidget::OnResize( const CVector2i& pos )
{

}

Void CWidget::OnCursorEnter( CWidgetEvent& event )
{
	SignalMouseEnter( event );
	event.Skip();
}

Void CWidget::OnCursorLeave( CWidgetEvent& event )
{
	SignalMouseLeave( event );
	event.Skip();
}

Void CWidget::OnCursorMove( CWidgetEvent& event )
{
}

Void CWidget::OnCursorBtnUp( CWidgetEvent& event )
{
	SignalMouseBtnUp( event );
}

Void CWidget::OnCursorBtnDown( CWidgetEvent& event )
{
	SignalMouseBtnDown( event );
}

Void CWidget::OnEvent( CWidgetEvent& event )
{
	CNode* child = GetChild();

	if( event.GetIsSkiped() || !IsVisible() )
		return;

	if( event.GetType() == CWidgetEvent::nType_CursorDown )
	{
		if( IsInside( event.GetCursorPos() ) && IsVisible() ) 
		{
			OnCursorBtnDown( event );
		}
	}
	else if( event.GetType() == CWidgetEvent::nType_CursorUp )
	{
		if( IsInside( event.GetCursorPos() ) && IsVisible() ) 
		{
			OnCursorBtnUp( event );
		}
	}
	else if( event.GetType() == CWidgetEvent::nType_CursorMove )
	{
		if( IsInside(event.GetCursorPos()) && !HasFocus()) 
		{
			SetFocus(TRUE);
			CWidgetEvent enterEvent( CWidgetEvent::nType_CursorEnter, event.GetCursorPos(), event.GetData() );
			OnCursorEnter( enterEvent );
		} 
		else if( !IsInside(event.GetCursorPos()) && HasFocus() ) 
		{
			SetFocus(FALSE);
			CWidgetEvent leaveEvent( CWidgetEvent::nType_CursorLeave, event.GetCursorPos(), event.GetData() );
			OnCursorLeave( leaveEvent );
		} 
		else if( IsInside(event.GetCursorPos() ) && HasFocus()) 
		{
			OnCursorMove( event );
		}
	}

	while( child && !event.GetIsSkiped() )
	{
		CWidget* w = child->CastTo<CWidget>();
		if( w )
			w->OnEvent( event );

		child = child->GetSibling();
	}
}

CWidget& CWidget::SetPosition( const CVector2i& pos )
{
    CVector2i tmp = m_Position;
    m_Position = pos;

    OnMove( tmp );

	return *this;
}

CWidget& CWidget::SetSize( const CVector2i& size )
{
    CVector2i tmp = m_Size;
    m_Size = size;

    OnResize(m_Size);

	return *this;
}

const CVector2i& CWidget::GetStretchFactor() const
{
	return m_StretchFactor;
}

ESizePolicy CWidget::GetVSizePolicy() const
{
	return m_VSizePolicy;
}

ESizePolicy CWidget::GetHSizePolicy() const
{
	return m_HSizePolicy;
}

Void CWidget::SetVSizePolicy( ESizePolicy p )
{
	m_VSizePolicy = p;
}

Void CWidget::SetHSizePolicy( ESizePolicy p )
{
	m_HSizePolicy = p;
}

CWidget& CWidget::SetStretchFactor( const CVector2i& size )
{
	CVector2i tmp = m_StretchFactor;
	m_StretchFactor = size;

	return *this;
}

Bool CWidget::Update( )
{
    if( m_Layout )
    {
        m_Layout->Apply( GetPositionRecursive(), GetSize() );
    }

	return CNode::Update();
}

Bool CWidget::IsInside(const CVector2i& pos)
{
    return GetRect().IsInside( pos );
}               

CVector2i CWidget::GetPositionRecursive() const
{
	CVector2i p;
	if( GetParent() == NULL )
	{
		p = m_Position;
	}
	else 
	{
		CWidget* w = GetParent()->CastTo<CWidget>();
		if( w )
		{
			p = w->GetPositionRecursive() + m_Position;
		}
		else
		{
			p = m_Position;
		}
	}
	return p;
}

CRect2Di CWidget::GetRect( ) const
{
	CRect2Di rect;

	rect.SetPosition( GetPositionRecursive() + m_Size / 2 );

	rect.SetSize( m_Size );

	return rect;
}

Void CWidget::Show( Bool b )
{
    m_Show = b;
}

CWidget& CWidget::SetCustomShader( const CShader* shader )
{
	m_CustomShader = shader;
	return *this;
}

CWidget& CWidget::SetCustomVB( const CGeometryVertexBuffer* vb )
{
	m_CustomVB = vb;
	return *this;
}

CShader* CWidget::GetCustomShader( ) const
{
	return m_CustomShader;
}

CGeometryVertexBuffer* CWidget::GetCustomVB( ) const
{
	return m_CustomVB;
}

CWidget& CWidget::SetColor( const CColor& col )
{
	return *this;
}