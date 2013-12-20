#include <Sable/Graphics/Geometry/IndexBuffer.h>

#include <Sable/Graphics/Geometry/Impl/Stub/IndexBuffer.h>
#include <Sable/Graphics/Common/Manager.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CGeometryIndexBuffer, CManagedObject );

CGeometryIndexBuffer::CGeometryIndexBuffer()
{
	m_DrawIndexCount = 0;
	m_IndexByteCount = 4;
	m_IndexCount = 0;
}

CGeometryIndexBuffer::~CGeometryIndexBuffer()
{
}

Void CGeometryIndexBuffer::SetDrawIndexCount( UInt32 count )
{
	if( count > GetIndexCount() )
		m_DrawIndexCount = GetIndexCount();

	m_DrawIndexCount = count;
}

Void CGeometryIndexBuffer::SetRawData( UInt32 indexCount, UInt32 indexByteCount, const Byte* data )
{
	m_IndexCount = indexCount;
	m_IndexByteCount = indexByteCount;
	if( data )
	{
		m_RawData.SetFrom( data, m_IndexByteCount*m_IndexCount );
	}
}

UInt32 CGeometryIndexBuffer::GetIndexByteCount() const
{
	return m_IndexByteCount;
}

Void CGeometryIndexBuffer::Load( )
{
	if( m_Impl.IsInitialized() )
		return;

	m_Impl.Initialize( GetIndexCount(), m_RawData.GetBuffer(), GetIndexCount()*GetIndexByteCount() );
}

Void CGeometryIndexBuffer::Activate( CRenderer& renderer )
{
	DebugProfile("CGeometryIndexBuffer::Activate");
	DebugGraphicCommandGroup( "CGeometryIndexBuffer::Activate" );

	DebugAssertMsg( m_IndexCount > 0, "Index buffer probably not initialized" );
	m_Impl.Activate( );
}

UInt32 CGeometryIndexBuffer::GetIndexCount() const
{
    return m_IndexCount;
}

UInt32 CGeometryIndexBuffer::GetPrimitiveCount( EPrimitiveType type, UInt32 indexCount ) const 
{
    switch( type )
    {
    case nPrimitiveType_TriangleList:
        return indexCount / 3;

    case nPrimitiveType_LineStrip:
        return indexCount - 1;

    default:
        break;
    }

    DebugError( "Unsuported primitive type" );

    return 0;

}

const Byte* CGeometryIndexBuffer::GetRawData() const
{
    return m_RawData.GetBuffer();
}

UInt32 CGeometryIndexBuffer::GetRawDataByteCount() const
{
    return m_RawData.GetItemCount();
}

CBufferVisitor  CGeometryIndexBuffer::GetBufferVisitor( const Byte* rawData ) const
{
    return CBufferVisitor( rawData, 0, sizeof( UInt32 ), GetIndexCount() );
}

Bool CGeometryIndexBuffer::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;
	UInt32 dataByteCount = GetRawDataByteCount();

	if( ar.BeginScope( WT("IndexBuffer"), version ) == version )
	{
		ar.Serialize( m_IndexCount, WT("IndexCount") );

		ar.Serialize( m_DrawIndexCount, WT("DrawIndexCount") );

		ar.Serialize( m_IndexByteCount, WT("IndexByteCount") );

		ar.Serialize( dataByteCount, WT("DataByteCount") );
		
		if( dataByteCount )
		{
			if( ar.IsLoading() )
				m_RawData.SetItemCount( dataByteCount );
			ar.Serialize( m_RawData.GetBuffer(), dataByteCount, WT("RawData") );
		}

		ar.EndScope();
	}

	return CManagedObject::Serialize( ar );
}
