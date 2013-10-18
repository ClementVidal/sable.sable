#include <Sable/Graphics/RenderPass/RenderPass.h>

#include <Sable/Graphics/Renderer/Renderer.h>
#include <Sable/Graphics/Material/Header.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CRenderPass );

CRenderPass::CRenderPass( CRenderer& renderer)
{
    m_Renderer = &renderer;
	m_IsEnabled = TRUE;
}

CRenderPass::~CRenderPass()
{
}

Bool CRenderPass::ProcessTraversedNode( CNode& node, CRenderer& renderer )
{
	DebugError( "Must be re implemented in sub classes" );
	return TRUE;
}

Void CRenderPass::Render( CRenderer& renderer )
{
	DebugError( "Must be re implemented in child class" );
}

/**
Initialize this render pass:
If outputRenderTarget == NULL, the output render target for this pass will be the renderer output render target.

This function also load and create the default shader.
*/
Void CRenderPass::Initialize( CRenderer& renderer, CRenderTarget* outputRenderTarget )
{
	SetRenderTarget( outputRenderTarget );
}

Void CRenderPass::UnInitialize( CRenderer& renderer )
{
}

Void CRenderPass::SetIsEnabled( Bool onOff )
{
	m_IsEnabled = onOff;
}

Bool CRenderPass::GetIsEnabled() const
{
	return m_IsEnabled;
}