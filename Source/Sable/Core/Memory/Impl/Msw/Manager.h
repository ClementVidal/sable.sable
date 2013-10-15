#ifndef _SABLE_CORE_MEMORY_IMPL_MSW_MANAGER_
#define _SABLE_CORE_MEMORY_IMPL_MSW_MANAGER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Memory\Impl\Stub\Manager.h>

namespace Sable
{

/** 
*/
class CImplMswMemoryManager : public CImplStubMemoryManager
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplMswMemoryManager( CMemoryManager& publicImpl );
    ~CImplMswMemoryManager();
    //@}

	/** @name Manipulator*/
	//@{
	SysSize	GetPageSize() const;
	Void*	AllocPages( SysSize size );
	Bool	FreePages( Void* pages );
	//@}

protected:

    // Attributes

};

}

#endif
