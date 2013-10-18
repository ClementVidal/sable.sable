#include <Sable/Core/ManagedObject/ManagedObject.h>

#include <Sable/Core/Memory/Heap.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CManagedObject );

CManagedObject::CManagedObject()
{	
	m_PointerCounter = 0;
	m_MemoryHeap = NULL;
}

CManagedObject::~CManagedObject()
{
}

/**
This method is called explicitly by the NEWOBJ macro right after the new operator is executed.
So this method is ONLY called if the object is allocated dynamically
*/
CManagedObject* CManagedObject::OnAllocate( CMemoryHeap* heap )
{
	if( heap ) 
	{ 
		m_MemoryHeap = heap; 
	} 
	else 
	{ 
		m_MemoryHeap = &CoreManager.GetMemoryManager().GetBuddyHeap(); 
	} 
	return this;
}

/**
Debug version of the new operator without specific heap
*/
Void* CManagedObject::operator new( SysSize size, const Char* fileName, UInt32 line )
{ 
    CMemoryHeap& heap = CoreManager.GetMemoryManager().GetBuddyHeap(); 
	CManagedObject* object = (CManagedObject*) heap.DebugAllocate( size, fileName, line); 
	return (Void*)object; 
} 

/**
Debug version of the new operator with specific heap.
\param heap The heap used to allocate teh necessary memory. if NULL, The global dummy head is used instead
*/
Void* CManagedObject::operator new( SysSize size, CMemoryHeap* heap, const Char* fileName, UInt32 line )
{ 
	CManagedObject* object; 
	if( heap ) 
	{ 
		object = (CManagedObject*) heap->DebugAllocate( size, fileName, line); 
	} 
	else 
	{ 
        CMemoryHeap& heap = CoreManager.GetMemoryManager().GetBuddyHeap(); 
		object = (CManagedObject*) heap.DebugAllocate( size, fileName, line); 
	} 
	return (Void*)object; 
} 

/**
Release version of the new operator without specific heap
*/
Void* CManagedObject::operator new( SysSize size ) 
{ 
    CMemoryHeap& heap = CoreManager.GetMemoryManager().GetBuddyHeap(); 
	CManagedObject* object = (CManagedObject*) heap.Allocate( size ); 
	return (Void*)object; 
} 

/**
Release version of the new operator with specific heap
\param heap The heap used to allocate teh necessary memory. if NULL, The global dummy head is used instead
*/
Void* CManagedObject::operator new( SysSize size, CMemoryHeap* heap ) 
{ 
	CManagedObject* object; 
	if( heap ) { 
		object = (CManagedObject*) heap->Allocate( size ); 
	} 
	else 
	{ 
        CMemoryHeap& heap = CoreManager.GetMemoryManager().GetBuddyHeap(); 
		object = (CManagedObject*) heap.Allocate( size ); 
	} 
	return (Void*)object; 
} 

Void CManagedObject::operator delete( Void* data )
{
	DebugError("CManagedObject::operator delete - CManagedObject cannot be destroyed manualy");
} 

Void CManagedObject::operator delete( Void* data, CMemoryHeap* heap )
{
    DebugError("CManagedObject::operator delete - CManagedObject cannot be destroyed manualy");
} 

Void CManagedObject::operator delete( Void* data, const Char* fileName, UInt32 line )
{
    DebugError("CManagedObject::operator delete - CManagedObject cannot be destroyed manualy");
} 

Void CManagedObject::operator delete( Void* data, CMemoryHeap* heap, const Char* fileName, UInt32 line )
{
    DebugError("CManagedObject::operator delete - CManagedObject cannot be destroyed manualy");
} 

Bool CManagedObject::Serialize( CPersistentArchive& ar )
{
	Char buffer[128];
	StringCopy( GetTypeInfo().GetFullTypeName(), buffer, 128 );
	ar.Serialize( buffer, 128, WT("Type") );

	return TRUE;
}
