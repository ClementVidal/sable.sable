#include <Sable/Graphics/Geometry/Mesh.h>

#include <Sable/Core/Geometry/AABox.h>
#include <Sable/Core/ManagedObject/Ref.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CGeometryMesh, CManagedObject ) ;

CGeometryMesh::CGeometryMesh()
{
    m_VertexOffset = 0;
    m_UsedVertexCount = 0;
    m_PrimitiveType = nPrimitiveType_TriangleList;
    m_BoundingBox.SetEmpty();
}

CGeometryMesh::~CGeometryMesh()
{
}

Void CGeometryMesh::Load()
{
	m_VertexBuffer->Load();
	m_IndexBuffer->Load();
    m_VertexLayout->Initialize();
}

Void CGeometryMesh::Render()
{
	DebugGraphicCommandGroup( "CGeometryMesh::Render" );
    DebugAssert( m_VertexBuffer != NULL );
    if( m_IndexBuffer != NULL )
    {
        GraphicsManager.GetImpl().DrawIndexed( 
            m_PrimitiveType,
            GetIndexCount(), 
            0, 
            0
            );
    }
    else
    {
        GraphicsManager.GetImpl().Draw( 
            m_PrimitiveType,
            m_UsedVertexCount == 0 ? GetVertexCount() : m_UsedVertexCount, 
            m_VertexOffset
            );
    }
}

Void CGeometryMesh::Activate( CRenderer& renderer )
{
	DebugGraphicCommandGroup( "CGeometryMesh::Activate" );

    if( m_IndexBuffer )
    {
        renderer.Activate( *m_IndexBuffer );
    }

    if( m_VertexBuffer  )
    {
		renderer.Activate( *m_VertexBuffer, 0 );
    }

	if( m_VertexLayout  )
	{
		renderer.Activate( *m_VertexLayout );
	}

}

UInt32 CGeometryMesh::GetIndexCount() const 
{
    return m_IndexBuffer->GetIndexCount();
}

UInt32 CGeometryMesh::GetPrimitiveCount() const 
{
    switch( m_PrimitiveType )
    {
    case nPrimitiveType_TriangleList:
        return m_UsedVertexCount / 3;

    case nPrimitiveType_LineStrip:
        return m_UsedVertexCount - 1;

    case nPrimitiveType_LineList:
        return m_UsedVertexCount / 2;

    case nPrimitiveType_PointList:
        return m_UsedVertexCount ;
    }

    DebugError( "Unsuported primitive type" );

    return 0;

}

UInt32 CGeometryMesh::GetVertexCount() const
{
    return m_VertexBuffer->GetVertexCount();
}

Void CGeometryMesh::SetVertexBuffer( CGeometryVertexBuffer* vb )
{
    m_VertexBuffer = vb;
}

Void CGeometryMesh::SetVertexLayout( CGeometryVertexLayout* vl )
{
	m_VertexLayout = vl;
}

CGeometryVertexLayout*	CGeometryMesh::GetVertexLayout() const
{
	return m_VertexLayout;
}

CGeometryVertexBuffer*    CGeometryMesh::GetVertexBuffer( ) const
{
    return m_VertexBuffer;
}

CGeometryIndexBuffer*   CGeometryMesh::GetIndexBuffer( ) const
{
    return m_IndexBuffer;
}

Void CGeometryMesh::SetIndexBuffer( CGeometryIndexBuffer* ib )
{
    m_IndexBuffer = ib;
	if( ib )
		m_UsedVertexCount = ib->GetIndexCount();
}

Bool CGeometryMesh::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;
	if( ar.BeginScope( WT("Mesh"), version ) == version )
	{
		UInt32 primType = (UInt32)m_PrimitiveType;

		ar.Serialize( m_VertexOffset, WT("Offset") );
		ar.Serialize( m_UsedVertexCount, WT("Count") );
		ar.Serialize( primType, WT("PrimitiveType") );

		ar.Serialize( m_IndexBuffer, WT("IndexBuffer") );
		ar.Serialize( m_VertexBuffer, WT("VertexBuffer") );
        ar.Serialize( m_VertexLayout, WT("VertexLayout") );

		ar.Serialize( m_BoundingBox, WT("BoundingBox") );

		m_PrimitiveType = (EPrimitiveType) primType;

		ar.EndScope();
	}

	return CManagedObject::Serialize( ar );
}

Void CGeometryMesh::SetBoundingBox( const CAABox& box )
{
	m_BoundingBox = box;
}