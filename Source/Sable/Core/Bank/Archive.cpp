#include <Sable\Core\Bank\Archive.h>

#include <Sable\Core\Bank\Library.h>
#include <Sable\Core\Bank\Bank.h>


using namespace Sable;

CBankArchive::CBankArchive( ) :
	CPersistentArchive( )
{
	m_Library = NULL;
}

Int64 CBankArchive::AcquirePointerID( CManagedObject* obj )
{
	DebugAssert( m_Library );
	return m_Library->AcquirePointerID( obj );
}


Void CBankArchive::SetLibrary( CBankLibrary* lib )
{
	m_Library = lib;
}

Void CBankArchive::AddObjectWithoutLibraryLookup( CManagedObject* obj, Int64 id )
{
	CPersistentArchive::AddObject( obj, id );
}

CManagedObject* CBankArchive::GetObjectFromID( Int64 id ) const
{
	DebugAssert( m_Library );
	return m_Library->GetObjectFromID( id );
}

Int64 CBankArchive::GetIDFromObject( CManagedObject* obj )
{
	DebugAssert( m_Library );
	return m_Library->GetIDFromObject( obj );
}

Void CBankArchive::AddObject( CManagedObject* obj, Int64 id )
{
	DebugAssert( m_Library );
	return m_Library->AddObject( obj, id );
}
