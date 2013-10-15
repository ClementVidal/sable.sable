#ifndef _CORE_COMMON_COREMANAGER_
#define _CORE_COMMON_COREMANAGER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\ManagedObject\ManagedObject.h>

#include <Sable\Setup.h>
#include <Sable\Core\File\System.h>
#include <Sable\Setup.h>
#include <Sable\Core\ManagedObject\Singleton.h>
#include <Sable\Core\Math\Random.h>
#include <Sable\Core\Memory\Manager.h>
#include <Sable\Core\Log\Header.h>
#include <Sable\Core\Time\Timer.h>
#include <Sable\Core\Debug\Prof.h>

#define		COREMANAGER_CODETIMER_COUNT 64
#define		CoreManager  Sable::CCoreManager::GetInstance()

namespace Sable
{

class CDebugCodeTimer;

/** 
\ingroup Core
Core manager
*/
class CCoreManager : public CSingleton<CCoreManager>
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CCoreManager();
	virtual ~CCoreManager();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
    CDebugProf&		GetDebugProf();
	CRandom&		GetRandomGenerator() ;
    CLogger&		GetLog();
	CMemoryManager& GetMemoryManager();
	CFileSystem&	GetFileSystem();
    //@}

	/** @name Manipulator*/
	//@{
	Void		Update();
	//@}

private:

	// DataType

	// Attributes

	CMemoryManager                          m_MemoryManager;
    CRandom                                 m_RandomGenerator;
	CFileSystem                             m_FileSystem;
    CLogger                                 m_Log;
	CLogConsoleHandler                      m_LogConsoleHandler;
	CLogOutputWindowHandler                 m_LogOutputWindowHandler;
	CDebugProf								m_DebugProf;

	CTimer									m_CoreTimer;
	Float64									m_LastSampleTime;
	UInt32									m_FrameCount;

};


}

#endif


