#include <Sable/Graphics/Geometry/RibbonMesh.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CGeometryRibbonMesh, CGeometryMesh ) ;

CGeometryRibbonMesh::CGeometryRibbonMesh()
{
	m_StepCount = 0;
	m_Width = 0.05f;
	m_VertexBuffer.SetAttribute( CGeometryVertexBuffer::nFlag_Dynamic );
	SetStepCount( 32 );

	m_VertexLayout.AddElement( nVertexComponent_Position, nVertexComponentType_Float3 );
	m_VertexLayout.AddElement( nVertexComponent_TexCoord0, nVertexComponentType_Float2 );
	m_VertexLayout.Initialize();

	SetIndexBuffer( &m_IndexBuffer );
	SetVertexBuffer( &m_VertexBuffer );
	SetVertexLayout( &m_VertexLayout );
}

CGeometryRibbonMesh::~CGeometryRibbonMesh()
{
}

Void CGeometryRibbonMesh::AddSegment( const CCamera& cam, Byte* vtxBuffer, const CVector3f& a, const CVector3f& b )
{
	CVector3f dir = b - a;
	Float32 len = dir.GetLength();
	if( len == 0.0f )
		return;

	dir.Normalize();

	CVector3f normal = ( a + dir * len / 2.0f ) - cam.GetWorldTranslation();
	normal.Normalize();
	CVector3f tangent = dir.CrossProduct( normal );

	SVertex* v = (SVertex*)vtxBuffer;

	v[0].Position = a + tangent * m_Width / 2.0f;
	v[0].UVCoord = CVector2f::Zero;
	v[1].Position = b + tangent * m_Width / 2.0f;
	v[1].UVCoord = CVector2f::Zero;
	v[2].Position = b - tangent * m_Width / 2.0f;
	v[2].UVCoord = CVector2f::Zero;
	v[3].Position = a - tangent * m_Width / 2.0f;
	v[3].UVCoord = CVector2f::Zero;

}

Void CGeometryRibbonMesh::ReBuild( const CCamera& cam )
{
	// Create Buffer if necessary
	if( m_VertexBuffer.GetVertexCount() == 0 )
	{
		CreateBuffer();
	}

	Float32 t = 0.0f;
	CVector3f p1, p2;

	Byte* vtxBuffer = m_VertexBuffer.Lock();

	for( UInt32 i=1;i<=m_StepCount; i++ )
	{
		t = (Float32) (i-1) / (m_StepCount);
		p1 = m_Curve.EvaluteAt( t );
		t = (Float32) i / (m_StepCount);
		p2 = m_Curve.EvaluteAt( t );

		AddSegment( cam, vtxBuffer, p1, p2 );
		vtxBuffer += sizeof( SVertex ) * 4;
	}

	m_VertexBuffer.UnLock();
}

CTCBCurve3f&	CGeometryRibbonMesh::GetCurve()
{
	return m_Curve;
}

Void CGeometryRibbonMesh::CreateBuffer()
{
	if( m_StepCount == 0 )
		return;

	CArrayUInt16 indexBufferData( 6 * m_StepCount );
	for( UInt32 i=0;i<m_StepCount; i++ )
	{
		indexBufferData[ i*6 + 0 ] = i*4 + 3; 
		indexBufferData[ i*6 + 1 ] = i*4 + 1;
		indexBufferData[ i*6 + 2 ] = i*4 + 0;
		indexBufferData[ i*6 + 3 ] = i*4 + 3;
		indexBufferData[ i*6 + 4 ] = i*4 + 2;
		indexBufferData[ i*6 + 5 ] = i*4 + 1;
	}

	m_IndexBuffer.SetRawData( 6 * m_StepCount, sizeof( UInt16 ), (Byte*) indexBufferData.GetBuffer() );
	m_IndexBuffer.Load();

	m_VertexBuffer.SetRawData( 4 * m_StepCount, sizeof( SVertex ), NULL );
	m_VertexBuffer.Load();
}

Void CGeometryRibbonMesh::SetWidth( Float32 width )
{
	m_Width = width;
}

Void CGeometryRibbonMesh::SetStepCount( UInt32 count )
{
	if( count != m_StepCount )
	{
		m_StepCount = count;
		CreateBuffer();
	}
}