#include <Sable/Core/Log/OutputWindowHandler.h>

#ifdef SETUP_IMPLTYPE_MSW
#include <Windows.h>
#endif

using namespace Sable;

CLogOutputWindowHandler::CLogOutputWindowHandler( CLogger& logger ) :
    CLogHandler( logger )
{
}

CLogOutputWindowHandler::~CLogOutputWindowHandler()
{
}

Void CLogOutputWindowHandler::Log( UInt32 lvl, String header, String msg )
{
#ifdef SETUP_IMPLTYPE_MSW
	CString str;
    if( header )
    	str.WriteFormattedText( "Sable - %s: %s\n", header, msg );
    else
    	str.WriteFormattedText( "Sable - %s\n", msg );

	OutputDebugStringA( str.GetBuffer() );
#endif
}
