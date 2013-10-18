#ifndef _SABLE_GRAPHICS_NODE_BILLBOARD_
#define _SABLE_GRAPHICS_NODE_BILLBOARD_

#include <Sable/Graphics/Node/Render.h>

namespace Sable 
{

/**
*/
class CNodeBillboard : public CNodeRender
{

	DEFINE_MANAGED_CLASS( CNodeBillboard )

public:

	/** @name DataTypes*/
	//@{
	//@}

    /** @name Constructor/Destructor*/
	//@{
	CNodeBillboard( );
	CNodeBillboard( CNode&  parent );
    ~CNodeBillboard( );
    //@}
    
    /** @name Accessors*/
	//@{
    //@}
    
    /** @name Manipulator*/
	//@{
	Bool	Update( );
    //@}
    
private:

	// DataTypes

    // Methods	

	// Attributes
};	

}

#endif
