#ifndef _SABLE_CORE_THREAD_IMPL_STUB_CRITICALSECTION_
#define _SABLE_CORE_THREAD_IMPL_STUB_CRITICALSECTION_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CCriticalSection;

/** 
*/
class CImplStubCriticalSection
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplStubCriticalSection( CCriticalSection& publicImpl ){ m_PublicImpl = &publicImpl; }
    virtual ~CImplStubCriticalSection() {}
    //@}

	/** @name Manipulator*/
	//@{
    virtual Void Enter() {};
    virtual Void Leave() {};
	//@}

protected:

	// Attributes
	CCriticalSection*        m_PublicImpl;

};

}

#endif
