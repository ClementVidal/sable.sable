#ifndef _SABLE_CORE_THREAD_IMPL_MSW_THREAD_
#define _SABLE_CORE_THREAD_IMPL_MSW_THREAD_

#include <Sable\Core\Thread\Impl\Stub\Thread.h>

namespace Sable
{

/** 
*/
class CImplMswThread : public CImplStubThread
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplMswThread( CThread& publicImpl, UInt32 stackSize  );
    ~CImplMswThread();
    //@}

    /** @name Accessors*/
    //@{
    Bool IsFinished() const;
    //@}

	/** @name Manipulator*/
	//@{
    Void Start( );
    //@}

private:

    // Static methods
    static DWORD  WINAPI ThreadFunc( LPVOID params );

	// Attributes
    HANDLE  m_ThreadHandle;

};

}

#endif

