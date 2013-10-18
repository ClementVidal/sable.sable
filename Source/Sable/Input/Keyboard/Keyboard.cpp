#include <Sable/Input/Keyboard/Keyboard.h>

#include <Sable/Input/Common/Impl/Header.h>
#include <Sable/Input/Common/Manager.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CKeyboard, CKeyboardInterface );

CKeyboard::CKeyboard( CApplicationWindow& window ) : 
    CKeyboardInterface( window ),
	m_Impl(*this)
{
}

CKeyboard::~CKeyboard()
{

}

Void CKeyboard::Update()
{
	m_Impl.Update();
}

Bool CKeyboard::GetIsKeyDown( const EKeyboardEventData key ) const 
{
	return m_Impl.GetIsKeyDown( key );
}
