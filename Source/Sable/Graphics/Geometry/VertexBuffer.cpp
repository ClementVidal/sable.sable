#include <Sable/Graphics/Geometry/VertexBuffer.h>

#include <Sable/Graphics/Geometry/VertexLayout.h>
#include <Sable/Graphics/Geometry/Impl/Stub/VertexBuffer.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CGeometryVertexBuffer, CManagedObject );

CGeometryVertexBuffer::CGeometryVertexBuffer() :
	m_RawData( (CMemoryHeap*)NULL ),
	m_Impl( *this )
{
	m_VertexByteCount = 0;
	m_VertexCount = 0;
	m_Flags.Clear();
}

CGeometryVertexBuffer::~CGeometryVertexBuffer()
{
	UnLoad( );
}

UInt32 CGeometryVertexBuffer::GetVertexByteCount() const
{
	return m_VertexByteCount;
}

UInt32 CGeometryVertexBuffer::GetVertexCount() const
{
	return m_VertexCount;
}

CImplVertexStream& CGeometryVertexBuffer::GetImpl()
{
    return m_Impl;
}

Void CGeometryVertexBuffer::SetRawData( UInt32 vertexCount, UInt32 vertexByteCount, const Byte* data )
{
	m_VertexCount = vertexCount;
	m_VertexByteCount = vertexByteCount;

	if( data )
	{
		m_RawData.SetFrom( data, m_VertexCount*m_VertexByteCount);
	}
	else
	{
		m_RawData.SetItemCount( m_VertexCount*m_VertexByteCount );
		m_RawData.Fill( 0 );
	}
}

const Byte* CGeometryVertexBuffer::GetRawData() const
{
    return m_RawData.GetBuffer();
}

UInt32 CGeometryVertexBuffer::GetRawDataByteCount() const
{
    return m_VertexByteCount*m_VertexCount;
}

Void CGeometryVertexBuffer::UnLoad( )
{
	m_Impl.UnInitialize( );
	m_VertexByteCount = 0;
	m_VertexByteCount = 0;
	m_Flags.Clear();
}

/**
Create the vertex stream, and bind it's to the GPU.
**/
Void CGeometryVertexBuffer::Load( )
{
	// Static Buffer must always be provided with valid raw data at load time
	DebugAssert( ! ( !m_Flags.GetBit( nFlag_Dynamic ) && m_RawData.GetByteCount()==0 ) );
	m_Impl.Initialize( );
}

/**
Lock a part or the entire buffer.
The entire buffer is locked if start == size == 0
*/
Byte* CGeometryVertexBuffer::Lock( UInt32 vertexStart, UInt32 vertexCount )
{
    DebugAssertMsg( !m_Flags.GetBit( nFlag_Locked ), "CGeometryVertexBuffer::Lock - vertex stream already locked" );
	DebugAssertMsg( m_Flags.GetBit( nFlag_Dynamic ), "CGeometryVertexBuffer::Lock - vertex stream must be dynamic in order to be locked");
    m_Flags.SetBit( nFlag_Locked );
	return m_Impl.Lock( vertexStart,vertexCount );
}

Void CGeometryVertexBuffer::UnLock()
{
    m_Flags.ClearBit( nFlag_Locked );
	m_Impl.UnLock( );
}

Bool CGeometryVertexBuffer::IsLocked() const
{
    return m_Flags.GetBit( nFlag_Locked );
}

/**
Set the stream as current vertex stream
**/
Void CGeometryVertexBuffer::Activate( CRenderer& renderer, UInt8 streamIndex )
{
	DebugGraphicCommandGroup( "CGeometryVertexBuffer::Activate" );
	m_Impl.Activate( streamIndex );
}

Bool CGeometryVertexBuffer::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;

	if( ar.BeginScope( WT("Stream"), version ) == version )
	{
		ar.Serialize( m_VertexCount, WT("VertexCount") );
		ar.Serialize( m_VertexByteCount, WT("VertexByteCount") );
		ar.Serialize( m_Flags, WT("Flags") );

		if( ar.IsLoading() )
		{
			m_RawData.SetItemCount( m_VertexCount*m_VertexByteCount );
		}

		ar.Serialize( m_RawData.GetBuffer(), m_VertexCount*m_VertexByteCount, WT("RawData") );

		ar.EndScope();
	}
	return TRUE;
}

Void CGeometryVertexBuffer::SetAttribute( EFlag flag )
{
	m_Flags.SetBit( flag );
}

Bool CGeometryVertexBuffer::GetAttribute( EFlag flag ) const
{
	return m_Flags.GetBit( flag );
}


