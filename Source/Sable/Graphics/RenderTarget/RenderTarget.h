#ifndef _GRAPHICS_RENDER_RENDERTARGET_
#define _GRAPHICS_RENDER_RENDERTARGET_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Common\Color.h>
#include <Sable\Graphics\RenderTarget\Info.h>

namespace Sable
{

class CRenderer;

/** 
Render Target.
*/
class CRenderTarget : public CManagedObject 
{

	DEFINE_MANAGED_CLASS( CRenderTarget );

public:

    /** @name Constructor/Destructor*/
    //@{
	CRenderTarget();
	~CRenderTarget();
    //@}


	/** @name Accessors*/
	//@{
	const CRenderTargetInfo&	GetInfo() const;
	UInt32						GetWidth() const ;
	UInt32						GetHeight() const ;
	//@}

	/** @name Manipulator*/
	//@{
    virtual Void	Clear( const CColor& color ) = 0;
	virtual Void	Resize( const CVector2i& newSize );
	//@}
	
protected:

	//Attributes
	CRenderTargetInfo			m_Info;

    //Methods
    virtual Void	Activate( CRenderer& renderer, Int32 index );

private:

    // Friendship 
    friend class CRenderer;

    //Methods

	//Attributes
	CColor						m_ClearColor;

};

}

#endif
