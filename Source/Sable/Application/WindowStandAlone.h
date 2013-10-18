#ifndef _SABLE_APPLICATION_WINDOWSTANDALONE_
#define _SABLE_APPLICATION_WINDOWSTANDALONE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Application/Window.h>

#include <Sable/Application/Impl/Header.h>

namespace Sable
{

/**  
\ingroup Application
*/
class CApplicationWindowStandAlone : public CApplicationWindow
{

public:

    /** @name Constructor/destructor */
    //@{
    CApplicationWindowStandAlone();
    ~CApplicationWindowStandAlone();
    //@}

    /** @name Manipulator*/
    //@{
    Bool Update();
    Bool Initialize( const CSwapChainInfo& swapChainDesc );
    //@}

    /** @name Accessors*/
    //@{
    UInt32    GetHandle() const;
    //@}

private:

    // Attribute

    // Methods
    CImplStandAloneWindow  m_Impl;

};

}

#endif
