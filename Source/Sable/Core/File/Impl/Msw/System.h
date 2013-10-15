#ifndef _SABLE_CORE_FILE_IMPL_MSW_SYSTEM_
#define _SABLE_CORE_FILE_IMPL_MSW_SYSTEM_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\File\Impl\Stub\System.h>

namespace Sable
{

class CFileSystem;

/** 
*/
class CImplMswFileSystem : public CImplStubFileSystem
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplMswFileSystem( CFileSystem& publicImpl );
    ~CImplMswFileSystem();
    //@}

	/** @name Manipulator*/
	CFilePath		GetRootPath() const;
	Bool			DoesFileExist( const CFilePath& file ) const;
	Bool			ListDirectory( const CFilePath& dir, CArray<CFilePath>& list ) const;
	//@}

protected:

	// Mathods
	CFilePath	ProcessFindData( String dir, const Void* data ) const;
	Bool		IsValidFindData( const Void* data ) const;

    // Attributes

};

}

#endif
