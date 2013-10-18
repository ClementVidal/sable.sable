#include <Sable/Graphics/RenderTarget/Impl/GLES/DepthStencil.h>

using namespace Sable;

CImplGLESRenderTargetDepthStencil::CImplGLESRenderTargetDepthStencil( CRenderTargetDepthStencil& publicImpl  ):
    CImplStubRenderTargetDepthStencil( publicImpl )
{
}

CImplGLESRenderTargetDepthStencil::~CImplGLESRenderTargetDepthStencil()
{
}

Void CImplGLESRenderTargetDepthStencil::Activate( )
{

}

Void CImplGLESRenderTargetDepthStencil::Initialize( const CRenderTargetInfo& info )
{

}

Void CImplGLESRenderTargetDepthStencil::Clear( Float32 depth, UInt8 stencil )
{
	glClearDepthf( depth );
	glClearStencil( stencil );
	glClear( GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
