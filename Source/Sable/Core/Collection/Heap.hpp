
/**
Create an empty heap.

use SetCapacity() to set the heap capacity
*/
template< class DataType >
CHeap<DataType>::CHeap()
{
	m_Capacity = 0;
	m_Array = NULL;
	m_ItemCount = 0;
    m_MemoryHeap = &MemoryManager.GetBuddyHeap();
}

/**
Create a heap and set it's capacity
*/
template< class DataType >
CHeap<DataType>::CHeap( UInt32 size )
{
	m_Capacity = 0;
	m_Array = NULL;
	m_ItemCount = 0;
    m_MemoryHeap = &MemoryManager.GetBuddyHeap();
    SetCapacity( size );
}

template< class DataType >
CHeap<DataType>::~CHeap()
{
	Free( );
}

/**
Check if no item is currently in the heap
*/
template< class DataType >
Bool CHeap<DataType>::IsEmpty() const
{
	return m_ItemCount == 0;
}

/**
Push an item on the top of the heap.
*/
template< class DataType >
Void CHeap<DataType>::PushItem( const DataType& item )
{
	DebugAssert( m_ItemCount < (Int32)m_Capacity );

	m_Array[m_ItemCount] = item;
	Int32 iCur = m_ItemCount ++;
	Int32 iParent = (iCur - 1) / 2;
	while( iParent >= 0 && m_Array[iParent] < m_Array[iCur] ) 
	{
		DataType t = m_Array[iCur];
		m_Array[iCur] = m_Array[iParent];
		m_Array[iParent] = t;
		iCur = iParent;
		iParent = (iCur - 1) / 2;
	}
}

/**
Return the number of item currently in the stack
\note This value cannot exceed GetCapacity()
*/
template< class DataType >
UInt32 CHeap<DataType>::GetItemCount() const
{
    return m_ItemCount;
}

template< class DataType >
Void CHeap<DataType>::PopItem()
{
	if( IsEmpty() )
		return;

	DestructObject( &m_Array[0], DataType );
	m_Array[0] = m_Array[--m_ItemCount]; // move the last elem to the first place

	InternalReformat( 0 );
}

/**
Return the item at the top of the stack
*/
template< class DataType >
const DataType& CHeap<DataType>::GetTopItem() const
{
	DebugAssert( m_Array != NULL );
	DebugAssert( m_ItemCount );

	return m_Array[ 0 ];
}

/**
Return the item at the top of the stack
*/
template< class DataType >
DataType& CHeap<DataType>::GetTopItem()
{
	DebugAssert( m_Array != NULL );
	DebugAssert( m_ItemCount );

	return m_Array[ 0 ];
}

template< class DataType >
Void CHeap<DataType>::Reformat( const DataType& item ) 
{
	Int32 i=0;
	for( i=0;i<m_ItemCount;i++ )
	{
		if( m_Array[i] == item )
			break;
	}

	if( i<m_ItemCount )
	{
		InternalReformat( i );
	}
}

template< class DataType >
Void CHeap<DataType>::InternalReformat( Int32 iRoot ) 
{
	Int32 iChild = 2 * iRoot + 1; // left child index
	if (iChild < m_ItemCount)
	{
		Int32 iRightChild = iChild + 1; // right child index
		if (iRightChild < m_ItemCount)
		{
			if ( m_Array[iChild] < m_Array[iRightChild] )
				iChild = iRightChild;
		}
		if ( m_Array[iRoot] < m_Array[iChild] ) 
		{
			DataType t = m_Array[iRoot];
			m_Array[iRoot] = m_Array[iChild];
			m_Array[iChild] = t;
			InternalReformat(iChild);
		}
	}
}

/**
Return a pointer to the base of the stack
*/
template< class DataType >
DataType* CHeap<DataType>::GetBuffer() const 
{
	return m_Array;
}

/**
Return the total capacity of the stack
*/
template< class DataType >
UInt32 CHeap<DataType>::GetCapacity() const 
{
	return m_Capacity;
}

template< class DataType >
Void CHeap<DataType>::Free()
{	
	ClearAllItems();

	if( m_Capacity )
	{
		if( m_MemoryHeap )
			MemoryFree( *m_MemoryHeap, (Byte*)m_Array );
		else
			MemoryManager.FreePages( m_Array );

		m_Array = NULL;
		m_Capacity = 0;
	}
}

/**
Clear the stack
*/
template< class DataType >
Void CHeap<DataType>::ClearAllItems()
{
	if( m_Capacity )
	{
		for(Int32 i=0;i<m_ItemCount;i++)
		{
			DestructObject( &m_Array[i], DataType );
		}
		m_ItemCount = 0;
	}
}

/**
Set the maximum capacity of the stack
*/
template< class DataType >
Void CHeap<DataType>::SetCapacity( const UInt32 count )
{
	if( count == m_Capacity )
		return;

	ClearAllItems();
	Free();
	
	if( count )
	{
		m_Array = (DataType*) MemoryAllocate( *m_MemoryHeap, sizeof(DataType) * count);
	}
	else
	{
		m_Array = NULL;
	}

	m_Capacity = count;
}

