#include <Sable/Graphics/RenderTarget/BackBuffer.h>

#include <Sable/Graphics/RenderTarget/Impl/Stub/BackBuffer.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CRenderTargetBackBuffer, CRenderTarget );

CRenderTargetBackBuffer::CRenderTargetBackBuffer():
    CRenderTarget(), 
    m_Impl( *this )
{
	m_OwnerSwapChain = NULL;
}

CRenderTargetBackBuffer::~CRenderTargetBackBuffer()
{
}

CImplRenderTargetBackBuffer& CRenderTargetBackBuffer::GetImpl()
{
	return m_Impl;
}

Bool CRenderTargetBackBuffer::Initialize( CSwapChain& chain )
{
	m_OwnerSwapChain = &chain;
	m_Impl.Initialize( );
	m_Info = chain.GetInfo().RenderTargetInfo;


    return TRUE;
}

CSwapChain* CRenderTargetBackBuffer::GetOwnerSwapChain() const
{
	return m_OwnerSwapChain;
}

Void CRenderTargetBackBuffer::Resize( const CVector2i& newSize )
{
	CRenderTargetInfo info = GetInfo();
	if( newSize == CVector2i( info.TextureInfo.Width, info.TextureInfo.Height ) ) 
		return;

	DebugAssert( m_OwnerSwapChain );
	m_Impl.Resize( newSize );
	CRenderTarget::Resize(newSize);
}

Void CRenderTargetBackBuffer::Activate( CRenderer& renderer, Int32 index )
{
	DebugGraphicCommandGroup( "CRenderTargetBackBuffer::Activate" );
	m_Impl.Activate( index );
    CRenderTarget::Activate(renderer, index);
}

Void CRenderTargetBackBuffer::Clear( const CColor& color )
{
    DebugGraphicCommandGroup( "CRenderTargetBackBuffer::Clear" );
    m_Impl.Clear( color );
}
