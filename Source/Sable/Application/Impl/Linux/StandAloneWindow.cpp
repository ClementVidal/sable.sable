#include <Sable/Application/Impl/Linux/StandAloneWindow.h>

using namespace Sable;

CImplLinuxStandAloneWindow::CImplLinuxStandAloneWindow() :
	m_X11Display( NULL )
{
}

CImplLinuxStandAloneWindow::~CImplLinuxStandAloneWindow()
{
}


Bool CImplLinuxStandAloneWindow::Update()
{
    XNextEvent( m_X11Display, &m_X11Event );

    switch( m_X11Event.type)
    {
    case ConfigureNotify:
        
        break;
    case ButtonPress:
        XCloseDisplay(m_X11Display);
        return FALSE;
    }
    return TRUE;
}

UInt32 CImplLinuxStandAloneWindow::GetHandle() const
{
    return (UInt32) m_X11Window;
}


Void CImplLinuxStandAloneWindow::Initialize( const CTextureInfo& info )
{

    static const EGLint attribs[] = {
        EGL_RED_SIZE, 1,
        EGL_GREEN_SIZE, 1,
        EGL_BLUE_SIZE, 1,
        EGL_DEPTH_SIZE, 1,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_NONE
     };
     static const EGLint ctx_attribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
     };
     int scrnum;
     XSetWindowAttributes attr;
     unsigned long mask;
     Window root;
     XVisualInfo *visInfo, visTemplate;
     int num_visuals;
     EGLContext ctx;
     EGLConfig config;
     EGLint num_configs;
     EGLint vid;
     EGLint egl_major, egl_minor;

     m_X11Display = XOpenDisplay(NULL);
     m_EGLDisplay = eglGetDisplay(m_X11Display);

     scrnum = DefaultScreen( m_X11Display );
     root = RootWindow( m_X11Display, scrnum );

     if (!eglInitialize( m_EGLDisplay, &egl_major, &egl_minor))
     {
          printf("Error: eglInitialize() failed\n");
          return;
     }


     if (!eglChooseConfig( m_EGLDisplay, attribs, &config, 1, &num_configs))
     {
    	 EGLint err = eglGetError();
         DebugError("Failled to set current EGL context");
         return;
     }

     DebugAssert(config);
     DebugAssert(num_configs > 0);

     if (!eglGetConfigAttrib(m_EGLDisplay, config, EGL_NATIVE_VISUAL_ID, &vid))
     {
         DebugError("Failled to set current EGL context");
         return;
     }

     /* The X m_X11Windowdow visual must match the EGL config */
     visTemplate.visualid = vid;
     visInfo = XGetVisualInfo(m_X11Display, VisualIDMask, &visTemplate, &num_visuals);
     if (!visInfo)
     {
         DebugError("Failled to set current EGL context");
         return;
     }

     /* m_X11Windowdow attributes */
     attr.background_pixel = 0;
     attr.border_pixel = 0;
     attr.colormap = XCreateColormap( m_X11Display, root, visInfo->visual, AllocNone);
     attr.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask;
     mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

     m_X11Window = XCreateWindow( m_X11Display, root, 0, 0, info.Width, info.Height,
                  0, visInfo->depth, InputOutput,
                  visInfo->visual, mask, &attr );

     /* set hints and properties */
     {
        XSizeHints sizehints;
        sizehints.x = 0;
        sizehints.y = 0;
        sizehints.width  = info.Width;
        sizehints.height = info.Height;
        sizehints.flags = USSize | USPosition;
        XSetNormalHints(m_X11Display, m_X11Window, &sizehints);
        XSetStandardProperties(m_X11Display, m_X11Window, "Test", "Test",None, (char **)NULL, 0, &sizehints);
     }

  #if USE_FULL_GL /* XXX fix this when eglBindAPI() works */
     eglBindAPI(EGL_OPENGL_API);
  #else
     eglBindAPI(EGL_OPENGL_ES_API);
  #endif

     ctx = eglCreateContext(m_EGLDisplay, config, EGL_NO_CONTEXT, ctx_attribs );
     if (!ctx)
     {
         DebugError("Failled to set current EGL context");
         return;
     }

     /* test eglQueryContext() */
     {
        EGLint val;
        eglQueryContext(m_EGLDisplay, ctx, EGL_CONTEXT_CLIENT_VERSION, &val);
        DebugAssert(val == 2);
     }

     m_EGLSurface = eglCreateWindowSurface(m_EGLDisplay, config, m_X11Window, NULL);
     if (!m_EGLSurface)
     {
    	 DebugError("Error: eglCreatem_X11WindowdowSurface failed\n");
    	 return;
     }

     /* sanity checks */
     {
        EGLint val;
        eglQuerySurface(m_EGLDisplay, m_EGLSurface, EGL_WIDTH, &val);
        DebugAssert(val == info.Width);
        eglQuerySurface(m_EGLDisplay, m_EGLSurface, EGL_HEIGHT, &val);
        DebugAssert(val == info.Height);

     }

     XFree(visInfo);


	return;

}
