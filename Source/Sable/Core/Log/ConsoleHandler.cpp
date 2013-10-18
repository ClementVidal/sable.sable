#include <Sable/Core/Log/ConsoleHandler.h>

#ifdef SETUP_IMPLTYPE_ANDROID
#include <Android/Log.h>
#endif

using namespace Sable;

CLogConsoleHandler::CLogConsoleHandler( CLogger& logger ) :
    CLogHandler( logger )
{
}

CLogConsoleHandler::~CLogConsoleHandler()
{
}

Void CLogConsoleHandler::Log( UInt32 lvl, String header, String msg )
{
#ifdef SETUP_IMPLTYPE_ANDROID

	android_LogPriority prior = ANDROID_LOG_DEBUG;
	if( lvl == CLogger::nLevel_Error )
		prior = ANDROID_LOG_ERROR;
	else if( lvl == CLogger::nLevel_Warning )
		prior = ANDROID_LOG_WARN;
	else if( lvl == CLogger::nLevel_Info )
		prior = ANDROID_LOG_INFO;

    if( header )
    	__android_log_print( prior, "Sable", "%s: %s\n", header, msg );
    else
    	__android_log_print( prior, "Sable", "%s\n", msg );
#else
    if( header )
        printf("%s", header );

    printf("%s\n", msg );
#endif
}
