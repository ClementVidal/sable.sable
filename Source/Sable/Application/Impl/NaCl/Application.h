#ifndef _SABLE_APPLICATION_IMPL_NACL_APPLICATION_
#define _SABLE_APPLICATION_IMPL_NACL_APPLICATION_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Application/Impl/Stub/Application.h>

namespace Sable
{

class CApplication;

/**  
\ingroup Application
*/
class CImplNaClApplication : public CImplStubApplication
{

public:

    /** @name Constructor/destructor */
    //@{
    CImplNaClApplication();
    ~CImplNaClApplication();
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
