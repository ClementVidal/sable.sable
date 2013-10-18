#ifndef _SABLE_INPUT_MOUSE_IMPL_HEADER_
#define _SABLE_INPUT_MOUSE_IMPL_HEADER_

#include <Sable/Setup.h>

#if defined( SETUP_IMPLTYPE_MSW )
#include <Sable/Input/Mouse/Impl/Msw/Mouse.h>
#else
#include <Sable/Input/Mouse/Impl/Stub/Mouse.h>
#endif

namespace Sable
{
#if defined( SETUP_IMPLTYPE_MSW )
	typedef CImplMswMouse					CImplMouse;
#else
	typedef CImplStubMouse					CImplMouse;
#endif
}

#endif