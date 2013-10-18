#include <Sable/Graphics/RenderTarget/Texture.h>

#include <Sable/Graphics/RenderTarget/Impl/Stub/Texture.h>
#include <Sable/Graphics/Common/Manager.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CRenderTargetTexture, CRenderTarget );

CRenderTargetTexture::CRenderTargetTexture() :
    m_Impl( *this )
{
	m_MinFilteringMode = nStateFilter_Point;
	m_MagFilteringMode = nStateFilter_Point;
}

CRenderTargetTexture::CRenderTargetTexture( const CRenderTargetInfo& info ) :
    m_Impl( *this )
{
	m_MinFilteringMode = nStateFilter_Point;
	m_MagFilteringMode = nStateFilter_Point;
    Create( info );
}

CRenderTargetTexture::~CRenderTargetTexture()
{

}

Void CRenderTargetTexture::Create( const CRenderTargetInfo& info )
{
	m_Impl.Initialize( info );
	m_Info = info;
}

Void CRenderTargetTexture::Resize( const CVector2i& newSize )
{
	if( newSize == CVector2i( m_Info.TextureInfo.Width, m_Info.TextureInfo.Height ) ) 
		return;

	CRenderTargetInfo info = m_Info;
	info.TextureInfo.Width = newSize.GetX();
	info.TextureInfo.Height = newSize.GetY();

	m_Impl.Initialize( info );
	m_Info = info;
}

Void CRenderTargetTexture::Activate( CRenderer& renderer, Int32 index )
{	
	DebugGraphicCommandGroup( "CRenderTargetTexture::Activate" );
	m_Impl.Activate( index );
    CRenderTarget::Activate( renderer, index);
}

Void CRenderTargetTexture::Clear( const CColor& color )
{
    DebugGraphicCommandGroup( "CRenderTargetTexture::Clear" );
    m_Impl.Clear( color );
}
