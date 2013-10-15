#include <Sable\Graphics\Geometry\Impl\DirectX\VertexBuffer.h>
#include <Sable\Graphics\Geometry\Impl\DirectX\Helper.h>

#include <Sable\Core\Math\Vector3f.h>
#include <Sable\Core\Math\Vector2f.h>
#include <Sable\Graphics\Common\DataTypes.h>
#include <Sable\Graphics\Geometry\VertexBuffer.h>
#include <Sable\Graphics\Geometry\VertexLayout.h>
#include <Sable\Graphics\Common\Impl\DirectX\GraphicsManager.h>

using namespace Sable;

extern CImplDirectXGeometryHelper  ImplMswGeometryHelper;

CImplDirectXVertexStream::CImplDirectXVertexStream( CGeometryVertexBuffer& stream ):
    CImplStubVertexStream( stream )
{
	m_VertexBuffer = NULL;
}

CImplDirectXVertexStream::~CImplDirectXVertexStream()
{
	UnInitialize();
}

Void CImplDirectXVertexStream::UnInitialize()
{
	if( m_VertexBuffer )
	{
		UInt32 r  = m_VertexBuffer->Release();
        //REFACTORDX10
		//DebugAssert( r == 0 );
	}
	m_VertexBuffer = NULL;
}

Void CImplDirectXVertexStream::Activate( const UInt8 streamIndex )
{
    ImplMswGeometryHelper.ActivateVertexBuffer( streamIndex, (CImplDirectXVertexStream *)this );
}

Void CImplDirectXVertexStream::Initialize( )
{
	UnInitialize();

	if( m_PublicImpl->GetVertexCount() == 0 || m_PublicImpl->GetVertexByteCount() == 0 )
		return;

    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();

	// Prepare resources flags
	D3D10_CPU_ACCESS_FLAG access = D3D10_CPU_ACCESS_READ;
    m_Usage = D3D10_USAGE_DEFAULT;

    if( m_PublicImpl->GetAttribute( CGeometryVertexBuffer::nFlag_Dynamic )  )
    {
        m_Usage = D3D10_USAGE_DYNAMIC;
        m_AllowedAcces = nBufferAcces_Write;	
		access = D3D10_CPU_ACCESS_WRITE;
    }
    else 
    {
        m_AllowedAcces = nBufferAcces_None;	
		access = (D3D10_CPU_ACCESS_FLAG)0;
    }

	// Create resource
    D3D10_BUFFER_DESC bd;
	MemoryFill( &bd, 0, sizeof( bd ) );
    bd.Usage = m_Usage;
    bd.ByteWidth = m_PublicImpl->GetVertexByteCount() * m_PublicImpl->GetVertexCount();
    bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = access;
    bd.MiscFlags = 0;
	
	if( m_PublicImpl->GetAttribute( CGeometryVertexBuffer::nFlag_Dynamic )  )
	{
		AssertDXCall( device->CreateBuffer( &bd, NULL, &m_VertexBuffer ) );
	}
	else
	{
		// Fill in the subresource data.
		D3D10_SUBRESOURCE_DATA initData;
		initData.pSysMem = m_PublicImpl->GetRawData();
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;

		AssertDXCall( device->CreateBuffer( &bd, &initData, &m_VertexBuffer ) );
	}

	// Load data into resource
	if( m_PublicImpl->GetRawData() == NULL )
		return;

    if( m_PublicImpl->GetAttribute( CGeometryVertexBuffer::nFlag_Dynamic )  )
	{
		Byte* streamData = Lock( 0,0 );

		MemoryCopy( (Void*) m_PublicImpl->GetRawData(), streamData, m_PublicImpl->GetRawDataByteCount() );

		UnLock( );
	}
}

Bool CImplDirectXVertexStream::IsInitialized() const
{
	return m_VertexBuffer != NULL;
}

Byte* CImplDirectXVertexStream::Lock( UInt32 vertexStart, UInt32 vertexCount )
{
	void* pData = NULL;
	D3D10_MAP lockFlags;

	lockFlags = D3D10_MAP_WRITE;

	if( m_AllowedAcces == nBufferAcces_Read )
	{
		lockFlags = D3D10_MAP_READ;
	}

	if( m_Usage == D3D10_USAGE_DYNAMIC )
	{
		lockFlags = D3D10_MAP_WRITE_NO_OVERWRITE;
        if( !m_PublicImpl->GetAttribute( CGeometryVertexBuffer::nFlag_DoNotDiscard ) )
        {
			lockFlags = D3D10_MAP_WRITE_DISCARD;
        }
	}

#ifdef SETUP_CONFIG_DEBUG
    
    D3D10_BUFFER_DESC desc;
	if( m_VertexBuffer )
	{
		m_VertexBuffer->GetDesc( &desc );
		DebugAssert( (vertexStart*m_PublicImpl->GetVertexByteCount()+vertexCount*m_PublicImpl->GetVertexByteCount() ) <= desc.ByteWidth );
	}
#endif

	if( m_VertexBuffer )
	{
		AssertDXCall( m_VertexBuffer->Map( lockFlags, 0, &pData ) );

		return ((Byte*)pData) + vertexStart*m_PublicImpl->GetVertexByteCount();
	}

	return NULL;
}

Void CImplDirectXVertexStream::UnLock( )
{
	if( m_VertexBuffer )
		m_VertexBuffer->Unmap();
}
