#include <Sable/Network/Impl/Msw/Host.h>

#include <Sable/Core/Debug/Header.h>

CImplMswNetworkHost::CImplMswNetworkHost(CNetworkHost& publicHost) : 
	CImplStubNetworkHost( publicHost )
{
	Char buffer[128];
	if( gethostname( buffer, 128 ) != 0 )
	{
		DebugLogWarning( "CImplMswNetworkHost::CImplMswNetworkHost - Failed to get local host name" );
		return;
	}

	m_Name = buffer;

	ExtractHostInfo();
}

CImplMswNetworkHost::CImplMswNetworkHost(CNetworkHost& publicHost, String nameOrAddress ) : 
	CImplStubNetworkHost( publicHost )
{
	m_Name = nameOrAddress;

	ExtractHostInfo();
}

CImplMswNetworkHost::~CImplMswNetworkHost()
{
}

Void CImplMswNetworkHost::ExtractHostInfo( )
{
	m_HostInfo = gethostbyname( m_Name.GetBuffer() );
	if( m_HostInfo == NULL )
	{
		in_addr addr;
		addr.s_addr = inet_addr(m_Name);
		if (addr.s_addr == INADDR_NONE) 
		{
			DebugLogWarning( "CImplMswNetworkHost::ExtractHostInfo - Invalid Ip address" );
			return;
		} 
		else
		{
			m_HostInfo = gethostbyaddr((char *) &addr, 4, AF_INET);
		}
	}

	if( m_HostInfo == NULL )
	{
		DebugLogWarning( "CImplMswNetworkHost::ExtractHostInfo - Failed to get host info" );
		return;
	}

	DebugAssertMsg( m_HostInfo->h_addrtype == AF_INET, "CImplMswNetworkHost::ExtractHostInfo - Address is not an Ipv4 valid address");
}

String CImplMswNetworkHost::GetName() const
{
	return m_Name;
}

UInt32	CImplMswNetworkHost::GetIPAddressAsUInt32() const
{
	DebugAssert( m_HostInfo );
	UInt32 addr;
	addr = (UInt32) *(u_long *) m_HostInfo->h_addr_list[0];
	return addr;
}

String	CImplMswNetworkHost::GetIPAddressAsString() const
{
	DebugAssert( m_HostInfo );
	in_addr addr;
	addr.s_addr = *(u_long *) m_HostInfo->h_addr_list[0];
	return inet_ntoa( addr );
}
