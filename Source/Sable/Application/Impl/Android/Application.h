#ifndef _SABLE_APPLICATION_IMPL_ANDROID_APPLICATION_
#define _SABLE_APPLICATION_IMPL_ANDROID_APPLICATION_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Application\Impl\Stub\Application.h>


namespace Sable
{

class CApplication;

/**  
\ingroup Application
*/
class CImplAndroidApplication : public CImplStubApplication
{

public:

    /** @name Constructor/destructor */
    //@{
    CImplAndroidApplication();
    ~CImplAndroidApplication();
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
