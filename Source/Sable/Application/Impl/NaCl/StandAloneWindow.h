#ifndef _SABLE_APPLICATION_IMPL_NACL_STANDALONEWINDOW_
#define _SABLE_APPLICATION_IMPL_NACL_STANDALONEWINDOW_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Application/Impl/Stub/Window.h>
/*
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#undef Bool
*/
/*
#include <EGL/egl.h>
#include <GLES2/gl2.h>
*/

namespace Sable
{

/**  
\ingroup Application
*/
class CImplNaClStandAloneWindow : public CImplStubApplicationWindow
{

public:

    /** @name Constructor/destructor */
    //@{
    CImplNaClStandAloneWindow();
    ~CImplNaClStandAloneWindow();
    //@}

    /** @name Manipulator*/
    //@{
    Void Initialize( const CTextureInfo& info );
    Bool Update();
    //@}

    /** @name Accessors*/
    //@{
    UInt32    GetHandle() const;
    //@}

private:

    // Attribute
   /* Display* m_X11Display;
    Window   m_X11Window;
    XEvent   m_X11Event;

    EGLDisplay  m_EGLDisplay;
    EGLSurface	m_EGLSurface;
*/
    // Methods

};

}

#endif
