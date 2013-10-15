#ifndef _SABLE_CORE_LOG_OUTPUTWINDOWHANDLER_
#define _SABLE_CORE_LOG_OUTPUTWINDOWHANDLER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Log\Handler.h>

namespace Sable
{

/** 
\ingroup CoreLog
Console handler
*/
class CLogOutputWindowHandler : public CLogHandler
{

public:

	/** @name Constructor/Destructor*/
    //@{
	CLogOutputWindowHandler( CLogger& logger );
	~CLogOutputWindowHandler();
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
