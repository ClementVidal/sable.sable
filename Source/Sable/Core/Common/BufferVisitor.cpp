#include <Sable/Core/Common/BufferVisitor.h>

CBufferVisitor::CBufferVisitor( )
{
    m_RawData           = NULL;
    m_ElementByteOffset = 0;
    m_ChunckByteSize    = 0;
    m_ChunckCount = 0;
}

/**
Initialize a buffer visitor.
The parameters are used to specify where each instances of the data are located within the stream
*/
CBufferVisitor::CBufferVisitor( const Byte* rawBuffer, UInt32 elementByteOffset, UInt32 chunckByteSize, UInt32 chunckCount )
{
	m_RawData           = rawBuffer;
	m_ElementByteOffset = elementByteOffset;
	m_ChunckByteSize    = chunckByteSize;
    m_ChunckCount = chunckCount;
}

CBufferVisitor::~CBufferVisitor( )
{
}

UInt32 CBufferVisitor::GetChunckCount() const
{
    return m_ChunckCount;
}

Bool CBufferVisitor::IsValid() const
{
    return m_RawData && m_ChunckByteSize > 0 && m_ChunckCount > 0;
}