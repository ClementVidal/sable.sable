#include <Sable/Application/Impl/Android/StandAloneWindow.h>

#include <Sable/Application/Impl/Android/Helper.h>

using namespace Sable;

extern CImplAndroidApplicationHelper ImplAndroidApplicationHelper;

CImplAndroidStandAloneWindow::CImplAndroidStandAloneWindow() 
{
}

CImplAndroidStandAloneWindow::~CImplAndroidStandAloneWindow()
{
}

UInt32 CImplAndroidStandAloneWindow::GetHandle() const
{
    return m_Handle;
}

Void CImplAndroidStandAloneWindow::Initialize( const CTextureInfo& info )
{
    const EGLint attribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BLUE_SIZE, 5,
        EGL_GREEN_SIZE, 6,
        EGL_RED_SIZE, 5,
        EGL_NONE
    };
    EGLint w, h, dummy, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;

    /* Here, the application chooses the configuration it desires. In this
     * sample, we have a very simplified selection process, where we pick
     * the first EGLConfig that matches our criteria */
    eglChooseConfig(ImplAndroidApplicationHelper.GetEGLDisplay(), attribs, &config, 1, &numConfigs);

    DebugLogInfo("CImplAndroidStandAloneWindow::Initialize: Available EGL config count: %d",numConfigs );

    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
    eglGetConfigAttrib(ImplAndroidApplicationHelper.GetEGLDisplay(), config, EGL_NATIVE_VISUAL_ID, &format);

    ANativeWindow_setBuffersGeometry( ImplAndroidApplicationHelper.GetAndroidApp()->window, 0, 0, format);

    surface = eglCreateWindowSurface(ImplAndroidApplicationHelper.GetEGLDisplay(), config, ImplAndroidApplicationHelper.GetAndroidApp()->window, NULL);
    context = eglCreateContext(ImplAndroidApplicationHelper.GetEGLDisplay(), config, NULL, NULL);

    if (eglMakeCurrent(ImplAndroidApplicationHelper.GetEGLDisplay(), surface, surface, context) == EGL_FALSE) 
    {
        DebugError("Failled to set current EGL context");
        return;
    }

    ImplAndroidApplicationHelper.SetEGLContext( context );
    ImplAndroidApplicationHelper.SetEGLSurface( surface );

    eglQuerySurface(ImplAndroidApplicationHelper.GetEGLDisplay(), surface, EGL_WIDTH, &w);
    eglQuerySurface(ImplAndroidApplicationHelper.GetEGLDisplay(), surface, EGL_HEIGHT, &h);

    DebugLogInfo("CImplAndroidStandAloneWindow::Initialize: GL_VERSION: %s",glGetString(GL_VERSION) );
    DebugLogInfo("CImplAndroidStandAloneWindow::Initialize: GL_VENDOR: %s",glGetString(GL_VENDOR) );
    DebugLogInfo("CImplAndroidStandAloneWindow::Initialize: GL_RENDERER: %s",glGetString(GL_RENDERER) );
    DebugLogInfo("CImplAndroidStandAloneWindow::Initialize: GL_EXTENSIONS: %s",glGetString(GL_EXTENSIONS) );

    // Initialize GL state.
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
}

Bool CImplAndroidStandAloneWindow::Update()
{

    return TRUE;
}
