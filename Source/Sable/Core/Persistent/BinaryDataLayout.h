#ifndef _SABLE_CORE_PERSISTENT_BINARYDATALAYOUT_
#define _SABLE_CORE_PERSISTENT_BINARYDATALAYOUT_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Persistent/DataLayout.h>
#include <Sable/Core/Collection/Stack.h>

namespace Sable
{

class CIODevice;
class CPersistentArchive;

/** 
\ingroup CorePersistent

Implementation of a binary data layout.
Allow read and write operation.
*/
class CBinaryDataLayout : public CPersistentDataLayout
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CBinaryDataLayout( );
	CBinaryDataLayout( CIODevice& iodevice );
	~CBinaryDataLayout();
	//@}

	/** @name Manipulator*/
	//@{
	Void SetIODevice( CIODevice& iodevice );
    Bool Open( CPersistentArchive& ar );
	Void FlushData( const Bool IsStoring );

	Int16 BeginScope( WString name, Int16 version );
	Bool EndScope( );

	Void Store( UInt64 data, WString type, WString name );
	Void Store( UInt32 data, WString type, WString name );
	Void Store( UInt16 data, WString type, WString name );
	Void Store( UInt8 data, WString type, WString name );
	Void Store( Int64 data, WString type, WString name );
	Void Store( Int32 data, WString type, WString name );
	Void Store( Int16 data, WString type, WString name );
	Void Store( Int8 data, WString type, WString name );
	Void Store( Float32 data, WString type, WString name );
	Void Store( String data, UInt32 s, WString type, WString name );
	Void Store( WString data, UInt32 s, WString type, WString name );
	Void Store( Byte* data, UInt32 s, WString type, WString name );
	Void Store( const CString& data, WString type, WString name );

	Bool Load( UInt64& data, WString type, WString name );
	Bool Load( UInt32& data, WString type, WString name );
	Bool Load( UInt16& data, WString type, WString name );
	Bool Load( UInt8& data, WString type, WString name );
	Bool Load( Int64& data, WString type, WString name );
	Bool Load( Int32& data, WString type, WString name );
	Bool Load( Int16& data, WString type, WString name );
	Bool Load( Int8& data, WString type, WString name );
	Bool Load( Float32& data, WString type, WString name );
	Bool Load( Char* data, UInt32 s, WString type, WString name );
	Bool Load( WChar* data, UInt32 s, WString type, WString name );
	Bool Load( Byte* data, UInt32 s, WString type, WString name ) ;
	Bool Load( CString& data, WString type, WString name );
	//@}

private:

    // DataTypes

    // Methods
    Bool LoadName( WString s );
    Void StoreName( WString s );

    // Attributes
    CPersistentArchive*     m_Archive;
    CIODevice*              m_IODevice;
    CStack<UInt32>          m_ScopeStack;
};

}

#endif