#ifndef _SABLE_GRAPHICS_SHADER_IMPL_HEADER_
#define _SABLE_GRAPHICS_SHADER_IMPL_HEADER_ 

#include <Sable/Setup.h>

#if defined( SETUP_IMPLTYPE_DIRECTX )
#include <Sable/Graphics/Shader/Impl/DirectX/Program.h>
#include <Sable/Graphics/Shader/Impl/DirectX/Shader.h>
#include <Sable/Graphics/Shader/Impl/DirectX/Parameter.h>
#elif defined( SETUP_IMPLTYPE_GLES )
#include <Sable/Graphics/Shader/Impl/GLES/Program.h>
#include <Sable/Graphics/Shader/Impl/GLES/Shader.h>
#include <Sable/Graphics/Shader/Impl/GLES/Parameter.h>
#else
#include <Sable/Graphics/Shader/Impl/Stub/Program.h>
#include <Sable/Graphics/Shader/Impl/Stub/Shader.h>
#include <Sable/Graphics/Shader/Impl/Stub/Parameter.h>
#endif

namespace Sable
{
#if defined( SETUP_IMPLTYPE_DIRECTX )
	typedef CImplDirectXShaderProgram   CImplShaderProgram;
	typedef CImplDirectXShader			CImplShader;
	typedef CImplDirectXShaderParameter	CImplShaderParameter;
#elif defined( SETUP_IMPLTYPE_GLES )
	typedef CImplGLESShaderProgram		CImplShaderProgram;
	typedef CImplGLESShader				CImplShader;
	typedef CImplGLESShaderParameter	CImplShaderParameter;
#else
	typedef CImplStubShaderProgram		CImplShaderProgram;
	typedef CImplStubShader				CImplShader;
	typedef CImplStubShaderParameter	CImplShaderParameter;
#endif
}

#endif