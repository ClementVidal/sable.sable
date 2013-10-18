#ifndef _SABLE_GRAPHICS_STATES_IMPL_MSW_BLEND_
#define _SABLE_GRAPHICS_STATES_IMPL_MSW_BLEND_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/States/Impl/Stub/Blend.h>

namespace Sable
{

/** 

*/
class CImplDirectXStatesBlend : public CImplStubStatesBlend
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplDirectXStatesBlend( CStatesBlend& publicImpl );
    ~CImplDirectXStatesBlend();
    //@}

    /** @name Accessors*/
    //@{
    ID3D10BlendState* GetD3DState() const;
    Void Acquire();
    Void Activate();
    //@}

protected:

    // Methods
    UInt32                  TranslateWriteMask( UInt32 mode );
    D3D10_BLEND_OP          TranslateBlendOp( EStateBlendOp mode );
    D3D10_BLEND             TranslateBlend( EStateBlend mode );

    // Attributes
    ID3D10BlendState*       m_State;
};

}

#endif
