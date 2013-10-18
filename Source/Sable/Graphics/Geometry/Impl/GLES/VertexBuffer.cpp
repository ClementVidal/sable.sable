#include <Sable/Graphics/Geometry/Impl/GLES/VertexBuffer.h>

#include <Sable/Core/Math/Vector3f.h>
#include <Sable/Core/Math/Vector2f.h>
#include <Sable/Graphics/Common/DataTypes.h>
#include <Sable/Graphics/Geometry/VertexBuffer.h>
#include <Sable/Graphics/Geometry/VertexLayout.h>

#include <GLES2/gl2ext.h>

using namespace Sable;

CImplGLESVertexStream::CImplGLESVertexStream( CGeometryVertexBuffer& stream ):
    CImplStubVertexStream( stream )
{
	m_PublicImpl = &stream;
	m_BufferID = 0;
	m_LockedVertexCount = 0;
	m_LockedVertexStart = 0;
}

CImplGLESVertexStream::~CImplGLESVertexStream()
{
	UnInitialize();
}

Void CImplGLESVertexStream::UnInitialize()
{
	if( m_BufferID != 0 )
	{
		glDeleteBuffers( 1, &m_BufferID );
	}
}

Void CImplGLESVertexStream::Activate( const UInt8 streamIndex )
{
	DebugAssert( m_BufferID != 0 );
	DebugAssertGLCall( glBindBuffer( GL_ARRAY_BUFFER, m_BufferID ) );
}

Void CImplGLESVertexStream::Initialize( )
{
	GLenum usage =  GL_STATIC_DRAW;

	if( m_PublicImpl->GetAttribute( CGeometryVertexBuffer::nFlag_Dynamic ) )
		usage = GL_DYNAMIC_DRAW;

	DebugAssertGLCall( glGenBuffers( 1, &m_BufferID ) );

	DebugAssertGLCall( glBindBuffer( GL_ARRAY_BUFFER, m_BufferID ) );

	DebugAssertGLCall( glBufferData( GL_ARRAY_BUFFER, m_PublicImpl->GetVertexByteCount() * m_PublicImpl->GetVertexCount(), m_PublicImpl->GetRawData(), usage ) );

}

Bool CImplGLESVertexStream::IsInitialized() const
{
	return m_BufferID != 0;
}

Byte* CImplGLESVertexStream::Lock( UInt32 vertexStart, UInt32 vertexCount )
{
	DebugAssert( m_LockedVertexCount == 0 );

	m_LockedVertexCount = vertexCount==0?m_PublicImpl->GetVertexCount():vertexCount;
	m_LockedVertexStart = vertexStart;

	DebugAssert( m_PublicImpl->GetRawData() != NULL );
	return ((Byte*)m_PublicImpl->GetRawData()) + m_LockedVertexStart*m_PublicImpl->GetVertexByteCount();
}

Void CImplGLESVertexStream::UnLock( )
{	
	DebugAssert( m_LockedVertexCount != 0 );

	Byte* rawData = ((Byte*)m_PublicImpl->GetRawData()) + m_LockedVertexStart*m_PublicImpl->GetVertexByteCount();
	int previousBuffer = -1;

	DebugAssertGLCall( glGetIntegerv( GL_ARRAY_BUFFER_BINDING, &previousBuffer ) );
	DebugAssertGLCall( glBindBuffer( GL_ARRAY_BUFFER, m_BufferID ) );
	DebugAssertGLCall( glBufferSubData( GL_ARRAY_BUFFER, 
		m_LockedVertexStart*m_PublicImpl->GetVertexByteCount(), 
		m_LockedVertexCount*m_PublicImpl->GetVertexByteCount(),
		rawData) );

	DebugAssertGLCall( glBindBuffer( GL_ARRAY_BUFFER, previousBuffer ) );

	m_LockedVertexCount = 0;
	m_LockedVertexStart = 0;
}
