#include <Sable/Graphics/RenderTarget/Info.h>

using namespace Sable;

CRenderTargetInfo::CRenderTargetInfo()
{
    MultiSamplingQuality = nMultiSamplingQuality_None;
};

CRenderTargetInfo::CRenderTargetInfo( 
                  UInt32 width, 
                  UInt32 height, 
                  ETextureFormat format, 
                  EMultiSamplingQuality multisampling
                  )
{
    TextureInfo.MipMapCount = 1;
    TextureInfo.Width = width;
    TextureInfo.Height = height;
    TextureInfo.Format = format;
    MultiSamplingQuality = multisampling;
};