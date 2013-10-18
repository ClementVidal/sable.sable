#include <Sable/Graphics/States/Impl/DirectX/Rasterizer.h>

using namespace Sable;

CImplDirectXStatesRasterizer::CImplDirectXStatesRasterizer( CStatesRasterizer& publicImpl ) :
    CImplStubStatesRasterizer(publicImpl)
{
    m_State = NULL;
}

CImplDirectXStatesRasterizer::~CImplDirectXStatesRasterizer()
{
}

Void CImplDirectXStatesRasterizer::Activate()
{
    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();
	DebugAssert( m_State );
    device->RSSetState( m_State );
}

Void CImplDirectXStatesRasterizer::Acquire()
{
    if( m_State )
        m_State->Release();

    D3D10_RASTERIZER_DESC desc;
    MemoryFill( &desc, 0, sizeof( desc ) );

    desc.AntialiasedLineEnable = FALSE;
    desc.CullMode = TranslateCullMode( m_PublicImpl->GetDesc().CullMode );
    desc.DepthBias = (Int32)m_PublicImpl->GetDesc().DepthBias;
    desc.DepthBiasClamp = 0.0f;
    desc.DepthClipEnable = TRUE;
    desc.FillMode = TranslateFillMode( m_PublicImpl->GetDesc().FillMode );
    desc.FrontCounterClockwise = FALSE;
    desc.MultisampleEnable = m_PublicImpl->GetDesc().MultiSamplingEnabled;
    desc.ScissorEnable = m_PublicImpl->GetDesc().ScissorRectEnabled;
    desc.SlopeScaledDepthBias = 0.0f;

    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();
    AssertDXCall( device->CreateRasterizerState( &desc, &m_State ) );
}

ID3D10RasterizerState* CImplDirectXStatesRasterizer::GetD3DState() const
{
    return m_State;
}

D3D10_CULL_MODE	CImplDirectXStatesRasterizer::TranslateCullMode( EStateCullMode mode )
{
    switch( mode )
    {
    case nStateCullMode_CW:
        return D3D10_CULL_FRONT;
    case nStateCullMode_CCW:
        return D3D10_CULL_BACK;
    case nStateCullMode_Disabled:
        return D3D10_CULL_NONE;
    }

    DebugError( "Invalid culling mode" );

    return D3D10_CULL_NONE;
}

D3D10_FILL_MODE	CImplDirectXStatesRasterizer::TranslateFillMode( EStateFillMode mode )
{
    switch( mode )
    {
    case nStateFillMode_WireFrame:
        return D3D10_FILL_WIREFRAME;
    case nStateFillMode_Solid:
        return D3D10_FILL_SOLID;
    }

    DebugError( "Invalid fill mode" );

    return D3D10_FILL_WIREFRAME ;
}
