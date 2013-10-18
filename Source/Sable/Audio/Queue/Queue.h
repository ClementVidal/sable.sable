#ifndef _SABLE_AUDIO_QUEUE_QUEUE_
#define _SABLE_AUDIO_QUEUE_QUEUE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/ManagedObject.h>
#include <Sable/Core/ManagedObject/ObjectMethod.h>
#include <Sable/Core/Collection/Array.h>
#include <Sable/Core/Memory/FreeListHeap.h>
#include <Sable/Audio/Buffer/Buffer.h>

//#define AUDIOBUFFERQUEUE_DEBUG_BUFFER_ORDER

namespace Sable
{

class CAudioSource;
class CAudioWorld;

/** 
\ingroup AudioBuffer
Audio buffer
*/
class CAudioQueue : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CAudioQueue )

public:

    /** @name DataTypes*/
    //@{
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CAudioQueue( CAudioWorld& world, UInt32 bufferCount, UInt32 sampleCount, CAudioBuffer::EFormat fmt, UInt32 freq );
    virtual ~CAudioQueue();
    //@}

    /** @name Accessors*/
    //@{
    Void            UnBind();
    Void            SetReFillCallback( const CObjectMethod& callBack );
    Void            SetPlayEndCallback( const CObjectMethod& callBack );
    //@}

    /** @name Manipulator*/
    //@{
    Void    Update();
    //@}

private:

    // DataTypes
    typedef CMap<UInt32, CRef<CAudioBuffer>> BufferTable;
#ifdef AUDIOBUFFERQUEUE_DEBUG_BUFFER_ORDER
    typedef CMap<UInt32, UInt32> DebugTable;
#endif

    // Friendship
    friend class CAudioSource;

    // Methods
    Void BindToActor( CAudioSource& source );
    Void OnStartPlaying();
    Void OnStopPlaying();
    Void ReFill( CAudioBuffer& buffer );
    Void PlayEnd( CAudioBuffer& buffer );

    // Attributes
    CAudioWorld*                        m_World;
    CAudioSource*                        m_Source;
    BufferTable                         m_InputTable;
#ifdef AUDIOBUFFERQUEUE_DEBUG_BUFFER_ORDER
    DebugTable                          m_DebugTable;
#endif
    CMemoryFreeListHeap                 m_BufferHeap;
    CObjectMethod                       m_ReFillCallback;
    CObjectMethod                       m_PlayEndCallback;
    CAudioBuffer::EFormat               m_Format;
    UInt32                              m_Freq;
};


}

#endif


