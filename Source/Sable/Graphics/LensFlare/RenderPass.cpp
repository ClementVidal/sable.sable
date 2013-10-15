#include <Sable\Graphics\LensFlare\RenderPass.h>

#include <Sable\Graphics\RenderPass\Depth.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CLensFlareRenderPass );


CLensFlareRenderPass::CLensFlareRenderPass( CRenderer& renderer ):
    CRenderPass( renderer )
{
    SVertex buffer[4];

    m_Shader = NEWOBJ( CShader, ( ) );
    m_Shader->Load( CoreManager.GetFileSystem().GetFilePath( "System/Shader", "World/LensFlare.vsh" ),
                    CoreManager.GetFileSystem().GetFilePath( "System/Shader", "World/LensFlare.psh" ),
                    CFilePath() );

    m_VertexLayout.AddElement( nVertexComponent_Position, nVertexComponentType_Float2 );
    m_VertexLayout.AddElement( nVertexComponent_TexCoord0, nVertexComponentType_Float2 );
	m_VertexLayout.Initialize();

    buffer[ 0 ].Pos = CVector2f( -1.0f,  1.0f );
    buffer[ 1 ].Pos = CVector2f(  1.0f,  1.0f );
    buffer[ 2 ].Pos = CVector2f( -1.0f, -1.0f );
    buffer[ 3 ].Pos = CVector2f(  1.0f, -1.0f );

    buffer[ 0 ].TexCoord0 = CVector2f( 0.0f, 0.0f );
    buffer[ 1 ].TexCoord0 = CVector2f( 1.0f, 0.0f );
    buffer[ 2 ].TexCoord0 = CVector2f( 0.0f, 1.0f );
    buffer[ 3 ].TexCoord0 = CVector2f( 1.0f, 1.0f );

	m_VertexBuffer.SetRawData( 4, sizeof( SVertex ), (Byte*) buffer );

    m_VertexBuffer.Load();

    m_FlareCount = 0;
}

CLensFlareRenderPass::~CLensFlareRenderPass()
{
}

Void CLensFlareRenderPass::Initialize(CRenderer &renderer)
{
    CRenderPass::Initialize( renderer );

	CStatesDepthStencil::SDesc dsDesc;
	dsDesc.DepthTestEnable = FALSE;
	m_DepthStates.Acquire( dsDesc );

	CStatesBlend::SDesc blendDesc;
	blendDesc.BlendEnable[0] = TRUE;
	blendDesc.SrcColorBlend = nStateBlend_SrcAlpha;
	blendDesc.DstColorBlend = nStateBlend_InvSrcAlpha;
	m_BlendStates.Acquire( blendDesc );
}

Void CLensFlareRenderPass::AddLensFlare( CLensFlare& flare )
{
    m_FlareTable[m_FlareCount] = &flare;
    m_FlareCount++;
}

Bool CLensFlareRenderPass::ProcessTraversedNode( CNode& node, CRenderer& renderer )
{
    const CTypeInfo& type = node.GetTypeInfo();

    if( type.IsKindOf( CLensFlare::GetStaticTypeInfo() ) ) {

        AddLensFlare( (CLensFlare&)node );
    }

	return TRUE;
}

Void CLensFlareRenderPass::Render( CRenderer& renderer )
{
    UInt32 j;
	DebugGraphicCommandGroup( "CLensFlareRenderPass::Render" );

    UInt32 i;
    CCamera& currentCamera = *GetRenderer().GetView()->GetCamera();
    CMatrix4x4f viewProj = currentCamera.GetViewProjectionMatrix();

    renderer.Activate( *m_Shader );

    renderer.Activate( m_DepthStates );
	renderer.Activate(m_BlendStates );

    renderer.Activate( m_VertexBuffer, 0 );
    
    for( j=0; j<m_FlareCount; j++)
    {
        CVector3f pos = m_FlareTable[j]->GetWorldPosition();
        pos.TransformPosition( viewProj );
        CVector2f dir, posFlare, posSpot;
        CColor color;

        posFlare = CVector2f( pos.GetX(), pos.GetY() );
        dir = -posFlare;
        dir.Normalize();
        
        Float32 borderHNDist = ( 1.0f + posFlare.GetX() );
        Float32 borderHPDist = 2.0f - ( 1.0f + posFlare.GetX() );
        Float32 borderVNDist = ( 1.0f + posFlare.GetY() );
        Float32 borderVPDist = 2.0f - ( 1.0f + posFlare.GetY() );

        Float32 borderDist = MathMin( MathMin( borderHNDist, borderHPDist), MathMin( borderVNDist, borderVPDist) );
        
        if( renderer.GetDepthRenderPass() )
            m_Shader->GetParameter( "DepthTexture" )->SetValue( renderer.GetDepthRenderPass()->GetDepthTexture() );
        
        //Render Flare only if it's within the screen
        if( posFlare.GetX() > -1.0f && posFlare.GetX() < 1.0f && 
            posFlare.GetY() > -1.0f && posFlare.GetY() < 1.0f && pos.GetZ() < 1.0f ) {

            for( i = 0; i<m_FlareTable[j]->GetSpotCount(); i++ ) {
                CLensFlare::SSpot& spot = m_FlareTable[j]->GetSpotAtIndex( i );
                color = spot.Color;
                color.a *= borderDist;
                posSpot = posFlare + dir * spot.Pos * m_FlareTable[j]->GetLength();
                m_Shader->GetParameter( "Texture" )->SetValue( *spot.Texture );
                m_Shader->GetParameter( "Size" )->SetValue( spot.Size );
                m_Shader->GetParameter( "SpotPos" )->SetValue( posSpot );
                m_Shader->GetParameter( "FlarePos" )->SetValue( posFlare );
                m_Shader->GetParameter( "Color" )->SetValue( color );
                
				renderer.Draw( nPrimitiveType_TriangleStrip, m_VertexBuffer.GetVertexCount(), 0 );
            }
        }
    }
    m_FlareCount = 0;
}
