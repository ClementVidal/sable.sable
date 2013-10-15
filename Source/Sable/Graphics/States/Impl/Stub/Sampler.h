#ifndef _SABLE_GRAPHICS_STATES_IMPL_STUB_SAMPLER_
#define _SABLE_GRAPHICS_STATES_IMPL_STUB_SAMPLER_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CStatesSampler;

/** 
*/
class CImplStubStatesSampler
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplStubStatesSampler( CStatesSampler& publicImpl ) { m_PublicImpl = &publicImpl; }
    virtual ~CImplStubStatesSampler() {};
    //@}

    /** @name Accessors*/
    //@{
    virtual Void Acquire() {};
    //@}

protected:

    // Attributes
    CStatesSampler*  m_PublicImpl;
};

}

#endif
