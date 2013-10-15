#ifndef _CORE_COLLECTION_STACK_
#define _CORE_COLLECTION_STACK_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Memory\Heap.h>

namespace Sable
{

/**
\ingroup CoreCollection
Stack 
*/
template< class DataType >
class CStack 
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
        CIterator( const CStack<DataType2>* stack ) :
            m_Stack( stack )
        {
            m_Index = 0;
        }
        //@}

        /** @name Operator*/
        //@{
        DataType2& operator * () const
        {
            return m_Stack->m_Array[m_Index];
        }
        //@}

        /** @name Accessor*/
        //@{
        DataType2& GetData() const
		{
		    return m_Stack->m_Array[m_Index];
		}

		Bool    GetIsValid() const 
        {
            return m_Index < m_Stack->GetItemCount();
        }
        //@}

	    /** @name Manipulator*/
        //@{
        Void    Iterate()
        {
            m_Index++;
        }
        //@}

    private:

        const CStack<DataType2>*    m_Stack;
        UInt32              m_Index;

    };

    /** @name Types*/
    //@{
    typedef CIterator<DataType> Iterator;
    //@}

	/** @name Constructor/Destructor*/
    //@{
	CStack();
	CStack( UInt32 s );
	~CStack();
    //@}

	/** @name Operator*/
    //@{
    //@}

	/** @name Accessors*/
    //@{
	DataType*			GetBuffer() const ;
	UInt32				GetCapacity() const ;
	Void				SetCapacity( UInt32 count );
    UInt32				GetItemCount() const;
	Bool				IsEmpty() const;
	const DataType&		GetTopItem() const;
    DataType&			GetTopItem() ;

    const DataType&	    GetItemAtIndex( UInt32 i ) const;
    DataType&			GetItemAtIndex( UInt32 i );
    //@}

    /** @name Manipulator*/
    //@{
	Void        PushItem( );
	Void        PushItem( const DataType& item );
	Void        PopItem();
	Void        ClearAllItems();
    Void        StartIteration( Iterator& iterator ) const;
    //@}

private:

	//Methods
	DataType*		Allocate( SysSize s );
	Void    		Free( );

    //Attributes
	Int32			m_StackIndex;
	DataType*		m_Array;
	UInt32			m_Capacity;
    CMemoryHeap*	m_MemoryHeap;
};

#include <Sable\Core\Collection\Stack.hpp>

}

#endif
