#include <Sable/Graphics/States/Impl/DirectX/Sampler.h>

using namespace Sable;

CImplDirectXStatesSampler::CImplDirectXStatesSampler( CStatesSampler& publicImpl ) :
    CImplStubStatesSampler(publicImpl)
{
    m_State = NULL;
}

CImplDirectXStatesSampler::~CImplDirectXStatesSampler()
{
}

Void CImplDirectXStatesSampler::Acquire()
{
    if( m_State )
        m_State->Release();

    D3D10_SAMPLER_DESC desc;
    MemoryFill( &desc, 0, sizeof( desc ) );

    desc.Filter = TranslateFilter( m_PublicImpl->GetDesc().MinFilter, m_PublicImpl->GetDesc().MagFilter, m_PublicImpl->GetDesc().MipFilter );
	desc.AddressU = TranslateAddressMode( m_PublicImpl->GetDesc().AddressU );
	desc.AddressV = TranslateAddressMode( m_PublicImpl->GetDesc().AddressV );
	desc.AddressW = TranslateAddressMode( m_PublicImpl->GetDesc().AddressW );
	desc.MipLODBias = 0.0f;
	desc.MaxAnisotropy = 16;
	desc.ComparisonFunc = D3D10_COMPARISON_NEVER;
	desc.BorderColor[0] = 0.0f;
	desc.BorderColor[1] = 0.0f;
	desc.BorderColor[2] = 0.0f;
	desc.BorderColor[3] = 0.0f;
	desc.MinLOD = m_PublicImpl->GetDesc().MinLOD;
	desc.MaxLOD = m_PublicImpl->GetDesc().MaxLOD;

    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();
    AssertDXCall( device->CreateSamplerState( &desc, &m_State ) );
}

ID3D10SamplerState* CImplDirectXStatesSampler::GetD3DState() const
{
    return m_State;
}

D3D10_TEXTURE_ADDRESS_MODE	CImplDirectXStatesSampler::TranslateAddressMode( EStateAddress mode ) const
{
    switch( mode )
    {
    case nStateAddress_Wrap:
        return D3D10_TEXTURE_ADDRESS_WRAP;
    case nStateAddress_Mirror:
        return D3D10_TEXTURE_ADDRESS_MIRROR;
    case nStateAddress_Clamp:
        return D3D10_TEXTURE_ADDRESS_CLAMP;
    }

    DebugError( "Invalid texture address mode" );

    return D3D10_TEXTURE_ADDRESS_WRAP;
}

D3D10_FILTER CImplDirectXStatesSampler::TranslateFilter( EStateFilter minMode, EStateFilter magMode, EStateFilter mipMode ) const
{
	if( minMode == nStateFilter_Point && magMode == nStateFilter_Point && mipMode == nStateFilter_Point )
		return D3D10_FILTER_MIN_MAG_MIP_POINT;
	else if( minMode == nStateFilter_Point && magMode == nStateFilter_Point && mipMode == nStateFilter_Linear )
		return D3D10_FILTER_MIN_MAG_POINT_MIP_LINEAR;
	else if( minMode == nStateFilter_Point && magMode == nStateFilter_Linear && mipMode == nStateFilter_Point )
		return D3D10_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
	else if( minMode == nStateFilter_Point && magMode == nStateFilter_Linear && mipMode == nStateFilter_Linear )
		return D3D10_FILTER_MIN_POINT_MAG_MIP_LINEAR;
	else if( minMode == nStateFilter_Linear && magMode == nStateFilter_Point && mipMode == nStateFilter_Point )
		return D3D10_FILTER_MIN_LINEAR_MAG_MIP_POINT;
	else if( minMode == nStateFilter_Linear && magMode == nStateFilter_Point && mipMode == nStateFilter_Linear )
		return D3D10_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR ;
	else if( minMode == nStateFilter_Linear && magMode == nStateFilter_Linear && mipMode == nStateFilter_Point )
		return D3D10_FILTER_MIN_MAG_LINEAR_MIP_POINT;
	else if( minMode == nStateFilter_Linear && magMode == nStateFilter_Linear && mipMode == nStateFilter_Linear )
		return D3D10_FILTER_MIN_MAG_MIP_LINEAR;

    return D3D10_FILTER_MIN_MAG_MIP_POINT;
}
