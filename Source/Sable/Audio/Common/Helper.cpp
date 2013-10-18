#include <Sable/Audio/Common/Helper.h>


using namespace Sable;

ALenum CAudioHelper::ConvertBufferFormat( CAudioBuffer::EFormat fmt )
{
    switch( fmt )
    {
    case CAudioBuffer::nFormat_Mono8:
        return AL_FORMAT_MONO8;
    case CAudioBuffer::nFormat_Mono16:
        return AL_FORMAT_MONO16;
    case CAudioBuffer::nFormat_Stereo8:
        return AL_FORMAT_STEREO8;
    case CAudioBuffer::nFormat_Stereo16:
        return AL_FORMAT_STEREO16;
    }

    DebugError("CAudioHelper::ConvertBufferFormat - Invalid audio format");

    return AL_FORMAT_MONO8;
}

CAudioBuffer::EFormat CAudioHelper::ConvertBufferFormat( ALenum fmt )
{
    switch( fmt )
    {
    case AL_FORMAT_MONO8:
        return CAudioBuffer::nFormat_Mono8;
    case AL_FORMAT_MONO16:
        return CAudioBuffer::nFormat_Mono16;
    case AL_FORMAT_STEREO8:
        return CAudioBuffer::nFormat_Stereo8;
    case AL_FORMAT_STEREO16:
        return CAudioBuffer::nFormat_Stereo16;
    }

    DebugError("CAudioHelper::ConvertBufferFormat - Invalid audio format");

    return CAudioBuffer::nFormat_Mono8;
}