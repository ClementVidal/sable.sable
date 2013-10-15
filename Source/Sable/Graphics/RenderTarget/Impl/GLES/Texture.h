#ifndef _SABLE_GRAPHICS_RENDERTARGET_IMPL_GLES_TEXTURE_
#define _SABLE_GRAPHICS_RENDERTARGET_IMPL_GLES_TEXTURE_

#include <Sable\Graphics\RenderTarget\Impl\Stub\Texture.h>
#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

/** 

*/
class CImplGLESRenderTargetTexture : public CImplStubRenderTargetTexture
{  

public:

	/* @name Constructor/Destructor*/
	//@{
	CImplGLESRenderTargetTexture( CRenderTargetTexture& publicImpl );
	~CImplGLESRenderTargetTexture();
	//@}

	/** Operator*/
	//@{
	//@}

	/* @name Mutator*/
	//@{
	//@}

	/* @name Manipulator*/
	//@{
	Void		Activate( Int32 index );
	Void 		UnInitialize( );
	Void		Initialize( const CRenderTargetInfo& info );
    Void        Clear( const CColor& col );
	//@}

private:

	//Method

	//Attribute
    UInt32	m_TextureID;

	//Static method

};

}

#endif

