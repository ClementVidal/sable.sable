#ifndef _SABLE_CORE_COMMON_BUFFER_
#define _SABLE_CORE_COMMON_BUFFER_

#include <Sable\Core\Common\IODevice.h>
#include <Sable\Core\Collection\Array.h>

namespace Sable
{

/**
\ingroup CoreCommon
The CBuffer class provides a CIODevice interface for a CArray<Byte>
*/
class CBuffer : public CIODevice
{

public:

	/** @name Constructor/Destructor*/
    //@{
    CBuffer( );
	~CBuffer();
    //@}

	/** @name Accessors*/
    //@{
    Bool            IsOpen() const;
    UInt32          GetPosition() const;
    UInt32          GetSize() const;
    Bool            GetIsEndOfFile() const;
    Bool	        SetRelativePosition( Int32 newposition);
    Bool	        SetPosition( UInt32 newposition );
    //@}

    /** @name Manipulator*/
    //@{
    Bool            Open( const CArray<Byte>& data, EAccesMode acces );
    Bool            Open( CArray<Byte>& data, EAccesMode acces );
    Void            Close();
    Bool            Read( Void* data, UInt32 size );
    Bool            Write( Void* data, UInt32 size );
    Void            Flush();
    //@}

private:

    //Attributes
	CArray<Byte>*    m_Array;
    UInt32           m_Position;


};

}

#endif
