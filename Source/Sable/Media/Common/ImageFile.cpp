#include <Sable\Media\Common\ImageFile.h>

#include <Sable\Core\Math\Primitives.h>
//#include <Sable\Core\File\System.h>
#include <Sable\Media\Dds\DDSFile.h>
#include <Sable\Media\Tga\TGAFile.h>

using namespace Sable;

CImageFile::CImageFile()
{
}

CImageFile::~CImageFile()
{
}

UInt32 CImageFile::GetPixelByteCount( const ETextureFormat pixelFormat ) const
{
	switch( pixelFormat )
	{

	case nTextureFormat_A2R10G10B10:
		return 4;

	case nTextureFormat_R8G8B8A8:
	case nTextureFormat_X8R8G8B8:
		return 4;

	case nTextureFormat_R5G6B5:
		return 2;

	case nTextureFormat_R8G8B8:
		return 3;

	case nTextureFormat_A8:
		return 1;

	case nTextureFormat_L8:
		return 1;
	}

//	DebugLogWarning( "Invalid Pixel Format" );

	return 0;
}

Bool CImageFile::Load( const CFilePath& fileName, Bool decompress )
{
    CFile file;
    Bool returnCode;

    returnCode = file.Open( fileName, nAccesMode_Read );

    if(!returnCode)
        return FALSE;

    return LoadInternal( file, decompress );
}

CColor CImageFile::GetPixel( UInt32 surfaceType, UInt32 mipMapIndex, UInt32 x, UInt32 y )
{
    ETextureFormat format = GetTextureInfo().Format;
    UInt32 byteCount = 0;
    UInt32 bytePerPixel = GetPixelByteCount( format );
    const Byte* rawData = GetSurfaceData( surfaceType, mipMapIndex, byteCount );

    const Byte* pixelData = &rawData[ (y*GetTextureInfo().Width*bytePerPixel) + (x*bytePerPixel) ];

    return ConvertPixel( pixelData, format );
}

CColor CImageFile::ConvertPixel( const Byte* pixelData, ETextureFormat fmt )
{
    if( fmt == nTextureFormat_R8G8B8A8 || fmt == nTextureFormat_X8R8G8B8)
    {
        return CColor( pixelData[0]/255.0f, pixelData[1]/255.0f, pixelData[2]/255.0f, pixelData[3]/255.0f );
    }
    else  if( fmt == nTextureFormat_R8G8B8 )
    {
        return CColor( 1.0f, pixelData[1]/255.0f, pixelData[2]/255.0f, pixelData[3]/255.0f );
    }
    else  if( fmt == nTextureFormat_R5G6B5 )
    {
        UInt16 data = *((UInt16*)pixelData);
        Float32 r = ((data & 0xf800 ) >> 11) / 32.0f;
        Float32 g = ((data & 0x07e0 ) >> 5 )/ 64.0f;
        Float32 b = ((data & 0x001f ) )/ 32.0f;
        return CColor( 1.0f, r, g, b );
    }
    else  if( fmt == nTextureFormat_A8 || fmt == nTextureFormat_L8 )
    {
        return CColor( 1.0f, pixelData[0] / 255.0f, pixelData[0] / 255.0f, pixelData[0] / 255.0f );
    }
    return CColor::Black;
}