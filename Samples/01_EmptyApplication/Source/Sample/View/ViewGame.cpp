#include <Sample\View\ViewGame.h>

#include <Sample\Application\Renderer.h>

#include <Sable\Graphics\Camera\Perspective.h>
#include <Sable\Graphics\Scene\World.h>
#include <Sable\Graphics\Debug\RenderPass.h>
#include <Sable\Graphics\Common\Manager.h>

using namespace Sample;

IMPLEMENT_MANAGED_CLASS1( Sample, CViewGame, CView );

CViewGame::CViewGame()
{
}

CViewGame::CViewGame(CApplication& app) : 
    CView()
{
}

CViewGame::~CViewGame()
{
}

Void CViewGame::Initialize()
{
    CVector3f position;

    // Create Renderer
    CGameRenderer* renderer = NEWOBJ( CGameRenderer, ( *this, GraphicsManager.GetRenderTargetBackBuffer() ) );
    SetRenderer(*renderer);

    // Create Camera
    CCameraPerspective* camera = NEWOBJ( CCameraPerspective, () );
    SetCamera(camera);

    // Create World
    CSceneWorld* world = NEWOBJ( CSceneWorld, ( *this ) );
    SetWorld( world );

    position.Set(20,20,20.0f);
    camera->SetParent( world->GetRootNode() );
    camera->SetCameraPosition(position);

    CView::Initialize();

    camera->SetAspect( (Float32) renderer->GetRenderTarget().GetHeight() / (Float32) renderer->GetRenderTarget().GetWidth() );
    camera->SetFOV( MathPi / 2.5f );

}

Void CViewGame::Update()
{
    CView::Update();
}

Void CViewGame::Render()
{
    CDebugRenderPass& debugRp = *GetRenderer().GetDebugRenderPass();

    debugRp.PushViewProjMatrix();

    debugRp.BeginLineList();

        debugRp.DrawLine( CVector3f( 0.0f, 0.0f, 0.0f ), CVector3f( 0.0f, 1.0f, 0.0f )  );
        debugRp.DrawLine( CVector3f( 0.0f, 0.0f, 0.0f ), CVector3f( 0.0f, 0.0f, 1.0f )  );
        debugRp.DrawLine( CVector3f( 0.0f, 0.0f, 0.0f ), CVector3f( 1.0f, 0.0f, 0.0f )  );

    debugRp.EndLineList();

    debugRp.PopViewProjMatrix();

    CView::Render();
}