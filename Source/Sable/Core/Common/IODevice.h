#ifndef _SABLE_CORE_COMMON_IOBUFFER_
#define _SABLE_CORE_COMMON_IOBUFFER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\ManagedObject\ManagedObject.h>

namespace Sable
{

/**
\ingroup CoreCommon
*/
class CIODevice : public CManagedObject
{

public:

	/** @name Constructor/Destructor*/
    //@{
    CIODevice();
	~CIODevice();
    //@}

	/** @name Accessors*/
    //@{
    EAccesMode              GetAccesMode() const;
    virtual Bool            IsOpen() const = 0;
    virtual UInt32          GetPosition() const = 0;
    virtual UInt32          GetSize() const = 0;
    virtual Bool            GetIsEndOfFile() const = 0;
    virtual Bool	        SetRelativePosition( Int32 newposition ) = 0;
    virtual Bool	        SetPosition( UInt32 newposition ) = 0;
    //@}

    /** @name Manipulator*/
    //@{
    virtual Void            Close();
    virtual Bool            Open( EAccesMode acces );
    virtual Bool            Read( Void* data, UInt32 size ) = 0;
    virtual Bool            Write( Void* data, UInt32 size ) = 0;
    virtual Void            Flush() = 0;
	Bool					ReadChar( Char& c );
	Int32					ReadLine( Char* buffer, Int32 bufferLen );
    //@}

private:

    //Attributes
    EAccesMode          m_AccessMode; 
	
};


}

#endif
