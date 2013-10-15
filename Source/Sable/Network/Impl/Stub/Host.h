#ifndef _SABLE_NETWORK_IMPL_STUB_HOST_
#define _SABLE_NETWORK_IMPL_STUB_HOST_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CNetworkHost;

/** 
\ingroup Input
*/
class CImplStubNetworkHost 
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CImplStubNetworkHost(){}
	CImplStubNetworkHost( CNetworkHost& socket ){}
	CImplStubNetworkHost( CNetworkHost& socket, String nameOrAddress ){}
	virtual ~CImplStubNetworkHost(){}
	//@}

	/** @name Accessors*/
	//@{
	virtual String	GetName() const = 0;
	virtual UInt32	GetIPAddressAsUInt32() const = 0;
	virtual String	GetIPAddressAsString() const = 0;
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
