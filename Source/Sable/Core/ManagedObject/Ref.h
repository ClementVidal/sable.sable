#ifndef _SABLE_CORE_MANAGEDOBJECT_REF_
#define _SABLE_CORE_MANAGEDOBJECT_REF_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/ManagedObject.h>
#include <Sable/Core/ManagedObject/RefBase.h>

namespace Sable
{

class CPersistentArchive;

/** 
\ingroup CoreManagedObject
Smart pointer
*/
template < class DataType >
class CRef : public CRefBase
{

public:

	/* @name Constructor/Destructor*/
	//@{
	CRef();
	~CRef();
	CRef( const CRef<DataType>& sp );
	CRef( const DataType* sp );
	//@}

	/* @name Operator*/
	//@{
	CRef<DataType>&     operator = ( const DataType* n );
	CRef<DataType>&     operator = ( const CRef<DataType>& sp );	
	DataType&           operator * () const;
	DataType*           operator-> () const ;
	operator DataType* () const ;
	//@}

	/* @name Manipulator*/
	//@{
	Bool            GetIsNull() const;
	Bool            GetIsValid() const;
	Void            SetNull();
	//@}

protected:

	//Methods
	Void ReleasePointer();
	Void AcquirePointer( const Void* n );
	CManagedObject* GetPointer( );
	Void SetPointer( CManagedObject* p );

	//Attributes
    DataType*	m_Pointer;

};

#include <Sable/Core/ManagedObject/Ref.hpp>


}

#endif
