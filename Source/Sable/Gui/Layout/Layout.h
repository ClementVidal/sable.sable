#ifndef _SABLE_USERINTERFACE_LAYOUT_LAYOUT_
#define _SABLE_USERINTERFACE_LAYOUT_LAYOUT_

#include <Sable/Core/Common/Header.h>
#include <SAble/Core/Math/Vector2i.h>
#include <Sable/Gui/Layout/Item.h>

namespace Sable
{

class CWidget;

/**  
\ingroup UserInterface
Base class for any layout
*/
class CLayout : public CLayoutItem
{

	DEFINE_MANAGED_CLASS( CLayout );

public:

	/** @name Constructor/destructor */
	//@{
	CLayout( );
	virtual ~CLayout();
	//@}

	/** @name Accessors*/
	//@{
	Void					SetStretchFactor( const CVector2i& s );
	const CVector2i&		GetStretchFactor() const;
	ESizePolicy				GetHSizePolicy() const;
	ESizePolicy				GetVSizePolicy() const;
	Void					SetVSizePolicy( ESizePolicy p );
	Void					SetHSizePolicy( ESizePolicy p );
	Void					SetSize( const CVector2i& s );
	const CVector2i&		GetSize()const;
	//@}

	/** @name Manipulator*/
    //@{
    Void  AddLayout( CLayout& layout );
    Void  AddWidget( CWidget& widget );
    Void  SetPositionAndSize( const CVector2i& pos, const CVector2i& size );
    virtual Void Apply( const CVector2i& pos, const CVector2i& size ) = 0;
	//@}

private:

    // Methods

    // Attributes
	CVector2i	m_StretchFactor;
	ESizePolicy	m_VSizePolicy;
	ESizePolicy	m_HSizePolicy;
	CVector2i	m_Size;
};

}

#endif
