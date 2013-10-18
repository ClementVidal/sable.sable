#ifndef _SABLE_GRAPHICS_COMMON_IMPL_GLES_GRAPHICSMANAGERHELPER_
#define _SABLE_GRAPHICS_COMMON_IMPL_GLES_GRAPHICSMANAGERHELPER_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/Common/DataTypes.h>

#ifdef SETUP_CONFIG_DEBUG

#define DebugAssertEGLCall( call ) \
call; \
{ \
EGLint eglError = eglGetError(); \
if(eglError != EGL_SUCCESS) { \
DebugLogError( "EGL error: = %i (0x%.8x) at line %i\n", eglError, eglError, __LINE__); \
DebugBreakExecution();\
} \
}

#define DebugAssertGLCall( call ) \
call; \
{ \
GLenum glError = glGetError(); \
if(glError != GL_NO_ERROR) { \
	DebugLogError( "GL error: = %i (0x%.8x) at line %i:\n", glError, glError, __LINE__ ); \
DebugBreakExecution();\
} \
}

#define DebugAssertGLNoError \
{ \
	GLenum glError = glGetError(); \
	if(glError != GL_NO_ERROR) { \
	DebugLogError( "GL error: = %i (0x%.8x) at line %i\n", glError, glError, __LINE__); \
	DebugBreakExecution();\
	} \
}

#else

#define DebugAssertEGLCall( call ) call; 
#define DebugAssertGLCall( call ) call; 
#define DebugAssertGLNoError {}

#endif

#include <EGL/egl.h>

namespace Sable
{

/** 

*/
class CImplGLESGraphicsManagerHelper
{  

public:

	/* @name Constructor/Destructor*/
	//@{
	CImplGLESGraphicsManagerHelper();
	~CImplGLESGraphicsManagerHelper();
	//@}

	/* @name Accessors*/
	//@{
	EGLDisplay&     GetEGLDisplay();
	Void            SetEGLDisplay( EGLDisplay& display );
	EGLSurface&     GetEGLSurface();
	Void            SetEGLSurface( EGLSurface& surface );
	EGLContext&     GetEGLContext();
	Void            SetEGLContext( EGLContext& context );
	EGLConfig&		GetEGLConfig();
	Void            SetEGLConfig( EGLConfig& config );
	//@}

	/* @name Manipulator*/
	//@{
	static		Bool	IsCompressedTextureFormat( ETextureFormat format );
	static     GLenum	TranslatePixelFormat( ETextureFormat format );
	static     GLenum	TranslatePixelType( ETextureFormat format );
	static     GLenum	TranslatePrimitiveType( EPrimitiveType format );
	//@}

private:

	//Method

	//Attribute
	EGLDisplay      m_EGLDisplay;
	EGLSurface      m_EGLSurface;
	EGLContext      m_EGLContext;
	EGLConfig		m_EGLConfigs;

	//Static method

};

}
#endif

