#ifndef _SABLE_USERINTERFACE_LAYOUT_VBOX_
#define _SABLE_USERINTERFACE_LAYOUT_VBOX_

#include <Sable/Core/Common/Header.h>
#include <Sable/Gui/Layout/Layout.h>

namespace Sable
{

class CRenderer;

/**  
\ingroup UserInterface
Vertical box layout.
*/
class CLayoutVBox : public CLayout
{

	DEFINE_MANAGED_CLASS( CLayoutVBox );

public:

	/** @name Constructor/destructor */
	//@{
	CLayoutVBox( );
	virtual ~CLayoutVBox();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
	//@}

	/** @name Manipulator*/
    //@{
	Void Apply( const CVector2i& pos, const CVector2i& size );
	//@}

private:

    // Methods

    // Attributes

};

}

#endif
