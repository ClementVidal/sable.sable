#ifndef _SABLE_CORE_FILE_IMPL_STUB_SYSTEM_
#define _SABLE_CORE_FILE_IMPL_STUB_SYSTEM_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Collection\Array.h>
#include <Sable\Core\File\FilePath.h>

namespace Sable
{

class CFileSystem;

/** 
*/
class CImplStubFileSystem
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplStubFileSystem( CFileSystem& publicImpl ) { m_PublicImpl = &publicImpl; }
    virtual ~CImplStubFileSystem() {};
    //@}

	/** @name Manipulator*/
	//@{
	virtual CFilePath	GetRootPath() const { return CFilePath(); }
	virtual Bool		DoesFileExist( const CFilePath& file ) const { return FALSE; }
	virtual Bool		ListDirectory( const CFilePath& dir, CArray<CFilePath>& list ) const { return TRUE; }
	//@}

protected:

    // Attributes
    CFileSystem*  m_PublicImpl;
};

}

#endif
