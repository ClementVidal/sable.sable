#include <Sable\Gui\Widget\Canvas.h>

#include <Sable\Gui\Common\Header.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CWidgetCanvas, CWidget );

CWidgetCanvas::CWidgetCanvas() :
	CWidget( )
{
    m_Color = CColor( 1.0f, 1.0f, 1.0f, 1.0f );
}

CWidgetCanvas::~CWidgetCanvas()
{
}

Bool CWidgetCanvas::Serialize( CPersistentArchive& ar )
{
    Int16 version = 0;

    if( ar.BeginScope( WT("CWidgetCanvas"), version ) == version )
    {
        ar.Serialize( m_Color, WT("Color") );
        ar.Serialize( m_NinePatch, WT("NinePatch") );

        ar.EndScope();
    }

    return CWidget::Serialize( ar );
}

Void CWidgetCanvas::SetNinePatch( CGuiNinePatch* texture )
{
    m_NinePatch = texture;
}

CWidget& CWidgetCanvas::SetColor( const CColor& col )
{
    m_Color = col;
	return *this;
}

Void CWidgetCanvas::Render(CRenderer& renderer, CShader& shader)
{
	CGuiRenderPass& uiPass = *renderer.GetGuiRenderPass();

    if( m_NinePatch )
    {
        shader.GetParameter("UseTexture")->SetValue( (Bool) TRUE );
//        shader.GetParameter("Texture")->SetValue( *m_NinePatch );
    }
    else
    {
        shader.GetParameter("UseTexture")->SetValue( (Bool) FALSE );
    }

    const CColor& col = m_Color;
    uiPass.DrawQuad(shader, GetRect(), col);

    CWidget::Render(renderer, shader);
}

CColor& CWidgetCanvas::GetColor()
{
    return m_Color;
}
