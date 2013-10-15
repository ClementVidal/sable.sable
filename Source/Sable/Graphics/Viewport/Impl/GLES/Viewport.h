#ifndef _SABLE_GRAPHICS_VIEWPORT_IMPL_GLES_VIEWPORT_
#define _SABLE_GRAPHICS_VIEWPORT_IMPL_GLES_VIEWPORT_

#include <Sable\Graphics\Viewport\Impl\Stub\Viewport.h>
#include <Sable\Core\Common\DataTypes.h>


namespace Sable
{

/** 
*/
class CImplGLESViewport : public CImplStubViewport
{  

public:

	/* @name Constructor/Destructor*/
	//@{
	CImplGLESViewport( CViewport& publicImpl );
	~CImplGLESViewport();
	//@}

	/** Operator*/
	//@{
	//@}

	/* @name Accessors*/
	//@{
	//@}

	/* @name Manipulator*/
	//@{
    Void Activate();
	//@}

private:

	//Method

	//Attribute
    CViewport*  m_PublicImpl;

};

}

#endif

