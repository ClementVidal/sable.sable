#ifndef _SABLE_NETWORK_SOCKET_UDP_
#define _SABLE_NETWORK_SOCKET_UDP_

#include <Sable\Network\Socket\Impl\Header.h>

namespace Sable 
{

class CNetworkHost;

/**
\ingroup Network
Represent a UDP Socket
*/
class CSocketUDP 
{

public:

    /** @name DataTypes*/
    //@{
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CSocketUDP();
    ~CSocketUDP();
    //@}
    
    /** @name Accessors*/
    //@{
    const CNetworkHost& GetHostInformation() const;
    //@}
    
    /** @name Manipulator*/
    //@{
    Bool    Bind( UInt16 port );
    Bool    Listen( UInt16 nbConnect );
    Bool    Accept( CSocketUDP& acceptedSocket );
    Int32   Send( CSocketUDP& toSocket, Byte* buffer, UInt32 size );
    Int32   Receive( CSocketUDP& fromSocket, Byte* buffer, UInt32 size );
    Bool    Connect( CNetworkHost& distantHost );
    //@}
    
private:

    // DataTypes

    // Methods  

    // Attributes
    CImplSocketUDP  m_Impl;

};      

}

#endif
