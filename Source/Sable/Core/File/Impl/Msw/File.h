#ifndef _SABLE_CORE_FILE_IMPL_MSW_FILE_
#define _SABLE_CORE_FILE_IMPL_MSW_FILE_

#include <Sable\Core\File\Impl\Stub\File.h>

namespace Sable
{

/** 
*/
class CImplMswFile : public CImplStubFile
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplMswFile( CFile& publicImpl );
    virtual ~CImplMswFile();
    //@}

    /** @name Accessors*/
    //@{
    Bool            IsOpen() const  ;
    UInt32          GetPosition() const ;
    UInt32          GetSize() const;
    Bool            IsEndOfFile() const;
    //@}

	/** @name Manipulator*/
	//@{
    Void            Close();

    Bool            Open( const CFilePath& filename, const EAccesMode acces = nAccesMode_ReadWrite );

    Bool            Read( Void* data, const UInt32 size );
    Bool            Write( const Void* data, const UInt32 size );
    Void            Flush();

    Bool	        SetRelativePosition( const Int32 newposition);
    Bool	        SetPosition( const UInt32 newposition);
	//@}

private:

	// Attributes
	Void*          m_FileHandle;

};

}

#endif

