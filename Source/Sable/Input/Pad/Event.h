#ifndef _SABLE_INPUT_PAD_EVENT_
#define _SABLE_INPUT_PAD_EVENT_

#include <Sable/Core/Common/DataTypes.h>

/** 
\file Sable\Input\Pad\PadEvent.h
Pad events data and pad events type
*/


namespace Sable
{

/**
\ingroup InputPad
Pad event data
*/
enum EPadEventData
{
	nPadEventData_Count,
	nPadEventData_None = -1
};

/**
\ingroup InputPad
Pad event type
*/
enum EPadEventType
{
	nPadEventType_BtnDown =1,
	nPadEventType_BtnUp,
	nPadEventType_AnalogStickChange,
	nPadEventType_AnalogBtnChange,

	nPadEventType_Count,
	nPadEventType_None = -1
};

}

#endif


