#ifndef _SABLE_CORE_MEMORY_BUDDYHEAP_
#define _SABLE_CORE_MEMORY_BUDDYHEAP_

#include <Sable\Core\Memory\Heap.h>

#define BUDDYHEAP_NODESTABLE_MAXSIZE 32

namespace Sable
{

/**
\ingroup CoreMemory
Define a buddy allocator
*/
class CMemoryBuddyHeap : public CMemoryHeap
{

public:

	/** @name Constructor*/
	//@{
	CMemoryBuddyHeap( String name );
	virtual ~CMemoryBuddyHeap();
	//@}

	/** @name Manipulator*/
	//@{
	EType	GetType() const;
    Void	Initialize( CMemoryHeap* parent, UInt32 reservedSize, SysSize min = 16, SysSize max = 1024*1024*4, UInt8 align = 4 );
	Void*   Allocate( SysSize size) ;
	Void    Free( Void* object );
	//@}

private:

	// Type
	struct SHeader
	{
		UInt32 Size;
	};

	struct SNode
	{
		SHeader Header;
		SNode*	Next;
		SNode*	Prev;
	};

	struct SNodeList
	{
		UInt32	Size;
		Int32	AllocationCount;
		SNode*	First;
	};

	// Methods
	Void	OnAllocate( SNode* n );
	Void	OnFree( SNode* n );
	Void	SetupNodesTable();
	SNode*	RecursiveSplit( SNode* parent, UInt32 s, UInt32 level );
	Void	RecursiveMerge( SNode* node, UInt32 level );
	Bool	RemoveNode( SNode* n, UInt32 level );
	Bool	AddNode( SNode* n, UInt32 level );
	Void	FreeReservedMemory();

	// Attribute
	SNodeList		m_NodeLists[BUDDYHEAP_NODESTABLE_MAXSIZE];
	UInt32			m_NodeListsUpLimit;
	UInt32			m_NodeListsDownLimit;

	Byte*			m_AlignedBaseAdress;
	CMemoryHeap*	m_ParentHeap;
};


}

#endif
