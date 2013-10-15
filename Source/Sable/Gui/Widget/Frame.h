#ifndef _SABLE_USERINTERFACE_WIDGET_FRAME_
#define _SABLE_USERINTERFACE_WIDGET_FRAME_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Geometry\Rect2Df.h>
#include <Sable\Core\Common\Color.h>
#include <Sable\Gui\Widget\Widget.h>

namespace Sable
{

class CWidget;
class CTexture2D;

/**  
\ingroup UserInterface
Window class.
*/
class CWidgetFrame : public CWidget
{

	DEFINE_MANAGED_CLASS( CWidgetFrame );

public:

	/** @name Constructor/destructor */
	//@{
	//@}

	/** @name Constructor/destructor */
	//@{
	CWidgetFrame( );
	~CWidgetFrame();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
    CColor&			GetColor();
    CWidget&        SetColor( const CColor& pos );
    Void            SetTexture( CTexture2D* texture );
	Void			SetTextureSize( const CVector2f& s );
	Void			SetTextureOrigin( const CVector2f& o );
	//@}

	/** @name Manipulator*/
    //@{
    Bool            Serialize( CPersistentArchive& ar );
    virtual Void    Render( CRenderer& renderer, CShader& shader );
	//@}

protected:

	// Protected methods

private:

	// Types

	// Methods

    // Attributes
    CColor					m_Color;
    CRef<CTexture2D>		m_Texture;
	CVector2f				m_TextureSize;
	CVector2f				m_TextureOrigin;

};

}

#endif
