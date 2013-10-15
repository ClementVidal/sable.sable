#ifndef _SABLE_INPUT_COMMON_MANAGER_
#define _SABLE_INPUT_COMMON_MANAGER_

#include <Sable\Core\Common\Header.h>
#include <Sable\Core\ManagedObject\Header.h>
#include <Sable\Input\Common\Impl\Header.h>

#define		InputManager  Sable::CInputManager::GetInstance()

namespace Sable
{

class CPadInterface;
class CMouseInterface;
class CKeyboardInterface;
class CApplicationInterface;

/** 
\ingroup Input
Global manager for all input operation
*/
class CInputManager : public CSingleton<CInputManager>
{

public:

    /** @name DataTypes*/
    //@{
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CInputManager();
    virtual ~CInputManager();
    //@}

    /** @name Accessors*/
    //@{
    CImplInputManager&   GetImpl();
    CMouseInterface*     GetMouse();
    CKeyboardInterface*  GetKeyboard();
    CPadInterface*       GetPad();

    Void SetMouse( CMouseInterface* mouse );
    Void SetKeyboard( CKeyboardInterface* kbd );
    Void SetPad( CPadInterface* pad );
    //@}

    /** @name Manipulator*/
    //@{
    Void Update();
    Void Initialize( );
    Void UnInitialize();
    //@}

private:

    // Attributes
    CRef<CKeyboardInterface>    m_Keyboard;
    CRef<CMouseInterface>       m_Mouse;
    CRef<CPadInterface>       m_Pad;


    CImplInputManager					m_Wrapper;

};

Inline
CImplInputManager& CInputManager::GetImpl()
{
    return m_Wrapper;
}

Inline
CMouseInterface* CInputManager::GetMouse()
{
    return m_Mouse;
}

Inline
CKeyboardInterface* CInputManager::GetKeyboard()
{
    return m_Keyboard;
}

Inline
CPadInterface* CInputManager::GetPad()
{
    return m_Pad;
}

}

#endif


