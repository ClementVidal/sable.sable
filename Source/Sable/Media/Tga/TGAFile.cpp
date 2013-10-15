#include <Sable\Media\Tga\TGAFile.h>

#include <Sable\Core\Math\Primitives.h>
#include <Sable\Core\Common\IODevice.h>
#include <Sable\Media\Tga\TGAFileData.h>

#define BUFFER_SIZE 2048

using namespace Sable;

CTGAFile::CTGAFile( CMemoryHeap* heap ) :
	CImageFile(),
	m_SurfaceTable( (CMemoryHeap*)heap )
{

}

CTGAFile::~CTGAFile()
{
}

UInt8 CTGAFile::GetMipMapCount( ) const
{
	return 1;
}

const CTextureInfo& CTGAFile::GetTextureInfo( ) const
{
	return m_TextureInfo;
}

const Byte* CTGAFile::GetSurfaceData( UInt32 surfaceType, UInt32 mipMapIndex, UInt32& byteCount ) const
{
	const Byte* ptr = m_SurfaceTable.GetBuffer();
	byteCount = m_SurfaceTable.GetItemCount();
	return ptr;
}

ETextureFormat CTGAFile::GetPixelFormat( const ETGAFileHeader& header ) const
{
	switch (header.ImageType)
	{
		case 3:  /* Grayscale 8 bits */
		case 11: /* Grayscale 8 bits (RLE) */
		case 1:  /* 8 bits color index */
		case 9:  /* 8 bits color index (RLE) */
		case 10: /* BGR 16-24-32 bits (RLE) */
			break;

		case 2:  /* BGR 16-24-32 bits */
		{
			/* 8 bits and 16 bits images will be converted to 24 bits */
			if (header.PixelDepth == 16)
			{
				return nTextureFormat_R5G6B5;
			}
			else if(header.PixelDepth == 24) /* 24 bits */
			{
				return nTextureFormat_R8G8B8;
			}
			else if(header.PixelDepth == 32)/* 32 bits */
			{
				return nTextureFormat_R8G8B8A8;
			}

			break;
		}
	}

	return nTextureFormat_None;
}

Bool CTGAFile::LoadInternal( CIODevice& ioDevice, Bool decompress )
{
    ETGAFileHeader header;

	ioDevice.Read( &header, sizeof( ETGAFileHeader ) );

	m_TextureInfo.MipMapCount = 1;
	m_TextureInfo.Format = GetPixelFormat( header );
	if( m_TextureInfo.Format == nTextureFormat_None )
		return FALSE;

    m_TextureInfo.Width = header.Width;
    m_TextureInfo.Height = header.Height;
    m_TextureInfo.SliceCount = 0;

	ReadStandardTexture( ioDevice, header );

    return TRUE;
}

Void CTGAFile::ReadStandardTexture( CIODevice& ioDevice, const ETGAFileHeader& header )
{    
	UInt8 bpp = GetPixelByteCount( m_TextureInfo.Format );
	Byte buffer[BUFFER_SIZE];
	Int32 byteLeft = 0;
	Int32 byteToProcess = 0;

	if( m_TextureInfo.Format == nTextureFormat_R8G8B8 )
	{
		bpp = 4;
	}
	m_SurfaceTable.SetItemCount( bpp * m_TextureInfo.Width * m_TextureInfo.Height );

	UInt32 i;

	Byte* dstBuffer = m_SurfaceTable.GetBuffer();

	if( m_TextureInfo.Format == nTextureFormat_R5G6B5 )
	{
		UInt16 color;
		byteToProcess = 2;
		for(i=0;i<m_TextureInfo.Width * m_TextureInfo.Height;i++)
		{
			RefillBuffer( ioDevice, buffer, byteToProcess, byteLeft );

			((Byte*)&color)[0] = buffer[BUFFER_SIZE - byteLeft];
			((Byte*)&color)[1] = buffer[BUFFER_SIZE - byteLeft + 1];

			/* Convert BGR to RGB */
			dstBuffer[(i * 3) + 0] = (Byte)(((color & 0x7C00) >> 10) << 3);
			dstBuffer[(i * 3) + 1] = (Byte)(((color & 0x03E0) >>  5) << 3);
			dstBuffer[(i * 3) + 2] = (Byte)(((color & 0x001F) >>  0) << 3);

			byteLeft -= byteToProcess;
		}
	}
	else if( m_TextureInfo.Format == nTextureFormat_R8G8B8 )
	{
		byteToProcess = 3;
		for(i=0;i<m_TextureInfo.Width * m_TextureInfo.Height;i++)
		{
			RefillBuffer( ioDevice, buffer, byteToProcess, byteLeft );

			/* Read and convert BGR to RGB */
			dstBuffer[(i * 4) + 0] = buffer[BUFFER_SIZE - byteLeft + 0];
			dstBuffer[(i * 4) + 1] = buffer[BUFFER_SIZE - byteLeft + 1];
			dstBuffer[(i * 4) + 2] = buffer[BUFFER_SIZE - byteLeft + 2];
			dstBuffer[(i * 4) + 3] = 255;

			byteLeft -= byteToProcess;
		}
		m_TextureInfo.Format = nTextureFormat_R8G8B8A8;
	}
	else if( m_TextureInfo.Format == nTextureFormat_R8G8B8A8 )
	{
		byteToProcess = 4;
		for(i=0;i<m_TextureInfo.Width * m_TextureInfo.Height;i++)
		{
			RefillBuffer( ioDevice, buffer, byteToProcess, byteLeft );

			/* Read and convert BGRA to RGBA */
			dstBuffer[(i * 4) + 0] = buffer[BUFFER_SIZE - byteLeft + 2];
			dstBuffer[(i * 4) + 1] = buffer[BUFFER_SIZE - byteLeft + 1];
			dstBuffer[(i * 4) + 2] = buffer[BUFFER_SIZE - byteLeft + 0];
			dstBuffer[(i * 4) + 3] = buffer[BUFFER_SIZE - byteLeft + 3];

			byteLeft -= byteToProcess;
		}
	}
}

Void CTGAFile::RefillBuffer( CIODevice& ioDevice, Byte* buffer, Int32 byteToProcess, Int32& byteLeft )
{
	if( ( byteLeft - byteToProcess ) <= 0)
	{
		if( byteLeft )
			MemoryCopy( buffer + BUFFER_SIZE - byteLeft, buffer, byteLeft );

		ioDevice.Read( buffer + byteLeft, BUFFER_SIZE - byteLeft );
		byteLeft = BUFFER_SIZE;
	}
}

Bool CTGAFile::GetIsStandardTexture() const
{
	return TRUE;
}

Bool CTGAFile::GetIsCubeTexture() const
{
	return FALSE;
}

Bool CTGAFile::GetIsVolumeTexture() const
{
	return FALSE;
}