#ifndef _USERINTERFACE_WIDGET_ROWLAYOUT_
#define _USERINTERFACE_WIDGET_ROWLAYOUT_

#include <Sable\Core\Common\Header.h>
#include <Sable\Gui\Layout\Layout.h>

namespace Sable
{

class CRenderer;
class CManagedObject;

/**  
\ingroup UserInterface
Column ( vertical ) widget layout.
*/
class CLayoutHBox : public CLayout
{

	DEFINE_MANAGED_CLASS( CLayoutHBox );

public:

	/** @name Constructor/destructor */
	//@{
	CLayoutHBox();
	virtual ~CLayoutHBox();
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
