#ifndef _INPUT_KEYBOARD_KEYBOARD_
#define _INPUT_KEYBOARD_KEYBOARD_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Input/Keyboard/Interface.h>
#include <Sable/Input/Keyboard/Impl/Header.h>

namespace Sable
{

class CKeyboardObserver;

/** 
\ingroup InputKeyboard
*/
class CKeyboard : public CKeyboardInterface
{

	DEFINE_MANAGED_CLASS( CKeyboard );

public:

	/** @name Constructor/Destructor*/
	//@{
	CKeyboard( CApplicationWindow& window );
	virtual ~CKeyboard();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
	Bool	GetIsKeyDown( const EKeyboardEventData key ) const ;
	//@}

	/** @name Manipulator*/
	//@{
	Void				Update();
	//@}

private:

	// Attributes
	CImplKeyboard	    m_Impl;

};


}

#endif


