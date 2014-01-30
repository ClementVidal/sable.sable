#include <Sample/Application/Application.h>

#include <Sable/Graphics/SwapChain/SwapChain.h>
#include <Sable/Input/Mouse/Mouse.h>
#include <Sable/Input/Keyboard/Keyboard.h>
#include <Sable/Input/Common/Manager.h>

using namespace Sample;
namespace Sb = Sable;

CApplication::CApplication() : 
    Sb::CApplication()
{
    Initialize();
}

CApplication::~CApplication()
{

}

Void CApplication::Run()
{
    Bool v = TRUE;

    while( v )
    {
        v = Update();
    }
}

Bool CApplication::Update()
{
    if( !Sb::CApplication::Update() )
        return FALSE;

    return TRUE;
}

Void CApplication::Initialize()
{
    Sb::CApplication::Initialize();

    Sb::CSwapChainInfo desc;
    desc.RenderTargetInfo.TextureInfo.Format = nTextureFormat_R8G8B8A8;
    desc.RenderTargetInfo.TextureInfo.Width = 1024;
    desc.RenderTargetInfo.TextureInfo.Height = 768;
    desc.RenderTargetInfo.MultiSamplingQuality = nMultiSamplingQuality_None;
    m_Window.Initialize( desc );

    AddWindow( m_Window );

    Sb::CKeyboard* kbd = NEWOBJ( Sb::CKeyboard, (m_Window) );
    Sb::CMouse* mouse = NEWOBJ( Sb::CMouse, (m_Window) );

    InputManager.SetMouse( mouse );
    InputManager.SetKeyboard( kbd );

}
