#ifndef _SABLE_GRAPHICS_STATES_IMPL_GLES_RASTERIZER_
#define _SABLE_GRAPHICS_STATES_IMPL_GLES_RASTERIZER_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/States/Impl/Stub/Rasterizer.h>

#include <GLES2/gl2.h>

namespace Sable
{

/** 

*/
class CImplGLESStatesRasterizer : public CImplStubStatesRasterizer
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplGLESStatesRasterizer( CStatesRasterizer& publicImpl );
    ~CImplGLESStatesRasterizer();
    //@}

    /** @name Accessors*/
    //@{
    Void Acquire();
    Void Activate();
    //@}

protected:

    // Methods
    GLenum         TranslateCullMode( EStateCullMode mode );
    GLenum	        TranslateFillMode( EStateFillMode mode );

    // Attributes

};

}

#endif
