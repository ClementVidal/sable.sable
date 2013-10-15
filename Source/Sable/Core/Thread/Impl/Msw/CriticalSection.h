#ifndef _SABLE_CORE_THREAD_IMPL_MSW_CRITICALSECTION_
#define _SABLE_CORE_THREAD_IMPL_MSW_CRITICALSECTION_

#include <Sable\Core\Thread\Impl\Stub\CriticalSection.h>

namespace Sable
{

/** 
*/
class CImplMswCriticalSection : public CImplStubCriticalSection
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplMswCriticalSection( CCriticalSection& publicImpl );
    ~CImplMswCriticalSection();
    //@}

    /** @name Manipulator*/
    //@{
    virtual Void Enter();
    virtual Void Leave();
    //@}

private:

    // Static methods

	// Attributes
    CRITICAL_SECTION m_CS;
};

}

#endif
