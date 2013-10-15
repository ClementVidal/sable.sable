#ifndef _SABLE_CORE_BANK_ARCHIVE_
#define _SABLE_CORE_BANK_ARCHIVE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Persistent\Archive.h>

namespace Sable
{

class CBank;
class CPersistentArchive;
class CBankLibrary;

/** 
\ingroup CoreBank
Bank interface.

Allow to load bank file and to serialize object in/out .

*/
class CBankArchive : public CPersistentArchive
{

public:

	CBankArchive( );

	Void				SetLibrary( CBankLibrary* lib );
	Int64				AcquirePointerID( CManagedObject* obj );
	CManagedObject*		GetObjectFromID( Int64 id ) const;
	Int64				GetIDFromObject( CManagedObject* obj );
	Void				AddObject( CManagedObject* obj, Int64 id );
	Void				AddObjectWithoutLibraryLookup( CManagedObject* obj, Int64 id );

private:

	// Attributes
	CBankLibrary* m_Library;
};


}

#endif
