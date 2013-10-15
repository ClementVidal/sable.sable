#include <Sable\Graphics\Texture\TextureInfo.h>

using namespace Sable;

CTextureInfo::CTextureInfo()
{
    Width = 0;
    Height = 0;
    SliceCount = 0;
    Format = nTextureFormat_None;
	Type = nTextureType_None;
    MipMapCount = 0;
}

CTextureInfo::CTextureInfo( UInt32 width, UInt32 height, ETextureFormat format, UInt8 mipmapCount, ETextureType type )
{
    Width = width;
    Height = height;
    SliceCount = 0;
    Format = format;
	Type = type;
    MipMapCount = mipmapCount;
}

CTextureInfo::CTextureInfo( UInt32 width, UInt32 height, UInt32 sliceCount, ETextureFormat format, UInt8 mipmapCount )
{
    Width = width;
    Height = height;
    SliceCount = SliceCount;
    Format = format;
	Type = nTextureType_3D;
    MipMapCount = mipmapCount;
}

UInt32 CTextureInfo::GetTextureByteCount( ) const
{
    UInt32 size = 0;

	if( Type == nTextureType_Cube )
		size = GetSurfaceByteCount() * 6;
	else if( Type == nTextureType_3D )
		size = GetSurfaceByteCount() * SliceCount;
	else 
		size = GetSurfaceByteCount();

    return size;
}

UInt32 CTextureInfo::GetSurfaceByteCount( ) const
{
	UInt32 i=0;
	UInt32 size = 0;

	for(i=0;i<MipMapCount;i++)
	{
		size += GetMipMapByteCount( i );
	}

	return size;
}

UInt32 CTextureInfo::GetMipMapWidth( UInt32 index ) const
{
	return Width / (UInt32)MathPow( 2.0f, (Float32)index );
}

UInt32 CTextureInfo::GetMipMapHeight( UInt32 index ) const
{
	return Height / (UInt32)MathPow( 2.0f, (Float32)index );
}

UInt32 CTextureInfo::GetMipMapByteCount( UInt32 index ) const
{
    UInt32	size = 0;

    if( ( Format == nTextureFormat_A16B16G16R16F)  ) 
    {
        size = 8 * Height * Width;
        size /= ( UInt32 ) MathPow( 4.0f,  ( Float32 ) index );
    }
    else if( Format == nTextureFormat_DXT1  ) 
    {
        size = MathMax( 1, Width / 4 ) * MathMax( 1, Height / 4 ) * 8;
        size /= ( UInt32 ) MathPow( 4.0f,  ( Float32 ) index );
        if( size < 8 )
            size = 8;
    }
    else if( ( Format == nTextureFormat_DXT2 ) ||
        ( Format == nTextureFormat_DXT3 ) ||
        ( Format == nTextureFormat_DXT4 ) ||
        ( Format == nTextureFormat_DXT5 ) 
        ) 
    {
        size = MathMax( 1, Width / 4 ) * MathMax( 1, Height / 4 ) * 16;
        size /= ( UInt32 ) MathPow( 4.0f,  ( Float32 ) index );
        if( size < 16 )
            size = 16;
    }
    else
    {
        size = (UInt32) Width / (UInt32)MathPow( 2.0f, (Float32)index ) * 
                        Height / (UInt32)MathPow( 2.0f, (Float32)index ) * GetPixelByteCount();
    }

    DebugAssert( size != 0 );

    return size;
}

UInt32 CTextureInfo::GetPixelByteCount() const
{
	switch( Format )
	{
	case nTextureFormat_A8:
		return 1;
	case nTextureFormat_L8:
		return 1;
	case nTextureFormat_R5G6B5:
		return 2;
	case nTextureFormat_R8G8B8A8:
		return 4;
	case nTextureFormat_X8R8G8B8:
		return 4;
	case nTextureFormat_D24S8:
		return 3;
	case nTextureFormat_R16F:
		return 2;
	case nTextureFormat_A16B16G16R16F:
		return 8;
	case nTextureFormat_G16R16F:
		return 4;
    case nTextureFormat_DXT1:
    case nTextureFormat_DXT2:
    case nTextureFormat_DXT3:	
    case nTextureFormat_DXT4:
    case nTextureFormat_DXT5:
	case nTextureFormat_ETC:
	case nTextureFormat_ATC:
	case nTextureFormat_3DC:
	case nTextureFormat_PVRTC:
        DebugError("Cannot compute compressed format pixel size");
        return 0;
	}

	DebugError("Invalid pixel format");
	return 0;
}

Bool CTextureInfo::IsValid() const
{
    return Format != nTextureFormat_None && Width != 0 && Height != 0;
}

Bool CTextureInfo::Serialize( CPersistentArchive& ar )
{
    Int16 version = 0;

    if( ar.BeginScope( WT("TextureInfo" ), version ) == version )
    {
        ar.Serialize( Width, WT("Width" ) );
        ar.Serialize( Height, WT("Height" ) );
        ar.Serialize( SliceCount, WT("SliceCount" ) );
        ar.Serialize( (UInt32&)Format, WT("Format" ) );
		ar.Serialize( MipMapCount, WT("MipMapCount" ) );
		// 'If' used only for compatibility... remove asap
		if( !ar.Serialize( (UInt32&)Type, WT("Type" ) ) )
			Type = nTextureType_2D;

        return ar.EndScope();
    }
    return FALSE;
}

UInt32  CTextureInfo::GetLinePitch( UInt32 index ) const
{
	UInt32 mipMapWidth = Width / ( UInt32 ) MathPow( 2.0f,  ( Float32 ) index );
    if( Format == nTextureFormat_DXT1 )
        return MathMax( 1, ((mipMapWidth+3)/4) ) * 8;
    else if( Format == nTextureFormat_DXT2 || Format == nTextureFormat_DXT3 || Format == nTextureFormat_DXT4 || Format == nTextureFormat_DXT5 )
        return MathMax( 1, ((mipMapWidth+3)/4) ) * 16;

    return ( mipMapWidth * GetPixelByteCount() );
}