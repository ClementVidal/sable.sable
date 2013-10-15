#include <Sable\Graphics\Renderer\Renderer.h>

#include <Sable\Graphics\PostProcess\PostProcess.h>
#include <Sable\Graphics\RenderTarget\Texture.h>
#include <Sable\Graphics\RenderPass\RenderPass.h>
#include <Sable\Graphics\RenderPass\Lighting.h>
#include <Sable\Graphics\Debug\RenderPass.h>
#include <Sable\Graphics\RenderPass\Depth.h>
#include <Sable\Application\Window.h>
#include <Sable\Gui\Common\RenderPass.h>
#include <Sable\Graphics\Common\Manager.h>
#include <Sable\Graphics\Node\Traversal.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CRenderer );

/**
Default constructor for a renderer.
\param renderTarget The render target used a main output surface
*/
CRenderer::CRenderer( )
{
    m_DebugPass = NULL;
	m_GuiPass = NULL;
	
    m_ActiveShader = NULL;
	m_ActiveIndexBuffer = NULL;
	m_ActiveVertexBuffer = NULL;
    m_ActiveStateBlend = NULL;
    m_ActiveStateDepthStencil = NULL;
    m_ActiveStateRasterizer = NULL;
    m_ActiveRenderTarget = NULL;
	m_ActiveVertexLayout = NULL;
	m_ActiveInstanceBuffer = NULL;
	m_CurrentViewport = NULL;
	m_ActiveDepthStencil = NULL;

    m_RendererPassTable.SetCapacity( 16 );

	CStatesBlend::SDesc blendDesc;
	m_DefaultBlendStates.Acquire( blendDesc );

	CStatesDepthStencil::SDesc dsDesc;
	m_DefaultDepthStencilStates.Acquire( dsDesc );

	CStatesRasterizer::SDesc srDesc;
	m_DefaultRasterizerStates.Acquire( srDesc );

}

CRenderer::~CRenderer()
{
}

/**
Called by the GraphicsManager to prepare the scene before a render.\n
<b>Overloaded version MUST call the base one<b>
*/
Void CRenderer::TraverseNodeTree( const CNode& rootNode )
{
	Index index;

	for(index=0; index<GetRendererPassCount(); index++)
	{
        CRenderPass& pass = GetRendererPassAtIndex(index);
        TraverseNodeTree( rootNode, pass );
	}
}
/*
Void CRenderer::ClearRenderTarget( CRenderTarget& rt, CRenderTargetDepthStencil& ds )
{
    RendererPassTable::Iterator it;
    CRenderTarget*	rtTable[8];
    CRenderTarget*  tmpRt;

    for( Int32 i=0;i<8;i++)
    {
        rtTable[i] = NULL;
    }

    ForEachItem( it, m_RendererPassTable )
    {
        tmpRt = (*it)->GetRenderTarget();
        if( !tmpRt )
            tmpRt = &rt;
        
        // Find if rt was already cleared
        for( Int32 i=0;i<8;i++)
        {
            if( rtTable[i] == tmpRt )
            {
                tmpRt = NULL;
                break;
            }
        }

        // If rt was not already cleared
        if( tmpRt )
        {
            tmpRt->Clear( CColor::Black );
            for( Int32 i=0;i<8;i++)
            {
                if( rtTable[i] == NULL )
                {
                    rtTable[i] = tmpRt;
                    break;
                }
            }
        }
    }
}
*/
/**
Called by the GraphicsManager to render the scene.\n
Call BeginRender, execute all the registered callback and call EndRender\n
<b>Overloaded version MUST call the base one<b>
*/
Void CRenderer::Render( CRenderTarget& rt, CRenderTargetDepthStencil& ds, CViewport& viewport )
{
	CRenderPass* previous = NULL;
	CRenderPass* tmp = NULL;
    RendererPassTable::Iterator it;
	CRenderTarget* tmpRt = NULL;
	CRenderTargetDepthStencil* tmpDs = NULL;
	CRenderPass*	currentPass = NULL;

	if(! m_View )
		return;

	rt.Clear( CColor::Blue );
	ds.Clear( 1.0f, 0 );

	if( m_View->GetWorld() )
	{
		TraverseNodeTree( m_View->GetWorld()->GetRootNode() );
		TraverseNodeTree( m_View->GetWorld()->GetGuiRootNode() );
	}

	Activate( viewport );

    ForEachItem( it, m_RendererPassTable )
    {
		if( (*it)->GetIsEnabled() )
		{
			currentPass = (*it);

			if( ( previous == NULL ) || ( previous->GetRenderTarget() != currentPass->GetRenderTarget() ) )
				tmpRt = currentPass->GetRenderTarget();

			if( !tmpRt )
				tmpRt = &rt;

			if( !tmpDs )
				tmpDs = &ds;

			Activate( *tmpDs );
			Activate( *tmpRt );

			currentPass->Render( *this );

			previous = currentPass;
		}
    }
}

Void CRenderer::Draw( EPrimitiveType primitive, UInt32 vertexCount, UInt32 offset )
{
	GraphicsManager.GetImpl().Draw( primitive, vertexCount, offset );
}

Void CRenderer::DrawIndexed( EPrimitiveType primitive, UInt32 indexCount, UInt32 startIndexLocation, UInt32 baseVertexLocation )
{
	GraphicsManager.GetImpl().DrawIndexed( primitive, indexCount, startIndexLocation, baseVertexLocation );
}

Void CRenderer::DrawInstanced( EPrimitiveType primitive, UInt32 vertexCount, UInt32 offset, UInt32 instanceCount )
{
	GraphicsManager.GetImpl().DrawInstanced( primitive, vertexCount, offset, instanceCount );
}

Void CRenderer::DrawIndexedInstanced( EPrimitiveType primitive, UInt32 indexCount, UInt32 startIndexLocation, UInt32 baseVertexLocation, UInt32 instanceCount )
{
	GraphicsManager.GetImpl().DrawIndexedInstanced( primitive, indexCount, startIndexLocation, baseVertexLocation, instanceCount );
}

CStatesBlend& CRenderer::GetDefaultBlendStates()
{
	return m_DefaultBlendStates;
}

CStatesRasterizer& CRenderer::GetDefaultRasterizerStates()
{
	return m_DefaultRasterizerStates;
}

CStatesDepthStencil& CRenderer::GetDefaultDepthStencilStates()
{
	return m_DefaultDepthStencilStates;
}

/**
Initialize the renderer.\n
Iterate over all the registered CRenderPass and call their Initialize()\n
<b>Overloaded version MUST call the base one<b>
\param outputRenderTarget The render target used for output
*/
Void CRenderer::Initialize( )
{
    Index index;

    for(index=0; index<GetRendererPassCount(); index++)
    {
        GetRendererPassAtIndex(index).Initialize(*this);
    }
}

/**
This will automaticaly resize all the render target of every renderpass to the given resolution
*/
Void CRenderer::Resize( const CVector2i& newSize )
{
	UInt32 index;

	for(index=0; index<GetRendererPassCount(); index++)
	{
		CRenderTarget* rt = GetRendererPassAtIndex(index).GetRenderTarget();
		if( rt )
			rt->Resize( newSize );
	}
}

UInt32 CRenderer::GetRendererPassCount( ) const
{
    return m_RendererPassTable.GetItemCount( );
}

CRenderPass& CRenderer::GetRendererPassAtIndex( UInt32 i ) const
{
    return *m_RendererPassTable.GetItemAtIndex( i );
}

CRenderPass& CRenderer::GetRendererPassByType( const CTypeInfo& type ) const
{
    RendererPassTable::Iterator it;

    ForEachItem( it, m_RendererPassTable )
    {
        if( (*it)->GetTypeInfo() == type )
            return *(*it);
    }

    return GetNullReference( CRenderPass );
}

/**
Push a render pass to the render pass stack

\return Return the index of this render pass in the stack
*/
UInt32 CRenderer::PushRenderPass( CRenderPass& pass )
{
    m_RendererPassTable.PushItem( &pass );

    // Automaticly grab Debug Renderer and depth pass
    if( pass.GetTypeInfo().IsKindOf( CDebugRenderPass::GetStaticTypeInfo() ) ) 
    {
        m_DebugPass = (CDebugRenderPass*) &pass;
    } 
    else if( pass.GetTypeInfo().IsKindOf( CRenderPassDepth::GetStaticTypeInfo() ) ) 
    {
        m_DepthPass = (CRenderPassDepth*) &pass;
    }
	else if( pass.GetTypeInfo().IsKindOf( CRenderPassLighting::GetStaticTypeInfo() ) ) 
	{
		m_LightingPass = (CRenderPassLighting*) &pass;
	}
	else if( pass.GetTypeInfo().IsKindOf( CGuiRenderPass::GetStaticTypeInfo() ) ) 
	{
		m_GuiPass = (CGuiRenderPass*) &pass;
	}

    return m_RendererPassTable.GetItemCount() - 1 ;
}

/**
UnInitialize the renderer.\n
Iterate over all the registered CRenderPass and call their UnInitialize()\n
<b>Overloaded version MUST call the base one<b>
*/
Void CRenderer::UnInitialize()
{
    Index index;

    for(index=0; index<GetRendererPassCount(); index++) 
	{
        GetRendererPassAtIndex(index).UnInitialize(*this);
    }
}

Void CRenderer::TraverseNodeTree( const CNode& node, CRenderPass& pass  )
{
    DebugProfile("CRenderer::TraverseNodeTree");

    const CTypeInfo& nodeType = node.GetTypeInfo();

	Bool canTraverse = TRUE;
	CNodeSpatial* nodeSpatial = node.CastTo<CNodeSpatial>();
	if( nodeSpatial )
	{
		if( ! nodeSpatial->IsVisible( *GetView()->GetCamera() ) )
		{
			canTraverse = FALSE;
		}
	}

	if( canTraverse )
	{
		if( !pass.ProcessTraversedNode( (CNode&)node, *this ) )
			return;
	}

	CNode* child = node.GetChild();
	while( child )
	{		
		TraverseNodeTree( *child, pass );
        child = child->GetSibling();
	}	
}

Void CRenderer::Activate( CRenderTargetDepthStencil& ds )
{
	if( &ds != m_ActiveDepthStencil )
	{
		ds.Activate( );
		m_ActiveDepthStencil = &ds;
	}
}
Void CRenderer::Activate( CRenderTarget& rt )
{
    if( &rt != m_ActiveRenderTarget )
    {
		rt.Activate( *this, 0 );
		m_ActiveRenderTarget = &rt;
    }
}

Void CRenderer::Activate( CShader& shader )
{
//	if( &shader != m_ActiveShader )
	{
		shader.Activate( *this );
		m_ActiveShader = &shader;
	}
}

Void  CRenderer::Activate( CShaderProgram& program )
{
    DebugAssert( program.GetType() != nShaderProgramType_Count && program.GetType() != nShaderProgramType_None );

    if( &program != m_ActiveShaderProgram[program.GetType()] )
    {
        program.Activate( *this );
        m_ActiveShaderProgram[program.GetType()] = &program;
    }
}

Void CRenderer::Activate( CGeometryInstanceBuffer& ib, UInt32 index )
{
	//if( &ib != m_ActiveInstanceBuffer )
	{
		ib.Activate( *this, index );
		m_ActiveInstanceBuffer = &ib;
	}
}

Void CRenderer::Activate( CGeometryIndexBuffer& ib  )
{
	if( &ib != m_ActiveIndexBuffer )
	{
		ib.Activate( *this  );
		m_ActiveIndexBuffer = &ib;
	}
}

Void CRenderer::Activate( CViewport& vpt  )
{
	if( &vpt != m_CurrentViewport )
	{
		vpt.Activate( );
		m_CurrentViewport = &vpt;
	}
}

Void CRenderer::Activate( CGeometryVertexLayout& vl  )
{
	//if( &vl != m_ActiveVertexLayout )
	{
		vl.Activate( *this );
		m_ActiveVertexLayout = &vl;
	}
}

Void CRenderer::Activate( CGeometryVertexBuffer& vb, UInt32 index  )
{
//	if( &vb != m_ActiveVertexBuffer )
	{
		vb.Activate( *this, index );
		m_ActiveVertexBuffer = &vb;
	}
}

CSceneView* CRenderer::GetView( ) const
{
	return m_View;
}

Void CRenderer::SetView( CSceneView* view )
{
	m_View = view;
}

CDebugRenderPass* CRenderer::GetDebugRenderPass() const
{
    return m_DebugPass;
}

CRenderPassDepth* CRenderer::GetDepthRenderPass() const
{
    return m_DepthPass;
}

CRenderPassLighting* CRenderer::GetLightingRenderPass() const
{
    return m_LightingPass;
}

CGuiRenderPass*	CRenderer::GetGuiRenderPass() const
{
    return m_GuiPass;
}

CViewport*  CRenderer::GetCurrentViewport() const
{
	return m_CurrentViewport;
}

Void CRenderer::Activate( CStatesRasterizer& sr  )
{
    //if( &sr != m_ActiveStateRasterizer )
    {
		sr.Activate( *this  );
		m_ActiveStateRasterizer = &sr;
	}
}

Void CRenderer::Activate( CStatesDepthStencil& ds  )
{
    //if( &ds != m_ActiveStateDepthStencil )
    {
		ds.Activate( *this  );
		m_ActiveStateDepthStencil = &ds;
	}
}

Void CRenderer::Activate( CStatesBlend& bl  )
{
    //if( &bl != m_ActiveStateBlend )
    {
		bl.Activate( *this  );
		m_ActiveStateBlend = &bl;
    }
}
