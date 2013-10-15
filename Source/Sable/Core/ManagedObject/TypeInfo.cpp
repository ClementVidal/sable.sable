#include <Sable\Core\ManagedObject\TypeInfo.h>

#include <Sable\Core\ManagedObject\ManagedObject.h>
#include <Sable\Setup.h>

using namespace Sable;

const CTypeInfo** CTypeInfo::m_DummyBaseClass = { 0 };
const CTypeInfo CTypeInfo::NullType( "NULL", "NULL", CTypeInfo::m_DummyBaseClass, 0, 0);
UInt16 CTypeInfo::m_TypeIDCount = 0;


CTypeInfo::CTypeInfo( String typeName, 
		String nameSpace, 
        const CTypeInfo* bb[],
        const Int8 basetypecount,
		const UInt32 byteSize,
		const Allocator alloc ) :
	m_TypeName( typeName ),
	m_NameSpace( nameSpace )
{
	StringAppend( nameSpace, "::", m_FullTypeName, TYPEINFO_CLASSNAME_LENGTH);
	StringAppend( m_FullTypeName, typeName, m_FullTypeName, TYPEINFO_CLASSNAME_LENGTH);

    m_BaseType = bb;

    m_Allocator = alloc;

    for( Int8 i = 0; i < basetypecount; i++ )
    {
        ((CTypeInfo**)m_BaseType)[i]->AddSubType(*this);
    }

    m_BaseTypeCount = basetypecount;
    m_TypeID = ++m_TypeIDCount;
	m_Size = byteSize;
}

CTypeInfo::~CTypeInfo()
{
}

Bool CTypeInfo::HasAllocator() const
{
    return m_Allocator != NULL;
}

UInt32 CTypeInfo::GetSize() const
{
	return m_Size;
}

UInt32 CTypeInfo::GetMaxSizeOfDerivedClass() const
{
	UInt32 i,s = GetSize();
	for(i=0;i<m_SubTypeCount;i++)
	{
		s = MathMax( s, m_SubType[i]->GetMaxSizeOfDerivedClass() );
	}

	return s;
}

/**
Return the type information of a specific type, given it's name
*/
const CTypeInfo& CTypeInfo::GetDerivedClass( String fullTypeName ) const 
{
    const CTypeInfo* t = GetDerivedClassRecursive( fullTypeName );
    if( t )
        return *t;

    return NullType;
} 

CManagedObject* CTypeInfo::CreateObject( CMemoryHeap* heap ) const
{
    if( m_Allocator )
    {
        return m_Allocator( heap );
    }

    return NULL;
}

const CTypeInfo* CTypeInfo::GetDerivedClassRecursive( String fullTypeName ) const
{
    Index subTypeIndex;

    if( StringCompare( (String)m_FullTypeName, fullTypeName ) == 0 )
    {
        return this;
    }
    else
    {
        for( subTypeIndex = 0; subTypeIndex < m_SubTypeCount; subTypeIndex++ )
        {
            const CTypeInfo* t = m_SubType[ subTypeIndex ]->GetDerivedClassRecursive( fullTypeName );

            if( t )
                return t;
        }
    }

    return NULL;
}

 
Void CTypeInfo::AddSubType( const CTypeInfo & info )	
{
    DebugAssert( m_SubTypeCount + 1 < TYPEINFO_MAX_SUBTYPE );
    m_SubType[m_SubTypeCount] = &info;
    m_SubTypeCount++;
}
 