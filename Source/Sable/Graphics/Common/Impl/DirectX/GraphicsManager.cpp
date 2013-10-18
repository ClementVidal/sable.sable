#include <Sable/Graphics/Common/Impl/DirectX/GraphicsManager.h>

#include <Sable/Graphics/Common/Impl/DirectX/GraphicsManagerHelper.h>

using namespace Sable;

CImplDirectXGraphicsManager::CImplDirectXGraphicsManager()
{
    m_D3DState.Clear();
    m_Device = NULL;
    m_LastPrimitiveType = nPrimitiveType_None;
}

ID3D10Device* CImplDirectXGraphicsManager::GetDevice()
{
    return m_Device;
}

Bool	CImplDirectXGraphicsManager::Initialize( CGraphicsManager& manager )
{
    m_PublicInterface = &manager;

    UInt32 flags = 0;
    IDXGIAdapter* selectedAdapter = NULL;
    D3D10_DRIVER_TYPE driverType = D3D10_DRIVER_TYPE_HARDWARE;

#ifdef SETUP_CONFIG_DEBUG
    flags = D3D10_CREATE_DEVICE_DEBUG;
#endif

    AssertDXCall( D3D10CreateDevice( selectedAdapter,
        driverType,
        NULL,
        flags,
        D3D10_SDK_VERSION,
        &m_Device ) );

#ifdef SETUP_CONFIG_DEBUG
	IDXGIDevice * pDXGIDevice;
	IDXGIAdapter * pDXGIAdapter;
	AssertDXCall( m_Device->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice) );
	AssertDXCall( pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&pDXGIAdapter) );

	DXGI_ADAPTER_DESC desc;
	pDXGIAdapter->GetDesc( &desc );

	Char description[256];
	WStringToString( desc.Description, description, 256 );
	DebugLogInfo("-----------------------------");
	DebugLogInfo("Description: %s", description );
	DebugLogInfo("DedicatedVideoMemory: %f mo", desc.DedicatedVideoMemory / 1024.0f / 1024.0f );
	DebugLogInfo("DedicatedSystemMemory: %f mo", desc.DedicatedSystemMemory / 1024.0f / 1024.0f );
	DebugLogInfo("SharedSystemMemory: %f mo", desc.SharedSystemMemory / 1024.0f / 1024.0f );
	DebugLogInfo("-----------------------------");
#endif

	return TRUE;
}

Bool	CImplDirectXGraphicsManager::UnInitialize()
{
    return TRUE;
}

Bool CImplDirectXGraphicsManager::Draw( EPrimitiveType primitive, UInt32 vertexCount, UInt32 offset )
{
    SetPrimitiveType( primitive );
	GetDevice()->Draw( vertexCount, offset );
    return TRUE;
}

Bool CImplDirectXGraphicsManager::DrawIndexedInstanced( EPrimitiveType primitive, UInt32 indexCount, UInt32 startIndexLocation, UInt32 baseVertexLocation, UInt32 instanceCount )
{
	SetPrimitiveType( primitive );
	GetDevice()->DrawIndexedInstanced( indexCount, instanceCount, startIndexLocation, baseVertexLocation, 0 );
	return TRUE;
}

Bool CImplDirectXGraphicsManager::DrawInstanced( EPrimitiveType primitive, UInt32 vertexCount, UInt32 offset, UInt32 instanceCount )
{
	SetPrimitiveType( primitive );
	GetDevice()->DrawInstanced( vertexCount, instanceCount, offset, 0 );
	return TRUE;
}

Void CImplDirectXGraphicsManager::SetPrimitiveType( EPrimitiveType primitive )
{
    if( primitive != m_LastPrimitiveType )
    {
        if( primitive == nPrimitiveType_TriangleList )
            GetDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
        else if( primitive == nPrimitiveType_TriangleStrip )
            GetDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
        else if( primitive == nPrimitiveType_LineList )
            GetDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINELIST );
        else if( primitive == nPrimitiveType_LineStrip )
            GetDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP );
        else if( primitive == nPrimitiveType_PointList )
            GetDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_POINTLIST );
        else 
        {
            DebugError("");
        }

        m_LastPrimitiveType = primitive;
    }
}

Bool CImplDirectXGraphicsManager::DrawIndexed( EPrimitiveType primitive, UInt32 indexCount, UInt32 startIndexLocation, UInt32 baseVertexLocation )
{
    SetPrimitiveType( primitive );
	GetDevice()->DrawIndexed( indexCount, startIndexLocation, baseVertexLocation );
    return TRUE;
}
