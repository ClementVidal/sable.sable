#ifndef _SABLE_CORE_LOG_LOGGER_
#define _SABLE_CORE_LOG_LOGGER_

#include <Sable/Core/Common/DataTypes.h>

#include <stdarg.h>

#define LOG_HANDLER_TABLE_SIZE 8
#define LOG_HANDLER_HEADER_LENGTH 64

namespace Sable
{

class CLogHandler;

/** 
\ingroup CoreLog
Singleton log class.

Use the Logger macro to acces instance
*/
class CLogger 
{

public:

	/** @name Constructor/Destructor*/
    //@{
    enum ELevel
    {
        nLevel_Error = 1,
        nLevel_Warning,
        nLevel_Info,
        nLevel_All = 0x0fffffff,
        nLevel_Count,
        nLevel_None
    };
    //@}

	/** @name Constructor/Destructor*/
    //@{
	CLogger( );
	virtual ~CLogger();
    //@}

	/** @name Accessor*/
    //@{
    //@}

	/** @name Manipulator*/
	//@{
    Void LogError( String format, ... );
    Void LogWarning( String format, ... );
    Void LogInfo( String format, ... );

    Void Log( ELevel lvl, String format, va_list& args );

	//@}

private:

	// FriendShip
	friend class CLogHandler;
    //Types

	//Methods
	Void	AddHandler( CLogHandler& handler );
	Void	RemoveHandler( CLogHandler& handler );
    String	GetHeader( CLogger::ELevel lvl );

    //Attributes
    CLogHandler*     m_HandlerTable[LOG_HANDLER_TABLE_SIZE];
    Char            m_CurrentHeader[LOG_HANDLER_HEADER_LENGTH];
    Char*           m_WorkingBuffer;

};

}

#endif
