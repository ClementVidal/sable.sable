#ifndef _SABLE_CORE_FILE_IMPL_LINUX_SYSTEM_
#define _SABLE_CORE_FILE_IMPL_LINUX_SYSTEM_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/File/Impl/Stub/System.h>

namespace Sable
{

class CFileSystem;

/** 
*/
class CImplLinuxFileSystem : public CImplStubFileSystem
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplLinuxFileSystem( CFileSystem& publicImpl );
    ~CImplLinuxFileSystem();
    //@}

    /** @name Manipulator*/
    //@{
    Bool	ListDirectory( const CFilePath& dir, CArray<CFilePath>& list ) const;
    //@}

protected:

    // Mathods
    CFilePath	ProcessFindData( String dir, const Void* data ) const;
    Bool        IsValidFindData( const Void* data ) const;

    // Attributes

};

}

#endif
