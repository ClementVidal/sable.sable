#ifndef _SABLE_GRAPHICS_TEXTURE_IMPL_HEADER_
#define _SABLE_GRAPHICS_TEXTURE_IMPL_HEADER_

#include <Sable/Setup.h>

#if defined( SETUP_IMPLTYPE_DIRECTX )
#include <Sable/Graphics/Texture/Impl/DirectX/Texture2D.h>
#include <Sable/Graphics/Texture/Impl/DirectX/Texture3D.h>
#include <Sable/Graphics/Texture/Impl/DirectX/TextureCube.h>
#elif defined( SETUP_IMPLTYPE_GLES )
#include <Sable/Graphics/Texture/Impl/GLES/Texture2D.h>
#include <Sable/Graphics/Texture/Impl/GLES/Texture3D.h>
#include <Sable/Graphics/Texture/Impl/GLES/TextureCube.h>
#else
#include <Sable/Graphics/Texture/Impl/Stub/Texture2D.h>
#include <Sable/Graphics/Texture/Impl/Stub/Texture3D.h>
#include <Sable/Graphics/Texture/Impl/Stub/TextureCube.h>
#endif

namespace Sable
{
#if defined( SETUP_IMPLTYPE_DIRECTX )
	typedef CImplDirectXTexture2D			CImplTexture2D;
	typedef CImplDirectXTexture3D			CImplTexture3D;
	typedef CImplDirectXTextureCube			CImplTextureCube;
#elif defined( SETUP_IMPLTYPE_GLES )
	typedef CImplGLESTexture2D		CImplTexture2D;
	typedef CImplGLESTexture3D		CImplTexture3D;
	typedef CImplGLESTextureCube		CImplTextureCube;
#else
	typedef CImplStubTexture2D			CImplTexture2D;
	typedef CImplStubTexture3D			CImplTexture3D;
	typedef CImplStubTextureCube		CImplTextureCube;
#endif
}

#endif
