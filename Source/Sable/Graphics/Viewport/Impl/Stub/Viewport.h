#ifndef _SABLE_GRAPHICS_VIEWPORT_IMPL_STUP_VIEWPORT_
#define _SABLE_GRAPHICS_VIEWPORT_IMPL_STUP_VIEWPORT_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CViewport;

/** 
*/
class CImplStubViewport
{

public:

	/** @name Accessor*/
	//@{
	CImplStubViewport( CViewport& viewport ) {}
	//@}

	/** @name Manipulator*/
	//@{
    virtual Void Activate() {};
	//@}

};

}

#endif
