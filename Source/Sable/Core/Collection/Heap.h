#ifndef _SABLE_CORE_COLLECTION_HEAP_
#define _SABLE_CORE_COLLECTION_HEAP_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Memory\Heap.h>

namespace Sable
{

/**
\ingroup CoreCollection
Stack 
*/
template< class DataType >
class CHeap 
{

public:

	/** @name Constructor/Destructor*/
    //@{
	CHeap();
	CHeap( UInt32 s );
	~CHeap();
    //@}

	/** @name Operator*/
    //@{
    //@}

	/** @name Accessors*/
    //@{
	DataType*			GetBuffer() const ;
	UInt32				GetCapacity() const ;
	Void				SetCapacity( const UInt32 count );
    UInt32				GetItemCount() const;
	Bool				IsEmpty() const;
	const DataType&		GetTopItem() const;
    DataType&			GetTopItem() ;
    //@}

    /** @name Manipulator*/
    //@{
	Void        PushItem( const DataType& item );
	Void        PopItem();
	Void        ClearAllItems();
	Void		Reformat( const DataType& item );
    //@}

private:

	// Methods
	Void		InternalReformat( Int32 iRoot );
	Void		Free();

    //Attributes
	Int32		m_ItemCount;
	DataType*   m_Array;
	UInt32		m_Capacity;
    CMemoryHeap* m_MemoryHeap;
};

#include <Sable\Core\Collection\Heap.hpp>

}

#endif
