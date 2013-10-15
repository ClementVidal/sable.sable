#ifndef _GRAPHICS_RENDER_RENDERTAGETBACKBUFFER_
#define _GRAPHICS_RENDER_RENDERTAGETBACKBUFFER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\ManagedObject\Macro.h>
#include <Sable\Graphics\RenderTarget\RenderTarget.h>
#include <Sable\Setup.h>

#include <Sable\Graphics\RenderTarget\Impl\Header.h>

namespace Sable
{

class CSwapChain;

/** 
Render Target back buffer.
*/
class CRenderTargetBackBuffer : public CRenderTarget 
{

	DEFINE_MANAGED_CLASS( CRenderTargetBackBuffer );

public:

    /** @name Constructor/Destructor*/
    //@{
	CRenderTargetBackBuffer();
	~CRenderTargetBackBuffer();
    //@}

    /** @name Operator*/
    //@{
     //@}

	/** @name Accessor*/
	//@{
	CSwapChain*						GetOwnerSwapChain() const;
	CImplRenderTargetBackBuffer&	GetImpl();
	//@}

	/** @name Manipulator*/
	//@{
	Bool	Initialize( CSwapChain& chain );
    Void    Clear( const CColor& color );
	Void	Resize( const CVector2i& newSize );
	//@}

private:

	//Methods
	Void	Activate( CRenderer& renderer, Int32 index ) ;

	//Attributes
	CImplRenderTargetBackBuffer			m_Impl;
	CSwapChain*							m_OwnerSwapChain;

};


}

#endif
