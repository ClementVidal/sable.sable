#ifndef _SABLE_INPUT_PAD_IMPL_HEADER_
#define _SABLE_INPUT_PAD_IMPL_HEADER_

#include <Sable\Setup.h>

#if defined( SETUP_IMPLTYPE_MSW )
#include <Sable\Input\Pad\Impl\Msw\Pad.h>
#else
#include <Sable\Input\Pad\Impl\Stub\Pad.h>
#endif

namespace Sable
{
#if defined( SETUP_IMPLTYPE_MSW )
	typedef CImplMswPad					CImplPad;
#else
	typedef CImplStubPad					CImplPad;
#endif
}

#endif