#include <Sable\Core\Thread\Impl\Msw\Thread.h>

#include <Sable\Core\Thread\Thread.h>

using namespace Sable;

CImplMswThread::CImplMswThread( CThread& publicImpl, UInt32 stackSize ) :
    CImplStubThread( publicImpl,stackSize )
{
    DebugAssert( stackSize > 0 );

    m_ThreadHandle = CreateThread( NULL, stackSize, CImplMswThread::ThreadFunc, this, 
            CREATE_SUSPENDED, NULL );
}

CImplMswThread::~CImplMswThread()
{
    CloseHandle( m_ThreadHandle );
}

Bool CImplMswThread::IsFinished() const
{
    DWORD exitCode;
    Bool   ret;
    ret = GetExitCodeThread( m_ThreadHandle, &exitCode );

    DebugAssert( ret );

    if( exitCode == STILL_ACTIVE )
        return FALSE;

    return TRUE;
}

Void CImplMswThread::Start()
{
    ResumeThread( m_ThreadHandle );
}

DWORD WINAPI CImplMswThread::ThreadFunc( LPVOID params )
{
    CImplMswThread* impl = (CImplMswThread*) params;

    impl->m_PublicImpl->Entry( );

    return 0;
} 


