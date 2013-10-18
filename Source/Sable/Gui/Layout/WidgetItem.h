#ifndef _SABLE_USERINTERFACE_WIDGETITEM_
#define _SABLE_USERINTERFACE_WIDGETITEM_

#include <Sable/Core/Common/Header.h>
#include <Sable/Gui/Layout/Item.h>

namespace Sable
{

class CWidget;

/**  
\ingroup UserInterface
Bridge that allow to treat Widget as any CLayoutItem
*/
class CLayoutWidgetItem : public CLayoutItem
{

	DEFINE_MANAGED_CLASS( CLayoutWidgetItem );

public:

	/** @name Constructor/destructor */
	//@{
	CLayoutWidgetItem( CWidget& widget );
	virtual ~CLayoutWidgetItem();
	//@}
    
    /** @name Accessors*/
    //@{
	CWidget& GetWidget() const;
	ESizePolicy				GetHSizePolicy() const;
	ESizePolicy				GetVSizePolicy() const;
	const CVector2i&		GetStretchFactor() const;
	const CVector2i&		GetSize()const;
    //@}

	/** @name Manipulator*/
    //@{
    Void  SetPositionAndSize( const CVector2i& pos, const CVector2i& size );
	//@}

private:

    // Methods

    // Attributes
    CRef<CWidget>    m_Widget;
};

}

#endif
