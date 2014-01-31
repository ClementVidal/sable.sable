//#ifndef _SABLE_CORE_FILE_IMPL_HEADER_
//#define _SABLE_CORE_FILE_IMPL_HEADER_


#include <Sable/Setup.h>

#if defined( SETUP_IMPLTYPE_MSW )
#include <Sable/Core/File/Impl/Msw/System.h>
#include <Sable/Core/File/Impl/Msw/File.h>
#elif defined( SETUP_IMPLTYPE_ANDROID )
#include <Sable/Core/File/Impl/Android/System.h>
#include <Sable/Core/File/Impl/Android/File.h>
#elif defined( SETUP_IMPLTYPE_LINUX )
#include <Sable/Core/File/Impl/Linux/System.h>
#include <Sable/Core/File/Impl/Linux/File.h>
#else
#include <Sable/Core/File/Impl/Stub/System.h>
#include <Sable/Core/File/Impl/Stub/File.h>
#endif

namespace Sable
{
#if defined( SETUP_IMPLTYPE_MSW )
	typedef CImplMswFileSystem					CImplFileSystem;
	typedef CImplMswFile						CImplFile;
#elif defined( SETUP_IMPLTYPE_ANDROID )
	typedef CImplAndroidFileSystem				CImplFileSystem;
	typedef CImplAndroidFile					CImplFile;
#elif defined( SETUP_IMPLTYPE_LINUX )
	typedef CImplLinuxFileSystem				CImplFileSystem;
	typedef CImplLinuxFile					CImplFile;
#else
	typedef CImplStubFileSystem					CImplFileSystem;
	typedef CImplStubFile						CImplFile;
#endif
}

//#endif
