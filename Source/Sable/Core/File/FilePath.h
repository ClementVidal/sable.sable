#ifndef _SABLE_CORE_FILE_FILENAME_
#define _SABLE_CORE_FILE_FILENAME_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\String\String.h>

#define FILENAME_BUFFER_SIZE 128

namespace Sable
{

class CPersistentArchive;

/** 
\ingroup CoreFile
Parse a string corresponding to a file path or a dir path.
\note This object can either represent a File path OR a Directory path.
Use the IsFilePath() method to ditinguish between two.

Expose function to retrieve part of the path:
- Extension: The extension of the file if any
- Directory: The directory where the file is located ( or the directory if no file is specified )
- Name: The name of the file without the extension
- FullName: The name of the file plus the extension
*/
class CFilePath
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CFilePath( );
    explicit CFilePath( String fullPath );
    ~CFilePath( );
    //@}

    /** @name Operator*/
    //@{
    Bool operator < ( const CFilePath& other ) const;
	Bool operator != ( const CFilePath& other ) const;
	Bool operator == ( const CFilePath& other ) const;
    //@}

    /** @name Accessors*/
    //@{
	UInt32			GetLength() const;
	const Char*		GetBuffer() const;
    Bool			Exist() const;
	Bool			IsValid() const;
	Bool			IsRelative() const;
	Bool			IsFilePath() const;
	Bool			IsDirPath() const;
    String			GetExtension( Char* buff, UInt32 s ) const;
    String			GetName( Char* buff, UInt32 s ) const;
    String			GetFullTypeName( Char* buff, UInt32 s ) const;
    String			GetPath( ) const;
    String			GetDirectory( Char* buff, UInt32 s ) const;
	static UInt32	GetPathMaxLen();
	//@}
    
    /** @name Manipulator*/
    //@{
    Void        SetPath( String dir, String fullName );
	Void		SetExtension( String ext );
	Void		SetName( String ext );

    Bool        Serialize( CPersistentArchive& ar );
    Void        SetEmpty( ) ;
	Void		AppendDir( String dir );
	Void		AppendRelativePath( const CFilePath& relativePath );
	Bool		MakeRelativeTo( const CFilePath& rootDir );
	//@}

private:

    //Methods
    Bool FixFullName( String fullName, Char* buffer, UInt32 size );
    Bool FixDirectory( String dir, Char* buffer, UInt32 size );
    Void NormalizeSeparator( Char* buffer );
	Void RemoveDuplicatedSeparator( Char* buffer );
	Void RemoveDotSlash( Char* buffer );
	Void Normalize( Char* buffer );

    Int32 GetDirectoryEnd( ) const;
    Int32 GetDirectoryStart( ) const;
    Int32 GetNameEnd( ) const;
    Int32 GetNameStart( ) const;
    Int32 GetExtEnd( ) const;
    Int32 GetExtStart( ) const;

    //Attributes
    Char    m_Buffer[FILENAME_BUFFER_SIZE];
    UInt32  m_Length;

};

}



#endif
