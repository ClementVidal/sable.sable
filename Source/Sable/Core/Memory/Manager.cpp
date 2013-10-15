#include <Sable\Core\Memory\Manager.h>

using namespace Sable;

CMemoryManager::CMemoryManager() :
	m_HeapCount( 0 ),
	m_BuddyHeap( "Manager" ),
	m_StackHeap( "Manager" ),
	m_Impl( *this )
{
#ifndef SETUP_PROJECT_DUNE
	m_BuddyHeap.Initialize( NULL, MegaBytesToBytes( 32 ) );
#endif

	m_StackHeap.Initialize( NULL, MegaBytesToBytes( 17 ) );	
	
	m_EventHeap.Initialize( NULL, 1024*4, sizeof( CList<Void*>::Node ) );
	m_AllocatedPages = 0;
}

CMemoryManager::~CMemoryManager()
{
}

/**
Specific heap used only to allocate memory for the event signal/slot subsystem
*/
CMemoryHeap& CMemoryManager::GetEventHeap()
{
	return m_EventHeap;
}

/**
Return the default Buddy heap
*/
CMemoryHeap& CMemoryManager::GetBuddyHeap() 
{
    return m_BuddyHeap;
}

/**
Return the default Stack heap
*/
CMemoryStackHeap& CMemoryManager::GetStackHeap() 
{
	return m_StackHeap;
}


UInt32	CMemoryManager::GetHeapCount() const
{
	return m_HeapCount;
}

CMemoryHeap& CMemoryManager::GetHeapAtIndex( UInt32 i ) const
{
	DebugAssert( i < m_HeapCount );
	return *m_HeapTable[i];
}

Void CMemoryManager::RegisterHeap( CMemoryHeap& h )
{
	m_HeapTable[m_HeapCount] = &h;
	m_HeapCount++;
	DebugAssert( m_HeapCount < MEMORYMANAGER_MAXHEAP );
}

Void CMemoryManager::UnRegisterHeap( CMemoryHeap& h )
{
	UInt32 i, j;
	for(i=0;i<m_HeapCount;i++)
	{
		if( m_HeapTable[i] == &h )
		{	
			m_HeapTable[i] = NULL;
			for(j=i;j<m_HeapCount;j++)
			{
				m_HeapTable[j] = m_HeapTable[j+1];
			}
			break;
		}
	}

	m_HeapCount--;
}

/**
Return the total amount of byte reserved by each currently registered heap
*/
UInt32 CMemoryManager::GetReservedBytes() const
{
	UInt32 s = 0;
	UInt32 i;
	for(i=0;i<m_HeapCount;i++)
	{
		s += (UInt32)m_HeapTable[i]->GetReservedBytes();
	}

	return s;
}

/**
Return the total amount of byte allocated by each currently registered heap
*/
UInt32 CMemoryManager::GetAllocatedBytes() const
{
	UInt32 s = 0;
	UInt32 i;
	for(i=0;i<m_HeapCount;i++)
	{
		s += (UInt32)m_HeapTable[i]->GetAllocatedBytes();
	}

	return s;
}

/**
Ask the system to allocate as many page as necessary in order to satisfy the requested size
\param size the total number of byte to allocate
*/
Void* CMemoryManager::AllocPages( SysSize size )
{
	SysSize pageSize = GetPageSize();

	size += sizeof( SPagesHeader );
	SPagesHeader* header = (SPagesHeader*)m_Impl.AllocPages( size );
	if( header == NULL )
		return NULL;

	header->Size = (UInt32) MemoryGetAlignedSize( size, (UInt32) pageSize );
	header->PageCount = header->Size / pageSize;

	m_AllocatedPages += header->PageCount;

	return ((Byte*)header) + sizeof( SPagesHeader );
}

Void CMemoryManager::FreePages( Void* pages )
{
	Byte* ptr = (Byte*) pages;
	ptr -= sizeof( SPagesHeader );

	m_AllocatedPages -= ((SPagesHeader*)ptr)->PageCount;

	Bool ret = m_Impl.FreePages( ptr );
	//DebugAssert( ret == TRUE );
}

/**
Return the size of a memory page in byte
*/
SysSize	CMemoryManager::GetPageSize() const
{
	return m_Impl.GetPageSize();
}

/**
Return the total number of allocated page count
*/
UInt32 CMemoryManager::GetAllocatedPageCount() const
{
	return m_AllocatedPages;
}
