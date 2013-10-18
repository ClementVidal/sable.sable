#ifndef _SABLE_CORE_MEMORY_MANAGER_
#define _SABLE_CORE_MEMORY_MANAGER_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/Singleton.h>
#include <Sable/Core/Memory/BuddyHeap.h>
#include <Sable/Core/Memory/StackHeap.h>
#include <Sable/Core/Memory/MallocHeap.h>
#include <Sable/Core/Memory/FreeListHeap.h>
#include <Sable/Core/Memory/Heap.h>

#include <Sable/Core/Memory/Impl/Header.h> 

#define MEMORYMANAGER_MAXHEAP 128

#define		MemoryManager  Sable::CMemoryManager::GetInstance()

namespace Sable
{

/** 
\ingroup CoreMemory
Core manager
*/
class CMemoryManager : public CSingleton<CMemoryManager>
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CMemoryManager();
	virtual ~CMemoryManager();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
	UInt32				GetAllocatedPageCount() const;
	SysSize				GetPageSize() const;
	UInt32				GetHeapCount() const;
	CMemoryHeap&		GetHeapAtIndex( UInt32 i ) const;
	UInt32				GetAllocatedBytes() const;
	UInt32				GetReservedBytes() const;

	CMemoryHeap&		GetBuddyHeap();
	CMemoryStackHeap&	GetStackHeap();

	CMemoryHeap&		GetEventHeap();
    //@}

	/** @name Manipulator*/
	//@{
	Void*	AllocPages( SysSize size );
	Void	FreePages( Void* pages );
	//@}

private:

	// Friendship
	friend class CMemoryHeap;

	// DataTypes
	struct SPagesHeader
	{
		UInt32 Size;
		UInt32 PageCount;
	};

	// Methods
	Void	RegisterHeap( CMemoryHeap& h );
	Void	UnRegisterHeap( CMemoryHeap& h );

	// Attributes
	UInt32				m_HeapCount;
	CMemoryHeap*		m_HeapTable[MEMORYMANAGER_MAXHEAP];

#ifdef SETUP_PROJECT_DUNE
	CMemoryMallocHeap	m_BuddyHeap;
	CMemoryMallocHeap	m_EventHeap;
#else
	CMemoryBuddyHeap	m_BuddyHeap;
	CMemoryFreeListHeap	m_EventHeap;
#endif

	CMemoryStackHeap	m_StackHeap;

	UInt32				m_AllocatedPages;
	
	// Impl
	CImplMemoryManager        m_Impl;
};


}

#endif


