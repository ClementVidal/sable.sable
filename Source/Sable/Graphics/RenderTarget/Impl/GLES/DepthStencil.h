#ifndef _SABLE_GRAPHICS_RENDERTARGET_IMPL_GLES_DEPTHSTENCIL_
#define _SABLE_GRAPHICS_RENDERTARGET_IMPL_GLES_DEPTHSTENCIL_

#include <Sable\Graphics\RenderTarget\Impl\Stub\DepthStencil.h>
#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

/** 
DirectX9 Wrapper for Render Target
*/
class CImplGLESRenderTargetDepthStencil : public CImplStubRenderTargetDepthStencil
{  

public:

	/* @name Constructor/Destructor*/
	//@{
	CImplGLESRenderTargetDepthStencil( CRenderTargetDepthStencil& publicImpl );
	~CImplGLESRenderTargetDepthStencil();
	//@}

	/** Operator*/
	//@{
	//@}

	/* @name Mutator*/
	//@{
	//@}

	/* @name Manipulator*/
	//@{
	Void		Activate( );
	Void		Initialize( const CRenderTargetInfo& info );
    Void        Clear( Float32 depth, UInt8 stencil );
	//@}

private:

	//Method

	//Attribute

	//Static method

};

}

#endif

