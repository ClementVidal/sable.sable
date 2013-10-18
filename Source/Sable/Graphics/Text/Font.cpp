#include <Sable/Graphics/Text/Font.h>

#include <Sable/Core/File/Header.h>

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CTextFont, CManagedObject );

CTextFont::SChar::SChar()
{
	BoundX = 0;
	BoundY = 0;
	BoundWidth = 0;
	BoundHeight = 0;
	OffsetX = 0;
	OffsetY = 0;
	CharWidth = 0;
}

CTextFont::SHeader::SHeader()
{
	m_FourCC[0] = 'D';
	m_FourCC[1] = 'F';
	m_FourCC[2] = 'N';
	m_FourCC[3] = 'T';

	m_Version = 1;
}

CTextFont::SInfo::SInfo()
{
	BitmapWidth = 512;
	BitmapHeight = 512;
	FontSize = 32;
	FontAttributes = 0;
	LineSpacing = 0;
}

Bool CTextFont::SInfo::Serialize( CPersistentArchive& ar )
{
    Int16 version = 0;

    if( ar.BeginScope( WT("Info"), version ) == 0 )
    {
        ar.Serialize( BitmapWidth, WT("BitmapWidth" ) );
        ar.Serialize( BitmapHeight, WT("BitmapHeight" ) );
        ar.Serialize( FontSize, WT("FontSize" ) );
        ar.Serialize( FontAttributes, WT("FontAttributes" ) );
        ar.Serialize( LineSpacing, WT("LineSpacing" ) );
        ar.Serialize( FaceName, WT("FaceName" ) );
        ar.EndScope();
    }

    return TRUE;
}

Bool CTextFont::SHeader::IsValidFourCC() const
{
	return m_FourCC[0] == 'D' && m_FourCC[1] == 'F' && m_FourCC[2] == 'N' && m_FourCC[3] == 'T';
}

UInt32 CTextFont::SHeader::GetVersion() const
{
	return m_Version;
}

CTextFont::CTextFont()
{
	m_CharDef.SetItemCount(256);
}

CTextFont::~CTextFont()
{

}

UInt32 CTextFont::GetLineSpacing() const
{
	return m_Info.LineSpacing;
}

Bool CTextFont::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;

	if( ar.BeginScope( WT("TextFont"), version ) == 0 )
	{
		ar.Serialize( m_Info, WT("Info") );
        ar.Serialize( (Byte*)m_CharDef.GetBuffer(), m_CharDef.GetByteCount(), WT("CharDef") );
        ar.Serialize( m_Texture, WT("Texture") );
		ar.EndScope();
	}

	return CManagedObject::Serialize( ar );
}

Bool CTextFont::Load( const CFilePath& path )
{
    if( path.Exist() == FALSE )
        return FALSE;

    CFile file( path );
    if( !SetRawData( file ) )
        return FALSE;

    return Load();
}

Bool CTextFont::Load( )
{
    m_Texture.Load();

    m_Shader.Load(  CoreManager.GetFileSystem().GetFilePath( "System/Shader", "System/Text2D.vsh" ),
                    CoreManager.GetFileSystem().GetFilePath( "System/Shader", "System/Text2D.psh" ),
                    CFilePath() );

	CStatesBlend::SDesc blendDesc;
	blendDesc.BlendEnable[0] = TRUE;
	blendDesc.SrcColorBlend = nStateBlend_SrcAlpha;
	blendDesc.DstColorBlend = nStateBlend_InvSrcAlpha;
	m_BlendStates.Acquire( blendDesc );

	CStatesDepthStencil::SDesc dsDesc;
	dsDesc.DepthTestEnable = FALSE;
	dsDesc.DepthWriteEnable = FALSE;
    m_DepthStencilStates.Acquire( dsDesc );

    m_Shader.SetBlendStates( &m_BlendStates );
    m_Shader.SetDepthStencilStates( &m_DepthStencilStates );

	CStatesSampler::SDesc ssDesc;
	ssDesc.MinFilter = nStateFilter_Point;
	ssDesc.MagFilter = nStateFilter_Point;
	ssDesc.MipFilter = nStateFilter_Point;
	m_SamplerState.Acquire( ssDesc );

	CShaderParameter* samplerParam = m_Shader.GetParameter( "InputSampler" );
	if( samplerParam )
		samplerParam->SetValue( m_SamplerState );

	CShaderParameter* sizeParam = m_Shader.GetParameter( "TextureSize" );
	if( sizeParam )
		sizeParam->SetValue( CVector2f( (Float32)m_Texture.GetWidth(), (Float32)m_Texture.GetWidth() ) );

    return TRUE;
}

Bool CTextFont::SetRawDataFromFile( const CFilePath& path )
{
    if( path.Exist() == FALSE )
        return FALSE;

    CFile file( path );
    return SetRawData( file );
}

Bool CTextFont::SetRawData( CIODevice& device, UInt32 byteCount )
{
    SHeader header;
    CFile file;
    Int32 index;
    SChar def;

    if( !device.Read(&header, sizeof( SHeader ) ) )
        return FALSE;

    if( header.IsValidFourCC() == FALSE )
        return FALSE;

    if( header.GetVersion() == 1 )
    {
        if( !device.Read(&m_Info, sizeof( SInfo ) ) )
            return FALSE;
    }

    // Read offset table
    for(index=0; index<256; index++)
    {
        device.Read(&def, sizeof(SChar));
        m_CharDef[index] = def;
    }

    // Read bitmap
    m_Texture.SetTextureInfo( CTextureInfo(m_Info.BitmapWidth, m_Info.BitmapHeight, nTextureFormat_A8, 1) );
    if( !m_Texture.SetRawData( device, m_Info.BitmapHeight * m_Info.BitmapWidth ) )
        return FALSE;

    return TRUE;
}

CShader& CTextFont::GetShader()
{
	return m_Shader;
}