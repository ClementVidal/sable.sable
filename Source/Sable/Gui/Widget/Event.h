#ifndef _SABLE_GUI_WIDGET_EVENT_
#define _SABLE_GUI_WIDGET_EVENT_

#include <Sable/Core/Common/Header.h>
#include <Sable/Core/Collection/Header.h>

namespace Sable
{

class CWidget;

/**  
\ingroup UserInterface
Event base class
*/
class CWidgetEvent : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CWidgetEvent );

public:
	
	/** @name DataTypes */
	//@{
	enum EType
	{
		nType_CursorMove = 0,
		nType_CursorUp,
		nType_CursorDown,
		nType_CursorEnter,
		nType_CursorLeave,
		nType_WidgetResize,
		nType_WidgetMove,
		nType_Count,
		nType_None = -1,

		nType_UserType
	};
	//@}

	/** @name Constructor/destructor */
	//@{
	CWidgetEvent( EType type, const CVector2i& pos, UInt32 data = 0, CWidget* source = NULL );
	~CWidgetEvent();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
	EType				GetType() const;
	const CVector2i&	GetCursorPos() const;
	UInt32				GetData() const;
	Void				Skip();
	Bool				GetIsSkiped() const;
	//@}

	/** @name Manipulator*/
    //@{
	//@}

	/** @name Signals*/
	//@{
	//@}

protected:

	// Types

	// Methods

    // Attributes
	EType			m_Type;
	CVector2i		m_CursorPos;
	UInt32			m_Data;
	Bool			m_Skip;
	CWidget*		m_Source;
};

}

#endif
