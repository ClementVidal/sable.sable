#ifndef _SABLE_APPLICATION_IMPL_HEADER_
#define _SABLE_APPLICATION_IMPL_HEADER_

#include <Sable/Setup.h>

#if defined( SETUP_IMPLTYPE_MSW )
#include <Sable/Application/Impl/Msw/Application.h>
#include <Sable/Application/Impl/Msw/StandAloneWindow.h>
#elif defined( SETUP_IMPLTYPE_ANDROID )
#include <Sable/Application/Impl/Android/Application.h>
#include <Sable/Application/Impl/Android/StandAloneWindow.h>
#elif defined( SETUP_IMPLTYPE_LINUX )
#include <Sable/Application/Impl/Linux/Application.h>
#include <Sable/Application/Impl/Linux/StandAloneWindow.h>
#else
#include <Sable/Application/Impl/Stub/Application.h>
#include <Sable/Application/Impl/Stub/Window.h>
#endif

namespace Sable
{
#if defined( SETUP_IMPLTYPE_MSW )
    typedef CImplMswApplication			CImplApplication;
    typedef CImplMswStandAloneWindow		CImplStandAloneWindow;
#elif defined( SETUP_IMPLTYPE_ANDROID )
    typedef CImplAndroidApplication		CImplApplication;
    typedef CImplAndroidStandAloneWindow	CImplStandAloneWindow;
#elif defined( SETUP_IMPLTYPE_LINUX )
    typedef CImplLinuxApplication		CImplApplication;
    typedef CImplLinuxStandAloneWindow	        CImplStandAloneWindow;
#else
    typedef CImplStubApplication		CImplApplication;
    typedef CImplStubApplicationWindow		CImplApplicationWindow;
    typedef CImplStubApplicationWindow		CImplStandAloneWindow;
#endif
}

#endif
