#include <Sable\Graphics\Viewport\Impl\DirectX\Viewport.h>

#include <Sable\Graphics\Common\Impl\DirectX\GraphicsManagerHelper.h>

#include <D3D10.h>

using namespace Sable;

CImplDirectXViewport::CImplDirectXViewport( CViewport& publicImpl ):
    CImplStubViewport( publicImpl )
{
    m_PublicImpl = &publicImpl;
}

CImplDirectXViewport::~CImplDirectXViewport()
{
	
}

Void CImplDirectXViewport::Activate()
{
    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();

    D3D10_VIEWPORT viewports[1];

    //define viewports
    viewports[0].Width = m_PublicImpl->GetWidth();
    viewports[0].Height = m_PublicImpl->GetHeight();
    viewports[0].MinDepth = m_PublicImpl->GetMinDepth();
    viewports[0].MaxDepth = m_PublicImpl->GetMaxDepth();
    viewports[0].TopLeftX = m_PublicImpl->GetTopLeftX();
    viewports[0].TopLeftY = m_PublicImpl->GetTopLeftY();

    device->RSSetViewports( 1, viewports );
}
