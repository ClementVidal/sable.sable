#include <Sable/Core/File/Impl/Linux/File.h>

#include <Sable/Core/File/FilePath.h>

using namespace Sable;

CImplLinuxFile::CImplLinuxFile( CFile& publicImpl ) :
    CImplStubFile( publicImpl )
{
    m_FileHandle = NULL;
}

CImplLinuxFile::~CImplLinuxFile()
{
}

void CImplLinuxFile::Close()
{
    if (m_FileHandle)
    {
        fflush( (FILE*) m_FileHandle);
        fclose( (FILE*) m_FileHandle);
        m_FileHandle = NULL;
    }
}

void CImplLinuxFile::Flush()
{
    fflush( (FILE*) m_FileHandle);
}

Bool	CImplLinuxFile::Open( const CFilePath& filename, const EAccesMode acces )
{
    Close();

    String fileaccess;

    switch( acces )
    {
        //Open a file for reading. The file must exist.
    case nAccesMode_Read:
        fileaccess = "rb"; 
        break;

    //Create an empty file for writing. 
    //If a file with the same name already exists its content is erased 
    // and the file is treated as a new empty file. 
    case nAccesMode_Write:
        fileaccess = "wb";
        break;
    default:

    // Create an empty file for both reading and writing. 
     // If a file with the same name already exists its content 
        // is erased and the file is treated as a new empty file
		case nAccesMode_ReadWrite:
			fileaccess = "w+b"; // Open for reading & writing if file does not exist create it
			break;

	}

    m_FileHandle = fopen( filename.GetPath(), fileaccess );
	
	if( m_FileHandle == NULL )
	{
		return FALSE;
	}

	return TRUE;
}

Bool CImplLinuxFile::Read( Void* data, const UInt32 size )
{
    UInt32 blockread = 0;
    
    DebugAssert( m_FileHandle );
    
    blockread = (UInt32) fread( data, size, 1, (FILE*) m_FileHandle);

    if( ferror ( (FILE*) m_FileHandle) )
    {
        DebugError("CImplLinuxFile::Read Read failled");
        return FALSE;
    }

    return TRUE;
}

Bool    CImplLinuxFile::IsEndOfFile() const
{
    if( feof( (FILE*) m_FileHandle ) )
        return TRUE;

    return FALSE;
}

Bool CImplLinuxFile::Write( const Void* data, const UInt32 size)
{
    UInt32 bytesWritten = 0;

    DebugAssert( m_FileHandle );

    if (size && data )
    {
        bytesWritten = (UInt32) fwrite( data, size ,1 ,(FILE*)m_FileHandle );
    }
    
    if(bytesWritten == 1)
        return TRUE;
    
    return FALSE;
}


UInt32	CImplLinuxFile::GetPosition() const
{
    if( m_FileHandle == NULL )
        return 0;
    
    return ( ftell( (FILE*) m_FileHandle ) );
}

Bool	CImplLinuxFile::SetRelativePosition( const Int32 newposition)
{
    if( m_FileHandle == NULL )
        return false;
    
    if( fseek( (FILE*) m_FileHandle, (long)newposition, SEEK_CUR))
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

Bool	CImplLinuxFile::SetPosition( const UInt32 newposition)
{
    if( m_FileHandle == NULL )
        return false;
    
    if( fseek( (FILE*) m_FileHandle, (long)newposition, SEEK_SET))
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

UInt32	CImplLinuxFile::GetSize() const
{
    if( m_FileHandle == NULL )
        return 0;


    UInt32 currentpos = GetPosition();
    
    fseek( (FILE*) m_FileHandle, 0, SEEK_END);
    
    UInt32 size = GetPosition();
    
    if( fseek( (FILE*) m_FileHandle, (long)currentpos, SEEK_SET) )
    {
        return 0;
    }

    return size;
}

Bool CImplLinuxFile::IsOpen()  const
{
    return (m_FileHandle==NULL)?false:true;
}
