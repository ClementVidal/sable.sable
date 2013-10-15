

template <class DataType>
CList<DataType>::CList()
{
    m_EntryCount= 0;
    m_RootNode = m_LastNode = NULL;
    m_MemoryHeap = &MemoryManager.GetBuddyHeap();
}

template <class DataType>
CList<DataType>::CList( CMemoryHeap& heap )
{
	m_EntryCount= 0;
	m_RootNode = m_LastNode = NULL;
	m_MemoryHeap = &heap;
}

template <class DataType>
CList<DataType>::~CList()
{
    ClearAllItems();
}

template <class DataType>
CList<DataType>& CList<DataType>::operator=( const CList& other )
{
	CList<DataType>::Iterator iterator;

	ClearAllItems();

	ForEachItem( iterator, other )
	{
		AddItemAtEnd( iterator.GetData() );
	}

	return *this;
}

template <class DataType>
UInt32 CList<DataType>::GetItemCount() const
{
    return m_EntryCount;
}

template <class DataType>
Void CList<DataType>::SetItemCount( UInt32 count )
{
	ClearAllItems();
	while( count )
	{
		AddItemAtEnd();
		count--;
	}
}

template <class DataType>
DataType& CList<DataType>::GetItemAtIndex( const UInt32 pos ) const 
{
    DebugAssertMsg( pos < m_EntryCount, "CList<DataType>::GetItemAtIndex\n Invalid index");

    Node* node;
    UInt32 i;

    node = m_RootNode;

    for( i = 0; node!=NULL; i++)
    {
        if( i == pos )
            break;

        node = node->Next;
    }

    DebugAssertMsg( node != NULL, "CList<DataType>::GetItemAtIndex\n Invalid operation");

    return node->Data;
}

template <class DataType>
Void CList<DataType>::ClearAllItems( )
{
    Node* node = m_RootNode;
    Node* next;

    while( node )
    {
        next = node->Next;

		FreeNode( node );

        node = next;
    }

    m_EntryCount = 0;
    m_RootNode = NULL;
}

template <class DataType>
Void CList<DataType>::PushItem( const DataType& data )
{
	Node* node = AllocNode();

	node->Data = data;
	m_EntryCount++;

	if( m_RootNode == NULL )
	{
		m_RootNode = node;
		m_LastNode = node;
	}
	else
	{
		m_LastNode->Next = node;
		node->Previous = m_LastNode;
		m_LastNode = node;
	}
}

template <class DataType>
DataType CList<DataType>::PopItem( )
{
	DataType	tempData;

	Node* node;

	DebugAssertMsg( m_LastNode != NULL, "Cannot pop an empty list" );

	node = m_LastNode->Previous;
	if(node)
	{
		node->Next = NULL;
	}
	else
	{
		m_RootNode = NULL;
	}
	tempData = m_LastNode->Data;

	FreeNode( m_LastNode );

	m_LastNode = node ;

	m_EntryCount--;

	return tempData;
}

template <class DataType>
Bool CList<DataType>::AddItemAtEnd( const DataType& data)
{
    Node* node = AllocNode();

	node->Data = data;
    m_EntryCount++;

    if( m_RootNode == NULL )
    {
        m_RootNode = node;
        m_LastNode = node;
    }
    else
    {
        m_LastNode->Next = node;
        node->Previous = m_LastNode;
        m_LastNode = node;
    }
    return TRUE;
}

template <class DataType>
typename CList<DataType>::Node* CList<DataType>::AllocNode()
{
	Node* node = NULL;

	node = (Node*) MemoryAllocate( *m_MemoryHeap, sizeof( Node ) );
	ConstructObject( node, Node );

	return node;
}

template <class DataType>
Void CList<DataType>::FreeNode( typename CList<DataType>::Node* n )
{
	DestructObject( n, Node );
	MemoryFree( *m_MemoryHeap, n );
}

template <class DataType>
DataType&   CList<DataType>::AddItemAtEnd( )
{
	Node* node = AllocNode();

	m_EntryCount++;

	if( m_RootNode == NULL )
	{
		m_RootNode = node;
		m_LastNode = node;
	}
	else
	{
		m_LastNode->Next = node;
		node->Previous = m_LastNode;
		m_LastNode = node;
	}
	return node->Data;
}


template <class DataType>
Bool CList<DataType>::Delete( const DataType& data )
{
    Node* node,
                        *prev,
                        *next;

    node = m_RootNode;

    while ( node )
    {
        if( node->Data == data )
        {
            m_EntryCount--;

            prev = node->Previous;
            next = node->Next;

            if( node == m_LastNode )
            {
                m_LastNode = prev;
            }

			FreeNode( node );

            if( prev ) 
            {
                prev->Next = next;
            }
            else
            {
                m_RootNode = next;
            }

            if( next )
                next->Previous = prev;
            return TRUE;
        }
        node = node->Next;
    }
 
    return FALSE;
}

template <class DataType>
Bool CList<DataType>::RemoveItemAtEnd( )
{
    Node* node;

    if(m_LastNode == NULL)
        return FALSE;

    node = m_LastNode->Previous;
    if(node)
    {
        node->Next = NULL;
    }
    else
    {
        m_RootNode = NULL;
    }

	FreeNode( m_LastNode );

    m_LastNode = node ;

	m_EntryCount--;

    return TRUE;
}

template <class DataType>
DataType& CList<DataType>::GetFirstItem() const
{
	DebugAssertMsg( m_RootNode != NULL, "DataType& CList<DataType>::GetFirstItem()\nEmpty CList, operration failed" );
    return m_RootNode->Data;
}

template <class DataType>
DataType& CList<DataType>::GetLastItem( ) const
{
	DebugAssertMsg( m_LastNode != NULL, "DataType& CList<DataType>::GetLastItem()\nEmpty CList, operration failed" );
    return m_LastNode->Data;
}

template <class DataType>
Void        CList<DataType>::StartIteration( Iterator& iterator ) const 
{
    iterator = Iterator( m_RootNode );
}

template <class DataType>
Bool CList<DataType>::AddItemAtIndex( const DataType& item, const UInt32 pos ) 
{
    DebugError( "Not Implemented" );
    return TRUE;
}

template <class DataType>
Bool CList<DataType>::RemoveItemAtIndex( const UInt32 pos ) 
{
	Node* node,
		*prev,
		*next;

	UInt32 index;

	node = m_RootNode;
	index = 0;
	while ( node )
	{
		if( index == pos )
		{
			m_EntryCount--;

			prev = node->Previous;
			next = node->Next;

			if( node == m_LastNode )
			{
				m_LastNode = prev;
			}

			FreeNode( node );

			if( prev ) 
			{
				prev->Next = next;
			}
			else
			{
				m_RootNode = next;
			}

			if( next )
				next->Previous = prev;
			return TRUE;
		}
        index++;
		node = node->Next;
	}
	return FALSE;
}

template <class DataType>
Bool CList<DataType>::RemoveItemAtBegin( ) 
{
    DebugError( "Not Implemented" );
    return TRUE;
}

template <class DataType>
Bool CList<DataType>::HasItem( const DataType& d ) const
{
	Node* node;
	node = m_RootNode;

	while ( node )
	{
        if( node->Data == d )
		{
            return TRUE;
		}
		node = node->Next;
	}
	return FALSE;
}


template <class DataType>
Bool CList<DataType>::RemoveItem( const DataType& d )
{
	Node* node,
		*prev,
		*next;

	UInt32 index;

	node = m_RootNode;
	index = 0;
	while ( node )
	{
        if( node->Data == d )
		{
			m_EntryCount--;

			prev = node->Previous;
			next = node->Next;

			if( node == m_LastNode )
			{
				m_LastNode = prev;
			}

			FreeNode( node );

			if( prev ) 
			{
				prev->Next = next;
			}
			else
			{
				m_RootNode = next;
			}

			if( next )
				next->Previous = prev;
			return TRUE;
		}
		node = node->Next;
	}
	return FALSE;
}

template <class DataType>
Bool CList<DataType>::AddItemAtBegin( const DataType& item ) 
{
	Node* node = AllocNode();

	node->Data = item;

	m_EntryCount++;

	if( m_RootNode == NULL )
	{
		m_RootNode = node;
		m_LastNode = node;
	}
	else
	{
		node->Next = m_RootNode;
		node->Previous = NULL;
		m_RootNode->Previous = node;
		m_RootNode = node;
	}

	return TRUE;
}

template <class DataType>
Void CList<DataType>::SwapItems( const UInt32 a, const UInt32 b )
{
    DebugError( "Not Implemented" );
}
