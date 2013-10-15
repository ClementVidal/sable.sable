#include <Sable\Graphics\States\Impl\DirectX\DepthStencil.h>

using namespace Sable;

CImplDirectXStatesDepthStencil::CImplDirectXStatesDepthStencil( CStatesDepthStencil& publicImpl ) :
    CImplStubStatesDepthStencil(publicImpl)
{
    m_State = NULL;
}

CImplDirectXStatesDepthStencil::~CImplDirectXStatesDepthStencil()
{
}

ID3D10DepthStencilState* CImplDirectXStatesDepthStencil::GetD3DState() const
{
    return m_State;
}

Void CImplDirectXStatesDepthStencil::Activate()
{
    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();
	DebugAssert( m_State );
    device->OMSetDepthStencilState ( m_State, 0 );
}

Void CImplDirectXStatesDepthStencil::Acquire()
{
    if( m_State )
	{
        m_State->Release();
		m_State = NULL;
	}

    D3D10_DEPTH_STENCIL_DESC desc;
    MemoryFill( &desc, 0, sizeof( desc ) );

    desc.DepthEnable = m_PublicImpl->GetDesc().DepthTestEnable;
    desc.DepthFunc = TranslateDepthFunc( m_PublicImpl->GetDesc().DepthFunc );
    desc.DepthWriteMask = m_PublicImpl->GetDesc().DepthWriteEnable ? D3D10_DEPTH_WRITE_MASK_ALL : D3D10_DEPTH_WRITE_MASK_ZERO;
    desc.StencilEnable = FALSE;

    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();
    AssertDXCall( device->CreateDepthStencilState( &desc, &m_State ) );
}

D3D10_COMPARISON_FUNC CImplDirectXStatesDepthStencil::TranslateDepthFunc( EStateDepthFunc mode )
{
    switch( mode )
    {
    case nStateDepthFunc_Never:
        return D3D10_COMPARISON_NEVER;
    case nStateDepthFunc_Less:
        return  D3D10_COMPARISON_LESS;
    case nStateDepthFunc_Equal:
        return D3D10_COMPARISON_EQUAL ;
    case nStateDepthFunc_LessEqual:
        return D3D10_COMPARISON_LESS_EQUAL;
    case nStateDepthFunc_Greater:
        return D3D10_COMPARISON_GREATER;
    }

    DebugError( "Invalid Depth func mode" );

    return D3D10_COMPARISON_NEVER;
}