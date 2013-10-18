#ifndef _SABLE_GRAPHICS_GEOMETRY_IMPL_GLES_INDEXBUFFER_
#define _SABLE_GRAPHICS_GEOMETRY_IMPL_GLES_INDEXBUFFER_

#include <Sable/Graphics/Geometry/Impl/Stub/IndexBuffer.h>
#include <Sable/Core/Common/DataTypes.h>

namespace Sable
{

/** 
DirectX9 Wrapper for index buffer
*/
class CImplGLESIndexBuffer : public CImplStubIndexBuffer
{

public:

	/** @name Constructor / Destructor*/
	//@{
	CImplGLESIndexBuffer( );
	~CImplGLESIndexBuffer( );
	//@}

	/** @name Manipulator*/
	//@{
	Bool	IsInitialized() const;
	Void 	UnInitialize();
	Void	Initialize( UInt32 indexCount, Byte* data, UInt32 byteCount );
    Void	Activate( );
	//@}

private:

	//Method

	//Atribute
    UInt32 	m_BufferID;

};

}

#endif
