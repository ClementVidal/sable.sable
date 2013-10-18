#ifndef _SABLE_CORE_MEMORY_STACKHEAP_
#define _SABLE_CORE_MEMORY_STACKHEAP_

#include <Sable/Core/Memory/Heap.h>

#define MEMORYSTACKHEAP_STACKSIZE 128

namespace Sable
{

/**
\ingroup CoreMemory
Define a satck allocator
*/
class CMemoryStackHeap : public CMemoryHeap
{

public:

	/** @name Constructor*/
	//@{
	CMemoryStackHeap( String name );
	virtual ~CMemoryStackHeap();
	//@}

	/** @name manipulator*/
	//@{
	Void*	PushMarkerAndAllocate( SysSize size );
	Void	PopMarkerAndFree( Void* object );

	Void	PushMarker();
	Void	PopMarker();
	EType	GetType() const;
	Void	Initialize( CMemoryHeap* parent, SysSize maxSize, UInt8 align = 4 );
	Void*   Allocate( SysSize size) ;
	Void    Free( Void* object );
	Void	Reset( );
	//@}

private:

	// Methods
	Void	FreeReservedMemory();

	// Type
	struct SHeader
	{
		UInt32 Size;
	};

	struct SAlloc
	{
		Byte* Ptr;
		Int32 Size;
	};

	// Methods

	// Attribute
	Byte*			m_HeapPtr;
	Byte*			m_AlignedBaseAdress;
	SAlloc			m_StackAlloc[MEMORYSTACKHEAP_STACKSIZE];
	Int32			m_StackIndex;

	CMemoryHeap*	m_ParentHeap;
};


}

#endif
