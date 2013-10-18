#ifndef _SABLE_GRAPHICS_GEOMETRY_IMPL_STUB_VERTEXSTREAM_
#define _SABLE_GRAPHICS_GEOMETRY_IMPL_STUB_VERTEXSTREAM_

#include <Sable/Core/Common/DataTypes.h>

namespace Sable
{

class CGeometryVertexBuffer;

/** 
Interface Wrapper for both static and dynamic vertex buffer manipulation 
*/
class CImplStubVertexStream
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CImplStubVertexStream( CGeometryVertexBuffer& stream );
	virtual ~CImplStubVertexStream();
	//@}

	/** @name Manipulator*/
	//@{
	virtual Bool	IsInitialized() const { return TRUE; }
    virtual Void	Initialize( CGeometryVertexBuffer& stream ) {}
    virtual Void	UnInitialize( ) {}
	virtual Void	Activate( CGeometryVertexBuffer& stream, const UInt8 streamIndex ) {}
	virtual Byte*	Lock( CGeometryVertexBuffer& stream, UInt32 start, UInt32 size ) { return NULL; }
	virtual Void	UnLock( ) {}
	//@}

protected:

	// Attribute
	CGeometryVertexBuffer*	m_PublicImpl;

};

}

#endif
