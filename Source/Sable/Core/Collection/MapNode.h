#ifndef _CORE_COLLECTION_MAPNODE_
#define _CORE_COLLECTION_MAPNODE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Memory/Heap.h>
#include <Sable/Core/Debug/Primitives.h>
#include <Sable/Core/Memory/Primitives.h>

namespace Sable
{

class CPersistentArchive;

/** 
\ingroup Core
Archive.
*/
template <class KeyType, class DataType>
class CMapNode 
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CMapNode( );
    //@}

	/** @name Types*/
	//@{
    typedef CMapNode< KeyType, DataType > MapNode;
	//@}

	/** @name Manipulator*/
	//@{
	Void ComputeHeight();
    Int8 GetBalanceValue();
    Void Clear(CMemoryHeap& alloc);
    CMapNode<KeyType,DataType>* MoveDownRightHandSide( CMapNode<KeyType,DataType>* rhs );
    CMapNode<KeyType,DataType>* Balance();
    CMapNode<KeyType,DataType>* Delete( const KeyType& inkey, CMapNode<KeyType,DataType>*& listRoot, CMemoryHeap& alloc );
    CMapNode<KeyType,DataType>* Get( const KeyType& inkey ) const ;
	CMapNode<KeyType,DataType>* New( const KeyType& inkey, const DataType& indata, CMapNode<KeyType,DataType>*& listRoot, CMemoryHeap& alloc );
    CMapNode<KeyType,DataType>* ExchangeLeft(CMapNode<KeyType,DataType>* & r, CMapNode<KeyType,DataType>* node );
    CMapNode<KeyType,DataType>* ExchangeRight(CMapNode<KeyType,DataType>* & r, CMapNode<KeyType,DataType>* node );
    CMapNode<KeyType,DataType>* RotateLeft();
    CMapNode<KeyType,DataType>* RotateRight();
	//@}


	KeyType			Key;
	DataType		Data;
	Int32			Height;

	MapNode* Left;
	MapNode* Right;

	MapNode* Next;
	MapNode* Previous;

private:

	// Types

	// Methods

};


#include <Sable/Core/Collection/MapNode.hpp>

}

#endif
