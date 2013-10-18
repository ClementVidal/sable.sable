#ifndef _SABLE_INPUT_KEYBOARD_IMPL_MSW_KEYBOARD_
#define _SABLE_INPUT_KEYBOARD_IMPL_MSW_KEYBOARD_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Input/Keyboard/Impl/Stub/Keyboard.h>

#define DIRECTINPUT_VERSION 0x0800

#include <Dinput.h>

namespace Sable
{

class CKeyboard;

/** 
\ingroup Input
*/
class CImplMswKeyboard : public CImplStubKeyboard
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CImplMswKeyboard(CKeyboard& keyboard);
	virtual ~CImplMswKeyboard();
	//@}

	/** @name Accessors*/
	//@{
	Bool GetIsKeyDown( const EKeyboardEventData key ) const; 
	//@}

	/** @name Manipulator*/
	//@{
	Void	Update();
	//@}

private:

	// Methods
	EKeyboardEventData	TranslateKey( const UInt32 key ) const ;
	UInt32	TranslateKey( const EKeyboardEventData key ) const;
	Void	ProcessImmediateData();
	Void	ProcessBufferedData();

	// Attributes
	CKeyboard&				m_Keyboard;
	LPDIRECTINPUTDEVICE8	m_DirectInputKeyboard;
	CArray<Byte>			m_KeyboardState;

};

}

#endif
