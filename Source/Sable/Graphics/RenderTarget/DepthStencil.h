#ifndef _SABLE_GRAPHICS_RENDERTARGET_DEPTHSTENCIL_
#define _SABLE_GRAPHICS_RENDERTARGET_DEPTHSTENCIL_

#include <Sable\Core\ManagedObject\Macro.h>
#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\RenderTarget\RenderTarget.h>

#include <Sable\Graphics\RenderTarget\Impl\Header.h>

namespace Sable
{

/** 
Render Target texture.
*/
class CRenderTargetDepthStencil : public CManagedObject
{

friend class CRenderTarget;

	DEFINE_MANAGED_CLASS( CRenderTargetDepthStencil );

public:

    /** @name Constructor/Destructor*/
    //@{
    CRenderTargetDepthStencil();
    ~CRenderTargetDepthStencil();
    //@}

    /** @name Operator*/
    //@{
    //@}

	/** @name Accessors*/
	//@{
	const CImplRenderTargetDepthStencil&	GetImpl() const;
	const CRenderTargetInfo&				GetInfo() const;
	//@}

	/** @name Manipulator*/
	//@{
	Void					Activate( );
	Bool					Create( const CRenderTargetInfo& info );
    Void                    Clear( Float32 depth, UInt8 stencil );
	Void					Resize( const CVector2i& newSize );
	//@}

private:

	//Methods

	//Attributes
	CRenderTargetInfo					m_Info;
	CImplRenderTargetDepthStencil		m_Impl;

};

Inline
const CImplRenderTargetDepthStencil& CRenderTargetDepthStencil::GetImpl() const
{
	return m_Impl;
}


}

#endif
