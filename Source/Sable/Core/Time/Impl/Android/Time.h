#ifndef _SABLE_CORE_TIME_IMPL_ANDROID_TIME_
#define _SABLE_CORE_TIME_IMPL_ANDROID_TIME_

#include <Sable\Core\Time\Impl\Stub\Time.h>

#include <time.h>

namespace Sable
{

/** 
*/
class CImplAndroidTime : public CImplStubTime
{

public:

    /** @name Constructor/Destructor*/
    //@{
	CImplAndroidTime();
    virtual ~CImplAndroidTime();
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
	time_t	m_Freq;

};

}

#endif
