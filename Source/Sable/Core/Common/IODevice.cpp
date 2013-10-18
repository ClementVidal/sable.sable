#include <Sable/Core/Common/IODevice.h>

CIODevice::CIODevice( )
{
    m_AccessMode = nAccesMode_None;
}

CIODevice::~CIODevice( )
{
}

EAccesMode CIODevice::GetAccesMode() const
{
    return m_AccessMode;
}

Bool CIODevice::Open( EAccesMode acces )
{
    m_AccessMode = acces;
    return TRUE;
}

Void CIODevice::Close()
{
    m_AccessMode = nAccesMode_None;
}


Bool CIODevice::ReadChar( Char& c )
{
	return Read( &c, 1 );
}

Int32 CIODevice::ReadLine( Char* buffer, Int32 bufferLen )
{
	Int32 i=0;

	while( i<bufferLen )
	{
		Char tmp;
		if( ! ReadChar( tmp ) )
		{
			return -1;
		}

		if( tmp == '\n' )
		{
			buffer[i] = 0;
			return i;
		}
		
		buffer[i] = tmp;
		i++;
	}

	return i;
}