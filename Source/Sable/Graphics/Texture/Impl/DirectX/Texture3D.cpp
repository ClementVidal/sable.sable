#include <Sable\Graphics\Texture\Impl\DirectX\Texture3D.h>

using namespace Sable;

CImplDirectXTexture3D::CImplDirectXTexture3D()
{
	m_Width = 0;
	m_Height = 0;
	m_SliceCount = 0;
	m_Texture = NULL;
}

CImplDirectXTexture3D::~CImplDirectXTexture3D()
{
	if( m_Texture )
	{
		if( m_Texture->Release() != 0 )
		{
			DebugLogWarning("CImplDirectXTexture3D::~CImplDirectXTexture3D - Unfreed texture resource");
		}
	}
	m_Texture = NULL;
}

Void CImplDirectXTexture3D::Initialize( const CTextureInfo& info, const Byte* data )
{
    //REFACTORDX10
    /*
	HRESULT 
		hr;
	D3DPOOL 
		d3dPool;
	DWORD	
		usage;
	D3DFORMAT 
		d3dformat;
	IDirect3DVolumeTexture9
		*dx9VolumeTexture;

	d3dPool = D3DPOOL_MANAGED;
	usage = 0;

	m_Width = width;
	m_Height = height;
	m_SliceCount = sliceCount;

	if( mipmaplevel == 0 )
		usage = D3DUSAGE_AUTOGENMIPMAP;

	d3dformat =  CImplDirectXGraphicsManagerHelper::TranslatePixelFormat( format );
	hr = CImplDirectXGraphicsManagerHelper::GetDevice()->CreateVolumeTexture( 
			m_Width, m_Height, m_SliceCount, 
			mipmaplevel, usage, d3dformat, 
			d3dPool, &dx9VolumeTexture, NULL );

	DebugAssertMsg( hr == S_OK, "Unable to create 3D texture" );

	m_Texture = dx9VolumeTexture;*/
}

ID3D10ShaderResourceView* CImplDirectXTexture3D::GetD3DTextureShaderView() const
{
	return NULL;
}

