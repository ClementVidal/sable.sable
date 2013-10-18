#ifndef _SABLE_APPLICATION_IMPL_ANDROID_STANDALONEWINDOW_
#define _SABLE_APPLICATION_IMPL_ANDROID_STANDALONEWINDOW_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Application/Impl/Stub/Window.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

namespace Sable
{

/**  
\ingroup Application
*/
class CImplAndroidStandAloneWindow : public CImplStubApplicationWindow
{

public:

    /** @name Constructor/destructor */
    //@{
    CImplAndroidStandAloneWindow();
    ~CImplAndroidStandAloneWindow();
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
    UInt32      m_Handle;
    EGLDisplay  m_Display;
    
    // Methods

};

}

#endif
