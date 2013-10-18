#ifndef _SABLE_GRAPHICS_GEOMETRY_IMPL_HEADER_
#define _SABLE_GRAPHICS_GEOMETRY_IMPL_HEADER_ 

#include <Sable/Setup.h>

#if defined( SETUP_IMPLTYPE_DIRECTX )
#include <Sable/Graphics/Geometry/Impl/DirectX/IndexBuffer.h>
#include <Sable/Graphics/Geometry/Impl/DirectX/VertexBuffer.h>
#include <Sable/Graphics/Geometry/Impl/DirectX/VertexLayout.h>
#elif defined( SETUP_IMPLTYPE_GLES )
#include <Sable/Graphics/Geometry/Impl/GLES/IndexBuffer.h>
#include <Sable/Graphics/Geometry/Impl/GLES/VertexBuffer.h>
#include <Sable/Graphics/Geometry/Impl/GLES/VertexLayout.h>
#else
#include <Sable/Graphics/Geometry/Impl/Stub/IndexBuffer.h>
#include <Sable/Graphics/Geometry/Impl/Stub/VertexBuffer.h>
#include <Sable/Graphics/Geometry/Impl/Stub/VertexLayout.h>
#endif

namespace Sable
{
#if defined( SETUP_IMPLTYPE_DIRECTX )
	typedef CImplDirectXIndexBuffer				    CImplIndexBuffer;
	typedef CImplDirectXVertexStream				CImplVertexStream;
	typedef CImplDirectXVertexLayout				CImplVertexLayout;
#elif defined( SETUP_IMPLTYPE_GLES )
	typedef CImplGLESIndexBuffer				CImplIndexBuffer;
	typedef CImplGLESVertexStream			CImplVertexStream;
	typedef CImplGLESVertexLayout			CImplVertexLayout;
#else
	typedef CImplStubIndexBuffer				CImplIndexBuffer;
	typedef CImplStubVertexStream				CImplVertexStream;
	typedef CImplStubVertexLayout				CImplVertexLayout;
#endif
}

#endif
