#ifndef _SABLE_APPLICATION_IMPL_MSW_STANDALONEWINDOW_
#define _SABLE_APPLICATION_IMPL_MSW_STANDALONEWINDOW_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Application/Impl/Stub/Window.h>

namespace Sable
{

/**  
\ingroup Application
*/
class CImplMswStandAloneWindow : public CImplStubApplicationWindow
{

public:

    /** @name Constructor/destructor */
    //@{
    CImplMswStandAloneWindow();
    ~CImplMswStandAloneWindow();
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
