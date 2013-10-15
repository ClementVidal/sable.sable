#include <Sable\Graphics\Texture\TextureCube.h>

#include <Sable\Media\Dds\DDSFile.h>
#include <Sable\Core\Collection\Array.h>
#include <Sable\Graphics\Texture\TextureInfo.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CTextureCube, CTexture );

CTextureCube::CTextureCube( )
{
}

CTextureCube::~CTextureCube()
{
}

const CImplTextureCube& CTextureCube::GetImpl() const
{
	return m_Impl;
}

Bool CTextureCube::Load( )
{
    if( GetTextureInfo().IsValid() == FALSE )
        return FALSE;

    if( !Create( GetTextureInfo(), m_RawData.GetBuffer() ) )
        return FALSE;

    return TRUE;
}

Bool CTextureCube::Create( const CTextureInfo& info, const Byte* data )
{	
    DebugAssert( data );

    m_Impl.Initialize( info, data );

    SetTextureInfo( info );

    return TRUE;
}

Bool CTextureCube::SetRawData( CIODevice& device, UInt32 byteCount )
{
    if( byteCount == 0 )
        m_RawData.SetItemCount( device.GetSize() );
    else
        m_RawData.SetItemCount( byteCount );

    return device.Read( m_RawData.GetBuffer(), byteCount );
}

Bool CTextureCube::SetRawDataFromFile( const CFilePath& path )
{
    if( path.Exist() == FALSE )
        return FALSE;

    CoreManager.GetMemoryManager().GetStackHeap().PushMarker();
    {
        CImageFile* imageFile = NULL;
        CDDSFile ddsFile;

        UInt32 offset = 0;
        Byte* destinationdata;
        UInt8 faceIndex, mipmapIndex;
        Char ext[6];

        path.GetExtension( ext, 6 );
        StringToLower( ext, ext, 6 );

        if( StringCompare( ext, "dds" ) == 0 )
            imageFile = &ddsFile;

        if( imageFile && !imageFile->Load( path ) )
        {
            CoreManager.GetMemoryManager().GetStackHeap().PopMarker();
            return FALSE;
        }

        DebugAssert( imageFile->GetIsCubeTexture() );

        SetTextureInfo( imageFile->GetTextureInfo() );

        m_RawData.SetItemCount( GetTextureInfo().GetTextureByteCount() );
        destinationdata = m_RawData.GetBuffer();

        for( faceIndex = 0 ; faceIndex < 6; faceIndex++)
        {
            for( mipmapIndex = 0 ; mipmapIndex < GetTextureInfo().MipMapCount; mipmapIndex++)
            {
                UInt32 mipMapSize;
                const Byte* srcData = imageFile->GetSurfaceData( faceIndex, mipmapIndex, mipMapSize );

                MemoryCopy( srcData, destinationdata + offset, mipMapSize );
                offset += mipMapSize;
            }
        }
    }

    CoreManager.GetMemoryManager().GetStackHeap().PopMarker();

    return TRUE;
}

Bool CTextureCube::Load( const CFilePath& path )
{
    if( !SetRawDataFromFile( path ) )
        return FALSE;

    return Load();
}


Bool CTextureCube::Serialize( CPersistentArchive& ar )
{
    DebugError("Not yet reimplemented since CPersistentArchive refactoring");

	if( ar.IsLoading( ) )
	{
        
	/*	// Handle relative path
		Char arDir[128];
		Char finalPath[128];
		String filePath = m_FilePath.GetPath( );
		ar.GetFilePath().GetDirectory( arDir, 128 );

		if( filePath[0] == '.' && filePath[1] == '/' )
		{
			StringAppend( arDir, filePath+2, finalPath, 128 );
			Load( finalPath );
		}
		else
		{
			Load( m_FilePath );
		}*/
	}

	return CTexture::Serialize( ar );
}
