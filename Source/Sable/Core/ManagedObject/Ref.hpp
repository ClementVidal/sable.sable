 


template < class DataType >
CRef<DataType>::CRef()
{
	m_Pointer = NULL;
}

template < class DataType >
CRef<DataType>::CRef( const CRef<DataType>& sp )
{		
	m_Pointer = NULL;
	(*this) = (DataType*)sp.m_Pointer;
}

template < class DataType >
CRef<DataType>::CRef( const DataType* sp )
{
	m_Pointer = NULL;
	(*this) = sp;
}

template < class DataType >
CRef<DataType>::~CRef()
{
	ReleasePointer();

	m_Pointer = NULL;
}


template < class DataType >
Void CRef<DataType>::ReleasePointer()
{
	if( m_Pointer == NULL ) 
		return;

    CManagedObject* m = (CManagedObject*) m_Pointer;
	CMemoryHeap* heap = m->GetMemoryHeap();
	m->ReleasePointer();
	if( m->GetRefCount() == 0 && heap)   
	{
		DestructObject( m, CManagedObject );

		MemoryFree( *heap, m_Pointer );
	}

	m_Pointer = NULL;
}

template < class DataType >
Void CRef<DataType>::AcquirePointer( const Void* n )
{
	if( m_Pointer != NULL ) 
		ReleasePointer(); 

	if( n == NULL ) 
		return;

	m_Pointer = (DataType*) n;

    CManagedObject* m = (CManagedObject*) m_Pointer;

    m->AddPointer(); 
}

template <class DataType>
DataType& CRef<DataType>::operator* () const
{
	DebugAssertMsg( m_Pointer!=NULL, "CPointer::operator*\nNull pointer access");
	return *(m_Pointer);
}

template < class DataType >
DataType* CRef<DataType>::operator-> () const 
{ 
	DebugAssertMsg( m_Pointer!=NULL, "CPointer::operator->\nNull pointer access");
	return (m_Pointer); 
}

template < class DataType >
CRef<DataType>& CRef<DataType>::operator = ( const DataType* n )
{
	if( n == (m_Pointer)) 
		return *this; 

	ReleasePointer();
	AcquirePointer( n ); 
	return *this;
}

template < class DataType >
CRef<DataType>& CRef<DataType>::operator = ( const CRef<DataType>& sp )
{			
	if( (CManagedObject*)sp.m_Pointer == ((CManagedObject*)m_Pointer)) 
		return *this; 

	ReleasePointer();
	AcquirePointer( (DataType*)sp.m_Pointer ); 
	return *this;
}

template < class DataType >
CRef<DataType>::operator DataType* () const
{
    return m_Pointer;
}

template < class DataType >
Bool CRef<DataType>::GetIsNull() const
{
	return ( m_Pointer == NULL );
}

template < class DataType >
Bool CRef<DataType>::GetIsValid() const
{
	return ( m_Pointer != NULL );
}

template < class DataType >
Void CRef<DataType>::SetNull()
{
	(*this) = (const DataType*) NULL;
}

template < class DataType >
CManagedObject* CRef<DataType>::GetPointer( )
{
	return (CManagedObject*)m_Pointer;
}

template < class DataType >
Void CRef<DataType>::SetPointer( CManagedObject* p )
{
	m_Pointer = (DataType*)p;
}
