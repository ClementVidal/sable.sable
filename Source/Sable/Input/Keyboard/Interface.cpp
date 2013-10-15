#include <Sable\Input\Keyboard\Interface.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CKeyboardInterface );

CKeyboardInterface::CKeyboardInterface( CApplicationWindow& window )
{
    m_AttachedWindow = &window;
}

CKeyboardInterface::~CKeyboardInterface()
{

}

CApplicationWindow& CKeyboardInterface::GetAttachedWindow() const
{
    return *m_AttachedWindow;
}

Char CKeyboardInterface::KeyboardEventToAscii( EKeyboardEventData key )
{
    switch( key ) {
        case nKeyboardEventData_1:
            return '1';
        case nKeyboardEventData_2:
            return '2';
        case nKeyboardEventData_3:
            return '3';
        case nKeyboardEventData_4:
            return '4';
        case nKeyboardEventData_5:
            return '5';
        case nKeyboardEventData_6:
            return '6';
        case nKeyboardEventData_7:
            return '7';
        case nKeyboardEventData_8:
            return '8';
        case nKeyboardEventData_9:
            return '9';
        case nKeyboardEventData_0:
            return '0';
        case nKeyboardEventData_Minus:
            return '-';
        case nKeyboardEventData_Equals:
            return '=';
        case nKeyboardEventData_A:
            return 'a';
        case nKeyboardEventData_Z:
            return 'z';
        case nKeyboardEventData_E:
            return 'e';
        case nKeyboardEventData_R:
            return 'r';
        case nKeyboardEventData_T:
            return 't';
        case nKeyboardEventData_Y:
            return 'y';
        case nKeyboardEventData_U:
            return 'u';
        case nKeyboardEventData_I:
            return 'i';
        case nKeyboardEventData_O:
            return 'o';
        case nKeyboardEventData_P:
            return 'p';
        case nKeyboardEventData_LeftBracket:
            return '(';
        case nKeyboardEventData_RightBracket:
            return ')';
        case nKeyboardEventData_Q:
            return 'q';
        case nKeyboardEventData_S:
            return 's';
        case nKeyboardEventData_D:
            return 'd';
        case nKeyboardEventData_F:
            return 'f';
        case nKeyboardEventData_G:
            return 'g';
        case nKeyboardEventData_H:
            return 'h';
        case nKeyboardEventData_J:
            return 'j';
        case nKeyboardEventData_K:
            return 'k';
        case nKeyboardEventData_L:
            return 'l';
        case nKeyboardEventData_M:
            return 'm';
        case nKeyboardEventData_Apostrophe:
            return '\'';
        case nKeyboardEventData_W:
            return 'w';
        case nKeyboardEventData_X:
            return 'x';
        case nKeyboardEventData_C:
            return 'c';
        case nKeyboardEventData_V:
            return 'v';
        case nKeyboardEventData_B:
            return 'b';
        case nKeyboardEventData_N:
            return 'n';
        case nKeyboardEventData_Semicolon:
            return ';';
        case nKeyboardEventData_Comma:
            return ',';
        case nKeyboardEventData_Period:
            return '.';
        case nKeyboardEventData_Slash:
            return '/';
        case nKeyboardEventData_Multiply:
            return '*';
        case nKeyboardEventData_Space:
            return ' ';

    }
    return ' ';
}