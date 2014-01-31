#include <Sable/Core/File/FilePath.h>

#include <Sable/Core/String/Primitives.h>

using namespace Sable;

CFilePath::CFilePath()
{
    SetEmpty();
}

/**
Construct a file name from a file path.
*/
CFilePath::CFilePath( String path )
{
	Bool isFilePath = TRUE;
    UInt32 len = StringGetLength( path );

	if( len )
	{
		if( path[len-1] == '/' || path[len-1] == '\\' )
		{
			isFilePath = FALSE;
		}

		if( !isFilePath )
		{
			SetPath( path, NULL );
		}
		else
		{
			Char fullTypeName[256];
			Char dir[128];
			Char tmp[256];

			StringCopy( path, tmp, 256 );

			NormalizeSeparator( tmp );

			Int32 index = CharArrayReverseFind( tmp, StringGetLength( tmp ), '/' );

			if( index > -1 )
			{
				StringCopySubPart( tmp, index+1, len-index-1, fullTypeName, 128 );
				StringCopySubPart( tmp, 0, index+1, dir, 128 );
			}
			else 
			{
				StringCopy( "", dir, 128 );
				StringCopySubPart( tmp, 0, len, fullTypeName, 128 );
			}

			SetPath( dir, fullTypeName );
		}
	}
	else
	{
		SetEmpty();
	}

}

CFilePath::~CFilePath()
{
}

Void CFilePath::SetEmpty( )
{
    m_Buffer[0] = '\0';
    m_Length = 0;
}

/**
return TRUE if the file really exist on the disk.
False otherwise
*/
Bool CFilePath::Exist() const
{
	if( IsValid() == FALSE )
		return FALSE;

    return CoreManager.GetFileSystem().DoesFileExist( *this );
}

UInt32	CFilePath::GetLength() const
{
	return m_Length;
}

const Char*	CFilePath::GetBuffer() const
{
	return m_Buffer;
}
/*
Char*	CFilePath::GetBuffer()
{
	return m_Buffer;
}
*/
UInt32 CFilePath::GetPathMaxLen()
{
	return FILENAME_BUFFER_SIZE;
}

Void CFilePath::Normalize( Char* buffer )
{
	NormalizeSeparator( buffer );
	RemoveDotSlash( buffer );
	RemoveDuplicatedSeparator( buffer );
}

Void CFilePath::RemoveDotSlash( Char* buffer )
{
	UInt32 len, i, j, c;

	len = StringGetLength( buffer );

	i = len-1;
	c = 0;
	// Don't go after 1 because we don't want to remove the first ./ in a relative file path
	while( i>1 )
	{
		if( buffer[i] == '/' && buffer[i-1] == '.' )
		{
			for( j=i-1; j<len-c; j++ )
			{
				buffer[j] = buffer[j+1];
			}

			c++;
		}
		i--;
	}

	m_Length = len - c;
}

Void CFilePath::RemoveDuplicatedSeparator( Char* buffer )
{
	UInt32 len, i, j, c;

	len = StringGetLength( buffer );

	i = len-1;
	c = 0;
	while( i>0 )
	{
		if( buffer[i] == '/' && buffer[i-1] == '/' )
		{
			for( j=i-1; j<len-c; j++ )
			{
				buffer[j] = buffer[j+1];
			}

			c++;
		}
		i--;
	}

	m_Length = len - c;
}

Void CFilePath::NormalizeSeparator( Char* buffer )
{
    UInt32 len, i;

    len = StringGetLength( buffer );

    for( i=0;i<len;i++ )
    {
        if( buffer[i] == '\\' )
            buffer[i] = '/';
    }
}

/**
Assign a new path to this file name object.
\param dir the directory part of the path
\param fullName the fullName (name+ext) of the file. Can be NULL if only a directory path need to be specified
*/
Void CFilePath::SetPath( String dir, String fullName )
{
    Char validDir[FILENAME_BUFFER_SIZE];
    Char validFullName[FILENAME_BUFFER_SIZE];

    if( !FixDirectory( dir, validDir, FILENAME_BUFFER_SIZE ) )
    {
        SetEmpty();
        return;
    }
    StringCopy( validDir, m_Buffer, FILENAME_BUFFER_SIZE );

	if( fullName )
	{
		if( !FixFullName( fullName, validFullName, FILENAME_BUFFER_SIZE ) )
		{
			SetEmpty();
			return;
		}

		StringAppend( m_Buffer, validFullName, m_Buffer, 256 );
	}

    m_Length = StringGetLength( m_Buffer );
}

Bool CFilePath::FixFullName( String fullName, Char* buffer, UInt32 size )
{
    StringCopy( fullName, buffer, size );
    return TRUE;
}

Bool CFilePath::FixDirectory( String path, Char* buffer, UInt32 size )
{
    StringCopy( path, buffer, size );
    UInt32 len;
    
    len = StringGetLength( buffer );
    if( len == 0 )
        return FALSE;

    NormalizeSeparator( buffer );

    if( buffer[len-1] != '/' )
    {
        buffer[len] = '/';
        buffer[len+1] = '\0';
    }

    Normalize( buffer );

    return TRUE;
}

/**
Make this path relative to a given root dir.
\return TRUE in case of success. FALSE if this path or rootDir are already relative
*/
Bool CFilePath::MakeRelativeTo( const CFilePath& rootDir )
{
	if( IsRelative() || rootDir.IsRelative() )
		return FALSE;

	DebugAssert( rootDir.IsDirPath() );

	const Char* thisBuffer = GetBuffer();
	const Char* rootDirBuffer = rootDir.GetBuffer();

	Int32 i =0;
	// Search for a first difference
	for( i=0;i<MathMin( GetLength(), rootDir.GetLength() );i++ )
	{
		if( thisBuffer[i] != rootDirBuffer[i] )
			break;
	}

	// Path are not relative to each other
	if( i == 0 )
		return FALSE;

	// Search back for a separator
	while( i >= 0 )
	{
		if( thisBuffer[i] == '/' )
			break;
		i--;
	}

	Char newPath[256];
	newPath[0] = '.';
	StringCopy( thisBuffer+i, newPath+1, 255 );

	*this = CFilePath( newPath );

	return TRUE;
}

/**
Append a relative path to this one.
\note Current CFilePath MUST be a directory and relativePath MUST be a relative path
*/
Void CFilePath::AppendRelativePath( const CFilePath& relativePath )
{
	DebugAssert( IsDirPath() );
	DebugAssert( relativePath.IsRelative() );

	Char fileDir[256];
	Char fileName[256];
	Char fileExt[256];
	relativePath.GetDirectory( fileDir, 256 );

	AppendDir( fileDir );
	relativePath.GetName(fileName, 256);
	relativePath.GetExtension(fileExt, 256);
	SetName( fileName );
	SetExtension( fileExt );
}

Bool CFilePath::IsRelative() const
{
	if( !IsValid() )
		return FALSE;

	if( m_Buffer[0] == '.' )
		return TRUE;

	return FALSE;
}

/**
Return TRUE when this path point to a file and not to a directory
*/
Bool CFilePath::IsFilePath() const
{
	if( IsValid() )
		return m_Buffer[m_Length-1] != '/';

	return FALSE;
}

/**
Return TRUE when this path point to a directory and not to a file
*/
Bool CFilePath::IsDirPath() const
{
	return !IsFilePath();
}

/**
Return the file extension part of the file
\note With "c:\mydir\myfile.txt" this will return "txt" WITHOUT the '.'
\param buff The buffer for the output directory
\param s The size of the output buffer in Char
\return a pointer to buff or NULL is the path is a path to a directory
*/
String CFilePath::GetExtension( Char* buff, UInt32 s ) const
{
	if( IsFilePath() )
	{
		Int32 i;
		Int32 start = GetExtStart();
		Int32 end = GetExtEnd();
		Int32 l = end - start;

		if( start == -1 || end == -1 || l >= (Int32) ( s - 1) )
			return NULL;

		start += 1;  // Plus One to skip the '.'
		for( i=0; i<l;i++ )
		{
			buff[i] = m_Buffer[start+i];
		}
		buff[i] = '\0';
	}
	else
	{
		buff[0] = 0;
	}

    return buff;
}

/**
Set the extension for the given file.
If this path point to a directory, nothing is done.
The extension must be specified without the '.' (ex: "bmp")
*/
Void CFilePath::SetName( String name )
{
	Int32 nameStart = GetNameStart();
	Int32 nameLength = StringGetLength( name );
	MemoryCopy( name, m_Buffer+nameStart, nameLength );

	m_Length = nameStart + nameLength;
	m_Buffer[ m_Length ] = 0;
}

/**
Set the extension for the given file.
If this path point to a directory, nothing is done.
The extension must be specified without the '.' (ex: "bmp")
*/
Void CFilePath::SetExtension( String ext )
{
	if( IsFilePath() == FALSE )
		return;

	Int32 extLength = StringGetLength( ext );
	Int32 extStart = GetExtStart();
	if( extStart == -1 )
	{	
		extStart = m_Length+1;
		m_Buffer[m_Length] = '.';
		MemoryCopy( ext, m_Buffer+m_Length+1, extLength );
	}
	else
	{
		MemoryCopy( ext, m_Buffer+extStart+1, extLength );
	}

	m_Length = extStart+extLength;
	m_Buffer[ m_Length ] = 0;

}

/**
Return the file name  part of the file
\note With "c:\mydir\myfile.txt" this will return "myfile"
\param buff The buffer for the output directory
\param s The size of the output buffer in Char
\return a pointer to buff or NULL is the path is a path to a directory
*/
String CFilePath::GetName( Char* buff, UInt32 s ) const
{
	if( IsFilePath() )
	{
		Int32 start = GetNameStart();
		Int32 end = GetNameEnd();
		Int32 l = end - start;

		if( start == -1 || end == -1 || l >= (Int32) ( s - 1) )
			return NULL;

		StringCopySubPart( m_Buffer, start, l, buff, s );
	}
	else
	{
		buff[0] = 0;
		return NULL;
	}

    return buff;
}

/**
Return the file name and the file extension part of the file
\note With "c:\mydir\myfile.txt" this will return "myfile.txt"
\param buff The buffer for the output directory
\param s The size of the output buffer in Char
\return a pointer to buff or NULL is the path is a path to a directory
*/
String CFilePath::GetFullTypeName( Char* buff, UInt32 s ) const
{
	if( IsFilePath() )
	{
		Char tmpExt[256];
		GetName( buff, s );

		if( GetExtStart( ) > -1 )
		{
			GetExtension( tmpExt, 256 );
			StringAppend( buff, ".", buff, 256 );
			StringAppend( buff, tmpExt, buff, 256 );
		}
	}
	else
	{
		buff[0] = 0;
		return NULL;
	}

    return buff;
}

/**
Return the full path stored in this file name
\note With "c:\mydir\myfile.txt" this will return "c:\mydir\myfile.txt"
*/
String CFilePath::GetPath( ) const
{
    return m_Buffer;
}

/**
Return the directory part of the file, or NULL if the path does not specify any directory
\param buff The buffer for the output directory
\param s The size of the output buffer in Char
\return a pointer to buff
*/
String CFilePath::GetDirectory( Char* buff, UInt32 s ) const
{
	Int32 start = GetDirectoryStart();
	Int32 end = GetDirectoryEnd();
	Int32 l = end - start;

	if( start == -1 || end == -1 || l >= (Int32) ( s - 1) )
		return NULL;

	StringCopySubPart( m_Buffer, start, l, buff, s );
	return buff;
}


Int32 CFilePath::GetDirectoryStart( ) const
{
    if( GetDirectoryEnd() > -1 )
    {
        return 0;
    }
    return -1;
}


Int32 CFilePath::GetDirectoryEnd( ) const
{
    Int32 s = 0;
    Int32 lastSeparator = -1;

    lastSeparator = StringReverseFind( m_Buffer, '/' );
    if( lastSeparator != -1 )
        lastSeparator++;

    return lastSeparator;
}

Int32 CFilePath::GetNameEnd( ) const
{
    Int32 s = GetExtStart( );

    if( s == -1 )
        return m_Length;

    return s;
}

Int32 CFilePath::GetNameStart( ) const
{
    Int32 s = GetDirectoryEnd( ) ;

    if( s == -1 )
        s = 0;

    return s;
}

Int32 CFilePath::GetExtEnd( ) const
{
    Int32 s = GetExtStart( );

    if( s == -1 )
        return -1;

    return m_Length;
}

Int32 CFilePath::GetExtStart( ) const
{
	if( IsFilePath() == FALSE )
		return -1;

    Int32 s = 0;
    Int32 lastDot = -1;

    for( s=m_Length-1; s>=0; s-- )
    {
        if( m_Buffer[s] == '.' )
		{
            return s;
		}
    }

    return -1;
}


/**
Return true if the path is correctly formed, false otherwise.

\note This method does not test if the file exist on disk, it just test if the path is correctly formed
\note Use Exist() method to test if the file really exist on disk
*/
Bool CFilePath::IsValid() const
{
    return m_Length > 0;
}

Bool CFilePath::operator != ( const CFilePath& other ) const
{
    return StringCompare( GetPath(), other.GetPath() ) != 0;
}

Bool CFilePath::operator == ( const CFilePath& other ) const
{
	return StringCompare( GetPath(), other.GetPath() ) == 0;
}

Bool CFilePath::Serialize( CPersistentArchive& ar )
{
    Char buffer[FILENAME_BUFFER_SIZE];

    if( ar.IsStoring() )
    {
        StringCopy( m_Buffer, buffer, FILENAME_BUFFER_SIZE );
    }
    
    if( ar.Serialize( buffer, FILENAME_BUFFER_SIZE, WT("Buffer") ) )
    {
        if( ar.IsLoading() )
        {
            *this = CFilePath( buffer );
        }
        return TRUE;
    }

    return FALSE;
}

/**
Append a directory to the path.
*/
Void CFilePath::AppendDir( String dir )
{
	DebugAssert( !IsFilePath() );
	StringSetFormattedText( m_Buffer, FILENAME_BUFFER_SIZE, "%s%s/", m_Buffer, dir );
	m_Length = StringGetLength( m_Buffer );

	Normalize( m_Buffer );
}

Bool CFilePath::operator < ( const CFilePath& other ) const
{
	if( StringCompare( m_Buffer, other.m_Buffer ) < 0 )
		return TRUE;

	return FALSE;
}
