#ifndef _SABLE_GRAPHICS_VIEWPORT_IMPL_MSW_VIEWPORT_
#define _SABLE_GRAPHICS_VIEWPORT_IMPL_MSW_VIEWPORT_

#include <Sable\Graphics\Viewport\Impl\Stub\Viewport.h>
#include <Sable\Core\Common\DataTypes.h>


namespace Sable
{

/** 
*/
class CImplDirectXViewport : public CImplStubViewport
{  

public:

	/* @name Constructor/Destructor*/
	//@{
	CImplDirectXViewport( CViewport& publicImpl );
	~CImplDirectXViewport();
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

