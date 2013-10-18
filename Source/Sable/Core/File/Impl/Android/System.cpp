#include <Sable/Core/File/Impl/Msw/System.h>

using namespace Sable;

CImplMswFileSystem::CImplMswFileSystem( CFileSystem& publicImpl ) :
    CImplStubFileSystem(publicImpl)
{
}

CImplMswFileSystem::~CImplMswFileSystem()
{
}

Bool CImplMswFileSystem::IsValidFindData( const Void* data ) const
{
/*    const WIN32_FIND_DATA& findData = *(const WIN32_FIND_DATA*)data;
	if( ( StringCompare( findData.cFileName, WT(".") ) == 0 ) || ( StringCompare( findData.cFileName, WT("..") ) == 0 ) )
		return FALSE;
*/
	return TRUE;
}

CFilePath CImplMswFileSystem::ProcessFindData( String dir, const Void* data  ) const
{
	/*
    const WIN32_FIND_DATA& findData = *(const WIN32_FIND_DATA*)data;

	CFilePath fileName;
	Char tmpBuffer[256];

	if( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
	{
		WStringToString( findData.cFileName, tmpBuffer, 256 );
		fileName.SetPath( dir, NULL );
		fileName.AppendDir( tmpBuffer );
	}
	else 
	{
		WStringToString( findData.cFileName, tmpBuffer, 256 );
		fileName.SetPath( dir, tmpBuffer );
	}

	return fileName;*/
	return CFilePath();
}

Bool CImplMswFileSystem::ListDirectory( const CFilePath& dir, CArray<CFilePath>& list ) const
{
/*	DebugAssert( dir.IsFilePath() == FALSE );
	HANDLE hFind; 
	WIN32_FIND_DATA findData; 
	UInt32 entryCount = 0;
	UInt32 i = 0;

	Char tmpBuffer[256];
	WChar tmpWBuffer[256];
	StringToWString( dir.GetDirectory( tmpBuffer, 256 ), tmpWBuffer, 256 );
	StringAppend( tmpWBuffer, WT( "*" ), tmpWBuffer, 256 );

	// Count entry
	hFind = ::FindFirstFile( tmpWBuffer, &findData );
	if( hFind != INVALID_HANDLE_VALUE )
	{
		if( IsValidFindData( &findData ) )
		{
			entryCount++;
		}

		while( ::FindNextFile( hFind, &findData ) ) 
		{ 
			if( IsValidFindData( &findData ) )
			{
				entryCount++;
			}
		}
		::FindClose( hFind ); 
	}
	else
	{
		return FALSE;
	}

	list.SetItemCount( entryCount );

	// Fill Table
	hFind = ::FindFirstFile( tmpWBuffer, &findData );
	if( hFind != INVALID_HANDLE_VALUE )
	{
		if( IsValidFindData( &findData ) )
		{
			list[i++] = ProcessFindData( dir.GetBuffer(), &findData );
		}

		while( ::FindNextFile( hFind, &findData ) ) 
		{ 
			if( IsValidFindData( &findData ) )
			{
				list[i++] = ProcessFindData( dir.GetBuffer(), &findData );
			}
		}

		::FindClose( hFind ); 
	}
	*/
	return FALSE;
}
