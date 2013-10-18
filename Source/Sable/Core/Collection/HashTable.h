#ifndef _SABLE_CORE_COLLECTION_HASHTABLE_
#define _SABLE_CORE_COLLECTION_HASHTABLE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Memory/Heap.h>
#include <SAble/Core/Collection/Array.h>

namespace Sable
{

template< class DataType >
HashValue ComputeHashValue( const DataType& data );

template< class DataType >
HashValue ComputeHashValue( const CStringIdentifier& data );

template< class DataType >
HashValue ComputeHashValue( const UInt32& data );

template< class DataType >
HashValue ComputeHashValue( const Int32& data );

template< class DataType >
HashValue ComputeHashValue( const UInt64& data );

template< class DataType >
HashValue ComputeHashValue( const UInt64& data );

template< class DataType >
HashValue ComputeHashValue( const DataType* data );

template< class DataType >
HashValue ComputeHashValue( DataType* data );

/**
\ingroup CoreCollection
Hash table 
*/
template< class KeyType, class DataType >
class CHashTable 
{

public:

	/** 
	Iterator. 
	*/
	template < class KeyType2, class DataType2>
	class CIterator
	{

	public:

		/** @name Constructor/Destructor*/
		//@{
		CIterator( )
		{
			m_Index = 0;
			m_HashTable = NULL;
			m_ProbedItemCount = 0;
		}
		CIterator( const CHashTable<KeyType2, DataType2>& table )
		{
			m_HashTable = &table;
			m_Index = 0;
			m_ProbedItemCount = 0;

			if( m_Index < m_HashTable->GetCapacity() && m_HashTable->m_Table[m_Index].Used )
			{
				m_ProbedItemCount++;
			}
			else
			{
				Iterate();
			}
		}
		//@}

		/** @name Operator*/
		//@{
		DataType2& operator * () const
		{
			return m_HashTable->m_Table[m_Index].Data;
		}
		DataType2* operator -> () const
		{
			return &m_HashTable->m_Table[m_Index].Data;
		}
		//@}

		/** @name Accessors*/
		//@{
		Bool    GetIsValid() const 
		{
			return ( m_ProbedItemCount <= m_HashTable->GetItemCount() && m_Index < m_HashTable->GetCapacity() );
		}
		KeyType2& GetKey() const
		{
			return m_HashTable->m_Table[m_Index].Key;
		}
		//@}

		/** @name Manipulator*/
		//@{
		Void    Iterate()
		{
			do
			{
				m_Index++;
			}
			while( m_Index < m_HashTable->GetCapacity() && m_HashTable->m_Table[m_Index].Used == FALSE );

			if( m_Index < m_HashTable->GetCapacity() && m_HashTable->m_Table[m_Index].Used )
			{
				m_ProbedItemCount++;
			}
		}
		//@}

	private:

		UInt32									m_ProbedItemCount;
		Index									m_Index;
		const CHashTable<KeyType2, DataType2>*	m_HashTable;
	};

	/** @name Types*/
	//@{
	typedef CIterator<KeyType, DataType> Iterator;
	//@}

	/** @name Constructor/Destructor*/
    //@{
	CHashTable();
	CHashTable( UInt32 s );
	~CHashTable();
    //@}

	/** @name Operator*/
    //@{
    //@}

	/** @name Accessors*/
    //@{
	UInt32				GetCapacity() const ;
	Void				SetCapacity( const UInt32 count );
    UInt32				GetItemCount() const;
	Bool				IsEmpty() const;

	DataType&			AddItem( const KeyType& key );
	Void				AddItem( const KeyType& key, const DataType& data );
	Void				RemoveItem( const KeyType& key );
	Bool				HasItem( const KeyType& key ) const;
	DataType&			GetItem( const KeyType& key );
    const DataType&	    GetItem( const KeyType& key ) const;
	DataType*			GetItemPtr( const KeyType& key );
	const DataType*	    GetItemPtr( const KeyType& key ) const;
    //@}

    /** @name Manipulator*/
    //@{
	Void        ClearAllItems();
	Void        StartIteration( Iterator& iterator ) const ;
    //@}

private:

	// DataTypes
	struct SEntry
	{
		Bool		Used;
		KeyType		Key;
		DataType	Data;
	};

	// Methods
	Void				AddItemByHashValue( HashValue hash, const KeyType& key, const DataType& data );
	DataType&			AddItemByHashValue( HashValue hash, const KeyType& key );
	Void				RemoveItemByHashValue( HashValue hash, const KeyType& key );
	Bool				HasItemByHashValue( HashValue hash, const KeyType& key ) const;
	DataType*			GetItemPtrByHashValue( HashValue hash, const KeyType& key );
	const DataType*	    GetItemPtrByHashValue( HashValue hash, const KeyType& key ) const;

	Int32				ProbeItem( HashValue hash, const KeyType& key ) const;
	Int32				ProbeFreeSlot( HashValue hash ) const;

    //Attributes
	CArray<SEntry>	m_Table;
	UInt32			m_ItemCount;

};

#include <Sable/Core/Collection/HashTable.hpp>

}

#endif
