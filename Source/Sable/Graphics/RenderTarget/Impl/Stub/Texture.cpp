#include <Sable\Graphics\RenderTarget\Impl\Stub\Texture.h>

using namespace Sable;

CImplStubRenderTargetTexture::CImplStubRenderTargetTexture( CRenderTargetTexture& publicImpl )
{
    m_PublicImpl = &publicImpl;
}

CImplStubRenderTargetTexture::~CImplStubRenderTargetTexture( )
{
}