#ifndef _SABLE_GRAPHICS_STATES_IMPL_DIRECTX_SAMPLER_
#define _SABLE_GRAPHICS_STATES_IMPL_DIRECTX_SAMPLER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\States\Impl\Stub\Sampler.h>

namespace Sable
{

class CStatesSampler;

/** 

*/
class CImplDirectXStatesSampler : public CImplStubStatesSampler
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplDirectXStatesSampler( CStatesSampler& publicImpl );
    ~CImplDirectXStatesSampler();
    //@}

    /** @name Accessors*/
    //@{
    ID3D10SamplerState* GetD3DState() const;
    Void Acquire();
    //@}

protected:

    // Methods
    D3D10_TEXTURE_ADDRESS_MODE			TranslateAddressMode( EStateAddress mode ) const;
    D3D10_FILTER						TranslateFilter( EStateFilter minMode, EStateFilter magMode, EStateFilter mipMode ) const;

    // Attributes
    ID3D10SamplerState*       m_State;
};

}

#endif
