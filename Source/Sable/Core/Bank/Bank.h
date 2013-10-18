#ifndef _SABLE_CORE_BANK_BANK_
#define _SABLE_CORE_BANK_BANK_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/Ref.h>
#include <Sable/Core/Collection/List.h>
#include <Sable/Core/Collection/Map.h>
#include <Sable/Core/File/File.h>
#include <Sable/Core/String/StaticString.h>
#include <Sable/Core/Bank/Archive.h>
#include <Sable/Core/Persistent/BinaryDataLayout.h>

namespace Sable
{

class CManagedObject;
class CBankLibrary;

/** 
\ingroup CoreBank
Bank interface.

Allow to load bank file and to serialize object in/out .

*/
class CBank : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CBank )

public:

    /** @name Types*/
    //@{
    struct SHeader
    {
        SHeader();
        Char    FourCC[4];
        UInt32  Version;
    };
    //@}

    /** @name Constructor/Destructor*/
    //@{
	CBank( );
    ~CBank();
    //@}

    /** @name Operator*/
    //@{
	Void SetFilePath( const CFilePath& filePath );
	Void SetLibrary( CBankLibrary* lib );
	Void SetMemoryHeap( CMemoryHeap* m );
    //@}

    /** @name Accessor*/
    //@{
    template< typename ObjType >
	ObjType*		GetObjectByName( String name ) const;
    String          GetName() const;
	HashValue		GetId() const;
	Bool			HasObject( CManagedObject* obj ) const;
	CBankArchive&	GetArchive() ;
    //@}

    /** @name Manipulator*/
    //@{
	Bool			Open( EAccesMode mode );
	Bool			Load( );
	Bool			Save( );
	Void			Clear();
    Bool            AddObject( CManagedObject& obj, String name );
    //@}

private:

    // Friend ship

    // DataTypes
	typedef CList< CRef<CManagedObject> >				ObjectList;
    typedef CMap< CStringIdentifier, ObjectList >		ObjectTable;

    // Methods
	Bool    IsHeaderValid( const SHeader& h ) const;
	Bool	InternalSerialize( CPersistentArchive& ar );

    //Attributes
	UInt32			m_ObjectCount;
    UInt32          m_Version;
    CFile           m_File;
    CFilePath       m_FilePath;
    Char            m_Name[64];
    ObjectTable     m_ObjectTable;
	CMemoryHeap*	m_AllocHeap;

	CBinaryDataLayout	m_DataLayout;
	CBankArchive		m_Archive;


    //Static Methods

    //Static Attributes
};

template< typename ObjType >
ObjType* CBank::GetObjectByName( String objName ) const
{
	if( m_ObjectTable.HasItem( objName ) )
	{
		ObjectList::Iterator it;
		const ObjectList& objList = m_ObjectTable.GetItem( objName );

		ForEachItem( it, objList )
		{
			if( (*it)->GetTypeInfo().IsKindOf( ObjType::GetStaticTypeInfo() ) )
			{
				CManagedObject& obj = *(*it);
				return (ObjType*)&obj;
			}
		}
	}

	return NULL;
}

}

#endif
