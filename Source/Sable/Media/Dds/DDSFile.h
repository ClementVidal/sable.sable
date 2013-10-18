#ifndef _SABLE_MEDIA_DDS_DDSFILE_
#define _SABLE_MEDIA_DDS_DDSFILE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Collection/Array.h>
#include <Sable/Graphics/Texture/TextureInfo.h>
#include <Sable/Graphics/Common/DataTypes.h>
#include <Sable/Media/Dds/DDSFileData.h>
#include <Sable/Media/Common/ImageFile.h>

namespace Sable
{

class CIODevice;

/**  
\ingroup Media
DDS File Reader. 
*/
class CDDSFile : public CImageFile
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CDDSFile( CMemoryHeap* heap = NULL );
	virtual ~CDDSFile();
	//@}

	/** Accessors*/
	//@{    
	Bool					GetIsStandardTexture() const;
	Bool					GetIsCubeTexture() const;
	Bool					GetIsVolumeTexture() const;
	const CTextureInfo&		GetTextureInfo( ) const;
	const Byte*				GetSurfaceData( UInt32 surfaceType, UInt32 mipMapIndex, UInt32& byteCount ) const;
	Void					SetSurfaceData( UInt32 surfaceType, UInt32 mipMapIndex, const Byte* data, UInt32 size ) const;
	//@}

	/** Manipulator*/
	//@{

    Bool Save( const CFilePath& file );
	//@}

private:

	//Types

	// Methods
    Bool                        LoadInternal( CIODevice& ioDevice, Bool decompress );
	UInt32						GetSurfaceSize( ) const;
	UInt32						GetTextureSize( ) const;
	UInt32						GetMipMapCount( ) const;
	UInt32						GetSurfaceCount( ) const;
	ETextureType				GetTextureType( ) const;
	ETextureFormat				GetPixelFormat( ) const;

	// Attributes
	CArray<Byte>						m_Data;
	CTextureInfo						m_TextureInfo;
	EDDSFileHeader						m_Header;

};

}

#endif
