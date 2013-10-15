#ifndef _SABLE_GRAPHICS_VIEWPORT_IMPL_HEADER_
#define _SABLE_GRAPHICS_VIEWPORT_IMPL_HEADER_

#include <Sable\Setup.h>

#if defined( SETUP_IMPLTYPE_DIRECTX )
#include <Sable\Graphics\Viewport\Impl\DirectX\Viewport.h>
#elif defined( SETUP_IMPLTYPE_GLES )
#include <Sable\Graphics\Viewport\Impl\GLES\Viewport.h>
#else
#include <Sable\Graphics\Viewport\Impl\Stub\Viewport.h>
#endif

namespace Sable
{
#if defined( SETUP_IMPLTYPE_DIRECTX )
	typedef CImplDirectXViewport		CImplViewport;
#elif defined( SETUP_IMPLTYPE_GLES )
	typedef CImplGLESViewport	CImplViewport;
#else
	typedef CImplStubViewport		CImplViewport;
#endif
}

#endif
