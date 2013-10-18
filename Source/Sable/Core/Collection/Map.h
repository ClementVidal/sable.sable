#ifndef _CORE_COLLECTION_MAP_
#define _CORE_COLLECTION_MAP_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Common/Primitives.h>
#include <Sable/Core/Collection/MapNode.h>
#include <Sable/Core/Memory/Manager.h>

namespace Sable
{

class CPersistentArchive;
class CMemory;

/** 
\ingroup CoreCollection
Map (use AVL tree). 
*/
template <class KeyType, class DataType>
class CMap
{

public:

	/** 
	Iterator. 
	*/
    template <class KeyType2, class DataType2>
    class CIterator
    {

    public:

	    /** @name Constructor/Destructor*/
        //@{
        CIterator( )
        {
            m_Node = NULL;
        }
        CIterator( CMapNode<KeyType2,DataType2>* node )
        {
            m_Node = node;
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
        KeyType2& GetKey()
        {
            return m_Node->Key;
        }
        //@}

	    /** @name Manipulator*/
        //@{
        Void    Iterate()
        {
            if( m_Node )
                m_Node = m_Node->Next;
        }
        //@}

    private:

        CMapNode<KeyType2,DataType2>*    m_Node;

    };

    /** @name Types*/
    //@{
    typedef CIterator<KeyType, DataType> Iterator;
    //@}

	/** @name Constructor/Destructor*/
    //@{
	CMap();
	virtual ~CMap();
    //@}

	/** @name Operator*/
	//@{
	CMap<KeyType, DataType>&   operator =( const CMap< KeyType, DataType>& other );
	//@}

    /** @name Accessors*/
    //@{
	UInt32			GetItemCount() const ;
	Void			SetItem( const KeyType& key, const DataType& data ) ;
	const DataType&	GetItem( const KeyType& key ) const;
	const DataType*	GetItemPtr( const KeyType& key ) const;
	DataType&		GetItem( const KeyType& key ) ;
	DataType*		GetItemPtr( const KeyType& key ) ;
	Bool			HasItem( const KeyType& key ) const;
    //@}

	/** @name Manipulator*/
    //@{
	DataType&	AddItem( const KeyType& key );
	Bool		AddItem( const KeyType& key, const DataType& data);
	Bool		RemoveItemAtKey( const KeyType& key );
	Void		ClearAllItems( ); 
    Void        StartIteration( Iterator& iterator ) const;
    //@}

private:

	// Types
	typedef CMapNode<KeyType,DataType> MapNode;

    //Attributes
	MapNode*		m_TreeRootNode;
	MapNode*		m_ListRootNode;
	UInt32		    m_EntryCount;
    CMemoryHeap*	m_MemoryHeap;

};

#include <Sable/Core/Collection/Map.hpp>

}
#endif
