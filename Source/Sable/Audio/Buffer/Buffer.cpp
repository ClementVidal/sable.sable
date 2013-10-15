#include <Sable\Audio\Buffer\Buffer.h>

#include <Sable\Audio\Common\Helper.h>
#include <Sable\Audio\Common\World.h>

#include <Al.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CAudioBuffer, CManagedObject )

CAudioBuffer::CAudioBuffer() 
{
    m_SampleCount = 0;
    m_Format = nFormat_None;
    m_Freq = 0;
    alGenBuffers(1, &m_OALName);
    DebugAssert( alGetError() == AL_NO_ERROR );
}

CAudioBuffer::CAudioBuffer( UInt32 sampleCount, EFormat fmt, UInt32 freq  ) 
{
    alGenBuffers(1, &m_OALName);
    DebugAssert( alGetError() == AL_NO_ERROR );

	AllocatePCMBuffer( sampleCount, fmt, freq );
}

CAudioBuffer::~CAudioBuffer()
{
    alDeleteBuffers(1, &m_OALName);
}

Void CAudioBuffer::AllocatePCMBuffer( UInt32 sampleCount, EFormat fmt, UInt32 freq )
{
	m_Format = fmt;
	m_SampleCount = sampleCount;
	m_Freq = freq;
    m_Data.SetItemCount( GetByteCount() );
}

Void* CAudioBuffer::GetPCMData( ) const
{
    return m_Data.GetBuffer();
}

UInt32 CAudioBuffer::GetSampleCount() const
{
	return m_SampleCount;
}

UInt32 CAudioBuffer::GetByteCount() const
{
    if( m_Format == nFormat_Mono8 )
        return m_SampleCount * 1;

    if( m_Format == nFormat_Mono16 )
        return m_SampleCount * 2;

    if( m_Format == nFormat_Stereo8 )
        return m_SampleCount * 1;

    if( m_Format == nFormat_Stereo16 )
        return m_SampleCount * 2;

    DebugError("CAudioBuffer::GetByteCount - Invalid format\n" );
    return 0;
}

Void CAudioBuffer::BindPCMData()
{
	alGetError();
	alBufferData( m_OALName, CAudioHelper::ConvertBufferFormat( m_Format ), m_Data.GetBuffer(), GetByteCount() , m_Freq );
	ALenum error = alGetError();
	DebugAssert( error == AL_NO_ERROR );
}

Void CAudioBuffer::SetPCMData( Void* data )
{
    DebugAssert( GetByteCount() != 0 );

    MemoryCopy( data, m_Data.GetBuffer(), GetByteCount() );
	BindPCMData();
}

Float32 CAudioBuffer::GetDuration() const
{
    return (Float32) m_SampleCount / (Float32) m_Freq;
}

UInt32 CAudioBuffer::GetName() const
{
    return m_OALName;
}

CAudioBuffer::EFormat CAudioBuffer::GetFormat() const
{
    return m_Format;
}

UInt32 CAudioBuffer::GetFreq() const
{
    return m_Freq;
}