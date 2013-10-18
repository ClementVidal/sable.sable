#ifndef _SABLE_CORE_FILE_IMPL_STUB_FILE_
#define _SABLE_CORE_FILE_IMPL_STUB_FILE_

#include <Sable/Core/Common/DataTypes.h>

namespace Sable
{

class CFilePath;
class CFile;

/** 
*/
class CImplStubFile
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplStubFile( CFile& publicImpl ) { m_PublicImpl = &publicImpl; }
    virtual ~CImplStubFile() {};
    //@}

    /** @name Accessors*/
    //@{
    virtual Bool            IsOpen() const {return FALSE;}
    virtual UInt32          GetPosition() const {return 0;}
    virtual UInt32          GetSize() const {return 0;}
    virtual Bool            IsEndOfFile() const {return TRUE;}
    //@}

    /** @name Manipulator*/
    //@{
    virtual Void            Close(){}

    virtual Bool            Open( const CFilePath& filename, const EAccesMode acces ){return FALSE;}

    virtual Bool            Read( Void* data, const UInt32 size ){return FALSE;}
    virtual Bool            Write( const Void* data, const UInt32 size ){return FALSE;}
    virtual Void            Flush(){}

    virtual Bool            SetRelativePosition( const Int32 newposition){return FALSE;}
    virtual Bool            SetPosition( const UInt32 newposition){return FALSE;}

 	//@}

protected:

    // Attributes
    CFile*  m_PublicImpl;

};

}

#endif
