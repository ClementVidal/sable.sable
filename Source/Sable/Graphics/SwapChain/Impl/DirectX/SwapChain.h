#ifndef _SABLE_GRAPHICS_SWAPCHAIN_IMPL_MSW_SWAPCHAIN_
#define _SABLE_GRAPHICS_SWAPCHAIN_IMPL_MSW_SWAPCHAIN_

#include <Sable/Graphics/SwapChain/Impl/Stub/SwapChain.h>
#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Math/Vector2i.h>

namespace Sable
{

/** 
*/
class CImplDirectXSwapChain : public CImplStubSwapChain
{  

public:

	/* @name Constructor/Destructor*/
	//@{
	CImplDirectXSwapChain( CSwapChain& swapChain );
	~CImplDirectXSwapChain();
	//@}

	/** Operator*/
	//@{
	//@}

	/* @name Accessors*/
	//@{
    IDXGISwapChain* GetD3DSwapChain() const;
	//@}

	/* @name Manipulator*/
	//@{
	Void Resize( const CVector2i& newSize );
    Bool Initialize( ) ;
    Bool Present( );
	//@}

private:

	//Method

	//Attribute
    IDXGISwapChain* m_SwapChain;

};

}

#endif

