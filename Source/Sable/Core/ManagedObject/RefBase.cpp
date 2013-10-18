#include <Sable/Core/ManagedObject/RefBase.h> 

using namespace Sable;

CRefBase::CRefBase()
{
}

CRefBase::~CRefBase()
{

}

Bool CRefBase::Serialize( CPersistentArchive& ar, WString name, CMemoryHeap* heap )
{
    Char fullTypeName[128];
	Int16 version = 0;
    Int64 id;

    if( ar.IsStoring() )
    {
        if( GetPointer() )
        {
			if( ar.BeginScope( WT("Ref"), version ) == version )
			{
				StringCopy( GetPointer()->GetTypeInfo().GetFullTypeName(), fullTypeName, 128 );
				ar.Serialize( fullTypeName, 128, WT("Type") );

				// Get the ID of the pointer if it was already registered into the archive internal DB
				id = ar.GetIDFromObject( GetPointer() );
				if( id == -1 )
				{
					// If not, quire a new one from the archive internal DB
					id = ar.AcquirePointerID( GetPointer() );
					ar.AddObject( GetPointer(), id );
				}

				ar.Serialize( id, WT("Ouid") );

				ar.EndScope();
			}
        }
        else
        {
            id = -1;
            StringCopy( "", fullTypeName, 128 );
			if( ar.BeginScope( WT("Ref"), version ) == version )
			{
				ar.Serialize( fullTypeName, 128, WT("Type") );
				ar.Serialize( id, WT("Ouid") );
				ar.EndScope();
			}
        }
    }
    else
    {
       SetPointer( NULL );

        CManagedObject* ptr = NULL;
		if( ar.BeginScope( WT("Ref"), version ) == version )
		{
			ar.Serialize( fullTypeName, 128, WT("Type") );
			ar.Serialize( id, WT("Ouid") );

			if( id != -1 )
			{
				ptr = ar.GetObjectFromID( id );
				if( ptr == NULL )
				{
					const CTypeInfo& classType = CManagedObject::GetStaticTypeInfo().GetDerivedClass( fullTypeName );

					if( classType != CTypeInfo::NullType )
					{
						DebugAssert( classType.HasAllocator() );

						ptr = (CManagedObject*) classType.CreateObject( heap );
						DebugAssert( ptr->GetTypeInfo().IsA( fullTypeName ) );
						ar.AddObject( ptr, id );
					}
					else
					{
						CoreManager.GetLog().LogWarning( "Trying to deserialize object (Ouid: %d) with an invalid type: %s", (UInt32)id, fullTypeName );
					}
				}

				// This will increase ref count of object
				if( ptr )
					AcquirePointer( ptr );
			}
			ar.EndScope();
		}
    }
    return TRUE;
}
