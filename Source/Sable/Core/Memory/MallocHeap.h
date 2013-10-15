#ifndef _SABLE_CORE_MEMORY_MALLOVHEAP_
#define _SABLE_CORE_MEMORY_MALLOVHEAP_

#include <Sable\Core\Memory\Heap.h>

namespace Sable
{

/**
\ingroup CoreMemory
Define an allocator that allocate/free memory using std ::malloc function
*/
class CMemoryMallocHeap : public CMemoryHeap
{

public:

	/** @name Constructor*/
	//@{
	CMemoryMallocHeap( String name );
	virtual ~CMemoryMallocHeap();
	//@}

	/** @name Manipulator*/
	//@{
	EType	GetType() const;
 	Void*   Allocate( SysSize size) ;
	Void    Free( Void* object );
	//@}

private:

	// Type

	// Methods

	// Attribute

};


}

#endif
