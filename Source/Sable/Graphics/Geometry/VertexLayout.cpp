#include <Sable/Graphics/Geometry/VertexLayout.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CGeometryVertexLayout, CManagedObject );

CGeometryVertexLayout::CGeometryVertexLayout() :
	m_Impl( *this )
{
	m_ElementCount = 0;
	m_VertexByteCount = 0;
	m_IsActivated = FALSE;
}

CGeometryVertexLayout::~CGeometryVertexLayout()
{
}

const CGeometryVertexElement& CGeometryVertexLayout::GetElementAtIndex( const Index index ) const
{
	return m_ElementTable[ index ];
}

UInt32 CGeometryVertexLayout::GetElementCount() const
{
	return m_ElementCount;
}

UInt32 CGeometryVertexLayout::GetVertexByteCount() const
{
	return m_VertexByteCount;
}

/**
Return a buffer visitor ready to visit each vertex component identified by the given semantic.
If the given semantic does not exist in this stream, return in invalid BufferVisitor.
\note rawData is a pointer previously obtained by either CGeometryVertexBuffer::Lock() or CGeometryVertexBuffer::GetRawData()
*/
CBufferVisitor CGeometryVertexLayout::GetBufferVisitor( EVertexComponent semantic, UInt32 vertexCount, const Byte* rawData ) const
{
    if( rawData == NULL )
        return CBufferVisitor();

    UInt32 i;
    for(i=0;i<m_ElementCount;i++)
    {
        if( m_ElementTable[i].Semantic == semantic )
        {
            return CBufferVisitor( rawData, m_ElementTable[i].ByteOffset, m_VertexByteCount, vertexCount );
        }
    }

    return CBufferVisitor();
}

Bool CGeometryVertexLayout::HasPerInstanceData() const
{
    UInt32 i;
    for(i=0;i<m_ElementCount;i++)
    {
        if( m_ElementTable[i].IsPerInstanceData )
        {
            return TRUE;
        }
    }

    return FALSE;
}

Void CGeometryVertexLayout::Activate( CRenderer& renderer )
{
	DebugGraphicCommandGroup( "CGeometryVertexLayout::Activate" );
	m_IsActivated = TRUE;
	m_Impl.Activate();
}

Void CGeometryVertexLayout::Initialize()
{
	if( m_Impl.IsInitialized() )
		return;

	m_Impl.Initialize();
}

Void CGeometryVertexLayout::UnInitialize()
{
	if( m_Impl.IsInitialized() )
	{
		m_Impl.UnInitialize( );
	}
}

Bool CGeometryVertexLayout::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;
	UInt32 i;

	if( ar.BeginScope( WT("Stream"), version ) == version )
	{
        ar.Serialize( m_ElementCount, WT("ElementCount") );

		for( i=0;i<m_ElementCount;i++)
		{
			if( ar.BeginScope( WT("Element"), version ) == version )
			{
				UInt32 tmp;
				ar.Serialize( m_ElementTable[i].ByteOffset, WT("ByteOffset") );
				ar.Serialize( m_ElementTable[i].StreamIndex, WT("StreamIndex") );
                ar.Serialize( m_ElementTable[i].IsPerInstanceData, WT("IsPerInstanceData") );
                
				tmp = (UInt32) m_ElementTable[i].Semantic;
				ar.Serialize( tmp, WT("Semantic") );
				m_ElementTable[i].Semantic = ( EVertexComponent )tmp;

				tmp = (UInt32) m_ElementTable[i].Type;
				ar.Serialize( tmp, WT("Type") );
				m_ElementTable[i].Type = ( EVertexComponentType )tmp;

				ar.EndScope();
			}
		}
		ar.EndScope();
	}

	return TRUE;
}

UInt32 CGeometryVertexLayout::GetVertexComponentByteCount( EVertexComponentType type ) const
{
	static UInt32 typeName[3] = { sizeof( CVector2f ),  sizeof( CVector3f ),  sizeof( CVector4f ) };

	return typeName[type];
}

/**
**/
Void CGeometryVertexLayout::AddElement( EVertexComponent semantic, EVertexComponentType type, UInt32 streamIndex, Bool perInstanceData )
{
	m_ElementTable[ m_ElementCount ].Semantic = semantic;
	m_ElementTable[ m_ElementCount ].Type = type;
	m_ElementTable[ m_ElementCount ].ByteOffset = m_VertexByteCount;
	m_ElementTable[ m_ElementCount ].StreamIndex = streamIndex;
    m_ElementTable[ m_ElementCount ].IsPerInstanceData = perInstanceData;
	m_VertexByteCount += GetVertexComponentByteCount( type );
	m_ElementCount++;
}

Bool CGeometryVertexLayout::HasElement( EVertexComponent semantic ) const
{
	Index index;

	for( index = 0; index < m_ElementCount; index ++ )
	{
		if ( m_ElementTable[ index ].Semantic == semantic )
			return TRUE;
	}

	return FALSE;
}

const CGeometryVertexElement& CGeometryVertexLayout::GetElementAtSemantic( EVertexComponent semantic ) const
{
	Index
		index;

	for( index = 0; index < m_ElementCount; index ++ )
	{
		if ( m_ElementTable[ index ].Semantic == semantic )
			return m_ElementTable[ index ];
	}

	DebugError( "Invalid semantic" );

	return *(CGeometryVertexElement*)(NULL);
}

UInt32 CGeometryVertexLayout::GetElementStreamIndex( EVertexComponent semantic ) const
{
	Index
		index;

	for( index = 0; index < m_ElementCount; index ++ )
	{
		if ( m_ElementTable[ index ].Semantic == semantic )
			return m_ElementTable[ index ].StreamIndex;
	}

	DebugError( "Invalid semantic" );
	return 0;
}
