#ifndef _CORE_MMANAGEDOBJECT_MANAGEDOBJECT_
#define _CORE_MMANAGEDOBJECT_MANAGEDOBJECT_

#include <Sable/Core/Debug/Primitives.h>
#include <Sable/Core/ManagedObject/Macro.h>
#include <Sable/Core/ManagedObject/TypeInfo.h>

namespace Sable
{

class CPersistentArchive;
class CMemoryHeap;

/** 
\ingroup CoreManagedObject
Base Class for every managed object
*/
class CManagedObject
{

	DEFINE_MANAGED_CLASS( CManagedObject );

public:

	/** @name Constructor*/
	//@{
	CManagedObject();
	virtual ~CManagedObject();
	//@}

	/** @name operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
	CManagedObject*	OnAllocate( CMemoryHeap* heap ) ;
	CMemoryHeap*    GetMemoryHeap() const;
	UInt32          GetRefCount()const { return m_PointerCounter; } /**< Get the number of pointer linked object*/ 
	//@}

	/** @name Mutator*/
	//@{
    // Debug new/delete
	Void* operator new( SysSize size, const Char* fileName, UInt32 line );
	Void operator delete( Void* data, const Char* fileName, UInt32 line );
	Void* operator new( SysSize size, CMemoryHeap* heap, const Char* fileName, UInt32 line );
	Void operator delete( Void* data, CMemoryHeap* heap, const Char* fileName, UInt32 line );
    // Release new/delete
	Void* operator new( SysSize size ) ;
    Void operator delete( Void* data );
	Void* operator new( SysSize size, CMemoryHeap* heap ) ;
    Void operator delete( Void* data, CMemoryHeap* heap ) ;

	template< class T >
	T* CastTo() const;
	//@}

	/** @name Manipulator*/
	//@{
	virtual UInt32  AddPointer() ;
	virtual UInt32  ReleasePointer();
    virtual Bool    Serialize( CPersistentArchive& ar );
    //@}

private:

	// Attribute
	UInt32	            m_PointerCounter;
	CMemoryHeap*        m_MemoryHeap;

	// Static method
};

Inline
UInt32 CManagedObject::AddPointer() 
{
	m_PointerCounter++;
	return m_PointerCounter;
}

Inline
UInt32 CManagedObject::ReleasePointer()
{
	DebugAssertMsg(m_PointerCounter > 0,"CManagedObject::~CManagedObject\nAnormal functionment");
	m_PointerCounter--;
	return m_PointerCounter;
}

Inline
CMemoryHeap* CManagedObject::GetMemoryHeap() const
{
	return m_MemoryHeap;
}

template< class T >
T* CManagedObject::CastTo() const
{
	if( GetTypeInfo().IsKindOf( T::GetStaticTypeInfo() ) )
		return (T*) this;

	return NULL;
}

}

#endif
