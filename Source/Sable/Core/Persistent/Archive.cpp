#include <Sable/Core/Persistent/Archive.h>

IMPLEMENT_MANAGED_CLASS1( Sable, CPersistentArchive, CManagedObject )

using namespace Sable;

#ifdef SETUP_CONFIG_DEBUG

    #define ARCHIVE_SUPPORT_PRIMITIVE( P ) \
    Bool CPersistentArchive::Serialize( P& obj, WString name ) \
    { \
	    if( m_AccesMode == nAccesMode_Write ) \
	    { \
            DebugAssertMsg( m_ScopeDataSet.GetTopItem().HasItem( name ) == FALSE, "Data in scope must have unique name" ); \
            DebugAssert( m_ScopeDataSet.GetTopItem().AddItem( name, 0 ) ); \
            m_DataLayout->Store( obj, WT(#P), name ); \
            return TRUE; \
	    } \
	    else if( m_AccesMode == nAccesMode_Read ) \
	    { \
		    return m_DataLayout->Load( obj, WT(#P), name ); \
	    } \
     \
        return FALSE; \
    } \

    #define ARCHIVE_SUPPORT_PRIMITIVE_ARRAY( P ) \
    Bool CPersistentArchive::Serialize( P obj, UInt32 s, WString name ) \
    { \
	    if( m_AccesMode == nAccesMode_Write ) \
	    { \
            DebugAssertMsg( m_ScopeDataSet.GetTopItem().HasItem( name ) == FALSE, "Data in scope must have unique name" ); \
            DebugAssert( m_ScopeDataSet.GetTopItem().AddItem( name, 0 ) ); \
            m_DataLayout->Store( obj, s, WT(#P), name ); \
		    return TRUE; \
	    } \
	    else if( m_AccesMode == nAccesMode_Read ) \
	    { \
		    return m_DataLayout->Load( obj, s, WT(#P), name ); \
	    } \
     \
        return FALSE; \
    } \

#else 

    #define ARCHIVE_SUPPORT_PRIMITIVE( P ) \
    Bool CPersistentArchive::Serialize( P& obj, WString name ) \
    { \
        if( m_AccesMode == nAccesMode_Write ) \
        { \
            m_DataLayout->Store( obj, WT(#P), name ); \
            return TRUE; \
        } \
        else if( m_AccesMode == nAccesMode_Read ) \
        { \
            return m_DataLayout->Load( obj, WT(#P), name ); \
        } \
        \
        return FALSE; \
    } \

    #define ARCHIVE_SUPPORT_PRIMITIVE_ARRAY( P ) \
    Bool CPersistentArchive::Serialize( P obj, UInt32 s, WString name ) \
    { \
        if( m_AccesMode == nAccesMode_Write ) \
        { \
            m_DataLayout->Store( obj, s, WT(#P), name ); \
            return TRUE; \
        } \
        else if( m_AccesMode == nAccesMode_Read ) \
        { \
            return m_DataLayout->Load( obj, s, WT(#P), name ); \
        } \
        \
        return FALSE; \
    } \

#endif

ARCHIVE_SUPPORT_PRIMITIVE( UInt64 )
ARCHIVE_SUPPORT_PRIMITIVE( UInt32 )
ARCHIVE_SUPPORT_PRIMITIVE( UInt16 )
ARCHIVE_SUPPORT_PRIMITIVE( UInt8 )
ARCHIVE_SUPPORT_PRIMITIVE( Int64 )
ARCHIVE_SUPPORT_PRIMITIVE( Int32 )
ARCHIVE_SUPPORT_PRIMITIVE( Int16 )
ARCHIVE_SUPPORT_PRIMITIVE( Int8 )
ARCHIVE_SUPPORT_PRIMITIVE( Float32 )
ARCHIVE_SUPPORT_PRIMITIVE( CString )
ARCHIVE_SUPPORT_PRIMITIVE_ARRAY( Char* )
ARCHIVE_SUPPORT_PRIMITIVE_ARRAY( WChar* )
ARCHIVE_SUPPORT_PRIMITIVE_ARRAY( Byte* )


CPersistentArchive::CPersistentArchive( )
{
    Reset();
}

CPersistentArchive::CPersistentArchive( CPersistentDataLayout& io, EAccesMode mode  )
{
    Reset();

    Bool rval = Open( io, mode );
	DebugAssert( rval );
}

CPersistentArchive::~CPersistentArchive()
{
}

Bool CPersistentArchive::Open( CPersistentDataLayout& dataLayout, EAccesMode mode )
{
    m_AccesMode = mode;
    m_DataLayout = &dataLayout;

	m_DepLevelStack.SetCapacity( 1024 );
	m_DepLevelStack.PushItem();
	m_CurrentDepLevel = &m_DepLevelStack.GetTopItem();
	m_CurrentDepLevel->SetCapacity( 2048 );

    return dataLayout.Open( *this );
}

CPersistentDataLayout& CPersistentArchive::GetDataLayout() const
{
	return *m_DataLayout;
}

Void CPersistentArchive::Reset()
{
	m_NextObjectId = 0;
	m_DataLayout = NULL;
	m_AccesMode = nAccesMode_None;
	m_CurrentDepLevel = NULL;
	m_DepLevelStack.ClearAllItems();

#ifdef SETUP_CONFIG_DEBUG
	m_ScopeDataSet.SetCapacity(128);
#endif
}

/** Return TRUE is the archive is in Storing mode
*/
Bool CPersistentArchive::IsStoring() const
{
    return ( m_AccesMode == nAccesMode_Write );
}

EAccesMode CPersistentArchive::GetAccesMode() const
{
	return m_AccesMode;
}

/** Return TRUE is the archive is in loading mode
*/
Bool CPersistentArchive::IsLoading() const
{
    return ( m_AccesMode == nAccesMode_Read );
}

/**
Flush Data MUST be called after in/out serialization in order to effectively flush right data
to/from file.

This include to deserialize the object table
*/
Void CPersistentArchive::FlushData()
{
    // Important: do no skeep order.
    // ObjectTable MUS be deserialized before effective flush data
    SerializeObjectTable();
    m_DataLayout->FlushData( IsStoring() );
}

Int16 CPersistentArchive::BeginScope( WString name, Int16 version  )
{
#ifdef SETUP_CONFIG_DEBUG
    m_ScopeDataSet.PushItem();
#endif

	return m_DataLayout->BeginScope( name, version );
}

Bool CPersistentArchive::EndScope( )
{
#ifdef SETUP_CONFIG_DEBUG
    m_ScopeDataSet.PopItem();
#endif

	return m_DataLayout->EndScope();
}

/**
Serialize a given dependencyLevel.
If during the serialization, of this level (i.e objects list) new object needs to be serialized,
they are going to be pushed onto a new dependencyLevel
*/
Void CPersistentArchive::SerializeDependencyLevel( const DependencyLevel& lvl )
{
	UInt32 i = 0;
	Int16 version = 0;

	for( i=0;i<lvl.GetItemCount();i++ )
	{
		SObjEntry entry = lvl.GetItemAtIndex( i );

		if( BeginScope( WT("Object"), version ) == version )
		{
			Serialize( entry.ID, WT("Ouid") );
			entry.Obj->Serialize( *this );

			EndScope();
		}
	}
}

Void CPersistentArchive::SerializeObjectTable()
{
    Int16 version = 0;

    if( BeginScope( WT("ObjectTable"), version ) == version )
    {
		// Loop will end if no new objects are add to the archive during the SerializeDependencyLevel()
		while( m_CurrentDepLevel->GetItemCount() )
		{
			DependencyLevel* depLevelToSerialize = m_CurrentDepLevel;
			// Prepare a new level of dependency.
			// Any new serialization request will then be pushed onto this new level and processed in order 
			// during the next loop iteration.
			m_DepLevelStack.PushItem( );
			m_CurrentDepLevel = &m_DepLevelStack.GetTopItem();
			m_CurrentDepLevel->SetCapacity( 2048 );

			SerializeDependencyLevel( *depLevelToSerialize );
		}

		EndScope();
    }
}

/**
Ask for a new Pointer ID.

During the life time of the archive, each call to AcquirePointerID will
return a unique integer which can be used to register new object to the archive.
*/
Int64 CPersistentArchive::AcquirePointerID( CManagedObject* obj )
{
    m_NextObjectId++;
    return m_NextObjectId - 1;
}

CManagedObject* CPersistentArchive::GetObjectFromID( Int64 id ) const
{
    if( m_IDToObject.HasItem( id ) )
        return m_IDToObject.GetItem( id );

    return NULL;
}

/**
Return the ID of a given pointer, or -1 is the pointer does not already exist in
the archive pointer data base.
*/
Int64 CPersistentArchive::GetIDFromObject( CManagedObject* obj )
{
    UInt32 addr = (UInt32) obj;

    if( m_ObjectToID.HasItem( obj ) )
        return m_ObjectToID.GetItem( obj );

    return -1;
}

/**
Push an object in the current dependency level
*/
Void CPersistentArchive::AddObject( CManagedObject* obj, Int64 id )
{
    DebugAssert( obj );

    m_ObjectToID.AddItem( obj, id );
    m_IDToObject.AddItem( id, obj );

	// Push the item on the current dependency level stack
	SObjEntry entry;
	entry.ID = id;
	entry.Obj = obj;
	m_CurrentDepLevel->PushItem( entry );
}
