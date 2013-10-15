#ifndef _SABLE_INPUT_BUILDFILEHEADER_
#define _SABLE_INPUT_BUILDFILEHEADER_

#include <Sable\Setup.h>
#include <stdarg.h>
#include <stdio.h>

#if defined( SETUP_IMPLTYPE_MSW )

#include <vadefs.h>
#include <windows.h>
#include <Dbghelp.h>

#endif

#if defined( SETUP_IMPLTYPE_DIRECTX )

#include <d3d10.h>
#include <d3dx10.h>
#include <d3dx10async.h>

#endif

#ifdef SETUP_IMPLTYPE_ANDROID

#include <Android\Log.h>

#endif

#if defined( SETUP_IMPLTYPE_GLES )

#include <EGL\egl.h>
#include <GLES2\gl2.h>
#include <GLES2\gl2ext.h>

#endif

#endif
