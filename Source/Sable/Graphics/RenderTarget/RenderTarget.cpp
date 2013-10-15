#include <Sable\Graphics\RenderTarget\RenderTarget.h>

#include <Sable\Graphics\Common\Impl\Stub\GraphicsManager.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CRenderTarget, CManagedObject );

CRenderTarget::CRenderTarget()
{
}

CRenderTarget::~CRenderTarget()
{
}

Void CRenderTarget::Activate( CRenderer& renderer, Int32 index )
{
}

Void CRenderTarget::Resize( const CVector2i& newSize )
{
	m_Info.TextureInfo.Width = newSize.GetX();
	m_Info.TextureInfo.Height = newSize.GetY();
}

const CRenderTargetInfo& CRenderTarget::GetInfo() const
{
	return m_Info;
}

UInt32 CRenderTarget::GetWidth() const
{
    return m_Info.TextureInfo.Width;
}

UInt32 CRenderTarget::GetHeight() const
{
    return m_Info.TextureInfo.Height;
}
