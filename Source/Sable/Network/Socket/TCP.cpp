#include <Sable/Network/Socket/TCP.h>

using namespace Sable;

CSocketTCP::CSocketTCP( Bool isBlocking ) :
    m_Impl( *this, isBlocking )
{
	m_IsBlocking = isBlocking;
}

CSocketTCP::~CSocketTCP()
{

}

CImplSocketTCP& CSocketTCP::GetImpl()
{
	return m_Impl;
}

Bool CSocketTCP::Bind( UInt16 port )
{
	return m_Impl.Bind( port );
}

Bool CSocketTCP::Listen( UInt16 nbConnect )
{
	return m_Impl.Listen( nbConnect );
}

Bool CSocketTCP::Accept( CSocketTCP& acceptedSocket )
{
	return m_Impl.Accept( acceptedSocket );
}

Int32 CSocketTCP::Send( const Byte* buffer, UInt32 size )
{
	return m_Impl.Send( buffer, size );
}

Int32 CSocketTCP::Receive( Byte* buffer, UInt32 size )
{
	return m_Impl.Receive( buffer, size );
}

Bool CSocketTCP::Connect( CNetworkHost& distantHost, UInt16 port  )
{
	return m_Impl.Connect( distantHost, port );
}