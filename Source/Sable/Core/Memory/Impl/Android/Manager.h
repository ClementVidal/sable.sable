#ifndef _SABLE_CORE_MEMORY_IMPL_ANDROID_MANAGER_
#define _SABLE_CORE_MEMORY_IMPL_ANDROID_MANAGER_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Memory/Impl/Stub/Manager.h>

namespace Sable
{

/** 
*/
class CImplAndroidMemoryManager : public CImplStubMemoryManager
{

public:

    /** @name Constructor/Destructor*/
    //@{
	CImplAndroidMemoryManager( CMemoryManager& publicImpl );
    ~CImplAndroidMemoryManager();
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
