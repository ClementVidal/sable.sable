#include <Sable\Graphics\Texture\Impl\DirectX\Texture2D.h>

using namespace Sable;

CImplDirectXTexture2D::CImplDirectXTexture2D()
{
	m_Texture = NULL;
	m_CurrentLevelLocked = -1;
    m_MipMapLevel = 0;
	m_ShaderView = NULL;
}

CImplDirectXTexture2D::~CImplDirectXTexture2D()
{
	if( m_Texture )
	{
		if( m_Texture->Release() != 0 )
		{
//			DebugLogWarning("CImplDirectXTexture2D::~CImplDirectXTexture2D - Unfreed texture resource");
		}
	}
	m_Texture = NULL;
}

ID3D10ShaderResourceView* CImplDirectXTexture2D::GetD3DTextureShaderView() const
{
	return m_ShaderView;
}

Void CImplDirectXTexture2D::Initialize( const CTextureInfo& info, Bool lockable, const Byte* data )
{
    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();

    D3D10_TEXTURE2D_DESC desc;
    MemoryFill( &desc, 0, sizeof(desc) );
    desc.Width = info.Width;
    desc.Height = info.Height;
	desc.Format = CImplDirectXGraphicsManagerHelper::TranslatePixelFormat( info.Format );

	if( lockable )
	{
		DebugAssert( info.MipMapCount == 1 );
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D10_USAGE_DYNAMIC;
		desc.BindFlags = D3D10_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		AssertDXCall( device->CreateTexture2D( &desc, NULL, &m_Texture ) );
	}
	else
	{
		D3D10_SUBRESOURCE_DATA subRscData[32];
		DebugAssert( info.MipMapCount <= 32 );

		UInt32 offset = 0;
		for( UInt32 i=0;i<info.MipMapCount;i++ )
		{
			subRscData[i].pSysMem = data + offset;
			subRscData[i].SysMemPitch = info.GetLinePitch( i );
			subRscData[i].SysMemSlicePitch = 0;
			offset += info.GetMipMapByteCount( i );
		}

		desc.MipLevels = info.MipMapCount;
		desc.ArraySize = 1;
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D10_USAGE_DEFAULT;
		desc.BindFlags = D3D10_BIND_SHADER_RESOURCE;
		AssertDXCall( device->CreateTexture2D( &desc, subRscData, &m_Texture ) );
	}

    m_Texture->GetDesc( &desc );
    m_MipMapLevel = desc.MipLevels;


	D3D10_SHADER_RESOURCE_VIEW_DESC viewDesc;
	MemoryFill( &viewDesc, 0, sizeof( viewDesc ) );
	viewDesc.Format = desc.Format;
	viewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
	viewDesc.Texture2D.MipLevels = desc.MipLevels;
	viewDesc.Texture2D.MostDetailedMip = 0;

	AssertDXCall( device->CreateShaderResourceView( m_Texture, &viewDesc, &m_ShaderView ) );
}

Void* CImplDirectXTexture2D::Lock( const UInt8 mipmaplevel, const EBufferAcces acces, UInt32& pitch )
{
    D3D10_MAPPED_TEXTURE2D mappedText;
    m_Texture->Map( D3D10CalcSubresource( mipmaplevel, 0, m_MipMapLevel ), D3D10_MAP_WRITE_DISCARD, 0, &mappedText );

    pitch = mappedText.RowPitch;

    m_CurrentLevelLocked = mipmaplevel;

    return mappedText.pData;
}

Void CImplDirectXTexture2D::UnLock( ) 
{
    DebugAssert( m_CurrentLevelLocked!= -1 );
    m_Texture->Unmap( D3D10CalcSubresource( m_CurrentLevelLocked, 0, m_MipMapLevel )  );
    m_CurrentLevelLocked = -1;

}
