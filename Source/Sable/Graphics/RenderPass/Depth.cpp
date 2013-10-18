#include <Sable/Graphics/RenderPass/Depth.h>

#include <Sable/Graphics/RenderTarget/Texture.h>
#include <Sable/Graphics/Debug/GraphicCommandGroup.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CRenderPassDepth, CRenderPass );

CRenderPassDepth::CRenderPassDepth( CRenderer& renderer ):
    CRenderPass(renderer)
{
    m_RenderDepthTexture = TRUE;
	SetRenderTarget( &m_DepthTexture );
}

CRenderPassDepth::~CRenderPassDepth()
{
}

Bool CRenderPassDepth::ProcessTraversedNode( CNode& node, CRenderer& renderer )
{
    const CTypeInfo& nodeType = node.GetTypeInfo();

    if( nodeType.IsKindOf( CNodeRender::GetStaticTypeInfo() ) ) 
	{
	    Index index;
        CNodeRender& nodeRenderable = (CNodeRender&)node;
		if( nodeRenderable.GetModel() == NULL )
			return TRUE;

        CGeometryModel& model = *nodeRenderable.GetModel();

        for( index = 0; index < model.GetSubsetCount(); index++ )
        {
	        CMaterial* material = model.GetSubset( index ).Material;
			if( material && material->IsOpaque() )
			{

				CRenderQueueEntry& renderEntry = GetRenderQueue().LockEntry();

				// Plus the material shaderconnector
				renderEntry.AddShaderConnector( *material );
				// Plus the node shaderconnector
				renderEntry.AddShaderConnector( nodeRenderable.GetShaderConnector() );
				// Plus the camera shaderConnector
				renderEntry.AddShaderConnector( renderer.GetView()->GetCamera()->GetShaderConnector() );
				// Plus the transform matrix shaderConnector
				renderEntry.ShaderConnectorTransformMatrix.Set( nodeRenderable, *renderer.GetView()->GetCamera() );
				renderEntry.AddShaderConnector( renderEntry.ShaderConnectorTransformMatrix );
				
				renderEntry.SetShader( &m_StandardShader );
				renderEntry.SetVertexLayout( nodeRenderable.GetModel()->GetSubset( index ).Mesh->GetVertexLayout() );
				renderEntry.SetVertexBuffer( nodeRenderable.GetModel()->GetSubset( index ).Mesh->GetVertexBuffer() );
				renderEntry.SetIndexBuffer( nodeRenderable.GetModel()->GetSubset( index ).Mesh->GetIndexBuffer() );
				renderEntry.SetStatesBlend( m_StandardShader.GetBlendStates() );
				renderEntry.SetStatesDepthStencil( m_StandardShader.GetDepthStencilStates() );
				renderEntry.SetStatesRasterizer( m_StandardShader.GetRasterizerStates() );

				renderEntry.SetPriority( nodeRenderable.GetRenderPriority() );

				GetRenderQueue().UnlockEntry();
			}		
        }
    }

	return TRUE;
}

CMaterial& CRenderPassDepth::GetDefaultMaterial()
{
	return m_DefaultMaterial;
}

Void CRenderPassDepth::LoadDefaultMaterial()
{
    m_DefaultMaterial.SetShader( &m_StandardShader );
}

Void CRenderPassDepth::Render( CRenderer& renderer )
{
	DebugProfile("CRenderPassDepth::Render");
	DebugGraphicCommandGroup( "CRenderPassDepth::Render" );

    renderer.Activate( m_BlendStates );
    renderer.Activate( m_RasterizerStates );
    renderer.Activate( m_DepthStates );

    GetRenderTarget()->Clear( CColor( 1.0f,1.0f,1.0f,1.0f ) );

	GetRenderQueue().Execute( renderer, *this );
}

Void CRenderPassDepth::SetRenderDepthTexture( const Bool renderDepthTexture )
{
	m_RenderDepthTexture = renderDepthTexture;
}

Bool CRenderPassDepth::GetRenderDepthTexture() const
{
	return m_RenderDepthTexture;
}

const CRenderTargetTexture& CRenderPassDepth::GetDepthTexture() const
{
	return m_DepthTexture;
}

Void CRenderPassDepth::Initialize( CRenderer& renderer, const CRenderTargetInfo& info )
{
	m_DepthTexture.Create( info );

#ifdef SETUP_IMPLTYPE_DIRECTX
    m_InstancingShader.Load(    CoreManager.GetFileSystem().GetFilePath( "System/Shader", "RendererPass/Depth/RendererDepthInstancing.vsh" ),
                                CoreManager.GetFileSystem().GetFilePath( "System/Shader", "RendererPass/Depth/RendererDepthInstancing.psh" ),
                                CFilePath() );
#endif

    m_StandardShader.Load(  CoreManager.GetFileSystem().GetFilePath( "System/Shader", "RendererPass/Depth/RendererDepthStandard.vsh" ),
                            CoreManager.GetFileSystem().GetFilePath( "System/Shader", "RendererPass/Depth/RendererDepthStandard.psh" ),
                            CFilePath() );

	CStatesBlend::SDesc blendDesc;
	blendDesc.BlendEnable[0] = FALSE;
	m_BlendStates.Acquire( blendDesc );

	CStatesDepthStencil::SDesc dsDesc;
	dsDesc.DepthTestEnable = TRUE;
	dsDesc.DepthWriteEnable = TRUE;
    m_DepthStates.Acquire( dsDesc );

	CStatesRasterizer::SDesc srDesc;
	srDesc.CullMode = nStateCullMode_CCW;
    m_RasterizerStates.Acquire( srDesc );

	LoadDefaultMaterial();
}

Void CRenderPassDepth::UnInitialize( CRenderer& renderer )
{
}


