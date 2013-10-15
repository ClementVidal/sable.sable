#include <Sable\Graphics\Geometry\Helper.h>

#include <Sable\Graphics\Geometry\Header.h>

using namespace Sable;


Bool CGeometryHelper::CreatePlane( CGeometryModel& model, const CColor& color, const CVector2f& size, const CVector2f& uvSize )
{
	struct SVertex
	{
		CVector3f	Position;
		CVector2f	TexCoord0;
		CColor		Color;
	};

	SVertex vertexBufferData[ 4 ];
	UInt16 indexBufferData[ 6 ];

	vertexBufferData[ 0 ].Position = CVector3f( -0.5f*size.GetX(), 0.0f,  0.5f*size.GetY() );
	vertexBufferData[ 1 ].Position = CVector3f(  0.5f*size.GetX(), 0.0f,  0.5f*size.GetY() );
	vertexBufferData[ 2 ].Position = CVector3f(  0.5f*size.GetX(), 0.0f, -0.5f*size.GetY() );
	vertexBufferData[ 3 ].Position = CVector3f( -0.5f*size.GetX(), 0.0f, -0.5f*size.GetY() );

	vertexBufferData[ 0 ].TexCoord0 = CVector2f( 0.0f,				0.0f );
	vertexBufferData[ 1 ].TexCoord0 = CVector2f( 1.0f*uvSize.GetX(),	0.0f );
	vertexBufferData[ 2 ].TexCoord0 = CVector2f( 1.0f*uvSize.GetX(),	1.0f*uvSize.GetY() );
	vertexBufferData[ 3 ].TexCoord0 = CVector2f( 0.0f,				1.0f*uvSize.GetY() );

	vertexBufferData[ 0 ].Color = color;
	vertexBufferData[ 1 ].Color = color;
	vertexBufferData[ 2 ].Color = color;
	vertexBufferData[ 3 ].Color = color;

	indexBufferData[ 0 ] = 0; 
	indexBufferData[ 1 ] = 1;
	indexBufferData[ 2 ] = 3;
	indexBufferData[ 3 ] = 1;
	indexBufferData[ 4 ] = 2;
	indexBufferData[ 5 ] = 3;

	CGeometryMesh* mesh = NEWOBJ( CGeometryMesh, () );
	CGeometryVertexBuffer* vb = NEWOBJ( CGeometryVertexBuffer, () );
	CGeometryIndexBuffer* ib = NEWOBJ( CGeometryIndexBuffer, () );
	CGeometryVertexLayout* vl = NEWOBJ( CGeometryVertexLayout, () );

	vl->AddElement( nVertexComponent_Position, nVertexComponentType_Float3 );
	vl->AddElement( nVertexComponent_TexCoord0, nVertexComponentType_Float2 );
	vl->AddElement( nVertexComponent_Color0, nVertexComponentType_Float4 );
	vl->Initialize();

	//vb->SetAttribute( CGeometryVertexBuffer::nFlag_Dynamic );
	vb->SetRawData( 4, sizeof( SVertex ), ( Byte* ) vertexBufferData );
	vb->Load( );

	ib->SetRawData( 6, sizeof( UInt16 ), (Byte*)indexBufferData );
	ib->Load( );

	mesh->SetIndexBuffer( ib );
	mesh->SetVertexBuffer( vb );
	mesh->SetVertexLayout( vl );

	model.SetSubsetCount( 1 );
	model.GetSubset(0).Mesh = mesh;

	return TRUE;
}