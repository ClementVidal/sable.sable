#ifndef _SABLE_GRAPHICS_COMMON_IMPL_HEADER_
#define _SABLE_GRAPHICS_COMMON_IMPL_HEADER_

#include <Sable\Setup.h>

#if defined( SETUP_IMPLTYPE_DIRECTX )
#include <Sable\Graphics\Common\Impl\DirectX\GraphicsManager.h>
#elif defined( SETUP_IMPLTYPE_GLES )
#include <Sable\Graphics\Common\Impl\GLES\GraphicsManager.h>
#else
#include <Sable\Graphics\Common\Impl\Stub\GraphicsManager.h>
#endif

namespace Sable
{
#if defined( SETUP_IMPLTYPE_DIRECTX )
	typedef CImplDirectXGraphicsManager			CImplGraphicsManager;
#elif defined( SETUP_IMPLTYPE_GLES )
	typedef CImplGLESGraphicsManager			CImplGraphicsManager;
#else
	typedef CImplStubGraphicsManager		CImplGraphicsManager;
#endif
}

#endif