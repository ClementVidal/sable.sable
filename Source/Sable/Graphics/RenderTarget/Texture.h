#ifndef _GRAPHICS_RENDERTARGET_TEXTURE_
#define _GRAPHICS_RENDERTARGET_TEXTURE_

#include <Sable\Core\ManagedObject\Macro.h>
#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\RenderTarget\RenderTarget.h>

#include <Sable\Graphics\RenderTarget\Impl\Header.h>

namespace Sable
{

/** 
Render Target texture.
*/
class CRenderTargetTexture : public CRenderTarget
{

friend class CRenderTarget;

	DEFINE_MANAGED_CLASS( CRenderTargetTexture );

public:

    /** @name Constructor/Destructor*/
    //@{
    CRenderTargetTexture();
    CRenderTargetTexture( const CRenderTargetInfo& info );
    ~CRenderTargetTexture();
    //@}

    /** @name Operator*/
    //@{
    //@}

	/** @name Accessors*/
	//@{
	const CImplRenderTargetTexture& GetImpl() const;
    Void					SetMagFilterMode( EStateFilter state ) { m_MagFilteringMode = state; }
    Void					SetMinFilterMode( EStateFilter state ) { m_MinFilteringMode = state; }
    EStateFilter			GetMinFilterMode( ) const { return m_MinFilteringMode; } 
    EStateFilter	        GetMagFilterMode( ) const { return m_MinFilteringMode; }
	//@}

	/** @name Manipulator*/
	//@{
	Void					Create( const CRenderTargetInfo& info );
    Void                    Clear( const CColor& color );	
	Void					Resize( const CVector2i& newSize );
	//@}

private:

	//Methods
	Void					Activate( CRenderer& renderer, Int32 index );

	//Attributes
	EStateFilter				    m_MinFilteringMode;
	EStateFilter				    m_MagFilteringMode;
	CImplRenderTargetTexture		m_Impl;

};

Inline
const CImplRenderTargetTexture& CRenderTargetTexture::GetImpl() const
{
	return m_Impl;
}


}

#endif
