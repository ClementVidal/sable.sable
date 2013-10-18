#ifndef _CORE_MANAGEDOBJECT_TYPEINFO_
#define _CORE_MANAGEDOBJECT_TYPEINFO_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/String/Primitives.h>

#define TYPEINFO_MAX_SUBTYPE 64
#define TYPEINFO_CLASSNAME_LENGTH 64

namespace Sable
{

class CMemoryHeap;
class CManagedObject;

/** 
\ingroup CoreManagedObject
Types Informations
Identify the class type at runtime.
Type Information is available only if the owner class is metadeclared
*/
class CTypeInfo
{

public:

	/** @name Types*/
	//@{
    static const CTypeInfo  NullType;	
    typedef CManagedObject* (*Allocator)( CMemoryHeap* heap );
	//@}

    /** @name Constructor/Destructor*/
    //@{
    CTypeInfo(  String typeName, 
				String nameSpace, 
                const CTypeInfo* bb[],
				const Int8 basetypecount,
				const UInt32 byteSize, 
                const Allocator alloc = NULL );

    ~CTypeInfo();
    //@}

	/** @name Operator*/
	//@{
	Bool operator==( const CTypeInfo & id ) const;
	Bool operator!=( const CTypeInfo & id ) const;
	//@}

    /** @name Accesors*/
    //@{
    Bool        HasAllocator() const;
	UInt32		GetSize() const;
	UInt32		GetMaxSizeOfDerivedClass() const;
    //@}

    /** @name Manipulator*/
    //@{
    CManagedObject*         CreateObject( CMemoryHeap* heap ) const;

	String					GetNameSpace() const;
	String					GetTypeName() const;
	String					GetFullTypeName() const;
	const CTypeInfo&        GetDerivedClass( String fullTypeName ) const;
    const CTypeInfo&        GetDerivedClass( const UInt8 nb ) const;
    UInt8                   GetDerivedClassCount() const;
    const CTypeInfo&        GetBaseClass( const UInt8 nb ) const;	
    UInt8		            GetBaseClassCount() const;	
    Bool 	                IsA( const CTypeInfo & info ) const;		
    Bool 	                IsA( String fullTypeName ) const;
    Bool                    IsKindOf( const CTypeInfo & info ) const;	
    Bool                    IsKindOf( String type ) const;	
    //@}

private:

    //Methods
    Void 					AddSubType( const CTypeInfo & info );
    Bool					HasBaseOf( const CTypeInfo & info ) const;
    Bool					HasBaseOf( String type ) const;
	const CTypeInfo*		GetDerivedClassRecursive( String fullTypeName ) const ;

    //Attributes
    const CTypeInfo*			m_SubType[TYPEINFO_MAX_SUBTYPE];		
    const CTypeInfo**			m_BaseType;	
    UInt8						m_SubTypeCount;	
	UInt8						m_BaseTypeCount;
	String 					    m_TypeName; 
	String 					    m_NameSpace; 
	Char 					    m_FullTypeName[TYPEINFO_CLASSNAME_LENGTH]; 
	UInt16						m_TypeID;
	UInt32						m_Size;
    Allocator                   m_Allocator;

    //Static Attributes
    static const CTypeInfo**	m_DummyBaseClass;
    static UInt16				m_TypeIDCount;

};

/**
Check if two type informations are exactly equivalent
*/ 
Inline
Bool CTypeInfo::IsA( const CTypeInfo & info ) const
{
	return m_TypeID == info.m_TypeID;
}

/**
Check if two type informations are exactly equivalent
*/ 
Inline
Bool CTypeInfo::IsA( String fullTypeName ) const			
{  										
	return ( Sable::StringCompare( fullTypeName, (String)m_FullTypeName ) == 0 );
}

/** 
Get a string representing the type name of this class
*/ 
Inline
String CTypeInfo::GetTypeName() const
{
	return (String) m_TypeName;
}

/** 
Return the fullType name of this type, i.e: the name of the class prefixed with it's namespace
*/ 
Inline
String CTypeInfo::GetFullTypeName() const
{
	return (String) m_FullTypeName;
}

/** 
Get a string representing the namespace of this class
*/ 
Inline
String CTypeInfo::GetNameSpace() const
{
	return (String) m_NameSpace;
}

Inline
Bool CTypeInfo::operator==( const CTypeInfo & id ) const
{
	return IsA( id ); 
}

Inline
Bool CTypeInfo::operator!=( const CTypeInfo & id) const
{
	return ! IsA( id );
}

/** 
Get the Sub class count of this class
*/
Inline
UInt8 CTypeInfo::GetDerivedClassCount() const				
{
	return m_SubTypeCount;
} 

/** 
Get the base class count of this class
*/
Inline
UInt8 CTypeInfo::GetBaseClassCount() const				
{
	return m_BaseTypeCount;
} 

/** Get the base class type information of this class
@param nb the index of the base class in the hierarchie
*/
Inline
const CTypeInfo& CTypeInfo::GetBaseClass( const UInt8 nb) const
{
	if(nb >= 0 && nb < m_BaseTypeCount)
	{
		return *m_BaseType[nb];
	}

	return  NullType;
}

Inline
Bool CTypeInfo::HasBaseOf( const CTypeInfo & info ) const
{  
	for(UInt8 i = 0; i < m_BaseTypeCount ; i++)
	{
		if (info.IsA( *m_BaseType[ i ] ) || m_BaseType[ i ]->HasBaseOf( info ) ) 
			return TRUE;				
	}

	return FALSE;									
}

Inline
Bool CTypeInfo::HasBaseOf( String type ) const
{  
	for(UInt8 i = 0; i < m_BaseTypeCount ; i++)
	{
		if ( ( Sable::StringCompare( type, m_BaseType[ i ]->GetFullTypeName() ) == 0 ) ||
            m_BaseType[ i ]->HasBaseOf( type ) ) 
			return TRUE;				
	}

	return FALSE;									
}

/** Get the Sub class type information of this class
@param nb the index of the sub class in the hierarchie
*/ 
Inline
const CTypeInfo& CTypeInfo::GetDerivedClass( const UInt8 nb ) const	
{
	if(nb>=0 && nb<m_SubTypeCount)
	{
		return *m_SubType[nb];
	}

	return  NullType;
} 

/** Check if the CTypeInfo argument represent a base class of 
this class
*/ 
Inline
Bool CTypeInfo::IsKindOf( const CTypeInfo & info ) const
{  
	return IsA( info ) || this->HasBaseOf( info ); 
}

Inline
Bool CTypeInfo::IsKindOf( String type ) const
{
	return IsA( type ) || this->HasBaseOf( type ); 
}

}

#endif
