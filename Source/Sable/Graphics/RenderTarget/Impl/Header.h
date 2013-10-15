#ifndef _SABLE_GRAPHICS_RENDERTARGET_IMPL_HEADER_
#define _SABLE_GRAPHICS_RENDERTARGET_IMPL_HEADER_

#include <Sable\Setup.h>

#if defined( SETUP_IMPLTYPE_DIRECTX )
#include <Sable\Graphics\RenderTarget\Impl\DirectX\Texture.h>
#include <Sable\Graphics\RenderTarget\Impl\DirectX\BackBuffer.h>
#include <Sable\Graphics\RenderTarget\Impl\DirectX\DepthStencil.h>
#elif defined( SETUP_IMPLTYPE_GLES )
#include <Sable\Graphics\RenderTarget\Impl\GLES\Texture.h>
#include <Sable\Graphics\RenderTarget\Impl\GLES\BackBuffer.h>
#include <Sable\Graphics\RenderTarget\Impl\GLES\DepthStencil.h>
#else
#include <Sable\Graphics\RenderTarget\Impl\Stub\Texture.h>
#include <Sable\Graphics\RenderTarget\Impl\Stub\BackBuffer.h>
#include <Sable\Graphics\RenderTarget\Impl\Stub\DepthStencil.h>
#endif

namespace Sable
{
#if defined( SETUP_IMPLTYPE_DIRECTX )
	typedef CImplDirectXRenderTargetTexture			CImplRenderTargetTexture;
	typedef CImplDirectXRenderTargetBackBuffer		CImplRenderTargetBackBuffer;
	typedef CImplDirectXRenderTargetDepthStencil	CImplRenderTargetDepthStencil;
#elif defined( SETUP_IMPLTYPE_GLES )
	typedef CImplGLESRenderTargetTexture			CImplRenderTargetTexture;
	typedef CImplGLESRenderTargetBackBuffer		CImplRenderTargetBackBuffer;
	typedef CImplGLESRenderTargetDepthStencil	CImplRenderTargetDepthStencil;
#else
	typedef CImplStubRenderTargetTexture		CImplRenderTargetTexture;
	typedef CImplStubRenderTargetBackBuffer		CImplRenderTargetBackBuffer;
	typedef CImplStubRenderTargetDepthStencil	CImplRenderTargetDepthStencil;
#endif
}

#endif
