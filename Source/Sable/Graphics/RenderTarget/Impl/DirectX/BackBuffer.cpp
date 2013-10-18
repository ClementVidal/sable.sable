#include <Sable/Graphics/RenderTarget/Impl/DirectX/BackBuffer.h>

#include <Sable/Graphics/SwapChain/SwapChain.h>
#include <Sable/Graphics/RenderTarget/Impl/DirectX/Helper.h>
#include <Sable/Graphics/Common/Impl/DirectX/GraphicsManagerHelper.h>

using namespace Sable;

extern CImplDirectXRenderTargetHelper  ImplMswRenderTargetHelper;

CImplDirectXRenderTargetBackBuffer::CImplDirectXRenderTargetBackBuffer( CRenderTargetBackBuffer& publicImpl ):
    CImplStubRenderTargetBackBuffer( publicImpl )
{
    m_RenderTargetView = NULL;
	m_Texture = NULL;
}

CImplDirectXRenderTargetBackBuffer::~CImplDirectXRenderTargetBackBuffer()
{
	ReleaseDXResource( m_Texture );
	ReleaseDXResource( m_RenderTargetView );
}

Void CImplDirectXRenderTargetBackBuffer::Activate( Int32 index )
{  
    ImplMswRenderTargetHelper.ActivateRenderTarget( index, &m_RenderTargetView );
}

Void CImplDirectXRenderTargetBackBuffer::Resize( const CVector2i& newSize )
{
	ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();

	ReleaseDXResource( m_Texture );
	ReleaseDXResource( m_RenderTargetView );
	DebugAssert( m_PublicImpl->GetOwnerSwapChain() );

	CSwapChain& swapChain = *m_PublicImpl->GetOwnerSwapChain();
	IDXGISwapChain* d3dSwapChain = swapChain.GetImpl().GetD3DSwapChain();

	// Grab texture from swapchain
	AssertDXCall( d3dSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&m_Texture) ) ;

	// Assert size are valids
	D3D10_TEXTURE2D_DESC textureDesc;
	m_Texture->GetDesc( &textureDesc );
	DebugAssert( textureDesc.Width == newSize.GetX() && textureDesc.Height == newSize.GetY() );

	// Create view Desc
	D3D10_RENDER_TARGET_VIEW_DESC rtDesc;
	MemoryFill( &rtDesc, 0, sizeof( rtDesc ) );
	rtDesc.Format = CImplDirectXGraphicsManagerHelper::TranslatePixelFormat( swapChain.GetInfo().RenderTargetInfo.TextureInfo.Format );
	if( swapChain.GetInfo().RenderTargetInfo.MultiSamplingQuality != nMultiSamplingQuality_None)
		rtDesc.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2DMS;
	else
		rtDesc.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;
	rtDesc.Texture2D.MipSlice = 0;

	// Recreate view
	AssertDXCall( device->CreateRenderTargetView(m_Texture, &rtDesc, &m_RenderTargetView) );

	ReleaseDXResource( m_Texture );
}

Void CImplDirectXRenderTargetBackBuffer::Initialize()
{
    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();

	ReleaseDXResource( m_Texture );
	ReleaseDXResource( m_RenderTargetView );
	DebugAssert( m_PublicImpl->GetOwnerSwapChain() );

	CSwapChain& swapChain = *m_PublicImpl->GetOwnerSwapChain();
    IDXGISwapChain* d3dSwapChain = swapChain.GetImpl().GetD3DSwapChain();

    AssertDXCall( d3dSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&m_Texture) ) ;

    D3D10_RENDER_TARGET_VIEW_DESC rtDesc;
    MemoryFill( &rtDesc, 0, sizeof( rtDesc ) );
    rtDesc.Format = CImplDirectXGraphicsManagerHelper::TranslatePixelFormat( swapChain.GetInfo().RenderTargetInfo.TextureInfo.Format );
    if( swapChain.GetInfo().RenderTargetInfo.MultiSamplingQuality != nMultiSamplingQuality_None)
        rtDesc.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2DMS;
    else
        rtDesc.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;
    rtDesc.Texture2D.MipSlice = 0;

    AssertDXCall( device->CreateRenderTargetView(m_Texture, &rtDesc, &m_RenderTargetView) );

	ReleaseDXResource( m_Texture );
}

Void CImplDirectXRenderTargetBackBuffer::Clear( const CColor& col )
{
    DebugAssert( m_RenderTargetView );

    float color[4];

    color[0] = col.GetR();
    color[1] = col.GetG();
    color[2] = col.GetB();
    color[3] = col.GetA();

    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();
    device->ClearRenderTargetView( m_RenderTargetView, color );
}