#include <Sable/Audio/Common/World.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CAudioWorld );

CAudioWorld::CAudioWorld( )
{
    // Create world listener
    m_Listener = NEWOBJ( CAudioListener, ( *this ) );
}

CAudioWorld::~CAudioWorld()
{
}

CAudioListener& CAudioWorld::GetListener()
{
    return *m_Listener;
}

Void CAudioWorld::Update( )
{
}
