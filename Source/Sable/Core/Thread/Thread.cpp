#include <Sable/Core/Thread/Thread.h>

using namespace Sable;

CThread::CThread( UInt32 stackSize ) :
    m_Impl( *this, stackSize )
{
}

CThread::~CThread()
{
    DebugAssertMsg( IsFinished(), "Cannot destroy a thread while still running" );
}

Void CThread::Start( )
{
    m_Impl.Start( );
}

Bool CThread::IsFinished() const
{
    return m_Impl.IsFinished();
}