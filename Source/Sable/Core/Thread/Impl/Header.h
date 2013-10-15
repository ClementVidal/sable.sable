#ifndef _SABLE_CORE_THREAD_IMPL_HEADER_
#define _SABLE_CORE_THREAD_IMPL_HEADER_

#include <Sable\Setup.h>

#if defined( SETUP_IMPLTYPE_MSW )
#include <Sable\Core\Thread\Impl\Msw\Thread.h>
#include <Sable\Core\Thread\Impl\Msw\CriticalSection.h>
#else
#include <Sable\Core\Thread\Impl\Stub\Thread.h>
#include <Sable\Core\Thread\Impl\Stub\CriticalSection.h>
#endif

namespace Sable
{
#if defined( SETUP_IMPLTYPE_MSW )
	typedef CImplMswThread				CImplThread;
	typedef CImplMswCriticalSection		CImplCriticalSection;
#else
	typedef CImplStubThread				CImplThread;
	typedef CImplStubCriticalSection	CImplCriticalSection;
#endif
}

#endif
