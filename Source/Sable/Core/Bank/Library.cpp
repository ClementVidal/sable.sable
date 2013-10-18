#include <Sable/Core/Bank/Library.h>

IMPLEMENT_MANAGED_CLASS1( Sable, CBankLibrary, CPersistentArchive )

using namespace Sable;


CBankLibrary::CBankLibrary( )
{
	m_NextFreeId = 0;
	m_CurrentBank = NULL;
	m_IsStoring = FALSE;
}

CBankLibrary::~CBankLibrary()
{
}

Int64 CBankLibrary::GetIDFromObject( CManagedObject* obj ) const
{
	UInt32 addr = (UInt32) obj;

	if( m_ObjectToID.HasItem( obj ) )
		return m_ObjectToID.GetItem( obj );

	return -1;
}

CManagedObject* CBankLibrary::GetObjectFromID( Int64 id ) const
{
	if( m_IDToObject.HasItem( id ) )
		return m_IDToObject.GetItem( id );

	return NULL;
}

Void CBankLibrary::AddObject( CManagedObject* obj, Int64 id )
{
	DebugAssert( obj );
	DebugAssert( m_ObjectToID.HasItem( obj ) == FALSE );

	m_ObjectToID.AddItem( obj, id );
	m_IDToObject.AddItem( id, obj );

	Int64 bankId = id;
	bankId >>= 32;

	CBank* b = FindBank( (HashValue)bankId );
	if( b )
		m_CurrentBank = b;

	m_CurrentBank->GetArchive().AddObjectWithoutLibraryLookup( obj, id );
	
}

Int64 CBankLibrary::AcquirePointerID( CManagedObject* obj )
{
	DebugAssert( m_ObjectToID.HasItem( obj ) == FALSE );

	Int64 i = -1;
	CBank* b = FindBank( obj );
	if( b )
		m_CurrentBank = b;

	DebugAssert( m_CurrentBank );
	
	Int64 msb = m_CurrentBank->GetId();
	Int64 lsb = m_NextFreeId;
	i = msb;
	i <<= 32;
	i |= lsb;
	m_NextFreeId++;
	
	return i;
}

CBank* CBankLibrary::FindBank( HashValue bankId ) const
{
	BankTable::Iterator it;
	ForEachItem( it, m_BankTable )
	{
		if( (*it)->GetId() == bankId )
			return (*it);		
	}
	return NULL;
}

CBank* CBankLibrary::FindBank( CManagedObject* obj ) const
{
	BankTable::Iterator it;
	ForEachItem( it, m_BankTable )
	{
		if( (*it)->HasObject( obj ) )
			return (*it);		
	}
	return NULL;
}

CBank* CBankLibrary::GetBank( String name ) const
{
	BankTable::Iterator it;
	ForEachItem( it, m_BankTable )
	{
		if( StringCompare( (*it)->GetName(), name ) == 0 )
			return *it;
	}
	return NULL;
}

Bool CBankLibrary::Save()
{
	BankTable::Iterator it;

	m_IsStoring = TRUE;

	ForEachItem( it, m_BankTable )
	{
		(*it)->Open( nAccesMode_Write );
	}

	ForEachItem( it, m_BankTable )
	{
		(*it)->Save( );
	}

	return TRUE;
}

Bool CBankLibrary::Load()
{
	BankTable::Iterator it;

	m_IsStoring = FALSE;

	ForEachItem( it, m_BankTable )
	{
		if( !(*it)->Open( nAccesMode_Read ) )
			return FALSE;
	}

	ForEachItem( it, m_BankTable )
	{
		(*it)->Load( );
	}

	return TRUE;
}

/**
Add a new bank to this library.
TODO: Check if a bank with the given path is not already loaded
*/
Bool CBankLibrary::AddBank( const CFilePath& path )
{
	CBank* b = NEWOBJ( CBank, () );
	b->SetFilePath( path );
	b->SetLibrary( this );

	m_BankTable.AddItemAtEnd( b );

	return TRUE;
}