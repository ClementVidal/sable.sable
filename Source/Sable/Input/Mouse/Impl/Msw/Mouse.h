#ifndef _SABLE_INPUT_MOUSE_IMPL_MSW_MOUSE_
#define _SABLE_INPUT_MOUSE_IMPL_MSW_MOUSE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Input/Mouse/Impl/Stub/Mouse.h>
#include <Sable/Input/Mouse/Event.h>

#define DIRECTINPUT_VERSION 0x0800

#include <Dinput.h>

namespace Sable
{

/** 
\ingroup Input
*/
class CImplMswMouse : public CImplStubMouse
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CImplMswMouse(CMouse& mouse);
	virtual ~CImplMswMouse();
	//@}

	/** @name Accessors*/
	//@{
	//@}

	/** @name Manipulator*/
	//@{
	Void	Update();
	//@}

private:

	// Methods
	EMouseEventData	TranslateKey( const UInt32 key ) const ;
	Void	ProcessImmediateData();
	Void	ProcessBufferedData();

	// Attributes
	CMouse&					m_Mouse;
	LPDIRECTINPUTDEVICE8	m_DirectInputMouse;
	DIMOUSESTATE2			m_MouseStateBuffer;
    
};  

}

#endif
