#include <Sable/Core/Persistent/BinaryDataLayout.h>

#include <Sable/Core/Common/IODevice.h>

using namespace Sable;

/**
Construct a binary data layout using a given file.

\warning The information parsing will start at current file pointer position of this file.
i.e: File pointer is not moved to beginning of file ( fseek( 0 ) ) before read start.
This allow data to be stored anywhere in an heterogeneous file.
*/
CBinaryDataLayout::CBinaryDataLayout( CIODevice& iodevice ):
    CPersistentDataLayout(),
    m_IODevice( &iodevice )
{
    m_ScopeStack.SetCapacity( 128 );
}

CBinaryDataLayout::CBinaryDataLayout( ):
	CPersistentDataLayout(),
	m_IODevice( NULL )
{
	m_ScopeStack.SetCapacity( 128 );
}

CBinaryDataLayout::~CBinaryDataLayout()
{
}

Void CBinaryDataLayout::SetIODevice( CIODevice& iodevice )
{
	m_IODevice = &iodevice;
}

/**
Open the binary data layout.
This function is called automaticly by CPersistentArchive.
\return 
    - TRUE if associated file acces mode match archive mode
    - FALSE if both mode missmatch
*/
Bool CBinaryDataLayout::Open( CPersistentArchive& ar )
{
    EAccesMode mode = m_IODevice->GetAccesMode();
    m_Archive = &ar;
    if( ar.IsStoring() )
    {
        if( ( mode == nAccesMode_Write ) || ( mode == nAccesMode_ReadWrite ) )
            return TRUE;
    }
    else if( ar.IsLoading() )
    {
        if( ( mode == nAccesMode_Read ) || ( mode == nAccesMode_ReadWrite ) )
            return TRUE;
    }

    return FALSE;
}

Int16 CBinaryDataLayout::BeginScope( WString name, Int16 version )
{
    struct Data
    {
        HashValue NameHash;
        Int16  Version;
    };

    Data data;

    if( m_Archive->IsStoring() )
    {
        if( version < 0 )
        {
            CoreManager.GetLog().LogError( "CBinaryDataLayout::BeginScope - Invalid version" );
            return -1;
        }

        data.Version = version;
        data.NameHash = StringGetHashCode( name );
        m_IODevice->Write( &data, sizeof( Data ) );
    }
    else
    {
        m_IODevice->Read( &data, sizeof( Data ) );
        

        if( data.NameHash != StringGetHashCode( name ) )
        {
            CoreManager.GetLog().LogError( "CBinaryDataLayout::BeginScope - Begin scope failed" );
            return -1;
        }
    }

    // If version does not match do not push item and return the scope version
    if( data.Version == version )
        m_ScopeStack.PushItem( m_IODevice->GetPosition() );

    return data.Version;
}

Bool CBinaryDataLayout::EndScope( )
{
    struct Data
    {
        UInt16 EndTag;
    };
    const UInt16 endTag = 0xf0f0;

    Data data;

    if( m_Archive->IsStoring() )
    {
        data.EndTag = endTag;
        m_IODevice->Write( &data, sizeof( Data ) );
        m_ScopeStack.PopItem( );
    }
    else
    {
        m_IODevice->Read( &data, sizeof( Data ) );
        m_ScopeStack.PopItem( );

        if( data.EndTag != endTag )
        {
            CoreManager.GetLog().LogError("CBinaryDataLayout::EndScope - End scope mismatch, file corrupted");
            return FALSE;
        }
    }

    return TRUE;
}

Void CBinaryDataLayout::FlushData( const Bool IsStoring )
{
    m_IODevice->Flush();
}

Void CBinaryDataLayout::StoreName( WString s )
{
    HashValue hash = StringGetHashCode( s );
    m_IODevice->Write( &hash, sizeof( HashValue ) );
}

Bool CBinaryDataLayout::LoadName( WString s )
{
	Int32 size = sizeof( HashValue );
    HashValue storedHash;
    HashValue hash = StringGetHashCode( s );
    m_IODevice->Read( &storedHash, size );

	if( storedHash != hash )
	{
		m_IODevice->SetRelativePosition( -size );
		return FALSE;
	}

    return TRUE;
}

Void CBinaryDataLayout::Store( UInt32 data, WString type, WString name )
{
    StoreName( name );
    m_IODevice->Write( &data, sizeof( UInt32 ) );
}

Void CBinaryDataLayout::Store( Int64 data, WString type, WString name )
{
	StoreName( name );
	m_IODevice->Write( &data, sizeof( Int64 ) );
}

Void CBinaryDataLayout::Store( UInt64 data, WString type, WString name )
{
	StoreName( name );
	m_IODevice->Write( &data, sizeof( UInt64 ) );
}

Void CBinaryDataLayout::Store( UInt16 data, WString type, WString name )
{
    StoreName( name );
    m_IODevice->Write( &data, sizeof( UInt16 ) );
}

Void CBinaryDataLayout::Store( UInt8 data, WString type, WString name )
{
    StoreName( name );
    m_IODevice->Write( &data, sizeof( UInt8 ) );
}

Void CBinaryDataLayout::Store( Int32 data, WString type, WString name )
{
    StoreName( name );
    m_IODevice->Write( &data, sizeof( Int32 ) );
}

Void CBinaryDataLayout::Store( Int16 data, WString type, WString name )
{
    StoreName( name );
    m_IODevice->Write( &data, sizeof( Int16 ) );
}

Void CBinaryDataLayout::Store( Int8 data, WString type, WString name )
{
    StoreName( name );
    m_IODevice->Write( &data, sizeof( Int8 ) );
}

Void CBinaryDataLayout::Store( Float32 data, WString type, WString name )
{
    StoreName( name );
    m_IODevice->Write( &data, sizeof( Float32 ) );
}

Void CBinaryDataLayout::Store( String data, UInt32 s, WString type, WString name )
{
    UInt32 len = StringGetLength( data );
    StoreName( name );
    m_IODevice->Write( &len, sizeof( UInt32 ) );
    m_IODevice->Write( (Void*) data, len * sizeof( Char ) );
}

Void CBinaryDataLayout::Store( WString data, UInt32 s, WString type, WString name )
{
    UInt32 len = StringGetLength( data );
    StoreName( name );
    m_IODevice->Write( &len, sizeof( UInt32 ) );
    m_IODevice->Write( (Void*) data, len * sizeof( WChar ) );
}

Void CBinaryDataLayout::Store( Byte* data, UInt32 s, WString type, WString name )
{
	StoreName( name );
	m_IODevice->Write( &s, sizeof( UInt32 ) );
	m_IODevice->Write( (Void*) data, s );
}

Void CBinaryDataLayout::Store( const CString& data, WString type, WString name )
{
	UInt32 len = data.GetLength();
	StoreName( name );
	m_IODevice->Write( &len, sizeof( UInt32 ) );
	m_IODevice->Write( (Void*) data.GetBuffer(), len );
}

Bool CBinaryDataLayout::Load( UInt32& data, WString type, WString name )
{
    if( !LoadName( name ) )
        return FALSE;
    m_IODevice->Read( &data, sizeof( UInt32 ) );
    return TRUE;
}

Bool CBinaryDataLayout::Load( Int64& data, WString type, WString name )
{
	if( !LoadName( name ) )
		return FALSE;
	m_IODevice->Read( &data, sizeof( Int64 ) );
	return TRUE;
}

Bool CBinaryDataLayout::Load( UInt64& data, WString type, WString name )
{
	if( !LoadName( name ) )
		return FALSE;
	m_IODevice->Read( &data, sizeof( UInt64 ) );
	return TRUE;
}

Bool CBinaryDataLayout::Load( UInt16& data, WString type, WString name )
{
    if( !LoadName( name ) )
        return FALSE;
    m_IODevice->Read( &data, sizeof( UInt16 ) );
    return TRUE;
}

Bool CBinaryDataLayout::Load( UInt8& data, WString type, WString name )
{
    if( !LoadName( name ) )
        return FALSE;
    m_IODevice->Read( &data, sizeof( UInt8 ) );
    return TRUE;
}

Bool CBinaryDataLayout::Load( Int32& data, WString type, WString name )
{
    if( !LoadName( name ) )
        return FALSE;
    m_IODevice->Read( &data, sizeof( Int32 ) );
    return TRUE;
}

Bool CBinaryDataLayout::Load( Int16& data, WString type, WString name )
{
    if( !LoadName( name ) )
        return FALSE;
    m_IODevice->Read( &data, sizeof( Int16 ) );
    return TRUE;
}

Bool CBinaryDataLayout::Load( Int8& data, WString type, WString name )
{
    if( !LoadName( name ) )
        return FALSE;
    m_IODevice->Read( &data, sizeof( Int8 ) );
    return TRUE;
}

Bool CBinaryDataLayout::Load( Float32& data, WString type, WString name )
{
    if( !LoadName( name ) )
        return FALSE;
    m_IODevice->Read( &data, sizeof( Float32 ) );
    return TRUE;
}

Bool CBinaryDataLayout::Load( WChar* data, UInt32 s, WString type, WString name )
{
    UInt32 len;
    if( !LoadName( name ) )
        return FALSE;

    m_IODevice->Read( &len, sizeof( UInt32 ) );
    if( len < s )
    {
        m_IODevice->Read( (Void*) data, len * sizeof( WChar ) );
        data[len] = WT('\0');
        return TRUE;
    }
    return FALSE;
}

Bool CBinaryDataLayout::Load( CString& data, WString type, WString name )
{
	UInt32 len;
	if( !LoadName( name ) )
		return FALSE;

	m_IODevice->Read( &len, sizeof( UInt32 ) );
	data.AllocateBuffer( len );
	m_IODevice->Read( (Void*) data.GetBuffer(), len );

	return TRUE;
}

Bool CBinaryDataLayout::Load( Char* data, UInt32 s, WString type, WString name )
{
    UInt32 len;
    if( !LoadName( name ) )
        return FALSE;

    m_IODevice->Read( &len, sizeof( UInt32 ) );
    if( len < s )
    {
        m_IODevice->Read( (Void*) data, len * sizeof( Char ) );
        data[len] = '\0';
        return TRUE;
    }
    return FALSE;
}


Bool CBinaryDataLayout::Load( Byte* data, UInt32 s, WString type, WString name )
{
	UInt32 len;
	if( !LoadName( name ) )
		return FALSE;

	m_IODevice->Read( &len, sizeof( UInt32 ) );
	if( s == len )
	{
		m_IODevice->Read( (Void*) data, s );
		return TRUE;
	}
	return FALSE;
}
