#ifndef _SABLE_USERINTERFACE_WIDGET_CANVAS_
#define _SABLE_USERINTERFACE_WIDGET_CANVAS_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Geometry/Rect2Df.h>
#include <Sable/Core/Common/Color.h>
#include <Sable/Gui/Widget/Widget.h>

namespace Sable
{

class CWidget;
class CGuiNinePatch;

/**  
\ingroup UserInterface
Window class.
*/
class CWidgetCanvas : public CWidget
{

	DEFINE_MANAGED_CLASS( CWidgetCanvas );
	friend class CGuiRenderPass;

public:

	/** @name Constructor/destructor */
	//@{
	//@}

	/** @name Constructor/destructor */
	//@{
	CWidgetCanvas( );
	~CWidgetCanvas();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
    CColor&			GetColor();
    CWidget&        SetColor( const CColor& pos );
    Void            SetNinePatch( CGuiNinePatch* texture );
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
    CRef<CGuiNinePatch>		m_NinePatch;

};

}

#endif
