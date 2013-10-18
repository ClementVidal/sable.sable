#include <Sable/Core/Time/Timer.h>

#include <Sable/Core/Common/Manager.h>

using namespace Sable;

CTimer::CTimer( )
{
	m_State.SetBit( nTimerState_On, FALSE );
	m_StartPause				= 0;
	m_TotalPause				= 0;
	m_StartTime					= 0;
	m_StopTime					= 0;
}

CTimer::~CTimer()
{
}

/** 
Start the timer
*/
Void CTimer::Start()
{
	Stop();
	m_StartPause				= 0;
	m_TotalPause				= 0;
	m_StopTime					= 0;
	m_State.SetBit( nTimerState_On, TRUE );
	m_StartTime					= m_Impl.GetTimerTime();
}

Bool CTimer::IsStarted() const
{
    return m_State.GetBit( nTimerState_On );
}

Bool CTimer::IsSuspended() const
{
	return m_State.GetBit( nTimerState_Hold );
}

Int64 CTimer::GetElapsedTicks() const
{
	Int64 time;

	if( m_State.GetBit( nTimerState_On ) )
	{
		Int64 t = m_Impl.GetTimerTime();
		time =  ( t - m_StartTime ) - m_TotalPause;
	}
	else
	{
		time = ( m_StopTime - m_StartTime ) - m_TotalPause;
	}

	return time;
}

Int64 CTimer::GetTicksFreq() const
{
	return m_Impl.GetTimerFreq();
}

/** Stop the timer
*/
Void CTimer::Stop()
{
	m_StopTime = m_Impl.GetTimerTime();
	
	if( m_State.GetBit( nTimerState_Hold ) )
	{
		m_TotalPause = m_StopTime - m_StartPause;
	}

	m_State.SetBit( nTimerState_On, FALSE );
}

/** Suspend the timer
*/
Void CTimer::Suspend()
{
	if( m_State.GetBit( nTimerState_On ) )
	{
		m_StartPause = m_Impl.GetTimerTime();
		m_State.SetBit( nTimerState_Hold, TRUE );
	}
}

/** Restart the timer from where it was suspended
*/
Void CTimer::Resume()	
{
	if( m_State.GetBit( nTimerState_Hold ) )
	{
		Int64 t = m_Impl.GetTimerTime();
		m_TotalPause += t - m_StartPause;
		m_State.SetBit( nTimerState_Hold, FALSE );
	}
}

/** Get elapsed second since timer start
*/
Float64 CTimer::GetElapsedSeconds() const
{
	return (Float64) GetElapsedTicks() / GetTicksFreq();
}

/** Get elapsed millisecond since timer start
*/
Float64 CTimer::GetElapsedMilliseconds() const
{
	return GetElapsedSeconds() * 1000.0;
}


