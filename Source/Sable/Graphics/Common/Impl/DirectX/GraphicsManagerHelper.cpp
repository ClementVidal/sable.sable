#include <Sable\Graphics\Common\Impl\DirectX\GraphicsManagerHelper.h>
#include <Sable\Graphics\Common\Impl\DirectX\GraphicsManager.h>

using namespace Sable;

CImplDirectXGraphicsManagerHelper::CImplDirectXGraphicsManagerHelper()
{
}

CImplDirectXGraphicsManagerHelper::~CImplDirectXGraphicsManagerHelper()
{
}

ID3D10Device* CImplDirectXGraphicsManagerHelper::GetDevice()
{
	return ( (CImplDirectXGraphicsManager&)GraphicsManager.GetImpl() ).GetDevice();
}

DXGI_SAMPLE_DESC CImplDirectXGraphicsManagerHelper::TranslateMultiSampling( EMultiSamplingQuality mt )
{
    DXGI_SAMPLE_DESC desc;
    desc.Count = 1;
    desc.Quality = 0;
    if( mt == nMultiSamplingQuality_1 )
    {
        desc.Count = 2;
        desc.Quality = 1;
    }
    else if( mt == nMultiSamplingQuality_2 )
    {
        desc.Count = 4;
        desc.Quality = 2;
    }
    else if( mt == nMultiSamplingQuality_3 )
    {
        desc.Count = 8;
        desc.Quality = 3;
    }
    else if( mt == nMultiSamplingQuality_4 )
    {
        desc.Count = 8;
        desc.Quality = 4;
    }

    return desc;
}

DXGI_FORMAT CImplDirectXGraphicsManagerHelper::TranslatePixelFormat( const ETextureFormat format )
{
	switch(format)
	{
	case nTextureFormat_X8R8G8B8:
		return DXGI_FORMAT_R8G8B8A8_UNORM;

	case nTextureFormat_A2R10G10B10:
		return DXGI_FORMAT_R10G10B10A2_UNORM;

	case nTextureFormat_R8G8B8A8:
		return DXGI_FORMAT_R8G8B8A8_UNORM;

	case nTextureFormat_A8:
		return DXGI_FORMAT_A8_UNORM;

	case nTextureFormat_L8:
		return DXGI_FORMAT_R8_UNORM;

	case nTextureFormat_D24S8:
		return DXGI_FORMAT_D24_UNORM_S8_UINT ;

	case nTextureFormat_DXT1:
		return DXGI_FORMAT_BC1_UNORM;

    case nTextureFormat_DXT2:
    case nTextureFormat_DXT3:
        return DXGI_FORMAT_BC2_UNORM;

	case nTextureFormat_DXT4:
	case nTextureFormat_DXT5:
		return DXGI_FORMAT_BC3_UNORM;

	case nTextureFormat_R16F:
		return DXGI_FORMAT_R16_FLOAT;

	case nTextureFormat_A16B16G16R16F:
		return DXGI_FORMAT_R16G16B16A16_FLOAT;

	case nTextureFormat_G16R16F:
		return DXGI_FORMAT_R16G16_FLOAT;

	case nTextureFormat_None:
		return DXGI_FORMAT_UNKNOWN;
	}

	DebugError( "Invalid pixel format" );
	
	return DXGI_FORMAT_UNKNOWN;
}
