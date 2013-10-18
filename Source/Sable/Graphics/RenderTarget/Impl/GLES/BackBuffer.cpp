#include <Sable/Graphics/RenderTarget/Impl/GLES/BackBuffer.h>

#include <Sable/Graphics/SwapChain/SwapChain.h>

using namespace Sable;


CImplGLESRenderTargetBackBuffer::CImplGLESRenderTargetBackBuffer( CRenderTargetBackBuffer& publicImpl ):
    CImplStubRenderTargetBackBuffer( publicImpl )
{

}

CImplGLESRenderTargetBackBuffer::~CImplGLESRenderTargetBackBuffer()
{
}

Void CImplGLESRenderTargetBackBuffer::Activate( Int32 index )
{  
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

Void CImplGLESRenderTargetBackBuffer::Initialize( CSwapChain& swapChain )
{

}

Void CImplGLESRenderTargetBackBuffer::Clear( const CColor& col )
{
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
	glClearColor( col.GetR(), col.GetG(), col.GetB(), col.GetA() );
	glClear(GL_COLOR_BUFFER_BIT);
}
