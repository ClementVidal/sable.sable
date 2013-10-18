#include <Sable/Audio/Common/Listener.h>

#include <Sable/Audio/Common/World.h>

#include <al.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CAudioListener )

CAudioListener::CAudioListener( CAudioWorld& world ) 
{
    m_World = &world;
}

CAudioListener::~CAudioListener()
{
}

Void CAudioListener::SetWorldPosition( const CVector3f& p )
{
    ALfloat pos[3];
    pos[0] = p.GetX();
    pos[1] = p.GetY();
    pos[2] = p.GetZ();

    alListenerfv( AL_POSITION, pos);
}

Void CAudioListener::SetWorldVelocity( const CVector3f& p )
{
    ALfloat pos[3];
    pos[0] = p.GetX();
    pos[1] = p.GetY();
    pos[2] = p.GetZ();

    alListenerfv( AL_VELOCITY, pos);
}

Void CAudioListener::SetWorldOrientation( const CVector3f& p )
{
    ALfloat pos[3];
    pos[0] = p.GetX();
    pos[1] = p.GetY();
    pos[2] = p.GetZ();

    alListenerfv( AL_ORIENTATION, pos);
}
