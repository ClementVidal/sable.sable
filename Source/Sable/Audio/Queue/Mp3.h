#ifndef _SABLE_AUDIO_BUFFER_DECODERMP3_
#define _SABLE_AUDIO_BUFFER_DECODERMP3_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/File/File.h>
#include <Sable/Core/Collection/Array.h>
#include <Sable/Core/ManagedObject/ManagedObject.h>
#include <Sable/Audio/Queue/Queue.h>

#include <mad.h> 


namespace Sable
{

class CAudioWorld;

/** 
\ingroup AudioBuffer
Audio buffer
*/
class CAudioQueueMp3 : public CAudioQueue
{

    DEFINE_MANAGED_CLASS( CAudioQueueMp3 )

public:

    /** @name DataTypes*/
    //@{
    struct SFrame
    {
        Void*                   Buffer;
        UInt32                  Size;
        CAudioBuffer::EFormat   Format;
        Float32                 Duration;
    };

    enum EReturn
    {
        nReturn_Error,
        nReturn_MoreInput,
        nReturn_Flush,
        nReturn_Eof,
        nReturn_CallAgain,
    };
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CAudioQueueMp3( CAudioWorld& world );
    virtual ~CAudioQueueMp3();
    //@}

    /** @name Accessors*/
    //@{
    Void SetOnFlushSynthetizedDataCB( const CObjectMethod& m );
    //@}

    /** @name Manipulator*/
    //@{
    Void        Initialize( );
    //@}

private:

    // Methods
    EReturn     Read( );
    Int16       ScalePCMSample( mad_fixed_t sample, mad_fixed_t *rndval_ptr );
    UInt32      GetRandomNumber( UInt32  state);
    Int32       ReFill( Void** args, UInt16 count );
    Void        FlushSynthetizedData( CAudioBuffer& buffer );

    // Attributes
    CFile           m_File;

    mad_stream 	    m_MADStream;
    mad_frame 	    m_MADFrame;
    mad_synth 	    m_MADSynth;
    mad_timer_t 	m_MADTimer;
    UInt32          m_MADFrameCounter;
    CArray<Byte>    m_OutputBuffer;
    CArray<Byte>    m_InputBuffer;
    Byte*           m_OutputBufferPtr;

    CObjectMethod   m_OnFlushSynthetizedDataCB;
    UInt32      m_WriteSize;
    Bool        m_IsEof;
    UInt32      m_ReadSize;
    UInt32      m_Remaining;

    Byte*       m_BufferStart;		
};


}

#endif


