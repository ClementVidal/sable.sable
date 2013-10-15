#ifndef _SABLE_CORE_MEMORY_IMPL_STUB_MANAGER_
#define _SABLE_CORE_MEMORY_IMPL_STUB_MANAGER_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CMemoryManager;

/** 
*/
class CImplStubMemoryManager
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplStubMemoryManager( CMemoryManager& publicImpl ) { m_PublicImpl = &publicImpl; }
    virtual ~CImplStubMemoryManager() {};
    //@}

	/** @name Manipulator*/
	//@{
	virtual	SysSize	GetPageSize() const { return 0; }
	virtual Void*	AllocPages( SysSize size ) { return NULL; }
	virtual Bool	FreePages( Void* pages ) { return FALSE; }
	//@}

protected:

    // Attributes
    CMemoryManager*  m_PublicImpl;
};

}

#endif
