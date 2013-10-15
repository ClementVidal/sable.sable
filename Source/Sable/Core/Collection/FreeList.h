#ifndef _SABLE_CORE_COLLECTION_FREELIST_
#define _SABLE_CORE_COLLECTION_FREELIST_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Memory\Heap.h>

namespace Sable
{

/**
\ingroup CoreCollection
Free list 
*/
template< class DataType >
class CFreeList 
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
        }
        CIterator( const CFreeList<DataType2>* stack ) :
            m_FreeList( stack )
        {
			m_Index = 0;

			while( m_FreeList->m_Array[m_Index].Free )
			{
				m_Index++;
				if( m_Index >= m_FreeList->m_Capacity )
				{
					return ;
				}
			}
        }
        //@}

        /** @name Operator*/
        //@{
        DataType2& operator * () const
        {
            return m_FreeList->m_Array[m_Index].Data;
        }
        //@}

        /** @name Accessor*/
        //@{
        Bool    GetIsValid() const 
        {
            return m_Index < m_FreeList->m_Capacity;
        }
        //@}

	    /** @name Manipulator*/
        //@{
        Void    Iterate()
        {
			do
			{
				m_Index++;
				if( m_Index >= m_FreeList->m_Capacity )
				{
					return ;
				}
			}
			while( m_FreeList->m_Array[m_Index].Free );
        }
        //@}

    private:

        const CFreeList<DataType2>*    m_FreeList;
		UInt32							m_Index;
    };

    /** @name Types*/
    //@{
    typedef CIterator<DataType> Iterator;
    //@}

	/** @name Constructor/Destructor*/
    //@{
	CFreeList();
	CFreeList( UInt32 s );
	virtual ~CFreeList();
    //@}

	/** @name Operator*/
    //@{
    //@}

	/** @name Accessors*/
    //@{
	DataType*		GetItemById( Int32 id ) const;
	UInt32          GetCapacity() const ;
	Void            SetCapacity( const UInt32 count );
    UInt32          GetItemCount() const;
	Bool		    IsEmpty() const;
	Bool		    IsFull() const;
    //@}

    /** @name Manipulator*/
    //@{
	DataType&	AddItem( Int32* id = NULL );
	Void		AddItem( const DataType& type, Int32* id = NULL );
	Void		RemoveItem( const DataType& type );
	Void		RemoveItemById( Int32 id );
	Void        ClearAllItems();
    Void        StartIteration( Iterator& iterator ) const;
    //@}

private:

	// DataTypes
	struct SEntry
	{
		DataType	Data;
		Int32		SpinCount;
		Bool		Free;
	};

	// Methods
	Int32	FindNextFree( Int32 from );
	Void	Free();

    //Attributes
	Int32			m_NextFree;
	UInt32			m_ItemCount;
	SEntry*			m_Array;
	UInt32			m_Capacity;
    CMemoryHeap*	m_MemoryHeap;
};

#include <Sable\Core\Collection\FreeList.hpp>

}

#endif
