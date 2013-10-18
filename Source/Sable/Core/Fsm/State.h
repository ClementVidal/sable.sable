#ifndef _SABLE_CORE_FSM_STATE_
#define _SABLE_CORE_FSM_STATE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Event/Header.h>

namespace Sable
{

/** 
\ingroup Core
Finite state machine
*/
class CFsmState : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CFsmState )

public:

	/** @name DataTypes*/
	//@{
	//@}

    /** @name Constructor/Destructor*/
    //@{
	CFsmState( );
	CFsmState( Int32 id, Int32 transitionCount );
    ~CFsmState();
    //@}

    /** @name Operator*/
	//@{
    //@}

	/** @name Accessors*/
    //@{
	Int32 GetId() const;
	Int32 GetTransitionOutput( Int32 input ) const;
    //@}

    /** @name Manipulator*/
    //@{
	Void	Initialize( Int32 id, Int32 transitionCount );
	Void	AddTransition( Int32 inputId, Int32 outputId );
    //@}

	/** @name Signal*/
	//@{
	//@}

private:

    // Methods
	typedef CPair<Int32, Int32> Transition;

    // Attributes
	Int32					m_Id;
	CArray< Transition >	m_TransitionTable;
};



}
#endif
