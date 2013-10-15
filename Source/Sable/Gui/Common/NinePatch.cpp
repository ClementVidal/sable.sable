#include <Sable\Gui\Common\NinePatch.h>

#include <Sable\Core\Math\Primitives.h>
#include <Sable\Core\File\File.h>

using namespace Sable;

CGuiNinePatch::SHeader::SHeader()
{
	m_FourCC[0] = 'D';
	m_FourCC[1] = '9';
	m_FourCC[2] = 'P';
	m_FourCC[3] = 'A';

	m_Version = 1;
}

CGuiNinePatch::SInfo::SInfo()
{
	HStretchableEnd = 512;
	HStretchableStart = 512;
	VStretchableEnd = 32;
	VStretchableStart = 0;
}

CGuiNinePatch::CGuiNinePatch( CMemoryHeap* heap )
{

}

CGuiNinePatch::~CGuiNinePatch()
{
}

Bool CGuiNinePatch::SetRawDataFromFile( const CFilePath& path )
{
	if( path.Exist() == FALSE )
		return FALSE;

	CFile file( path );
	return SetRawData( file );
}

Bool CGuiNinePatch::SetRawData( CIODevice& device, UInt32 byteCount )
{
	return TRUE;
}

CTexture2D* CGuiNinePatch::GetTexture() const
{
	return m_Texture;
}