#ifndef _SABLE_GRAPHICS_RENDERTARGET_INFO_
#define _SABLE_GRAPHICS_RENDERTARGET_INFO_

#include <Sable\Graphics\Texture\TextureInfo.h>

namespace Sable
{

/**  
REnder target information.
*/
class CRenderTargetInfo
{

public:

	/** @name Constructor/Destructor*/
    //@{
    CRenderTargetInfo();
    CRenderTargetInfo( 
        UInt32 width, 
        UInt32 height, 
        ETextureFormat format, 
        EMultiSamplingQuality multisampling
        );
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Attributes*/
    //@{
	CTextureInfo            TextureInfo;
    EMultiSamplingQuality   MultiSamplingQuality;
    //@}

    /** @name Accessors*/
    //@{
    //@}
};

}

#endif
