#ifndef _SABLE_APPLICATION_IMPL_MSW_APPLICATION_
#define _SABLE_APPLICATION_IMPL_MSW_APPLICATION_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Application/Impl/Stub/Application.h>

#include <Windows.h>

struct ID3D10Device;
struct IDXGISwapChain;

namespace Sable
{

class CApplication;

/**  
\ingroup Application
*/
class CImplMswApplication : public CImplStubApplication
{

public:

    /** @name Constructor/destructor */
    //@{
    CImplMswApplication();
    ~CImplMswApplication();
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
