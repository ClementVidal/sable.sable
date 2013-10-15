#ifndef _SABLE_CORE_FSM_FSM_
#define _SABLE_CORE_FSM_FSM_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CFsmState;
class CFsmTransition;
class CFsmInstance;
class CFsmEvent;

/** 
\ingroup Core
Finite state machine
*/
class CFsm : public CManagedObject
{

public:

	/** @name DataTypes*/
	//@{
	//@}

    /** @name Constructor/Destructor*/
    //@{
	CFsm( UInt32 maxStateCount );
    ~CFsm();
    //@}

    /** @name Accessors*/
    //@{
	CFsmState*		GetState( Int32 id );
    //@}

    /** @name Manipulator*/
    //@{
	Bool	SendEvent( CFsmInstance& instance, CFsmEvent& event );

	Void	AddState( CFsmState& state );
    //@}

private:

    // Methods
	typedef CHashTable< Int32, CRef<CFsmState> >	StateTable;

	// Attributes
	StateTable	m_StateTable;

};



}
#endif
