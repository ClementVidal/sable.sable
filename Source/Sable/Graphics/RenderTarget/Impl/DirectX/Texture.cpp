#include <Sable\Graphics\RenderTarget\Impl\DirectX\Texture.h>

#include <Sable\Graphics\Common\Impl\DirectX\GraphicsManagerHelper.h>
#include <Sable\Graphics\RenderTarget\Impl\DirectX\Helper.h>

using namespace Sable;

extern CImplDirectXRenderTargetHelper  ImplMswRenderTargetHelper;

CImplDirectXRenderTargetTexture::CImplDirectXRenderTargetTexture( CRenderTargetTexture& publicImpl ):
    CImplStubRenderTargetTexture( publicImpl )
{
	m_Texture = NULL;
    m_RenderTargetView = NULL;
}

CImplDirectXRenderTargetTexture::~CImplDirectXRenderTargetTexture()
{
	if( m_Texture )
	{
		if( m_Texture->Release() != 0 )
		{
//			DebugLogWarning("CImplDirectXRenderTargetTexture::~CImplDirectXRenderTargetTexture - Unfreed texture resource");
		}
	}
	m_Texture = NULL;


}

Void CImplDirectXRenderTargetTexture::Activate( Int32 index )
{
    ImplMswRenderTargetHelper.ActivateRenderTarget( index, &m_RenderTargetView );
}


ID3D10Texture2D* CImplDirectXRenderTargetTexture::GetD3DTexture( )
{
	return m_Texture;
}


Void CImplDirectXRenderTargetTexture::Initialize( const CRenderTargetInfo& info )
{
    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();

	ReleaseDXResource( m_Texture );
	ReleaseDXResource( m_RenderTargetView );

    D3D10_TEXTURE2D_DESC txDesc;
    MemoryFill( &txDesc, 0, sizeof(txDesc) );
    txDesc.Width = info.TextureInfo.Width;
    txDesc.Height = info.TextureInfo.Height;
    txDesc.Format = CImplDirectXGraphicsManagerHelper::TranslatePixelFormat( info.TextureInfo.Format );
    txDesc.MipLevels = 1;
    txDesc.ArraySize = 1;
    txDesc.SampleDesc = CImplDirectXGraphicsManagerHelper::TranslateMultiSampling( info.MultiSamplingQuality );
    txDesc.Usage = D3D10_USAGE_DEFAULT;
    txDesc.BindFlags = D3D10_BIND_RENDER_TARGET;

    AssertDXCall( device->CreateTexture2D( &txDesc, NULL, &m_Texture ) );

    D3D10_RENDER_TARGET_VIEW_DESC rtDesc;
    MemoryFill( &rtDesc, 0, sizeof( rtDesc ) );
    rtDesc.Format = txDesc.Format;
    rtDesc.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;
    rtDesc.Texture2D.MipSlice = 0;

    AssertDXCall( device->CreateRenderTargetView( m_Texture, &rtDesc, &m_RenderTargetView ) );

	ReleaseDXResource( m_Texture );
}

Void CImplDirectXRenderTargetTexture::Clear( const CColor& col )
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