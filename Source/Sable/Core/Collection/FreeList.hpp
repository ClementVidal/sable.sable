
/**
Create an empty freelist.

use SetCapacity() to set the freelist capacity
*/
template< class DataType >
CFreeList<DataType>::CFreeList()
{
	m_NextFree =-1;
	m_Capacity = 0;
	m_ItemCount = 0;
	m_Array = NULL;
    m_MemoryHeap = &MemoryManager.GetBuddyHeap();
}

/**
Create a freelist and set it's capacity
*/
template< class DataType >
CFreeList<DataType>::CFreeList( UInt32 size )
{
	m_NextFree = 0;
	m_Capacity = 0;
	m_ItemCount = 0;
	m_Array = NULL;
    m_MemoryHeap = &MemoryManager.GetBuddyHeap();
    SetCapacity( size );
}

template< class DataType >
CFreeList<DataType>::~CFreeList()
{
	Free( );
}

/**
Check if no item is currently in the freelist
*/
template< class DataType >
Bool CFreeList<DataType>::IsEmpty() const
{
	return m_ItemCount == 0;
}

/**
Check if no item is currently in the freelist
*/
template< class DataType >
Bool CFreeList<DataType>::IsFull() const
{
	return m_ItemCount == m_Capacity;
}

/**
Return the number of item currently in the freelist
\note This value cannot exceed GetCapacity()
*/
template< class DataType >
UInt32 CFreeList<DataType>::GetItemCount() const
{
    return m_ItemCount;
}

/**
Return the total capacity of the freelist
*/
template< class DataType >
UInt32 CFreeList<DataType>::GetCapacity() const 
{
	return m_Capacity;
}

/**
Clear the freelist
*/
template< class DataType >
Void CFreeList<DataType>::ClearAllItems()
{
	if( m_Capacity )
	{
		for(UInt32 i=0;i<m_Capacity;i++)
		{
			if( m_Array[i].Free == FALSE )
			{
				DestructObject( &m_Array[i].Data, DataType );
				m_Array[i].Free = TRUE;
			}
		}

		m_NextFree = 0;
		m_ItemCount = 0;
	}
}

template< class DataType >
Void CFreeList<DataType>::Free()
{
	ClearAllItems();

	MemoryFree( *m_MemoryHeap, m_Array );
	m_Capacity= 0;
	m_Array = NULL;
}

/**
Set the maximum capacity of the freelist
*/
template< class DataType >
Void CFreeList<DataType>::SetCapacity( const UInt32 count )
{
	Free();
	if( count )
	{
		m_Array = (SEntry*) MemoryAllocate( *m_MemoryHeap, sizeof(SEntry) * count);
		for(UInt32 i=0;i<count;i++)
		{
			m_Array[i].Free = TRUE;
		}
	}
	else 
	{
		m_Array = NULL;
	}

	m_Capacity = count;
	m_NextFree = 0;
}

template< class DataType >
Void CFreeList<DataType>::StartIteration( Iterator& iterator ) const
{
    iterator = Iterator( this );
}

template< class DataType >
Void CFreeList<DataType>::AddItem( const DataType& type, Int32* id )
{
	DebugAssert( m_NextFree != -1 );

	Int32 tmpId = m_NextFree;

	m_Array[ m_NextFree ].Data = type;
	m_Array[ m_NextFree ].Free = FALSE;
	m_ItemCount++;
	m_NextFree = FindNextFree( m_NextFree+1 );

	if( id )
		*id = tmpId;
}

template< class DataType >
DataType& CFreeList<DataType>::AddItem( Int32* id )
{
	DebugAssert( m_NextFree != -1 );

	Int32 tmpId = m_NextFree;
	ConstructObject( &m_Array[ m_NextFree ].Data, DataType );

	m_Array[ m_NextFree ].Free = FALSE;
	m_ItemCount++;
	m_NextFree = FindNextFree( m_NextFree+1 );

	if( id )
		*id = tmpId;

	ConstructObject( &m_Array[tmpId].Data, DataType );

	return m_Array[ tmpId ].Data;
}

template< class DataType >
Int32 CFreeList<DataType>::FindNextFree( Int32 from )
{
	Int32 j = from % m_Capacity;
	do
	{
		if( m_Array[j].Free )
			return j;

		j = (j+1) % m_Capacity;
	}
	while( j!=(from-1) );

	return -1;
}

template< class DataType >
Void CFreeList<DataType>::RemoveItemById( Int32 id )
{
	if( m_Array[id].Free == FALSE )
	{
		DestructObject( &m_Array[id].Data, DataType );
		m_Array[id].Free = TRUE;
		m_ItemCount--;
		m_NextFree = id;
	}
}

template< class DataType >
DataType* CFreeList<DataType>::GetItemById( Int32 id ) const
{
	if( m_Array[id].Free == FALSE )
	{
		return &m_Array[id].Data;
	}

	return NULL;
}

template< class DataType >
Void CFreeList<DataType>::RemoveItem( const DataType& type )
{
	UInt32 j;

	for(j=0;j<m_Capacity;j++)
	{
		if( m_Array[j].Data == type )
		{
			DestructObject( &m_Array[j].Data, DataType );
			m_Array[j].Free = TRUE;
			m_ItemCount--;
			m_NextFree = j;
			break;
		}
	}
}