#include <Sable/Network/Socket/Impl/Msw/TCP.h>

#include <Sable/Core/Debug/Header.h>

CImplMswSocketTCP::CImplMswSocketTCP( CSocketTCP& publicSocket, Bool isBlocking ) : 
	CImplStubSocketTCP( publicSocket, isBlocking )
{
	m_Socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if( m_Socket == INVALID_SOCKET )
	{
		DebugLogWarning( "CImplMswSocketTCP::CImplMswSocketTCP - Failed to create socket");
	}

	if( isBlocking )
	{
		DWORD nonBlocking = 1;
		if ( ioctlsocket( m_Socket, FIONBIO, &nonBlocking ) != 0 )
		{
			DebugLogWarning( "CImplMswSocketTCP::CImplMswSocketTCP - Failed to set in blocking mode");
			return;
		}
	}
}

CImplMswSocketTCP::~CImplMswSocketTCP()
{
	closesocket(m_Socket);
}

Bool CImplMswSocketTCP::Bind( UInt16 port )
{
	sockaddr_in address ;

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(port);

	if( bind( m_Socket, (struct sockaddr*)&address,	sizeof(sockaddr_in) )  == SOCKET_ERROR ) 
	{
		DebugLogWarning( "CImplMswSocketTCP::Bind - Failed to bind socket");
		return FALSE;
	}

	return TRUE;
}

Bool CImplMswSocketTCP::Listen( UInt16 nbConnect )
{
	if( listen( m_Socket, nbConnect ) == SOCKET_ERROR) 
	{
		return FALSE;
	}

	return TRUE;
}

Bool CImplMswSocketTCP::Accept( CSocketTCP& acceptedSocket )
{
	sockaddr_in acceptedConnexion;
	Int32 len = sizeof( sockaddr_in );

	SOCKET incoming = accept(m_Socket,(struct sockaddr*)&acceptedConnexion, &len);
	if( incoming == INVALID_SOCKET )
	{
		return FALSE;
	}

	((CImplMswSocketTCP&)acceptedSocket.GetImpl()).m_Socket = incoming;

	return TRUE;
}

Int32 CImplMswSocketTCP::Send( const Byte* buffer, UInt32 size )
{
	Int32 sendedBytes = 0;
	sendedBytes = send( m_Socket, (const char*) buffer, size, 0);
	return sendedBytes;
}

Int32 CImplMswSocketTCP::Receive( Byte* buffer, UInt32 size )
{
	Int32 recvBytes = 0;
	recvBytes = recv( m_Socket, (char*) buffer, size, 0 );
	if( recvBytes < 0 )
	{
		int errorCode = WSAGetLastError();
		if( errorCode == WSAEWOULDBLOCK )
		{
			return -2;
		}

		DebugLogError( "CImplMswSocketTCP::Receive - Failed to receive data");
		return -1;
	}

	return recvBytes;
}

Bool CImplMswSocketTCP::Connect( CNetworkHost& distantHost, UInt16 port ) 
{
	sockaddr_in addr; 
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = distantHost.GetIPAddressAsUInt32();
	addr.sin_port = htons( port );
	if( connect( m_Socket, (SOCKADDR*) &addr, sizeof( sockaddr_in ) ) == SOCKET_ERROR)
	{
		return FALSE;
	}

	return TRUE;
}