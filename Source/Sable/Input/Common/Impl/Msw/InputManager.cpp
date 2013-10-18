#include <Sable/Input/Common/Impl/Msw/InputManager.h>

#include <Sable/Graphics/Common/Impl/DirectX/GraphicsManagerHelper.h>

using namespace Sable;

CImplMswInputManager::CImplMswInputManager():
	CImplStubInputManager()
{
	HINSTANCE 
		g_hinst;

	g_hinst = (HINSTANCE)GetModuleHandle(NULL);

	AssertDXCall( 
		DirectInput8Create(
		g_hinst, 
		DIRECTINPUT_VERSION, 
		IID_IDirectInput8, 
		(void**)&m_DirectInputObject, 
		NULL
		) 
		);
}

CImplMswInputManager::~CImplMswInputManager()
{
	m_DirectInputObject->Release();	
}
