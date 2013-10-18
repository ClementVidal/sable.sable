#ifndef _SABLE_CORE_PERSISTENT_PERSISTENTDATALAYOUT_
#define _SABLE_CORE_PERSISTENT_PERSISTENTDATALAYOUT_

#include <Sable/Core/ManagedObject/Ref.h>

namespace Sable
{

class CPersistentArchive;
class CString;

/** 
\ingroup CorePersistent
Provide the virtual interface which will be in charge of formating the data coming from / to 
the persistent archive.

This class and it's derived version are in charge of reading/writting data to/from files.

*/
class CPersistentDataLayout
{


public:

	/** @name Constructor/Destructor*/
	//@{
	CPersistentDataLayout( );
	virtual ~CPersistentDataLayout();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessor*/
	//@{
	//@}

	/** @name Manipulator*/
	//@{
    virtual Bool Open( CPersistentArchive& ar ) = 0;
	virtual Void FlushData( const Bool IsStoring ) = 0;

	virtual Int16 BeginScope( WString name, Int16 version ) = 0;
	virtual Bool EndScope( ) = 0;

	virtual Void Store( UInt64 data, WString type, WString name ) = 0;
	virtual Void Store( UInt32 data, WString type, WString name ) = 0;
	virtual Void Store( UInt16 data, WString type, WString name ) = 0;
	virtual Void Store( UInt8 data, WString type, WString name ) = 0;
	virtual Void Store( Int64 data, WString type, WString name ) = 0;
	virtual Void Store( Int32 data, WString type, WString name ) = 0;
	virtual Void Store( Int16 data, WString type, WString name ) = 0;
	virtual Void Store( Int8 data, WString type, WString name ) = 0;
	virtual Void Store( Float32 data, WString type, WString name ) = 0;
	virtual Void Store( String data, UInt32 s, WString type, WString name ) = 0;
	virtual Void Store( WString data, UInt32 s, WString type, WString name ) = 0;
	virtual Void Store( Byte* data, UInt32 s, WString type, WString name ) = 0;
	virtual Void Store( const CString& s, WString type, WString name ) = 0;

	virtual Bool Load( UInt64& data, WString type, WString name ) = 0;
	virtual Bool Load( UInt32& data, WString type, WString name ) = 0;
	virtual Bool Load( UInt16& data, WString type, WString name ) = 0;
	virtual Bool Load( UInt8& data, WString type, WString name ) = 0;
	virtual Bool Load( Int64& data, WString type, WString name ) = 0;
	virtual Bool Load( Int32& data, WString type, WString name ) = 0;
	virtual Bool Load( Int16& data, WString type, WString name ) = 0;
	virtual Bool Load( Int8& data, WString type, WString name ) = 0;
	virtual Bool Load( Float32& data, WString type, WString name ) = 0;
	virtual Bool Load( Char* data, UInt32 s, WString type, WString name ) = 0;
	virtual Bool Load( WChar* data, UInt32 s, WString type, WString name ) = 0;
	virtual Bool Load( Byte* data, UInt32 s, WString type, WString name ) = 0;
	virtual Bool Load( CString& s, WString type, WString name ) = 0;
	//@}

private:

	// Attributes

};

}

#endif