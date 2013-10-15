#ifndef _SABLE_GRAPHICS_GEOMETRY_IMPL_MSW_VERTEXSTREAM_
#define _SABLE_GRAPHICS_GEOMETRY_IMPL_MSW_VERTEXSTREAM_

#include <Sable\Graphics\Geometry\Impl\Stub\VertexBuffer.h>
#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

/** 
DirectX9 Wrapper for VertexBuffer
*/
class CImplDirectXVertexStream : public CImplStubVertexStream
{

public:

	/** @name Constructor / Destructor*/
	//@{
	CImplDirectXVertexStream( CGeometryVertexBuffer& stream );
	~CImplDirectXVertexStream();
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
    friend class CImplDirectXGeometryHelper;

	//Method

	//Attribute
	D3D10_USAGE             m_Usage;
	UInt16                  m_VertexCount;
	ID3D10Buffer*           m_VertexBuffer;
	EBufferAcces			m_AllowedAcces;

};

}

#endif
