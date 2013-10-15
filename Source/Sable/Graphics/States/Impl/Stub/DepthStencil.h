#ifndef _SABLE_GRAPHICS_STATES_IMPL_STUB_DEPTHSTENCIL_
#define _SABLE_GRAPHICS_STATES_IMPL_STUB_DEPTHSTENCIL_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CStatesDepthStencil;

/** 
*/
class CImplStubStatesDepthStencil
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplStubStatesDepthStencil( CStatesDepthStencil& publicImpl ) { m_PublicImpl = &publicImpl; }
    virtual ~CImplStubStatesDepthStencil() {};
    //@}

    /** @name Accessors*/
    //@{
    virtual Void Acquire() {};
    virtual Void Activate() {};
    //@}

protected:

    // Attributes
    CStatesDepthStencil*  m_PublicImpl;
};

}

#endif
