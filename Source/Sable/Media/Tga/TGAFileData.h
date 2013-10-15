#ifndef _SABLE_MEDIA_TGA_TGAFILEDATA_
#define _SABLE_MEDIA_TGA_TGAFILEDATA_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\Common\DataTypes.h>

namespace Sable
{

#if defined( SETUP_IMPLTYPE_MSW )
#pragma pack(push, 1)
#else
#pragma pack(push, 1)
#endif

	struct ETGAFileHeader
	{
		UInt8	IdLenght;          /* size of image id */
		UInt8	ColormapType;      /* 1 is has a colormap */
		UInt8	ImageType;         /* compression type */

		Int16	CmFirstEntry;       /* colormap origin */
		Int16	CmLength;            /* colormap length */
		UInt8	CmSize;            /* colormap size */

		Int16	XOrigin;             /* bottom left x coord origin */
		Int16	YOrigin;             /* bottom left y coord origin */

		Int16	Width;                /* picture width (in pixels) */
		Int16	Height;               /* picture height (in pixels) */

		UInt8	PixelDepth;        /* bits per pixel: 8, 16, 24 or 32 */
		UInt8	ImageDescriptor;   /* 24 bits = 0x00; 32 bits = 0x80 */
	};

#if defined( SETUP_IMPLTYPE_MSW )
#pragma pack(pop)
#else
#pragma pack(pop)
#endif

}

#endif
