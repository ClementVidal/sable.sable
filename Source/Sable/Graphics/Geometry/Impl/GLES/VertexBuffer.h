#ifndef _SABLE_GRAPHICS_GEOMETRY_IMPL_GLES_VERTEXSTREAM_
#define _SABLE_GRAPHICS_GEOMETRY_IMPL_GLES_VERTEXSTREAM_

#include <Sable/Graphics/Geometry/Impl/Stub/VertexBuffer.h>
#include <Sable/Core/Common/DataTypes.h>

#include <GLES2/gl2.h>

namespace Sable
{

/** 
DirectX9 Wrapper for VertexBuffer
*/
class CImplGLESVertexStream : public CImplStubVertexStream
{

public:

	/** @name Constructor / Destructor*/
	//@{
	CImplGLESVertexStream( CGeometryVertexBuffer& stream );
	~CImplGLESVertexStream();
	//@}

	/** @name Accessors*/
	//@{
	//@}

	/** @name Manipulator*/
	//@{
	Bool	    IsInitialized() const;
	Void	    Initialize( );
	Void	    UnInitialize( );
	Void	    Activate( const UInt8 streamIndex );
	Byte*	    Lock( UInt32 vertexStart, UInt32 vertexCount );
	Void	    UnLock( );
	//@}

private:

    // Friendship

	//Method

	//Attribute
	CGeometryVertexBuffer*	m_PublicImpl;
    GLuint					m_BufferID;
	UInt32					m_LockedVertexCount;
	UInt32					m_LockedVertexStart;

};

}

#endif
