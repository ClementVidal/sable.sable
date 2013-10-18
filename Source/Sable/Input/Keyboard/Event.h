#ifndef _SABLE_INPUT_KEYBOARD_EVENT_
#define _SABLE_INPUT_KEYBOARD_EVENT_

#include <Sable/Core/Common/DataTypes.h>

/** 
\file Sable\Input\Keyboard\KeyboardEvent.h
*/


/**
\ingroup InputKeyboard
Keyboard event data
*/
enum EKeyboardEventData
{
	nKeyboardEventData_Escape         = 0x01,
	nKeyboardEventData_1              = 0x02,
	nKeyboardEventData_2              = 0x03,
	nKeyboardEventData_3              = 0x04,
	nKeyboardEventData_4              = 0x05,
	nKeyboardEventData_5              = 0x06,
	nKeyboardEventData_6              = 0x07,
	nKeyboardEventData_7              = 0x08,
	nKeyboardEventData_8              = 0x09,
	nKeyboardEventData_9              = 0x0A,
	nKeyboardEventData_0              = 0x0B,
	nKeyboardEventData_Minus          = 0x0C,   /* - on main keyboard */
	nKeyboardEventData_Equals         = 0x0D,
	nKeyboardEventData_Back           = 0x0E,   /* backspace */
	nKeyboardEventData_Tab            = 0x0F,
	nKeyboardEventData_A              = 0x10,
	nKeyboardEventData_Z              = 0x11,
	nKeyboardEventData_E              = 0x12,
	nKeyboardEventData_R              = 0x13,
	nKeyboardEventData_T              = 0x14,
	nKeyboardEventData_Y              = 0x15,
	nKeyboardEventData_U              = 0x16,
	nKeyboardEventData_I              = 0x17,
	nKeyboardEventData_O              = 0x18,
	nKeyboardEventData_P              = 0x19,
	nKeyboardEventData_LeftBracket    = 0x1A,
	nKeyboardEventData_RightBracket   = 0x1B,
	nKeyboardEventData_Return         = 0x1C,    /* Enter on main keyboard */
	nKeyboardEventData_LeftControl    = 0x1D,
	nKeyboardEventData_Q              = 0x1E,
	nKeyboardEventData_S              = 0x1F,
	nKeyboardEventData_D              = 0x20,
	nKeyboardEventData_F              = 0x21,
	nKeyboardEventData_G              = 0x22,
	nKeyboardEventData_H              = 0x23,
	nKeyboardEventData_J              = 0x24,
	nKeyboardEventData_K              = 0x25,
	nKeyboardEventData_L              = 0x26,
	nKeyboardEventData_M				= 0x27,
	nKeyboardEventData_Apostrophe     = 0x28,
	nKeyboardEventData_Grave          = 0x29,    /* accent grave */
	nKeyboardEventData_LeftShift       = 0x2A,
	nKeyboardEventData_BackSlash      = 0x2B,
	nKeyboardEventData_W              = 0x2C,
	nKeyboardEventData_X              = 0x2D,
	nKeyboardEventData_C              = 0x2E,
	nKeyboardEventData_V              = 0x2F,
	nKeyboardEventData_B              = 0x30,
	nKeyboardEventData_N              = 0x31,
	nKeyboardEventData_Semicolon      = 0x32,
	nKeyboardEventData_Comma          = 0x33,
	nKeyboardEventData_Period         = 0x34,    /* . on main keyboard */
	nKeyboardEventData_Slash          = 0x35,    /* / on main keyboard */
	nKeyboardEventData_RightShift		= 0x36,
	nKeyboardEventData_Multiply       = 0x37,    /* * on numeric keypad */
	nKeyboardEventData_LeftAlt       = 0x38,    /* left Alt */
	nKeyboardEventData_Space          = 0x39,
	nKeyboardEventData_Capital        = 0x3A,
	nKeyboardEventData_F1             = 0x3B,
	nKeyboardEventData_F2             = 0x3C,
	nKeyboardEventData_F3             = 0x3D,
	nKeyboardEventData_F4             = 0x3E,
	nKeyboardEventData_F5             = 0x3F,
	nKeyboardEventData_F6             = 0x40,
	nKeyboardEventData_F7             = 0x41,
	nKeyboardEventData_F8             = 0x42,
	nKeyboardEventData_F9             = 0x43,
	nKeyboardEventData_F10            = 0x44,
	nKeyboardEventData_NumLock        = 0x45,
	nKeyboardEventData_Scroll         = 0x46,    /* Scroll Lock */
	nKeyboardEventData_NumPad7        = 0x47,
	nKeyboardEventData_NumPad8        = 0x48,
	nKeyboardEventData_NumPad9        = 0x49,
	nKeyboardEventData_Substract      = 0x4A,    /* - on numeric keypad */
	nKeyboardEventData_NumPad4        = 0x4B,
	nKeyboardEventData_NumPad5        = 0x4C,
	nKeyboardEventData_NumPad6        = 0x4D,
	nKeyboardEventData_Add            = 0x4E,    /* + on numeric keypad */
	nKeyboardEventData_NumPad1        = 0x4F,
	nKeyboardEventData_NumPad2        = 0x50,
	nKeyboardEventData_NumPad3        = 0x51,
	nKeyboardEventData_NumPad0        = 0x52,
	nKeyboardEventData_Decimal        = 0x53,    /* . on numeric keypad */
	nKeyboardEventData_NumPadEnter    = 0x9C,    /* Enter on numeric keypad */
	nKeyboardEventData_RightControl   = 0x9D,
    nKeyboardEventData_PowerOfTwo   = 0x94,
	nKeyboardEventData_DIVIDE         = 0xB5,    /* / on numeric keypad */
	nKeyboardEventData_SYSRQ          = 0xB7,
	nKeyboardEventData_RightMenu          = 0xB8,    /* right Alt */
	nKeyboardEventData_PAUSE          = 0xC5,    /* Pause */
	nKeyboardEventData_HOME           = 0xC7,    /* Home on arrow keypad */
	nKeyboardEventData_UP             = 0xC8,    /* UpArrow on arrow keypad */
	nKeyboardEventData_PRIOR          = 0xC9,    /* PgUp on arrow keypad */
	nKeyboardEventData_LEFT           = 0xCB,    /* LeftArrow on arrow keypad */
	nKeyboardEventData_RIGHT          = 0xCD,    /* RightArrow on arrow keypad */
	nKeyboardEventData_END            = 0xCF,    /* End on arrow keypad */
	nKeyboardEventData_DOWN           = 0xD0,    /* DownArrow on arrow keypad */
	nKeyboardEventData_NEXT           = 0xD1,    /* PgDn on arrow keypad */
	nKeyboardEventData_INSERT         = 0xD2,    /* Insert on arrow keypad */
	nKeyboardEventData_DELETE         = 0xD3,    /* Delete on arrow keypad */

	nKeyboardEventData_Count,
	nKeyboardEventData_None = -1
};

/**
\ingroup InputKeyboard
Keyboard event type
*/
enum EKeyboardEventType
{
	nKeyboardEventType_KeyUp = 1,
	nKeyboardEventType_KeyDown,

	nKeyboardEventType_KeyCount,
	nKeyboardEventType_KeyNone = -1
};


#endif


