#ifndef _SABLE_CORE_MEMORY_IMPL_HEADER_
#define _SABLE_CORE_MEMORY_IMPL_HEADER_

#include <Sable\Setup.h>

#if defined( SETUP_IMPLTYPE_MSW )
#include <Sable\Core\Memory\Impl\Msw\Manager.h>
#elif defined( SETUP_IMPLTYPE_ANDROID )
#include <Sable\Core\Memory\Impl\Android\Manager.h>
#else
#include <Sable\Core\Memory\Impl\Stub\Manager.h>
#endif

namespace Sable
{
#if defined( SETUP_IMPLTYPE_MSW )
	typedef CImplMswMemoryManager				CImplMemoryManager;
#elif defined( SETUP_IMPLTYPE_ANDROID )
	typedef CImplAndroidMemoryManager			CImplMemoryManager;
#else
	typedef CImplStubMemoryManager				CImplMemoryManager;
#endif
}

#endif
