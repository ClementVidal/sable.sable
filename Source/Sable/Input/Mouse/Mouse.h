#ifndef _SABLE_INPUT_MOUSE_MOUSE_
#define _SABLE_INPUT_MOUSE_MOUSE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\ManagedObject\Header.h>
#include <Sable\Input\Mouse\Interface.h>

#include <Sable\Input\Mouse\Impl\Header.h>

#define MOUSE_Sensitivity 400

namespace Sable
{

/** 
\ingroup InputMouse
Represent the mouse device.
\nUse the "Mouse" macro to access this singleton
*/
class CMouse : public CMouseInterface
{

    DEFINE_MANAGED_CLASS( CMouse );

public:

    /** @name Constructor/Destructor*/
    //@{
    CMouse( CApplicationWindow& window );
    virtual ~CMouse();
    //@}

    /** @name Accessors*/
    //@{
    //@}

    /** @name Manipulator*/
    //@{
    Void				Update();
    //@}

private:

    // Attributes

    CImplMouse	m_Impl;

};

}

#endif


