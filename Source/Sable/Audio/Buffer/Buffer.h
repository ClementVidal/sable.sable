#ifndef _SABLE_AUDIO_BUFFER_BUFFER_
#define _SABLE_AUDIO_BUFFER_BUFFER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\ManagedObject\ManagedObject.h>
#include <Sable\Core\Collection\Array.h>

namespace Sable
{

class CAudioWorld;

/** 
\ingroup AudioBuffer
Audio buffer
*/
class CAudioBuffer : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CAudioBuffer )

public:

    /** @name DataTypes*/
    //@{
    enum EFormat
    {
        nFormat_Mono8,
        nFormat_Mono16,
        nFormat_Stereo8,
        nFormat_Stereo16,
        nFormat_None
    };
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CAudioBuffer( );
    CAudioBuffer( UInt32 sampleCount, EFormat fmt, UInt32 freq  );
    virtual ~CAudioBuffer();
    //@}

    /** @name Accessors*/
    //@{
	UInt32					GetSampleCount() const;
    Float32                 GetDuration() const;
    UInt32                  GetByteCount() const;
    CAudioBuffer::EFormat   GetFormat() const;
    UInt32                  GetFreq() const;
    UInt32					GetName() const;
    Void					SetPCMData( Void* data );
    Void*					GetPCMData() const;
    //@}

    /** @name Manipulator*/
    //@{
    //@}

protected:

	// Attributes
	CArray<Byte>    m_Data;

	// Methods
	Void AllocatePCMBuffer( UInt32 sampleCount, EFormat fmt, UInt32 freq );
	Void BindPCMData();

private:

    // Attributes
    UInt32          m_SampleCount;
    UInt32          m_OALName;
    EFormat         m_Format;
    UInt32          m_Freq;
};


}

#endif


