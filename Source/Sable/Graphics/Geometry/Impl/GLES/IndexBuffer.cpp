#include <Sable\Graphics\Geometry\Impl\GLES\IndexBuffer.h>

#include <Sable\Graphics\Common\Impl\Stub\GraphicsManager.h>

using namespace Sable;

CImplGLESIndexBuffer::CImplGLESIndexBuffer():
    CImplStubIndexBuffer()
{
	m_BufferID = 0;
}

CImplGLESIndexBuffer::~CImplGLESIndexBuffer()
{
	UnInitialize();
}

Void CImplGLESIndexBuffer::UnInitialize()
{
	if( m_BufferID != 0 )
	{
		glDeleteBuffers( 1, &m_BufferID );
	}
}

Bool CImplGLESIndexBuffer::IsInitialized() const
{
	return m_BufferID != 0;
}

Void CImplGLESIndexBuffer::Initialize( UInt32 indexCount, Byte* data, UInt32 byteCount )
{
	GLenum usage =  GL_STATIC_DRAW;

	DebugAssertGLCall( glGenBuffers( 1, &m_BufferID ) );

	DebugAssertGLCall( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_BufferID ) );

	DebugAssertGLCall( glBufferData( GL_ELEMENT_ARRAY_BUFFER, byteCount, data, usage ) );
}

Void CImplGLESIndexBuffer::Activate( )
{
	DebugAssert( m_BufferID != 0 );
	DebugAssertGLCall( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_BufferID ) );
}

