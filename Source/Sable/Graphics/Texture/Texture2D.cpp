#include <Sable\Graphics\Texture\Texture2D.h>

#include <Sable\Media\Dds\DDSFile.h>
#include <Sable\Media\Tga\TGAFile.h>
#include <Sable\Core\Collection\Array.h>
#include <Sable\Graphics\Texture\TextureInfo.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CTexture2D, CTexture );

CTexture2D::CTexture2D( )
{
}

const CImplTexture2D& CTexture2D::GetImpl() const
{
	return m_Impl;
}

CTexture2D::~CTexture2D()
{
}

Bool CTexture2D::Load( )
{
    if( GetTextureInfo().IsValid() == FALSE )
        return FALSE;

    if( !Create( GetTextureInfo(), m_RawData.GetBuffer() ) )
        return FALSE;

    return TRUE;
}

Bool CTexture2D::SetRawData( CIODevice& device, UInt32 byteCount )
{
    if( byteCount == 0 )
        m_RawData.SetItemCount( device.GetSize() );
    else
        m_RawData.SetItemCount( byteCount );

    return device.Read( m_RawData.GetBuffer(), byteCount );
}

Bool CTexture2D::SetRawDataFromFile( const CFilePath& path )
{
    if( path.Exist() == FALSE )
        return FALSE;

    CoreManager.GetMemoryManager().GetStackHeap().PushMarker();
    {
        CImageFile* imageFile = NULL;
        CDDSFile ddsFile;
        CTGAFile tgaFile( &CoreManager.GetMemoryManager().GetStackHeap() );

        UInt32 offset = 0;
        Byte* destinationdata;
        UInt8 index;
        Char ext[6];

        path.GetExtension( ext, 6 );
        StringToLower( ext, ext, 6 );

        if( StringCompare( ext, "tga" ) == 0 )
            imageFile = &tgaFile;
        else if( StringCompare( ext, "dds" ) == 0 )
            imageFile = &ddsFile;

        if( imageFile && !imageFile->Load( path ) )
        {
            CoreManager.GetMemoryManager().GetStackHeap().PopMarker();
            return FALSE;
        }

        DebugAssert( imageFile->GetIsStandardTexture() );

        SetTextureInfo( imageFile->GetTextureInfo() );

        m_RawData.SetItemCount( GetTextureInfo().GetTextureByteCount() );
        destinationdata = m_RawData.GetBuffer();

        for( index = 0 ; index < GetTextureInfo().MipMapCount; index++)
        {
            UInt32 mipMapSize;
            const Byte* srcData = imageFile->GetSurfaceData( 0, index, mipMapSize );

            MemoryCopy( srcData, destinationdata + offset, mipMapSize );
            offset += mipMapSize;
        }
    }

    CoreManager.GetMemoryManager().GetStackHeap().PopMarker();

    return TRUE;
}

Bool CTexture2D::Load( const CFilePath& path )
{
    if( !SetRawDataFromFile( path ) )
        return FALSE;

    return Load();
}

Void* CTexture2D::Lock( UInt8 mipmaplevel, UInt32& pitch )
{
	return m_Impl.Lock( mipmaplevel, nBufferAcces_Write, pitch );
}

Void* CTexture2D::Lock( UInt8 mipmaplevel )
{
    UInt32 pitch;
    return m_Impl.Lock( mipmaplevel, nBufferAcces_Write, pitch );
}

Void CTexture2D::UnLock( )
{
	m_Impl.UnLock( );
}


UInt32 CTexture2D::GetWidth() const
{
    return GetTextureInfo().Width;
}

UInt32 CTexture2D::GetHeight() const
{
    return GetTextureInfo().Height;
}

UInt32 CTexture2D::GetMipMapCount() const
{
    return GetTextureInfo().MipMapCount;
}


/**
Create a texture withot loading it from a file.
\param info Information regarding the texture to create ( size format ... )
\param data Optional buffer to raw data used to fill the buffer
\return TRUE if function succeed
*/
Bool CTexture2D::Create( const CTextureInfo& info, const Byte* data )
{	
	if( data )
		m_Impl.Initialize( info, FALSE, data );
	else
		m_Impl.Initialize( info, TRUE, NULL );

	SetTextureInfo( info );

	return TRUE;
}

Bool CTexture2D::Serialize( CPersistentArchive& ar )
{
    Int16 version = 0;
    CTextureInfo textureInfo = GetTextureInfo();

    if( ar.BeginScope( WT("Texture2D" ), version ) == version )
    {
        ar.Serialize( textureInfo, WT("TextureInfo" ) );

        UInt32 byteCount = m_RawData.GetItemCount();
        ar.Serialize( byteCount, WT("RawDataSize" ) );
        if( ar.IsLoading() )
        {
            m_RawData.SetItemCount( byteCount );
        }

        ar.Serialize( m_RawData.GetBuffer(), byteCount, WT("RawData" ) );

        if( ar.IsLoading() )
        {
            SetTextureInfo( textureInfo );
            Load();
        }

        ar.EndScope();

        return CManagedObject::Serialize( ar );
    }
    return FALSE;
}
