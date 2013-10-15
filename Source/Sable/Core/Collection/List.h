#ifndef _CORE_COLLECTION_LIST_
#define _CORE_COLLECTION_LIST_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Common\Primitives.h>
#include <Sable\Core\Memory\Heap.h>
#include <Sable\Core\Memory\Manager.h>
#include <Sable\Core\Memory\Primitives.h>

namespace Sable
{

/** 
\ingroup CoreCollection
Double linked list. 
*/
template <class DataType>
class CList
{

public:

    /** 
	Node. 
    */
	template <class DataType2>
	class CNode
	{

	public:

		CNode( )
		{
			Next = Previous = NULL;
		}

		DataType2		Data;

		CNode<DataType2>* Next;
		CNode<DataType2>* Previous;

	};

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
            m_Node = NULL;
			m_Next = NULL;
        }
        CIterator( CNode<DataType2>* node )
        {
            m_Node = node;
			m_Next = m_Node?m_Node->Next:NULL;
        }
        //@}

        /** @name Operator*/
        //@{
        DataType2& operator * () const
        {
            return m_Node->Data;
		}
		DataType2* operator -> () const
		{
			return &m_Node->Data;
		}
        //@}

        /** @name Accessor*/
        //@{
        Bool    GetIsValid() const 
        {
            return ( m_Node != NULL );
        }
        DataType2& GetData() const
        {
            return m_Node->Data;
        }
        Void SetData( const DataType2& data )
        {
            m_Node->Data = data;
        }
        //@}

	    /** @name Manipulator*/
        //@{
        Void    Iterate()
        {
            if( m_Node )
			{
                m_Node = m_Next;
				m_Next = m_Node?m_Node->Next:NULL;
			}
        }
        //@}

    private:

        CNode<DataType2>*    m_Node;
		CNode<DataType2>*    m_Next;
    };

	/** @name Types*/
    //@{
	typedef	typename CNode<DataType> Node;
    typedef CIterator<DataType> Iterator;
    //@}

	/** @name Constructor/Destructor*/
    //@{
	CList();
	CList( CMemoryHeap& heap );
	~CList();
    //@}

	/** @name Operator*/
	//@{
	CList& operator=( const CList& other );
	//@}
	/** @name Accessor*/
    //@{
	DataType&	GetFirstItem( ) const;
	DataType&	GetLastItem( )const;
	UInt32		GetItemCount() const;
	Void		SetItemCount( UInt32 count );
    //@}

    /** @name Mutator*/
    //@{
    DataType& GetItemAtIndex( const UInt32 pos ) const ;
    //@}

    /** @name Manipulator*/
    //@{
    Bool		Delete( const DataType& key );

    Void		ClearAllItems( );
    Bool        AddItemAtIndex( const DataType& item, const UInt32 pos ); 
    Bool        AddItemAtEnd( const DataType& item ) ;
    DataType&   AddItemAtEnd( )	;
    Bool        AddItemAtBegin( const DataType& item ) ;
    Bool        RemoveItemAtIndex( const UInt32 pos ) ;
    Bool        RemoveItem( const DataType& d ) ;
    Bool        RemoveItemAtEnd( ) ;
    Bool        RemoveItemAtBegin( ) ;
    Void		PushItem( const DataType& item ) ;
    DataType	PopItem( );
    Bool        HasItem( const DataType& d ) const;

    Void        StartIteration( Iterator& iterator ) const ;
    Void        SwapItems( const UInt32 a, const UInt32 b );
    //@}

private:

	// Methods
	Node*		AllocNode();
	Void		FreeNode( Node* n );

    //Attributes
	Node*				m_LastNode;
	Node*				m_RootNode;
	UInt32				m_EntryCount;
    CMemoryHeap*		m_MemoryHeap;

};

#include <Sable\Core\Collection\List.hpp>

}

#endif
