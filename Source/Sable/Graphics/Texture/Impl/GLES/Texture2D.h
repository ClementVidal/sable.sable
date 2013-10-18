#ifndef _SABLE_GRAPHICS_TEXTURE_IMPL_GLES_TEXTURE2D_
#define _SABLE_GRAPHICS_TEXTURE_IMPL_GLES_TEXTURE2D_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/Texture/Impl/Stub/Texture2D.h>

namespace Sable
{

/** 

*/
class CImplGLESTexture2D : public CImplStubTexture2D
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CImplGLESTexture2D();
	~CImplGLESTexture2D();
	//@}

	/** Operator */
	//@{
	//@}

	/** @name Accessors*/
	//@{
	UInt32	GetGLTextureName() const;
	//@}

	/** @name Manipulator*/
	//@{
	Void	Initialize( const CTextureInfo& info, Bool lockable, const Byte* data );
	Void	UnInitialize( );
	Void*	Lock( const UInt8 mipmaplevel, const EBufferAcces acces, UInt32& pitch ) ;
	Void	UnLock( ) ;
	//@}

private:

	// Methods

	// Attributes
    UInt32					m_TextureID;

};


}

#endif
