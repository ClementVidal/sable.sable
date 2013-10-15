#ifndef _SABLE_CORE_TIME_TIMER_
#define _SABLE_CORE_TIME_TIMER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Collection\BitArray.h>

#include <Sable\Setup.h>

#include <Sable\Core\Time\Impl\Header.h>

namespace Sable
{

/** 
\ingroup CoreTime
Precision Timer. 
*/
class CTimer
{

public:

	/** @name Constructor/Destructor*/
    //@{
	CTimer( );
	virtual ~CTimer();
    //@}

	/** @name Accessor*/
    //@{
    Bool    IsStarted() const;
	Bool    IsSuspended() const;
	Float64	GetElapsedSeconds() const;
	Float64	GetElapsedMilliseconds() const;
	Float64	GetElapsedHours() const;
	Int64	GetElapsedTicks() const;
	Int64	GetTicksFreq() const;
    //@}

	/** @name Manipulator*/
	//@{
	Void Start();	
	Void Stop();	
	Void Suspend();
	Void Resume();
	//@}

private:

    //Types
    enum ETimerState
	{
		nTimerState_On = 1,
		nTimerState_Hold,
	};

    //Methods

    //Attributes
	mutable Int64			m_StartTime;
	mutable Int64			m_StopTime;
	mutable Int64			m_StartPause;
	mutable Int64			m_TotalPause;

	CBitArray32				m_State;

    CImplTime           	m_Impl;

    //Static Attributes

};

}

#endif
