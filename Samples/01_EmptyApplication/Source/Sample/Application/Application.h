#ifndef _SAMPLE_APPLICATION_APPLICATION_
#define _SAMPLE_APPLICATION_APPLICATION_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/Ref.h>
#include <Sable/Application/StandAlone.h>
#include <Sable/Core/Event/Header.h>
#include <Sable/Input/Keyboard/Event.h>
#include <Sable/Input/Common/CameraController.h>

using namespace Sable;

namespace Sample
{

class CViewBase;

class CApplication : public CApplicationStandAlone
{

public:

	/** @name Constructor/Destructor*/
    //@{
	CApplication();
	virtual ~CApplication();
	//@}

	/** @name Operator*/
    //@{
    //@}

	/** @name Accessors*/
    //@{
    //@}

    /** @name Manipulator*/
    //@{
    Void        Run();
    Bool        Update();
    Void        Render();
    Void        Initialize();
    //@}

private:

	//Methods
    Void OnKeyboardEvent( EKeyboardEventType type, EKeyboardEventData data );

    //Attributes
    CCameraController   m_CameraController;
    CEventSlot<CApplication, EKeyboardEventType, EKeyboardEventData> m_SlotKeyboardEvent;
};

}

#endif
