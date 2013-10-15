#include <Sable\Graphics\RenderPass\Lighting.h>

#include <Sable\Graphics\Common\Manager.h>
#include <Sable\Graphics\Debug\GraphicCommandGroup.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CRenderPassLighting, CRenderPass );


CRenderPassLighting::CRenderPassLighting( CRenderer& renderer ):
    CRenderPass(renderer)
{
}

CRenderPassLighting::~CRenderPassLighting()
{
}

CMaterial& CRenderPassLighting::GetDefaultMaterial()
{
	return m_DefaultMaterial;
}

Void CRenderPassLighting::LoadDefaultMaterial()
{
	m_DefaultShader.Load(   CoreManager.GetFileSystem().GetFilePath( "System/Shader", "RendererPass/Default/Default.vsh" ),
                            CoreManager.GetFileSystem().GetFilePath( "System/Shader", "RendererPass/Default/Default.psh" ),
                            CFilePath() );

	m_DefaultMaterial.SetShader( &m_DefaultShader );
}

Bool CRenderPassLighting::ProcessTraversedNode( CNode& node, CRenderer& renderer )
{
    DebugProfile("CRenderPassLighting::ProcessTraversedNode");

    const CTypeInfo& nodeType = node.GetTypeInfo();

    if( nodeType.IsKindOf( CNodeRender::GetStaticTypeInfo() ) ) 
	{
        CNodeRender& nodeRenderable = (CNodeRender&)node;
		if( nodeRenderable.GetModel() == NULL || !nodeRenderable.GetIsVisible() )
			return TRUE;

        CGeometryModel& model = *nodeRenderable.GetModel();

        for( UInt32 index = 0; index < model.GetSubsetCount(); index++ )
        {
            CGeometryModel::SSubset& subset = model.GetSubset( index );
			CMaterial* material = subset.Material;
			if( material == NULL )
				material = &GetDefaultMaterial();

			CShader* shader = material->GetShader( );
			if( !shader )
				return TRUE;

			CRenderQueueEntry& renderEntry = GetRenderQueue().LockEntry();

			// Plus the material shaderconnector
			renderEntry.AddShaderConnector( *material );
			// Plus the node shaderConnector
			renderEntry.AddShaderConnector( nodeRenderable.GetShaderConnector() );
			// Plus the camera shaderConnector
			renderEntry.AddShaderConnector( renderer.GetView()->GetCamera()->GetShaderConnector() );
			// Plus the transform matrix shaderConnector
			renderEntry.ShaderConnectorTransformMatrix.Set( nodeRenderable, *renderer.GetView()->GetCamera() );
			renderEntry.AddShaderConnector( renderEntry.ShaderConnectorTransformMatrix );

            renderEntry.SetVertexLayout( subset.Mesh->GetVertexLayout() );
            renderEntry.SetVertexBuffer( subset.Mesh->GetVertexBuffer() );
			renderEntry.SetInstanceBuffer( nodeRenderable.GetInstanceBuffer() );
            renderEntry.SetIndexBuffer( subset.Mesh->GetIndexBuffer() );
			renderEntry.SetShader( shader );
            renderEntry.SetStatesBlend( shader->GetBlendStates() );
            renderEntry.SetStatesDepthStencil( shader->GetDepthStencilStates() );
            renderEntry.SetStatesRasterizer( shader->GetRasterizerStates() );

			renderEntry.SetPriority( nodeRenderable.GetRenderPriority() );

            GetRenderQueue().UnlockEntry();
        }
    }

	return TRUE;
}

Void CRenderPassLighting::Render( CRenderer& renderer )
{
	DebugProfile("CRenderPassLighting::Render");

	DebugGraphicCommandGroup( "CRenderPassLighting::Render" );

    renderer.Activate( m_DepthStates );

	GetRenderQueue().Execute( renderer, *this );

}

Void CRenderPassLighting::Initialize( CRenderer& renderer, CRenderTarget* outputRenderTarget )
{
    CRenderPass::Initialize( renderer, outputRenderTarget );

	CStatesDepthStencil::SDesc dsDesc;
	dsDesc.DepthTestEnable = TRUE;
	dsDesc.DepthWriteEnable = TRUE;

	m_DepthStates.Acquire( dsDesc );
    
	LoadDefaultMaterial();
}

Void CRenderPassLighting::UnInitialize( CRenderer& renderer )
{
}
