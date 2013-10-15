#include <Sable\Core\Thread\Impl\Msw\CriticalSection.h>

using namespace Sable;

CImplMswCriticalSection::CImplMswCriticalSection( CCriticalSection& publicImpl ) :
    CImplStubCriticalSection( publicImpl )
{
    ::InitializeCriticalSection(&m_CS);
}

CImplMswCriticalSection::~CImplMswCriticalSection()
{
    ::DeleteCriticalSection(&m_CS);
}

Void CImplMswCriticalSection::Enter()
{
    ::EnterCriticalSection(&m_CS);  
}

Void CImplMswCriticalSection::Leave()
{
    ::LeaveCriticalSection(&m_CS);
}
