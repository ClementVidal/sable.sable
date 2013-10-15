#ifndef _SABLE_APPLICATION_IMPL_STUB_APPLICATION_
#define _SABLE_APPLICATION_IMPL_STUB_APPLICATION_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CApplication;

/**
\ingroup Application
*/
class CImplStubApplication
{

public:

    /** @name Constructor/destructor */
    //@{
    CImplStubApplication( ) {}
    virtual ~CImplStubApplication(){}
    //@}


    /** @name Manipulator*/
    //@{
    virtual Void Initialize( CApplication& app ) {};
	virtual Void GetFormattedInformation( Char* str, UInt32 s )const { str = NULL; }
    //@}

    /** @name Accessors*/
    //@{
    //@}

protected:

    // Method

    // Attribute

};

}

#endif
