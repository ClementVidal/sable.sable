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

	struct ECTESFileData 
	{
		UInt32   Signature;           // Compression format signature
		UInt32   Width;               // Width of base level in pixels
		UInt32   Height;              // Height of base level in pixels
		UInt32   Flags;               // Flags (TXCMPR_RGB, TXCMPR_RGBA, TXCMPR_ALPHA_INTERP)
		UInt32   DataOffset;          // From start of header/file

		UInt32   HeaderVersion;       // Version number of header file
		UInt32   NumLevels;           // Number of mip levels stored in file
		UInt32   InternalFormat;      // Internal format to be passed to glCompressedTexImage2D()
	};

#if defined( SETUP_IMPLTYPE_MSW )
#pragma pack(pop)
#else
#pragma pack(pop)
#endif

}

#endif
