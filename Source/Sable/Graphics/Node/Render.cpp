#include <Sable\Graphics\Node\Render.h>

#include <Sable\Graphics\Shader\Shader.h>
#include <Sable\Graphics\RenderQueue\Entry.h>
#include <Sable\Graphics\Renderer\Renderer.h>
#include <Sable\Core\ManagedObject\Ref.h>
#include <Sable\Graphics\Geometry\InstanceBuffer.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CNodeRender, CNodeSpatial )

CNodeRender::CNodeRender( ):
	CNodeSpatial(),
	m_ShaderConnector( *this )
{
	m_Model.SetNull();
	m_IsVisible = TRUE;
	m_RenderPriority = 0;
}

CNodeRender::CNodeRender( CNode&  parent ):
	CNodeSpatial( parent ),
	m_ShaderConnector( *this )
{
	m_Model.SetNull();
	m_IsVisible = TRUE;
	m_RenderPriority = 0;
}

CNodeRender::~CNodeRender()
{
}

Bool CNodeRender::GetIsVisible() const
{
	return m_IsVisible;
}

Void CNodeRender::SetIsVisible( Bool onOff )
{
	m_IsVisible = onOff;
}


Void CNodeRender::SetRenderPriority( UInt32 p )
{
	m_RenderPriority = p;
}

UInt32 CNodeRender::GetRenderPriority( ) const
{
	return m_RenderPriority;
}

/**
This method return a color used when this node is binded to a CGeometryModelInstance.
Otherwise this value is not used
*/
const CColor& CNodeRender::GetInstanceColor() const
{
	return m_InstanceColor;
}

CShaderConnectorGraphNode& CNodeRender::GetShaderConnector()
{
	return m_ShaderConnector;
}

Void CNodeRender::SetInstanceColor( const CColor& col )
{
	m_InstanceColor = col;
}

Bool CNodeRender::Update( )
{
	Bool r = CNodeSpatial::Update();

	if( m_InstanceBuffer )
	{
		CGeometryInstanceBuffer::SInstanceData data;
		data.Matrix = GetWorldMatrix();
		data.Color = m_InstanceColor;
		if( m_InstanceBuffer->GetInstanceCount()  < m_InstanceBuffer->GetCapacity() )
		{
			m_InstanceBuffer->AddInstanceData( data );
		}
		else
		{
			DebugLogWarning( "Too many instance for instance bufer capacity" );
		}
		
	}

	return r;
}

Bool CNodeRender::Serialize( CPersistentArchive& ar )
{
    Int16 version = 0;

    if( ar.BeginScope( WT("NodeRender"), version ) == version )
    {
        ar.Serialize( m_Model, WT("Model") );
        ar.EndScope();
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

CGeometryInstanceBuffer* CNodeRender::GetInstanceBuffer( ) const
{
	return m_InstanceBuffer;
}

Void CNodeRender::SetInstanceBuffer( const CGeometryInstanceBuffer* buffer )
{
	m_InstanceBuffer = buffer;
}

Void CNodeRender::SetModel( const CGeometryModel* model )
{
    m_Model = model;
}

CGeometryModel* CNodeRender::GetModel( ) const 
{ 
    return m_Model; 
}

Void CNodeRender::GetLocalBoundingBox( CAABox& bbox ) const
{
    m_Model->GetBoundingBox( bbox );
}
