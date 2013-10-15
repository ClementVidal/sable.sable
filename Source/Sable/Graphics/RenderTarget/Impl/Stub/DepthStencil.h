#ifndef _SABLE_GRAPHICS_RENDERTARGET_IMPL_STUP_DEPTHSTENCIL_
#define _SABLE_GRAPHICS_RENDERTARGET_IMPL_STUP_DEPTHSTENCIL_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CRenderTargetDepthStencil;

/** 
Interface Wrapper for Render Target
*/
class CImplStubRenderTargetDepthStencil
{

public:

	/** @name Accessor*/
	//@{
    CImplStubRenderTargetDepthStencil( CRenderTargetDepthStencil& publicImpl );
    virtual ~CImplStubRenderTargetDepthStencil();
	//@}

	/** @name Manipulator*/
	//@{
    virtual Void		Activate( ) {};
    virtual Void		Initialize( const CRenderTargetInfo& info ) {};	
    virtual Void        Clear( Float32 depth, UInt8 stencil ) {};
	virtual Void		Resize( const CVector2i& newSize ) {};
	//@}

protected:

    // Attributes
    CRenderTargetDepthStencil*  m_PublicImpl;

};

}

#endif
