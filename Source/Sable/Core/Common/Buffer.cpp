#include <Sable/Core/Common/Buffer.h>

CBuffer::CBuffer( ) :
    CIODevice()
{
    m_Array = NULL;
    m_Position = 0;
}

CBuffer::~CBuffer( )
{
}

Bool CBuffer::IsOpen() const
{
    return GetAccesMode() != nAccesMode_None;
}

UInt32 CBuffer::GetPosition() const
{
    return m_Position;
}

Bool CBuffer::Open( const CArray<Byte>& data, EAccesMode acces )
{
    DebugAssert( acces == nAccesMode_Read );
    m_Array = const_cast< CArray<Byte>* >( &data );
    return CIODevice::Open( acces );
}

Bool CBuffer::Open( CArray<Byte>& data, EAccesMode acces )
{
    m_Array = &data;
    return CIODevice::Open( acces );
}

UInt32 CBuffer::GetSize() const
{
    if( m_Array )
        return m_Array->GetItemCount();

    return 0;
}

Bool CBuffer::GetIsEndOfFile() const
{
    if( m_Array && m_Position >= GetSize() )
        return TRUE;

    return FALSE;
}

Bool CBuffer::SetRelativePosition( Int32 newposition )
{
    if( !m_Array )
        return FALSE;

    m_Position = m_Position + newposition;
    if( m_Position >= GetSize() )
    {
        m_Position = GetSize() - 1;
        return FALSE;
    }

    return TRUE;
}

Bool CBuffer::SetPosition( UInt32 newposition )
{
    if( !m_Array )
        return FALSE;

    m_Position = newposition;
    if( m_Position >= GetSize() )
    {
        m_Position = GetSize() - 1;
        return FALSE;
    }

    return TRUE;
}

Void CBuffer::Close()
{
    CIODevice::Close();
}

Bool CBuffer::Read( Void* data, UInt32 size )
{
    if( !m_Array )
        return FALSE;

	if( m_Position == m_Array->GetItemCount() )
		return FALSE;

    UInt32 effectiveSize = MathMin( size, GetSize() - m_Position );
    MemoryCopy( &(*m_Array)[m_Position], data, effectiveSize );

    m_Position+=size;
    return TRUE;
}

Bool CBuffer::Write( Void* data, UInt32 size )
{
    if( !m_Array )
        return FALSE;

    UInt32 effectiveSize = MathMin( size, GetSize() - m_Position );
    MemoryCopy( data, &m_Array[m_Position], effectiveSize );
    m_Position+=size;
    return TRUE;
}

Void CBuffer::Flush()
{

}
