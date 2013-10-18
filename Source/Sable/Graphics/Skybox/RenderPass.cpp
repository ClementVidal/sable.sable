#include <Sable/Graphics/Skybox/RenderPass.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CSkyboxRenderPass );


CSkyboxRenderPass::CSkyboxRenderPass( CRenderer& renderer ):
    CRenderPass( renderer )
{
	m_Skybox = NULL;
}

CSkyboxRenderPass::~CSkyboxRenderPass()
{
}

CSkybox& CSkyboxRenderPass::GetSkybox() const
{
	return *m_Skybox;
}

Void CSkyboxRenderPass::Initialize(CRenderer &renderer, CRenderTarget* outputRenderTarget)
{
    CRenderPass::Initialize( renderer, outputRenderTarget);

	CStatesDepthStencil::SDesc dsDesc;
	dsDesc.DepthTestEnable = FALSE;
	dsDesc.DepthWriteEnable = FALSE;
	m_DepthStates.Acquire( dsDesc );
}

Void CSkyboxRenderPass::SetSkybox( CSkybox& skyBox )
{
    m_Skybox = &skyBox;
}

Bool CSkyboxRenderPass::ProcessTraversedNode( CNode& node, CRenderer& renderer )
{
	return TRUE;
}

Void CSkyboxRenderPass::Render( CRenderer& renderer )
{
	DebugGraphicCommandGroup( "CSkyboxRenderPass::Render" );

	renderer.Activate( m_DepthStates );

	if( m_Skybox )
		m_Skybox->Render( renderer );

}
