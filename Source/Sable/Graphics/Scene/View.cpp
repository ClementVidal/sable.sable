#include <Sable\Graphics\Scene\View.h>

#include <Sable\Graphics\Scene\World.h>
#include <Sable\Graphics\Camera\Perspective.h>
#include <Sable\Graphics\Common\Header.h>
#include <Sable\Graphics\RenderTarget\Texture.h>
#include <Sable\Core\Debug\Primitives.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CSceneView, CManagedObject );

CSceneView::CSceneView()
{
}

CSceneView::~CSceneView()
{
    m_World = NULL;
    m_Camera = NULL;
}

Void CSceneView::SetCamera( CCamera* camera )
{
	m_Camera = camera;
    if( m_World && GetCamera() )
        GetCamera()->SetParent( &m_World->GetRootNode() );
}

Void CSceneView::SetWorld( CSceneWorld* world )
{
    m_World = world;
    if( m_Camera )
    {
        if( world )
        {
			if( GetCamera()->GetParent() == NULL )
			{
				GetCamera()->SetParent( &world->GetRootNode() );
			}
        }
        else
        {
            GetCamera()->SetParent( NULL );
        }
    }
}

/** 
Create and initialize the world, the Camera 
*/
Void CSceneView::Initialize( )
{
	m_Background = NEWOBJ_EX(  NULL , CScreenQuad, () );

	CColor col1( 0.3f, 0.3f, 0.3f );
	CColor col2( 0.6f, 0.6f, 0.6f );

	m_Background->Initialize( col1, col1, col2, col2 );

	m_BackgroundShader = NEWOBJ_EX(  NULL , CShader, ( ) );
	m_BackgroundShader->Load(   CoreManager.GetFileSystem().GetFilePath( "System/Shader", "System/ScreenQuad.vsh" ),
                                CoreManager.GetFileSystem().GetFilePath( "System/Shader", "System/ScreenQuad.psh" ),
                                CFilePath() );

	CStatesDepthStencil* depthStencilStates = NEWOBJ_EX(  NULL , CStatesDepthStencil, () );

	CStatesDepthStencil::SDesc dsDesc;
	dsDesc.DepthWriteEnable = FALSE;
	dsDesc.DepthTestEnable = FALSE;
	depthStencilStates->Acquire( dsDesc );
	
	CStatesBlend* blendStates = NEWOBJ_EX( NULL, CStatesBlend, () );
	CStatesBlend::SDesc blendDesc;
	blendDesc.BlendEnable[0] = FALSE;
	blendStates->Acquire( blendDesc );

	m_BackgroundShader->SetDepthStencilStates( depthStencilStates );
	m_BackgroundShader->SetBlendStates( blendStates );

}

Bool CSceneView::Update()
{
    if( m_World )
        m_World->Update( );

    return TRUE;
}

CCamera* CSceneView::GetCamera() const
{
    return m_Camera;
}

CSceneWorld* CSceneView::GetWorld() const
{
    return m_World;
}
