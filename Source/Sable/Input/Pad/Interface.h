#ifndef _SABLE_INPUT_PAD_INTERFACE_
#define _SABLE_INPUT_PAD_INTERFACE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/Header.h>
#include <Sable/Core/Event/Header.h>
#include <Sable/Input/Pad/Event.h>

namespace Sable
{

/** 
\ingroup InputPad
Represent the pad device.
*/
class CPadInterface : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CPadInterface );

public:

	/** @name DataTypes*/
	//@{
    typedef CEventSignal<EPadEventType, EPadEventData> Signal;
    typedef CEventBase<EPadEventType, EPadEventData> Observer;
	//@}

	/** @name Constructor/Destructor*/
	//@{
	CPadInterface();
	virtual ~CPadInterface();
	//@}

	/** @name Accessors*/
	//@{
    //@}

	/** @name Manipulator*/
	//@{
	virtual Void		Update() = 0;
	virtual CVector2f	GetAnalogStick( UInt32 id ) const = 0;
	virtual Float32		GetAnalogButton( UInt32 id ) const = 0;
	virtual Bool		GetButton( UInt32 id ) const = 0;
	virtual Bool		IsAvailable() const = 0;

	Void				AddObserver( Observer& m );
	Void				RemoveAllObservers( );	
	//@}

	/** @name System*/
	//@{
	Void				TriggerEvents( EPadEventType axis, EPadEventData data );
	//@}

protected:

	// Attributes
    Signal                      m_Signal;

};

}

#endif


