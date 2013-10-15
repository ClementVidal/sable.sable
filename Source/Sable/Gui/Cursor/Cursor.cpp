#include <Sable\Gui\Cursor\Cursor.h>

#include <stdio.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CCursor );

CCursor::CCursor()
{
	m_Texture.Load( CoreManager.GetFileSystem().GetFilePath( "System", "Texture/UserInterface/DefaultCursor.dds" ) );

    m_Shader.Load(  CoreManager.GetFileSystem().GetFilePath( "System/Shader", "RendererPass/UserInterface/DefaultCursor.vsh" ),
                    CoreManager.GetFileSystem().GetFilePath( "System/Shader", "RendererPass/UserInterface/DefaultCursor.psh" ),
                    CFilePath() );

	InitVertexBuffer();

	CStatesDepthStencil::SDesc dsDesc;
	dsDesc.DepthTestEnable = FALSE;
    m_DepthStates.Acquire( dsDesc );

	CStatesBlend::SDesc blendDesc;
	blendDesc.BlendEnable[0] = TRUE;
	blendDesc.SrcColorBlend = nStateBlend_SrcAlpha;
	blendDesc.DstColorBlend = nStateBlend_InvSrcAlpha;
	m_BlendStates.Acquire( blendDesc );

	CStatesSampler::SDesc samplerDesc;
	samplerDesc.MagFilter = nStateFilter_Point;
	samplerDesc.MinFilter = nStateFilter_Point;
	m_SamplerStates.Acquire( samplerDesc );

}

CCursor::~CCursor()
{
}

Void CCursor::SetPosition( const CVector2f& pos )
{
    m_Position = pos;
}

Void CCursor::InitVertexBuffer()
{
	SVertex streamData[ 4 ];

	streamData[ 0 ].Position = CVector3f( -1.0f, 1.0f, 0.0f );
	streamData[ 1 ].Position = CVector3f(  1.0f, 1.0f, 0.0f );
	streamData[ 2 ].Position = CVector3f( -1.0f, -1.0f, 0.0f );
	streamData[ 3 ].Position = CVector3f(  1.0f, -1.0f, 0.0f );

	streamData[ 0 ].TexCoord0 = CVector2f( 0.0f, 0.0f );
	streamData[ 1 ].TexCoord0 = CVector2f( 1.0f, 0.0f );
	streamData[ 2 ].TexCoord0 = CVector2f( 0.0f, 1.0f );
	streamData[ 3 ].TexCoord0 = CVector2f( 1.0f, 1.0f );

	m_VertexLayout.AddElement( nVertexComponent_Position, nVertexComponentType_Float3 );
	m_VertexLayout.AddElement( nVertexComponent_TexCoord0, nVertexComponentType_Float2 );
	m_VertexLayout.Initialize();

	m_VertexBuffer.SetRawData( 4, sizeof( SVertex ), ( Byte* ) streamData );

	m_VertexBuffer.Load( );
}

Void CCursor::Activate(CRenderer& renderer)
{
	CGuiRenderPass& uiPass = *renderer.GetGuiRenderPass();

    // A calculer pour recentrer le curseur
    CVector2f offset = CVector2f( 7, -18 );

	m_Shader.GetParameter("CursorOffset")->SetValue( offset );
	m_Shader.GetParameter("CursorPosition")->SetValue(m_Position );
	m_Shader.GetParameter("CursorSize")->SetValue( CVector2f( 32, 32 ));
	m_Shader.GetParameter("Texture")->SetValue( m_Texture );
	CShaderParameter* p = m_Shader.GetParameter("Sampler");
	if( p )
		m_Shader.GetParameter("Sampler")->SetValue( m_SamplerStates );

	renderer.GetCurrentViewport()->GetShaderConnector().FlushParametersValues( m_Shader );

    renderer.Activate( m_Shader );
	renderer.Activate( m_VertexBuffer, 0 );
	renderer.Activate( m_VertexLayout );

    renderer.Activate( m_BlendStates );
    renderer.Activate( m_DepthStates );
}

Void CCursor::Render(CRenderer& renderer)
{
    DebugGraphicCommandGroup( "CCursor::Render" );

	Activate(renderer);
	
	renderer.Draw(nPrimitiveType_TriangleStrip, m_VertexBuffer.GetVertexCount(), 0 );
}
