#include <Sable\Graphics\Geometry\InstanceBuffer.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CGeometryInstanceBuffer, CManagedObject ) ;

CGeometryInstanceBuffer::CGeometryInstanceBuffer( )
{
	m_InstanceCount = 0;
    m_IsDirty = FALSE;
}

CGeometryInstanceBuffer::~CGeometryInstanceBuffer()
{
}

Void CGeometryInstanceBuffer::SetCapacity( UInt32 c )
{
    m_VertexBuffer.SetRawData( c, sizeof( SInstanceData ) );
    m_InstanceData.SetItemCount( c );
    m_VertexBuffer.Load();
}

UInt32 CGeometryInstanceBuffer::GetCapacity() const
{
	return m_VertexBuffer.GetVertexCount();
}

Void CGeometryInstanceBuffer::Flush()
{
	DebugGraphicCommandGroup( "CGeometryInstanceBuffer::Flush" );

    Byte* data = m_VertexBuffer.Lock();
    DebugAssert( data );
    MemoryCopy( m_InstanceData.GetBuffer(), data, m_VertexBuffer.GetRawDataByteCount() );
    m_VertexBuffer.UnLock();

    m_IsDirty = FALSE;
}

Void CGeometryInstanceBuffer::AddInstanceData( const CGeometryInstanceBuffer::SInstanceData& m )
{
    if( m_InstanceCount >= m_InstanceData.GetItemCount() )
    {
        DebugLogError("CGeometryInstanceBuffer::AddInstanceData - Not enough room in instance buffer");
    }
    else
    {
        m_InstanceData[m_InstanceCount] = m;
        m_InstanceCount++;
        m_IsDirty = TRUE;
    }
}

Void CGeometryInstanceBuffer::RemoveAllInstance()
{
	m_InstanceCount = 0;
    m_IsDirty = TRUE;
}

UInt32 CGeometryInstanceBuffer::GetInstanceCount() const
{
	return m_InstanceCount;
}

Bool CGeometryInstanceBuffer::IsDirty() const
{
    return m_IsDirty;
}

Void CGeometryInstanceBuffer::Activate( CRenderer& renderer, UInt32 index )
{
	if( IsDirty() )
    {
        Flush();
    }

    renderer.Activate( m_VertexBuffer, index );
}

Bool CGeometryInstanceBuffer::Serialize( CPersistentArchive& ar )
{
	return TRUE;
}