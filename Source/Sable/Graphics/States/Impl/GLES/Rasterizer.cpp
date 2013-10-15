#include <Sable\Graphics\States\Impl\GLES\Rasterizer.h>

using namespace Sable;

CImplGLESStatesRasterizer::CImplGLESStatesRasterizer( CStatesRasterizer& publicImpl ) :
    CImplStubStatesRasterizer(publicImpl)
{
}

CImplGLESStatesRasterizer::~CImplGLESStatesRasterizer()
{
}

Void CImplGLESStatesRasterizer::Activate()
{
	if( m_PublicImpl->GetDesc().CullMode == nStateCullMode_Disabled )
	{
		glDisable( GL_CULL_FACE );
	}
	else
	{
		glEnable( GL_CULL_FACE );
		glCullFace( TranslateCullMode( m_PublicImpl->GetDesc().CullMode ) );
	}
}

Void CImplGLESStatesRasterizer::Acquire()
{

}


GLenum	CImplGLESStatesRasterizer::TranslateCullMode( EStateCullMode mode )
{
    switch( mode )
    {
    case nStateCullMode_CW:
        return GL_BACK;
    case nStateCullMode_CCW:
        return GL_FRONT;
    case nStateCullMode_Disabled:
        return GL_FRONT;
    }

    DebugError( "Invalid culling mode" );

    return GL_FRONT;
}

GLenum	CImplGLESStatesRasterizer::TranslateFillMode( EStateFillMode mode )
{
    switch( mode )
    {
    case nStateFillMode_WireFrame:
    	DebugError( "Unsuported fill mode in OpenGLES2" );
        return GL_ZERO;
    case nStateFillMode_Solid:
        return GL_ZERO;
    }

    DebugError( "Invalid fill mode" );

    return GL_ZERO ;
}
