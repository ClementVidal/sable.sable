#include <Sable\Graphics\States\Impl\DirectX\Blend.h>

#include <Sable\Graphics\States\Sampler.h>
#include <Sable\Graphics\States\Blend.h>
#include <Sable\Graphics\States\Rasterizer.h>
#include <Sable\Graphics\States\DepthStencil.h>

using namespace Sable;

CImplDirectXStatesBlend::CImplDirectXStatesBlend( CStatesBlend& publicImpl ) :
    CImplStubStatesBlend(publicImpl)
{
    m_State = NULL;
}

CImplDirectXStatesBlend::~CImplDirectXStatesBlend()
{
}

ID3D10BlendState* CImplDirectXStatesBlend::GetD3DState() const
{
    return m_State;
}

Void CImplDirectXStatesBlend::Activate()
{
    Float32 BlendFactor[4];
    BlendFactor[0] = 1.0f;
    BlendFactor[1] = 1.0f;
    BlendFactor[2] = 1.0f;
    BlendFactor[3] = 1.0f;

    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();
	DebugAssert( m_State );	
    device->OMSetBlendState ( m_State, BlendFactor, 0xffffffff );
}

Void CImplDirectXStatesBlend::Acquire()
{
    if( m_State )
        m_State->Release();

    D3D10_BLEND_DESC desc;
    MemoryFill( &desc, 0, sizeof( desc ) );

    UInt32 i;
    for(i=0;i<8;i++)
    {
        desc.BlendEnable[i] = m_PublicImpl->GetDesc().BlendEnable[i];
        desc.RenderTargetWriteMask[i] = TranslateWriteMask( m_PublicImpl->GetDesc().WriteMask[0] );
    }

    desc.BlendOp = TranslateBlendOp( m_PublicImpl->GetDesc().ColorBlendOp );
    desc.BlendOpAlpha = TranslateBlendOp( m_PublicImpl->GetDesc().AlphaBlendOp );
    desc.SrcBlend = TranslateBlend( m_PublicImpl->GetDesc().SrcColorBlend );
    desc.DestBlend = TranslateBlend( m_PublicImpl->GetDesc().DstColorBlend );
    desc.SrcBlendAlpha = TranslateBlend( m_PublicImpl->GetDesc().SrcAlphaBlend );
    desc.DestBlendAlpha = TranslateBlend( m_PublicImpl->GetDesc().DstAlphaBlend );
    desc.AlphaToCoverageEnable = FALSE;

    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();
    AssertDXCall( device->CreateBlendState( &desc, &m_State ) );
}

UInt32 CImplDirectXStatesBlend::TranslateWriteMask( UInt32 mode )
{
    UInt32 mask = 0;

    if( mode & nStateWriteMask_Red )
        mask |= D3D10_COLOR_WRITE_ENABLE_RED;

    if( mode & nStateWriteMask_Green )
        mask |= D3D10_COLOR_WRITE_ENABLE_GREEN;

    if( mode & nStateWriteMask_Blue )
        mask |= D3D10_COLOR_WRITE_ENABLE_BLUE;

    if( mode & nStateWriteMask_Alpha )
        mask |= D3D10_COLOR_WRITE_ENABLE_ALPHA;

	return mask;
}

D3D10_BLEND_OP CImplDirectXStatesBlend::TranslateBlendOp( EStateBlendOp mode )
{
	switch( mode )
	{
	case nStateBlendOp_Add:
		return D3D10_BLEND_OP_ADD;
	case nStateBlendOp_Substract:
		return D3D10_BLEND_OP_SUBTRACT;
	case nStateBlendOp_RevSubstract:
		return D3D10_BLEND_OP_REV_SUBTRACT;
	case nStateBlendOp_Max:
		return D3D10_BLEND_OP_MAX;
	case nStateBlendOp_Min:
		return D3D10_BLEND_OP_MIN;
	}

	DebugError( "Invalid blend op mode" );

	return D3D10_BLEND_OP_ADD;
}

D3D10_BLEND CImplDirectXStatesBlend::TranslateBlend( EStateBlend mode )
{
	switch( mode )
	{
	case nStateBlend_Zero:
		return D3D10_BLEND_ZERO;
	case nStateBlend_One:
		return D3D10_BLEND_ONE;
	case nStateBlend_SrcColor:
		return D3D10_BLEND_SRC_COLOR;
	case nStateBlend_InvSrcColor:
		return D3D10_BLEND_INV_SRC_COLOR;
	case nStateBlend_SrcAlpha:
		return D3D10_BLEND_SRC_ALPHA;
	case nStateBlend_InvSrcAlpha:
		return  D3D10_BLEND_INV_SRC_ALPHA;
	case nStateBlend_DestAlpha:
		return D3D10_BLEND_DEST_ALPHA;
	case nStateBlend_InvDestAlpha:
		return D3D10_BLEND_INV_DEST_ALPHA;
	case nStateBlend_DestColor:
		return D3D10_BLEND_DEST_COLOR ;
    case nStateBlend_InvDestColor:
		return D3D10_BLEND_INV_DEST_COLOR;
	}

	DebugError( "Invalid blend mode" );

	return D3D10_BLEND_ZERO;
}
