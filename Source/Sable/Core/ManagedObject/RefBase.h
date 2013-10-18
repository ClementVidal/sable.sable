#ifndef _SABLE_CORE_MANAGEDOBJECT_REFBASE_
#define _SABLE_CORE_MANAGEDOBJECT_REFBASE_

#include <Sable/Core/Common/DataTypes.h>

namespace Sable
{

class CPersistentArchive;
class CMemoryHeap;

/** 
\ingroup CoreManagedObject
Smart pointer
*/
class CRefBase
{

public:

	/* @name Constructor/Destructor*/
	//@{
	CRefBase();
	virtual ~CRefBase();
	//@}

	/* @name Operator*/
	//@{
	//@}

	/* @name Manipulator*/
	//@{
    Bool            Serialize( CPersistentArchive& ar, WString name, CMemoryHeap* heap = NULL );
	//@}

protected:

	//Methods
	virtual Void AcquirePointer( const Void* n ) = 0;
	virtual CManagedObject* GetPointer( ) = 0;
	virtual Void SetPointer( CManagedObject* p ) = 0;

	//Attributes

};

}

#endif
