#include <Sable\Network\Host.h>

using namespace Sable;

CNetworkHost::CNetworkHost() :
	m_Impl( *this )
{

}

CNetworkHost::CNetworkHost( String nameOrAddress ) :
	m_Impl( *this, nameOrAddress )
{

}

CNetworkHost::~CNetworkHost()
{

}

String CNetworkHost::GetName() const
{
	return m_Impl.GetName();
}

UInt32 CNetworkHost::GetIPAddressAsUInt32() const
{
	return m_Impl.GetIPAddressAsUInt32();
}

String CNetworkHost::GetIPAddressAsString() const
{
	return m_Impl.GetIPAddressAsString();
}

CImplNetworkHost& CNetworkHost::GetImpl()
{
	return m_Impl;
}