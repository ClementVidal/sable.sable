#ifndef _SABLE_GRAPHICS_STATES_IMPL_HEADER_
#define _SABLE_GRAPHICS_STATES_IMPL_HEADER_

#include <Sable/Setup.h>

#if defined( SETUP_IMPLTYPE_DIRECTX )
#include <Sable/Graphics/States/Impl/DirectX/Blend.h>
#include <Sable/Graphics/States/Impl/DirectX/Rasterizer.h>
#include <Sable/Graphics/States/Impl/DirectX/DepthStencil.h>
#include <Sable/Graphics/States/Impl/DirectX/Sampler.h>
#elif defined( SETUP_IMPLTYPE_GLES )
#include <Sable/Graphics/States/Impl/GLES/Blend.h>
#include <Sable/Graphics/States/Impl/GLES/Rasterizer.h>
#include <Sable/Graphics/States/Impl/GLES/DepthStencil.h>
#include <Sable/Graphics/States/Impl/GLES/Sampler.h>
#else
#include <Sable/Graphics/States/Impl/Stub/Blend.h>
#include <Sable/Graphics/States/Impl/Stub/Rasterizer.h>
#include <Sable/Graphics/States/Impl/Stub/DepthStencil.h>
#include <Sable/Graphics/States/Impl/Stub/Sampler.h>
#endif

namespace Sable
{
#if defined( SETUP_IMPLTYPE_DIRECTX )
    typedef CImplDirectXStatesBlend			CImplStatesBlend;
    typedef CImplDirectXStatesRasterizer    CImplStatesRasterizer;
	typedef CImplDirectXStatesDepthStencil  CImplStatesDepthStencil;
	typedef CImplDirectXStatesSampler		CImplStatesSampler;
#elif defined( SETUP_IMPLTYPE_GLES )
	typedef CImplGLESStatesBlend			CImplStatesBlend;
	typedef CImplGLESStatesRasterizer		CImplStatesRasterizer;
	typedef CImplGLESStatesDepthStencil		CImplStatesDepthStencil;
	typedef CImplGLESStatesSampler			CImplStatesSampler;
#else
	typedef CImplStubStatesBlend			CImplStatesBlend;
    typedef CImplStubStatesRasterizer		CImplStatesRasterizer;
	typedef CImplStubStatesDepthStencil		CImplStatesDepthStencil;
	typedef CImplStubStatesSampler			CImplStatesSampler;
#endif
}

#endif