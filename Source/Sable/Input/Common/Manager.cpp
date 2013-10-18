#include <Sable/Input/Common/Manager.h>

#include <Sable/Input/Mouse/Interface.h>
#include <Sable/Input/Keyboard/Interface.h>
#include <Sable/Input/Pad/Interface.h>

using namespace Sable;


CInputManager::CInputManager()
{
    m_Pad = NULL;
    m_Mouse = NULL;
    m_Keyboard = NULL;
}

CInputManager::~CInputManager()
{
}

Void CInputManager::SetMouse( CMouseInterface* mouse )
{
    m_Mouse = mouse;
}

Void CInputManager::SetKeyboard( CKeyboardInterface* kbd )
{
    m_Keyboard = kbd;
}

Void CInputManager::SetPad( CPadInterface* pad )
{
    m_Pad = pad;
}

Void CInputManager::Update()
{
	DebugProfile("CInputManager::Update" );

	if( m_Mouse )
        m_Mouse->Update();

    if( m_Keyboard )
        m_Keyboard->Update();

    if( m_Pad )
        m_Pad->Update();
}

Void CInputManager::Initialize( )
{

}

Void CInputManager::UnInitialize()
{
    m_Pad = NULL;
    m_Mouse = NULL;
    m_Keyboard = NULL;
}
