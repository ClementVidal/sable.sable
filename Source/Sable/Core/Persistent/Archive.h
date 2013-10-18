#ifndef _CORE_PERSISTENT_PERSISTENTARCHIVE_
#define _CORE_PERSISTENT_PERSISTENTARCHIVE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Collection/Map.h>
#include <Sable/Core/Collection/Stack.h>
#include <Sable/Core/Persistent/DataLayout.h>
#include <Sable/Core/ManagedObject/Ref.h>
#include <Sable/Core/File/FilePath.h>
#include <Sable/Core/Event/Header.h>
#include <Sable/Setup.h>

namespace Sable
{

class CPersistentArchive;


/** 
\ingroup CorePersistent
Provide High level interface for serialization of classes.
\n Manage the ManagedObject pointer table, and call the PersistentDataLayout appropriate method.
\n This class must be binded to a DataLayout which will send the data to the dataStream
*/
class CPersistentArchive : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CPersistentArchive )

public:

    /** @name Types*/
    //@{
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CPersistentArchive( );
    CPersistentArchive( CPersistentDataLayout& io, EAccesMode mode );
    ~CPersistentArchive();
    //@}

    /** @name Operator*/
    //@{
    Bool Open( CPersistentDataLayout& io, EAccesMode mode );

    template<typename ObjType>
    Bool Serialize( ObjType& obj, WString name );

    template<typename ObjType>
    Bool Serialize( CRef<ObjType>& obj, WString name );
    template<typename ObjType>
    Bool Serialize( CRef<ObjType>& obj, WString name, CMemoryHeap* heap );

    template< UInt32 Count>
    Bool Serialize( CStaticString<Count>& obj, WString name );

    Bool Serialize( UInt64& obj, WString name );
    Bool Serialize( UInt32& obj, WString name );
    Bool Serialize( UInt16& obj, WString name );
	Bool Serialize( UInt8& obj, WString name );
	Bool Serialize( Int64& obj, WString name );
    Bool Serialize( Int32& obj, WString name );
    Bool Serialize( Int16& obj, WString name );
    Bool Serialize( Int8& obj, WString name );
	Bool Serialize( Float32& obj, WString name );
    Bool Serialize( Char* obj, UInt32 s, WString name );
    Bool Serialize( WChar* obj, UInt32 s, WString name );
	Bool Serialize( Byte* obj, UInt32 s, WString name );

	Bool Serialize( CString& str, WString name );
    //@}

    /** @name Accessor*/
    //@{
    CPersistentDataLayout&  GetDataLayout() const ;
    Bool                    IsStoring() const;
    Bool                    IsLoading() const;
	EAccesMode				GetAccesMode() const;
    //@}

    /** @name Manipulator*/
    //@{
	Void					Reset();
    Void                    FlushData();
    Int16                   BeginScope( WString name, Int16 version );
    Bool                    EndScope( );
    //@}

    /** @name System reserved*/
    //@{
    virtual Int64            AcquirePointerID( CManagedObject* obj );
    virtual CManagedObject*  GetObjectFromID( Int64 id ) const;
    virtual Int64            GetIDFromObject( CManagedObject* obj );
    virtual Void             AddObject( CManagedObject* obj, Int64 id );
    //@}

private:

    // DataTypes
	struct SObjEntry
	{
		Int64			ID;
		CManagedObject*	Obj;
	};
    typedef CStack<SObjEntry>   DependencyLevel;
    typedef CMap< CStaticString<256>, UInt32 > ScopeDataSet;

    // Methods
    Void SerializeObjectTable();
	Void SerializeDependencyLevel( const DependencyLevel& lvl );

    // Attributes
    CPersistentDataLayout*                  m_DataLayout;
    EAccesMode                              m_AccesMode;
    CMap< Int64, CManagedObject* >          m_IDToObject;
    CMap< CManagedObject*, Int64 >          m_ObjectToID;

	DependencyLevel*						m_CurrentDepLevel;
	CStack<DependencyLevel>				    m_DepLevelStack;

    Int64                                   m_NextObjectId;

#ifdef SETUP_CONFIG_DEBUG
    CStack<ScopeDataSet>                    m_ScopeDataSet;
#endif

    //Static Methods

    //Static Attributes
};

/**
Function used to serialize all kind of composite object.
*/
template<typename ObjType>
Bool CPersistentArchive::Serialize( ObjType& obj, WString name )
{
    Bool v = FALSE;
    Int16 version = 0;

    DebugAssert( name != NULL )

    if( BeginScope( name, version ) == version )
    {
        v = obj.Serialize( *this );
        EndScope();
    }

    return v;
}

/**
Function used to serialize a ManagedObject CRef<>
\param obj The CRef<> to serialize
\param name the name of the serialized ref
\param heap the heap used to allocate object on de-serialization
\param args Argument passed to the allocation function used to allocate object on de-serialization
\param count Number of argument un args
*/
template<typename ObjType>
Bool CPersistentArchive::Serialize( CRef<ObjType>& obj, WString name, CMemoryHeap* heap )
{
    return obj.Serialize( *this, name, heap );
}

/**
Function used to serialize a ManagedObject CRef<>
\note This function is only provided for convenience, you should use the extended one ( that use the heap parameter ...)
If the object should be allocated it will be allocated on the default heap.
\param obj The CRef<> to serialize
\param name the name of the serialized ref
*/
template<typename ObjType>
Bool CPersistentArchive::Serialize( CRef<ObjType>& obj, WString name )
{
    return obj.Serialize( *this, name, NULL );
}

template< UInt32 Count >
Bool CPersistentArchive::Serialize( CStaticString<Count>& obj, WString name )
{
    DebugAssert( obj.GetCapacity() == Count );

    Bool retVal = TRUE;
    Char tmp[Count];
    StringCopy( obj.GetBuffer(), tmp, Count );

    retVal = Serialize( tmp, Count, name );

    if( IsLoading() )
        obj = tmp;

    return retVal;
}

}

#endif
