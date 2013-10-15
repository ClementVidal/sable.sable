#include <Sable\Graphics\SwapChain\Info.h>

using namespace Sable;

CSwapChainInfo::CSwapChainInfo()
{
    DesiredFPS = 60;
    FullScreen = FALSE;
};

CSwapChainInfo::CSwapChainInfo( 
                  UInt32 width, 
                  UInt32 height, 
                  ETextureFormat format, 
                  EMultiSamplingQuality multisampling,
                  UInt32  desiredFPS,
                  Bool fullScreen
                  )
{
    RenderTargetInfo.MultiSamplingQuality = multisampling;
    RenderTargetInfo.TextureInfo.Format = format;
    RenderTargetInfo.TextureInfo.Width = width;
    RenderTargetInfo.TextureInfo.Height = height;
    DesiredFPS = desiredFPS;
    FullScreen = fullScreen;
};