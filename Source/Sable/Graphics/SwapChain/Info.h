#ifndef _SABLE_GRAPHICS_SWAPCHAIN_INFO_
#define _SABLE_GRAPHICS_SWAPCHAIN_INFO_

#include <Sable\Graphics\RenderTarget\Info.h>

namespace Sable
{

/**  
Swap chain information.
*/
class CSwapChainInfo
{

public:

	/** @name Constructor/Destructor*/
    //@{
    CSwapChainInfo();
    CSwapChainInfo( 
        UInt32 width, 
        UInt32 height, 
        ETextureFormat format, 
        EMultiSamplingQuality multisampling,
        UInt32  desiredFPS,
        Bool fullScreen
        );
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Attributes*/
    //@{
	CRenderTargetInfo       RenderTargetInfo;
    UInt32                  DesiredFPS;
    Bool                    FullScreen;
    //@}

    /** @name Accessors*/
    //@{
    //@}
};

}

#endif
