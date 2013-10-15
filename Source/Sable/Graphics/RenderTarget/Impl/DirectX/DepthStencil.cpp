#include <Sable\Graphics\RenderTarget\Impl\DirectX\DepthStencil.h>

#include <Sable\Graphics\RenderTarget\Impl\DirectX\Helper.h>
#include <Sable\Graphics\Common\Impl\DirectX\GraphicsManagerHelper.h>

using namespace Sable;

extern CImplDirectXRenderTargetHelper  ImplMswRenderTargetHelper;

CImplDirectXRenderTargetDepthStencil::CImplDirectXRenderTargetDepthStencil( CRenderTargetDepthStencil& publicImpl  ):
    CImplStubRenderTargetDepthStencil( publicImpl )
{
	m_Texture = NULL;
    m_DepthStencilView = NULL;
}

CImplDirectXRenderTargetDepthStencil::~CImplDirectXRenderTargetDepthStencil()
{
	if( m_Texture )
	{
		if( m_Texture->Release() != 0 )
		{
//			DebugLogWarning("CImplDirectXRenderTargetDepthStencil::~CImplDirectXRenderTargetDepthStencil - Unfreed texture resource");
		}
	}
	m_Texture = NULL;


}

Void CImplDirectXRenderTargetDepthStencil::Activate( )
{
    ImplMswRenderTargetHelper.ActivatedepthStencil( &m_DepthStencilView );
}


ID3D10Texture2D* CImplDirectXRenderTargetDepthStencil::GetD3DTexture( )
{
	return m_Texture;
}


Void CImplDirectXRenderTargetDepthStencil::Initialize( const CRenderTargetInfo& info )
{
    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();

	ReleaseDXResource( m_Texture );
	ReleaseDXResource( m_DepthStencilView );

    DebugAssert( info.TextureInfo.Format == nTextureFormat_D24S8 );

    D3D10_TEXTURE2D_DESC txDesc;
    MemoryFill( &txDesc, 0, sizeof(txDesc) );
    txDesc.Width = info.TextureInfo.Width;
    txDesc.Height = info.TextureInfo.Height;
    txDesc.Format = CImplDirectXGraphicsManagerHelper::TranslatePixelFormat( info.TextureInfo.Format );
    txDesc.MipLevels = 1;
    txDesc.ArraySize = 1;
    txDesc.SampleDesc = CImplDirectXGraphicsManagerHelper::TranslateMultiSampling( info.MultiSamplingQuality );
    txDesc.Usage = D3D10_USAGE_DEFAULT;
    txDesc.BindFlags = D3D10_BIND_DEPTH_STENCIL;

    AssertDXCall( device->CreateTexture2D( &txDesc, NULL, &m_Texture ) );

    D3D10_DEPTH_STENCIL_VIEW_DESC rtDesc;
    MemoryFill( &rtDesc, 0, sizeof( rtDesc ) );
    rtDesc.Format = txDesc.Format;
    if( txDesc.SampleDesc.Quality > 0)
        rtDesc.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2DMS;
    else
        rtDesc.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
    rtDesc.Texture2D.MipSlice = 0;

    AssertDXCall( device->CreateDepthStencilView( m_Texture, &rtDesc, &m_DepthStencilView ) );
}

Void CImplDirectXRenderTargetDepthStencil::Resize( const CVector2i& newSize )
{
	CRenderTargetInfo info = m_PublicImpl->GetInfo();
	info.TextureInfo.Width = newSize.GetX();
	info.TextureInfo.Height = newSize.GetY();

	Initialize( info );
}

Void CImplDirectXRenderTargetDepthStencil::Clear( Float32 depth, UInt8 stencil )
{
    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();
    device->ClearDepthStencilView( m_DepthStencilView, D3D10_CLEAR_DEPTH|D3D10_CLEAR_STENCIL, depth, stencil );
}