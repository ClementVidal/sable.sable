#include <Sable\Graphics\RenderQueue\Entry.h>

#include <Sable\Graphics\Camera\Camera.h>
#include <Sable\Graphics\Node\Render.h>
#include <Sable\Graphics\Shader\Connector.h>
#include <Sable\Graphics\Common\Manager.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CRenderQueueEntry, CManagedObject );

CRenderQueueEntry::CRenderQueueEntry( )
{
    Clear();
}

CRenderQueueEntry::CRenderQueueEntry( const CRenderQueueEntry& other )
{
    m_Shader = other.m_Shader;
    m_IndexBuffer = other.m_IndexBuffer;
    m_VertexBuffer = other.m_VertexBuffer;
    m_VertexLayout = other.m_VertexLayout;
	m_InstanceBuffer = other.m_InstanceBuffer;
	m_StatesBlend = other.m_StatesBlend;
	m_StatesRasterizer = other.m_StatesRasterizer;
	m_StatesDepthStencil = other.m_StatesDepthStencil;
    m_PrimitiveType = other.m_PrimitiveType;

	for( UInt32 i=0;i<8;i++ )
	{
		m_ConnectorTable[i] = other.m_ConnectorTable[i];
	}
}

CRenderQueueEntry& CRenderQueueEntry::operator=( const CRenderQueueEntry& other )
{
	m_Shader = other.m_Shader;
    m_IndexBuffer = other.m_IndexBuffer;
    m_VertexBuffer = other.m_VertexBuffer;
    m_VertexLayout = other.m_VertexLayout;
	m_InstanceBuffer = other.m_InstanceBuffer;
	m_StatesBlend = other.m_StatesBlend;
	m_StatesRasterizer = other.m_StatesRasterizer;
	m_StatesDepthStencil = other.m_StatesDepthStencil;
    m_PrimitiveType = other.m_PrimitiveType;

	for( UInt32 i=0;i<8;i++ )
	{
		m_ConnectorTable[i] = other.m_ConnectorTable[i];
	}

	m_Priority = other.m_Priority;

	return *this;
}

CRenderQueueEntry::~CRenderQueueEntry()
{
    Clear();
}

Void CRenderQueueEntry::Clear()
{
	m_Priority = 0;
	m_Shader = NULL;
    m_IndexBuffer = NULL;
    m_VertexBuffer = NULL;
    m_VertexLayout = NULL;
	m_InstanceBuffer = NULL;
	m_StatesBlend = NULL;
	m_StatesRasterizer = NULL;
	m_StatesDepthStencil = NULL;
    m_PrimitiveType = nPrimitiveType_TriangleList;

	for( UInt32 i=0;i<8;i++ )
	{
		m_ConnectorTable[i] = NULL;
	}
}

Void CRenderQueueEntry::Render( CRenderer& renderer )
{
	DebugProfile("CRenderPass::Render");
	DebugGraphicCommandGroup("CRenderPass::Render");
	if( m_InstanceBuffer )
	{
		if( m_IndexBuffer ) 
		{
			renderer.DrawIndexedInstanced( m_PrimitiveType, m_IndexBuffer->GetIndexCount(), 0, 0, m_InstanceBuffer->GetInstanceCount() );
		} 
		else if( m_VertexBuffer ) 
		{
			renderer.DrawInstanced( m_PrimitiveType, m_VertexBuffer->GetVertexCount(), 0, m_InstanceBuffer->GetInstanceCount()  );
		}
	}
	else
	{
		if( m_IndexBuffer ) 
		{
			renderer.DrawIndexed( m_PrimitiveType, m_IndexBuffer->GetIndexCount(), 0, 0 );
		} 
		else if( m_VertexBuffer ) 
		{
			renderer.Draw( m_PrimitiveType, m_VertexBuffer->GetVertexCount(), 0 );
		}
	}

}

Bool CRenderQueueEntry::Activate( CRenderer& renderer )
{
	if( !m_Shader )
		return FALSE;

    DebugGraphicCommandGroup("CRenderQueueEntry::Activate");

	if( m_StatesBlend )
		renderer.Activate( *m_StatesBlend );

	if( m_StatesRasterizer )
		renderer.Activate( *m_StatesRasterizer );

	if( m_StatesDepthStencil )
		renderer.Activate( *m_StatesDepthStencil );


	// Update shader parameters value according to the attached shader connectors
	for( UInt32 i = 0;i<8;i++ )
	{
		if( m_ConnectorTable[i] )
		{
			m_ConnectorTable[i]->FlushParametersValues( *m_Shader );
		}
	}

	DebugAssert( m_Shader );
	DebugAssert( m_VertexLayout );
	DebugAssert( m_VertexBuffer );

	renderer.Activate( *m_Shader );
	renderer.Activate( *m_VertexBuffer, 0 );
    renderer.Activate( *m_VertexLayout );

	if ( m_InstanceBuffer )
		renderer.Activate( *m_InstanceBuffer, 1 );

    if( m_IndexBuffer )
        renderer.Activate( *m_IndexBuffer );

    return TRUE;
}

Bool CRenderQueueEntry::IsOpaque() const
{
	if( m_StatesBlend && m_StatesBlend->GetDesc().BlendEnable[0] )
		return FALSE;
	return TRUE;
}

Bool   CRenderQueueEntry::operator<( const CRenderQueueEntry& other)
{
	// Opaque objects at left side, translucent objects at right side
	if( IsOpaque() && !other.IsOpaque() )
	{
		return TRUE;
	}
	else if( !IsOpaque() && other.IsOpaque() )
	{
		return FALSE;
	}

	// priority
	if( m_Priority < other.m_Priority )
	{
		return TRUE;
	}
	if( m_Priority > other.m_Priority )
	{
		return FALSE;
	}

	// Shaders
	if( m_Shader == other.m_Shader )
	{
		if( m_VertexBuffer == other.m_VertexBuffer )
		{
			if( m_IndexBuffer == other.m_IndexBuffer )
			{
				return FALSE;
			}
			return FALSE;
		}
		return FALSE;
	}

	return TRUE;
}

/**
Validate if a RQ entry is fully specified
called by CRenderPass::ActivateRQEntry
*/
Bool CRenderQueueEntry::IsValid() const
{
	if( m_Shader == NULL )
		return FALSE;

	if( m_VertexBuffer == NULL )
		return FALSE;

    if( m_VertexLayout == NULL )
        return FALSE;

	return TRUE;
}

Void CRenderQueueEntry::AddShaderConnector( CShaderConnector& connector )
{
	for( Int32 i=0;i<8;i++ )
	{
		if( m_ConnectorTable[i] == NULL )
		{
			m_ConnectorTable[i] = &connector;
			return;
		}
	}
}