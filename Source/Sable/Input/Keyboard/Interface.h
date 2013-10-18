#ifndef _SABLE_INPUT_KEYBOARD_INTERFACE_
#define _SABLE_INPUT_KEYBOARD_INTERFACE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Collection/Map.h>
#include <Sable/Input/Keyboard/Event.h>
#include <Sable/Core/ManagedObject/Header.h>
#include <Sable/Core/Collection/Array.h>

#include <Sable/Input/Mouse/Impl/Header.h>
#include <Sable/Core/Event/Header.h>

namespace Sable
{

class CApplicationWindow;

/** 
\ingroup InputKeyboard
*/
class CKeyboardInterface : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CKeyboardInterface );

public:

    /** @name DataTypes*/
    //@{
    typedef CEventSignal<EKeyboardEventType, EKeyboardEventData> Signal;
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CKeyboardInterface( CApplicationWindow& window );
    ~CKeyboardInterface();
    //@}

    /** @name Operator*/
    //@{
    //@}

    /** @name Accessors*/
    //@{
    CApplicationWindow& GetAttachedWindow() const;
    virtual Bool	GetIsKeyDown( const EKeyboardEventData key ) const = 0;
    //@}

    /** @name Manipulator*/
    //@{
    virtual Void        Update() = 0;
    Char                KeyboardEventToAscii( EKeyboardEventData key );
    //@}

    /** @name Signals*/
    //@{
    Signal          SignalEvent;
    //@}

private:

    // Attributes
    CApplicationWindow* m_AttachedWindow;
};


}

#endif


