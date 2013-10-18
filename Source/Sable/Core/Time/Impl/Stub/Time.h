#ifndef _SABLE_CORE_TIME_IMPL_STUB_TIME_
#define _SABLE_CORE_TIME_IMPL_STUB_TIME_

#include <Sable/Core/Common/DataTypes.h>

namespace Sable
{

/** 

*/
class CImplStubTime
{

public:

    /** @name Constructor/Destructor*/
    //@{
	CImplStubTime( ) {};
    virtual ~CImplStubTime() {};
    //@}

    /** @name Accessors*/
    //@{
    //@}

    /** @name Manipulator*/
    //@{
	virtual Int64		GetTimerTime() const { return 0; }	
    virtual Int64       GetTimerFreq() const { return 0; }
    //@}

protected:

    // Attributes

};

}

#endif
