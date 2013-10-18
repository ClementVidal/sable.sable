#ifndef _SABLE_GRAPHICS_TEXT_FONT_
#define _SABLE_GRAPHICS_TEXT_FONT_

#include <Sable/Core/Common/Header.h>
#include <Sable/Core/ManagedObject/Ref.h>
#include <Sable/Graphics/Texture/Header.h>
#include <Sable/Graphics/Shader/Header.h>

namespace Sable
{

/**  
\ingroup GraphicsText
Text font class.
Use this class to load a font from a file.

*/
class CTextFont : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CTextFont );

public:

    /** @name Type*/
    //@{
	struct SHeader
	{
		SHeader();
		Bool IsValidFourCC() const;
		UInt32 GetVersion() const;

	private:
		Char	m_FourCC[4];
		UInt32	m_Version;
	};

	struct SInfo
	{
		SInfo();
		UInt32				BitmapWidth;
		UInt32				BitmapHeight;
		UInt32				FontSize;
		UInt32				FontAttributes;
		CStaticString<64>	FaceName;
		UInt32				LineSpacing;
        Bool	Serialize( CPersistentArchive& ar );
	};

	struct SChar
    {
		SChar();
        Int32 BoundX;
        Int32 BoundY;
        Int32 BoundWidth;
        Int32 BoundHeight;
        Int32 OffsetX;
        Int32 OffsetY;
        Int32 CharWidth;
    };
    //@}

    /** @name Constructor/destructor */
    //@{
    CTextFont();
    ~CTextFont();
    //@}

    /** @name Accessors*/
    //@{
    Bool                SetRawDataFromFile( const CFilePath& path );
	Bool				SetRawData( CIODevice& device, UInt32 byteCount = 0 );
    const CTexture2D&   GetTexture() const;
    const SChar&		GetChar( const Char i) const;
    UInt32				GetLineSpacing() const;
	UInt32				GetTextureWidth() const;
    UInt32				GetTextureHeight() const;
	CShader&			GetShader();
    //@}

    /** @name Manipulator*/
    //@{
	Bool	Serialize( CPersistentArchive& ar );
    Bool	Load();
    Bool	Load( const CFilePath& fileName );
    //@}

private:

    // Methods

    // Attributes
	SInfo				m_Info;
    CArray<SChar>       m_CharDef;
    CTexture2D		    m_Texture;	
	CShader				m_Shader;
	CStatesBlend		m_BlendStates;
	CStatesSampler		m_SamplerState;
	CStatesDepthStencil m_DepthStencilStates;

};

Inline
const CTexture2D& CTextFont::GetTexture() const
{
	return m_Texture;
}

Inline
const CTextFont::SChar& CTextFont::GetChar( const Char i) const
{
	UInt32 c = (UInt32) i;

	if( c >= m_CharDef.GetItemCount() )
		c = (UInt32) '#';

	return m_CharDef[c];
}

Inline
UInt32 CTextFont::GetTextureWidth() const
{
	return m_Texture.GetTextureInfo().Width;
}

Inline
UInt32 CTextFont::GetTextureHeight() const
{
	return m_Texture.GetTextureInfo().Height;
}

}

#endif
