#include <Sable\Gui\Widget\Text.h>

#include <Sable\Graphics\Text\Font.h>
#include <Sable\Graphics\Text\Text.h>

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CWidgetText, CWidget );

CWidgetText::CWidgetText( const CTextFont& font, UInt32 capacity):
    CWidget( ),
    m_Text( font, capacity )
{
	m_HAlign = nHAlign_Center;
	m_VAlign = nVAlign_Center;
	SetCustomShader( &m_Text.GetFont().GetShader() );
	SetCustomVB( &m_Text.GetVertexBuffer() );
}

CWidgetText::CWidgetText( ):
	CWidget( ),
	m_Text( )
{
	m_HAlign = nHAlign_Center;
	m_VAlign = nVAlign_Center;
}

CWidgetText::~CWidgetText()
{

}

CWidgetText& CWidgetText::SetColor( const CColor& color )
{
    m_Text.SetColor( color );
	return *this;
}

CWidgetText& CWidgetText::SetCapacity( UInt32 c )
{
	m_Text.SetCapacity( c );
	return *this;
}

Void CWidgetText::Render(CRenderer& renderer, CShader& shader )
{
	CVector2f vpSize = renderer.GetCurrentViewport()->GetSize();
	CVector2f txtPos = GetTextPosition();
	m_Text.SetPosition( txtPos / vpSize );
    m_Text.Render( renderer );
	m_Size = m_Text.GetSize();
    CWidget::Render(renderer, shader);
}

Bool CWidgetText::Update( )
{
	// Force the update/or creation of the underlying vertex buffer.
	// This must be done here, because right after the UIRenderPass will activate the vertexbuffer
	// So the the VB MUST be created before it is activated.
	m_Text.UpdateBuffer( );

	return CWidget::Update();
}

CVector2i CWidgetText::GetTextPosition() const
{
	CVector2i widgetPos = GetRect().GetLowerLeftCorner();
	CVector2i widgetSize = GetRect().GetSize();
	CVector2i textSize = m_Text.GetSize();
/*
	if( m_VAlign == nVAlign_Center )
		widgetPos = widgetPos + CVector2f( 0.0f, widgetSize.GetY() / 2 - textSize.GetY() / 2 );
	else if( m_VAlign == nVAlign_Bottom )
		widgetPos = widgetPos + CVector2f( 0.0f, widgetSize.GetY() - textSize.GetY() );

	if( m_HAlign == nHAlign_Center )
		widgetPos = widgetPos + CVector2f( widgetSize.GetX() / 2 - textSize.GetX() / 2, 0.0f );
	else if( m_HAlign == nHAlign_Right )
		widgetPos = widgetPos + CVector2f( widgetSize.GetX() - textSize.GetX(), 0.0f  );
*/
	return widgetPos;
}

CWidgetText& CWidgetText::SetText( String string)
{
    m_Text.SetText( string );
	m_Size = m_Text.GetSize();
	return *this;
}

CWidgetText& CWidgetText::SetFontSize( Float32 s )
{
    m_Text.SetFontSize(s);
	return *this;
}

CWidgetText& CWidgetText::SetHAlign( EHAlign align )
{
	m_HAlign = align;
	return *this;
}

CWidgetText& CWidgetText::SetVAlign( EVAlign align )
{
	m_VAlign = align;
	return *this;
}

CWidgetText& CWidgetText::SetFont( const CTextFont& font )
{
	m_Text.SetFont( font );
	return *this;
}

Bool CWidgetText::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;
	UInt32 hAlign = (UInt32)m_HAlign;
	UInt32 vAlign = (UInt32)m_VAlign;

	if( ar.BeginScope( WT("WidgetText"), version ) == 0 )
	{
		ar.Serialize( m_Text, WT("Text") );
		ar.Serialize( hAlign, WT("HAlign") );
		ar.Serialize( vAlign, WT("VAlign") );

		if( ar.IsLoading() )
		{
			m_HAlign = (EHAlign)hAlign;
			m_VAlign = (EVAlign)vAlign;
		}

		ar.EndScope();
	}

	return CWidget::Serialize( ar );
}