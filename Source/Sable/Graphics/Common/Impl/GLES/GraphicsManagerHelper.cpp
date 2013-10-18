#include <Sable/Graphics/Common/Impl/GLES/GraphicsManagerHelper.h>

using namespace Sable;

CImplGLESGraphicsManagerHelper ImplGLESGraphicsManagerHelper;

CImplGLESGraphicsManagerHelper::CImplGLESGraphicsManagerHelper()
{
}

CImplGLESGraphicsManagerHelper::~CImplGLESGraphicsManagerHelper()
{
}

GLenum	CImplGLESGraphicsManagerHelper::TranslatePixelFormat( ETextureFormat format )
{
	if( format == nTextureFormat_R8G8B8A8 )
		return GL_RGBA;
	else if( format == nTextureFormat_R8G8B8 )
		return GL_RGB;
	else if( format == nTextureFormat_R5G6B5 )
		return GL_RGB;
	else if( format == nTextureFormat_A8 )
		return GL_ALPHA;
	else if( format == nTextureFormat_L8 )
		return GL_LUMINANCE;

	return GL_RGBA;
}


GLenum	CImplGLESGraphicsManagerHelper::TranslatePrimitiveType( EPrimitiveType type )
{
	if( type == nPrimitiveType_TriangleList )
		return GL_TRIANGLES;
	else if( type == nPrimitiveType_TriangleStrip )
		return GL_TRIANGLE_STRIP;
	else if( type == nPrimitiveType_LineStrip )
		return GL_LINE_STRIP;
	else if( type == nPrimitiveType_LineList )
		return GL_LINES;
	else if( type == nPrimitiveType_PointList )
		return GL_POINTS;

	return GL_TRIANGLES;
}

Bool CImplGLESGraphicsManagerHelper::IsCompressedTextureFormat( ETextureFormat format )
{
	return	format == nTextureFormat_DXT1 || format == nTextureFormat_DXT2 || 
			format == nTextureFormat_DXT2 || format == nTextureFormat_DXT4 || 
			format == nTextureFormat_DXT5 || format == nTextureFormat_ETC || 
			format == nTextureFormat_ATC  || format == nTextureFormat_3DC;
}

GLenum	CImplGLESGraphicsManagerHelper::TranslatePixelType( ETextureFormat format )
{
	if( format == nTextureFormat_R8G8B8A8 )
		return GL_UNSIGNED_BYTE;
	else if( format == nTextureFormat_R8G8B8 )
		return GL_UNSIGNED_BYTE;
	else if( format == nTextureFormat_R5G6B5 )
		return  GL_UNSIGNED_SHORT_5_6_5;
	else if( format == nTextureFormat_A8 )
		return GL_UNSIGNED_BYTE;
	else if( format == nTextureFormat_L8 )
		return GL_UNSIGNED_BYTE;
	else if( format == nTextureFormat_DXT1 )
		return GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
	else if( format == nTextureFormat_DXT2 )
		return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
#ifdef SETUP_OPENGLES_USE_ANGLE
	else if( format == nTextureFormat_DXT3 )
		return GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE;
	else if( format == nTextureFormat_DXT5 )
		return GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE;
#endif

	DebugError("Invalid PixelType");
	return GL_UNSIGNED_BYTE;
}


EGLDisplay& CImplGLESGraphicsManagerHelper::GetEGLDisplay()
{
	return m_EGLDisplay;
}

Void CImplGLESGraphicsManagerHelper::SetEGLDisplay( EGLDisplay& display )
{
	m_EGLDisplay = display;
}

EGLSurface& CImplGLESGraphicsManagerHelper::GetEGLSurface()
{
	return m_EGLSurface;
}

Void CImplGLESGraphicsManagerHelper::SetEGLSurface( EGLSurface& surface )
{
	m_EGLSurface = surface;
}

EGLContext& CImplGLESGraphicsManagerHelper::GetEGLContext()
{
	return m_EGLContext;
}

Void CImplGLESGraphicsManagerHelper::SetEGLContext( EGLContext& context )
{
	m_EGLContext = context;
}

EGLConfig& CImplGLESGraphicsManagerHelper::GetEGLConfig()
{
	return m_EGLConfigs;
}

Void CImplGLESGraphicsManagerHelper::SetEGLConfig( EGLConfig& config )
{
	m_EGLConfigs = config;
}