#ifndef _SABLE_APPLICATION_IMPL_LINUX_STANDALONEWINDOW_
#define _SABLE_APPLICATION_IMPL_LINUX_STANDALONEWINDOW_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Application/Impl/Stub/Window.h>

namespace Sable
{

/**  
\ingroup Application
*/
class CImplLinuxStandAloneWindow : public CImplStubApplicationWindow
{

public:

    /** @name Constructor/destructor */
    //@{
    CImplLinuxStandAloneWindow();
    ~CImplLinuxStandAloneWindow();
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
    UInt32 m_Handle;

    // Methods

};

}

#endif
