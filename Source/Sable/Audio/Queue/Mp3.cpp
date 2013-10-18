#include <Sable/Audio/Queue/Mp3.h>

#include <Sable/Audio/Common/Helper.h>
#include <Sable/Audio/Common/World.h>
#include <Sable/Core/Log/Header.h>
#include <Sable/Core/File/Header.h>
#include <Sable/Core/Common/Manager.h>

#define INPUT_BUFFER_SIZE	(5*1152*4)
#define OUTPUT_BUFFER_SIZE	 (1152*4) 

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CAudioQueueMp3, CAudioQueue )

CAudioQueueMp3::CAudioQueueMp3( CAudioWorld& world ) :
CAudioQueue( world, 128, 1152, CAudioBuffer::nFormat_Stereo16, 44100 )
{
    SetReFillCallback( CObjectMethod( *this, (CObjectMethod::MethodPtr)&CAudioQueueMp3::ReFill ) );
    Initialize();
}

CAudioQueueMp3::~CAudioQueueMp3()
{
}

Int32 CAudioQueueMp3::ReFill( Void** args, UInt16 count )
{
    CAudioBuffer& buffer = *(CAudioBuffer*)args[0];

    EReturn mxsig = nReturn_CallAgain;

    do
    {
        mxsig = Read(  );
        if ( mxsig == nReturn_Error )			// Error
        {
            return 0;
        }
        else if (mxsig == nReturn_MoreInput)		// Fill buffer
        {
            if (m_BufferStart)			// Fill partial buffer
                m_File.Read(m_BufferStart, m_ReadSize );
            else							// Read full buffer
                m_File.Read(m_InputBuffer.GetBuffer(), m_ReadSize );

            if ( m_File.GetIsEndOfFile() )		// EOF must be flagged
            {
                m_IsEof = 1;
                //m_ReadSize = a;					
            }
        }
    }
    while ( mxsig != nReturn_Flush && mxsig != nReturn_Eof );

    
    if (mxsig == nReturn_Flush) 	// Output to file
    {
        FlushSynthetizedData( buffer );
    }
    else if (mxsig == nReturn_Eof) 		// Input file EOF
    {
        int a = 0;
        return 0;	
        
    }

    return 0;
}

Void CAudioQueueMp3::FlushSynthetizedData( CAudioBuffer& buffer )
{
    SFrame frame;
    Float32 duration = m_MADFrame.header.duration.seconds + (Float32) m_MADFrame.header.duration.fraction / (Float32) MAD_TIMER_RESOLUTION;

    Int32 a = 0;
    CAudioBuffer::EFormat format = CAudioBuffer::nFormat_Mono16;
    if( m_MADSynth.pcm.channels == 2 )
        format = CAudioBuffer::nFormat_Stereo16;

    DebugAssert( m_WriteSize == buffer.GetByteCount() );
    DebugAssert( m_MADSynth.pcm.samplerate == buffer.GetFreq() );


    buffer.SetPCMData( m_OutputBuffer.GetBuffer() );


    frame.Buffer = m_OutputBuffer.GetBuffer();
    frame.Size = m_WriteSize;
    frame.Format = format;
    frame.Duration = duration;

    Void* args[1];
    args[0] = (Void*)&frame;

    m_OnFlushSynthetizedDataCB.Call( args, 1 );

}

Void CAudioQueueMp3::SetOnFlushSynthetizedDataCB( const CObjectMethod& m )
{
    m_OnFlushSynthetizedDataCB = m;
}

Void CAudioQueueMp3::Initialize()
{
    // Initialize libmad structures 
    mad_stream_init(&m_MADStream);
    mad_frame_init(&m_MADFrame);
    mad_synth_init(&m_MADSynth);
    mad_timer_reset(&m_MADTimer);	

    m_OutputBuffer.SetItemCount( OUTPUT_BUFFER_SIZE );
    m_InputBuffer.SetItemCount( INPUT_BUFFER_SIZE );

    m_OutputBufferPtr = m_OutputBuffer.GetBuffer();

    m_MADFrameCounter = 0;

    CFilePath filePath = CoreManager.GetFileSystem().GetFilePath( "Root", "test.mp3" );
    m_File.Open( filePath, nAccesMode_Read );

    m_IsEof = FALSE;
    m_ReadSize = 0;
    m_Remaining = 0;
    m_BufferStart = NULL;
}

Int16 CAudioQueueMp3::ScalePCMSample( mad_fixed_t sample, mad_fixed_t *rndval_ptr )
{
	unsigned int scalebits;
	mad_fixed_t output, mask, rnd;

	// bias 
	output = sample + (1L << (MAD_F_FRACBITS + 1 - 16 - 1));	
	
  	scalebits = MAD_F_FRACBITS + 1 - 16;
  	mask = (1L << scalebits) - 1;

  	// dither 
	rnd = GetRandomNumber(*rndval_ptr);
  	output += (rnd & mask) - (*rndval_ptr & mask);
	*rndval_ptr = rnd;
	
  	// clip 
	if (output >= MAD_F_ONE)
    	output = MAD_F_ONE - 1;
	else if (output < -MAD_F_ONE)
    	output = -MAD_F_ONE;

  	// quantize 
  	output &= ~mask;

	// scale 
	return output >> scalebits;
}

UInt32 CAudioQueueMp3::GetRandomNumber( UInt32  state)
{
    return (state * 0x0019660dL + 0x3c6ef35fL) & 0xffffffffL;
}


CAudioQueueMp3::EReturn CAudioQueueMp3::Read( )
{
    // "Random" seed for generating dither. Used 
    // by scale_audio() in preparing the samples 
    // for 16 bit output. 
    mad_fixed_t 	rnscale = 0xa8b9ff7e;

    Byte* guardPtr = NULL;
    Byte* readStart;

    // Input file has been read completely
    if ( m_IsEof && !m_ReadSize )
    {
        CoreManager.GetLog().LogError( "CAudioQueueMp3::Read - End of input m_MADStream"); 
        return nReturn_Eof; 
    }	
    // Executes on initial loop
    if ( (m_ReadSize == 0) && (m_Remaining == 0) && ( m_MADStream.buffer == NULL ) )
    {
        m_ReadSize = INPUT_BUFFER_SIZE;
        m_Remaining = 0;
        return nReturn_MoreInput;
    }

    readStart = m_InputBuffer.GetBuffer();

    // Stream buffer
    if ( m_MADStream.buffer == NULL || m_MADStream.error == MAD_ERROR_BUFLEN )
    {
        // BUFFER_GUARD
        // "m_IsEof" must be set to
        // non-zero IMMEDIATELY (see "test.cpp")
        // once it is detected, so the following
        // may execute, padding the buffer.
        if( m_IsEof )
        {
            guardPtr = m_InputBuffer.GetBuffer() + m_ReadSize;
            MemoryFill( guardPtr, 0, MAD_BUFFER_GUARD );
        
            m_ReadSize += MAD_BUFFER_GUARD;
        }

        // Pipe the NEW buffer content to libmad's 
        // m_MADStream decoder facility.
        mad_stream_buffer( &m_MADStream, m_InputBuffer.GetBuffer(), m_ReadSize + m_Remaining );
        
        m_MADStream.error = (mad_error)0;
    }

    // [Madlld comment]:
    // Decode the next MPEG m_MADFrame. The streams is read from the
    // buffer, its constituents are broken down and stored in the 
    // mxhouse->m_MADFrame structure, ready for examination/alteration 
    // or PCM synthesis. Decoding options are carried in the Frame
    // structure from the mxhouse->m_MADStream structure.
    // 
    // Error handling: mad_frame_decode() returns a non zero value
    // when an error occurs. The error condition can be checked in
    // the error member of the mxhouse->m_MADStream structure. A mad error is
    // recoverable or fatal, the error status is checked with the
    // MAD_RECOVERABLE macro.
    // 
    // {4} When a fatal error is encountered all decoding
    // activities shall be stopped, except when a MAD_ERROR_BUFLEN
    // is signaled. This condition means that the
    // mad_frame_decode() function needs more input to complete
    // its work. One shall refill the buffer and repeat the
    // mad_frame_decode() call. Some bytes may be left unused at
    // the end of the buffer if those bytes forms an incomplete
    // m_MADFrame. Before refilling, the m_Remaining bytes must be moved
    // to the beginning of the buffer and used for input for the
    // next mad_frame_decode() invocation. (See the comments
    // marked {2} earlier for more details.)
    // 
    // Recoverable errors are caused by malformed bit-streams, in
    // this case one can call again mad_frame_decode() in order to
    // skip the faulty part and re-sync to the next m_MADFrame.

    if( mad_frame_decode(&m_MADFrame, &m_MADStream) )
    {
        if( MAD_RECOVERABLE(m_MADStream.error) )
        {
            // Do not print a message if the error is 
            // a loss of synchronization or this loss 
            // is due to the end of m_MADStream guard bytes. 

            if( m_MADStream.error != MAD_ERROR_LOSTSYNC || m_MADStream.this_frame != guardPtr ||
                // Suppress error if caused by ID3 tag.
               (m_MADStream.this_frame[0] != 'I' &&		// ID3v2
                m_MADStream.this_frame[1] != 'D' &&
                m_MADStream.this_frame[2] != '3') 
                ||
               (m_MADStream.this_frame[0] != 'T' &&		// ID3v1
                m_MADStream.this_frame[1] != 'A' &&
                m_MADStream.this_frame[2] != 'G') )
            {			
                CoreManager.GetLog().LogError("CAudioQueueMp3::Read - Recoverable m_MADFrame level error (%s)", mad_stream_errorstr(&m_MADStream));
            }	
            return nReturn_CallAgain; 
        }
        else		// Non-recoverable error
        {
            // MAD_ERROR_BUFLEN means that more input
            // is needed (it's not recoverable without
            // interaction from the calling code). The
            // bytes already in the buffer must be 
            // preserved. "mxstat->m_BufferStart" is used
            // to point to the end of the preserved
            // bytes in "m_InputBuffer.GetBuffer()", then MORE_INPUT 
            // is requested. "mxstat->m_BufferStart" is set
            // to 0 every time "madx_read()" is 
            // called. The calling code checks this 
            // variable to determine if a full buffer 
            // read or a partial read is necessary.
            // (Not "0" signifies a partial read.)

            if( m_MADStream.error == MAD_ERROR_BUFLEN )
            {
                CoreManager.GetLog().LogError( "CAudioQueueMp3::Read - Need more input (%s)",	mad_stream_errorstr(&m_MADStream));
                m_Remaining = (UInt32) ( m_MADStream.bufend - m_MADStream.next_frame );
                MemoryCopy( (Void*) m_MADStream.next_frame, m_InputBuffer.GetBuffer(), m_Remaining);
                m_ReadSize = INPUT_BUFFER_SIZE - m_Remaining;

                // How far "forward" m_InputBuffer.GetBuffer() to begin:
                m_BufferStart = m_InputBuffer.GetBuffer() + m_Remaining;

                return nReturn_MoreInput;

            }
            else			// Error returned
            {
                CoreManager.GetLog().LogError("CAudioQueueMp3::Read - Unrecoverable m_MADFrame level error (%s).", mad_stream_errorstr(&m_MADStream));
                return nReturn_Error; 
            }
        }
    }

    // [Madlld comment]:
    // Accounting. The computed m_MADFrame duration is in the m_MADFrame
    // header structure. It is expressed as a fixed point number
    // whole data type is mad_timer_t. It is different from the
    // samples fixed point format and unlike it, it can't directly
    // be added or subtracted. The m_MADTimer module provides several
    // functions to operate on such numbers. Be careful there, as
    // some functions of libmad's m_MADTimer module receive some of
    // their mad_timer_t arguments by value!

    m_MADFrameCounter++;
    mad_timer_add( &m_MADTimer, m_MADFrame.header.duration );

    // Once decoded the m_MADFrame is synthesized to 
    // PCM samples. No errors are reported by 
    // mad_synth_frame();
    mad_synth_frame( &m_MADSynth, &m_MADFrame );

    // [Madlld comment]:
    // Synthesized samples must be converted from libmad's fixed
    // point number to the consumer format. Here we use unsigned
    // 16 bit big endian integers on two channels. Integer samples
    // are temporarily stored in a buffer that is flushed when
    // full.
    //
    // Note: Code to computer "big-endian" has been preserved
    // below. It is simply commented out. This source produces
    // 16-bit "little-endian" PCM samples.

    Int32 i;
    for( i=0; i < m_MADSynth.pcm.length; i++ )
    {
        Int16	sample;

        // Left channel
        sample = ScalePCMSample(m_MADSynth.pcm.samples[0][i], &rnscale);

        // Originally big-endian:
        // *(mxhouse->outputPtr++)=sample>>8;      
        // *(mxhouse->outputPtr++)=sample&0xff;

        // 16-bit little-endian

        *(m_OutputBufferPtr++)=((sample>>0) & 0xff);
        *(m_OutputBufferPtr++)=((sample>>8) & 0xff);

        // Right channel. 
        // If the decoded m_MADStream is monophonic then 
        // the right output channel is the same as 
        // the left one.

        if(MAD_NCHANNELS(&m_MADFrame.header)==2)
            sample = ScalePCMSample(m_MADSynth.pcm.samples[1][i], &rnscale);

        // Originally big-endian:
        // *(mxhouse->outputPtr++)=sample>>8;      
        // *(mxhouse->outputPtr++)=sample&0xff;

        // 16-bit little-endian
        *(m_OutputBufferPtr++)=((sample>>0) & 0xff);
        *(m_OutputBufferPtr++)=((sample>>8) & 0xff);
    }

    // Tell calling code buffer size
    m_WriteSize = (UInt32) ( m_OutputBufferPtr - m_OutputBuffer.GetBuffer() );

    // Indicate that buffer is ready to be
    // written.

    if ( m_MADSynth.pcm.length < 1152 || OUTPUT_BUFFER_SIZE - m_WriteSize  < 1152 )
    {
        // Reset pointer
        m_OutputBufferPtr = m_OutputBuffer.GetBuffer();  
        return nReturn_Flush;
    }
    else
        return nReturn_CallAgain; 		// Otherwise, continue

}
