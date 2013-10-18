#include <Sable/Graphics/Geometry/Impl/Stub/VertexBuffer.h>

using namespace Sable;

CImplStubVertexStream::CImplStubVertexStream( CGeometryVertexBuffer& stream )
{
	m_PublicImpl = &stream;
}

CImplStubVertexStream::~CImplStubVertexStream()
{
}