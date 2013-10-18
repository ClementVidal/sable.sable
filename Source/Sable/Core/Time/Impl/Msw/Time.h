#ifndef _SABLE_CORE_TIME_IMPL_MSW_TIME_
#define _SABLE_CORE_TIME_IMPL_MSW_TIME_

#include <Sable/Core/Time/Impl/Stub/Time.h>

#ifdef SETUP_IMPLTYPE_MSW

#include <Windows.h>
#endif

namespace Sable
{

/** 
*/
class CImplMswTime : public CImplStubTime
{

public:

    /** @name Constructor/Destructor*/
    //@{
	CImplMswTime();
    virtual ~CImplMswTime();
    //@}

    /** @name Accessors*/
    //@{
	Int64		GetTimerTime() const;
	Int64       GetTimerFreq() const;
	//@}

	/** @name Manipulator*/
	//@{
	//@}

private:

	// Attributes
	LONGLONG	m_Freq;
};

}

#endif

