#ifndef _SABLE_AUDIO_COMMON_HELPER_
#define _SABLE_AUDIO_COMMON_HELPER_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Audio/Buffer/Buffer.h>

#include <al.h>

namespace Sable
{

/** 
\ingroup AudioCommon
Helper class for Audios package
*/
class CAudioHelper 
{

public:
	
    static ALenum ConvertBufferFormat( CAudioBuffer::EFormat fmt );
    static CAudioBuffer::EFormat ConvertBufferFormat( ALenum fmt );

};

}

#endif