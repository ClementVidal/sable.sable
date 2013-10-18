#ifndef _SABLE_INPUT_KEYBOARD_IMPL_HEADER_
#define _SABLE_INPUT_KEYBOARD_IMPL_HEADER_

#include <Sable/Setup.h>

#if defined( SETUP_IMPLTYPE_MSW )
#include <Sable/Input/Keyboard/Impl/Msw/Keyboard.h>
#else
#include <Sable/Input/Keyboard/Impl/Stub/Keyboard.h>
#endif

namespace Sable
{
#if defined( SETUP_IMPLTYPE_MSW )
	typedef CImplMswKeyboard					CImplKeyboard;
#else
	typedef CImplStubKeyboard					CImplKeyboard;
#endif
}

#endif