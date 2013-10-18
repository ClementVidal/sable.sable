#include <Sable/Gui/Widget/Frame.h>

#include <Sable/Gui/Common/Header.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CWidgetFrame, CWidget );

CWidgetFrame::CWidgetFrame( ) :
	CWidget( )
{
    m_Color = CColor( 1.0f, 1.0f, 1.0f, 1.0f );
}

CWidgetFrame::~CWidgetFrame()
{
}

Bool CWidgetFrame::Serialize( CPersistentArchive& ar )
{
    Int16 version = 0;

    if( ar.BeginScope( WT("CWidgetFrame"), version ) == version )
    {
        ar.Serialize( m_Color, WT("Color") );
        ar.Serialize( m_Texture, WT("Texture") );
        ar.Serialize( m_TextureSize, WT("TextureSize") );
        ar.Serialize( m_TextureOrigin, WT("TextureOrigin") );

        ar.EndScope();
    }

    return CWidget::Serialize( ar );
}

Void CWidgetFrame::SetTexture( CTexture2D* texture )
{
    m_Texture = texture;
}

CWidget& CWidgetFrame::SetColor( const CColor& col )
{
    m_Color = col;
	return *this;
}

Void CWidgetFrame::SetTextureSize( const CVector2f& s )
{
	m_TextureSize = s;
}

Void CWidgetFrame::SetTextureOrigin( const CVector2f& o )
{
	m_TextureOrigin = o;
}

Void CWidgetFrame::Render(CRenderer& renderer, CShader& shader)
{
	CGuiRenderPass& uiPass = *renderer.GetGuiRenderPass();

    if( m_Texture )
    {
        shader.GetParameter("UseTexture")->SetValue( (Bool) TRUE );
        shader.GetParameter("Texture")->SetValue( *m_Texture );
    }
    else
    {
        shader.GetParameter("UseTexture")->SetValue( (Bool) FALSE );
    }

	shader.GetParameter("TextureSize")->SetValue( m_TextureSize );
	shader.GetParameter("TextureOrigin")->SetValue( m_TextureOrigin );

    const CColor& col = m_Color;
    uiPass.DrawQuad(shader, GetRect(), col);

    CWidget::Render(renderer, shader);
}

CColor& CWidgetFrame::GetColor()
{
    return m_Color;
}
