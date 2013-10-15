
/**
Create an empty stack.

use SetCapacity() to set the stack capacity
*/
template< class DataType >
CStack<DataType>::CStack()
{
	m_StackIndex = -1;
	m_Capacity = 0;
	m_Array = NULL;
    m_MemoryHeap = &MemoryManager.GetBuddyHeap();
}

/**
Create a stack and set it's capacity
*/
template< class DataType >
CStack<DataType>::CStack( UInt32 size )
{
	m_StackIndex = -1;
	m_Capacity = 0;
	m_Array = NULL;
    m_MemoryHeap = &MemoryManager.GetBuddyHeap();
    SetCapacity( size );
}

template< class DataType >
CStack<DataType>::~CStack()
{
	Free( );
}

/**
Check if no item is currently in the stack
*/
template< class DataType >
Bool CStack<DataType>::IsEmpty() const
{
	return m_StackIndex == -1;
}

/**
Push an item on the top of the stack.
\note Pushed item count connot exceed the stack capacity set by SetCapacity
*/
template< class DataType >
Void CStack<DataType>::PushItem( const DataType& item )
{
	m_StackIndex++;
	DebugAssertMsg( (UInt32) m_StackIndex < m_Capacity, "Stack overflow" );

	ConstructObject( &m_Array[ m_StackIndex ], DataType );

	m_Array[ m_StackIndex ] = item;
}

/**
Push an item on the top of the stack.
\note Pushed item count connot exceed the stack capacity set by SetCapacity
*/
template< class DataType >
Void CStack<DataType>::PushItem( )
{
	m_StackIndex++;
	ConstructObject( &m_Array[ m_StackIndex ], DataType );

	DebugAssertMsg( (UInt32) m_StackIndex < m_Capacity, "Stack overflow" );
}

/**
Return the number of item currently in the stack
\note This value cannot exceed GetCapacity()
*/
template< class DataType >
UInt32 CStack<DataType>::GetItemCount() const
{
    return m_StackIndex + 1;
}

/**
Return an item using a given stack index
*/
template< class DataType >
DataType& CStack<DataType>::GetItemAtIndex( UInt32 i)
{
    DebugAssert( i < GetItemCount() );

    return m_Array[i];
}

/**
Return an item using a given stack index
*/
template< class DataType >
const DataType& CStack<DataType>::GetItemAtIndex( UInt32 i ) const
{
    DebugAssert( i < GetItemCount() );

    return m_Array[i];
}

/**
Pop an item from the stack
*/
template< class DataType >
Void CStack<DataType>::PopItem()
{
	DebugAssert( m_StackIndex > -1 );

	DestructObject( &m_Array[m_StackIndex], DataType );

	m_StackIndex--;
}

/**
Return the item at the top of the stack
*/
template< class DataType >
const DataType& CStack<DataType>::GetTopItem() const
{
	DebugAssert( m_Array != NULL );
	DebugAssert( m_StackIndex > -1 );

	return m_Array[ m_StackIndex ];
}

/**
Return the item at the top of the stack
*/
template< class DataType >
DataType& CStack<DataType>::GetTopItem()
{
	DebugAssert( m_Array != NULL );
	DebugAssert( m_StackIndex > -1 );

	return m_Array[ m_StackIndex ];
}

/**
Return a pointer to the base of the stack
*/
template< class DataType >
DataType* CStack<DataType>::GetBuffer() const 
{
	return m_Array;
}

/**
Return the total capacity of the stack
*/
template< class DataType >
UInt32 CStack<DataType>::GetCapacity() const 
{
	return m_Capacity;
}

/**
Clear the stack
*/
template< class DataType >
Void CStack<DataType>::ClearAllItems()
{
	if( m_Capacity )
	{
		for(Int32 i=0;i<=m_StackIndex;i++)
		{
			DestructObject( &m_Array[i], DataType );
		}
		m_StackIndex = -1;
	}
}

/**
Set the maximum capacity of the stack
*/
template< class DataType >
Void CStack<DataType>::SetCapacity( UInt32 count )
{
	if( count == m_Capacity )
		return;

	ClearAllItems();
	Free();

	m_Array = Allocate( sizeof( DataType) * count );

	m_Capacity = count;
}

template< class DataType >
Void CStack<DataType>::StartIteration( Iterator& iterator ) const
{
    iterator = Iterator( this );
}

template <class DataType>
Void CStack<DataType>::Free( )
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

template <class DataType>
DataType* CStack<DataType>::Allocate( SysSize s )
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

