#include <Sable\Input\Mouse\Impl\Msw\Mouse.h>

#include <Sable\Input\Mouse\Mouse.h>
#include <Sable\Application\Window.h>

#define DX9MOUSE_BufferSize 128

CImplMswMouse::CImplMswMouse(CMouse& mouse) : 
	CImplStubMouse( mouse ),
	m_Mouse(mouse)
{
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj        = 0;
	dipdw.diph.dwHow        = DIPH_DEVICE;
	dipdw.dwData            = DX9MOUSE_BufferSize; 

	LPDIRECTINPUT8			
		inputDevice = ((CImplMswInputManager&)InputManager.GetImpl()).GetInputDevice();

	AssertDXCall( 
		inputDevice->CreateDevice(
		GUID_SysMouse, 
		&m_DirectInputMouse, 
		NULL
		)
		); 

	AssertDXCall( 
		m_DirectInputMouse->SetDataFormat(
		&c_dfDIMouse2
		)
		); 

	AssertDXCall( 
		m_DirectInputMouse->SetCooperativeLevel( 
		(HWND) mouse.GetAttachedWindow().GetHandle(), 
        DISCL_FOREGROUND | DISCL_EXCLUSIVE
		)
		); 

	AssertDXCall( 
		m_DirectInputMouse->SetProperty( 
		DIPROP_BUFFERSIZE, 
		&dipdw.diph 
		) 
		) ;

	m_DirectInputMouse->Acquire(); 

}

CImplMswMouse::~CImplMswMouse()
{
	m_DirectInputMouse->Release();
}

Void CImplMswMouse::Update( )
{
	ProcessImmediateData( );
	ProcessBufferedData( );
}

Void CImplMswMouse::ProcessImmediateData()
{
	HRESULT hr;

    Int32 screenW = m_Mouse.GetAttachedWindow().GetSwapChain().GetInfo().RenderTargetInfo.TextureInfo.Width;
    Int32 screenH = m_Mouse.GetAttachedWindow().GetSwapChain().GetInfo().RenderTargetInfo.TextureInfo.Height;

	MemoryFill( &m_MouseStateBuffer, 0, sizeof( DIMOUSESTATE2 ) );

	hr = m_DirectInputMouse->GetDeviceState(
		sizeof( DIMOUSESTATE2 ) ,
		(LPVOID)&m_MouseStateBuffer
		);

	if ( hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED )
	{	
		m_DirectInputMouse->Acquire();
		return;
	} 

	Int32 pixelPosX;
	Int32 pixelPosY;

	pixelPosX = m_MouseStateBuffer.lX;
	pixelPosY = m_MouseStateBuffer.lY;

	m_Mouse.m_State.XPosition += (Float32)pixelPosX / (Float32)screenW;
	m_Mouse.m_State.YPosition += ( (Float32)pixelPosY / (Float32)screenH );

	if( m_Mouse.ClampCoordinate() )
	{
		m_Mouse.m_State.XPosition = MathClamp( m_Mouse.m_State.XPosition, 0.0f, 1.0f );
		m_Mouse.m_State.YPosition = MathClamp( m_Mouse.m_State.YPosition, 0.0f, 1.0f );
	}
}

Void CImplMswMouse::ProcessBufferedData()
{
	HRESULT	hr;
	DIDEVICEOBJECTDATA bufferedData[ DX9MOUSE_BufferSize ];  // Receives buffered data 
	UInt32 dwElements;
	Index index;

	dwElements = DX9MOUSE_BufferSize;

	hr = m_DirectInputMouse->GetDeviceData( 
		sizeof(DIDEVICEOBJECTDATA),
		bufferedData, 
		( LPDWORD )&dwElements, 
		0 
		);

	if ( hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED )
	{	
		m_DirectInputMouse->Acquire();
		return;
	} 


	EMouseEventData
		mouseEventData;

	for( index = 0; index < dwElements; index ++  )
	{
		mouseEventData = TranslateKey( bufferedData[ index ].dwOfs );

		if( mouseEventData < nMouseEventData_AxisX )
		{
			if( bufferedData[ index ].dwData & 0x80 )
			{
				m_Mouse.SignalEvent( nMouseEventType_KeyDown, mouseEventData, CVector2f( m_Mouse.m_State.XPosition, m_Mouse.m_State.YPosition ) );
			}
			else
			{
				m_Mouse.SignalEvent( nMouseEventType_KeyUp, mouseEventData, CVector2f( m_Mouse.m_State.XPosition, m_Mouse.m_State.YPosition )  );
			}
		}
		else
		{
			/*
			CMouse::SAxisData
				axisData;
			axisData.Axis = mouseEventData;
			axisData.Value = bufferedData[ index ].dwData;
*/			
			m_Mouse.SignalEvent( nMouseEventType_Move, mouseEventData, CVector2f( m_Mouse.m_State.XPosition, m_Mouse.m_State.YPosition )  );
		}
	}
}

EMouseEventData CImplMswMouse::TranslateKey( const UInt32 key ) const 
{
	switch( key )
	{
	case DIMOFS_BUTTON0:
		return nMouseEventData_LeftBtn;
	case DIMOFS_BUTTON1:
		return nMouseEventData_RightBtn;
	case DIMOFS_BUTTON2:
		return nMouseEventData_MiddleBtn;

	case DIMOFS_X:
		return nMouseEventData_AxisX;
	case DIMOFS_Y:
		return nMouseEventData_AxisY;
	case DIMOFS_Z:
		return nMouseEventData_AxisZ;
	}

	return nMouseEventData_None;
}
