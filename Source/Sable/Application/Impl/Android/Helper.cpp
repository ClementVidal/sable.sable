#include <Sable\Application\Impl\Android\Helper.h>

#include <Sable\Application\Impl\Android\android_native_app_glue.cxx>

using namespace Sable;

CImplAndroidApplicationHelper ImplAndroidApplicationHelper;

CImplAndroidApplicationHelper::CImplAndroidApplicationHelper()
{
    m_AndroidApp = NULL;
}

CImplAndroidApplicationHelper::~CImplAndroidApplicationHelper()
{
}

EGLDisplay& CImplAndroidApplicationHelper::GetEGLDisplay()
{
    return m_EGLDisplay;
}

Void CImplAndroidApplicationHelper::SetEGLDisplay( EGLDisplay& display )
{
    m_EGLDisplay = display;
}

EGLSurface& CImplAndroidApplicationHelper::GetEGLSurface()
{
    return m_EGLSurface;
}

Void CImplAndroidApplicationHelper::SetEGLSurface( EGLSurface& surface )
{
    m_EGLSurface = surface;
}

EGLContext& CImplAndroidApplicationHelper::GetEGLContext()
{
    return m_EGLContext;
}

Void CImplAndroidApplicationHelper::SetEGLContext( EGLContext& context )
{
    m_EGLContext = context;
}

android_app* CImplAndroidApplicationHelper::GetAndroidApp()
{
    return m_AndroidApp;
}

Void CImplAndroidApplicationHelper::SetAndroidApp( android_app* app )
{
    m_AndroidApp = app;
}
