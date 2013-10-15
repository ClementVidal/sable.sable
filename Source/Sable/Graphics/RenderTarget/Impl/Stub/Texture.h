#ifndef _SABLE_GRAPHICS_RENDERTARGET_IMPL_STUP_TEXTURE_
#define _SABLE_GRAPHICS_RENDERTARGET_IMPL_STUP_TEXTURE_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CRenderTargetTexture;

/** 
Interface Wrapper for Render Target
*/
class CImplStubRenderTargetTexture
{

public:

	/** @name Accessor*/
	//@{
    CImplStubRenderTargetTexture( CRenderTargetTexture& publicImpl );
    virtual ~CImplStubRenderTargetTexture( );
	//@}

	/** @name Manipulator*/
	//@{
    virtual Void		Activate( Int32 index ) {};
    virtual Void		Initialize( const CRenderTargetInfo& info ) {};	
    virtual Void        Clear( const CColor& col ) {};
	//@}

protected:

    // Attributes
    CRenderTargetTexture*   m_PublicImpl;

};

}

#endif
