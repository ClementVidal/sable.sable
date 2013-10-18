#ifndef _SABLE_GRAPHICS_STATES_IMPL_GLES_SAMPLER_
#define _SABLE_GRAPHICS_STATES_IMPL_GLES_SAMPLER_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/States/Impl/Stub/Sampler.h>

namespace Sable
{

class CStatesSampler;

/** 

*/
class CImplGLESStatesSampler : public CImplStubStatesSampler
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplGLESStatesSampler( CStatesSampler& publicImpl );
    ~CImplGLESStatesSampler();
    //@}

    /** @name Accessors*/
    //@{
    Void Acquire();
    //@}

protected:

    // Methods

    // Attributes
};

}

#endif
