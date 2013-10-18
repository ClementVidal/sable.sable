#ifndef _SABLE_INPUT_MOUSE_EVENT_
#define _SABLE_INPUT_MOUSE_EVENT_

#include <Sable/Core/Common/DataTypes.h>

/** 
\file Sable\Input\Mouse\MouseEvent.h
Basic string primitives
*/


/**
\ingroup InputMouse
Mouse data
*/
enum EMouseEventData
{
	nMouseEventData_LeftBtn         = 0x00,
	nMouseEventData_RightBtn         = 0x01,
	nMouseEventData_MiddleBtn         = 0x02,
	nMouseEventData_AxisX		= 0x08,
	nMouseEventData_AxisY		= 0x09,
	nMouseEventData_AxisZ		= 0x0a,

	nMouseEventData_Count,
	nMouseEventData_None = -1
};

/**
\ingroup InputMouse
Mouse event type
*/
enum EMouseEventType
{
	nMouseEventType_KeyDown =1,
	nMouseEventType_KeyUp,
	nMouseEventType_Move,

	nMouseEventType_Count,
	nMouseEventType_None = -1
};


#endif


