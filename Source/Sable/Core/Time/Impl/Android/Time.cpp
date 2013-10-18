#include <Sable/Core/Time/Impl/Android/Time.h>

using namespace Sable;

CImplAndroidTime::CImplAndroidTime() :
	CImplStubTime()
{
	timespec t;
	clock_getres( CLOCK_MONOTONIC, &t );
	m_Freq = 1000000000 / t.tv_nsec;
}

CImplAndroidTime::~CImplAndroidTime()
{
}

Int64 CImplAndroidTime::GetTimerFreq() const
{
	return m_Freq;
}

Int64 CImplAndroidTime::GetTimerTime() const
{
	timespec t;
	clock_getres( CLOCK_MONOTONIC, &t );

	return  t.tv_nsec;
}
