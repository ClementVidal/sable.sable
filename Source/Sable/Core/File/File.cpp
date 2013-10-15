#include <Sable\Core\File\File.h>

#include <Sable\Core\File\System.h>

#include <stdarg.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CFile );

/**
Construct a file object without doing anything else
*/
CFile::CFile() :
    m_Impl( *this )
{
}

/**
Construct a file object and try to open.
\param filePath file to open
\param acces Acces right see CFile::Open
*/
CFile::CFile( const CFilePath& fileName, EAccesMode acces ) :
    m_Impl( *this )
{
    Open( fileName, acces );
}

CFile::~CFile()
{
	Close();
}

/**
Close the file
*/
Void CFile::Close()
{
    Flush();

    m_Impl.Close();

    CIODevice::Close();
}

/**
Flush buffer ensure the user that all data stored in any kind of temporary place is
flushed down to the hard drive.

This method is automaticly called when Object is detroyed
*/
Void CFile::Flush()
{
    m_Impl.Flush();
}

/**
Open a file with a given access.

\param filePath file to the path
\param acces acces mode used has fallow:
    
    - nAccesMode_Read : 
    Open a file for reading. The file must exist.

    - nAccesMode_Write : 
    Create an empty file for writing. 
    If a file with the same name already exists its content is erased 
    and the file is treated as a new empty file. 

    - nAccesMode_ReadWrite:
    Create an empty file for both reading and writing. 
    If a file with the same name already exists its content 
    is erased and the file is treated as a new empty file

\return FALSE if open fail
*/
Bool CFile::Open( const CFilePath& fileName, EAccesMode acces )
{
    Close();

    if( !m_Impl.Open( fileName, acces ) )
    {
        return FALSE;
    }

    m_Path = fileName;

    return CIODevice::Open( acces );
}

/**
Read size byte into the file.
\param data Readed bytes
\param size Byte count
*/
Bool CFile::Read( Void* data, UInt32 size )
{
    return m_Impl.Read( data, size );
}

Bool CFile::GetIsEndOfFile() const
{
    return m_Impl.IsEndOfFile();
}

Bool CFile::ReadAll( CArray<Byte>& data )
{
    data.SetItemCount( GetSize() );
    return Read( data.GetBuffer(), data.GetItemCount() );
}

/**
Write byte into the file.
\param data Written bytes
\param size Byte count
*/
Bool CFile::Write( Void* data, UInt32 size)
{
    return m_Impl.Write( data, size );
}


UInt32	CFile::GetPosition() const
{
    return m_Impl.GetPosition();
}

Bool	CFile::SetRelativePosition( Int32 newposition )
{
    return m_Impl.SetRelativePosition( newposition );
}

Bool	CFile::SetPosition( UInt32 newposition )
{
    return m_Impl.SetPosition( newposition );
}

UInt32	CFile::GetSize() const
{
	return m_Impl.GetSize();
}

String CFile::GetFilePath() const
{ 
    return m_Path.GetPath();
}

Bool	CFile::IsOpen()  const 
{
	return m_Impl.IsOpen();
}
