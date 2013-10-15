
template< class DataType >
HashValue ComputeHashValue( const DataType& data )
{
	DebugError("Please implement the right hash function")
	return 0;
}  

template< class DataType >
HashValue ComputeHashValue( const CStringIdentifier& data )
{
	return StringGetHashCode( data.GetBuffer() );
}

template< class DataType >
HashValue ComputeHashValue( const DataType* data )
{
	return ComputeHashValue( (UInt32) data );
}

template< class DataType >
HashValue ComputeHashValue( const Int32& data )
{
	UInt32 tmp;
	MemoryCopy( &data, &tmp, sizeof( Int32 ) );
	tmp += ~(tmp << 15);
	tmp ^= (tmp >> 10);
	tmp += (tmp << 3);
	tmp ^= (tmp >> 6);
	tmp += ~(tmp << 11);
	tmp ^= (tmp >> 16);
	return tmp;
}

template< class DataType >
HashValue ComputeHashValue( DataType* data )
{
	return ComputeHashValue( (UInt32) data );
}

// Thomas Wang's 64 Bit Mix Function: http://www.cris.com/~Ttwang/tech/inthash.htm
template< class DataType >
HashValue ComputeHashValue( const UInt64& data )
{
	UInt32 tmp = data;
	tmp += ~(tmp << 32);
	tmp ^= (tmp >> 22);
	tmp += ~(tmp << 13);
	tmp ^= (tmp >> 8);
	tmp += (tmp << 3);
	tmp ^= (tmp >> 15);
	tmp += ~(tmp << 27);
	tmp ^= (tmp >> 31);
	return static_cast<HashValue>(tmp);
}

// Thomas Wang's 32 Bit Mix Function: http://www.cris.com/~Ttwang/tech/inthash.htm
template< class DataType >
HashValue ComputeHashValue( const UInt32& data )
{
	UInt32 tmp = data;
	tmp += ~(tmp << 15);
	tmp ^= (tmp >> 10);
	tmp += (tmp << 3);
	tmp ^= (tmp >> 6);
	tmp += ~(tmp << 11);
	tmp ^= (tmp >> 16);
	return tmp;
}

/**
Create an empty hash table.
*/
template< class KeyType, class DataType >
CHashTable<KeyType, DataType>::CHashTable()
{
	m_ItemCount = 0;
}

/**
Create a hash table and set it's capacity
*/
template< class KeyType, class DataType >
CHashTable<KeyType, DataType>::CHashTable( UInt32 size )
{
	SetCapacity( size );
}

template< class KeyType, class DataType >
CHashTable<KeyType, DataType>::~CHashTable()
{
	ClearAllItems( );
}

/**
Check if no item is currently in the table
*/
template< class KeyType, class DataType >
Bool CHashTable<KeyType, DataType>::IsEmpty() const
{
	return m_ItemCount == 0;
}

/**
Return the number of item currently in the hash table
\note This value cannot exceed GetCapacity()
*/
template< class KeyType, class DataType >
UInt32 CHashTable<KeyType, DataType>::GetItemCount() const
{
    return m_ItemCount;
}

template< class KeyType, class DataType >
Bool CHashTable<KeyType, DataType>::HasItemByHashValue( HashValue hash, const KeyType& key ) const
{
	Int32 index = ProbeItem( hash, key );

	return index != -1;
}

template< class KeyType, class DataType >
Bool CHashTable<KeyType, DataType>::HasItem( const KeyType& key ) const
{
	HashValue hash = ComputeHashValue<KeyType>( key );

	return HasItemByHashValue( hash, key );
}

/**
Return an item using a given key, this method will use the ComputeHashValue<KeyType> method to compute the hashed value of the key
*/
template< class KeyType, class DataType >
const DataType& CHashTable<KeyType, DataType>::GetItem( const KeyType& key  ) const
{
	HashValue hash = ComputeHashValue<KeyType>( key );
	const DataType* data = GetItemPtrByHashValue( hash, key );
	DebugAssert( data );
	return *data;
}

/**
Return an item using a given key, this method will use the ComputeHashValue<KeyType> method to compute the hashed value of the key
*/
template< class KeyType, class DataType >
DataType& CHashTable<KeyType, DataType>::GetItem( const KeyType& key )
{
    HashValue hash = ComputeHashValue<KeyType>( key );
	DataType* data = GetItemPtrByHashValue( hash, key );
	DebugAssert( data );
	return *data;
}

/**
Return an item using a given key, this method will use the ComputeHashValue<KeyType> method to compute the hashed value of the key
*/
template< class KeyType, class DataType >
const DataType* CHashTable<KeyType, DataType>::GetItemPtr( const KeyType& key  ) const
{
	HashValue hash = ComputeHashValue<KeyType>( key );
	return GetItemPtrByHashValue( hash, key );
}

/**
Return an item using a given key, this method will use the ComputeHashValue<KeyType> method to compute the hashed value of the key
*/
template< class KeyType, class DataType >
DataType* CHashTable<KeyType, DataType>::GetItemPtr( const KeyType& key )
{
    HashValue hash = ComputeHashValue<KeyType>( key );
    return GetItemPtrByHashValue( hash, key );
}

/**
Return an item using a given stack index
*/
template< class KeyType, class DataType >
const DataType* CHashTable<KeyType, DataType>::GetItemPtrByHashValue( HashValue hash, const KeyType& key ) const
{
	Int32 index = ProbeItem( hash, key );

	if( index != -1 )
		return &m_Table[index].Data;

	return NULL;
}

/**
Return an item using a given stack index
*/
template< class KeyType, class DataType >
DataType* CHashTable<KeyType, DataType>::GetItemPtrByHashValue( HashValue hash, const KeyType& key )
{
	Int32 index = ProbeItem( hash, key );

	if( index != -1 )
		return &m_Table[index].Data;

	return NULL;
}

/**
Clear the stack
*/
template< class KeyType, class DataType >
Void CHashTable<KeyType, DataType>::ClearAllItems()
{
	for( UInt32 i=0;i<m_Table.GetItemCount(); i++ )
	{
		if( m_Table[i].Used )
			DestructObject( &m_Table[i], SEntry );

		m_Table[i].Used = FALSE;
	}
	m_ItemCount = 0;
}

/**
Set the maximum capacity of the hash table
*/
template< class KeyType, class DataType >
Void CHashTable<KeyType, DataType>::SetCapacity( UInt32 count )
{
	m_Table.SetItemCount( count );
	for( UInt32 i=0;i<count; i++ )
	{
		m_Table[i].Used = FALSE;
	}
	m_ItemCount = 0;
}

/**
Get the capacity of the map
*/
template< class KeyType, class DataType >
UInt32 CHashTable<KeyType, DataType>::GetCapacity( ) const
{
	return m_Table.GetItemCount();
}

template< class KeyType, class DataType >
DataType& CHashTable<KeyType, DataType>::AddItem( const KeyType& key )
{
	HashValue hash = ComputeHashValue<KeyType>( key );

	return AddItemByHashValue( hash, key );
}

template< class KeyType, class DataType >
Void CHashTable<KeyType, DataType>::AddItem( const KeyType& key, const DataType& data )
{
	HashValue hash = ComputeHashValue<KeyType>( key );

	return AddItemByHashValue( hash, key, data );
}

template< class KeyType, class DataType >
Void CHashTable<KeyType, DataType>::RemoveItem( const KeyType& key )
{
	HashValue hash = ComputeHashValue<KeyType>( key );

	return RemoveItemByHashValue( hash, key );
}

template< class KeyType, class DataType >
Void CHashTable<KeyType, DataType>::AddItemByHashValue( HashValue hash, const KeyType& key, const DataType& data )
{
	Int32 index = ProbeFreeSlot( hash );

	DebugAssert( index != -1 );

	m_Table[index].Key = key;
	m_Table[index].Data = data;
	m_Table[index].Used = TRUE;

	m_ItemCount++;
}

template< class KeyType, class DataType >
DataType& CHashTable<KeyType, DataType>::AddItemByHashValue( HashValue hash, const KeyType& key )
{
	Int32 index = ProbeFreeSlot( hash );

	DebugAssert( index != -1 );

	m_Table[index].Key = key;
	m_Table[index].Used = TRUE;
	m_ItemCount++;

	ConstructObject( &m_Table[index].Data, DataType );

	return m_Table[index].Data;
}

template< class KeyType, class DataType >
Int32 CHashTable<KeyType, DataType>::ProbeItem( HashValue hash, const KeyType& key ) const
{
	if( m_Table.GetItemCount() == 0 )
		return -1;

	Int32 index = hash % m_Table.GetItemCount();

	UInt32 j = 0;
	while(j < m_Table.GetItemCount() ) 
	{
		if(m_Table[index].Used && m_Table[index].Key == key )
		{
			return index;
		}
		j++;
		index = (hash + j * j) % m_Table.GetItemCount();
	}

	return -1;
}

template< class KeyType, class DataType >
Int32 CHashTable<KeyType, DataType>::ProbeFreeSlot( HashValue hash ) const
{
	if( m_Table.GetItemCount() == 0 )
		return -1;

	Int32 index = hash % m_Table.GetItemCount();

	UInt32 j = 0;
	while(j < m_Table.GetItemCount() ) 
	{
		if(m_Table[index].Used == FALSE )
		{
			return index;
		}
		j++;
		index = (hash + j * j) % m_Table.GetItemCount();
	}

	return -1;
}

template< class KeyType, class DataType >
Void CHashTable<KeyType, DataType>::RemoveItemByHashValue( HashValue hash, const KeyType& key  )
{
	UInt32 index = ProbeItem( hash, key );

	DebugAssert( index != -1 );

	m_Table[index].Used = FALSE;

	DestructObject( &m_Table[index], SEntry );

	m_ItemCount--;
}

template< class KeyType, class DataType >
Void CHashTable<KeyType, DataType>::StartIteration( Iterator& iterator ) const
{
	iterator = Iterator( *this );
}