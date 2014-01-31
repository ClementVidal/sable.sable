#ifndef _SABLE_APPLICATION_IMPL_LINUX_APPLICATION_
#define _SABLE_APPLICATION_IMPL_LINUX_APPLICATION_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Application/Impl/Stub/Application.h>

namespace Sable
{

class CApplication;

/**  
\ingroup Application
*/
class CImplLinuxApplication : public CImplStubApplication
{

public:

    /** @name Constructor/destructor */
    //@{
    CImplLinuxApplication();
    ~CImplLinuxApplication();
    //@}

    /** @name Manipulator*/
    //@{
    Void Initialize( CApplication& app );
    //@}

    /** @name Accessors*/
    //@{
    //@}

private:

    // Attribute

    // Methods


};

}

#endif
