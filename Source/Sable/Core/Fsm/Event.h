#ifndef _SABLE_CORE_FSM_EVENT_
#define _SABLE_CORE_FSM_EVENT_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

/** 
\ingroup Core
Finite state machine
*/
class CFsmEvent
{

public:

	/** @name DataTypes*/
	//@{
	//@}

    /** @name Constructor/Destructor*/
    //@{
	CFsmEvent( Int32 id );
    ~CFsmEvent();
    //@}

    /** @name Operator*/
    //@{
    //@}

    /** @name Accessors*/
    //@{
	Int32	GetId() const;
    //@}

    /** @name Manipulator*/
    //@{
    //@}

private:

    // Methods

    // Attributes
	Int32	m_Id;

};



}
#endif
