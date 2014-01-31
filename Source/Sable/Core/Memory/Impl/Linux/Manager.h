#ifndef _SABLE_CORE_MEMORY_IMPL_LINUX_MANAGER_
#define _SABLE_CORE_MEMORY_IMPL_LINUX_MANAGER_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Memory/Impl/Stub/Manager.h>

namespace Sable
{

/** 
*/
class CImplLinuxMemoryManager : public CImplStubMemoryManager
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplLinuxMemoryManager( CMemoryManager& publicImpl );
    ~CImplLinuxMemoryManager();
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
