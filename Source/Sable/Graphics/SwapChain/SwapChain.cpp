#include <Sable\Graphics\SwapChain\SwapChain.h>

#include <Sable\Graphics\Common\Manager.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CSwapChain, CManagedObject );

CSwapChain::CSwapChain( ) :
	m_Impl( *this )
{
    m_OwnerWindow = NULL;
}

CSwapChain::~CSwapChain()
{
}

CApplicationWindow* CSwapChain::GetOwnerWindow() const
{
    return m_OwnerWindow;
}

CRenderTargetBackBuffer& CSwapChain::GetBackBuffer()
{
    return m_BackBuffer;
}

CRenderTargetDepthStencil& CSwapChain::GetDepthStencil()
{
    return m_DepthStencil;
}

const CSwapChainInfo& CSwapChain::GetInfo() const
{
    return m_Info;  
}

Void CSwapChain::Clear( Float32 depth, UInt8 stencil, const CColor& color )
{
	GetBackBuffer().Clear( color );
	GetDepthStencil().Clear( depth, stencil );
}

/**
Resize the swap chain to a given resolution.
This will resize it's backbuffer AND depth stencil without changing internal pixel format
*/
Void CSwapChain::Resize( const CVector2i& newSize )
{
	if( newSize == CVector2i( m_Info.RenderTargetInfo.TextureInfo.Width, m_Info.RenderTargetInfo.TextureInfo.Height ) ) 
		return;

	m_Impl.Resize( newSize );

	// This will resize the backbuffer correctly
	GetBackBuffer().Resize( newSize );

	// This will resize the Depth stencil correctly
	GetDepthStencil().Resize( newSize );

	GetViewport().Resize( newSize );
}

Bool CSwapChain::Initialize( CApplicationWindow& ownerWindow, const CSwapChainInfo& info)
{
    m_OwnerWindow = &ownerWindow;

    Bool ret = TRUE;
    m_Info = info;
    ret = m_Impl.Initialize( );
    if( !ret )
        return FALSE;

    CRenderTargetInfo depthStencilInfo;
    depthStencilInfo.TextureInfo.Format = nTextureFormat_D24S8;
    depthStencilInfo.TextureInfo.Width = info.RenderTargetInfo.TextureInfo.Width;
    depthStencilInfo.TextureInfo.Height = info.RenderTargetInfo.TextureInfo.Height;
    depthStencilInfo.MultiSamplingQuality = info.RenderTargetInfo.MultiSamplingQuality;

    m_Viewport.Set( 0, 0, info.RenderTargetInfo.TextureInfo.Width, info.RenderTargetInfo.TextureInfo.Height, 0.0f, 1.0f );
    if( m_BackBuffer.Initialize( *this ) )
        return m_DepthStencil.Create( depthStencilInfo );

    return FALSE;
}

const CImplSwapChain& CSwapChain::GetImpl() const
{
    return m_Impl;
}

Bool CSwapChain::Present()
{
    DebugGraphicCommandGroup("CSwapChain::Present");
    return m_Impl.Present();
}

CViewport& CSwapChain::GetViewport()
{
    return m_Viewport;
}