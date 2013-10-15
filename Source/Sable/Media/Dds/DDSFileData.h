#ifndef _MEDIA_DDS_DDSFILEDATA_
#define _MEDIA_DDS_DDSFILEDATA_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\Common\DataTypes.h>

namespace Sable
{
	enum EDDSFileConstant
	{
		nDDSConstant_DDSD_CAPS = 0x00000001 ,
		nDDSConstant_DDSD_HEIGHT = 0x00000002 ,
		nDDSConstant_DDSD_WIDTH = 0x00000004 ,
		nDDSConstant_DDSD_PITCH = 0x00000008 ,
		nDDSConstant_DDSD_PIXELFORMAT = 0x00001000 ,
		nDDSConstant_DDSD_MIPMAPCOUNT = 0x00020000 ,
		nDDSConstant_DDSD_LINEARSIZE = 0x00080000 ,
		nDDSConstant_DDSD_DEPTH = 0x00800000 ,

		nDDSConstant_DDPF_ALPHAPIXELS = 0x00000001 ,
		nDDSConstant_DDPF_FOURCC = 0x00000004 ,
		nDDSConstant_DDPF_RGB = 0x00000040 ,
		nDDSConstant_DDPF_YUV = 0x00000200 ,
		nDDSConstant_DDPF_LUMINANCE = 0x00020000 ,

		nDDSConstant_DDSCAPS_COMPLEX = 0x00000008 ,
		nDDSConstant_DDSCAPS_TEXTURE = 0x00001000 ,
		nDDSConstant_DDSCAPS_MIPMAP = 0x00400000 ,

		nDDSConstant_DDSCAPS2_CUBEMAP = 0x00000200 ,
		nDDSConstant_DDSCAPS2_CUBEMAP_POSITIVEX = 0x00000400 ,
		nDDSConstant_DDSCAPS2_CUBEMAP_NEGATIVEX = 0x00000800 ,
		nDDSConstant_DDSCAPS2_CUBEMAP_POSITIVEY = 0x00001000 ,
		nDDSConstant_DDSCAPS2_CUBEMAP_NEGATIVEY = 0x00002000 ,
		nDDSConstant_DDSCAPS2_CUBEMAP_POSITIVEZ = 0x00004000 ,
		nDDSConstant_DDSCAPS2_CUBEMAP_NEGATIVEZ = 0x00008000 ,
		nDDSConstant_DDSCAPS2_VOLUME = 0x00200000 ,

	};

    struct EDDSPixelFormat
    {
        UInt32 Size;
        UInt32 Flags ;
        UInt32 FourCC ;
        UInt32 RGBBitCount ;
        UInt32 RBitMask;
        UInt32 GBitMask;
        UInt32 BBitMask ;
        UInt32 ABitMask ;
    };

	struct EDDSFileHeader
	{
		UInt32 Magic;
		UInt32 Size ;
		UInt32 Flags ;
		UInt32 Height;
		UInt32 Width;
		UInt32 PitchOrLinearSize;
		UInt32 Depth;
		UInt32 MipMapCount;
		UInt32 Reserved1[11];

        //PixelFormat
        EDDSPixelFormat PixelFormat;

		//DDCAPS2
        UInt32  Caps;
        UInt32  Caps2;
        UInt32  Caps3;
        UInt32  Caps4;
        UInt32  Reserved2;
	};
}

#endif
