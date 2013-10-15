#ifndef _SABLE_CORE_THREAD_CRITICALSECTION_
#define _SABLE_CORE_THREAD_CRITICALSECTION_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Setup.h>

#include <Sable\Core\Thread\Impl\Header.h>

namespace Sable
{

/** 
\ingroup CoreThread
Critical section implementation
*/
class CCriticalSection
{

public:

	/** @name DataTypes*/
    //@{
    //@}

	/** @name Constructor/Destructor*/
    //@{
    CCriticalSection( );
	virtual ~CCriticalSection();
    //@}

	/** @name Accessor*/
    //@{
    //@}

    /** @name Manipulator*/
    //@{
    Void Enter();
    Void Leave();
    //@}

private:

    //Types

    //Methods

    //Attributes
    CImplCriticalSection           m_Impl;

};

}

#endif
