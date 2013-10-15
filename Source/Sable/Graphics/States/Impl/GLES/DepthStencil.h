#ifndef _SABLE_GRAPHICS_STATES_IMPL_GLES_DEPTHSTENCIL_
#define _SABLE_GRAPHICS_STATES_IMPL_GLES_DEPTHSTENCIL_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\States\Impl\Stub\DepthStencil.h>

namespace Sable
{

/** 

*/
class CImplGLESStatesDepthStencil : public CImplStubStatesDepthStencil
{

public:

    /** @name Constructor/Destructor*/
    //@{
	CImplGLESStatesDepthStencil( CStatesDepthStencil& publicImpl );
    ~CImplGLESStatesDepthStencil();
    //@}

    /** @name Accessors*/
    //@{
    Void Acquire();
    Void Activate();
    //@}

protected:

    // Methods
    GLenum   TranslateDepthFunc( EStateDepthFunc mode );

    // Attributes

};

}

#endif
