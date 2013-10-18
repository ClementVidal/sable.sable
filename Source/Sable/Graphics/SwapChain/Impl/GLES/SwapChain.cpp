#include <Sable/Graphics/SwapChain/Impl/GLES/SwapChain.h>

#include <Sable/Application/Window.h>
#include <Sable/Graphics/Common/Impl/GLES/GraphicsManagerHelper.h>

using namespace Sable;

extern CImplGLESGraphicsManagerHelper ImplGLESGraphicsManagerHelper;

CImplGLESSwapChain::CImplGLESSwapChain( CSwapChain& swapChain ):
    CImplStubSwapChain( swapChain )
{
	m_Surface = NULL;
}

CImplGLESSwapChain::~CImplGLESSwapChain()
{
	
}

Bool CImplGLESSwapChain::Initialize( )
{
	m_Surface = DebugAssertEGLCall(eglCreateWindowSurface(ImplGLESGraphicsManagerHelper.GetEGLDisplay(), ImplGLESGraphicsManagerHelper.GetEGLConfig(), (EGLNativeWindowType)m_PublicImpl->GetOwnerWindow()->GetHandle(), NULL));

	DebugAssertEGLCall(eglMakeCurrent(ImplGLESGraphicsManagerHelper.GetEGLDisplay(), m_Surface, m_Surface, ImplGLESGraphicsManagerHelper.GetEGLContext()));

    return TRUE;
}

Bool CImplGLESSwapChain::Present( )
{
    // Just fill the screen with a color.
    eglSwapBuffers(ImplGLESGraphicsManagerHelper.GetEGLDisplay(), m_Surface );

    return TRUE;
}
