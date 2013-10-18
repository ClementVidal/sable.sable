#include <Sable/Core/Bank/Bank.h>

#include <Sable/Core/Persistent/BinaryDataLayout.h>

IMPLEMENT_MANAGED_CLASS1( Sable, CBank, CPersistentArchive )

using namespace Sable;

CBank::SHeader::SHeader()
{
    FourCC[0] = 'B';
    FourCC[1] = 'A';
    FourCC[2] = 'N';
    FourCC[3] = 'K';

    Version = 0;
}

CBank::CBank( )
{
	SetMemoryHeap( NULL );
	m_Version = 0;
	m_ObjectCount = 0;
}

CBank::~CBank()
{
}

Void CBank::SetMemoryHeap( CMemoryHeap* m )
{
	m_AllocHeap = m;
}

Bool CBank::IsHeaderValid( const SHeader& h ) const
{
    if( ( h.FourCC[0] == 'B') && ( h.FourCC[1] == 'A') && ( h.FourCC[2] == 'N') && ( h.FourCC[3] == 'K') )
        return TRUE;

    return FALSE;
}

Void CBank::SetLibrary( CBankLibrary* lib )
{
	m_Archive.SetLibrary( lib );
}

Void CBank::SetFilePath( const CFilePath& filePath )
{
	m_Version = 0;
	m_FilePath = filePath;
	m_FilePath.GetName( m_Name, 64 );
}

/**
Return the name of the bank.
The name is automaticly taken from the name of the file used to load the bank.
*/
String CBank::GetName() const
{
    return m_Name;
}

HashValue CBank::GetId() const
{
	return StringGetHashCode( GetName() );
}


Bool CBank::Open( EAccesMode mode )
{
	if( mode == nAccesMode_Read )
	{
		SHeader header;

		Clear();

		if( !m_File.Open( m_FilePath, nAccesMode_Read ) )
		{
			DebugLogWarning( "CBank::Serialize - Failed to open: %s", m_FilePath.GetPath() );
			return FALSE;
		}

		m_File.Read( &header, sizeof( SHeader ) );
		if( !IsHeaderValid( header ) )
		{
			DebugLogWarning( "CBank::Serialize - Invalid file format: %s", m_FilePath.GetPath() );
			return FALSE;
		}

		m_Version = header.Version;

		m_DataLayout.SetIODevice( m_File );
		if(! m_Archive.Open( m_DataLayout, nAccesMode_Read ) )
			return FALSE;
	}
	else
	{
		SHeader header;

		// Increase version at save time
		m_Version++;
		header.Version = m_Version;

		if( ! m_File.Open( m_FilePath, nAccesMode_Write ) )
			return FALSE;
		m_File.Write( &header, sizeof( SHeader ) ); 

		m_DataLayout.SetIODevice( m_File );
		if( !m_Archive.Open( m_DataLayout, nAccesMode_Write ) )
			return FALSE;
	}

	return TRUE;
}

/**
Create a bank:
- if mode is set to nAccesMode_Read, this method will parse the header and table of content of the bank
specified by filePath.
- If mode is set to nAccesMode_Write, a new bank is created

\return FALSE if an invalid accesMode is specified, or if m_File does not exist or is not a bank m_File.
*/
Bool CBank::Load( )
{
    if( m_Archive.GetAccesMode() != nAccesMode_Read )
		return FALSE;

    InternalSerialize( m_Archive );
    m_Archive.FlushData();

    return TRUE;
}

Bool CBank::Save( )
{
	if( m_Archive.GetAccesMode() != nAccesMode_Write )
		return FALSE;

	InternalSerialize( m_Archive );
	m_Archive.FlushData();

	return TRUE;
}
/**
This will serialize the whole object table of the bank
*/
Bool CBank::InternalSerialize( CPersistentArchive& ar )
{
    UInt32 i;
    Int16 version = 0;
    Char buff[64];
    ObjectTable::Iterator it;

    if( ar.BeginScope( WT("Bank"), version ) == version )
    {
        ar.Serialize( m_ObjectCount, WT("ObjectCount" ) );

        if( ar.IsStoring() )
        {
            ForEachItem( it, m_ObjectTable )
            {
				ObjectList::Iterator itObj;

				ForEachItem( itObj, *it )
				{
                    if( ar.BeginScope( WT("Entry"), version ) == version )
                    {
					    // serialize ref 
					    StringCopy( it.GetKey(), buff, 64 );

						ar.Serialize( buff, 64, WT("Name") );
					    ar.Serialize( (*itObj), WT("Object"), NULL );

                        ar.EndScope();
                    }

				}
            }
        }
        else
        {
            for( i=0;i<m_ObjectCount;i++ )
            {   
                CRef<CManagedObject> p;
                if( ar.BeginScope( WT("Entry"), version ) == version )
                {
                    ar.Serialize( buff, 64, WT("Name") );
                    ar.Serialize( p, WT("Object"), m_AllocHeap );
                    ar.EndScope();

                    if( m_ObjectTable.HasItem( buff ) == FALSE )
                        m_ObjectTable.AddItem( buff );

                    ObjectList& list = m_ObjectTable.GetItem( buff );

                    list.AddItemAtEnd( p );
                }
            }
        }
    }

	return TRUE;
}

CBankArchive& CBank::GetArchive() 
{
	return m_Archive;
}

/**
Add an object prototype to the bank.

Use this method to setup a bank before serializing it to disk
*/
Bool CBank::AddObject( CManagedObject& obj, String name )
{
	if( m_ObjectTable.HasItem( name ) == FALSE )
		m_ObjectTable.AddItem( name );

	ObjectList& list = m_ObjectTable.GetItem( name );

    list.AddItemAtEnd( &obj );
	m_ObjectCount++;

	return TRUE;
}

Bool CBank::HasObject( CManagedObject* obj ) const
{
	ObjectList::Iterator itList;
	ObjectTable::Iterator itTable;

	ForEachItem( itTable, m_ObjectTable )
	{
		ForEachItem( itList, *itTable )
		{
			if( *itList == obj )
				return TRUE;
		}
	}

	return FALSE;
}

Void CBank::Clear()
{
	m_ObjectCount = 0;
	m_ObjectTable.ClearAllItems();
	m_Archive.Reset();
}