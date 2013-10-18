#ifndef _SABLE_GRAPHICS_TEXTURE_2D_
#define _SABLE_GRAPHICS_TEXTURE_2D_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/Texture/Texture.h>

#include <Sable/Graphics/Texture/Impl/Header.h>

namespace Sable
{

class CPersistentArchive;
class CIODevice;

/**  
2D texture.
*/
class CTexture2D : public CTexture
{

	DEFINE_MANAGED_CLASS( CTexture2D );

public:

    /** @name DataTypes*/
    //@{
	//@}

	/** @name Constructor/Destructor*/
	//@{
	CTexture2D( );
	~CTexture2D();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
    Bool					SetRawDataFromFile( const CFilePath& filePath );
    Bool					SetRawData( CIODevice& device, UInt32 byteCount = 0 );
    UInt32					GetWidth() const;
    UInt32					GetHeight() const;
    UInt32					GetMipMapCount() const;
	const CImplTexture2D&	GetImpl() const;
	//@}

	/** @name Manipulator*/
	//@{
    Bool        Serialize( CPersistentArchive& ar );
	Bool		Load( );
    Bool        Load( const CFilePath& filePath );
	Void*       Lock( UInt8 mipmaplevel, UInt32& pitch );
	Void*       Lock( UInt8 mipmaplevel );
	Void        UnLock( );
	Bool        Create( const CTextureInfo& info, const Byte* data );
	//@}

private:

	// Method

	// Attribute
    CArray<Byte>        m_RawData;
	CImplTexture2D		m_Impl;

};  

}
#endif
