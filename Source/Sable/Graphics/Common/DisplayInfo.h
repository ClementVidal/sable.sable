#ifndef _GRAPHICS_COMMON_DISPLAYINFO_
#define _GRAPHICS_COMMON_DISPLAYINFO_

#include <Sable\Graphics\Common\DataTypes.h>

namespace Sable
{

/**  
Display information.
*/
class CDisplayInfo 
{

public:

	/** @name Constructor/Destructor*/
    //@{
    CDisplayInfo()
    {
        Width = 0;
        Height = 0;
        Format = nBackBufferFormat_None;
        RefreshRate = 0;
        IsWindowed = FALSE;
        WaitForVSynch = FALSE;
		MultiSample = FALSE;
    }
    //@}

    /** @name Attributes*/
    //@{
    UInt32	            Width;
    UInt32	            Height;
    EBackBufferFormat    Format;
    UInt32	            RefreshRate;
    Bool                IsWindowed;
    Bool                WaitForVSynch;
	Bool				MultiSample;
	//@}

};

}

#endif
