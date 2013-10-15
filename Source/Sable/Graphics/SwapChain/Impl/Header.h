#ifndef _SABLE_GRAPHICS_SWAPCHAIN_IMPL_HEADER_
#define _SABLE_GRAPHICS_SWAPCHAIN_IMPL_HEADER_

#include <Sable\Setup.h>

#if defined( SETUP_IMPLTYPE_DIRECTX )
#include <Sable\Graphics\SwapChain\Impl\DirectX\SwapChain.h>
#elif defined( SETUP_IMPLTYPE_GLES )
#include <Sable\Graphics\SwapChain\Impl\GLES\SwapChain.h>
#else
#include <Sable\Graphics\SwapChain\Impl\Stub\SwapChain.h>
#endif

namespace Sable
{
#if defined( SETUP_IMPLTYPE_DIRECTX )
	typedef CImplDirectXSwapChain		CImplSwapChain;
#elif defined( SETUP_IMPLTYPE_GLES )
	typedef CImplGLESSwapChain	CImplSwapChain;
#else
	typedef CImplStubSwapChain		CImplSwapChain;
#endif
}

#endif
