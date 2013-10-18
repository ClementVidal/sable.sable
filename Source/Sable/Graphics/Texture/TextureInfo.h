#ifndef _GRAPHICS_COMMON_TEXTUREINFO_
#define _GRAPHICS_COMMON_TEXTUREINFO_

#include <Sable/Graphics/Common/DataTypes.h>

namespace Sable
{

/**  
Texture information.
*/
class CTextureInfo
{

public:

	/** @name Constructor/Destructor*/
    //@{
    CTextureInfo();
    CTextureInfo( UInt32 width, UInt32 height, ETextureFormat format, UInt8 mipmapCount, ETextureType type = nTextureType_2D );
	CTextureInfo( UInt32 width, UInt32 height, UInt32 sliceCount, ETextureFormat format, UInt8 mipmapCount );
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Attributes*/
    //@{
	UInt32	        Width;
	UInt32	        Height;
	UInt32			SliceCount;
	ETextureFormat  Format;
	ETextureType	Type;
    UInt8           MipMapCount;
    //@}

    /** @name Accessors*/
	//@{
	UInt32  GetSurfaceByteCount( ) const;
    UInt32  GetTextureByteCount( ) const;
    UInt32  GetMipMapByteCount( UInt32 index ) const;
	UInt32  GetPixelByteCount() const;
    Bool    IsValid() const;
    UInt32  GetLinePitch( UInt32 index ) const;
    Bool    Serialize( CPersistentArchive& ar );
	UInt32	GetMipMapWidth( UInt32 index ) const;
	UInt32	GetMipMapHeight( UInt32 index ) const;
    //@}
};

}

#endif
