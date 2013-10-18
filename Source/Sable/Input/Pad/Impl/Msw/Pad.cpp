#include <Sable/Input/Pad/Impl/Stub/Pad.h>

CImplMswPad::CImplMswPad(CPad& pad) : 
	CImplStubPad(pad)
{
	m_Pad = NULL;
    EnumDevices();
	BuildDataFormat();
}

CImplMswPad::~CImplMswPad()
{

}

Void CImplMswPad::Update( )
{
	HRESULT hr;

	if( m_Pad == NULL )
		return;

	MemoryFill( &m_State, 0, sizeof( SPadState ) );

	hr = m_Pad->GetDeviceState(	sizeof( SPadState ) ,(LPVOID)&m_State );

	if ( hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED )
	{	
		m_Pad->Acquire();
		return;
	} 

}

Bool CImplMswPad::GetButton( UInt32 id ) const
{
	UInt32 povStep = 4500;
	UInt32 btnStep = 128;

	if( !m_Pad )
		return CImplPad::GetButton( id );

	// id from 0 to 3 are direction cross on ps3 pad and come frtom the POV state
	if( id == 0 ) // Up
		return ( m_State.Pov == povStep*7 ) || ( m_State.Pov == povStep*0 ) || ( m_State.Pov == povStep*1 );
	else if( id == 1 ) // Right
		return ( m_State.Pov == povStep*1 ) || ( m_State.Pov == povStep*2 ) || ( m_State.Pov == povStep*3 );
	else if( id == 2 ) //Down
		return ( m_State.Pov == povStep*3 ) || ( m_State.Pov == povStep*4 ) || ( m_State.Pov == povStep*5 );
	else if( id == 3 ) //Left
		return ( m_State.Pov == povStep*5 ) || ( m_State.Pov == povStep*6 ) || ( m_State.Pov == povStep*7 );

	else if( id == 4 ) //Triangle
		return m_State.Btn[0]?TRUE:FALSE;
	else if( id == 5 ) // round
		return m_State.Btn[1]?TRUE:FALSE;
	else if( id == 6 ) // cross
		return m_State.Btn[2]?TRUE:FALSE;
	else if( id == 7 ) // square
		return m_State.Btn[3]?TRUE:FALSE;

	else if( id == 8 ) // L1
		return m_State.Btn[6]?TRUE:FALSE;
	else if( id == 9 ) // L2
		return m_State.Btn[4]?TRUE:FALSE;
	else if( id == 10 ) // L3
		return m_State.Btn[10]?TRUE:FALSE;

	else if( id == 11 ) // R1
		return m_State.Btn[7]?TRUE:FALSE;
	else if( id == 12 ) // R2
		return m_State.Btn[5]?TRUE:FALSE;
	else if( id == 13 ) // R3
		return m_State.Btn[11]?TRUE:FALSE;

	else if( id == 14 ) // Select
		return m_State.Btn[8]?TRUE:FALSE;
	else if( id == 15 ) // Start
		return m_State.Btn[9]?TRUE:FALSE;
	else if( id == 16 ) // PS
		return m_State.Btn[12]?TRUE:FALSE;

	DebugError("Invalid button id ");

	return FALSE;
}

Float32 CImplMswPad::GetAnalogButton( UInt32 id ) const
{
	if( !m_Pad )
		return CImplPad::GetAnalogButton( id );

	DebugError("No analog button supported");
	return 0.0f;
}

CVector2f CImplMswPad::GetAnalogStick( UInt32 id ) const
{
	Float32 x, y;
	
	if( !m_Pad )
		return CImplPad::GetAnalogStick( id );

	if( id == 0 )
	{
		x = ( (Float32) m_State.Axis[7] / 65535.0f );
		x =  ( x * 2.0f ) -1.0f; 

		y = ( (Float32) m_State.Axis[6] / 65535.0f );
		y =  ( y * 2.0f ) -1.0f; 
	}
	else if( id == 1 )
	{
		x = ( (Float32) m_State.Axis[2] / 65535.0f );
		x =  ( x * 2.0f ) -1.0f; 

		y = ( (Float32) m_State.Axis[5] / 65535.0f );
		y =  ( y * 2.0f ) -1.0f; 
	}
	else
	{
		DebugError("Invalid axis");
	}

	if( MathAbs( x ) < 0.08f )
		x = 0.00f;
	if( MathAbs( y ) < 0.08f )
		y = 0.00f;

	return CVector2f( x, y );
}

BOOL CALLBACK CImplMswPad::EnumDeviceButtonCallback( LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef )
{
	CImplMswPad* impl = (CImplMswPad*)pvRef;

	impl->m_ObjectTable[impl->m_ObjectCount] = *lpddoi;
	impl->m_ObjectCount++;

	return DIENUM_CONTINUE;
}

BOOL CALLBACK CImplMswPad::EnumDevicePovCallback( LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef )
{
	CImplMswPad* impl = (CImplMswPad*)pvRef;

	impl->m_ObjectTable[impl->m_ObjectCount] = *lpddoi;
	impl->m_ObjectCount++;

	return DIENUM_CONTINUE;
}

BOOL CALLBACK CImplMswPad::EnumDeviceAxisCallback( LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef )
{
	CImplMswPad* impl = (CImplMswPad*)pvRef;

	impl->m_ObjectTable[impl->m_ObjectCount] = *lpddoi;
	impl->m_ObjectCount++;

	return DIENUM_CONTINUE;
}

// Callback d'énumération
BOOL CALLBACK CImplMswPad::EnumDeviceCallback( LPCDIDEVICEINSTANCE instance, LPVOID reference )
{
	HRESULT result;
	CImplMswPad* implPadDX9 = (CImplMswPad*) reference;

    LPDIRECTINPUT8 diObject = ((CImplMswInputManager&)InputManager.GetImpl()).GetInputDevice();

	// Création du périphérique
	result = diObject->CreateDevice( instance->guidInstance, &implPadDX9->m_Pad, NULL);
	
	// Gestion des erreurs
	if(FAILED( result )) 
	{
		// En cas d'échec ... on continue l'enumération
		return DIENUM_CONTINUE; 
	}
	
	DIDEVICEINSTANCE devInfo;
	implPadDX9->m_Pad->GetDeviceInfo( &devInfo );

	// En cas de réussite ... on arrête l'enumération
	return DIENUM_STOP;
}

Void CImplMswPad::BuildDataFormat()
{
	if( !m_Pad )
		return ;

	DIOBJECTDATAFORMAT objFormat[] = 
	{ 
		// Axis data
		{ &m_ObjectTable[0].guidType, FIELD_OFFSET( SPadState, Axis[0] ), 
		DIDFT_AXIS | DIDFT_ANYINSTANCE, 0 }, 
		{ &m_ObjectTable[1].guidType, FIELD_OFFSET( SPadState, Axis[1] ),
		DIDFT_AXIS | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[2].guidType, FIELD_OFFSET( SPadState, Axis[2] ),
			DIDFT_AXIS | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[3].guidType, FIELD_OFFSET( SPadState, Axis[3] ),
			DIDFT_AXIS | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[4].guidType, FIELD_OFFSET( SPadState, Axis[4] ),
			DIDFT_AXIS | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[5].guidType, FIELD_OFFSET( SPadState, Axis[5] ),
			DIDFT_AXIS | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[6].guidType, FIELD_OFFSET( SPadState, Axis[6] ),
			DIDFT_AXIS | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[7].guidType, FIELD_OFFSET( SPadState, Axis[7] ),
			DIDFT_AXIS | DIDFT_ANYINSTANCE, 0 },

		// Button data
		{ &m_ObjectTable[8].guidType, FIELD_OFFSET( SPadState, Btn[0] ),
		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[9].guidType, FIELD_OFFSET( SPadState, Btn[1] ),
		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[10].guidType, FIELD_OFFSET( SPadState, Btn[2] ),
		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[11].guidType, FIELD_OFFSET( SPadState, Btn[3] ),
		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[12].guidType, FIELD_OFFSET( SPadState, Btn[4] ),
		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[13].guidType, FIELD_OFFSET( SPadState, Btn[5] ),
		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[14].guidType, FIELD_OFFSET( SPadState, Btn[6] ),
		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[15].guidType, FIELD_OFFSET( SPadState, Btn[7] ),
		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[16].guidType, FIELD_OFFSET( SPadState, Btn[8] ),
		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[17].guidType, FIELD_OFFSET( SPadState, Btn[9] ),
		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[18].guidType, FIELD_OFFSET( SPadState, Btn[10] ),
		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[19].guidType, FIELD_OFFSET( SPadState, Btn[11] ),
		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[20].guidType, FIELD_OFFSET( SPadState, Btn[12] ),
		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[21].guidType, FIELD_OFFSET( SPadState, Btn[13] ),
		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[22].guidType, FIELD_OFFSET( SPadState, Btn[14] ),
		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[23].guidType, FIELD_OFFSET( SPadState, Btn[15] ),
		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[24].guidType, FIELD_OFFSET( SPadState, Btn[16] ),
		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[25].guidType, FIELD_OFFSET( SPadState, Btn[17] ),
		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[26].guidType, FIELD_OFFSET( SPadState, Btn[18] ),
		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[27].guidType, FIELD_OFFSET( SPadState, Btn[19] ),
		DIDFT_BUTTON | DIDFT_ANYINSTANCE, 0 },
		{ &m_ObjectTable[28].guidType, FIELD_OFFSET( SPadState, Pov ),
		DIDFT_POV | DIDFT_ANYINSTANCE, 0 },

	}; 

	const UInt32 objCount = sizeof(objFormat) / sizeof(DIOBJECTDATAFORMAT);

	DIDATAFORMAT            dataFormat = 
	{ 
		sizeof( DIDATAFORMAT ), 
		sizeof( DIOBJECTDATAFORMAT ), 
		DIDF_ABSAXIS, 
		sizeof( SPadState ), 
		objCount, 
		objFormat 
	}; 

	AssertDXCall( m_Pad->SetDataFormat( &dataFormat ) );

	DIPROPDWORD  dipdw;
	dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj        = 0;
	dipdw.diph.dwHow        = DIPH_DEVICE;
	dipdw.dwData            = objCount; 

	AssertDXCall( m_Pad->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph ) ) ;

	AssertDXCall( m_Pad->Acquire() ); 
}


Void CImplMswPad::EnumDevices()
{
    HRESULT result;

	m_ObjectCount = 0;

    LPDIRECTINPUT8 diObject = ((CImplMswInputManager&)InputManager.GetImpl()).GetInputDevice();

    result = diObject->EnumDevices( DI8DEVCLASS_GAMECTRL, &CImplMswPad::EnumDeviceCallback, this, DIEDFL_ATTACHEDONLY );
    if( FAILED( result ) )
        return ;

	if( m_Pad == NULL )
		return;

    DIDEVICEINSTANCE deviceInfo;
    result = m_Pad->GetDeviceInfo( &deviceInfo );

    result = m_Pad->EnumObjects( &CImplMswPad::EnumDeviceAxisCallback, this, DIDFT_AXIS );
    if( FAILED( result ) )
        return ;

    result = m_Pad->EnumObjects( &CImplMswPad::EnumDeviceButtonCallback, this, DIDFT_BUTTON );
    if( FAILED( result ) )
        return ;

	result = m_Pad->EnumObjects( &CImplMswPad::EnumDevicePovCallback, this, DIDFT_POV );
	if( FAILED( result ) )
		return ;
}

Bool CImplMswPad::IsAvailable() const
{
	return m_Pad != NULL;
}

Void CImplMswPad::PrintState() const
{
	DebugLogInfo(	"\nLeftStick(%f %f) RightStick(%f %f)\n"
					"Up(%d) Right(%d) Down(%d) Left(%d)\n"
					"Tri(%d) circle(%d) Cross(%d) Square(%d)"
					"L1(%d) L2(%d) L3(%d)"
					"R1(%d) R2(%d) R3(%d)"
					"Select(%d) Start(%d) PS(%d)",

					GetAnalogStick( 0 ).GetX(), GetAnalogStick(0).GetY(),
					GetAnalogStick( 1 ).GetX(), GetAnalogStick(1).GetY(),
					GetButton(0), GetButton(1), GetButton(2), GetButton(3),
					GetButton(4), GetButton(5), GetButton(6), GetButton(7),
					GetButton(8), GetButton(9), GetButton(10), 
					GetButton(11), GetButton(12), GetButton(13),
					GetButton(14), GetButton(15), GetButton(16)
					);
}
