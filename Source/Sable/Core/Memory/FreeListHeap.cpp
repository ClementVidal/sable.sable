#include <Sable/Core/Memory/FreeListHeap.h>

using namespace Sable;

CMemoryFreeListHeap::CMemoryFreeListHeap( String name ) :
    CMemoryHeap( name )
{
    m_SlotSize = 0;
	m_ReservedSize = 0;
    m_NextFree = NULL;
    m_AlignedBaseAdress = NULL;
    m_Align = 0;
    m_SlotCount = 0;
	m_ParentHeap = NULL;
	m_AllocatedSlotCount = 0;
}

CMemoryFreeListHeap::~CMemoryFreeListHeap()
{
	DumpAlloc();
    FreeReservedMemory();
}

Void CMemoryFreeListHeap::FreeReservedMemory()
{
	if( m_BaseAddress )
	{
		if( m_ParentHeap )
			MemoryFree( *m_ParentHeap, m_BaseAddress );
		else
			CoreManager.GetMemoryManager().FreePages( m_BaseAddress );

		m_BaseAddress = NULL;
	}
}

/**
Initialize all related variable and allocate the effective heap size
*/
Void CMemoryFreeListHeap::Initialize( CMemoryHeap* parent, UInt32 slotCount, SysSize slotSize, UInt8 align )
{
	FreeReservedMemory();

#ifdef SETUP_MEMORY_TRACKER
	slotSize = slotSize + GetHeaderSize();
#endif

	m_ParentHeap = parent;

    // Compute an aligned slot size
    m_EffectiveSlotSize = MemoryGetAlignedSize( slotSize+sizeof( SSlot ), align );

    // Compute total heap size + align to avoid overflow after re alignement
    m_ReservedSize = slotCount * m_EffectiveSlotSize + align;
    m_SlotSize = slotSize;

	// Allocate memory either from an existing heap or from the system directly
	if( m_ParentHeap )
		m_BaseAddress = MemoryAllocate( *m_ParentHeap, m_ReservedSize + align ); 
	else
		m_BaseAddress = CoreManager.GetMemoryManager().AllocPages( m_ReservedSize + align );

	// Store the aligned base adress
    m_AlignedBaseAdress = (Byte*) MemoryGetAlignedAddress( m_BaseAddress, align );
    m_NextFree = ( SSlot* ) m_AlignedBaseAdress;
    m_Align = align;
    m_SlotCount = slotCount;
    SetupMemory( );
}

/**
Setup the memory to create the linked list of free block
*/
Void CMemoryFreeListHeap::SetupMemory( )
{
    SysSize size = 0;
    SysSize offset = 0;
    SSlot* sh;
    UInt32 realSlotCount = 0;

    sh = ( SSlot* )m_AlignedBaseAdress;

    while ( size + m_EffectiveSlotSize <= m_ReservedSize && realSlotCount <= m_SlotCount ) 
    {
        sh->Next = (SSlot*) (((Byte*)sh) + m_EffectiveSlotSize);
		DebugAssertMsg( MemoryIsAddressAligned( sh->Next, m_Align ), "Memory not correctly aligned" );
        if( realSlotCount < m_SlotCount - 1 )
        {
            sh = sh->Next;
        }
        size += m_EffectiveSlotSize;

        realSlotCount ++;
    }

    sh->Next = (SSlot*) NULL;

    DebugAssertMsg( realSlotCount == m_SlotCount, "CMemoryFreeListHeap::SetupMemory - Failled to setup correctly memory layout" );
    
    m_NextFree = ( SSlot* )m_AlignedBaseAdress;

}

Void* CMemoryFreeListHeap::Allocate( SysSize size)
{
    DebugAssert( size <= m_SlotSize );
	DebugAssert( m_AllocatedSlotCount + 1 <= m_SlotCount );

    if( (Void*)m_NextFree != NULL )
    {
        SSlot* tmp = m_NextFree;
        m_NextFree = m_NextFree->Next;
        tmp->Next = NULL;
        Byte* ptr = ((Byte*)tmp) + MemoryGetAlignedSize( sizeof( SSlot ), m_Align );

#ifdef SETUP_CONFIG_DEBUG
        MemoryFill( ptr, 0xcd, m_SlotSize );
#endif

		m_AllocatedSlotCount++;

        DebugAssertMsg( MemoryIsAddressAligned( ptr, m_Align ), "Memory not correctly aligned" );

		CMemoryHeap::OnAllocate( (UInt32) m_EffectiveSlotSize );
		
		return ptr;
    }

    DebugError( "CMemoryFreeListHeap::Allocate - Not enough memory in pool heap" );
    return NULL;
}

/**
The released object memory slot is inserted at the beggining of the linked list and will become the next free slot
*/
Void CMemoryFreeListHeap::Free( Void* object )
{
	DebugAssert( m_AllocatedSlotCount > 0 );

    if( object != NULL ) 
    {
        SSlot* sh = (SSlot*) (((Byte*)object) - MemoryGetAlignedSize( sizeof( SSlot ), m_Align ));
        sh->Next = m_NextFree;
        m_NextFree = sh;
		m_AllocatedSlotCount--;

#ifdef SETUP_CONFIG_DEBUG
		MemoryFill( object, 0xcd, m_SlotSize );
#endif

		CMemoryHeap::OnFree( (UInt32) m_EffectiveSlotSize );
    }
}

UInt32 CMemoryFreeListHeap::GetSlotCount() const
{
	return m_SlotCount;
}

UInt32 CMemoryFreeListHeap::GetAllocatedSlotCount() const
{
	return m_AllocatedSlotCount;
}

CMemoryHeap::EType CMemoryFreeListHeap::GetType() const
{
	return nType_FreeListHeap;
}