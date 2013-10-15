#ifndef _SABLE_CORE_BANK_LIBRARY_
#define _SABLE_CORE_BANK_LIBRARY_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CPersistentArchive;
class CManagedObject;

/** 
\ingroup CoreBank
Bank library

*/
class CBankLibrary : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CBankLibrary )

public:

    /** @name Types*/
    //@{
    //@}

    /** @name Constructor/Destructor*/
    //@{
	CBankLibrary( );
    ~CBankLibrary();
    //@}

    /** @name Operator*/
    //@{
    //@}

    /** @name Accessor*/
    //@{
	CBank*	GetBank( String name ) const;
	CBank*	GetBank( HashValue id ) const;
	CBank*	FindBank( CManagedObject* obj ) const;
	CBank*	FindBank( HashValue bankId ) const;
    //@}

    /** @name Manipulator*/
    //@{
	Bool	AddBank( const CFilePath& path );
	Bool	Load();
	Bool	Save();
	Int64	AcquirePointerID( CManagedObject* obj ); 
	Int64	GetIDFromObject( CManagedObject* obj ) const;
	CManagedObject* GetObjectFromID( Int64 id ) const;
	Void	AddObject( CManagedObject* obj, Int64 id );
    //@}

private:

    // Friend ship

    // DataTypes
	typedef CList< CRef<CBank> >	BankTable;

    // Methods

    // Attributes
	BankTable		m_BankTable;
	UInt32			m_NextFreeId;
	CMap< Int64, CManagedObject* >          m_IDToObject;
	CMap< CManagedObject*, Int64 >          m_ObjectToID;
	CBank*			m_CurrentBank;
	Bool			m_IsStoring;

    // Static Methods

    // Static Attributes
};

}

#endif
