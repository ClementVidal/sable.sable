#include <Sable\Core\Log\Handler.h>
#include <Sable\Core\Log\Logger.h>

using namespace Sable;

CLogHandler::CLogHandler( CLogger& logger )
{
	m_Logger = &logger;
    m_LevelMask = CLogger::nLevel_All;
	m_Logger->AddHandler( *this );
}

CLogHandler::~CLogHandler()
{
	m_Logger->RemoveHandler( *this );
}

Void CLogHandler::SetLevelMask( UInt32 mask )
{
    m_LevelMask = mask;
}

UInt32 CLogHandler::GetLevelMask() const
{
    return m_LevelMask;
}