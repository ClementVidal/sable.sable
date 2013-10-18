#ifndef _SABLE_CORE_THREAD_THREAD_
#define _SABLE_CORE_THREAD_THREAD_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Event/Header.h>
#include <Sable/Setup.h>

#include <Sable/Core/Thread/Impl/Header.h>

namespace Sable
{

class CThread;

/** 
\ingroup CoreThread
CPU thread
*/
class CThread
{

public:

	/** @name DataTypes*/
    //@{
    //@}

	/** @name Constructor/Destructor*/
    //@{
    CThread( UInt32 stackSize = (1024*512) );
	virtual ~CThread();
    //@}

	/** @name Accessor*/
    //@{
    Bool    IsFinished() const;
    //@}

    /** @name Manipulator*/
    //@{
    Void Start( );
    //@}

    /** @name Manipulator*/
    //@{
    virtual Void Entry() = 0;
    //@}

private:

    // Friendship 

    // Types

    // Methods

    // Attributes
    CImplThread        m_Impl;

};

}

#endif
