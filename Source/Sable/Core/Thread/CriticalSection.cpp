#include <Sable\Core\Thread\CriticalSection.h>

using namespace Sable;

CCriticalSection::CCriticalSection( ) :
    m_Impl( *this )
{
}

CCriticalSection::~CCriticalSection()
{

}

/**
This will enter the critical section.
*/
Void CCriticalSection::Enter()
{
    m_Impl.Enter();
}

/**
This will leave the critical section.
*/
Void CCriticalSection::Leave()
{
    m_Impl.Leave();
}