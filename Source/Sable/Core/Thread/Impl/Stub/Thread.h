#ifndef _SABLE_CORE_THREAD_IMPL_THREAD_
#define _SABLE_CORE_THREAD_IMPL_THREAD_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CThread;

/** 
*/
class CImplStubThread
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplStubThread( CThread& publicImpl, UInt32 stackSize ){ m_PublicImpl = &publicImpl; }
    virtual ~CImplStubThread() {}
    //@}

    /** @name Accessors*/
    //@{
    Bool IsFinished() const { return TRUE; }
    //@}

	/** @name Manipulator*/
	//@{
    virtual Void Start( ) {}
	//@}

protected:

	// Attributes
	CThread*        m_PublicImpl;

};

}

#endif
