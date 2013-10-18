#ifndef _CORE_MEMORY_POOLHEAP_
#define _CORE_MEMORY_POOLHEAP_

#include <Sable/Core/Memory/Heap.h>

namespace Sable
{

/**
\ingroup CoreMemory
Define a simple free list allocator
*/
class CMemoryFreeListHeap : public CMemoryHeap
{
	
public:

	/** @name Constructor*/
	//@{
	CMemoryFreeListHeap( String name = "" );
	virtual ~CMemoryFreeListHeap();
	//@}

	/** @name Accessors*/
	//@{
	UInt32	GetSlotCount() const;
	UInt32	GetAllocatedSlotCount() const;
	EType	GetType() const;
	//@}

	/** @name manipulator*/
	//@{
    Void			Initialize( CMemoryHeap* parent, UInt32 slotCount, SysSize slotSize, UInt8 align = 4 );
	virtual Void*   Allocate( SysSize size ) ;
	virtual Void    Free( Void* object );
	//@}

private:

	// Type
    struct SSlot
    {
        SSlot* Next;
    };

	// Methods
    Void SetupMemory( );
	Void FreeReservedMemory();

	// Attribute
	SSlot*			m_NextFree;
    Byte*			m_AlignedBaseAdress;
    UInt32			m_SlotCount;
	UInt32			m_AllocatedSlotCount;
    SysSize			m_SlotSize;
    SysSize			m_EffectiveSlotSize;
	CMemoryHeap*	m_ParentHeap;
};


}

#endif
