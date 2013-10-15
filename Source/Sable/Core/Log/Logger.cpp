#include <Sable\Core\Log\Logger.h>

#define LOG_WORKING_BUFFER_SIZE 4096

using namespace Sable;

CLogger::CLogger( )
{
    Int32 i;

    m_WorkingBuffer = (Char*) MemoryAllocate( CoreManager.GetMemoryManager().GetBuddyHeap(), LOG_WORKING_BUFFER_SIZE );
    for( i=0;i<LOG_HANDLER_TABLE_SIZE;i++ )
    {
        m_HandlerTable[i] = NULL;
    }
}

CLogger::~CLogger()
{
    MemoryFree( CoreManager.GetMemoryManager().GetBuddyHeap(), m_WorkingBuffer );
}

Void CLogger::LogError( String format, ... )
{
    va_list args;
    va_start( args, format );
    Log( nLevel_Error, format, args );
    va_end( args );
}

Void CLogger::LogWarning( String format, ... )
{
    va_list args;
    va_start( args, format );
    Log( nLevel_Warning, format, args );
    va_end( args );
}

Void CLogger::LogInfo( String format, ... )
{
    va_list args;
    va_start( args, format );
    Log( nLevel_Info, format, args );
    va_end( args );
}

Void CLogger::Log( ELevel lvl, String format, va_list& args )
{
    Int32 i;
    
    vsnprintf( m_WorkingBuffer, LOG_WORKING_BUFFER_SIZE, format, args ); 

    for( i=0;i<LOG_HANDLER_TABLE_SIZE;i++ )
    {
        if( m_HandlerTable[i] )
        {
            if( m_HandlerTable[i]->GetLevelMask() & lvl )
                m_HandlerTable[i]->Log( lvl, GetHeader( lvl ), m_WorkingBuffer );
        }
    }

}

Void CLogger::RemoveHandler( CLogHandler& handler )
{
	Int32 i;

	for( i=0; i<LOG_HANDLER_TABLE_SIZE; i++ )
	{
		if( m_HandlerTable[i] == &handler )
		{
			m_HandlerTable[i] = NULL;
			break;
		}
	}
}

Void CLogger::AddHandler( CLogHandler& handler )
{
    Int32 i;

    for( i=0; i<LOG_HANDLER_TABLE_SIZE; i++ )
    {
        if( m_HandlerTable[i] == NULL )
        {
            m_HandlerTable[i] = & handler;
            break;
        }
    }
}

String CLogger::GetHeader( CLogger::ELevel lvl )
{
    switch( lvl )
    {
    case nLevel_Error:
        StringSetFormattedText( m_CurrentHeader, LOG_HANDLER_HEADER_LENGTH, "Error: " );
        break;
    case nLevel_Warning:
        StringSetFormattedText( m_CurrentHeader, LOG_HANDLER_HEADER_LENGTH, "Warning: " );
        break;
    case nLevel_Info:
        StringSetFormattedText( m_CurrentHeader, LOG_HANDLER_HEADER_LENGTH, "Info: " );
        break;
    case nLevel_None:
        StringSetFormattedText( m_CurrentHeader, LOG_HANDLER_HEADER_LENGTH, "" );
        break;
    default:
        return NULL;
    }
    
    return m_CurrentHeader;
}