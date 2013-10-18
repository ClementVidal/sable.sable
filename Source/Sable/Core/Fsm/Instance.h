#ifndef _SABLE_CORE_FSM_INSTANCE_
#define _SABLE_CORE_FSM_INSTANCE_

#include <Sable/Core/Common/DataTypes.h>

namespace Sable
{

class CFsmState;
class CFsmEvent;


/** 
\ingroup Core
Finite state machine
*/
class CFsmInstance
{

public:

	/** @name DataTypes*/
	//@{
	//@}

    /** @name Constructor/Destructor*/
    //@{
	CFsmInstance( Int32 id );
    ~CFsmInstance();
    //@}

    /** @name Operator*/
    //@{
    //@}

    /** @name Accessors*/
    //@{
	Int32	GetStateId() const;
    //@}

	/** @name Manipulator*/
	//@{
	Void	OnEnter( CFsmState& state, CFsmEvent& event );
	Void	OnLeave( CFsmState& state, CFsmEvent& event );
	//@}

	/** @name Signal*/
	//@{
	CEventSignal<CFsmState&, CFsmEvent&>	SignalOnEnter;
	CEventSignal<CFsmState&, CFsmEvent&>	SignalOnLeave;
	//@}

private:

	// Friendship
	friend class CFsm;

    // Methods
	Void SetStateId( Int32 id );

    // Attributes
	Int32	m_Id;

};



}
#endif
