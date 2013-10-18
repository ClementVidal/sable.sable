#ifndef _SABLE_GRAPHICS_STATES_IMPL_DIRECTX_RASTERIZER_
#define _SABLE_GRAPHICS_STATES_IMPL_DIRECTX_RASTERIZER_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/States/Impl/Stub/Rasterizer.h>

namespace Sable
{

/** 

*/
class CImplDirectXStatesRasterizer : public CImplStubStatesRasterizer
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplDirectXStatesRasterizer( CStatesRasterizer& publicImpl );
    ~CImplDirectXStatesRasterizer();
    //@}

    /** @name Accessors*/
    //@{
    ID3D10RasterizerState* GetD3DState() const;
    Void Acquire();
    Void Activate();
    //@}

protected:

    // Methods
    D3D10_CULL_MODE         TranslateCullMode( EStateCullMode mode );
    D3D10_FILL_MODE	        TranslateFillMode( EStateFillMode mode );

    // Attributes
    ID3D10RasterizerState*       m_State;
};

}

#endif
