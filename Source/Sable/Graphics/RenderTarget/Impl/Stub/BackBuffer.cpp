#include <Sable\Graphics\RenderTarget\Impl\Stub\BackBuffer.h>

using namespace Sable;

CImplStubRenderTargetBackBuffer::CImplStubRenderTargetBackBuffer( CRenderTargetBackBuffer& publicImpl )
{
    m_PublicImpl = &publicImpl;
}

CImplStubRenderTargetBackBuffer::~CImplStubRenderTargetBackBuffer( )
{

}
