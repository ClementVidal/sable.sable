#ifndef _SABLE_MEDIA_TGA_TGAFILE_
#define _SABLE_MEDIA_TGA_TGAFILE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Collection/Array.h>
#include <Sable/Core/File/Header.h>
#include <Sable/Graphics/Texture/TextureInfo.h>
#include <Sable/Graphics/Common/DataTypes.h>
#include <Sable/Media/Common/ImageFile.h>

namespace Sable
{

struct ETGAFileHeader;

/**  
\ingroup Media
TGA File Reader. 
*/
class CTGAFile : public CImageFile
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CTGAFile( CMemoryHeap* heap = NULL );
	virtual ~CTGAFile();
	//@}

	/** Accessors*/
	//@{    
	Bool					GetIsStandardTexture() const;
	Bool					GetIsCubeTexture() const;
	Bool					GetIsVolumeTexture() const;
	UInt8					GetMipMapCount( ) const ;
	const CTextureInfo&		GetTextureInfo( ) const;
	const Byte*				GetSurfaceData( UInt32 surfaceType, UInt32 mipMapIndex, UInt32& byteCount ) const;
	//@}

	/** Manipulator*/
	//@{

	//@}

private:

	//Types

	// Methods
    Bool                        LoadInternal( CIODevice& ioDevice, Bool decompress );
	Void						ReadStandardTexture(  CIODevice& ioDevice, const ETGAFileHeader& header );
	ETextureFormat				GetPixelFormat( const ETGAFileHeader& header ) const;
	Void						RefillBuffer(  CIODevice& ioDevice, Byte* buffer, Int32 byteToProcess, Int32& byteLeft );

	// Attributes
	CArray< Byte >	m_SurfaceTable; // Surface->MipMap->Data
	CTextureInfo						m_TextureInfo;
	CMemoryHeap*			m_Heap;

};

}

#endif
