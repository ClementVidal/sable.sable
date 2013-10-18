#include <Sable/Audio/Common/Manager.h>

#include <Sable/Audio/Common/World.h>
#include <Sable/Core/Debug/Prof.h>

#include <al.h>

using namespace Sable;

CAudioManager::CAudioManager()
{
	m_OALDevice = 0;
}

CAudioManager::~CAudioManager()
{
}

Void CAudioManager::SetWorld( CAudioWorld* world )
{
    m_World = world;
}

Void CAudioManager::Update()
{
	DebugProfile("CAudioManager::Update" );

	if( m_World )
        m_World->Update( );
}

ALCdevice&  CAudioManager::GetDevice() const
{
    return *m_OALDevice;
}

Void CAudioManager::Initialize()
{   
    // Initialization
    m_OALDevice = alcOpenDevice(NULL); // select the "preferred device"
    DebugAssertMsg( m_OALDevice, "CAudioManager::Initialize - Failled to create OpenAL audio device" );

	m_OALContext = alcCreateContext( m_OALDevice,NULL);
	alcMakeContextCurrent(m_OALContext);
	alGetError(); // clear error code
}

Void CAudioManager::UnInitialize()
{
    if( m_World )
	{
		DebugAssert(m_World->GetRefCount() == 1);
		m_World = NULL;
	}

    if( m_OALDevice )
    {
        // Destroy context
        if( m_OALContext )
        {
            alcMakeContextCurrent(NULL);
            alcDestroyContext( m_OALContext );
            m_OALContext = NULL;
        }

        // The close device
        alcCloseDevice( m_OALDevice );
        m_OALDevice = NULL;
    }

}
