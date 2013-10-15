#include <Sable\Graphics\Particle\System.h>

#include <Sable\Graphics\Material\Material.h>
#include <Sable\Graphics\Renderer\Header.h>
#include <Sable\Graphics\Particle\Group.h>

#define PARTICLESYSTEM_RENDERQUEUE_PRIORITY 65535

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CParticleSystem, CNodeRender );

CParticleSystem::CParticleSystem( ) :
	CNodeRender( )
{
}

CParticleSystem::CParticleSystem( CNodeSpatial& parent, CParticleGroup& sim, CMaterial& material ) :
    CNodeRender(parent)
{    	
	Initialize( parent, sim, material );
}

CParticleSystem::~CParticleSystem()
{
}

Void CParticleSystem::RebuildBuffer( const CCamera& cam )
{       
    CMatrix4x4f rotationMatrix;
    CVector3f axis;
	UInt32 pCount = 0;

    CParticle* partBuff = m_Group->GetBuffer();

	if( partBuff == NULL )
		return;

	SVertex* vertexBuff = (SVertex*)m_VertexBuffer.Lock( 0, 0 );

	UInt32 i;
    for( i=0; i<m_Group->GetParticleCapacity(); i++) 
	{
		CParticle& particle = partBuff[i];

		if( particle.Age >= 0.0f )
		{
			m_Group->GetParticleMatrix( cam, particle, rotationMatrix);

			CVector3f xVec = ( rotationMatrix.GetXComponent() ) / 2.0f;
			CVector3f yVec = ( rotationMatrix.GetYComponent() ) / 2.0f;
			CVector3f pos = particle.Position;

			vertexBuff[ (pCount*4)+0 ].Position = CVector3f( pos - xVec + yVec ) ;
			vertexBuff[ (pCount*4)+0 ].TexCoord0 = CVector2f( 0.0f, 0.0f );
			vertexBuff[ (pCount*4)+0 ].Color = particle.Color;

			vertexBuff[ (pCount*4)+1 ].Position = CVector3f( pos + xVec + yVec ) ;
			vertexBuff[ (pCount*4)+1 ].TexCoord0 = CVector2f( 1.0f, 0.0f );
			vertexBuff[ (pCount*4)+1 ].Color = particle.Color;

			vertexBuff[ (pCount*4)+2 ].Position = CVector3f( pos + xVec - yVec ) ;
			vertexBuff[ (pCount*4)+2 ].TexCoord0 = CVector2f( 1.0f, 1.0f );
			vertexBuff[ (pCount*4)+2 ].Color = particle.Color;

			vertexBuff[ (pCount*4)+3 ].Position = CVector3f( pos - xVec - yVec ) ;
			vertexBuff[ (pCount*4)+3 ].TexCoord0 = CVector2f( 0.0f, 1.0f );
			vertexBuff[ (pCount*4)+3 ].Color = particle.Color;

			pCount++;
		}
    }

    m_VertexBuffer.UnLock();
        
	m_IndexBuffer.SetDrawIndexCount( 6 * pCount );
	
}

Bool CParticleSystem::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;

	if( ar.BeginScope( WT("ParticleSystem"), version ) == 0 )
	{
		ar.Serialize( m_Material, WT("Material") );
		ar.Serialize( m_Group, WT("Group") );

		ar.EndScope();
	}
	else
	{
		return FALSE;
	}

	return CNodeRender::Serialize( ar );
}

Bool CParticleSystem::Update()
{
	DebugError("Need to be updated");/*
    m_Group->Update( *this, renderer );
	RebuildBuffer( renderer );*/
    return CNodeRender::Update();
}

Void CParticleSystem::SetGroup(CParticleGroup& simulator)
{
	m_Group = &simulator;
}

Void CParticleSystem::SetMaterial( CMaterial* material )
{
	m_Material = material;
}

CMaterial& CParticleSystem::GetParticleMaterial( ) const
{
    return *GetModel()->GetSubset(0).Material;
}

Void CParticleSystem::InitializeStreamData( CArray<SVertex>& data, UInt32 particleCapacity )
{
	UInt32 i;
	data.SetItemCount( particleCapacity * 4 );

	for( i=0;i<particleCapacity;i++ )
	{
		SVertex& v0 = data[(i*4)+0];
		SVertex& v1 = data[(i*4)+1];
		SVertex& v2 = data[(i*4)+2];
		SVertex& v3 = data[(i*4)+3];

		v0.Position = CVector3f( -1.0f, +1.0f, 0.0f );
		v1.Position = CVector3f( +1.0f, +1.0f, 0.0f );
		v2.Position = CVector3f( +1.0f, -1.0f, 0.0f );
		v3.Position = CVector3f( -1.0f, -1.0f, 0.0f );
	}
}

Void CParticleSystem::InitializeIndexData( CArrayUInt32& data, UInt32 particleCapacity )
{
	UInt32 i;
	data.SetItemCount( particleCapacity * 6 );

	for( i=0;i<particleCapacity;i++ )
	{
		data[(i*6)+0] = (i*4)+0;
		data[(i*6)+1] = (i*4)+1;
		data[(i*6)+2] = (i*4)+2;

		data[(i*6)+3] = (i*4)+2;
		data[(i*6)+4] = (i*4)+3;
		data[(i*6)+5] = (i*4)+0;
	}
}

Void CParticleSystem::Initialize( )
{
	CArray<SVertex> streamData;
	CArrayUInt32 indexBufferData;

	m_VertexBuffer.SetAttribute( CGeometryVertexBuffer::nFlag_Dynamic );
	
	m_VertexLayout.AddElement( nVertexComponent_Position, nVertexComponentType_Float3 );
	m_VertexLayout.AddElement( nVertexComponent_TexCoord0, nVertexComponentType_Float2 );
	m_VertexLayout.AddElement( nVertexComponent_Color0, nVertexComponentType_Float4 );
	m_VertexLayout.Initialize();

	InitializeStreamData( streamData, m_Group->GetParticleCapacity() );
	m_VertexBuffer.SetRawData( streamData.GetItemCount(), sizeof( SVertex ), (Byte*) streamData.GetBuffer() );

	m_VertexBuffer.Load();

	InitializeIndexData( indexBufferData, m_Group->GetParticleCapacity() );

	m_IndexBuffer.SetRawData( indexBufferData.GetItemCount(), sizeof( UInt32 ),	(Byte*)indexBufferData.GetBuffer() );

	m_IndexBuffer.Load( );

	m_Mesh.SetVertexBuffer( &m_VertexBuffer );
	m_Mesh.SetIndexBuffer( &m_IndexBuffer );
	m_Mesh.SetVertexLayout( &m_VertexLayout );

	m_Model.SetSubsetCount(1);
	m_Model.GetSubset(0).Mesh = &m_Mesh;
	m_Model.GetSubset(0).Material = m_Material;
	SetModel( &m_Model );

	if( m_Material->GetShader() == NULL )
	{
		DebugLogWarning( "CParticleSystem::Initialize - Material is not using any shader");
		CShader* sh = NEWOBJ( CShader, (  ) );
		sh->Load(   CoreManager.GetFileSystem().GetFilePath( "System/Shader", "RendererPass/Particle/Particle.vsh" ),
                    CoreManager.GetFileSystem().GetFilePath( "System/Shader", "RendererPass/Particle/Particle.psh" ),
                    CFilePath() );
        m_Material->SetShader( sh );
	}
	
	m_Material->Load();

	if( m_Material->GetShader()->GetBlendStates() )
	{
		m_BlendStates = m_Material->GetShader()->GetBlendStates();
	}
	else
	{
		DebugLogWarning( "CParticleSystem::Initialize - Material used does not contain any Blend States");
		m_BlendStates = NEWOBJ( CStatesBlend, () );

		CStatesBlend::SDesc blendDesc;
		blendDesc.BlendEnable[0] = TRUE;
		blendDesc.SrcColorBlend = nStateBlend_SrcAlpha;
		blendDesc.DstColorBlend = nStateBlend_InvSrcAlpha;
		m_BlendStates->Acquire( blendDesc );

		m_Material->GetShader()->SetBlendStates( m_BlendStates );
	}

	if( m_Material->GetShader()->GetDepthStencilStates() )
	{
		m_DepthStencilStates = m_Material->GetShader()->GetDepthStencilStates();
	}
	else
	{
		DebugLogWarning( "CParticleSystem::Initialize - Material used does not contain any Depth Stencil States");
		m_DepthStencilStates = NEWOBJ( CStatesDepthStencil, () );
		CStatesDepthStencil::SDesc dsDesc;
		dsDesc.DepthTestEnable = TRUE;
		dsDesc.DepthWriteEnable = FALSE;
		m_DepthStencilStates->Acquire( dsDesc );
		m_Material->GetShader()->SetDepthStencilStates( m_DepthStencilStates );
	}

	SetAttribute( nAttribute_DoNotRenderToDepthBuffer, TRUE ) ;

}

Void CParticleSystem::Initialize(  CNodeSpatial& parent, CParticleGroup& sim, CMaterial& material )
{
	SetGroup( sim );
	SetMaterial( &material );
	SetParent( &parent );

	Initialize();
}

CStatesBlend& CParticleSystem::GetBlendStates()
{
	return *m_BlendStates;
}

