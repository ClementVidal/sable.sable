#include <Sable\Graphics\Texture\Impl\DirectX\TextureCube.h>

using namespace Sable;

CImplDirectXTextureCube::CImplDirectXTextureCube()
{
	m_Texture = NULL;
	m_ShaderView = NULL;
	m_CurrentLevelLocked = 0;
	m_MipMapLevel = 0;
}

CImplDirectXTextureCube::~CImplDirectXTextureCube()
{
	if( m_Texture )
	{
		UInt32 r  = m_Texture->Release();
		DebugAssert( r == 0 );
	}
	m_Texture = NULL;
	m_ShaderView = NULL;
}

ID3D10ShaderResourceView* CImplDirectXTextureCube::GetD3DTextureShaderView() const
{
	return m_ShaderView;
}

Void CImplDirectXTextureCube::Initialize( const CTextureInfo& info, const Byte* data )
{
	ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();

	DebugAssertMsg( info.MipMapCount == 1, "Not yet implemented" );

	D3D10_TEXTURE2D_DESC desc;
	MemoryFill( &desc, 0, sizeof(desc) );
	desc.Width = info.Width;
	desc.Height = info.Height;
	desc.MipLevels = info.MipMapCount;
	desc.ArraySize = 6;
	desc.Format = CImplDirectXGraphicsManagerHelper::TranslatePixelFormat( info.Format );
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D10_USAGE_DEFAULT;
	desc.CPUAccessFlags = 0;
	desc.BindFlags = D3D10_BIND_SHADER_RESOURCE;
    desc.MiscFlags = D3D10_RESOURCE_MISC_TEXTURECUBE;

    D3D10_SUBRESOURCE_DATA subRscData[6];
    MemoryFill( &subRscData, 0, sizeof( D3D10_SUBRESOURCE_DATA ) * 6 );
    subRscData[0].pSysMem = data + info.GetSurfaceByteCount() * 0;
    subRscData[0].SysMemPitch = info.GetLinePitch( 0 );
    subRscData[1].pSysMem = data + info.GetSurfaceByteCount() * 1;
    subRscData[1].SysMemPitch = info.GetLinePitch( 0 );
    subRscData[2].pSysMem = data + info.GetSurfaceByteCount() * 2;
    subRscData[2].SysMemPitch = info.GetLinePitch( 0 );
    subRscData[3].pSysMem = data + info.GetSurfaceByteCount() * 3;
    subRscData[3].SysMemPitch = info.GetLinePitch( 0 );
    subRscData[4].pSysMem = data + info.GetSurfaceByteCount() * 4;
    subRscData[4].SysMemPitch = info.GetLinePitch( 0 );
    subRscData[5].pSysMem = data + info.GetSurfaceByteCount() * 5;
    subRscData[5].SysMemPitch = info.GetLinePitch( 0 );


	AssertDXCall( device->CreateTexture2D( &desc, subRscData, &m_Texture ) );

	m_Texture->GetDesc( &desc );
	m_MipMapLevel = desc.MipLevels;

	D3D10_SHADER_RESOURCE_VIEW_DESC viewDesc;
	MemoryFill( &viewDesc, 0, sizeof( viewDesc ) );
	viewDesc.Format = desc.Format;
	viewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURECUBE;
    viewDesc.TextureCube.MipLevels = desc.MipLevels;
    viewDesc.TextureCube.MostDetailedMip = 0;

	AssertDXCall( device->CreateShaderResourceView( m_Texture, &viewDesc, &m_ShaderView ) );
}

