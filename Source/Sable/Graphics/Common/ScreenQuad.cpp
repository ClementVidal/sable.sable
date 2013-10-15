#include <Sable\Graphics\Common\ScreenQuad.h>

#include <Sable\Graphics\Common\DataTypes.h>
#include <Sable\Graphics\Debug\GraphicCommandGroup.h>

using namespace Sable;

CScreenQuad::CScreenQuad() :
	CManagedObject()
{
}

CScreenQuad::~CScreenQuad()
{
    UnInitialize();
}

Void CScreenQuad::UnInitialize()
{
}

Void CScreenQuad::Initialize( const CColor& col )
{
	Initialize( col, col, col, col );
}

Void CScreenQuad::Initialize( )
{
	CColor col( 0.0f, 0.0f, 0.0f, 0.0f );
	Initialize( col, col, col, col );
}

Void CScreenQuad::SetColor( const CColor& col1, const CColor& col2, const CColor& col3, const CColor& col4 )
{
	SVertex* vertices = (SVertex*)m_VertexBuffer.Lock();

	vertices[ 0 ].Position = CVector2f( -1.0f,  1.0f );
	vertices[ 1 ].Position = CVector2f(  1.0f,  1.0f );
	vertices[ 2 ].Position = CVector2f(  1.0f, -1.0f );
	vertices[ 3 ].Position = CVector2f( -1.0f, -1.0f );

	vertices[ 0 ].TexCoord0 = CVector2f( 0.0f, 0.0f );
	vertices[ 1 ].TexCoord0 = CVector2f( 1.0f, 0.0f );
	vertices[ 2 ].TexCoord0 = CVector2f( 1.0f, 1.0f );
	vertices[ 3 ].TexCoord0 = CVector2f( 0.0f, 1.0f );

	vertices[ 0 ].Color = col1;
	vertices[ 1 ].Color = col2;
	vertices[ 2 ].Color = col3;
	vertices[ 3 ].Color = col4;

	m_VertexBuffer.UnLock();
}

Void CScreenQuad::SetColor( const CColor& col )
{
	SetColor( col, col, col, col );
}

Void CScreenQuad::Initialize( const CColor& col1, const CColor& col2, const CColor& col3, const CColor& col4 )
{
	SVertex vertexBufferData[ 4 ];
	UInt16 indexBufferData[ 6 ];

	vertexBufferData[ 0 ].Position = CVector2f( -1.0f,  1.0f );
	vertexBufferData[ 1 ].Position = CVector2f(  1.0f,  1.0f );
	vertexBufferData[ 2 ].Position = CVector2f(  1.0f, -1.0f );
	vertexBufferData[ 3 ].Position = CVector2f( -1.0f, -1.0f );

	vertexBufferData[ 0 ].TexCoord0 = CVector2f( 0.0f, 0.0f );
	vertexBufferData[ 1 ].TexCoord0 = CVector2f( 1.0f, 0.0f );
	vertexBufferData[ 2 ].TexCoord0 = CVector2f( 1.0f, 1.0f );
	vertexBufferData[ 3 ].TexCoord0 = CVector2f( 0.0f, 1.0f );

	vertexBufferData[ 0 ].Color = col1;
	vertexBufferData[ 1 ].Color = col2;
	vertexBufferData[ 2 ].Color = col3;
	vertexBufferData[ 3 ].Color = col4;

	indexBufferData[ 0 ] = 0; 
	indexBufferData[ 1 ] = 1;
	indexBufferData[ 2 ] = 3;
	indexBufferData[ 3 ] = 1;
	indexBufferData[ 4 ] = 2;
	indexBufferData[ 5 ] = 3;

	m_VertexLayout.AddElement( nVertexComponent_Position, nVertexComponentType_Float2 );
	m_VertexLayout.AddElement( nVertexComponent_TexCoord0, nVertexComponentType_Float2 );
	m_VertexLayout.AddElement( nVertexComponent_Color0, nVertexComponentType_Float4 );
	m_VertexLayout.Initialize();

	m_VertexBuffer.SetAttribute( CGeometryVertexBuffer::nFlag_Dynamic );
	m_VertexBuffer.SetRawData( 4, sizeof( SVertex ), ( Byte* ) vertexBufferData );
	m_VertexBuffer.Load( );

	m_IndexBuffer.SetRawData( 6, sizeof( UInt16 ), (Byte*)indexBufferData );
	m_IndexBuffer.Load( );

}

Void CScreenQuad::Render( CRenderer& renderer, const CVector2f& pos, const CVector2f& size, CShader& shader )
{
	DebugGraphicCommandGroup( "CScreenQuad::Render" );

	CShaderParameter* p;	
	p = shader.GetParameter( "Size" );
	if( p )
		p->SetValue( CShaderParameterData( size ) );
	
	p = shader.GetParameter( "Position" );
	if( p )
		p->SetValue( CShaderParameterData( pos ) );

	renderer.Activate( m_VertexBuffer, 0 );
	renderer.Activate( m_VertexLayout );
	renderer.Activate( m_IndexBuffer );
	renderer.Activate( shader );

	GraphicsManager.GetImpl().DrawIndexed( nPrimitiveType_TriangleList, 6, 0, 0 );

}