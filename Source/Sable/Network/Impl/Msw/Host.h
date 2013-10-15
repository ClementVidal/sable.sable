#ifndef _SABLE_NETWORK_IMPL_MSW_HOST_
#define _SABLE_NETWORK_IMPL_MSW_HOST_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\String\StaticString.h>
#include <Sable\Network\Impl\Stub\Host.h>

#include <Winsock.h>

namespace Sable
{

class CNetworkHost;

/** 
\ingroup Input
*/
class CImplMswNetworkHost : public CImplStubNetworkHost
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CImplMswNetworkHost(CNetworkHost& socket);
	CImplMswNetworkHost( CNetworkHost& socket, String nameOrAddress );
	virtual ~CImplMswNetworkHost();
	//@}

	/** @name Accessors*/
	//@{
	String	GetName() const;
	UInt32	GetIPAddressAsUInt32() const;
	String	GetIPAddressAsString() const;
	//@}

	/** @name Manipulator*/
	//@{
	//@}

private:

	// Methods
	Void	ExtractHostInfo( );

	// Attributes
	CStaticString<128>	m_Name;
	hostent*			m_HostInfo;

};

}

#endif
