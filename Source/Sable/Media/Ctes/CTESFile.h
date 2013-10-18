#ifndef _SABLE_MEDIA_CTES_CTESFILE_
#define _SABLE_MEDIA_CTES_CTESFILE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Collection/Array.h>
#include <Sable/Graphics/Texture/TextureInfo.h>
#include <Sable/Graphics/Common/DataTypes.h>
#include <Sable/Media/Common/ImageFile.h>

namespace Sable
{

class CIODevice;

/**  
\ingroup Media
CTES File Reader. 
*/
class CCTESFile : public CImageFile
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CCTESFile( CMemoryHeap* heap = NULL );
	virtual ~CCTESFile();
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
   
	// Attributes
	CArray<Byte>						m_Data;
	CTextureInfo						m_TextureInfo;
	EDDSFileHeader						m_Header;

};

}

#endif
