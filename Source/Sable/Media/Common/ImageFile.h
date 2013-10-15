#ifndef _SABLE_MEDIA_COMMON_IMAGEFILE_
#define _SABLE_MEDIA_COMMON_IMAGEFILE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Collection\Array.h>
#include <Sable\Graphics\Common\DataTypes.h>
#include <Sable\Core\Common\Color.h>
#include <Sable\Core\File\FilePath.h>
#include <Sable\Core\Common\IODevice.h>

namespace Sable
{

class CIODevice;
class CFilePath;
class CTextureInfo;

/**  
\ingroup Media
Base class for image reader. 
*/
class CImageFile
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CImageFile();
	virtual ~CImageFile();
	//@}

	/** Accessors*/
	//@{    
	virtual Bool					GetIsStandardTexture() const = 0;
	virtual Bool					GetIsCubeTexture() const = 0;
	virtual Bool					GetIsVolumeTexture() const = 0;
	virtual const CTextureInfo&		GetTextureInfo( ) const = 0;
	virtual const Byte*				GetSurfaceData( UInt32 surfaceType, UInt32 mipMapIndex, UInt32& byteCount ) const = 0;
    CColor                          GetPixel( UInt32 surfaceType, UInt32 mipMapIndex, UInt32 x, UInt32 y );
	//@}

	/** Manipulator*/
	//@{
    Bool Load( const CFilePath& file, Bool decompress = FALSE );
	//@}

    /** Static function*/
    //@{
    static CColor       ConvertPixel( const Byte* pixelData, ETextureFormat fmt );
    //@}

protected:

	//Types
    virtual Bool LoadInternal( CIODevice& ioDevice, Bool decompress ) = 0;

	// Methods
	UInt32 GetPixelByteCount( const ETextureFormat pixelFormat ) const;

	// Attributes

};

}

#endif
