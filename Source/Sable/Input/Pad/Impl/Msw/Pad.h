#ifndef _SABLE_INPUT_PAD_IMPL_MSW_PAD_
#define _SABLE_INPUT_PAD_IMPL_MSW_PAD_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Input/Pad/Impl/Stub/Pad.h>
#include <Sable/Input/Pad/Event.h>

#define DIRECTINPUT_VERSION 0x0800

#include <Dinput.h>

namespace Sable
{

/** 
\ingroup InputPad

This implementation provide an interface to a PS3 dual shock controller.
In order to works, the controller must use the motioninjoy driver:
http://www.motioninjoy.com/

Button can be accessed with the following enum

enum EPS3ControllerBtn
{
	nPS3ControllerBtn_Up = 0,
	nPS3ControllerBtn_Right = 1,
	nPS3ControllerBtn_Down = 2,
	nPS3ControllerBtn_Left = 3,

	nPS3ControllerBtn_Triangle = 4,
	nPS3ControllerBtn_Circle = 5,
	nPS3ControllerBtn_Cross = 6,
	nPS3ControllerBtn_Square = 7,

	nPS3ControllerBtn_L1 = 8,
	nPS3ControllerBtn_L2 = 9,
	nPS3ControllerBtn_L3 = 10,

	nPS3ControllerBtn_R1 = 11,
	nPS3ControllerBtn_R2 = 12,
	nPS3ControllerBtn_R3 = 13,

	nPS3ControllerBtn_Select = 14,
	nPS3ControllerBtn_Start = 15,
	nPS3ControllerBtn_PS = 16,
};

Analogic stick can be accessed by the following enum

enum EPS3ControllerStick
{
	nPS3ControllerStick_Left = 0,
	nPS3ControllerStick_Right = 1
};

Analogic value of button L2 and R2 are not supported.
*/
class CImplMswPad : public CImplStubPad
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CImplMswPad( CPad& pad );
	virtual ~CImplMswPad();
	//@}

	/** @name Accessors*/
	//@{
	Bool		IsAvailable() const;
	CVector2f	GetAnalogStick( UInt32 id ) const;
	Float32		GetAnalogButton( UInt32 id ) const;
	Bool		GetButton( UInt32 id ) const;
	//@}

	/** @name Manipulator*/
	//@{
	Void	Update();
	//@}

private:

	// DataTypes
	struct SPadState
	{ 
		LONG Axis[8];
		BYTE Btn[20];
		LONG Pov;
		BYTE Pad[1]; // One byt of padding to be a multiple of 4
	}; 


	// Methods
    Void EnumDevices();
	Void BuildDataFormat();
	Void PrintState() const;

	// Attributes
    LPDIRECTINPUTDEVICE8		m_Pad; 
	DIDEVICEOBJECTINSTANCE		m_ObjectTable[32];
	UInt32						m_ObjectCount;
	SPadState					m_State;

    // Static Methods
    static BOOL CALLBACK EnumDeviceCallback( LPCDIDEVICEINSTANCE instance, LPVOID reference );
    static BOOL CALLBACK EnumDeviceAxisCallback( LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef );
    static BOOL CALLBACK EnumDeviceButtonCallback( LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef );
	static BOOL CALLBACK EnumDevicePovCallback( LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef );

};

}

#endif
