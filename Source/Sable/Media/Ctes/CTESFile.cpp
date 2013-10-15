#include <Sable\Media\Ctes\CTESFile.h>

#include <Sable\Core\Math\Primitives.h>
#include <Sable\Core\Common\IODevice.h>


using namespace Sable;

CCTESFile::CCTESFile( CMemoryHeap* heap ) :
	CImageFile(),
	m_Data( heap )
{
	
}

CCTESFile::~CCTESFile()
{
}

const CTextureInfo& CCTESFile::GetTextureInfo( ) const
{
	return m_TextureInfo;
}

Bool CCTESFile::GetIsStandardTexture() const
{
	return FALSE;
}

Bool CCTESFile::GetIsCubeTexture() const
{
	return FALSE;
}

const Byte*	 CCTESFile::GetSurfaceData( UInt32 surfaceType, UInt32 mipMapIndex, UInt32& byteCount ) const
{
	return NULL;
}

Bool CCTESFile::GetIsVolumeTexture() const
{
	return FALSE;
}

Void CCTESFile::SetSurfaceData( UInt32 surfaceIndex, UInt32 mipMapIndex, const Byte* data, UInt32 byteCount ) const
{

}