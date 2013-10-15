#include <Sable\Core\Memory\BuddyHeap.h>

using namespace Sable;

CMemoryBuddyHeap::CMemoryBuddyHeap( String name ) :
    CMemoryHeap( name )
{
	m_BaseAddress = NULL;
	m_Align = 0;
	m_ParentHeap = NULL;
}

CMemoryBuddyHeap::~CMemoryBuddyHeap()
{
	DumpAlloc();
    FreeReservedMemory();
}

CMemoryHeap::EType CMemoryBuddyHeap::GetType() const
{
	return nType_BuddyHeap;
}

Void CMemoryBuddyHeap::FreeReservedMemory()
{	
	//DebugAssert( GetAllocatedBytes() == 0 );
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
\param reservedSize The total amount of memory to reserve (in bytes)
\param min
*/
Void CMemoryBuddyHeap::Initialize( CMemoryHeap* parent, UInt32 reservedSize, SysSize min, SysSize max, UInt8 align )
{
	FreeReservedMemory();

	m_ParentHeap = parent;

    // Compute an aligned slot size
    m_ReservedSize = MemoryGetAlignedSize( reservedSize, align );
    DebugAssert( m_ReservedSize >= reservedSize );
	DebugAssert( MathIsPowerOfTwo( (Int32) m_ReservedSize ) );

	if( m_ParentHeap )
		m_BaseAddress = MemoryAllocate( *m_ParentHeap, m_ReservedSize + align ); // + m_Align to avoid any overflow
	else
		m_BaseAddress = CoreManager.GetMemoryManager().AllocPages( m_ReservedSize + align );

	if( m_BaseAddress == NULL )
	{
		m_BaseAddress = NULL;
		m_Align = 0;
		m_ParentHeap = NULL;
		DebugError( "Failled to allocate memory for Buddy Heap pool" );
		return;
	}

    m_AlignedBaseAdress = (Byte*) MemoryGetAlignedAddress( m_BaseAddress, align );
    m_Align = align;

#ifdef SETUP_CONFIG_DEBUG
	MemoryFill( m_BaseAddress, 0xcd, m_ReservedSize + m_Align );
#endif

	// Up and down limits of nodes list
	SysSize s = m_ReservedSize;
	m_NodeListsDownLimit = 1;
	while( s > min )
	{
		m_NodeListsDownLimit++;
		s = m_ReservedSize / MathPow( 2, m_NodeListsDownLimit );
	}
	m_NodeListsUpLimit = m_NodeListsDownLimit;
	while( s < max )
	{
		m_NodeListsUpLimit--;
		s = m_ReservedSize / MathPow( 2, m_NodeListsUpLimit );
	}

	SetupNodesTable();
}

/**
Setup the NodeList in the following way:
NodeList[0] = m_ReservedSize
NodeList[1] = m_ReservedSize/2
NodeList[2] = m_ReservedSize/4
NodeList[3] = m_ReservedSize/8
NodeList[4] = m_ReservedSize/16
NodeList[5] = m_ReservedSize/32
NodeList[6] = m_ReservedSize/64
...
*/
Void CMemoryBuddyHeap::SetupNodesTable()
{
	DebugAssert( m_NodeListsDownLimit <= BUDDYHEAP_NODESTABLE_MAXSIZE );

	UInt32 i;
	// init Node lists
	for(i=0;i<BUDDYHEAP_NODESTABLE_MAXSIZE;i++)
	{
		m_NodeLists[i].First = NULL;
		m_NodeLists[i].Size = ((Int32)m_ReservedSize) / MathPow( 2, i );
		m_NodeLists[i].AllocationCount = 0;
	}

	// Fill initial list (i.e: the list at the Up Limit determined by the max parameter of Initialize() )
	UInt32 slotSize = m_NodeLists[m_NodeListsUpLimit].Size;
	UInt32 slotCount = (UInt32) ( m_ReservedSize / slotSize );
	for(i=0;i<slotCount;i++ )
	{
		SNode* n = (SNode*) &m_AlignedBaseAdress[i*slotSize];
		n->Header.Size = slotSize;
		AddNode( n, m_NodeListsUpLimit );
	}

}

Void CMemoryBuddyHeap::RecursiveMerge( SNode* node, UInt32 level )
{
	SNode* buddy = NULL;

	// Add the node to the free list
	AddNode( node, level );
	if( level == m_NodeListsUpLimit )
		return;

	// Search it's buddy
	SNode* it = m_NodeLists[level].First;
	while( it )
	{
		if( it == (SNode*)((Byte*)node + node->Header.Size) ||
			it == (SNode*)((Byte*)node - node->Header.Size) )
		{
			buddy = it;
			break;
		}
		it = it->Next;
	}
	if( buddy )
	{
		RemoveNode( node, level );
		RemoveNode( buddy, level );
		
		SNode* mergedNode = MathMin( node, buddy );
		mergedNode->Header.Size = m_NodeLists[level-1].Size;
		RecursiveMerge( mergedNode, level-1 );
	}
}

CMemoryBuddyHeap::SNode*	CMemoryBuddyHeap::RecursiveSplit( SNode* parent, UInt32 size, UInt32 level )
{
	DebugAssert( level >= m_NodeListsUpLimit );
	DebugAssert( level <= m_NodeListsDownLimit );

	SNode* final = NULL;
	SNode* previous = NULL;
	SNodeList* parentList = &m_NodeLists[level];
	SNodeList* childList = &m_NodeLists[level+1];

	// If we can split at this level
	if( level < m_NodeListsDownLimit && size <= ( parentList->Size / 2 ) )
	{
		// Remove parent node
		RemoveNode( parent, level );
		// Add Two buddy at the sub level
		SNode* lChild = (SNode*) ((Byte*)parent + 0 );
		SNode* rChild = (SNode*) ((Byte*)parent + childList->Size );
		lChild->Header.Size = childList->Size;
		rChild->Header.Size = childList->Size;
		AddNode( lChild, level+1 );
		AddNode( rChild, level+1 );

		// Split recursivly the left child then the right child
		final = RecursiveSplit( lChild, size, level+1);
		if( final == NULL )
		{
			final = RecursiveSplit( rChild, size, level+1);
		}
	}
	// Allocate the block, if we can't split
	else
	{
		final = parentList->First;
		RemoveNode( final, level );
	}

	return final;
}

/**
Add a new node to the node list of the given level
*/
Bool CMemoryBuddyHeap::AddNode( SNode* n, UInt32 level )
{
	DebugAssert( level >= m_NodeListsUpLimit && level <= m_NodeListsDownLimit );
	DebugAssert( n->Header.Size == m_NodeLists[level].Size );

	SNode* prev = m_NodeLists[level].First;
	m_NodeLists[level].First = n;
	n->Next = prev;
	n->Prev = NULL;
	
	if( prev )
		prev->Prev = n;

	return TRUE;
}

Bool CMemoryBuddyHeap::RemoveNode( SNode* node, UInt32 level )
{
	DebugAssert( node );
	DebugAssert( level >= m_NodeListsUpLimit && level <= m_NodeListsDownLimit );
	DebugAssert( node->Header.Size == m_NodeLists[level].Size );

	SNode* p = node->Prev;
	SNode* n = node->Next;
	SNode* next = NULL;

	if( p && n )
	{
		p->Next = n;
		n->Prev = p;
		next = p;
	}
	else if( p && !n )
	{
		p->Next = NULL;
		next = p;
	}
	else if( !p && n )
	{
		n->Prev = NULL;
		next = n;
	}

	m_NodeLists[level].First = next;

	return TRUE;
}

Void* CMemoryBuddyHeap::Allocate( SysSize size )
{
	UInt32 i;
	UInt32 headerSize = (UInt32) MemoryGetAlignedSize( sizeof( SHeader ), m_Align );
	size = size + headerSize;

	Byte* n = NULL;
	// First search for the list with corresponding size
	for(i=m_NodeListsDownLimit;i>=m_NodeListsUpLimit;i--)
	{
		if( size <= m_NodeLists[i].Size )
			break;
	}
	if( i < m_NodeListsUpLimit )
	{
		DebugLogError( "CMemoryBuddyHeap::Allocate - Trying to allocate a block of %d bytes, while max allowed block size is %d bytes", size, m_NodeLists[m_NodeListsUpLimit].Size );
		return NULL;
	}

	// If the no list correspond or if the corresponding list is find but does not have a free slot
	// Find the closest available free slot
	for(;i>=m_NodeListsUpLimit;i--)
	{
		if( m_NodeLists[i].First )
			break;
	}

	// If we find a free slot which belong to a valid list (i.e: a list in the alowed range )
	if( i >= m_NodeListsUpLimit && i <= m_NodeListsDownLimit )
	{
		n = (Byte*)RecursiveSplit( m_NodeLists[i].First, (UInt32)size, i );
	}

	if( n )
	{
		SNode* node = ((SNode*)n);
		DebugAssert( size >= node->Header.Size / 2 );
		OnAllocate( node );
		return n + headerSize;
	}
	else
	{
		DebugLogError( "CMemoryBuddyHeap::Allocate - Not enough memory available" );
	}

    return NULL;
}

Void CMemoryBuddyHeap::Free( Void* object )
{
	if( object == NULL )
		return;

	UInt32 headerSize = (UInt32) MemoryGetAlignedSize( sizeof( SHeader ), m_Align );
	SNode* n = (SNode*) ((Byte*)object - headerSize);
	OnFree( (SNode*) n );

	UInt32 i;
	// Search for the list where the node should reside
	for(i=m_NodeListsUpLimit;i<=m_NodeListsDownLimit;i++)
	{
		if( m_NodeLists[i].Size == n->Header.Size )
			break;
	}
	// if a valid list is found (which should alway be the case)
	// recursive merge the freed node
	if( i >= m_NodeListsUpLimit && i <= m_NodeListsDownLimit )
	{
		RecursiveMerge( n, i );
	}
}

Void CMemoryBuddyHeap::OnAllocate( SNode* n )
{
	UInt32 i;
	for(i=m_NodeListsUpLimit;i<=m_NodeListsDownLimit;i++)
	{
		if( m_NodeLists[i].Size == n->Header.Size )
		{
			m_NodeLists[i].AllocationCount++;
			break;
		}
	}

	CMemoryHeap::OnAllocate( n->Header.Size );
}

Void CMemoryBuddyHeap::OnFree( SNode* n )
{
	UInt32 i;
	for(i=m_NodeListsUpLimit;i<=m_NodeListsDownLimit;i++)
	{
		if( m_NodeLists[i].Size == n->Header.Size )
		{
			m_NodeLists[i].AllocationCount--;
			break;
		}
	}

	CMemoryHeap::OnFree( n->Header.Size );
	DebugAssert( m_NodeLists[i].AllocationCount>= 0 );
}

