#ifndef _SABLE_GRAPHICS_RENDERTARGET_IMPL_GLES_BACKBUFFER_
#define _SABLE_GRAPHICS_RENDERTARGET_IMPL_GLES_BACKBUFFER_

#include <Sable/Graphics/RenderTarget/Impl/Stub/BackBuffer.h>
#include <Sable/Core/Common/DataTypes.h>

namespace Sable
{

class CSwapChain;

/** 
*/
class CImplGLESRenderTargetBackBuffer : public CImplStubRenderTargetBackBuffer
{  

public:

	/* @name Constructor/Destructor*/
	//@{
	CImplGLESRenderTargetBackBuffer( CRenderTargetBackBuffer& publicImpl );
	~CImplGLESRenderTargetBackBuffer();
	//@}

	/* @name Mutator*/
	//@{
	//@}

	/* @name Manipulator*/
	//@{
	Void		Activate( Int32 index );
	Void		Initialize( CSwapChain& swapChain );
    Void        Clear( const CColor& col );
	//@}

private:

	//Method

	//Attribute

	//Static method

};

}
#endif
