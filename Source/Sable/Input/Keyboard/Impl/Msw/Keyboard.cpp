#include <Sable/Input/Keyboard/Impl/Msw/Keyboard.h>

#include <Sable/Graphics/Common/Manager.h>
#include <Sable/Input/Keyboard/Keyboard.h>
#include <Sable/Application/Window.h>

#define DX9KEYBOARD_BufferSize 16

CImplMswKeyboard::CImplMswKeyboard(CKeyboard& keyboard) : 
	CImplStubKeyboard( keyboard ),
	m_Keyboard(keyboard)
{
	DIPROPDWORD 
		dipdw;

	m_KeyboardState.SetItemCount(256);
    m_KeyboardState.Fill( 0 );

	dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj        = 0;
	dipdw.diph.dwHow        = DIPH_DEVICE;
	dipdw.dwData            = DX9KEYBOARD_BufferSize; 

	LPDIRECTINPUT8			
		inputDevice = ((CImplMswInputManager&)InputManager.GetImpl()).GetInputDevice();

	AssertDXCall( 
		inputDevice->CreateDevice(
		GUID_SysKeyboard, 
		&m_DirectInputKeyboard, 
		NULL
		)
		); 

	AssertDXCall( 
		m_DirectInputKeyboard->SetDataFormat(
		&c_dfDIKeyboard
		)
		); 

	AssertDXCall( 
		m_DirectInputKeyboard->SetCooperativeLevel( 
		(HWND)keyboard.GetAttachedWindow().GetHandle(), 
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE
		)
		); 

	AssertDXCall( 
		m_DirectInputKeyboard->SetProperty( 
		DIPROP_BUFFERSIZE, 
		&dipdw.diph 
		) 
		) ;

	m_DirectInputKeyboard->Acquire(); 


}

CImplMswKeyboard::~CImplMswKeyboard()
{
	m_DirectInputKeyboard->Release();
}

Void CImplMswKeyboard::Update( )
{
	ProcessImmediateData( );
	ProcessBufferedData( );
}

Void CImplMswKeyboard::ProcessImmediateData()
{
	HRESULT
		hr;

	hr = m_DirectInputKeyboard->GetDeviceState(
		m_KeyboardState.GetItemCount(),
		(LPVOID)m_KeyboardState.GetBuffer()
		);

	if ( hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED )
	{	
		m_DirectInputKeyboard->Acquire();
	} 
}

Bool CImplMswKeyboard::GetIsKeyDown( const EKeyboardEventData key ) const 
{
	return m_KeyboardState[ TranslateKey( key ) ] & 0x80 ;
}

Void CImplMswKeyboard::ProcessBufferedData()
{
	HRESULT
		hr;
	DIDEVICEOBJECTDATA 
		bufferedData[ DX9KEYBOARD_BufferSize ];  // Receives buffered data 
	UInt32              
		dwElements;
	Index
		index;

	dwElements = DX9KEYBOARD_BufferSize;

	hr = m_DirectInputKeyboard->GetDeviceData( 
		sizeof(DIDEVICEOBJECTDATA),
		bufferedData, 
		( LPDWORD )&dwElements, 
		0 
		);

	if ( hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED )
	{	
		m_DirectInputKeyboard->Acquire();
		return;
	} 

	for( index = 0; index < dwElements; index ++  )
	{
		if( bufferedData[ index ].dwData & 0x80 )
		{
			m_Keyboard.SignalEvent( nKeyboardEventType_KeyDown, TranslateKey( bufferedData[ index ].dwOfs ) );
		}
		else
		{
			m_Keyboard.SignalEvent( nKeyboardEventType_KeyUp, TranslateKey( bufferedData[ index ].dwOfs ) );
		}
	}
}

UInt32 CImplMswKeyboard::TranslateKey( const EKeyboardEventData key ) const
{
	return ( UInt32 ) key;
}

EKeyboardEventData CImplMswKeyboard::TranslateKey( const UInt32 key ) const 
{
	return ( EKeyboardEventData ) key;
}