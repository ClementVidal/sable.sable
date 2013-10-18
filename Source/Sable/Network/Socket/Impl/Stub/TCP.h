#ifndef _SABLE_NETWORK_SOCKET_IMPL_STUB_KEYBOARD_
#define _SABLE_NETWORK_SOCKET_IMPL_STUB_KEYBOARD_

#include <Sable/Core/Common/DataTypes.h>

namespace Sable
{

class CSocketTCP;

/** 
\ingroup Input
*/
class CImplStubSocketTCP 
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CImplStubSocketTCP( ){}
	CImplStubSocketTCP( CSocketTCP& socket, Bool isBlocking  ){}
	virtual ~CImplStubSocketTCP(){}
	//@}

	/** @name Accessors*/
	//@{
	//@}

	/** @name Manipulator*/
	//@{
    virtual Bool    Bind( UInt16 port ) = 0;
    virtual Bool    Listen( UInt16 nbConnect ) = 0;
    virtual Bool    Accept( CSocketTCP& acceptedSocket ) = 0;
    virtual Int32   Send( const Byte* buffer, UInt32 size ) = 0;
    virtual Int32   Receive( Byte* buffer, UInt32 size ) = 0;
    virtual Bool    Connect( CNetworkHost& distantHost, UInt16 port  ) = 0;
	//@}

private:

	// Methods

	// Attributes

};

}

#endif
