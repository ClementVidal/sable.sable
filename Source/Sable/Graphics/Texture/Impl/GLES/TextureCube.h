#ifndef _SABLE_GRAPHICS_TEXTURE_IMPL_GLES_TEXTURECUBE_
#define _SABLE_GRAPHICS_TEXTURE_IMPL_GLES_TEXTURECUBE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\Texture\Impl\Stub\TextureCube.h>

namespace Sable
{

/** 
Interface Wrapper for both static and dynamic index buffer	 
*/
class CImplGLESTextureCube : public CImplStubTextureCube
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CImplGLESTextureCube();
	~CImplGLESTextureCube();
	//@}

	/** @name Operator*/
	//@{
	//@}
	
	/** @name Accessors*/
	//@{
	UInt32	GetGLTextureName() const;
	//@}

	/** @name Manipulator*/
	//@{
	Void	Initialize( const CTextureInfo& info, const Byte* data );
	Void	UnInitialize();
	//@}

private:

	// Attributes
	UInt32	m_TextureID;

};

}

#endif
