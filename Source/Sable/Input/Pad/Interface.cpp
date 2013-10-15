#include <Sable\Input\Pad\Interface.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CPadInterface );

CPadInterface::CPadInterface()
{
}

CPadInterface::~CPadInterface()
{
}

Void CPadInterface::TriggerEvents( EPadEventType type, EPadEventData data )
{
    m_Signal( type, data );
}

Void CPadInterface::AddObserver( CPadInterface::Observer& m  )
{
    m.Connect( m_Signal );
}

Void CPadInterface::RemoveAllObservers( )
{
	DebugError( "Not yet implemented" );
}

