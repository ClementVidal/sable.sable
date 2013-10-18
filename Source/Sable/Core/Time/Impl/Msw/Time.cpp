#include <Sable/Core/Time/Impl/Msw/Time.h>

using namespace Sable;

CImplMswTime::CImplMswTime() :
    CImplStubTime()
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	m_Freq = frequency.QuadPart;
}

CImplMswTime::~CImplMswTime()
{
}

Int64 CImplMswTime::GetTimerFreq() const
{
	return m_Freq;
}

Int64 CImplMswTime::GetTimerTime() const
{
	LARGE_INTEGER sample;

	QueryPerformanceCounter(&sample);

	return  sample.QuadPart;
}
