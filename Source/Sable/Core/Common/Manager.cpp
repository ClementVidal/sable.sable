#include <Sable\Core\Common\Manager.h>

#include <Sable\Core\File\System.h>
#include <Sable\Core\Math\Range.h>

#include <Sable/Setup.h>

#ifdef SETUP_IMPLTYPE_MSW
#include <Winsock.h>
#include <crtdbg.h>
#endif

using namespace Sable;

CCoreManager::CCoreManager() :
	m_LogConsoleHandler( m_Log ),
	m_LogOutputWindowHandler( m_Log )
{

//TEMP: This should be moved to an Impl File
#ifdef SETUP_IMPLTYPE_MSW
	Int32 iResult;
	WSADATA wsaData;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	DebugAssertMsg( iResult == 0, "julCCoreManager::CCoreManager - Failed to initialize winsock library");

	int flags = _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF );
#endif

    m_FileSystem.LoadConfigFile();
}

CMemoryManager& CCoreManager::GetMemoryManager()
{
	return m_MemoryManager;
}

CFileSystem& CCoreManager::GetFileSystem()
{
	return m_FileSystem;
}

CCoreManager::~CCoreManager()
{
//TEMP: This should be moved to an Impl File
#ifdef SETUP_IMPLTYPE_MSW
      WSACleanup();
#endif
}

Void CCoreManager::Update()
{
	DebugProfile("CCoreManager::Update" );
}

CLogger& CCoreManager::GetLog() 
{
    return m_Log;
}

CRandom& CCoreManager::GetRandomGenerator()
{
    return m_RandomGenerator;
}

CDebugProf& CCoreManager::GetDebugProf()
{
	return m_DebugProf;
}
