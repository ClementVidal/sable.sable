
template <class DataType>
CArray<DataType>::CArray( CMemoryHeap* heap )
{
    m_ItemCount = 0;
    m_Capacity = 0;
    m_Array = NULL;
	m_MemoryHeap = heap;
}

template <class DataType>
CArray<DataType>::CArray( )
{
	m_ItemCount= 0;
    m_Capacity = 0;
	m_Array = NULL;
	m_MemoryHeap = &MemoryManager.GetBuddyHeap();
}

template <class DataType>
CArray<DataType>::CArray( UInt32 size )
{
	m_MemoryHeap = &MemoryManager.GetBuddyHeap();
    m_ItemCount = 0;
    m_Capacity = 0;
    m_Array = NULL;
	SetItemCount( size );
}

template <class DataType>
CArray<DataType>::CArray( UInt32 size, CMemoryHeap* heap )
{
    m_MemoryHeap = heap;
    m_ItemCount = 0;
    m_Capacity = 0;
    m_Array = NULL;
    SetItemCount( size );
}

template <class DataType>
CArray<DataType>::CArray( const CList<DataType>& list )
{
    m_Array = NULL;
    m_ItemCount = 0;
    m_MemoryHeap = &MemoryManager.GetBuddyHeap();
    m_Capacity = 0;

    *this = list;
}

template <class DataType>
CArray<DataType>::CArray( const CArray<DataType>& other )
{
	m_Array = NULL;
	m_ItemCount = 0;
	m_MemoryHeap = &MemoryManager.GetBuddyHeap();
	m_Capacity = 0;

	*this = other;
}

template <class DataType>
CArray<DataType>::~CArray()
{
	Free();
}

template <class DataType>
DataType* CArray<DataType>::Allocate( SysSize s  )
{
	if( s == 0 )
		return NULL;

	DataType* tmp = NULL;

	if( m_MemoryHeap )
		tmp = ( DataType* ) MemoryAllocate( *m_MemoryHeap, s );
	else
		tmp = ( DataType* ) MemoryManager.AllocPages( s );

	return tmp;
}

template <class DataType>
Void CArray<DataType>::SetFrom( const DataType* data, UInt32 count )
{
	SetItemCount( count );
	MemoryCopy( data, GetBuffer(), count * sizeof( DataType ) );
}

template <class DataType>
Void CArray<DataType>::Fill( UInt8 value )
{
    if( m_Array )
        MemoryFill( m_Array, value, GetByteCount() );
}

template <class DataType>
Bool CArray<DataType>::operator!=( const CArray<DataType>& a ) const
{
	return this->operator ==( a ) == FALSE;
}

template <class DataType>
Bool CArray<DataType>::operator==( const CArray<DataType>& a ) const
{
	UInt32 i;
	if( m_ItemCount != a.GetItemCount() )
		return FALSE;

	DataType* other =  a.GetBuffer();

	for(i=0;i<m_ItemCount;i++)
	{
		if( m_Array[i] != other[i] )
			return FALSE;
	}

	return TRUE;
}

/** Get access to the raw data buffer
*/
template <class DataType>
DataType*   CArray<DataType>::GetBuffer() const
{
    return m_Array;
}

/** Access the raw data buffer.
*/
template <class DataType>
DataType& CArray<DataType>::operator[]( const UInt32 i) const
{
	DebugAssertMsg( i<m_ItemCount, "CArray<DataType>::operator[]\nInvalid index");
	return m_Array[i];
}

/**
Copy operator;
*/
template <class DataType>
CArray<DataType>& CArray<DataType>::operator=( const CArray<DataType>& other )
{
	Index index;

    // Does nothing if trying to copy an array into itself
    if( this == &other )
        return *this;

	SetItemCount(other.GetItemCount() );

	for( index = 0; index < GetItemCount(); index++  )
	{
		m_Array[ index ] = other.m_Array[ index ];
	}

	return *this;
}

template <class DataType>
CArray<DataType>&  CArray<DataType>::operator=( const CList<DataType>& other )
{
	typename CList<DataType>::Iterator iterator;
	Index index;

	SetItemCount(other.GetItemCount() );
	index = 0;
	ForEachItem( iterator, other )
	{
		(*this)[ index ] = iterator.GetData();
		index++;
	}

	return *this;
}

/** Acces the raw data buffer.
*/
template <class DataType>
Void CArray<DataType>::SetItemAtIndex( const DataType& item, const UInt32 pos ) 
{
	DebugAssertMsg( pos<m_ItemCount, "CArray<DataType>::operator[]\nInvalid index");
	m_Array[ pos ] = item;
}

/** Acces the raw data buffer.
*/
template <class DataType>
DataType& CArray<DataType>::GetItemAtIndex( const UInt32 pos ) const
{
    DebugAssertMsg( pos<m_ItemCount, "CArray<DataType>::GetItemAtIndex\nInvalid index");
    return m_Array[pos];
}

/** Get item count
*/
template <class DataType>
UInt32 CArray<DataType>::GetItemCount() const
{
    return m_ItemCount;
}

/** Get byte count of the raw buffer
*/
template <class DataType>
UInt32 CArray<DataType>::GetByteCount() const 
{
    return m_ItemCount*sizeof(DataType);
}

/** 
Remove All items, but DOES NOT delete the reserved buffer
*/
template <class DataType>
Void CArray<DataType>::ClearAllItems( )
{
    if( m_ItemCount )
    {
	    for(UInt32 i=0;i<m_ItemCount;i++)
		{
		    DestructObject( &m_Array[i], DataType );
		}
    	    
	    m_ItemCount = 0;
    }
}

template <class DataType>
Void CArray<DataType>::Free( )
{
	ClearAllItems( );

    if( m_Array )
    {
        if( m_MemoryHeap )
            MemoryFree( *m_MemoryHeap, (Byte*)m_Array );
        else
            MemoryManager.FreePages( m_Array );

        m_Array = NULL;
		m_Capacity = 0;
    }
}

/** Free previous raw buffer and allocate a new one according to the new size
@param count item count of the new raw buffer
*/
template <class DataType>
Void  CArray<DataType>::SetItemCount( UInt32 count )
{
    ClearAllItems();
	if( count )
	{
		SetCapacity( count );
		DebugAssert( m_Array );
		for(UInt32 i=0;i<count;i++)
		{
            ConstructObject( &m_Array[i], DataType );
		}
	}
	else 
	{
		m_Array = NULL;
	}
	m_ItemCount = count;
}

template <class DataType>
Void  CArray<DataType>::SetCapacity( UInt32 count )
{
	if( count == m_Capacity && m_Array )
		return;

	DataType* tmp = Allocate( sizeof( DataType ) * count );

	Int32 newItemCount = MathMin( m_ItemCount, count );
	for( Int32 i=0;i<newItemCount; i++ )
	{
		ConstructObject( &tmp[i], DataType );
		tmp[i] = m_Array[i];
	}

	ClearAllItems();
	Free();

	m_ItemCount = newItemCount;
	m_Array = tmp;
	m_Capacity = count;
}

/** Copy this array to an other one
@param destination destination buffer
*/
template <class DataType>
Void CArray<DataType>::CopyTo( CArray<DataType>& destination ) const 
{
    destination.ClearAllItems();
    destination.SetItemCount( m_ItemCount );

	if( m_ItemCount )
		MemoryCopy( m_Array, destination.m_Array, m_ItemCount* sizeof( DataType ) );
}

/** Swap two items according to their positions
@param a First position
@param b Second position
*/
template <class DataType>
Inline
Void CArray<DataType>::SwapItems( const UInt32 a, const UInt32 b )
{
	DataType tmp;

	tmp = m_Array[b];
	m_Array[b] = m_Array[a];
	m_Array[a] = tmp;
}

/** Move a given item to a new position
@param oldIndex Index of the item to move
@param newIndex New position for the item
*/
template <class DataType>
Inline
Void CArray<DataType>::MoveItem( UInt32 oldIndex, UInt32 newIndex )
{
	if( oldIndex == newIndex || GetItemCount() < 2 )
		return;

	DataType tmp;

	tmp = m_Array[oldIndex];

	if( oldIndex < newIndex )
	{
		for( UInt32 i=oldIndex; i<newIndex; i++ )
		{
			SwapItems( i, i + 1 );
		}
		m_Array[newIndex] = tmp;
	}
	else
	{
		for( UInt32 i=oldIndex; i>newIndex; i-- )
		{
			SwapItems( i, i - 1 );
		}
		m_Array[newIndex] = tmp;
	}
}

/**
Add a new item at the specified position.
*/
template <class DataType>
Bool CArray<DataType>::AddItemAtIndex( const DataType& item, const UInt32 pos ) 
{
    UInt32 i;

    // Re reserve memory if necessary
    if( m_ItemCount + 1 > m_Capacity )
    {
        UInt32 inc = m_Capacity / 2;
        if( m_Capacity < 2 )
            inc = 2;

        SetCapacity( m_Capacity + inc );
    }

    m_ItemCount++;

    for(i=m_ItemCount-1;i>(pos);i--)
    {
        m_Array[i] = m_Array[i-1];
    }

    ConstructObject( &m_Array[pos], DataType );
    m_Array[pos] = item;


    return TRUE;
}

/**
*/
template <class DataType>
Bool CArray<DataType>::AddItemAtEnd( const DataType& item )
{
    if( m_ItemCount > 0 )
	    AddItemAtIndex( item, m_ItemCount );
    else 
	    AddItemAtIndex( item, 0);
    return TRUE;
}

/**
*/
template <class DataType>
Bool CArray<DataType>::AddItemAtBegin( const DataType& item )
{
	AddItemAtIndex( item, 0 );

    return TRUE;
}

/**
*/
template <class DataType>
Bool CArray<DataType>::RemoveItemAtIndex( UInt32 pos )
{
	DebugAssert( pos < m_ItemCount );

	DestructObject( &m_Array[pos], DataType );

	if( pos < GetItemCount()-1 )
	{
		ConstructObject( &m_Array[pos], DataType );

		for(Index i=pos;i<GetItemCount()-1; i++)
		{
			m_Array[i] = m_Array[i+1];
		}
	}
    
    m_ItemCount--;
    return TRUE;
}

/**
*/
template <class DataType>
Bool CArray<DataType>::RemoveItemAtEnd( )
{
    DebugAssert( m_ItemCount > 0 );
    RemoveItemAtIndex( m_ItemCount - 1 );
    return TRUE;
}

/** TODO
*/
template <class DataType>
Bool CArray<DataType>::RemoveItemAtBegin( )
{
    RemoveItemAtIndex( 0 );
    return TRUE;
}

/** TODO
*/
template <class DataType>
Void CArray<DataType>::StartIteration( Iterator& iterator ) const 
{
    iterator = Iterator( *this );
}
