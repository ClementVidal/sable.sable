#ifndef _SABLE_USERINTERFACE_LAYOUT_ITEM_
#define _SABLE_USERINTERFACE_LAYOUT_ITEM_

#include <Sable\Core\Common\Header.h>
#include <Sable\Gui\Common\DataTypes.h>

namespace Sable
{

/**  
\ingroup UserInterface
Base class for any layout
*/
class CLayoutItem : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CLayoutItem );

public:

	/** @name DataTypes */
	//@{
	//@}

	/** @name Constructor/destructor */
	//@{
	CLayoutItem( );
	~CLayoutItem();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
    CLayoutItem&            SetParent( CLayoutItem* p );
    CLayoutItem*			GetParent() const;
    CLayoutItem*			GetSibling() const;
    CLayoutItem*			GetChild() const;
    UInt32					GetChildCount() const;
	virtual ESizePolicy				GetHSizePolicy() const = 0;
	virtual ESizePolicy				GetVSizePolicy() const = 0;
	virtual const CVector2i&		GetStretchFactor()const = 0;
	virtual const CVector2i&		GetSize()const = 0;
	//@}

	/** @name Manipulator*/
    //@{
    Void                    RemoveAllChild();
    virtual Void            SetPositionAndSize( const CVector2i& pos, const CVector2i& size ) = 0;
	//@}


protected:

    // Methods
    Void                    AddChild( CLayoutItem& child );
    Bool                    RemoveChild( CLayoutItem& w );


private:

    // Attributes
    CLayoutItem*                    m_Parent;
    CRef<CLayoutItem>				m_Sibling;
    CRef<CLayoutItem>				m_Child;
    Int32							m_ChildCount;
};

}

#endif
