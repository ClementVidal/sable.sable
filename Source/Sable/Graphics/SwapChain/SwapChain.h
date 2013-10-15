#ifndef _SABLE_GRAPHICS_SWAPCHAIN_SWAPCHAIN_
#define _SABLE_GRAPHICS_SWAPCHAIN_SWAPCHAIN_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\ManagedObject\ManagedObject.h>

#include <Sable\Graphics\Viewport\Viewport.h>
#include <Sable\Graphics\SwapChain\Info.h>
#include <Sable\Graphics\SwapChain\Impl\Header.h>
#include <Sable\Graphics\RenderTarget\BackBuffer.h>
#include <Sable\Graphics\RenderTarget\DepthStencil.h>

namespace Sable
{

class CApplicationWindow;

/** 
Swap chain
*/
class CSwapChain : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CSwapChain );

public:

    /** @name DataType*/
    //@{
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CSwapChain();
    ~CSwapChain();
    //@}

	/** @name Accessors*/
	//@{
    CApplicationWindow*         GetOwnerWindow() const;
    CViewport&                  GetViewport();
    CRenderTargetBackBuffer&    GetBackBuffer();
    CRenderTargetDepthStencil&  GetDepthStencil();
    const CSwapChainInfo&       GetInfo() const;
	const CImplSwapChain&       GetImpl() const;
	//@}

	/** @name Manipulator*/
	//@{
	Void	Clear( Float32 depth, UInt8 stencil, const CColor& color );
	Void    Resize( const CVector2i& newSize );
    Bool    Initialize( CApplicationWindow& ownerWindow, const CSwapChainInfo& info );
    Bool    Present();
	//@}

private:

	//Methods


	//Attributes
    CRenderTargetBackBuffer     m_BackBuffer;
    CRenderTargetDepthStencil   m_DepthStencil;
    CViewport                   m_Viewport;
    CSwapChainInfo              m_Info;
    CImplSwapChain              m_Impl;
    CApplicationWindow*         m_OwnerWindow;
};


}

#endif
