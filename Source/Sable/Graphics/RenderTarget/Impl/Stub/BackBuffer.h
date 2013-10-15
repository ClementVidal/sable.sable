#ifndef _SABLE_GRAPHICS_RENDERTARGET_IMPL_STUB_BACKBUFFER_
#define _SABLE_GRAPHICS_RENDERTARGET_IMPL_STUB_BACKBUFFER_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CSwapChain;
class CRenderTargetBackBuffer;

/** 
Interface Wrapper for Render Target
*/
class CImplStubRenderTargetBackBuffer
{

public:

	/** @name Accessor*/
	//@{
    CImplStubRenderTargetBackBuffer( CRenderTargetBackBuffer& publicImpl );
    virtual ~CImplStubRenderTargetBackBuffer( );
	//@}

	/** @name Manipulator*/
	//@{
    virtual Void		Activate( Int32 index ) {};
    virtual Void		Initialize( ) {};	
	virtual Void        Clear( const CColor& col ) {};
	virtual Void        Resize( const CVector2i& newSize ) {};
	//@}

protected:

    // Attributes
    CRenderTargetBackBuffer*    m_PublicImpl;

};

}

#endif
