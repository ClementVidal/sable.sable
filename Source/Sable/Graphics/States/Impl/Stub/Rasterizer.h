#ifndef _SABLE_GRAPHICS_STATES_IMPL_STUB_RASTERIZER_
#define _SABLE_GRAPHICS_STATES_IMPL_STUB_RASTERIZER_

#include <Sable/Core/Common/DataTypes.h>

namespace Sable
{

class CStatesRasterizer;

/** 
*/
class CImplStubStatesRasterizer
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplStubStatesRasterizer( CStatesRasterizer& publicImpl ) { m_PublicImpl = &publicImpl; }
    virtual ~CImplStubStatesRasterizer() {};
    //@}

    /** @name Accessors*/
    //@{
    virtual Void Acquire() {};
    virtual Void Activate() {};
    //@}

protected:

    // Attributes
    CStatesRasterizer*  m_PublicImpl;
};

}

#endif
