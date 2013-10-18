#ifndef _GRAPHICS_TEXTURE_CUBE_
#define _GRAPHICS_TEXTURE_CUBE_

#include <Sable/Graphics/Texture/Texture.h>

#include <Sable/Graphics/Texture/Impl/Header.h>

namespace Sable
{

/**  
Static Texture 2D. 
*/
class CTextureCube : public CTexture
{

	DEFINE_MANAGED_CLASS( CTextureCube );

public:

	/** @name Types*/
	//@{
	enum EFaceType
	{
		nFaceType_PositiveX = 0,
		nFaceType_NegativeX,
		nFaceType_PositiveY,
		nFaceType_NegativeY,
		nFaceType_PositiveZ,
		nFaceType_NegativeZ,
		nFaceType_Count,
		nFaceType_Undefined = -1
	};
	//@}

	/** @name Constructor/Destructor*/
	//@{
	CTextureCube( );
	~CTextureCube();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessor*/
	//@{
    Bool					SetRawDataFromFile( const CFilePath& filePath );
    Bool					SetRawData( CIODevice& device, UInt32 byteCount = 0 );
	const CImplTextureCube& GetImpl() const ;
	//@}

	/** @name Manipulator*/
	//@{
	Bool Load( const CFilePath& fileName );
	Bool Load( );
	Bool Serialize( CPersistentArchive& ar );
	//@}

private:

	// Method
    Bool Create( const CTextureInfo& info, const Byte* data );

	// Attribute
    CArray<Byte>        m_RawData;
	CImplTextureCube	m_Impl;

};  


}
#endif
