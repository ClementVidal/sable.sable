#ifndef _SABLE_CORE_LOG_CONSOLEHANDLER_
#define _SABLE_CORE_LOG_CONSOLEHANDLER_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Log/Handler.h>

namespace Sable
{

/** 
\ingroup CoreLog
Console handler
*/
class CLogConsoleHandler : public CLogHandler
{

public:

	/** @name Constructor/Destructor*/
    //@{
	CLogConsoleHandler( CLogger& logger );
	~CLogConsoleHandler();
    //@}

	/** @name Accessor*/
    //@{
    //@}

	/** @name Manipulator*/
	//@{
    Void Log( UInt32 lvl, String header, String msg );
	//@}

private:

    //Types

    //Methods

    //Attributes

};

}

#endif
