#include <Sable\Core\Fsm\Event.h>

using namespace Sable;

CFsmEvent::CFsmEvent( Int32 id )
{
	m_Id = id;
}

CFsmEvent::~CFsmEvent()
{

}

Int32 CFsmEvent::GetId() const
{
	return m_Id;
}