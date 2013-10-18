#ifndef _SABLE_NETWORK_SOCKET_IMPL_MSW_UDP_
#define _SABLE_NETWORK_SOCKET_IMPL_MSW_UDP_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Network/Socket/Impl/Stub/UDP.h>

#include <Winsock.h>

namespace Sable
{

class CSocketUDP;

/** 
\ingroup Input
*/
class CImplMswSocketUDP : public CImplStubSocketUDP
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CImplMswSocketUDP(CSocketUDP& socket);
	virtual ~CImplMswSocketUDP();
	//@}

	/** @name Accessors*/
	//@{
	//@}

	/** @name Manipulator*/
	//@{
	//@}

private:

	// Methods

	// Attributes

};

}

#endif
