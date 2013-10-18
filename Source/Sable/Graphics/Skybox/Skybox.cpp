#include <Sable/Graphics/Skybox/Skybox.h>

#include <Sable/Graphics/Geometry/Mesh.h>
#include <Sable/Graphics/Common/Manager.h>
#include <Sable/Graphics/Debug/GraphicCommandGroup.h>
#include <Sable/Graphics/Texture/Texture2d.h>

using namespace Sable;


IMPLEMENT_MANAGED_CLASS1( Sable, CSkybox, CManagedObject );

CSkybox::CSkybox()
{
}

CSkybox::CSkybox( CSceneWorld& world )
{
	m_World = &world;
}

CSkybox::~CSkybox()
{
}

Void CSkybox::Initialize( )
{
	m_Shader.Load(  CoreManager.GetFileSystem().GetFilePath( "System/Shader", "World/Skybox.vsh" ),
                    CoreManager.GetFileSystem().GetFilePath( "System/Shader", "World/Skybox.psh" ),
                    CFilePath() );

	m_DiffuseTexture = NEWOBJ( CTextureCube, ( ) );
    m_DiffuseTexture->Load( CoreManager.GetFileSystem().GetFilePath( "System", "Texture/World/Skybox.dds" ) );

	CStatesSampler::SDesc samplerDesc;
	samplerDesc.MagFilter = nStateFilter_Point;
	samplerDesc.MinFilter = nStateFilter_Point;
	m_SamplerStates.Acquire( samplerDesc );

	BuildMesh();
}

Void CSkybox::BuildMesh()
{
	SVertex vertexBufferData[ 8 ];
	UInt16 indexBufferData[ 36 ];

	vertexBufferData[ 0 ].Position = CVector3f( -1.0f,  1.0f, 1.0f );
	vertexBufferData[ 1 ].Position = CVector3f(  1.0f,  1.0f, 1.0f );
	vertexBufferData[ 2 ].Position = CVector3f(  1.0f, -1.0f, 1.0f );
	vertexBufferData[ 3 ].Position = CVector3f( -1.0f, -1.0f, 1.0f );

	vertexBufferData[ 4 ].Position = CVector3f( -1.0f,  1.0f, -1.0f );
	vertexBufferData[ 5 ].Position = CVector3f(  1.0f,  1.0f, -1.0f );
	vertexBufferData[ 6 ].Position = CVector3f(  1.0f, -1.0f, -1.0f );
	vertexBufferData[ 7 ].Position = CVector3f( -1.0f, -1.0f, -1.0f );

	MemoryFill( indexBufferData, 0, 36 * sizeof( UInt16 ) );
	// Z+
	indexBufferData[ 0 ] = 0; 
	indexBufferData[ 1 ] = 1;
	indexBufferData[ 2 ] = 3;
	indexBufferData[ 3 ] = 1;
	indexBufferData[ 4 ] = 2;
	indexBufferData[ 5 ] = 3;

	// Z-
	indexBufferData[ 6 ] = 7; 
	indexBufferData[ 7 ] = 5;
	indexBufferData[ 8 ] = 4;
	indexBufferData[ 9 ] = 7;
	indexBufferData[ 10] = 6;
	indexBufferData[ 11] = 5;

	// Y+
	indexBufferData[ 12 ] = 4; 
	indexBufferData[ 13 ] = 1;
	indexBufferData[ 14 ] = 0;
	indexBufferData[ 15 ] = 4;
	indexBufferData[ 16 ] = 5;
	indexBufferData[ 17 ] = 1;

	// Y-
	indexBufferData[ 18 ] = 3; 
	indexBufferData[ 19 ] = 2;
	indexBufferData[ 20 ] = 7;
	indexBufferData[ 21 ] = 2;
	indexBufferData[ 22 ] = 6;
	indexBufferData[ 23 ] = 7;

	// X+
	indexBufferData[ 24 ] = 6; 
	indexBufferData[ 25 ] = 1;
	indexBufferData[ 26 ] = 5;
	indexBufferData[ 27 ] = 6;
	indexBufferData[ 28 ] = 2;
	indexBufferData[ 29 ] = 1;

	// X-
	indexBufferData[ 30 ] = 4; 
	indexBufferData[ 31 ] = 0;
	indexBufferData[ 32 ] = 7;
	indexBufferData[ 33 ] = 0;
	indexBufferData[ 34 ] = 3;
	indexBufferData[ 35 ] = 7;

	m_VertexLayout.AddElement( nVertexComponent_Position, nVertexComponentType_Float3 );

	m_VertexBuffer.SetRawData( 8, sizeof( SVertex ), ( Byte* ) vertexBufferData );

	m_IndexBuffer.SetRawData( 36, sizeof( UInt16 ), (Byte*)indexBufferData );

	m_Mesh.SetIndexBuffer( &m_IndexBuffer );
	m_Mesh.SetVertexBuffer( &m_VertexBuffer );
    m_Mesh.SetVertexLayout( &m_VertexLayout );
    m_Mesh.Load();
}

Void CSkybox::UnInitialize( )
{
}

CTextureCube& CSkybox::GetTexture() const
{
	return *m_DiffuseTexture;
}

Void CSkybox::SetTexture( CTextureCube& texture )
{
	m_DiffuseTexture = &texture;
}

Void CSkybox::Render( CRenderer& renderer )
{
	CMatrix4x4f transform, scale, projection;
	if( !renderer.GetView() )
		return;

	CCamera* currentCamera = renderer.GetView()->GetCamera();
	
	if( currentCamera == NULL )
		return;

	DebugGraphicCommandGroup( "CSkybox::Render" );

	scale.SetFromScale( CVector3f( 500, 500, 500 ) );
	transform.SetFromIdentity();

	transform.SetTranslationComponent( currentCamera->GetWorldPosition() );
	transform = scale * transform ;
    projection.SetFromLHPerspProjectionValues( MathPi / 2.2f,1.0f, 0.5f, 1000.0f);

	m_Shader.GetParameter( "Texture" )->SetValue( *m_DiffuseTexture );

	CShaderParameter* sp = m_Shader.GetParameter("Sampler");
	if( sp )
		sp->SetValue( m_SamplerStates );

	transform = transform * currentCamera->GetViewMatrix() * projection;

	m_Shader.GetParameter( "WorldViewProjectionMatrix" )->SetValue( transform );
	renderer.Activate( m_Shader );
	m_Mesh.Activate( renderer );
	m_Mesh.Render();
}
