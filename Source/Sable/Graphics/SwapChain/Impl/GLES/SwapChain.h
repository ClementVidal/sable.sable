#ifndef _SABLE_GRAPHICS_SWAPCHAIN_IMPL_GLES_SWAPCHAIN_
#define _SABLE_GRAPHICS_SWAPCHAIN_IMPL_GLES_SWAPCHAIN_

#include <Sable\Graphics\SwapChain\Impl\Stub\SwapChain.h>
#include <Sable\Core\Common\DataTypes.h>

#include <EGL\EGL.h>

namespace Sable
{

/** 
*/
class CImplGLESSwapChain : public CImplStubSwapChain
{  

public:

	/* @name Constructor/Destructor*/
	//@{
	CImplGLESSwapChain( CSwapChain& swapChain );
	~CImplGLESSwapChain();
	//@}

	/** Operator*/
	//@{
	//@}

	/* @name Accessors*/
	//@{
	//@}

	/* @name Manipulator*/
	//@{
    Bool Initialize( ) ;
    Bool Present( );
	//@}

private:

	//Method

	//Attribute
	EGLSurface	m_Surface;

};

}

#endif

