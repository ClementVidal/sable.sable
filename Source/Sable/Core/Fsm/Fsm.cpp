#include <Sable/Core/Fsm/Fsm.h>

#include <Sable/Core/Fsm/State.h>
#include <Sable/Core/Fsm/Event.h>
#include <Sable/Core/Fsm/Instance.h>

using namespace Sable;

CFsm::CFsm( UInt32 maxStateCount )
{
	m_StateTable.SetCapacity( maxStateCount );
}

CFsm::~CFsm()
{

}

CFsmState* CFsm::GetState( Int32 id )
{
	if( m_StateTable.HasItem( id ) )
		return m_StateTable.GetItem( id );

	return NULL;
}

Bool CFsm::SendEvent( CFsmInstance& instance, CFsmEvent& event )
{
	CFsmState* currentState = GetState( instance.GetStateId() );
	DebugAssert( currentState );
	Int32 outputState = currentState->GetTransitionOutput( event.GetId() );
	if( outputState != -1 && outputState != instance.GetStateId() )
	{
		instance.OnLeave( *currentState, event );
		instance.SetStateId( outputState );
		currentState = GetState( outputState );
		DebugAssert( currentState );
		instance.OnEnter( *currentState, event );
		return TRUE;
	}

	return FALSE;
}

Void CFsm::AddState( CFsmState& state )
{
	if( m_StateTable.HasItem( state.GetId() ) )
		return;

	m_StateTable.AddItem( state.GetId(), &state );
}
