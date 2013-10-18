#ifndef _SABLE_INPUT_KEYBOARD_IMPL_STUB_KEYBOARD_
#define _SABLE_INPUT_KEYBOARD_IMPL_STUB_KEYBOARD_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Input/Keyboard/Event.h>
namespace Sable
{

class CKeyboard;

/** 
\ingroup Input
*/
class CImplStubKeyboard 
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CImplStubKeyboard(){}
	CImplStubKeyboard(CKeyboard& keyboard){}
	virtual ~CImplStubKeyboard(){}
	//@}

	/** @name Accessors*/
	//@{
	virtual Bool GetIsKeyDown( const EKeyboardEventData key ) const {return FALSE; } 
	//@}

	/** @name Manipulator*/
	//@{
	virtual Void	Update(){};
	//@}

private:

	// Methods

	// Attributes

};

}

#endif


