#include <Sable/Audio/Source/Source.h>

#include <Sable/Audio/Common/World.h>
#include <Sable/Audio/Buffer/Buffer.h>
#include <Sable/Audio/Queue/Queue.h>

#include <al.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CAudioSource )

CAudioSource::CAudioSource( CAudioWorld& world ) 
{
    m_World = &world;
    alGenSources(1,&m_OALName);
    DebugAssert( alGetError() == AL_NO_ERROR );
}

CAudioSource::~CAudioSource()
{
    // Queue must be unbinded BEFORE source is deleted
    if( m_Queue )
        m_Queue->UnBind();

    alDeleteSources( 1, &m_OALName );
    m_OALName = 0;
}

UInt32  CAudioSource::GetName() const
{
    return m_OALName;
}

Void CAudioSource::SetWorldPosition( const CVector3f& p )
{
    ALfloat pos[3];
    pos[0] = p.GetX();
    pos[1] = p.GetY();
    pos[2] = p.GetZ();

    alSourcefv( m_OALName, AL_POSITION, pos);
}

Void CAudioSource::SetWorldVelocity( const CVector3f& p )
{
    ALfloat pos[3];
    pos[0] = p.GetX();
    pos[1] = p.GetY();
    pos[2] = p.GetZ();

    alSourcefv( m_OALName, AL_VELOCITY, pos);
}

Void CAudioSource::SetPitch( Float32 p )
{
    alSourcef( m_OALName, AL_PITCH, p);
}

Void CAudioSource::SetGain( Float32 g )
{
    alSourcef( m_OALName, AL_GAIN, g);
}

Void CAudioSource::SetIsLooping( Bool onOff )
{
    alSourcei( m_OALName, AL_LOOPING, onOff );
}

Void CAudioSource::Play( Bool onOff )
{
    if( onOff )
    {
        if( m_Queue )
            m_Queue->OnStartPlaying();

        m_State.SetBit( nState_Playing, TRUE );
        alSourcePlay( m_OALName );
    }
    else
    {
        m_State.SetBit( nState_Playing, FALSE );
        alSourceStop( m_OALName );
        if( m_Queue )
            m_Queue->OnStopPlaying();
    }
}

Void CAudioSource::Pause( Bool onOff )
{
    if( !m_State.GetBit( nState_Playing ) )
        return;

    if( onOff )
    {
        m_State.SetBit( nState_Pause, TRUE );
        alSourcePause( m_OALName );
    }
    else
    {
        m_State.SetBit( nState_Pause, FALSE );
        alSourcePlay( m_OALName );
    }
}

Void CAudioSource::SetBuffer( CAudioBuffer& buffer )
{
    m_Buffer = &buffer;
    alSourcei( m_OALName, AL_BUFFER, buffer.GetName() );
    DebugAssert( alGetError() == AL_NO_ERROR );
}

Void CAudioSource::SetQueue( CAudioQueue& queue )
{
    m_Queue = &queue;
    queue.BindToActor( *this );
    //alSourcei( m_OALName, AL_BUFFER, buffer.GetName() );
    //DebugAssert( alGetError() == AL_NO_ERROR );
}

Bool CAudioSource::IsPlaying() const
{
    return m_State.GetBit( nState_Playing ) && !m_State.GetBit( nState_Pause );
}

Void CAudioSource::Update()
{
    if( m_Queue && IsPlaying() )
        m_Queue->Update();
}