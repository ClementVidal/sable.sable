#ifndef _SABLE_NETWORK_HOST_
#define _SABLE_NETWORK_HOST_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Network/Impl/Header.h>

namespace Sable 
{

/**
\ingroup Network
Represent a single host over the network
*/
class CNetworkHost 
{

public:

	/** @name DataTypes*/
	//@{
	//@}

    /** @name Constructor/Destructor*/
    //@{
	CNetworkHost();
    CNetworkHost( String nameOrAddress );
	~CNetworkHost();
	//@}
    
    /** @name Accessors*/
    //@{
	CImplNetworkHost&	GetImpl();
	String				GetName() const;
	UInt32				GetIPAddressAsUInt32() const;	
	String				GetIPAddressAsString() const;
    //@}
    
    /** @name Manipulator*/
    //@{
    //@}
    
private:

	// DataTypes

    // Methods	

	// Attributes
	CImplNetworkHost	m_Impl;

};	

}

#endif
