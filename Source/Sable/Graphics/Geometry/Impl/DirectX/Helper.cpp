#include <Sable/Graphics/Geometry/Impl/DirectX/Helper.h>

#include <Sable/Graphics/Common/Impl/DirectX/GraphicsManagerHelper.h>

using namespace Sable;

CImplDirectXGeometryHelper  ImplMswGeometryHelper;

CImplDirectXGeometryHelper::CImplDirectXGeometryHelper()
{
    MemoryFill( ActiveVertexBuffer, 0, sizeof( ID3D10Buffer* ) * 8 );
}

CImplDirectXGeometryHelper::~CImplDirectXGeometryHelper()
{

}

Void CImplDirectXGeometryHelper::Flush()
{
    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();

    ID3D10Buffer* buffer[8];
    UInt32 stride[8];
    UInt32 offset[8];
    UInt32 vbCount = 0;
    UInt32 totaleByteCOunt = 0;

    for(UInt32 i=0;i<8;i++)
    {
        if( ActiveVertexBuffer[i] )
        {
            buffer[i] = ActiveVertexBuffer[i]->m_VertexBuffer;
            stride[i] = ActiveVertexBuffer[i]->m_PublicImpl->GetVertexByteCount();
            offset[i] = 0;

            totaleByteCOunt += ActiveVertexBuffer[i]->m_PublicImpl->GetVertexByteCount();

            vbCount++;
        }
    }

    device->IASetVertexBuffers( 0, vbCount, buffer, stride, offset );
}

Void CImplDirectXGeometryHelper::ActivateVertexBuffer( UInt32 index, CImplDirectXVertexStream* rt )
{
    ActiveVertexBuffer[index] = rt;

    Flush();
}
