#ifndef _SABLE_NETWORK_SOCKET_IMPL_MSW_TCP_
#define _SABLE_NETWORK_SOCKET_IMPL_MSW_TCP_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Network\Socket\Impl\Stub\TCP.h>

#include <Winsock.h>

namespace Sable
{

class CKeyboard;

/** 
\ingroup Input
*/
class CImplMswSocketTCP : public CImplStubSocketTCP
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CImplMswSocketTCP( CSocketTCP& socket, Bool isBlocking );
	virtual ~CImplMswSocketTCP();
	//@}

	/** @name Accessors*/
	//@{
	//@}

	/** @name Manipulator*/
	//@{
	Bool    Bind( UInt16 port ) ;
	Bool    Listen( UInt16 nbConnect ) ;
	Bool    Accept( CSocketTCP& acceptedSocket ) ;
	Int32   Send( const Byte* buffer, UInt32 size ) ;
	Int32   Receive( Byte* buffer, UInt32 size ) ;
	Bool    Connect( CNetworkHost& distantHost, UInt16 port ) ;
	//@}

private:

	// Methods

	// Attributes
	SOCKET	m_Socket;

};

}

#endif
