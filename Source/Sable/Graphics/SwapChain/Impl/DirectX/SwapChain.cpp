#include <Sable\Graphics\SwapChain\Impl\DirectX\SwapChain.h>

#include <Sable\Application\Window.h>
#include <Sable\Graphics\Common\Impl\DirectX\GraphicsManagerHelper.h>

#include <DXGI.h>

using namespace Sable;

CImplDirectXSwapChain::CImplDirectXSwapChain(  CSwapChain& swapChain ):
    CImplStubSwapChain( swapChain )
{
    m_SwapChain = NULL;
}

CImplDirectXSwapChain::~CImplDirectXSwapChain()
{
	
}

IDXGISwapChain* CImplDirectXSwapChain::GetD3DSwapChain() const
{
    return m_SwapChain;
}

Bool CImplDirectXSwapChain::Initialize( ) 
{
    DebugAssertMsg( m_PublicImpl->GetOwnerWindow(), "Owner window was probably not initialized" );

    IDXGIFactory* pFactory;
    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();

    const CSwapChainInfo& sbDesc = m_PublicImpl->GetInfo();

    DXGI_SWAP_CHAIN_DESC desc;
    MemoryFill( &desc, 0, sizeof( desc ) );
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//CImplDirectXGraphicsManagerHelper::TranslatePixelFormat( sbDesc.TextureInfo.Format );
    desc.BufferDesc.Width = sbDesc.RenderTargetInfo.TextureInfo.Width;
    desc.BufferDesc.Height = sbDesc.RenderTargetInfo.TextureInfo.Height;
    desc.BufferDesc.RefreshRate.Numerator = sbDesc.DesiredFPS;
    desc.BufferDesc.RefreshRate.Denominator = 1;
    desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    desc.BufferCount = 2;
    desc.OutputWindow = (HWND)m_PublicImpl->GetOwnerWindow()->GetHandle();
    desc.Windowed = !sbDesc.FullScreen;
    desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    desc.SampleDesc = CImplDirectXGraphicsManagerHelper::TranslateMultiSampling( sbDesc.RenderTargetInfo.MultiSamplingQuality );
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.Flags = 0;

    IDXGIDevice * pDXGIDevice;
    IDXGIAdapter * pDXGIAdapter;
    AssertDXCall( device->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice) );
    AssertDXCall( pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&pDXGIAdapter) );
    AssertDXCall( pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&pFactory) );

    AssertDXCall( pFactory->CreateSwapChain( device, &desc, &m_SwapChain ) );

    return TRUE;
}

Bool CImplDirectXSwapChain::Present( )
{
    HRESULT hr;
    DebugAssert( m_SwapChain );

    {
        DebugProfile("CImplDirectXGraphicsManager::Present" );
        hr = m_SwapChain->Present( 0, 0 );
    }

    if( hr != S_OK )
    {
        return FALSE;
    }

    return TRUE;
}

Void CImplDirectXSwapChain::Resize( const CVector2i& newSize )
{
	CImplDirectXRenderTargetBackBuffer& backBuffer = m_PublicImpl->GetBackBuffer().GetImpl();
	ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();
	device->OMSetRenderTargets(0, 0, 0);

	// Release all outstanding references to the swap chain's buffers.
	ReleaseDXResource( backBuffer.m_RenderTargetView );

	// Preserve the existing buffer count and format.
	// Automatically choose the width and height to match the client rect for HWNDs.
	AssertDXCall( m_SwapChain->ResizeBuffers(0, newSize.GetX(),newSize.GetY(), DXGI_FORMAT_UNKNOWN, 0) );

}