#ifndef _SABLE_GRAPHICS_TEXTURE_3D_
#define _SABLE_GRAPHICS_TEXTURE_3D_

#include <Sable\Graphics\Texture\Texture.h>

#include <Sable\Graphics\Texture\Impl\Header.h>

namespace Sable
{

/**  
Static Texture 2D. 
*/
class CTexture3D : public CTexture
{

	DEFINE_MANAGED_CLASS( CTexture3D );

public:

	/** @name Constructor/Destructor*/
	//@{
	CTexture3D( );
	~CTexture3D();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
    Bool					SetRawDataFromFile( const CFilePath& filePath );
    Bool					SetRawData( CIODevice& device, UInt32 byteCount = 0 );
	const CImplTexture3D&	GetImpl() const ;
	//@}

	/** @name Manipulator*/
	//@{

	Bool Load( const CFilePath& fileName );
	Bool Load() ;
	Bool Serialize( CPersistentArchive& ar );
	//@}

private:

	// Method
    Bool Create( const CTextureInfo& info, const Byte* data );

	// Attribute
    CArray<Byte>        m_RawData;
	CImplTexture3D		m_Impl;

};  


}
#endif
