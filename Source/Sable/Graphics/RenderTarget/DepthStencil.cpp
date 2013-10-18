#include <Sable/Graphics/RenderTarget/DepthStencil.h>

#include <Sable/Graphics/RenderTarget/Impl/Stub/DepthStencil.h>
#include <Sable/Graphics/Common/Manager.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CRenderTargetDepthStencil, CManagedObject );

CRenderTargetDepthStencil::CRenderTargetDepthStencil() :
    m_Impl( *this )
{
}

CRenderTargetDepthStencil::~CRenderTargetDepthStencil()
{

}

const CRenderTargetInfo& CRenderTargetDepthStencil::GetInfo() const
{
	return m_Info;
}

Void CRenderTargetDepthStencil::Resize( const CVector2i& newSize )
{	
	CRenderTargetInfo info = GetInfo();
	if( newSize == CVector2i( info.TextureInfo.Width, info.TextureInfo.Height ) ) 
		return;

	m_Impl.Resize( newSize );
	m_Info.TextureInfo.Width = newSize.GetX();
	m_Info.TextureInfo.Height = newSize.GetY();
}

Void CRenderTargetDepthStencil::Activate( )
{
	DebugGraphicCommandGroup( "CRenderTargetDepthStencil::Activate" );
    m_Impl.Activate( );
}

Bool CRenderTargetDepthStencil::Create( const CRenderTargetInfo& info )
{
    m_Impl.Initialize( info );
	m_Info = info;
    return TRUE;
}

Void CRenderTargetDepthStencil::Clear( Float32 depth, UInt8 stencil )
{
	DebugGraphicCommandGroup( "CRenderTargetDepthStencil::Clear" );
    m_Impl.Clear( depth, stencil );
}