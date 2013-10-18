#include <Sable/Graphics/PostProcess/PostProcess.h>

#include <Sable/Graphics/Renderer/Renderer.h>
#include <Sable/Graphics/RenderPass/RenderPass.h>
#include <Sable/Graphics/RenderTarget/RenderTarget.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CPostProcess, CRenderPass );

CPostProcess::CPostProcess( CRenderer& renderer ):
    CRenderPass( renderer )
{
    m_Renderer = &renderer;
}

CPostProcess::~CPostProcess()
{

}

Void CPostProcess::Render( CRenderer& renderer )
{
}


/**
Initialize the post process.
<br> Each post process is binded to a CRenderTarget which is used as it's output.
\param renderer The renderer where this post process gonna be used.
\param outputRenderTarget the output render target. If NULL is specified,  we use the output render target of the renderer
*/
Void CPostProcess::Initialize( CRenderer& renderer, CRenderTarget* outputRenderTarget )
{
    CRenderPass::Initialize( renderer, outputRenderTarget );
}

Void CPostProcess::UnInitialize()
{

}