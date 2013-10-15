#include <Sable\Core\Collection\Map.h>


template <class KeyType, class DataType>
CMap<KeyType,DataType>::CMap()
{
    m_ListRootNode = NULL;
    m_TreeRootNode = NULL;
    m_EntryCount = 0;
    m_MemoryHeap = &MemoryManager.GetBuddyHeap();
}

template <class KeyType, class DataType>
CMap<KeyType,DataType>::~CMap()
{
	ClearAllItems();	
}

template <class KeyType, class DataType>
Inline
Bool CMap<KeyType,DataType>::AddItem( const KeyType& key, const DataType& data)
{
    m_TreeRootNode = m_TreeRootNode->New(key, data, m_ListRootNode, *m_MemoryHeap);
    m_EntryCount++;
    return TRUE;
}

template <class KeyType, class DataType>
Inline
DataType& CMap<KeyType,DataType>::AddItem( const KeyType& key )
{
	DataType
		data;

	m_TreeRootNode = m_TreeRootNode->New(key, data, m_ListRootNode, *m_MemoryHeap);
	m_EntryCount++;

	return GetItem( key );
}

template <class KeyType, class DataType>
Inline
Bool CMap<KeyType,DataType>::RemoveItemAtKey( const KeyType& key )
{
    m_TreeRootNode = m_TreeRootNode->Delete( key, m_ListRootNode, *m_MemoryHeap );
    m_EntryCount--;
    return TRUE;
}

template <class KeyType, class DataType>
Inline
DataType&	CMap<KeyType,DataType>::GetItem( const KeyType& key )
{
	MapNode* n = m_TreeRootNode->Get( key );
	DebugAssert( n );
	return  ( n->Data );
}

template <class KeyType, class DataType>
Inline
DataType*	CMap<KeyType,DataType>::GetItemPtr( const KeyType& key )
{
	CMapNode<KeyType, DataType>* node = m_TreeRootNode->Get( key );
	if( node )
		return &node->Data;

	return NULL;
}

template <class KeyType, class DataType>
Inline
const DataType&	CMap<KeyType,DataType>::GetItem( const KeyType& key ) const
{
	MapNode* n = m_TreeRootNode->Get( key );
	DebugAssert( n );
    return  ( n->Data );
}

template <class KeyType, class DataType>
Inline
const DataType*	CMap<KeyType,DataType>::GetItemPtr( const KeyType& key ) const
{
	CMapNode<KeyType, DataType>* node = m_TreeRootNode->Get( key );
	if( node )
		return &node->Data;

	return NULL;
}

template <class KeyType, class DataType>
Inline
CMap<KeyType, DataType>&   CMap<KeyType,DataType>::operator =( const CMap<KeyType, DataType>& other )
{
	CMap<KeyType, DataType>::Iterator
		iterator;

	ClearAllItems();
	ForEachItem( iterator, (other) )
	{
		AddItem( iterator.GetKey(), iterator.GetData() );
	}	

	return *this;
}

template <class KeyType, class DataType>
Inline
Void CMap<KeyType,DataType>::SetItem( const KeyType& key, const DataType& data ) 
{
	CMapNode<KeyType,DataType>* found;

	found = m_TreeRootNode->Get( key );

	found->Data = data;
}

template <class KeyType, class DataType>
Inline
Bool	CMap<KeyType,DataType>::HasItem( const KeyType& key ) const
{
	return  ( m_TreeRootNode->Get( key ) != NULL );
}


template <class KeyType, class DataType>
Inline
Void		CMap<KeyType,DataType>::ClearAllItems( )
{
    m_TreeRootNode->Clear( *m_MemoryHeap );
    m_TreeRootNode = NULL;
    m_ListRootNode = NULL;
    m_EntryCount = 0;
}


template <class KeyType, class DataType>
Inline
UInt32 CMap<KeyType,DataType>::GetItemCount() const
{
    return m_EntryCount;
}

template <class KeyType, class DataType>
Inline
Void   CMap<KeyType,DataType>::StartIteration( Iterator& iterator ) const
{
    iterator = Iterator( m_ListRootNode );
}
