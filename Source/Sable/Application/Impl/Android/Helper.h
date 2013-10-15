#ifndef _SABLE_APPLICATION_IMPL_ANDROID_HELPER_
#define _SABLE_APPLICATION_IMPL_ANDROID_HELPER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\Common\DataTypes.h>

#include <Sable\Application\Impl\Android\android_native_app_glue.h>

namespace Sable
{

/** 
*/
class CImplAndroidApplicationHelper 
{  

public:

	/* @name Constructor/Destructor*/
	//@{
	CImplAndroidApplicationHelper();
	~CImplAndroidApplicationHelper();
	//@}

	/* @name Accessors*/
	//@{
    EGLDisplay&     GetEGLDisplay();
    Void            SetEGLDisplay( EGLDisplay& display );
    EGLSurface&     GetEGLSurface();
    Void            SetEGLSurface( EGLSurface& surface );
    EGLContext&     GetEGLContext();
    Void            SetEGLContext( EGLContext& context );

    android_app*    GetAndroidApp();
    Void            SetAndroidApp( android_app* app );
	//@}

    /* @name Attributes*/
    //@{

    //@}

private:

	//Method

	//Attribute
    EGLDisplay      m_EGLDisplay;
    EGLSurface      m_EGLSurface;
    EGLContext      m_EGLContext;
    android_app*    m_AndroidApp;

	//Static method

};

}
#endif
