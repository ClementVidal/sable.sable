#ifndef _SABLE_NETWORK_IMPL_HEADER_
#define _SABLE_NETWORK_IMPL_HEADER_

#include <Sable/Setup.h>

#ifdef SETUP_IMPLTYPE_MSW
#include <Sable/Network/Impl/Msw/Host.h>
#else
#include <Sable/Network/Impl/Stub/Host.h>
#endif

namespace Sable
{
#if defined( SETUP_IMPLTYPE_MSW )
	typedef CImplMswNetworkHost					CImplNetworkHost;
#else
	typedef CImplStubNetworkHost				CImplNetworkHost;
#endif
}

#endif