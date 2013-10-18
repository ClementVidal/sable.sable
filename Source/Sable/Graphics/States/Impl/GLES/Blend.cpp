#include <Sable/Graphics/States/Impl/GLES/Blend.h>

#include <Sable/Graphics/States/Blend.h>


using namespace Sable;

CImplGLESStatesBlend::CImplGLESStatesBlend( CStatesBlend& publicImpl ) :
    CImplStubStatesBlend(publicImpl)
{
}

CImplGLESStatesBlend::~CImplGLESStatesBlend()
{
}


Void CImplGLESStatesBlend::Activate()
{
	const CStatesBlend::SDesc& desc = m_PublicImpl->GetDesc();

	if( desc.BlendEnable[0] )
	{
		glEnable( GL_BLEND);
	}
	else
	{
		glDisable( GL_BLEND );
	}

	glBlendFuncSeparate(
			TranslateBlend( desc.SrcColorBlend ), TranslateBlend( desc.DstColorBlend ),
			TranslateBlend( desc.SrcAlphaBlend ), TranslateBlend( desc.DstAlphaBlend ) );

	glBlendEquationSeparate(
			TranslateBlendOp( desc.ColorBlendOp ),
			TranslateBlendOp( desc.AlphaBlendOp ) );
}

Void CImplGLESStatesBlend::Acquire()
{

}

UInt32 CImplGLESStatesBlend::TranslateWriteMask( UInt32 mode )
{
	return 0;
}

GLenum CImplGLESStatesBlend::TranslateBlendOp( EStateBlendOp mode )
{
	switch( mode )
	{
	case nStateBlendOp_Add:
		return GL_FUNC_ADD;
	case nStateBlendOp_Substract:
		return GL_FUNC_SUBTRACT;
	case nStateBlendOp_RevSubstract:
		return GL_FUNC_REVERSE_SUBTRACT;

	case nStateBlendOp_Max:
		DebugError( "Unsuported blend op in OpenGLES2" );
		return GL_FUNC_ADD;
	case nStateBlendOp_Min:
		DebugError( "Unsuported blend op in OpenGLES2" );
		return GL_FUNC_ADD;
	}

	DebugError( "Invalid blend op mode" );

	return GL_FUNC_ADD;
}

GLenum CImplGLESStatesBlend::TranslateBlend( EStateBlend mode )
{
	switch( mode )
	{
	case nStateBlend_Zero:
		return GL_ZERO;
	case nStateBlend_One:
		return GL_ONE;
	case nStateBlend_SrcColor:
		return GL_SRC_COLOR;
	case nStateBlend_InvSrcColor:
		return GL_ONE_MINUS_SRC_COLOR;
	case nStateBlend_SrcAlpha:
		return GL_SRC_ALPHA;
	case nStateBlend_InvSrcAlpha:
		return  GL_ONE_MINUS_SRC_ALPHA;
	case nStateBlend_DestAlpha:
		return GL_DST_ALPHA;
	case nStateBlend_InvDestAlpha:
		return GL_ONE_MINUS_DST_ALPHA;
	case nStateBlend_DestColor:
		return GL_DST_COLOR ;
    case nStateBlend_InvDestColor:
		return GL_ONE_MINUS_DST_COLOR;
	}

	DebugError( "Invalid blend mode" );

	return GL_ZERO;
}
