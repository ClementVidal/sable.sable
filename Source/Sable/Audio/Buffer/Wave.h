#ifndef _SABLE_AUDIO_BUFFER_WAVE_
#define _SABLE_AUDIO_BUFFER_WAVE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\File\FilePath.h>

#include <Sable\Audio\Buffer\Buffer.h>

namespace Sable
{

class CAudioWorld;

/** 
\ingroup AudioBuffer
WAVE loader
*/
class CAudioBufferWave : public CAudioBuffer
{

	DEFINE_MANAGED_CLASS( CAudioBufferWave );

public:

    /** @name Constructor/Destructor*/
    //@{
	CAudioBufferWave();
    CAudioBufferWave( const CFilePath& path );
    virtual ~CAudioBufferWave();
    //@}

    /** @name Accessors*/
    //@{
	Void SetFilePath( const CFilePath& path );
    //@}

    /** @name Manipulator*/
    //@{
	Bool Serialize( CPersistentArchive& ar );
	Bool Initialize( );
    //@}

private:

	// Methods
	EFormat DeduceFormat( UInt32 bitPerSamples, UInt32 channel ) const;

    // Attributes
	CFilePath	m_FilePath;

};


}

#endif


