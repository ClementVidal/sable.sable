#ifndef _SABLE_USERINTERFACE_WIDGET_TEXT_
#define _SABLE_USERINTERFACE_WIDGET_TEXT_

#include <Sable/Core/Common/Header.h>
#include <Sable/Graphics/Geometry/Header.h>
#include <Sable/Graphics/Text/Text.h>
#include <Sable/Graphics/Text/Font.h>
#include <Sable/Gui/Widget/Widget.h>

namespace Sable
{

class CRenderer;

/**  
\ingroup UserInterface
Text.
*/
class CWidgetText : public CWidget
{

		DEFINE_MANAGED_CLASS( CWidgetText );

public:

	/** @name DataTypes */
	//@{
	enum EHAlign
	{
		nHAlign_Left = 0,
		nHAlign_Center,
		nHAlign_Right
	};
	enum EVAlign
	{
		nVAlign_Top = 0,
		nVAlign_Center,
		nVAlign_Bottom
	};
	//@}

	/** @name Constructor/destructor */
	//@{
	CWidgetText( );
	CWidgetText( const CTextFont& font, UInt32 capacity = 128);
	virtual ~CWidgetText();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
	String			GetText() const;
	CWidgetText&	SetFont( const CTextFont& font );
	CWidgetText&	SetHAlign( EHAlign align );
	CWidgetText&	SetVAlign( EVAlign align );
    CWidgetText&    SetFontSize( Float32 s );
	CWidgetText&    SetText( String string );
    CWidgetText&    SetColor( const CColor& color );
	CWidgetText&	SetCapacity( UInt32 c );
	//@}

	/** @name Manipulator*/
	//@{
	Bool			Serialize( CPersistentArchive& ar );
	virtual Void	Render(CRenderer& renderer, CShader& shader);
	Bool			Update( );
	//@}

private:

	// Types

    // Methods
	CVector2i GetTextPosition() const;

	// Attributes
    CText       m_Text;
	EHAlign		m_HAlign;
	EVAlign		m_VAlign;

};

Inline
String CWidgetText::GetText() const
{
	return m_Text.GetText();
}

}

#endif
