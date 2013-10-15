#ifndef _SABLE_GRAPHICS_GEOMETRY_IMPL_DIRECTX_INDEXBUFFER_
#define _SABLE_GRAPHICS_GEOMETRY_IMPL_DIRECTX_INDEXBUFFER_

#include <Sable\Graphics\Geometry\Impl\Stub\IndexBuffer.h>
#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

/** 
DirectX9 Wrapper for index buffer
*/
class CImplDirectXIndexBuffer : public CImplStubIndexBuffer
{

public:

	/** @name Constructor / Destructor*/
	//@{
	CImplDirectXIndexBuffer( );
	~CImplDirectXIndexBuffer( );
	//@}

	/** @name Manipulator*/
	//@{
	Bool	IsInitialized() const;
	Void	Initialize( UInt32 indexCount, Byte* data, UInt32 byteCount );
	Void 	UnInitialize();
    Void	Activate( );
	//@}

private:

	//Method

	//Atribute
	Bool							m_IsR32UInt;
	D3D10_USAGE						m_Usage;
	ID3D10Buffer*			        m_IndexBuffer;

};

}

#endif
