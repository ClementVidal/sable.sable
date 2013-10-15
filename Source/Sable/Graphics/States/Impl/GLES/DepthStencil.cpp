#include <Sable\Graphics\States\Impl\GLES\DepthStencil.h>

using namespace Sable;

CImplGLESStatesDepthStencil::CImplGLESStatesDepthStencil( CStatesDepthStencil& publicImpl ) :
    CImplStubStatesDepthStencil(publicImpl)
{

}

CImplGLESStatesDepthStencil::~CImplGLESStatesDepthStencil()
{
}

Void CImplGLESStatesDepthStencil::Activate()
{
	if( m_PublicImpl->GetDesc().DepthTestEnable )
		glEnable( GL_DEPTH_TEST );
	else
		glDisable( GL_DEPTH_TEST );

	glDepthMask( m_PublicImpl->GetDesc().DepthWriteEnable );

	glDepthFunc( TranslateDepthFunc( m_PublicImpl->GetDesc().DepthFunc ) );
}

Void CImplGLESStatesDepthStencil::Acquire()
{

}

GLenum CImplGLESStatesDepthStencil::TranslateDepthFunc( EStateDepthFunc mode )
{
    switch( mode )
    {
    case nStateDepthFunc_Never:
        return GL_NEVER;
    case nStateDepthFunc_Less:
        return  GL_LESS;
    case nStateDepthFunc_Equal:
        return GL_EQUAL ;
    case nStateDepthFunc_LessEqual:
        return GL_LEQUAL;
    case nStateDepthFunc_Greater:
        return GL_GREATER;
    }

    DebugError( "Invalid Depth func mode" );

    return GL_NEVER;
}
