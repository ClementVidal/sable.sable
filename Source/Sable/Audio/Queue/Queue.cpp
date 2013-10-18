#include <Sable/Audio/Queue/Queue.h>

#include <Sable/Audio/Common/Header.h>
#include <Sable/Audio/Source/Source.h>

#include <Al.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CAudioQueue )

/**
Create the buffer queue:
\param world The world to which the queue belong
\param bufferCount The number of buffer in the queue
\param sampleCount The number of sample in each buffer
\param fmt The format of each buffer
\param frq The frequency of each buffer
*/
CAudioQueue::CAudioQueue( CAudioWorld& world, UInt32 bufferCount, UInt32 sampleCount, CAudioBuffer::EFormat fmt, UInt32 freq ) :
	m_BufferHeap( "AudioQueue" )
{
    UInt32 i;
    m_World = &world;

    m_BufferHeap.Initialize( NULL, bufferCount + 1, 128, 16 );

    for(i=0;i<bufferCount;i++)
    {
        CAudioBuffer* buffer = NEWOBJ_EX( &m_BufferHeap, CAudioBuffer, ( sampleCount, fmt, freq ) );
        m_InputTable.AddItem( buffer->GetName(), buffer );

#ifdef AUDIOBUFFERQUEUE_DEBUG_BUFFER_ORDER
        m_DebugTable.AddItem( buffer->GetName(), i );
#endif
    }
}

CAudioQueue::~CAudioQueue()
{
    UnBind();
}

Void CAudioQueue::BindToActor( CAudioSource& source )
{
    m_Source = &source;
}

Void CAudioQueue::PlayEnd( CAudioBuffer& buffer )
{
    Void* args[2];

    args[0] = &buffer;
    args[1] = this;

    m_PlayEndCallback.Call( args, 2 );
}

Void CAudioQueue::ReFill( CAudioBuffer& buffer )
{
    Void* args[2];

    args[0] = &buffer;
    args[1] = this;

    m_ReFillCallback.Call( args, 2 );
}

Void CAudioQueue::Update()
{
    ALint  nbQueued;
    ALuint buffer;
    alGetSourcei(m_Source->GetName(), AL_BUFFERS_PROCESSED, &nbQueued);
    for (ALint i = 0; i < nbQueued; ++i)
    {
        alSourceUnqueueBuffers(m_Source->GetName(), 1, &buffer);

        // Call the play end callback
        PlayEnd( * m_InputTable.GetItem( buffer ) );

#ifdef AUDIOBUFFERQUEUE_DEBUG_BUFFER_ORDER
        CoreManager.GetLog().LogError("Queue: %d\n", m_DebugTable.GetItem( buffer ) );
#endif

        // Call the refill callback
        ReFill( * m_InputTable.GetItem( buffer ) );

        alSourceQueueBuffers(m_Source->GetName(), 1, &buffer);

    }
    alSourcei(m_Source->GetName(), AL_BUFFER, 0);

}

Void CAudioQueue::UnBind()
{
    ALint  nbQueued;
    ALuint buffer;

    if( m_InputTable.GetItemCount() == 0 || m_Source->GetName() == 0)
        return;

    alGetSourcei(m_Source->GetName(), AL_BUFFERS_QUEUED, &nbQueued);
 
    for (ALint i = 0; i < nbQueued; ++i)
    {
        alSourceUnqueueBuffers(m_Source->GetName(), 1, &buffer);
    }
    alSourcei(m_Source->GetName(), AL_BUFFER, 0);

    m_InputTable.ClearAllItems();

#ifdef AUDIOBUFFERQUEUE_DEBUG_BUFFER_ORDER
    m_DebugTable.ClearAllItems();
#endif

    m_Source = NULL;
}

Void CAudioQueue::SetReFillCallback( const CObjectMethod& callBack )
{
    m_ReFillCallback = callBack;
}

Void CAudioQueue::SetPlayEndCallback( const CObjectMethod& callBack )
{
    m_PlayEndCallback = callBack;
}

Void CAudioQueue::OnStopPlaying()
{
}

Void CAudioQueue::OnStartPlaying()
{
    BufferTable::Iterator it;

    ForEachItem( it, m_InputTable )
    {
        ReFill( **it );
        UInt32 bufferName = (*it)->GetName();
        alSourceQueueBuffers(m_Source->GetName(), 1, &bufferName );
    }
}