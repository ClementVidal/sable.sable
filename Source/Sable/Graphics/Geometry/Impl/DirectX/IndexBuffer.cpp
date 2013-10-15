#include <Sable\Graphics\Geometry\Impl\DirectX\IndexBuffer.h>

#include <Sable\Graphics\Common\Impl\Stub\GraphicsManager.h>
#include <Sable\Graphics\Common\Impl\DirectX\GraphicsManagerHelper.h>

using namespace Sable;

CImplDirectXIndexBuffer::CImplDirectXIndexBuffer():
    CImplStubIndexBuffer()
{
	m_IndexBuffer = NULL;
	m_IsR32UInt = FALSE;
}

CImplDirectXIndexBuffer::~CImplDirectXIndexBuffer()
{
	UnInitialize();
}

Void CImplDirectXIndexBuffer::UnInitialize()
{
	if( m_IndexBuffer )
	{
		UInt32 r  = m_IndexBuffer->Release();
		DebugAssert( r == 0 );
	}
	m_IndexBuffer = NULL;
}

Bool CImplDirectXIndexBuffer::IsInitialized() const
{
	return m_IndexBuffer != NULL;
}

Void CImplDirectXIndexBuffer::Initialize( UInt32 indexCount, Byte* data, UInt32 byteCount )
{
    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();

    m_Usage = D3D10_USAGE_DEFAULT;

    D3D10_BUFFER_DESC bd;
	MemoryFill( &bd, 0, sizeof( bd ) );
    bd.Usage = m_Usage;
    bd.ByteWidth = byteCount;
    bd.BindFlags = D3D10_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;

    DebugAssert( byteCount == bd.ByteWidth );

    D3D10_SUBRESOURCE_DATA subRscData;
    subRscData.pSysMem = data;
    subRscData.SysMemPitch = 0;
    subRscData.SysMemSlicePitch = 0;

	AssertDXCall( device->CreateBuffer( &bd, data?&subRscData:NULL, &m_IndexBuffer ) );

	UInt32 inedxSize = ( byteCount / indexCount );
	if( inedxSize == 4)
	{
		m_IsR32UInt = TRUE;
	}
	else if( inedxSize == 2)
	{
		m_IsR32UInt = FALSE;
	}
	else 
	{
		DebugError("Invalid index buffer byte size" );
	}


}

Void	CImplDirectXIndexBuffer::Activate( )
{
    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();
	device->IASetIndexBuffer( m_IndexBuffer, m_IsR32UInt?DXGI_FORMAT_R32_UINT:DXGI_FORMAT_R16_UINT, 0 );
}

