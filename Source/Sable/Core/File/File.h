#ifndef _SABLE_CORE_FILE_FILE_
#define _SABLE_CORE_FILE_FILE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Common\IODevice.h>
#include <Sable\Core\String\String.h>
#include <Sable\Core\File\FilePath.h>
#include <Sable\Setup.h>

#include <Sable\Core\File\Impl\Header.h>

namespace Sable
{

/** 
\ingroup CoreFile
File. 
*/
class CFile : public CIODevice 
{
 
    DEFINE_MANAGED_CLASS( CFile );

public:

    /** @name Constructor/Destructor*/
    //@{
    CFile();
    CFile( const CFilePath& filename, EAccesMode acces = nAccesMode_Read );
    ~CFile();
    //@}

    /** @name Accessors*/
    //@{
    String          GetFilePath() const ;
    Bool            IsOpen() const  ;
    UInt32          GetPosition() const ;
    UInt32          GetSize() const;
    Bool            GetIsEndOfFile() const;
    //@}
    
    /** @name Manipulator*/
    //@{
    Void            Close();

    Bool            Open( const CFilePath& filename, EAccesMode acces = nAccesMode_ReadWrite );

    Bool            ReadAll( CArray<Byte>& data );
    Bool            Read( Void* data, UInt32 size );
    Bool            Write( Void* data, UInt32 size );
    Void            Flush();

    Bool	        SetRelativePosition( Int32 newposition);
    Bool	        SetPosition( UInt32 newposition );
    //@}

private:

    //Methods

    //Attributes
	CFilePath           m_Path;
	
    CImplFile           m_Impl;

};

}



#endif
