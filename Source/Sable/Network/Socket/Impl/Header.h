#ifndef _SABLE_NETWORK_SOCKET_IMPL_HEADER_
#define _SABLE_NETWORK_SOCKET_IMPL_HEADER_

#include <Sable/Setup.h>

#if defined( SETUP_IMPLTYPE_MSW )
#include <Sable/Network/Socket/Impl/Msw/TCP.h>
#include <Sable/Network/Socket/Impl/Msw/UDP.h>
#else
#include <Sable/Network/Socket/Impl/Stub/TCP.h>
#include <Sable/Network/Socket/Impl/Stub/UDP.h>
#endif

namespace Sable
{
#if defined( SETUP_IMPLTYPE_MSW )
	typedef CImplMswSocketTCP					CImplSocketTCP;
	typedef CImplMswSocketUDP					CImplSocketUDP;
#else
	typedef CImplStubSocketTCP					CImplSocketTCP;
	typedef CImplStubSocketUDP					CImplSocketUDP;
#endif
}

#endif