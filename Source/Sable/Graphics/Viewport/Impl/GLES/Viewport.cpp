#include <Sable\Graphics\Viewport\Impl\GLES\Viewport.h>


using namespace Sable;

CImplGLESViewport::CImplGLESViewport( CViewport& publicImpl ):
    CImplStubViewport( publicImpl )
{
    m_PublicImpl = &publicImpl;
}

CImplGLESViewport::~CImplGLESViewport()
{
	
}

Void CImplGLESViewport::Activate()
{
    glDepthRangef( m_PublicImpl->GetMinDepth(), m_PublicImpl->GetMaxDepth() );
    glViewport( m_PublicImpl->GetTopLeftX(), m_PublicImpl->GetTopLeftY(), m_PublicImpl->GetWidth(), m_PublicImpl->GetHeight() );
}
