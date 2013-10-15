#ifndef _SABLE_INPUT_COMMON_IMPL_HEADER_
#define _SABLE_INPUT_COMMON_IMPL_HEADER_ 

#include <Sable\Setup.h>

#if defined( SETUP_IMPLTYPE_MSW )
#include <Sable\Input\Common\Impl\Msw\InputManager.h>
#else
#include <Sable\Input\Common\Impl\Stub\InputManager.h>
#endif

namespace Sable
{
#if defined( SETUP_IMPLTYPE_MSW )
	typedef CImplMswInputManager       CImplInputManager;
#else
	typedef CImplStubInputManager      CImplInputManager;
#endif
}

#endif