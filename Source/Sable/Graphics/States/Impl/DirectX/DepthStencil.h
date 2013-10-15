#ifndef _SABLE_GRAPHICS_STATES_IMPL_MSW_DEPTHSTENCIL_
#define _SABLE_GRAPHICS_STATES_IMPL_MSW_DEPTHSTENCIL_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\States\Impl\Stub\DepthStencil.h>

namespace Sable
{

/** 

*/
class CImplDirectXStatesDepthStencil : public CImplStubStatesDepthStencil
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplDirectXStatesDepthStencil( CStatesDepthStencil& publicImpl );
    ~CImplDirectXStatesDepthStencil();
    //@}

    /** @name Accessors*/
    //@{
    ID3D10DepthStencilState*    GetD3DState() const;
    Void Acquire();
    Void Activate();
    //@}

protected:

    // Methods
    D3D10_COMPARISON_FUNC   TranslateDepthFunc( EStateDepthFunc mode );

    // Attributes
    ID3D10DepthStencilState*       m_State;
};

}

#endif
