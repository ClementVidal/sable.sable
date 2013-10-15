#ifndef _SABLE_CORE_TIME_IMPL_HEADER_
#define _SABLE_CORE_FILE_IMPL_HEADER_

#include <Sable\Setup.h>

#if defined( SETUP_IMPLTYPE_MSW )
#include <Sable\Core\Time\Impl\Msw\Time.h>
#elif defined( SETUP_IMPLTYPE_ANDROID )
#include <Sable\Core\Time\Impl\Android\Time.h>
#else
#include <Sable\Core\Time\Impl\Stub\Time.h>
#endif

namespace Sable
{
#if defined( SETUP_IMPLTYPE_MSW )
	typedef CImplMswTime						CImplTime;
#elif defined( SETUP_IMPLTYPE_ANDROID )
	typedef CImplAndroidTime					CImplTime;
#else
	typedef CImplStubTime						CImplTime;
#endif
}

#endif
