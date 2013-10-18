#ifndef _SABLE_NETWORK_SOCKET_TCP_
#define _SABLE_NETWORK_SOCKET_TCP_

#include <Sable/Network/Socket/Impl/Header.h>

namespace Sable 
{

class CNetworkHost;

/**
\ingroup Network
Represent a TCP Socket
*/
class CSocketTCP 
{

public:

    /** @name DataTypes*/
    //@{
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CSocketTCP( Bool isBlocking = FALSE );
    ~CSocketTCP();
    //@}
    
    /** @name Accessors*/
    //@{
	CImplSocketTCP&		GetImpl();
    const CNetworkHost& GetHostInformation() const;
    //@}
    
    /** @name Manipulator*/
    //@{
    Bool    Bind( UInt16 port );
    Bool    Listen( UInt16 nbConnect = 5 );
    Bool    Accept( CSocketTCP& acceptedSocket );
    Int32   Send( const Byte* buffer, UInt32 size );
    Int32   Receive(  Byte* buffer, UInt32 size );
    Bool    Connect( CNetworkHost& distantHost, UInt16 port  );
    //@}
    
private:

    // DataTypes

    // Methods  

    // Attributes
    CImplSocketTCP  m_Impl;
	Bool			m_IsBlocking;

};      

}

#endif
