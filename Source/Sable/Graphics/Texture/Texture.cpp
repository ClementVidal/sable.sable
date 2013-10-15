#include <Sable\Graphics\Texture\Texture.h>
#include <Sable\Media\Dds\DDSFile.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CTexture, CManagedObject );

CTexture::CTexture( )
{
    m_MinFilteringMode = nStateFilter_Linear;
    m_MagFilteringMode = nStateFilter_Linear;
    m_AdressMode = nStateAddress_Wrap;
}

CTexture::CTexture( const CTexture& other )
{
    DebugError( "Not Implemented" );
}

CTexture& CTexture::operator=( const CTexture& other )
{
    DebugError( "Not Implemented" );
    return *this;
}

CTexture::~CTexture()
{
}

Void CTexture::SetTextureInfo( const CTextureInfo& info )
{
    m_TextureInfo = info;
}

const CTextureInfo& CTexture::GetTextureInfo()const
{
    return m_TextureInfo;
}

Void CTexture::SetAdressMode( const EStateAddress state )
{
    m_AdressMode = state;
}

EStateAddress CTexture::GetAdressMode( ) const 
{
    return m_AdressMode;
}

Void CTexture::SetMagFilterMode( const EStateFilter state )
{
    m_MagFilteringMode = state;
}

EStateFilter CTexture::GetMagFilterMode( ) const 
{
    return m_MagFilteringMode;
}

Void CTexture::SetMinFilterMode( const EStateFilter state )
{
    m_MinFilteringMode = state;
}

EStateFilter CTexture::GetMinFilterMode( ) const 
{
    return m_MinFilteringMode;
}
