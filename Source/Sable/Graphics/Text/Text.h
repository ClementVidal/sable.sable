#ifndef _SABLE_GRAPHICS_TEXT_TEXT_
#define _SABLE_GRAPHICS_TEXT_TEXT_

#include <Sable/Core/ManagedObject/Header.h>
#include <Sable/Core/Common/Header.h>
#include <Sable/Graphics/Geometry/Header.h>

namespace Sable
{

class CShader;
class CRenderer;
class CTextFont;

/**  
\ingroup GraphicsText
Base class used to draw text.
By default a CText object is able to store up to 128 character.
Use SetCapaciy() to change this
*/
class CText : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CText );

public:

    /** @name DataTypes */
    //@{
	enum EState 
	{
		nState_RecreateBuffer = 0,
		nState_UpdateBuffer
	};
    //@}

    /** @name Constructor/destructor */
    //@{
	CText( );
	CText( const CTextFont& font, UInt32 capacity = 128 );
    virtual ~CText();
    //@}

    /** @name Operator*/
    //@{
    //@}

    /** @name Accessors*/
    //@{
	Void						SetCapacity( UInt32 c );
	Void						SetFont( const CTextFont& font );
    Void						SetPosition( const CVector3f& pos );
    Void						SetPosition( const CVector2f& pos );
	Void						SetText( String string );
	Void						WriteFormattedText( String format, ... );
	Void						SetColor( const CColor& color );
	Void						SetFontSize( Float32 size );

    CVector2f					Get2DPosition() const;
    CVector3f					Get3DPosition() const;
    const CVector3f&			GetPosition() const;
    String						GetText() const;
    const CVector2i&			GetSize() const;
	CTextFont&					GetFont() const;
	const CGeometryVertexBuffer& GetVertexBuffer() const;
    //@}

    /** @name Manipulator*/
    //@{
	Bool	Serialize( CPersistentArchive& ar );
    Void    Render(CRenderer& renderer);
	Void    UpdateBuffer( );
    //@}

private:

    // Types
    struct SVertex
    {
        CVector2f	Position;
        CVector2f	TexCoord0;
    };

    // Methods
	Void ProcessText();
    Void UpdateBuffer( const UInt32 offset, const UInt32 count);
	Void CreateBuffer( );

    // Attributes
    CRef<CTextFont>	            m_Font;
	CGeometryVertexBuffer		m_VertexBuffer;
	CGeometryVertexLayout		m_VertexLayout;

    CArray<Char>                m_Text;
	Int32						m_TextLength;
	Int32						m_CtrlCharCount;
	Int32	                    m_Capacity;
    CColor                      m_Color;
    CVector3f                   m_Position;
    Float32                     m_FontSize;
    CVector2i                   m_Size;
	CBitArray32					m_State;

};

Inline
String CText::GetText() const
{
    return m_Text.GetBuffer();
}

}

#endif
