#include <Sable\Media\Dds\DDSFile.h>

#include <Sable\Core\Math\Primitives.h>
#include <Sable\Core\Common\IODevice.h>

#include <Sable\Media\DDS\Squish\Squish.h>

using namespace Sable;

CDDSFile::CDDSFile( CMemoryHeap* heap ) :
	CImageFile(),
	m_Data( heap )
{
	
}

CDDSFile::~CDDSFile()
{
}

const CTextureInfo& CDDSFile::GetTextureInfo( ) const
{
	return m_TextureInfo;
}

const Byte* CDDSFile::GetSurfaceData( UInt32 surfaceIndex, UInt32 mipMapIndex, UInt32& byteCount ) const
{
	UInt32 mipMapOffset = 0;
	UInt32 totalOffset = 0;
	UInt32 i = 0;

	for( i=0; i<mipMapIndex; i++ )
	{
		mipMapOffset += m_TextureInfo.GetMipMapByteCount( i );
	}

	Byte* data = m_Data.GetBuffer();
	totalOffset = GetSurfaceSize() * surfaceIndex + mipMapOffset;
	DebugAssert( totalOffset <= m_Data.GetItemCount() );

	data += totalOffset;
	byteCount = m_TextureInfo.GetMipMapByteCount( mipMapIndex );

	return data;
}

UInt32 CDDSFile::GetSurfaceSize( ) const
{
	UInt32 s = 0;
	UInt32 i;

	for(i=0;i<GetMipMapCount( ); i++ )
	{
		s += m_TextureInfo.GetMipMapByteCount( i );
	}

	return s;
}


UInt32 CDDSFile::GetTextureSize( ) const
{
	UInt32 s = GetSurfaceSize( );
	UInt32 t = GetSurfaceCount( );

	return s*t;
}


UInt32 CDDSFile::GetMipMapCount( ) const
{
	if( m_Header.Flags &  nDDSConstant_DDSD_MIPMAPCOUNT)
	{
		return m_Header.MipMapCount;
	}
	
	return 1;
}

UInt32 CDDSFile::GetSurfaceCount( ) const
{
	if( m_TextureInfo.Type == nTextureType_2D )
	{
		return 1;
	}
	else if( m_TextureInfo.Type == nTextureType_Cube )
	{
		return 6;
	}
	else if( m_TextureInfo.Type == nTextureType_3D )
	{
		return m_TextureInfo.SliceCount;
	}

	DebugError("CDDSFile::GetSurfaceCount - Invalid Type");
	return 0;
}

ETextureType CDDSFile::GetTextureType( ) const
{
	if( m_Header.Caps & nDDSConstant_DDSCAPS_COMPLEX )
	{
		if( m_Header.Caps2 & nDDSConstant_DDSCAPS2_CUBEMAP )
		{
			return nTextureType_Cube;
		}
	}
	else if( m_Header.Caps2 & nDDSConstant_DDSCAPS2_VOLUME )
	{
		return nTextureType_3D;
	}
	return nTextureType_2D;
}

ETextureFormat CDDSFile::GetPixelFormat( ) const
{
	if( m_Header.PixelFormat.Flags & nDDSConstant_DDPF_FOURCC )
	{	
        Char rawBuffer[5];
        MemoryCopy( (Char*) &m_Header.PixelFormat.FourCC, rawBuffer, 4 );
        rawBuffer[4] = 0;

		if( StringCompare( rawBuffer, "DXT1" ) == 0 )
		{
			return nTextureFormat_DXT1;
		}
		else if( StringCompare( rawBuffer, "DXT5" ) == 0 )
		{
			return nTextureFormat_DXT5;
		}
		else if( m_Header.PixelFormat.FourCC == 0x71 ) 
		{
			return nTextureFormat_A16B16G16R16F;
		}
	}
	else if( (m_Header.PixelFormat.Flags & nDDSConstant_DDPF_RGB))
	{
		if( m_Header.PixelFormat.RGBBitCount == 32)
		{
			if(m_Header.PixelFormat.Flags & nDDSConstant_DDPF_ALPHAPIXELS)
			{
				return nTextureFormat_R8G8B8A8;
			}
			else
			{
				return nTextureFormat_X8R8G8B8;
			}
		}
		else if(m_Header.PixelFormat.RGBBitCount == 16)
		{
			return nTextureFormat_R5G6B5;
		}
		else if(m_Header.PixelFormat.RGBBitCount == 24)
		{
			return nTextureFormat_R8G8B8;
		}
	}
	else if( (m_Header.PixelFormat.Flags & nDDSConstant_DDPF_ALPHAPIXELS ) )
	{
		return nTextureFormat_A8;
	}
	else if( (m_Header.PixelFormat.Flags & nDDSConstant_DDPF_LUMINANCE ) )
	{
		return nTextureFormat_L8;
	}
    // Strange case that happen when saving DDS using photoshop in Alpha 8 format
	else if( (m_Header.PixelFormat.Flags & 2))
	{
        if(m_Header.PixelFormat.RGBBitCount == 8)
		{
			return nTextureFormat_A8;
		}
    }

	DebugError( "Unsuported DDS pixel format" );
	return nTextureFormat_None;
}

/**
Save a DDS file to disk. Available format and type are:
Volume texture:
- 1 mipmap par slice
- format A8R8G8B8
*/
Bool CDDSFile::Save( const CFilePath& fileName )
{
	EDDSFileHeader m_Header;
	CFile file;
	Bool returnCode;

	DebugAssert( m_TextureInfo.MipMapCount == 1 );
	DebugAssert( m_TextureInfo.Format == nTextureFormat_R8G8B8A8 );

	returnCode = file.Open( fileName, nAccesMode_ReadWrite );

	if(!returnCode)
		return FALSE;

	// Prepare m_Header
	MemoryFill( &m_Header, 0, sizeof( EDDSFileHeader ) );
	m_Header.Magic = 0x20534444; // Code for DDS
	m_Header.Size = 124;
	m_Header.Height = m_TextureInfo.Height;
	m_Header.Width = m_TextureInfo.Width;
	m_Header.PitchOrLinearSize = 0;
	m_Header.Depth = m_TextureInfo.SliceCount;
	m_Header.MipMapCount = m_TextureInfo.MipMapCount;
	m_Header.Flags = nDDSConstant_DDSD_CAPS | nDDSConstant_DDSD_HEIGHT | nDDSConstant_DDSD_WIDTH | nDDSConstant_DDSD_PIXELFORMAT;
	m_Header.PixelFormat.Flags = nDDSConstant_DDPF_RGB | nDDSConstant_DDPF_ALPHAPIXELS;
	m_Header.PixelFormat.Size = 32;
	m_Header.PixelFormat.RGBBitCount = 32;
	m_Header.PixelFormat.RBitMask = 0xff0000;
	m_Header.PixelFormat.GBitMask = 0xff00;
	m_Header.PixelFormat.BBitMask = 0xff;
	m_Header.PixelFormat.ABitMask = 0xff000000;
	m_Header.Caps = nDDSConstant_DDSCAPS_TEXTURE;
	m_Header.Caps2 = 0;

	if( m_TextureInfo.Type == nTextureType_3D )
	{
		m_Header.Flags |= nDDSConstant_DDSD_DEPTH;
		m_Header.Caps |= nDDSConstant_DDSCAPS_COMPLEX;
		m_Header.Caps2 |= nDDSConstant_DDSCAPS2_VOLUME;
	}

	// Write Header
	file.Write( &m_Header, sizeof( EDDSFileHeader ) );

	// Write Data
	file.Write( m_Data.GetBuffer(), m_Data.GetItemCount() );

	return TRUE;
}

Bool CDDSFile::LoadInternal( CIODevice& ioDevice, Bool decompress )
{
	ioDevice.Read( &m_Header, sizeof( EDDSFileHeader ) );

    Char* fourCC = (Char*)&m_Header.PixelFormat.FourCC;
    fourCC[5] = 0;

	m_TextureInfo.MipMapCount = GetMipMapCount( );
	m_TextureInfo.Format = GetPixelFormat( );
    m_TextureInfo.Width = m_Header.Width;
    m_TextureInfo.Height = m_Header.Height;
    m_TextureInfo.SliceCount = m_Header.Depth;
	m_TextureInfo.Type = GetTextureType( );

	// Setup data buffer
	m_Data.SetItemCount( GetTextureSize() );

	UInt32 r = ioDevice.Read( m_Data.GetBuffer(), m_Data.GetByteCount() );

	if( decompress )
	{
		UInt32 byteCount = 0;
		CArray<Byte> byteArray;
		byteArray.SetItemCount( m_TextureInfo.Width*m_TextureInfo.Height*4 );
		const Byte* blocks = GetSurfaceData( 0,0, byteCount );

		int format = 0;
		if( m_TextureInfo.Format == nTextureFormat_DXT5 )
			format = squish::kDxt5;
		else if( m_TextureInfo.Format == nTextureFormat_DXT3 )
			format = squish::kDxt3;
		else if( m_TextureInfo.Format == nTextureFormat_DXT1 )
			format = squish::kDxt1;

		if( format )
		{

			squish::DecompressImage( byteArray.GetBuffer(), m_TextureInfo.Width, m_TextureInfo.Height, blocks, format );

			m_TextureInfo.MipMapCount = 1;
			m_TextureInfo.Format = nTextureFormat_R8G8B8A8;
			m_Data = byteArray;

		}
	}
	
    return TRUE;
}

Bool CDDSFile::GetIsStandardTexture() const
{
	return m_TextureInfo.Type == nTextureType_2D;
}

Bool CDDSFile::GetIsCubeTexture() const
{
	return m_TextureInfo.Type == nTextureType_Cube;
}

Bool CDDSFile::GetIsVolumeTexture() const
{
	return m_TextureInfo.Type == nTextureType_3D;
}

Void CDDSFile::SetSurfaceData( UInt32 surfaceIndex, UInt32 mipMapIndex, const Byte* data, UInt32 byteCount ) const
{
	UInt32 mipMapOffset = 0;
	UInt32 totalOffset = 0;
	UInt32 i = 0;

	for( i=0; i<mipMapIndex; i++ )
	{
		mipMapOffset += m_TextureInfo.GetMipMapByteCount( i );
	}

	Byte* dstData = m_Data.GetBuffer();
	totalOffset = GetSurfaceSize() * surfaceIndex + mipMapOffset;
	DebugAssert( totalOffset <= m_Data.GetItemCount() );

	dstData += totalOffset;
	DebugAssert( m_TextureInfo.GetMipMapByteCount( mipMapIndex ) == byteCount );

	MemoryCopy( data, dstData, byteCount );

}