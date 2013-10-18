#ifndef _CORE_MANAGEDOBJECT_MACRO_
#define _CORE_MANAGEDOBJECT_MACRO_

/** @file Type.h
Define standard macro for Meta typing*/

#include <Sable/Setup.h>
#include <Sable/Core/ManagedObject/TypeInfo.h>
#include <Sable/Core/Memory/Manager.h>
#include <Sable/Core/Memory/Primitives.h>

namespace Sable
{

/**
User new operator
*/
#ifdef SETUP_MEMORY_TRACKER

#define NEWOBJ( type, arg ) ((type*)((Sable::CManagedObject*) new(__FILE__, __LINE__) type arg)->OnAllocate( NULL ))
#define NEWOBJ_EX( heap, type, arg ) ((type*)((Sable::CManagedObject*) new(heap, __FILE__, __LINE__) type arg)->OnAllocate( heap ))

#else

#define NEWOBJ( type, arg ) ((type*)((Sable::CManagedObject*) new type arg)->OnAllocate( NULL ))
#define NEWOBJ_EX( heap, type, arg ) ((type*)((Sable::CManagedObject*) new(heap) type arg)->OnAllocate( heap ))

#endif

/**
Managed Class definition/implementation macro
*/
#define DEFINE_MANAGED_CLASS( classType ) \
    DEFINE_MANAGED_CLASS_TYPE_INFO( classType ) \

#define IMPLEMENT_MANAGED_CLASS( nameSpace, classType ) \
	IMPLEMENT_MANAGED_CLASS_TYPE_INFO( nameSpace, classType, NULL ) \

#define IMPLEMENT_MANAGED_CLASS1( nameSpace, classType, BaseClass1 ) \
	IMPLEMENT_MANAGED_CLASS_TYPE_INFO1( nameSpace, classType, BaseClass1, NULL ) \

#define IMPLEMENT_MANAGED_CLASS_ALLOC( nameSpace, classType ) \
	DEFINE_MANAGED_CLASS_ALLOCATOR( nameSpace, classType ) \
    IMPLEMENT_MANAGED_CLASS_TYPE_INFO( nameSpace, classType, Alloc_##nameSpace##_##classType ) \

#define IMPLEMENT_MANAGED_CLASS1_ALLOC( nameSpace, classType, BaseClass1 ) \
	DEFINE_MANAGED_CLASS_ALLOCATOR( nameSpace, classType ) \
    IMPLEMENT_MANAGED_CLASS_TYPE_INFO1( nameSpace, classType, BaseClass1, Alloc_##nameSpace##_##classType ) \

/**
Managed Class Type info macro
*/
#define DEFINE_MANAGED_CLASS_ALLOCATOR( nameSpace, classType ) \
    Sable::CManagedObject* Alloc_##nameSpace##_##classType( Sable::CMemoryHeap* heap ) \
    { \
	return NEWOBJ_EX(  heap , nameSpace::classType, ( ) ); \
    } \

#define DEFINE_MANAGED_CLASS_TYPE_INFO( classtype ) \
protected: \
    static  const  Sable::CTypeInfo m_TypeInfo; \
public: \
	virtual const Sable::CTypeInfo& GetTypeInfo() const { return m_TypeInfo; } \
	static  const Sable::CTypeInfo& GetStaticTypeInfo() { return m_TypeInfo; } \

#define IMPLEMENT_MANAGED_CLASS_TYPE_INFO( nameSpace, classType, alloc ) \
    namespace nameSpace \
    { \
	static const Sable::CTypeInfo* TypeInfo_##classType [] = { NULL }; \
	const Sable::CTypeInfo classType::m_TypeInfo( #classType, #nameSpace, TypeInfo_##classType, 0, sizeof( classType ), alloc ); \
    } \

#define IMPLEMENT_MANAGED_CLASS_TYPE_INFO1( nameSpace, classType, BaseClass1, alloc ) \
    namespace nameSpace \
    { \
    static const Sable::CTypeInfo* TypeInfo_##classType [] = { &BaseClass1::GetStaticTypeInfo() }; \
	const Sable::CTypeInfo classType::m_TypeInfo( #classType, #nameSpace, TypeInfo_##classType, 1, sizeof( classType ), alloc ); \
    } \

#define SafeCastRef( pointer, type ) \
	( (pointer) ? ( (pointer)->GetTypeInfo().IsKindOf( type::GetStaticTypeInfo() ) ? ( (type*)&(*pointer) ) : (type*)NULL ):NULL )

}

#endif
