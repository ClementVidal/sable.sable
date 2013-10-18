#ifndef _SABLE_CORE_COMMON_BUFFERVISITOR_
#define _SABLE_CORE_COMMON_BUFFERVISITOR_

#include <Sable/Core/Common/DataTypes.h>

namespace Sable
{

/**
\ingroup CoreCommon
Helper class used to navigate into an heterogeneous buffer:
It allow simple access to one typed element into a stream of data chunk.
*/
class CBufferVisitor 
{

public:

	/** @name Constructor/Destructor*/
    //@{
    CBufferVisitor();
	CBufferVisitor( const Byte* rawBuffer, UInt32 elementByteOffset, UInt32 chunckByteSize, UInt32 chunckCount );
	~CBufferVisitor();
    //@}

	/** @name Accessors*/
    //@{
    Bool    IsValid() const;
    template< class DataType >
    const DataType& GetChunckElement( UInt32 i ) const;
    UInt32 GetChunckCount() const;
    //@}

    /** @name Manipulator*/
    //@{
  
    //@}

private:

    //Attributes
    const Byte* m_RawData;
    UInt32      m_ElementByteOffset;
    UInt32      m_ChunckByteSize;
    UInt32      m_ChunckCount;
	
};

template< class DataType >
const DataType& CBufferVisitor::GetChunckElement( UInt32 i ) const
{
    UInt32 byteOffset = ( m_ChunckByteSize * i ) + m_ElementByteOffset;
    DebugAssert( byteOffset < m_ChunckCount * m_ChunckByteSize );

    const DataType* buffer = (const DataType*)(((Byte*)m_RawData)+byteOffset);

    return *buffer;
}


}

#endif
