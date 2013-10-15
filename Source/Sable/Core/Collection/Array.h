#ifndef _SABLE_CORE_COLLECTION_ARRAY_
#define _SABLE_CORE_COLLECTION_ARRAY_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Collection\List.h>
#include <Sable\Core\Memory\Primitives.h>
#include <Sable\Core\Memory\Heap.h>
#include <Sable\Core\Math\Primitives.h>

namespace Sable
{

/** 
\ingroup CoreCollection
Random access array 
*/
template <class DataType>
class CArray 
{

public:

	/** 
	Iterator. 
	*/
	template <class DataType2>
	class CIterator
	{

	public:

		/** @name Constructor/Destructor*/
		//@{
		CIterator( )
		{
			m_Index = 0;
			m_ItemCount = 0;
			m_Array = NULL;
		}
		CIterator( const CArray<DataType2>& array )
		{
			m_Array = array.GetBuffer();
			m_ItemCount = array.GetItemCount();
			m_Index = 0;
		}
		//@}

		/** @name Accessors*/
		//@{
		Bool    GetIsValid() const 
		{
			return ( m_Index < m_ItemCount );
		}
		DataType2& GetData() const
		{
			return m_Array[ m_Index ];
		}
		Void SetData( const DataType2& data )
		{
			m_Array[ m_Index ] = data;
		}
		//@}

		/** @name Manipulator*/
		//@{
		Void    Iterate()
		{
			if( m_Index < m_ItemCount )
				m_Index++;
		}
		//@}

	private:

		Index		m_Index;
		Index		m_ItemCount;
		DataType2*	m_Array;

	};

	/** @name Types*/
	//@{
	typedef CIterator<DataType> Iterator;
	//@}

	/** @name Constructor/Destructor*/
    //@{
	CArray( );
	CArray( CMemoryHeap* heap  );
	CArray( UInt32 size );
    CArray( UInt32 size, CMemoryHeap* heap );
	CArray( const CList<DataType>& list );
	CArray( const CArray<DataType>& other );
	virtual ~CArray();
    //@}

	/** @name Operator*/
    //@{
	DataType& operator[]( const UInt32 i ) const ;
	CArray<DataType>&    operator=( const CArray<DataType>& other );
	CArray<DataType>&    operator=( const CList<DataType>& other );
	Bool operator==( const CArray<DataType>& a ) const;
	Bool operator!=( const CArray<DataType>& a ) const;
    //@}

	/** @name Accessors*/
    //@{
    UInt32      GetByteCount() const;
    DataType*   GetBuffer() const ;
    UInt32      GetItemCount() const ;
	Void        SetItemCount( const UInt32 count );
	DataType&   GetItemAtIndex( const UInt32 pos ) const;
    Void        SetItemAtIndex( const DataType& item, const UInt32 pos ) ;
    //@}

	/** @name Manipulator*/
    //@{
	Void		SetFrom( const DataType* data, UInt32 count );
	Void        Fill( UInt8 value );
    Void        SetCapacity( UInt32 count );
    Void        CopyTo( CArray& destination ) const ;
    Bool        AddItemAtIndex( const DataType& item, const UInt32 pos ) ;
    Bool        AddItemAtEnd( const DataType& item ) ;
    Bool        AddItemAtBegin( const DataType& item ) ;
    Bool        RemoveItemAtIndex( UInt32 pos ) ;
    Bool        RemoveItemAtEnd( ) ;
    Bool        RemoveItemAtBegin( ) ;
    Void        StartIteration( Iterator& iterator ) const ;
    Void        SwapItems( const UInt32 a, const UInt32 b );
	Void		MoveItem( UInt32 oldIndex, UInt32 newIndex );
    Void        ClearAllItems();
    //@}

private:

    //Methods
    DataType*		Allocate( SysSize s );
    Void    		Free( );

    //Attributes
    DataType*           m_Array;
	UInt32		        m_ItemCount;
	UInt32		        m_Capacity;
    CMemoryHeap*        m_MemoryHeap;

};

#include <Sable\Core\Collection\Array.hpp>

typedef CArray<Byte> CArrayByte;
typedef CArray<Int32> CArrayInt32;
typedef CArray<UInt32> CArrayUInt32;
typedef CArray<Int16> CArrayInt16;
typedef CArray<UInt16> CArrayUInt16;

} 

#endif
