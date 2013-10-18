#ifndef _SABLE_APPLICATION_IMPL_STUB_WINDOW_
#define _SABLE_APPLICATION_IMPL_STUB_WINDOW_

#include <Sable/Core/Common/DataTypes.h>

namespace Sable
{

class CTextureInfo;

/**  
\ingroup Application
*/
class CImplStubApplicationWindow
{

public:

    /** @name Constructor/destructor */
    //@{
    CImplStubApplicationWindow() {};
    virtual ~CImplStubApplicationWindow() {};
    //@}

    /** @name Manipulator*/
    //@{
    virtual Void Initialize( const CTextureInfo& info ) {};
    virtual Bool Update() {return TRUE;}
    //@}

    /** @name Accessors*/
    //@{
    virtual UInt32    GetHandle() const { return 0; }
    //@}

private:

    // Attribute

    // Methods

};

}

#endif
