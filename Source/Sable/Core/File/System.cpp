#include <Sable/Core/File/System.h>

#include <Sable/Core/File/File.h>
#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Xml/Reader.h>

#define FILESYSTEM_CONFIG_FILE_NAME  "FileSystem.conf"

using namespace Sable;

CFileSystem::CFileSystem() :
    m_Impl( *this )
{
}

CFileSystem::~CFileSystem()
{

}

Void CFileSystem::SetupDefaultVDir()
{
	CFilePath gamePath;
	CFilePath systemPath;
    m_VDirTable.AddItem( "Root", GetRootPath().GetPath() );

	gamePath.SetPath( GetRootPath().GetPath(), NULL );
	gamePath.AppendDir( "Game" );
    m_VDirTable.AddItem( "Game", gamePath.GetPath());

	systemPath.SetPath( GetRootPath().GetPath(), NULL );
	systemPath.AppendDir( "System" );
	m_VDirTable.AddItem( "System", systemPath.GetPath());
}

/**
Load the config file if it exist, otherwise, setup default directory.
The config file, if needed, must be located at the root path of the application (i.e: the path where the executable is located)
and mus be named CoreManager.GetFileSystem().conf
*/
Void CFileSystem::LoadConfigFile()
{
	CFile file;
	CFilePath path;

	path.SetPath( GetRootPath().GetPath(), FILESYSTEM_CONFIG_FILE_NAME );
    SetupDefaultVDir();

    if( file.Open( path, nAccesMode_Read ) )
    {
        CXmlReader reader;
        reader.ReadFile( file );

        Char    vDir[64];
        Char    pDir[256];

        while( reader.ReadNode() )
        {
            reader.GetAttributeValue( 0, vDir, 64 );
            reader.GetAttributeValue( 1, pDir, 256 );
            
            if( !m_VDirTable.HasItem( vDir ) )
                m_VDirTable.AddItem( vDir );

            m_VDirTable.SetItem( vDir, pDir);
        }
    }
}

/**
Return a file path representing the FULL file path of a given file.

This path is created by the concatenation of two parts:
- Directory
- Path

The path is directly specified as a paramter.
The directory is extracting by looking in a virtual directory table.
The user provide a virtual directory name and the system replace it by the physical one.

*/
CFilePath CFileSystem::GetFilePath( String vDir, String path )
{
    if( m_VDirTable.HasItem( vDir ) )
    {
        Char tmp[256];
        String pDir = m_VDirTable.GetItem( vDir ).GetBuffer();

        StringSetFormattedText( tmp, 256, "%s%s", pDir, path );

        return CFilePath( tmp );
    }

    return CFilePath();
}

/**
Return a list of all the files and directory contained within dir.
\param dir The input directory, dir MUST be a dir name, and not a file name
\param list The list of files and sub directories
\return TRUE of the operation succeed, FALSE otherwise
*/
Bool CFileSystem::ListDirectory( const CFilePath& dir, CArray<CFilePath>& list ) const
{
	return m_Impl.ListDirectory( dir, list );
}

/**
Test if a given file exist
*/
Bool CFileSystem::DoesFileExist( const CFilePath& file )
{
	return m_Impl.DoesFileExist( file );
}

/**
Return the root path of the application.

We define the root path as the directory where the application executable is located
*/
CFilePath CFileSystem::GetRootPath() const
{
	return m_Impl.GetRootPath( );
}
