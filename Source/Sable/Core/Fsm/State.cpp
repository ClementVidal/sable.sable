#include <Sable\Core\Fsm\State.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CFsmState )

CFsmState::CFsmState( )
{
	m_Id = -1;
}

CFsmState::CFsmState( Int32 id, Int32 transitionCount )
{
	Initialize( id, transitionCount );
}

CFsmState::~CFsmState()
{

}

Void CFsmState::Initialize( Int32 id, Int32 transitionCount )
{
	m_Id = id;
	m_TransitionTable.SetItemCount( transitionCount );
	for( Int32 i=0;i<transitionCount;i++ )
	{
		m_TransitionTable[i] = CPair<Int32, Int32>( -1, -1 );
	}
}

Void CFsmState::AddTransition( Int32 inputTransitionId, Int32 outputStateId )
{
	UInt32 i;
	for( i=0;i<m_TransitionTable.GetItemCount(); i++ )
	{
		if( m_TransitionTable[i].GetFirst() == -1 )
			break;
	}

	DebugAssert( i <m_TransitionTable.GetItemCount() );

	m_TransitionTable[i].SetFirst( inputTransitionId );
	m_TransitionTable[i].SetSecond( outputStateId );
}


Int32 CFsmState::GetTransitionOutput( Int32 inputTransitionId ) const
{
	for( UInt32 i=0;i<m_TransitionTable.GetItemCount(); i++ )
	{
		if( m_TransitionTable[i].GetFirst() == -1 )
			break;

		if( m_TransitionTable[i].GetFirst() == inputTransitionId )
			return m_TransitionTable[i].GetSecond();

	}

	return -1;
}

Int32 CFsmState::GetId() const
{
	return m_Id;
}
