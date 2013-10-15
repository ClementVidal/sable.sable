
template <class KeyType, class DataType>
CMapNode<KeyType,DataType>::CMapNode( )
{
    Right       = NULL;
    Left        = NULL;
    Previous    = NULL;
    Next        = NULL;
    Height      = 1;
}

template <class KeyType, class DataType>
Void CMapNode<KeyType,DataType>::ComputeHeight()
{
	Height = 0;
	if( Left && ( Left->Height > Height ) )
		Height = Left->Height;
	if( Right && ( Right->Height > Height ) )
		Height = Right->Height;

	Height++;
}

template <class KeyType, class DataType>
CMapNode<KeyType,DataType>* CMapNode<KeyType,DataType>::New( const KeyType& inkey, const DataType& indata, CMapNode<KeyType,DataType>*& listRoot, CMemoryHeap& alloc )
{
	if( this == NULL )
    {
		MapNode* tmp;
		tmp = (MapNode*) MemoryAllocate( alloc, sizeof( MapNode ) );
        ConstructObject( tmp, MapNode );

        tmp->Key = inkey;
        tmp->Data = indata;

        tmp->Left = NULL;
        tmp->Right = NULL;

        tmp->Previous = NULL;
        tmp->Next = listRoot;

        if(listRoot)
            listRoot->Previous = tmp;
        
        listRoot = tmp;

		return tmp;
    }
    
    DebugAssertMsg(!(inkey == Key), "CMapNode<KeyType,DataType>::New\nA resource with the same hey already exist");

	if( inkey < Key )
		Left =  Left->New( inkey, indata, listRoot, alloc );
	else
		Right =  Right->New( inkey, indata, listRoot, alloc );

	return Balance();
}

template <class KeyType, class DataType>
CMapNode<KeyType,DataType>* CMapNode<KeyType, DataType>::Get( const KeyType& inkey ) const
{
	if( ! this )
		return NULL;

    if( inkey == Key )
        return (CMapNode<KeyType,DataType>*)this;

	if( inkey  < Key )
		return Left->Get( inkey );
	else
		return Right->Get( inkey );
}

template <class KeyType, class DataType>
Void CMapNode<KeyType, DataType>::Clear( CMemoryHeap& alloc )
{
	MapNode* tmp;

    if( this == NULL )
        return;

    Left->Clear( alloc );
    Right->Clear( alloc );

    tmp = this;
	tmp->MapNode::~MapNode();
	MemoryFree( alloc, tmp );
}

template <class KeyType, class DataType>
CMapNode<KeyType,DataType>* CMapNode<KeyType, DataType>::Delete( const KeyType& inkey, CMapNode<KeyType,DataType>*& listRoot, CMemoryHeap& alloc )
{
    if( this == NULL )
		return NULL;  

    if(inkey == Key)
    {
        MapNode* tmp1, *tmp2;
        tmp1 = Left->MoveDownRightHandSide( Right);

        Left = NULL;
        Right = NULL;

        //Modifie list pointer
        if( Previous )
            Previous->Next = Next;

        if( Next )
            Next->Previous = Previous;

        tmp2 = this;

		if( this == listRoot )
			listRoot = Next;

		tmp2->MapNode::~MapNode();
		MemoryFree( alloc, tmp2 );
		return tmp1;
    }

	if( inkey  < Key )
		Left =  Left->Delete( inkey, listRoot, alloc );
	else
		Right = Right->Delete( inkey, listRoot, alloc );

    return Balance();
}

template <class KeyType, class DataType>
CMapNode<KeyType,DataType>* CMapNode<KeyType, DataType>::Balance()
{
    Int8 d = GetBalanceValue();

    if( d < -1 || d > 1 )
    {
        if( d < 0 )
        {
            if( Right->GetBalanceValue() > 0)
                Right = Right->RotateRight();

            return RotateLeft();
        }
        else
        {
            if( Left->GetBalanceValue() < 0 )
                Left = Left->RotateLeft();

            return RotateRight();
        }
    }

    ComputeHeight();
    return this;
}

template <class KeyType, class DataType>
CMapNode<KeyType,DataType>* CMapNode<KeyType, DataType>::MoveDownRightHandSide( CMapNode<KeyType,DataType>* rhs )
{
    if( this == NULL)
        return rhs;

    Right = Right->MoveDownRightHandSide( rhs);
    return Balance();
}

template <class KeyType, class DataType>
CMapNode<KeyType,DataType>* CMapNode<KeyType, DataType>::ExchangeLeft(CMapNode<KeyType,DataType>* & r, CMapNode<KeyType,DataType>* node)
{
    r = Left;
    Left = node->Balance();
    return Balance();
}

template <class KeyType, class DataType>
CMapNode<KeyType,DataType>* CMapNode<KeyType, DataType>::ExchangeRight(CMapNode<KeyType,DataType>* & r, CMapNode<KeyType,DataType>* node)
{
    r = Right;
    Right = node->Balance();
    return Balance();
}

template <class KeyType, class DataType>
Int8 CMapNode<KeyType, DataType>::GetBalanceValue()
{
    Int8 leftheight = 0;
    Int8 rightheight = 0;

    if( Left )
    {
        leftheight = Left->Height;
    }

    if( Right )
    {
        rightheight = Right->Height;
    }

    return leftheight - rightheight;
}

template <class KeyType, class DataType>
CMapNode<KeyType,DataType>* CMapNode<KeyType, DataType>::RotateLeft()
{
    return Right->ExchangeLeft( Right, this );
}

template <class KeyType, class DataType>
CMapNode<KeyType,DataType>* CMapNode<KeyType, DataType>::RotateRight()
{
    return Left->ExchangeRight( Left, this );
}

