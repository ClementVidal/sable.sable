#ifndef _SABLE_GRAPHICS_STATES_IMPL_STUB_BLEND_
#define _SABLE_GRAPHICS_STATES_IMPL_STUB_BLEND_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CStatesBlend;

/** 
*/
class CImplStubStatesBlend
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplStubStatesBlend( CStatesBlend& publicImpl ) { m_PublicImpl = &publicImpl; }
    virtual ~CImplStubStatesBlend() {};
    //@}

    /** @name Accessors*/
    //@{
    virtual Void Acquire() {};
    virtual Void Activate() {};
    //@}

protected:

    // Attributes
    CStatesBlend*  m_PublicImpl;
};

}

#endif
