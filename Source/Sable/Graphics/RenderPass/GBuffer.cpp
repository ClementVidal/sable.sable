#include <Sable\Graphics\RenderPass\GBuffer.h>

#include <Sable\Graphics\RenderTarget\Texture.h>
#include <Sable\Graphics\Debug\GraphicCommandGroup.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CRenderPassGBuffer, CRenderPass );

CRenderPassGBuffer::CRenderPassGBuffer( CRenderer& renderer ):
    CRenderPass(renderer)
{
}

CRenderPassGBuffer::~CRenderPassGBuffer()
{
}

Bool CRenderPassGBuffer::ProcessTraversedNode( CNode& node, CRenderer& renderer )
{
	Index index;
    const CTypeInfo& nodeType = node.GetTypeInfo();

    if( nodeType.IsKindOf( CNodeRender::GetStaticTypeInfo() ) ) 
	{
        CNodeRender& nodeRenderable = (CNodeRender&) node;

		if( nodeRenderable.GetModel() == NULL )
			return TRUE;

        CGeometryModel& model = *nodeRenderable.GetModel();

		if( nodeRenderable.GetAttribute( CNode::nAttribute_DoNotRenderToDepthBuffer ) )
	        return TRUE;

        for( index = 0; index < model.GetSubsetCount(); index++ )
        {
	        CMaterial* material = model.GetSubset( index ).Material;
	//		if( material == NULL )
	//			material = &GetDefaultMaterial();

			CRenderQueueEntry& renderEntry = GetRenderQueue().LockEntry();

	/*		if( nodeRenderable.GetModel()->GetTypeInfo().IsKindOf( CGeometryModelInstance::GetStaticTypeInfo() ) )
				renderEntry.SetShader( m_InstancingShader );
			else
				renderEntry.SetShader( m_StandardShader );
*/
			renderEntry.SetVertexBuffer( nodeRenderable.GetModel()->GetSubset( index ).Mesh->GetVertexBuffer() );
			renderEntry.SetIndexBuffer( nodeRenderable.GetModel()->GetSubset( index ).Mesh->GetIndexBuffer() );

			GetRenderQueue().UnlockEntry();

        }
    }

	return TRUE;
}

Void CRenderPassGBuffer::Render( CRenderer& renderer )
{
	DebugProfile("CRenderPassGBuffer::Render");
	DebugGraphicCommandGroup( "CRenderPassGBuffer::Render" );

	GetRenderTarget()->Clear( CColor::Black );

	GetRenderQueue().Execute( renderer, *this );

}

Void CRenderPassGBuffer::Initialize( CRenderer& renderer, const CTextureInfo& info )
{
//	m_DepthTexture.Create( CRenderTargetInfo( info.Width, info.Height, info.Format, nMultiSamplingQuality_None ) );
/*
	m_InstancingShader.Load( CoreManager.GetFileSystem().GetFilePath( "System/Shader", "RendererPass/Depth/RendererDepthInstancing.fx" ) );

	m_StandardShader.Load( CoreManager.GetFileSystem().GetFilePath( "System/Shader", "RendererPass/Depth/RendererDepthStandard.fx" ) );

    m_BlendStates.SetBlendEnable( FALSE );
    m_DepthStates.SetDepthTestEnable( TRUE );
    m_DepthStates.SetDepthWriteEnable( TRUE );
    m_RasterizerStates.SetCullMode( nStateCullMode_CCW );
*/
//	LoadDefaultMaterial();
}

Void CRenderPassGBuffer::UnInitialize( CRenderer& renderer )
{
}
