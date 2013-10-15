#ifndef _SABLE_CORE_LOG_HANDLER_
#define _SABLE_CORE_LOG_HANDLER_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CLogger;

/** 
\ingroup CoreLog
Specific log
*/
class CLogHandler
{

public:

	/** @name Constructor/Destructor*/
    //@{
	CLogHandler( CLogger& logger );
	virtual ~CLogHandler();
    //@}

	/** @name Accessor*/
    //@{
    Void    SetLevelMask( UInt32 mask );
    UInt32  GetLevelMask() const;
    //@}

	/** @name Manipulator*/
	//@{
    virtual Void Log( UInt32 lvl, String header, String msg ) = 0;
	//@}

private:

    //Types

    //Methods

    //Attributes
    UInt32      m_LevelMask;
	CLogger*	m_Logger;

};

}

#endif
