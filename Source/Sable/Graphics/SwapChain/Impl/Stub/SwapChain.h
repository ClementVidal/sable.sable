#ifndef _SABLE_GRAPHICS_SWAPCHAIN_IMPL_STUP_SWAPCHAIN_
#define _SABLE_GRAPHICS_SWAPCHAIN_IMPL_STUP_SWAPCHAIN_

#include <Sable/Core/Common/DataTypes.h>

namespace Sable
{

class CSwapChain;

/** 
*/
class CImplStubSwapChain
{

public:

	/* @name Constructor/Destructor*/
	//@{
	CImplStubSwapChain( CSwapChain& swapChain ) { m_PublicImpl = &swapChain; }
	virtual ~CImplStubSwapChain() {};
	//@}

	/** @name Manipulator*/
	//@{
	virtual Void Resize( const CVector2i& newSize ) {};
    virtual Bool Initialize( ) { return TRUE; };
    virtual Bool Present( ) { return TRUE; };
	//@}

protected:

	// Attributes
	CSwapChain*	m_PublicImpl;

};

}

#endif
