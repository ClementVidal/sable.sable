#ifndef _SABLE_CORE_FILE_FILESYSTEM_
#define _SABLE_CORE_FILE_FILESYSTEM_

#include <Sable/Core/Collection/Header.h>
#include <Sable/Core/String/StaticString.h>

#include <Sable/Core/File/Impl/Header.h>

namespace Sable
{

/** 
\ingroup CoreFile
File system

Provide functions for file management at a system level.

Also provide functions to avoid the use of full physical file path
by providing a simple mechanism of virtual directory. ( see GetFilePath() )
*/
class CFileSystem
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CFileSystem();
	virtual ~CFileSystem();
	//@}

	/** @name Accessors*/
	//@{
    CFilePath               GetRootPath() const;
    CFilePath               GetFilePath( String vDir, String path );
	//@}

	/** @name Manipulator*/
	//@{
	Bool					ListDirectory( const CFilePath& dir, CArray<CFilePath>& list ) const;
	Bool                    DoesFileExist( const CFilePath& filePath );
	Void                    LoadConfigFile( );
	//@}

private:

	// Methods
    Void        SetupDefaultVDir();


    //Attributes
	CMap< CStringIdentifier, CStaticString<256> > m_VDirTable;

	CImplFileSystem	m_Impl;

};

}
#endif
