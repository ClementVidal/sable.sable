#include <Sable/Core/Fsm/Instance.h>

using namespace Sable;

CFsmInstance::CFsmInstance( Int32 id )
{
	m_Id = id;
}

CFsmInstance::~CFsmInstance()
{

}

Int32 CFsmInstance::GetStateId() const
{
	return m_Id;
}

Void CFsmInstance::SetStateId( Int32 id )
{
	m_Id = id;
}

Void CFsmInstance::OnEnter( CFsmState& state, CFsmEvent& event )
{
	SignalOnEnter( state, event );
}

Void CFsmInstance::OnLeave( CFsmState& state, CFsmEvent& event )
{
	SignalOnLeave( state, event );
}